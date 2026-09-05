"""Extend one freshly audited native package with this plugin's examples/docs.

Preserve the original build receipt; separately record the original package hash.
This does not load executable code, publish releases, install, or change the HXT.
"""
import ctypes
from ctypes import wintypes
import json
from pathlib import Path
import shutil
import sys
import tempfile
import zipfile

ROOT = Path(__file__).resolve().parent
HERE = ROOT.parent.parent
sys.path.insert(0, str(HERE))
from build_support import archive_name, seal_package, sha256, write_json


def resource_bytes(plugin, identifier):
    kernel = ctypes.WinDLL('kernel32', use_last_error=True)
    kernel.LoadLibraryExW.argtypes = [wintypes.LPCWSTR, wintypes.HANDLE, wintypes.DWORD]
    kernel.LoadLibraryExW.restype = wintypes.HMODULE
    kernel.FindResourceW.argtypes = [wintypes.HMODULE, ctypes.c_void_p, ctypes.c_void_p]
    kernel.FindResourceW.restype = wintypes.HRSRC
    kernel.SizeofResource.argtypes = [wintypes.HMODULE, wintypes.HRSRC]; kernel.SizeofResource.restype = wintypes.DWORD
    kernel.LoadResource.argtypes = [wintypes.HMODULE, wintypes.HRSRC]; kernel.LoadResource.restype = wintypes.HGLOBAL
    kernel.LockResource.argtypes = [wintypes.HGLOBAL]; kernel.LockResource.restype = ctypes.c_void_p
    kernel.FreeLibrary.argtypes = [wintypes.HMODULE]; kernel.FreeLibrary.restype = wintypes.BOOL
    module = kernel.LoadLibraryExW(str(plugin), None, 0x2 | 0x20)  # DATAFILE + IMAGE_RESOURCE: no DllMain
    if not module: raise ctypes.WinError(ctypes.get_last_error())
    try:
        resource = kernel.FindResourceW(module, identifier, 10)
        if not resource: raise ValueError('Embedded runner/bridge missing')
        size = kernel.SizeofResource(module, resource)
        address = kernel.LockResource(kernel.LoadResource(module, resource))
        if not address or not 0 < size <= 262144: raise ValueError('Invalid embedded resource')
        return ctypes.string_at(address, size)
    finally:
        kernel.FreeLibrary(module)


def main():
    packages = list((HERE/'artifacts/packages').glob('*.zip'))
    if len(packages) != 1: raise ValueError('Expected one native package')
    original = packages[0]
    expected = original.with_suffix('.zip.sha256').read_text().split()[0]
    if sha256(original) != expected: raise ValueError('Native ZIP checksum mismatch')
    scratch = HERE / '.work'; scratch.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='script-package-', dir=scratch) as directory:
        folder = Path(directory)
        with zipfile.ZipFile(original) as z:
            entries = z.infolist()
            if len(entries)>32 or sum(e.file_size for e in entries)>64*1024*1024: raise ValueError('Unexpected native payload size')
            names = [str(archive_name(e.filename)) for e in entries]
            if len(set(n.casefold() for n in names)) != len(names): raise ValueError('Duplicate package names')
            if z.testzip(): raise ValueError('Native ZIP integrity failure')
            z.extractall(folder)
        manifest = folder/'SHA256SUMS.txt'
        seen=set()
        for line in manifest.read_text().splitlines():
            digest, name = line.split('  ', 1)
            name = str(archive_name(name))
            if name in seen or sha256(folder/name) != digest: raise ValueError('Native payload mismatch')
            seen.add(name)
        if seen != {p.relative_to(folder).as_posix() for p in folder.rglob('*') if p.is_file() and p!=manifest}:
            raise ValueError('Unexpected native package payload')
        receipt = json.loads((folder/'build-receipt.json').read_text())
        if receipt['status'] != 'passed' or receipt['project'] != 'tools/am-cloud/plugins/AMScriptBuilder/AMScriptBuilder.vcxproj':
            raise ValueError('Wrong or failed project')
        plugin = folder/receipt['plugin']['file']
        if sha256(plugin)!=receipt['plugin']['sha256']: raise ValueError('HXT/receipt mismatch')
        resources = {}
        for identifier, name in ((201,'runner.py'),(202,'ambridge.py')):
            source = ROOT/'runtime'/name
            if resource_bytes(plugin, identifier)!=source.read_bytes(): raise ValueError('Embedded Python resource differs from reviewed source')
            resources[name]=sha256(source)
        for sub, files in {'runtime':['runner.py','ambridge.py'], 'examples':['three_point_spline.py','three_point_spline.json','grid.py','grid.json']}.items():
            (folder/sub).mkdir()
            for name in files: shutil.copy2(ROOT/sub/name, folder/sub/name)
        shutil.copy2(ROOT/'HOST-TEST.md', folder/'HOST-TEST.md')
        shutil.copy2(ROOT/'README.md', folder/'SCRIPT-BUILDER.md')
        (folder/'READ-ME-FIRST.txt').write_text(
            'AMScriptBuilder v1 - NEW MODEL ONLY\n\n'
            f"Configuration: {receipt['configuration']} x64\nPlugin: {plugin.name}\nSHA-256: {receipt['plugin']['sha256']}\n\n"
            'Native build and data/resource checks passed. A:M creation has NOT been host-tested by CI.\n'
            'Run Verify-Package.ps1 and read HOST-TEST.md before installation.\n'
            'With A:M closed, install ONLY the HXT. Keep examples/runtime/docs elsewhere.\n'
            'No Python is needed to import example JSON. Running scripts needs CPython 3.11 python.exe.\n'
            'Only execute reviewed scripts; process limits are NOT a security sandbox.\n'
            'Do not rely on whole-build Undo or automatic rollback. Test in a disposable project.\n'
            + ('\nDEBUG HOST ONLY. Do not install this Debug output into ordinary A:M.\n' if receipt['configuration']=='Debug' else ''), encoding='utf8')
        write_json(folder/'distribution-receipt.json', {'native_package':original.name,
            'native_package_sha256':sha256(original), 'embedded_resources_verified':resources,
            'source':receipt['source'], 'runtime_tested':False})
        manifest.unlink()
        destination = HERE/'artifacts/script-packages'/original.name
        digest = seal_package(folder, destination)
        write_json(HERE/'artifacts/diagnostics/script-package.json', {'file':destination.name,'sha256':digest,'resources':resources})
        print('PASS: embedded Python matches source; examples/docs sealed with the unchanged audited HXT.')
    return 0


if __name__ == '__main__': raise SystemExit(main())
