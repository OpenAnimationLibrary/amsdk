#!/usr/bin/env python3
"""Build A:M 19.5 x64 HXT plugins using Visual Studio 2022; Python 3.10+.

The SDK is a separately downloaded, checksum-locked dependency. This script
never installs A:M, changes a Visual Studio installation, or runs a plugin.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import shutil
import stat
import struct
import subprocess
import sys
import tempfile
from datetime import datetime, timezone
import urllib.request
import zipfile

HERE = Path(__file__).resolve().parent
EXPORTS = ("HxtLoadCommandEntry", "HxtOnAddCommandMenu", "HxtOnCommand")


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(block)
    return h.hexdigest()


def verify_hash(path: Path, expected: str) -> None:
    if not re.fullmatch(r"[0-9a-f]{64}", expected):
        raise ValueError("The SDK lock must contain a full SHA-256 digest.")
    if sha256(path) != expected:
        raise ValueError("SDK checksum mismatch. Do not bypass this check or mix SDK versions.")


def extract_sdk(archive: Path, destination: Path) -> Path:
    """Reject unsafe names and symlinks before writing any archive members."""
    with zipfile.ZipFile(archive) as z:
        entries = z.infolist()
        if sum(e.file_size for e in entries) > 256 * 1024 * 1024:
            raise ValueError("Unexpectedly large SDK archive.")
        for entry in entries:
            path = PurePosixPath(entry.filename.replace("\\", "/"))
            if path.is_absolute() or ".." in path.parts or ":" in str(path):
                raise ValueError("Unsafe SDK archive member: " + entry.filename)
            if stat.S_ISLNK(entry.external_attr >> 16):
                raise ValueError("Symlinks are not allowed in the SDK archive.")
        z.extractall(destination)
    roots = [p.parent.parent.parent for p in destination.rglob("Entry.h")
             if p.parent.name == "SDK" and p.parent.parent.name == "Include"]
    if len(roots) != 1 or not (roots[0] / "Lib/PC/Plugin_64.lib").is_file():
        raise ValueError("Expected one SDK root with Include/SDK and Lib/PC.")
    return roots[0]


def check_pe(path: Path) -> None:
    """Check PE32+ / AMD64 / DLL without loading the plugin."""
    data = path.read_bytes()
    if len(data) < 64 or data[:2] != b"MZ":
        raise ValueError("Output is not a Windows PE file.")
    offset = struct.unpack_from("<I", data, 0x3c)[0]
    if offset + 26 > len(data) or data[offset:offset + 4] != b"PE\0\0":
        raise ValueError("Invalid PE header.")
    machine = struct.unpack_from("<H", data, offset + 4)[0]
    characteristics = struct.unpack_from("<H", data, offset + 22)[0]
    magic = struct.unpack_from("<H", data, offset + 24)[0]
    if machine != 0x8664 or magic != 0x20b or not characteristics & 0x2000:
        raise ValueError("Expected an x64 PE32+ DLL, not an EXE or 32-bit plugin.")


def run(args: list[str], env: dict[str, str], log: Path,
        check: bool = True) -> str:
    result = subprocess.run(args, env=env, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True,
                            errors="replace", check=False)
    log.write_text(result.stdout, encoding="utf-8")
    print(result.stdout, end="", flush=True)
    if check and result.returncode:
        raise RuntimeError(f"{Path(args[0]).name} failed ({result.returncode}); see {log.name}.")
    return result.stdout


def visual_studio_environment(work: Path) -> tuple[dict[str, str], str]:
    if os.name != "nt":
        raise RuntimeError("Compile on Windows: use the included GitHub Actions workflow.")
    vswhere = Path(os.environ.get("ProgramFiles(x86)", "C:/Program Files (x86)")) / \
        "Microsoft Visual Studio/Installer/vswhere.exe"
    if not vswhere.is_file():
        raise RuntimeError("Visual Studio Installer/vswhere.exe was not found.")
    install = subprocess.check_output([
        str(vswhere), "-latest", "-products", "*", "-version", "[17.0,18.0)",
        "-requires", "Microsoft.VisualStudio.Component.VC.Tools.x86.x64",
        "Microsoft.VisualStudio.Component.VC.ATLMFC", "-property", "installationPath"
    ], text=True, errors="replace").strip()
    if not install:
        raise RuntimeError("VS 2022 with C++ x64 tools and MFC is required. See windows.vsconfig.")
    # A private temporary batch file imports the developer environment. Do not
    # log its 'set' output: environment variables may contain runner secrets.
    batch = work / "vc-env.cmd"
    batch.write_text('@echo off\ncall "' + install +
                     '\\Common7\\Tools\\VsDevCmd.bat" -no_logo -arch=x64 -host_arch=x64 >nul\n'
                     'if errorlevel 1 exit /b 1\nset\n', encoding="utf-8")
    text = subprocess.check_output(["cmd.exe", "/d", "/c", str(batch)],
                                   text=True, errors="replace")
    env = {k.upper(): v for k, v in os.environ.items()}
    for line in text.splitlines():
        if "=" in line and not line.startswith("="):
            key, value = line.split("=", 1)
            env[key.upper()] = value
    for name in ("cl.exe", "link.exe", "rc.exe", "mt.exe", "msbuild.exe", "dumpbin.exe"):
        if not shutil.which(name, path=env.get("PATH", "")):
            raise RuntimeError("Missing Windows build tool: " + name)
    for header in ("afxwin.h", "crtdbg.h", "windows.h"):
        if not any((Path(p) / header).is_file() for p in env.get("INCLUDE", "").split(";") if p):
            raise RuntimeError("Missing required build header: " + header)
    return env, install


def build(args: argparse.Namespace, receipt: dict, output: Path) -> None:
    lock = json.loads((HERE / "sdk.lock.json").read_text(encoding="utf-8"))
    receipt.update(sdk_version=lock["version"], sdk_sha256=lock["sha256"],
                   configuration=args.configuration, architecture="x64", runtime_tested=False)
    project = args.project.resolve()
    if project.suffix.lower() != ".vcxproj" or not project.is_file():
        raise ValueError("--project must name an existing .vcxproj file.")
    # Fresh intermediate and SDK directories prevent stale output or dependency mixing.
    with tempfile.TemporaryDirectory(prefix="am-cloud-") as temp:
        work = Path(temp)
        env, install = visual_studio_environment(work)
        receipt["toolchain"] = {"visual_studio": install,
            "vc_tools_version": env.get("VCTOOLSVERSION"),
            "windows_sdk_version": env.get("WINDOWSSDKVERSION"),
            "runner_image": os.environ.get("ImageVersion"),
            "runner_os": os.environ.get("ImageOS")}
        run([shutil.which("cl.exe", path=env["PATH"]), "/Bv"], env,
            output / "compiler-version.log", check=False)
        archive = args.sdk_zip.resolve() if args.sdk_zip else work / "sdk195.zip"
        if not args.sdk_zip:
            request = urllib.request.Request(lock["url"], headers={"User-Agent": "AM-Cloud-Build/0.1"})
            try:
                with urllib.request.urlopen(request, timeout=60) as response, archive.open("wb") as stream:
                    shutil.copyfileobj(response, stream)
            except Exception as error:
                raise RuntimeError("SDK download failed. On a Windows VM use --sdk-zip with your "
                                   "original sdk195.zip; never substitute the repository's older SDK. "
                                   + str(error)) from error
        verify_hash(archive, lock["sha256"])
        sdk = extract_sdk(archive, work / "sdk")
        bin_dir = work / "bin"
        bin_dir.mkdir()
        msbuild = shutil.which("msbuild.exe", path=env["PATH"])
        run([msbuild, str(project), "/nologo", "/m", "/t:Rebuild",
             "/p:Configuration=" + args.configuration, "/p:Platform=x64",
             "/p:PlatformToolset=v143", "/p:AMSdkRoot=" + str(sdk),
             "/p:OutDir=" + str(bin_dir) + "\\",
             "/p:IntDir=" + str(work / "obj") + "\\"], env, output / "msbuild.log")
        extension = ".hxt" if args.configuration == "Release" else ".hxtd"
        plugins = list(bin_dir.glob("*" + extension))
        if len(plugins) != 1:
            raise RuntimeError("Expected exactly one freshly built " + extension + " plugin.")
        plugin = plugins[0]
        check_pe(plugin)
        dumpbin = shutil.which("dumpbin.exe", path=env["PATH"])
        exports = run([dumpbin, "/nologo", "/exports", str(plugin)], env, output / "exports.log")
        for name in EXPORTS:
            if not re.search(r"\b" + name + r"\b", exports):
                raise RuntimeError("Missing HXT entry point: " + name)
        dependencies = run([dumpbin, "/nologo", "/dependents", str(plugin)], env,
                           output / "dependencies.log")
        # Dependency names, not DLL loading, are inspected here. A:M owns the host DLLs.
        if args.configuration == "Release" and re.search(
                r"\b(?:mfc140ud|mfc140d|msvcp140d|vcruntime140d|ucrtbased)\.dll\b",
                dependencies, re.I):
            raise RuntimeError("Release output depends on a debug runtime.")
        for p in [plugin, *bin_dir.glob("*.pdb")]:
            shutil.copy2(p, output / p.name)
        receipt["plugin"] = {"file": plugin.name, "sha256": sha256(plugin),
                              "exports_checked": list(EXPORTS), "pe_checked": "x64 PE32+ DLL"}
        (output / "SHA256SUMS.txt").write_text(
            sha256(plugin) + "  " + plugin.name + "\n", encoding="utf-8")
        receipt["status"] = "build-and-binary-audit-passed; A:M runtime test pending"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--configuration", choices=("Release", "Debug"), default="Release")
    parser.add_argument("--project", type=Path,
                        default=HERE / "plugins/AMBuildSmoke/AMBuildSmoke.vcxproj")
    parser.add_argument("--sdk-zip", type=Path, help="Use a local, checksum-matching SDK archive")
    parser.add_argument("--output", type=Path, default=HERE / "artifacts")
    args = parser.parse_args()
    output = args.output.resolve()
    # Refuse to delete user files or publish artifacts left over from an earlier run.
    if output.exists() and any(output.iterdir()):
        parser.error("Output directory must be empty. Select a new --output directory.")
    output.mkdir(parents=True, exist_ok=True)
    receipt = {"started_utc": datetime.now(timezone.utc).isoformat(),
               "source_commit": os.environ.get("GITHUB_SHA"), "status": "failed"}
    try:
        build(args, receipt, output)
        print("Build and binary audit passed. Loading in A:M remains a separate test.")
        return 0
    except Exception as error:
        receipt["error"] = str(error)
        print("ERROR: " + str(error), file=sys.stderr)
        return 1
    finally:
        receipt["finished_utc"] = datetime.now(timezone.utc).isoformat()
        (output / "build-receipt.json").write_text(json.dumps(receipt, indent=2) + "\n", encoding="utf-8")


if __name__ == "__main__":
    raise SystemExit(main())
