#!/usr/bin/env python3
"""Build and package one A:M 19.5 x64 command HXT. Python 3.10+; Windows/VS 2022.

No downloads, installation, host execution, automatic deployment or SDK fallback.
"""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET

from build_support import (audit_dependencies, audit_exports, audit_warnings,
                           check_pe, extract_sdk, seal_package, sha256,
                           validate_project, verify_hash, write_json)

HERE = Path(__file__).resolve().parent
REPOSITORY = HERE.parent.parent
DEFAULT_PROJECT = 'tools/am-cloud/plugins/AMBuildSmoke/AMBuildSmoke.vcxproj'


def utc_now() -> str:
    return datetime.now(timezone.utc).isoformat()


def capture(command: list[str], *, env: dict | None = None) -> str:
    result = subprocess.run(command, cwd=REPOSITORY, env=env, capture_output=True,
                            text=True, encoding='utf-8', errors='replace', timeout=60)
    if result.returncode:
        # Do not include the full environment/command or a credential-bearing URL.
        raise RuntimeError(f'{Path(command[0]).name} failed with exit code {result.returncode}.')
    return result.stdout.strip()


def run(command: list[str], env: dict[str, str], log: Path, timeout: int = 600) -> str:
    """Save output as it arrives; terminate the process tree on timeout."""
    print('Running ' + Path(command[0]).name + ' -> ' + log.name, flush=True)
    with log.open('w', encoding='utf-8') as stream:
        with subprocess.Popen(command, cwd=REPOSITORY, env=env, stdout=stream,
                              stderr=subprocess.STDOUT) as process:
            try:
                code = process.wait(timeout=timeout)
            except (subprocess.TimeoutExpired, KeyboardInterrupt):
                if os.name == 'nt':
                    taskkill = Path(os.environ['SystemRoot']) / 'System32/taskkill.exe'
                    subprocess.run([str(taskkill), '/PID', str(process.pid), '/T', '/F'],
                                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                                   timeout=15, check=False)
                process.kill()
                process.wait()
                raise RuntimeError(f'{Path(command[0]).name} interrupted/timed out; see {log.name}.')
    text = log.read_text(encoding='utf-8', errors='replace')
    print(text, end='', flush=True)
    if code:
        raise RuntimeError(f'{Path(command[0]).name} failed ({code}); see {log.name}.')
    return text


def source_info() -> dict:
    commit = capture(['git', 'rev-parse', 'HEAD'])
    tree = capture(['git', 'rev-parse', 'HEAD^{tree}'])
    dirty = bool(capture(['git', 'status', '--porcelain', '--untracked-files=normal', '--',
                          'tools/am-cloud', '.github/workflows/am-plugin-windows.yml']))
    if os.environ.get('GITHUB_ACTIONS') == 'true':
        if dirty or os.environ.get('GITHUB_SHA') != commit:
            raise ValueError('CI checkout is modified or differs from GITHUB_SHA.')
    return {'checkout_commit': commit, 'checkout_tree': tree, 'dirty': dirty,
            'pr_head_commit': os.environ.get('AM_PR_HEAD_SHA') or None,
            'base_commit': os.environ.get('AM_BASE_SHA') or None,
            'repository': os.environ.get('GITHUB_REPOSITORY'),
            'branch': os.environ.get('GITHUB_HEAD_REF') or os.environ.get('GITHUB_REF_NAME'),
            'event': os.environ.get('GITHUB_EVENT_NAME'),
            'run_id': os.environ.get('GITHUB_RUN_ID'),
            'run_number': os.environ.get('GITHUB_RUN_NUMBER'),
            'run_attempt': os.environ.get('GITHUB_RUN_ATTEMPT')}


