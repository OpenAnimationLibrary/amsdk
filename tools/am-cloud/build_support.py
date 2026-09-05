"""Pure validation and packaging helpers. These checks never load a plugin."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import shutil
import stat
import struct
import zipfile

EXPORTS = ('HxtLoadCommandEntry', 'HxtOnAddCommandMenu', 'HxtOnCommand')
MAX_ARCHIVE_BYTES = 32 * 1024 * 1024
MAX_EXTRACTED_BYTES = 256 * 1024 * 1024


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
    return digest.hexdigest()


def verify_hash(path: Path, expected: str) -> None:
    if not re.fullmatch(r'[0-9a-f]{64}', expected):
        raise ValueError('SDK lock requires a full lowercase SHA-256.')
    actual = sha256(path)
    if actual != expected:
        raise ValueError(f'SDK checksum mismatch: expected {expected}; received {actual}. '
                         'Restore the approved archive; do not bypass verification.')


def archive_name(name: str) -> PurePosixPath:
    """Reject path traversal and Windows aliases, also when running on Linux."""
    raw = name.replace('\\', '/')
    parts = raw.rstrip('/').split('/')
    reserved = re.compile(r'^(CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])(?:\.|$)', re.I)
    if not raw or raw.startswith('/') or any(
        not part or part in ('.', '..') or part.endswith((' ', '.')) or
        any(ord(c) < 32 or c in '<>:"|?*' for c in part) or reserved.match(part)
        for part in parts
    ):
        raise ValueError('Unsafe archive path: ' + repr(name))
    return PurePosixPath(*parts)


def extract_sdk(archive: Path, destination: Path, configuration: str = 'Release') -> Path:
    if configuration not in ('Release', 'Debug'):
        raise ValueError('Invalid configuration.')
    if destination.exists() or destination.is_symlink():
        raise ValueError('SDK extraction requires a new directory.')
    if archive.stat().st_size > MAX_ARCHIVE_BYTES:
        raise ValueError('SDK archive exceeds size limit.')
    with zipfile.ZipFile(archive) as z:
        entries = z.infolist()
        if len(entries) > 4096 or sum(e.file_size for e in entries) > MAX_EXTRACTED_BYTES:
            raise ValueError('SDK archive exceeds member/expanded size limit.')
        names = {}
        validated = []
        for entry in entries:
            path = archive_name(entry.filename)
            key = str(path).casefold()
            mode = stat.S_IFMT(entry.external_attr >> 16)
            if entry.flag_bits & 1 or mode not in (0, stat.S_IFREG, stat.S_IFDIR):
                raise ValueError('Encrypted or special archive member: ' + entry.filename)
            if key in names:
                raise ValueError('Duplicate/case-colliding archive member: ' + entry.filename)
            names[key] = entry.is_dir()
            validated.append((entry, path))
        for _, path in validated:
            for parent in path.parents:
                if names.get(str(parent).casefold()) is False:
                    raise ValueError('Archive file/directory collision: ' + str(path))
        # All names are validated before the first write. The destination is new.
        destination.mkdir(parents=True)
        for entry, path in validated:
            target = destination.joinpath(*path.parts)
            if entry.is_dir():
                target.mkdir(parents=True, exist_ok=True)
            else:
                target.parent.mkdir(parents=True, exist_ok=True)
                with z.open(entry) as src, target.open('xb') as dst:
                    shutil.copyfileobj(src, dst, 1024 * 1024)  # ZipFile verifies CRC.
    roots = [p.parent.parent.parent for p in destination.rglob('Entry.h')
             if p.parent.name == 'SDK' and p.parent.parent.name == 'Include']
    if len(roots) != 1:
        raise ValueError('Expected exactly one Include/SDK/Entry.h.')
    root = roots[0]
    suffix = '_64' if configuration == 'Release' else '_64d'
    required = ['Include/SDK/Entry.h', 'Include/SDK/Misc.h', 'Include/ObjType.h',
                'Include/3rdParty/Imath/half.h']
    required += [f'Lib/PC/{name}{suffix}.lib' for name in ('FileIO', 'Matrix', 'Plugin', 'SDK')]
    missing = [name for name in required if not (root / name).is_file()]
    if missing:
        raise ValueError('Incomplete SDK: ' + ', '.join(missing))
    return root


def validate_project(value: str, repository: Path) -> Path:
    # Restrict paths before passing a project to MSBuild, not just at shell level.
    if not re.fullmatch(r'[A-Za-z0-9_./ -]+\.vcxproj', value):
        raise ValueError('Project must be a repository-relative .vcxproj path.')
    path = archive_name(value)
    project = (repository / str(path)).resolve()
    allowed = (repository / 'tools/am-cloud/plugins').resolve()
    if not project.is_relative_to(allowed) or not project.is_file():
        raise ValueError('Project must exist below tools/am-cloud/plugins/.')
    return project


def check_pe(path: Path) -> dict:
    """Basic PE bounds, AMD64 DLL and ASLR/NX checks; not a Windows loader."""
    data = path.read_bytes()
    if len(data) < 64 or data[:2] != b'MZ':
        raise ValueError('Not a Windows PE file.')
    pe = struct.unpack_from('<I', data, 0x3c)[0]
    if pe < 64 or pe + 24 > len(data) or data[pe:pe + 4] != b'PE\0\0':
        raise ValueError('Invalid PE signature/header bounds.')
    machine, sections = struct.unpack_from('<HH', data, pe + 4)
    optional_size, flags = struct.unpack_from('<HH', data, pe + 20)
    optional = pe + 24
    table = optional + optional_size
    if machine != 0x8664 or flags & 0x2002 != 0x2002 or flags & 1:
        raise ValueError('Expected a relocatable AMD64 executable-image DLL.')
    if not 1 <= sections <= 96 or optional_size < 112 or table + 40 * sections > len(data):
        raise ValueError('Invalid optional-header/section-table bounds.')
    if struct.unpack_from('<H', data, optional)[0] != 0x20b:
        raise ValueError('Expected PE32+.')
    dll_flags = struct.unpack_from('<H', data, optional + 70)[0]
    if dll_flags & 0x140 != 0x140:
        raise ValueError('ASLR and NX must be enabled.')
    directories = struct.unpack_from('<I', data, optional + 108)[0]
    if directories < 6 or 112 + directories * 8 > optional_size:
        raise ValueError('Invalid PE data directory bounds.')
    if not all(struct.unpack_from('<II', data, optional + 112 + 5 * 8)):
        raise ValueError('Relocation directory is missing.')
    for n in range(sections):
        raw_size, raw_offset = struct.unpack_from('<II', data, table + n * 40 + 16)
        if raw_size and (raw_offset < table + sections * 40 or raw_offset + raw_size > len(data)):
            raise ValueError('Section extends outside file.')
    return {'machine': 'AMD64', 'format': 'PE32+', 'dll': True, 'aslr': True, 'nx': True}


def audit_exports(text: str) -> list[str]:
    # Match real export-table rows, not an error message mentioning an export.
    names = re.findall(r'^\s*\d+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8,16}\s+'
                       r'([A-Za-z_]\w*)(?:\s*=.*)?\s*$', text, re.M)
    missing = set(EXPORTS) - set(names)
    if missing:
        raise ValueError('Missing/unusable command exports: ' + ', '.join(sorted(missing)))
    return sorted(names)


def audit_dependencies(text: str, configuration: str) -> list[str]:
    names = sorted(set(re.findall(r'^\s+([A-Za-z0-9_.-]+\.dll)\s*$', text, re.M | re.I)))
    folded = {n.lower() for n in names}
    if configuration == 'Release':
        required = {'fileio_64.dll', 'plugin_64.dll', 'mfc140.dll'}
        forbidden = re.compile(r'^(?:.+_64d|(?:vcruntime|msvcp|msvcr|mfc|mfcm)\d[\w]*d|ucrtbased)\.dll$', re.I)
    elif configuration == 'Debug':
        required = {'fileio_64d.dll', 'plugin_64d.dll', 'mfc140d.dll'}
        forbidden = re.compile(r'^(?:fileio_64|plugin_64|sdk_64|matrix_64|mfc140u?|vcruntime140(?:_1)?|msvcp140(?:_1|_2|_atomic_wait|_codecvt_ids)?|ucrtbase)\.dll$', re.I)
    else:
        raise ValueError('Invalid configuration.')
    if required - folded:
        raise ValueError('Missing expected host/MFC imports: ' + ', '.join(sorted(required - folded)))
    bad = [n for n in names if forbidden.fullmatch(n)]
    if bad:
        raise ValueError('Mixed Release/Debug dependencies: ' + ', '.join(bad))
    return names


def audit_warnings(text: str, sdk: Path) -> list[str]:
    """Retain exact reviewed locked-SDK diagnostics; reject unreviewed warnings."""
    warnings = sorted(set(re.sub(r'^\d+>', '', line.strip()) for line in text.splitlines()
                          if re.search(r'\bwarning\s+[A-Z]+\d+\s*:', line, re.I)))
    # RGBByte inline bodies arrive via SDK scene headers; the reports do not call
    # their float-to-byte color scaling. See validation/sdk-warning-review.md.
    locations = {
        'Include/FileCons.h': {(83, 21), (84, 21), (85, 20), (86, 20)},
        'Include/RGBByte.h': {(138, 18), (139, 20), (140, 19), (299, 20), (473, 24), (474, 20)},
    }
    expected = {str((sdk / name).resolve()).replace('\\', '/').casefold(): positions
                for name, positions in locations.items()}
    for line in warnings:
        match = re.match(r'^(.+?)\((\d+),(\d+)\): warning ([A-Z]+\d+):', line, re.I)
        accepted = False
        if match:
            filename = str(Path(match[1]).resolve()).replace('\\', '/').casefold()
            row, column = int(match[2]), int(match[3])
            accepted = (match[4].upper() == 'C4244' and
                        (row, column) in expected.get(filename, set()))
        if not accepted:
            raise ValueError('Unreviewed build warning (see msbuild.log): ' + line)
    return warnings


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + '\n', encoding='utf-8')


def seal_package(folder: Path, destination: Path) -> str:
    """Hash every payload file, create a ZIP, verify CRC, then publish atomically."""
    if destination.exists():
        raise ValueError('Refusing to overwrite a package.')
    files = sorted(p for p in folder.rglob('*') if p.is_file())
    if not files or any(p.is_symlink() for p in folder.rglob('*')):
        raise ValueError('Empty package or symlink in package.')
    manifest = folder / 'SHA256SUMS.txt'
    if manifest.exists():
        raise ValueError('Package was already sealed.')
    manifest.write_text(''.join(f'{sha256(p)}  {p.relative_to(folder).as_posix()}\n'
                                for p in files), encoding='utf-8')
    temporary = destination.with_suffix('.tmp')
    destination.parent.mkdir(parents=True, exist_ok=True)
    try:
        with zipfile.ZipFile(temporary, 'x', zipfile.ZIP_DEFLATED) as z:
            for p in [*files, manifest]:
                z.write(p, p.relative_to(folder).as_posix())
        with zipfile.ZipFile(temporary) as z:
            if z.testzip() is not None:
                raise ValueError('Packaged ZIP failed CRC verification.')
        digest = sha256(temporary)
        # x-mode prevents replacement of an existing checksum on accidental reuse.
        with destination.with_suffix('.zip.sha256').open('x', encoding='utf-8') as f:
            f.write(f'{digest}  {destination.name}\n')
        temporary.rename(destination)
        return digest
    finally:
        temporary.unlink(missing_ok=True)
