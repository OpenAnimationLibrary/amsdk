#!/usr/bin/env python3
"""Create a private GitHub build repository using the user's complete SDK.

Run locally with Python 3.10+, Git and an authenticated GitHub CLI. No Visual
Studio or A:M installation is required. Remote creation/push requires an
interactive confirmation and never reuses an existing remote repository.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys

HERE = Path(__file__).resolve().parent
SOURCE_FILES = (
    '.gitignore', 'README.md', 'build.py', 'diagnose_sdk.py', 'sdk.lock.json',
    'windows.vsconfig', 'start_private_build.py', 'tests/test_build.py',
    'plugins/AMBuildSmoke/AMBuildSmoke.cpp',
    'plugins/AMBuildSmoke/AMBuildSmoke.rc',
    'plugins/AMBuildSmoke/AMBuildSmoke.vcxproj',
    'plugins/AMBuildSmoke/StdAfx.h',
)


def run(command: list[str], cwd: Path | None = None) -> str:
    result = subprocess.run(command, cwd=cwd, capture_output=True, text=True,
                            errors='replace', check=False)
    if result.returncode:
        raise RuntimeError(result.stderr.strip() or result.stdout.strip()
                           or f'{command[0]} exited with {result.returncode}')
    return result.stdout.strip()


def prepare_project(destination: Path, sdk_zip: Path) -> None:
    """Copy only an explicit source allowlist, not unrelated local files."""
    if destination.exists():
        raise ValueError('Destination already exists; choose a NEW directory: ' + str(destination))
    expected = json.loads((HERE / 'sdk.lock.json').read_text(encoding='utf-8'))['sha256']
    if not sdk_zip.is_file():
        raise ValueError('Complete SDK archive not found. Supply --sdk-zip with your original sdk195.zip.')
    if hashlib.sha256(sdk_zip.read_bytes()).hexdigest() != expected:
        raise ValueError('SDK checksum mismatch; the original complete SDK is required.')
    workflow = HERE.parent.parent / '.github/workflows/am-plugin-windows.yml'
    sources = [(HERE / p, Path('tools/am-cloud') / p) for p in SOURCE_FILES]
    sources.append((workflow, Path('.github/workflows/am-plugin-windows.yml')))
    if not all(source.is_file() for source, _ in sources):
        raise ValueError('Setup files are incomplete; extract the complete setup ZIP first.')
    destination.mkdir(parents=True)
    for source, relative in sources:
        target = destination / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)
    vendor = destination / 'tools/am-cloud/vendor'
    vendor.mkdir()
    shutil.copy2(sdk_zip, vendor / 'sdk195.zip')
    (destination / 'README.md').write_text(
        '# Private A:M plugin builder\n\n'
        'This repository contains the owner-supplied A:M SDK for private builds.\n'
        'Do not make this repository public without reviewing SDK redistribution rights.\n\n'
        'See [the build guide](tools/am-cloud/README.md).\n'
        'Open Actions to inspect the first Windows build. A successful build is not an A:M runtime test.\n',
        encoding='utf-8')


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repository', help='New OWNER/NAME; default: your login/am-plugin-build')
    parser.add_argument('--destination', type=Path, help='New local working directory')
    parser.add_argument('--sdk-zip', type=Path, default=HERE / 'vendor/sdk195.zip')
    args = parser.parse_args()
    try:
        for program in ('git', 'gh'):
            if not shutil.which(program):
                raise RuntimeError(f'{program} is required. Install Git / GitHub CLI, then reopen your terminal. '
                                   'No C++ compiler is needed locally.')
        # Authentication stays in gh's credential store, never in a file or argument here.
        run(['gh', 'auth', 'status', '--hostname', 'github.com'])
        account = json.loads(run(['gh', 'api', '--hostname', 'github.com', 'user']))
        repository = args.repository or account['login'] + '/am-plugin-build'
        if not re.fullmatch(r'[A-Za-z0-9][A-Za-z0-9-]*/[A-Za-z0-9_.-]+', repository):
            raise ValueError('--repository must have the form OWNER/NAME.')
        destination = (args.destination or Path.home() / 'AMDev' / repository.split('/')[1]).resolve()
        if destination.exists():
            raise ValueError('Choose a NEW --destination; existing files will not be changed.')
        print(f'Create PRIVATE repository {repository} and working copy {destination}.')
        print('Upload the complete SDK there and start a GitHub-hosted Windows build.')
        print('Private builds use your GitHub Actions allowance; overages can be billed.')
        print('Review your Actions budget before continuing. No A:M license is uploaded.')
        if input('Type CREATE to proceed: ').strip() != 'CREATE':
            print('Cancelled. No repository or working copy was created.')
            return 0
        prepare_project(destination, args.sdk_zip.resolve())
        run(['git', 'init', '--initial-branch=main'], destination)
        run(['git', 'add', '.'], destination)
        # The SDK is deliberately ignored in public source checkouts. This one
        # explicit file is staged ONLY in the fresh, private build repository.
        run(['git', 'add', '-f', 'tools/am-cloud/vendor/sdk195.zip'], destination)
        email = f"{account['id']}+{account['login']}@users.noreply.github.com"
        run(['git', '-c', 'user.name=' + account['login'], '-c', 'user.email=' + email,
             'commit', '-m', 'Set up private Windows build for A:M plugins'], destination)
        # No --push: verify the server reports private before sending SDK bytes.
        run(['gh', 'repo', 'create', repository, '--private', '--source', str(destination),
             '--remote', 'origin'], destination)
        details = json.loads(run(['gh', 'repo', 'view', repository, '--json', 'isPrivate,url'], destination))
        if details.get('isPrivate') is not True:
            raise RuntimeError('Remote is not confirmed PRIVATE. Nothing has been pushed.')
        run(['git', '-c', 'credential.helper=',
             '-c', 'credential.https://github.com.helper=!gh auth git-credential',
             'push', '--set-upstream', 'origin', 'main'], destination)
        print('Private sources pushed. The Windows workflow is triggered by this push.')
        print('Build status: ' + details['url'] + '/actions')
        print('Working copy: ' + str(destination))
        print('Allow this new private repository in your ChatGPT GitHub connection for collaborative development.')
        return 0
    except Exception as error:
        print('ERROR: ' + str(error), file=sys.stderr)
        print('Authentication help: gh auth login --hostname github.com --git-protocol https --web --scopes workflow',
              file=sys.stderr)
        print('A created repository/working copy is left in place on failure; nothing is deleted automatically.',
              file=sys.stderr)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