def visual_studio_environment(work: Path, lock: dict) -> tuple[dict[str, str], Path]:
    if os.name != 'nt':
        raise RuntimeError('Compile on Windows using the included GitHub Actions workflow.')
    for key in ('vc_tools_version', 'compiler_version', 'windows_sdk_version'):
        if not re.fullmatch(r'\d+\.\d+\.\d+(?:\.\d+)?', lock[key]):
            raise ValueError('Invalid toolchain lock field: ' + key)
    vswhere = Path(os.environ.get('ProgramFiles(x86)', 'C:/Program Files (x86)')) / \
        'Microsoft Visual Studio/Installer/vswhere.exe'
    installation = capture([str(vswhere), '-latest', '-products', '*', '-version', '[17.0,18.0)',
                            '-requires', 'Microsoft.VisualStudio.Component.VC.Tools.x86.x64',
                            'Microsoft.VisualStudio.Component.VC.ATLMFC', '-property', 'installationPath'])
    if not installation:
        raise RuntimeError('VS 2022 with x64 C++ tools and MFC is required; see windows.vsconfig.')
    install = Path(installation)
    tools = install / 'VC/Tools/MSVC' / lock['vc_tools_version']
    if not (tools / 'bin/Hostx64/x64/cl.exe').is_file():
        raise RuntimeError('Locked MSVC toolset is absent. Review toolchain.lock.json and revalidate; '
                           'the builder will not silently select another compiler.')
    # Remove inherited command-line overrides and prior developer-shell state.
    env = {k.upper(): v for k, v in os.environ.items()}
    exact = {'CL', '_CL_', 'LINK', '_LINK_', 'INCLUDE', 'LIB', 'LIBPATH',
             'VCTARGETSPATH', 'VCINSTALLDIR', 'VSINSTALLDIR', 'VISUALSTUDIOVERSION'}
    for key in list(env):
        if key in exact or key.startswith(('VSCMD_', 'VCTOOLS', 'WINDOWSSDK')):
            del env[key]
    env['VSLANG'] = '1033'
    env['DOTNET_CLI_UI_LANGUAGE'] = 'en-US'
    env['VSCMD_SKIP_SENDTELEMETRY'] = '1'
    # Values passed through cmd.exe are restricted; the path comes from vswhere.
    if any(c in installation for c in '%!\r\n"'):
        raise ValueError('Unsupported metacharacter in Visual Studio installation path.')
    batch = work / 'vc-env.cmd'
    batch.write_text('@echo off\ncall "' + str(install / 'VC/Auxiliary/Build/vcvarsall.bat') +
                     '" x64 ' + lock['windows_sdk_version'] + ' -vcvars_ver=' +
                     lock['vc_tools_version'] + ' >nul\nif errorlevel 1 exit /b 1\nset\n',
                     encoding='utf-8')
    # set output is parsed in memory, never saved as a diagnostic or artifact.
    text = capture(['cmd.exe', '/d', '/c', str(batch)], env=env)
    for line in text.splitlines():
        if '=' in line and not line.startswith('='):
            key, value = line.split('=', 1)
            env[key.upper()] = value
    for key, expected in [('VCTOOLSVERSION', lock['vc_tools_version']),
                          ('WINDOWSSDKVERSION', lock['windows_sdk_version'])]:
        if env.get(key, '').rstrip('\\/') != expected:
            raise RuntimeError('Developer environment did not select the locked ' + key)
    for name in ('cl.exe', 'link.exe', 'rc.exe', 'mt.exe', 'dumpbin.exe'):
        if not shutil.which(name, path=env.get('PATH', '')):
            raise RuntimeError('Missing build tool: ' + name)
    for header in ('afxwin.h', 'crtdbg.h', 'windows.h'):
        if not any((Path(p) / header).is_file() for p in env.get('INCLUDE', '').split(';') if p):
            raise RuntimeError('Missing build header: ' + header)
    return env, install


def prepare_output(path: Path) -> Path:
    # Never delete/reuse a caller-specified directory, even if it is empty.
    if path.exists() or path.is_symlink():
        raise ValueError('Output must be a NEW directory; choose another --output path.')
    path.mkdir(parents=True)
    (path / 'diagnostics').mkdir()
    return path


