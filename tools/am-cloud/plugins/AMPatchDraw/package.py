"""Seal Patch Draw instructions with an already audited native package."""
import json
from pathlib import Path
import shutil
import sys
import tempfile
import zipfile

ROOT = Path(__file__).resolve().parent
HERE = ROOT.parents[1]
sys.path.insert(0, str(HERE))
from build_support import archive_name, seal_package, sha256, write_json


def main():
    packages = list((HERE/'artifacts/packages').glob('*.zip'))
    if len(packages) != 1:
        raise ValueError('Expected one freshly audited package')
    original = packages[0]
    if sha256(original) != original.with_suffix('.zip.sha256').read_text().split()[0]:
        raise ValueError('Native archive checksum mismatch')
    with tempfile.TemporaryDirectory(prefix='patch-package-', dir=HERE/'.work') as temp:
        folder = Path(temp)
        with zipfile.ZipFile(original) as archive:
            entries = archive.infolist()
            names = [str(archive_name(e.filename)) for e in entries]
            if len(entries)>32 or sum(e.file_size for e in entries)>64*1024*1024 or len(set(n.casefold() for n in names)) != len(names):
                raise ValueError('Unexpected native archive payload')
            if archive.testzip():
                raise ValueError('Native ZIP integrity failure')
            archive.extractall(folder)
        manifest = folder/'SHA256SUMS.txt'
        seen = set()
        for line in manifest.read_text().splitlines():
            digest, name = line.split('  ', 1)
            name = str(archive_name(name))
            if name in seen or sha256(folder/name) != digest:
                raise ValueError('Native payload checksum mismatch')
            seen.add(name)
        if seen != {p.relative_to(folder).as_posix() for p in folder.rglob('*') if p.is_file() and p!=manifest}:
            raise ValueError('Unexpected unmanifested native file')
        receipt = json.loads((folder/'build-receipt.json').read_text())
        if receipt['status']!='passed' or receipt['project']!='tools/am-cloud/plugins/AMPatchDraw/AMPatchDraw.vcxproj':
            raise ValueError('Wrong or failed native project')
        if sha256(folder/receipt['plugin']['file']) != receipt['plugin']['sha256']:
            raise ValueError('HXT/receipt mismatch')
        shutil.copy2(ROOT/'README.md', folder/'PATCH-DRAW.md')
        shutil.copy2(ROOT/'HOST-TEST.md', folder/'HOST-TEST.md')
        (folder/'READ-ME-FIRST.txt').write_text(
            'AMPatchDraw v0.1 - STAGE B: CANVAS + JSON EXPORT\n\n'
            f"Configuration: {receipt['configuration']} x64\nPlugin: {receipt['plugin']['file']}\n"
            f"SHA-256: {receipt['plugin']['sha256']}\nCheckout: {receipt['source']['checkout_commit']}\n\n"
            'Build/audit checks are not an A:M host test. Verify-Package.ps1 checks file integrity.\n'
            'Close A:M and install ONLY the HXT alongside (not instead of) AMScriptBuilder.\n'
            'Menu: Plugins > Wizards > A:M Patch Draw v0.1 - Canvas\n'
            'Draw/Erase -> Export Plan to a NEW JSON file -> close -> import JSON in Script Builder.\n'
            'This canvas does not create/edit A:M models and needs no Python.\n'
            'Drawing-session Save/Load and direct native construction are not implemented yet.\n'
            'Read PATCH-DRAW.md and HOST-TEST.md for limits and the ring test.\n'
            + ('DEBUG HOST ONLY: not for ordinary A:M.\n' if receipt['configuration']=='Debug' else ''), encoding='utf-8')
        write_json(folder/'distribution-receipt.json', {
            'native_package':original.name, 'native_package_sha256':sha256(original),
            'source':receipt['source'], 'scope':'stage-B canvas and plan export; no native modeling',
            'runtime_tested':False})
        manifest.unlink()
        destination = HERE/'artifacts/patch-draw-packages'/original.name
        digest = seal_package(folder, destination)
        write_json(HERE/'artifacts/diagnostics/patch-draw-package.json', {'file':destination.name,'sha256':digest})
        print('PASS: audited HXT unchanged; stage-specific documentation sealed')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