def build(args: argparse.Namespace, receipt: dict, output: Path) -> None:
    diagnostics = output / 'diagnostics'
    receipt['stage'] = 'input-validation'
    project = validate_project(args.project, REPOSITORY)
    if ET.parse(project).find('.//{*}ProjectReference') is not None:
        raise ValueError('This builder handles one standalone HXT project, not ProjectReference graphs.')
    receipt['source'] = source_info()
    receipt['project'] = project.relative_to(REPOSITORY).as_posix()
    sdk_lock = json.loads((HERE / 'sdk.lock.json').read_text(encoding='utf-8'))
    tool_lock = json.loads((HERE / 'toolchain.lock.json').read_text(encoding='utf-8'))
    archive = (args.sdk_zip or HERE / 'vendor/sdk195.zip').resolve()
    if not archive.is_file():
        raise ValueError('Complete SDK missing: tools/am-cloud/vendor/sdk195.zip. '
                         'Restore it from this branch; there is no website fallback.')
    if archive.stat().st_size != sdk_lock['size_bytes']:
        raise ValueError('Unexpected SDK size; the approved complete archive has 6,529,791 bytes.')
    verify_hash(archive, sdk_lock['sha256'])
    receipt['sdk'] = {'version': sdk_lock['version'], 'sha256': sha256(archive),
                      'size_bytes': archive.stat().st_size}
    # Rebuild in a fresh checkout-local directory, not Windows TEMP. Only this
    # internally allocated directory is automatically removed on exit.
    work_parent = HERE / '.work'
    work_parent.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='build-', dir=work_parent) as temporary:
        work = Path(temporary).resolve()
        receipt['stage'] = 'sdk-validation'
        sdk = extract_sdk(archive, work / 'sdk', args.configuration)
        receipt['stage'] = 'toolchain-preflight'
        env, install = visual_studio_environment(work, tool_lock)
        compiler = install / 'VC/Tools/MSVC' / tool_lock['vc_tools_version'] / 'bin/Hostx64/x64/cl.exe'
        dumpbin = compiler.with_name('dumpbin.exe')
        msbuild = install / 'MSBuild/Current/Bin/MSBuild.exe'
        probe = work / 'compiler-probe.cpp'
        probe.write_text('#include <crtdbg.h>\nstatic_assert(sizeof(void*) == 8);\n', encoding='utf-8')
        version_text = run([str(compiler), '/Bv', '/c', str(probe),
                            '/Fo' + str(work / 'compiler-probe.obj')], env,
                           diagnostics / 'compiler-version.log', timeout=60)
        actual = re.search(r'Compiler Version ([0-9.]+) for x64', version_text)
        if actual is None or actual.group(1) != tool_lock['compiler_version']:
            raise RuntimeError('Compiler patch version differs from toolchain.lock.json; review and revalidate.')
        receipt['toolchain'] = {**{k: tool_lock[k] for k in
            ('vc_tools_version', 'compiler_version', 'windows_sdk_version')},
            'compiler_sha256': sha256(compiler), 'msbuild_sha256': sha256(msbuild),
            'msbuild_version': capture([str(msbuild), '/nologo', '/version'], env=env),
            'python': platform.python_version(), 'runner_image': os.environ.get('ImageVersion'),
            'runner_os': os.environ.get('ImageOS')}
        receipt['stage'] = 'compile-link'
        bin_dir, obj_dir = work / 'bin', work / 'obj'
        bin_dir.mkdir()
        # Pin both developer-shell and MSBuild selections; MSBuild does not simply
        # inherit toolset selection from vcvarsall. Forward slashes avoid trailing
        # backslash/quote ambiguity when Python marshals Windows arguments.
        command = [str(msbuild), str(project), '/nologo', '/m:1', '/t:Rebuild',
                   '/nodeReuse:false', '/noAutoResponse', '/verbosity:normal',
                   '/p:Configuration=' + args.configuration, '/p:Platform=x64',
                   '/p:PlatformToolset=v143', '/p:VCToolsVersion=' + tool_lock['vc_tools_version'],
                   '/p:WindowsTargetPlatformVersion=' + tool_lock['windows_sdk_version'],
                   '/p:AMSdkRoot=' + sdk.as_posix(),
                   '/p:OutDir=' + bin_dir.as_posix() + '/',
                   '/p:IntDir=' + obj_dir.as_posix() + '/']
        text = run(command, env, diagnostics / 'msbuild.log')
        receipt['stage'] = 'warning-policy'
        receipt['accepted_sdk_warnings'] = audit_warnings(text, sdk)
        extension = '.hxt' if args.configuration == 'Release' else '.hxtd'
        suffix = '_64' if args.configuration == 'Release' else '_64d'
        expected_name = project.stem + suffix + extension
        outputs = sorted(p for p in bin_dir.iterdir() if p.suffix.lower() in ('.hxt', '.hxtd'))
        if len(outputs) != 1 or outputs[0].name != expected_name:
            raise ValueError('Expected exactly one fresh plugin named ' + expected_name)
        plugin = outputs[0]
        receipt['stage'] = 'binary-audit'
        pe = check_pe(plugin)
        exports = audit_exports(run([str(dumpbin), '/nologo', '/exports', str(plugin)], env,
                                    diagnostics / 'exports.log', timeout=60))
        dependencies = audit_dependencies(run([str(dumpbin), '/nologo', '/dependents', str(plugin)],
                                              env, diagnostics / 'dependencies.log', timeout=60),
                                          args.configuration)
        receipt['plugin'] = {'file': plugin.name, 'size_bytes': plugin.stat().st_size,
                             'sha256': sha256(plugin), 'pe': pe,
                             'exports': exports, 'dependencies': dependencies}
        receipt['stage'] = 'packaging'
        package = work / 'package'
        package.mkdir()
        shutil.copy2(plugin, package / plugin.name)
        pdb = plugin.with_suffix('.pdb')
        if not pdb.is_file():
            raise ValueError('Matching PDB was not produced.')
        (package / 'symbols').mkdir()
        shutil.copy2(pdb, package / 'symbols' / pdb.name)
        for name in ('Verify-Package.ps1', 'HOST-TEST.md'):
            shutil.copy2(HERE / name, package / name)
        source = receipt['source']
        readme = (f'A:M CLOUD-BUILD TEST PACKAGE\n\nConfiguration: {args.configuration} x64\n'
                  f'Plugin: {plugin.name}\nSHA-256: {sha256(plugin)}\n'
                  f'Checkout commit: {source["checkout_commit"]}\n'
                  f'PR head: {source["pr_head_commit"]}\n'
                  f'Run: {source["run_number"]}; attempt: {source["run_attempt"]}\n\n'
                  'BUILD AND BINARY AUDIT PASSED. THIS BINARY HAS NOT BEEN HOST-TESTED BY CI.\n'
                  'Read HOST-TEST.md. Run Verify-Package.ps1 before manual installation.\n'
                  'Close A:M, keep a backup OUTSIDE scanned HXT folders, and copy ONLY the plugin.\n'
                  'No compiler or SDK needs to be installed on the test computer.\n')
        if args.configuration == 'Debug':
            readme += '\nDEBUG ONLY: needs the matching DEBUG A:M host and debug runtimes.\nDO NOT install in ordinary Release A:M.\n'
        (package / 'READ-ME-FIRST.txt').write_text(readme, encoding='utf-8')
        payload_receipt = {**receipt, 'status': 'passed', 'stage': 'complete', 'finished_utc': utc_now()}
        write_json(package / 'build-receipt.json', payload_receipt)
        label = re.sub(r'[^A-Za-z0-9_.-]', '-', project.stem)
        run_id = source['run_id'] or 'local'
        attempt = source['run_attempt'] or '1'
        if not re.fullmatch(r'(?:\d+|local)', run_id) or not attempt.isdecimal():
            raise ValueError('Unexpected build identity.')
        name = f'{label}-AM19.5-{args.configuration}-x64-{run_id}-a{attempt}-{source["checkout_commit"][:12]}.zip'
        digest = seal_package(package, output / 'packages' / name)
        receipt.update(payload_receipt)
        receipt['package'] = {'file': name, 'sha256': digest}


def finish(receipt: dict, diagnostics: Path) -> None:
    receipt.setdefault('finished_utc', utc_now())
    write_json(diagnostics / 'build-receipt.json', receipt)
    summary = (f'## A:M {receipt["configuration"]} x64\n\n'
               f'Build/binary audit: **{receipt["status"]}**. Stage: `{receipt["stage"]}`.\n\n'
               '**Host runtime: not tested by CI.** Previous user tests apply only to their recorded binary.\n')
    plugin = receipt.get('plugin')
    if plugin:
        summary += f'\nPlugin: `{plugin["file"]}`\n\nSHA-256: `{plugin["sha256"]}`\n'
    summary += f'\nAccepted locked-SDK diagnostic lines: {len(receipt.get("accepted_sdk_warnings", []))}. See diagnostics.\n'
    if 'error' in receipt:
        # Avoid injecting untrusted text into a Markdown summary; full error is in JSON/logs.
        summary += '\nSee diagnostics/build-receipt.json for the error. No installable artifact is published.\n'
    (diagnostics / 'summary.md').write_text(summary, encoding='utf-8')
    if os.environ.get('GITHUB_STEP_SUMMARY'):
        with open(os.environ['GITHUB_STEP_SUMMARY'], 'a', encoding='utf-8') as f:
            f.write(summary)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--configuration', choices=('Release', 'Debug'), default='Release')
    parser.add_argument('--project', default=DEFAULT_PROJECT)
    parser.add_argument('--sdk-zip', type=Path, help='Optional local copy; must match the same SDK lock')
    parser.add_argument('--output', type=Path, default=HERE / 'artifacts')
    args = parser.parse_args(argv)
    try:
        output = prepare_output(args.output.absolute())
    except (OSError, ValueError) as error:
        parser.error(str(error))
    receipt = {'schema_version': 2, 'started_utc': utc_now(), 'status': 'failed',
               'stage': 'starting', 'configuration': args.configuration,
               'architecture': 'x64', 'runtime_tested': False}
    try:
        build(args, receipt, output)
    except (Exception, KeyboardInterrupt) as error:
        receipt['status'] = 'failed'
        receipt['error'] = str(error) or 'Interrupted'
        print('ERROR: ' + receipt['error'], file=sys.stderr)
        return_code = 1
    else:
        print('Build, binary audit and package integrity passed. A:M runtime test remains separate.')
        return_code = 0
    finish(receipt, output / 'diagnostics')
    return return_code


if __name__ == '__main__':
    raise SystemExit(main())
