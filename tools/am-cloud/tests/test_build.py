"""Failure-path tests. Native build and A:M host validation are separate gates."""
from __future__ import annotations
import contextlib
import hashlib
import importlib.util
import io
import json
import os
from pathlib import Path
import stat
import struct
import sys
import tempfile
import unittest
from unittest import mock
import zipfile

HERE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(HERE))
import build
import build_support as support


class IsolatedTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)

    def zip(self, entries):
        path = self.root / 'input.zip'
        with zipfile.ZipFile(path, 'w') as z:
            for name, data in entries:
                z.writestr(name, data)
        return path

    def sdk_entries(self, debug=False):
        prefix = 'SDK/V19_5/'
        names = ['Include/SDK/Entry.h', 'Include/SDK/Misc.h', 'Include/ObjType.h',
                 'Include/3rdParty/Imath/half.h']
        suffix = '_64d' if debug else '_64'
        names += [f'Lib/PC/{name}{suffix}.lib' for name in ('FileIO', 'Matrix', 'Plugin', 'SDK')]
        return [(prefix + name, b'test fixture') for name in names]


class HashTests(IsolatedTest):
    def test_exact_hash(self):
        p = self.root / 'input'; p.write_bytes(b'abc')
        support.verify_hash(p, hashlib.sha256(b'abc').hexdigest())

    def test_mismatch(self):
        p = self.root / 'input'; p.write_bytes(b'abc')
        with self.assertRaisesRegex(ValueError, 'mismatch'):
            support.verify_hash(p, '0' * 64)

    def test_malformed_hash(self):
        with self.assertRaises(ValueError):
            support.verify_hash(self.root / 'input', 'short')

    def test_missing_archive(self):
        with self.assertRaises(FileNotFoundError):
            support.verify_hash(self.root / 'missing', '0' * 64)


class ArchiveTests(IsolatedTest):
    def test_release_layout(self):
        root = support.extract_sdk(self.zip(self.sdk_entries()), self.root / 'sdk')
        self.assertEqual(root, self.root / 'sdk/SDK/V19_5')

    def test_debug_layout(self):
        support.extract_sdk(self.zip(self.sdk_entries(True)), self.root / 'sdk', 'Debug')

    def test_debug_requires_debug_libraries(self):
        with self.assertRaisesRegex(ValueError, 'Incomplete SDK'):
            support.extract_sdk(self.zip(self.sdk_entries()), self.root / 'sdk', 'Debug')

    def test_missing_imath(self):
        entries = [(n, d) for n, d in self.sdk_entries() if not n.endswith('half.h')]
        with self.assertRaisesRegex(ValueError, 'half.h'):
            support.extract_sdk(self.zip(entries), self.root / 'sdk')

    def test_missing_library(self):
        with self.assertRaisesRegex(ValueError, 'SDK_64.lib'):
            support.extract_sdk(self.zip(self.sdk_entries()[:-1]), self.root / 'sdk')

    def test_unsafe_names_before_any_write(self):
        for name in ('../escape', '/root', 'C:/escape', 'a/../../escape',
                     r'a\..\..\escape', 'a/./b', 'a//b', 'a:stream', 'NUL.txt',
                     'a/COM1', 'a/LPT9.lib', 'a/end.', 'a/end ', 'bad\x01name', 'a?b'):
            with self.subTest(name=name):
                with self.assertRaisesRegex(ValueError, 'Unsafe'):
                    support.extract_sdk(self.zip([('safe', b'0'), (name, b'0')]), self.root / 'sdk')
                self.assertFalse((self.root / 'sdk').exists())

    def test_symlink(self):
        info = zipfile.ZipInfo('link'); info.external_attr = (stat.S_IFLNK | 0o777) << 16
        with self.assertRaisesRegex(ValueError, 'special'):
            support.extract_sdk(self.zip([(info, 'outside')]), self.root / 'sdk')

    def test_special_device(self):
        info = zipfile.ZipInfo('device'); info.external_attr = (stat.S_IFCHR | 0o600) << 16
        with self.assertRaises(ValueError):
            support.extract_sdk(self.zip([(info, '0')]), self.root / 'sdk')

    def test_case_collision(self):
        with self.assertRaisesRegex(ValueError, 'colliding'):
            support.extract_sdk(self.zip([('a', b'1'), ('A', b'2')]), self.root / 'sdk')

    def test_file_directory_collision(self):
        with self.assertRaisesRegex(ValueError, 'collision'):
            support.extract_sdk(self.zip([('a', b'1'), ('a/file', b'2')]), self.root / 'sdk')

    def test_existing_destination(self):
        (self.root / 'sdk').mkdir()
        with self.assertRaisesRegex(ValueError, 'new directory'):
            support.extract_sdk(self.zip(self.sdk_entries()), self.root / 'sdk')

    def test_expanded_size_limit(self):
        with mock.patch.object(support, 'MAX_EXTRACTED_BYTES', 2):
            with self.assertRaisesRegex(ValueError, 'size limit'):
                support.extract_sdk(self.zip([('a', b'123')]), self.root / 'sdk')

    def test_archive_size_limit(self):
        with mock.patch.object(support, 'MAX_ARCHIVE_BYTES', 2):
            with self.assertRaisesRegex(ValueError, 'size limit'):
                support.extract_sdk(self.zip([('a', b'123')]), self.root / 'sdk')

    def test_corrupt_archive(self):
        p = self.root / 'input'; p.write_bytes(b'not a zip')
        with self.assertRaises(zipfile.BadZipFile):
            support.extract_sdk(p, self.root / 'sdk')

    def test_bad_crc(self):
        p = self.zip([('entry', b'abcdef')])
        data = p.read_bytes().replace(b'abcdef', b'abcdeX', 1); p.write_bytes(data)
        with self.assertRaises(zipfile.BadZipFile):
            support.extract_sdk(p, self.root / 'sdk')

    def test_committed_sdk_release_and_debug(self):
        archive = HERE / 'vendor/sdk195.zip'
        self.assertTrue(archive.is_file(), 'Complete SDK must be committed on this branch')
        lock = json.loads((HERE / 'sdk.lock.json').read_text())
        support.verify_hash(archive, lock['sha256'])
        for configuration in ('Release', 'Debug'):
            support.extract_sdk(archive, self.root / configuration, configuration)


class ProjectTests(IsolatedTest):
    def test_valid_path_with_spaces(self):
        relative = 'tools/am-cloud/plugins/My Test/MyTest.vcxproj'
        p = self.root / relative; p.parent.mkdir(parents=True); p.touch()
        self.assertEqual(support.validate_project(relative, self.root), p.resolve())

    def test_unsafe_or_outside_path(self):
        for value in ('/project.vcxproj', '../project.vcxproj', 'other/project.vcxproj',
                      'tools/am-cloud/plugins/../../x.vcxproj', 'x.vcxproj;/p:foo=bar',
                      'C:/project.vcxproj', 'tools/am-cloud/plugins/$(foo).vcxproj',
                      'tools/am-cloud/plugins/%2Ffoo.vcxproj'):
            with self.subTest(value=value), self.assertRaises(ValueError):
                support.validate_project(value, self.root)

    def test_missing_project(self):
        with self.assertRaises(ValueError):
            support.validate_project('tools/am-cloud/plugins/X.vcxproj', self.root)

    def test_new_output(self):
        path = self.root / 'output'
        build.prepare_output(path)
        self.assertTrue((path / 'diagnostics').is_dir())

    def test_existing_output_preserved(self):
        path = self.root / 'output'; path.mkdir(); (path / 'keep').write_text('keep')
        with self.assertRaises(ValueError): build.prepare_output(path)
        self.assertEqual((path / 'keep').read_text(), 'keep')

    def test_existing_empty_output_rejected(self):
        with self.assertRaises(ValueError): build.prepare_output(self.root)


class PETests(IsolatedTest):
    def pe(self, mutation=None):
        data = bytearray(1024); data[:2] = b'MZ'
        struct.pack_into('<I', data, 0x3c, 128); data[128:132] = b'PE\0\0'
        struct.pack_into('<HH', data, 132, 0x8664, 1)
        struct.pack_into('<HH', data, 148, 240, 0x2002)
        struct.pack_into('<H', data, 152, 0x20b)
        struct.pack_into('<H', data, 222, 0x140)
        struct.pack_into('<I', data, 260, 16)
        struct.pack_into('<II', data, 304, 0x1000, 12)
        struct.pack_into('<II', data, 408, 512, 512)
        if mutation: mutation(data)
        path = self.root / 'test.hxt'; path.write_bytes(data)
        return path

    def test_valid_dll(self): self.assertTrue(support.check_pe(self.pe())['nx'])

    def test_wrong_architecture(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: struct.pack_into('<H', b, 132, 0x14c)))

    def test_exe_not_dll(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: struct.pack_into('<H', b, 150, 2)))

    def test_missing_executable_flag(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: struct.pack_into('<H', b, 150, 0x2000)))

    def test_no_aslr_or_nx(self):
        for flags in (0x100, 0x40, 0):
            with self.subTest(flags=flags), self.assertRaises(ValueError):
                support.check_pe(self.pe(lambda b: struct.pack_into('<H', b, 222, flags)))

    def test_section_truncated(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: struct.pack_into('<I', b, 408, 4096)))

    def test_directory_outside_header(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: struct.pack_into('<I', b, 260, 100)))

    def test_missing_relocations(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: struct.pack_into('<II', b, 304, 0, 0)))

    def test_bad_signature(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: b.__setitem__(slice(128, 132), b'NOPE')))

    def test_truncated_header(self):
        p = self.root / 'short'; p.write_bytes(b'MZ')
        with self.assertRaises(ValueError): support.check_pe(p)

    def test_huge_pe_offset(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: struct.pack_into('<I', b, 0x3c, 0xffffffff)))

    def test_pe32_not_pe32plus(self):
        with self.assertRaises(ValueError):
            support.check_pe(self.pe(lambda b: struct.pack_into('<H', b, 152, 0x10b)))


class AuditTests(IsolatedTest):
    release = '\n'.join('    ' + n for n in ('FileIO_64.dll', 'Plugin_64.dll', 'mfc140.dll', 'VCRUNTIME140_1.dll'))
    debug = '\n'.join('    ' + n for n in ('FileIO_64d.dll', 'Plugin_64d.dll', 'mfc140d.dll', 'VCRUNTIME140_1d.dll'))

    def test_real_export_rows(self):
        text = '\n'.join(f'   {i+1} {i} 00001000 {name} = @ILT+10({name})' for i, name in enumerate(support.EXPORTS))
        self.assertEqual(support.audit_exports(text), sorted(support.EXPORTS))

    def test_export_mentions_are_not_exports(self):
        with self.assertRaises(ValueError): support.audit_exports('error: ' + ' '.join(support.EXPORTS))

    def test_forwarders_rejected(self):
        text = '\n'.join(f'   1 0 {name} (forwarded to other.{name})' for name in support.EXPORTS)
        with self.assertRaises(ValueError): support.audit_exports(text)

    def test_release_dependencies(self): self.assertIn('mfc140.dll', support.audit_dependencies(self.release, 'Release'))
    def test_debug_dependencies(self): self.assertIn('mfc140d.dll', support.audit_dependencies(self.debug, 'Debug'))

    def test_debug_runtime_variants_rejected_in_release(self):
        for name in ('VCRUNTIME140_1d.dll', 'msvcp140d.dll', 'msvcp140_atomic_waitd.dll',
                     'mfc140ud.dll', 'ucrtbased.dll', 'SDK_64d.dll'):
            with self.subTest(name=name), self.assertRaises(ValueError):
                support.audit_dependencies(self.release + '\n    ' + name, 'Release')

    def test_release_host_rejected_in_debug(self):
        with self.assertRaises(ValueError):
            support.audit_dependencies(self.debug + '\n    Plugin_64.dll', 'Debug')

    def test_missing_host_import(self):
        with self.assertRaises(ValueError): support.audit_dependencies('    KERNEL32.dll', 'Release')

    def test_accepted_sdk_warning(self):
        sdk = self.root / 'SDK'; filename = sdk / 'Include/FileCons.h'
        text = f'{filename}(83,21): warning C4244: fixture\n'
        self.assertEqual(len(support.audit_warnings(text, sdk)), 1)

    def test_new_project_warning_fails(self):
        with self.assertRaisesRegex(ValueError, 'Unreviewed'):
            support.audit_warnings('test.cpp(1,1): warning C4244: narrowing', self.root)

    def test_path_warning_fails(self):
        with self.assertRaisesRegex(ValueError, 'Unreviewed'):
            support.audit_warnings('build.targets(1,1): warning MSB8029: temp', self.root)


class ProcessAndPackageTests(IsolatedTest):
    def test_run_logs_nonzero_exit(self):
        log = self.root / 'error.log'
        with contextlib.redirect_stdout(io.StringIO()), self.assertRaises(RuntimeError):
            build.run([sys.executable, '-c', "print('failure detail');raise SystemExit(3)"], dict(os.environ), log)
        self.assertIn('failure detail', log.read_text())

    def test_timeout_preserves_partial_log(self):
        log = self.root / 'timeout.log'
        with contextlib.redirect_stdout(io.StringIO()), self.assertRaises(RuntimeError):
            build.run([sys.executable, '-c', "import time;print('started',flush=True);time.sleep(10)"],
                      dict(os.environ), log, timeout=1)
        self.assertIn('started', log.read_text())

    def test_failed_build_receipt(self):
        output = self.root / 'output'
        with mock.patch.object(build, 'build', side_effect=ValueError('controlled failure')):
            with contextlib.redirect_stderr(io.StringIO()), mock.patch.dict(os.environ, {'GITHUB_STEP_SUMMARY': ''}):
                self.assertEqual(build.main(['--output', str(output)]), 1)
        receipt = json.loads((output / 'diagnostics/build-receipt.json').read_text())
        self.assertEqual(receipt['status'], 'failed')
        self.assertFalse(receipt['runtime_tested'])
        self.assertFalse((output / 'packages').exists())

    def test_package_manifest_covers_every_file(self):
        folder = self.root / 'payload'; folder.mkdir(); (folder / 'test.hxt').write_bytes(b'fixture')
        (folder / 'readme.txt').write_text('test')
        dest = self.root / 'output/test.zip'
        digest = support.seal_package(folder, dest)
        self.assertEqual(digest, support.sha256(dest))
        with zipfile.ZipFile(dest) as z:
            self.assertIsNone(z.testzip())
            manifest = z.read('SHA256SUMS.txt').decode().splitlines()
            self.assertEqual(len(manifest), 2)
            for line in manifest:
                expected, name = line.split('  ', 1)
                self.assertEqual(expected, hashlib.sha256(z.read(name)).hexdigest())

    def test_package_refuses_overwrite(self):
        p = self.root / 'existing.zip'; p.write_bytes(b'keep')
        with self.assertRaises(ValueError): support.seal_package(self.root, p)
        self.assertEqual(p.read_bytes(), b'keep')

    def test_empty_package_rejected(self):
        folder = self.root / 'empty'; folder.mkdir()
        with self.assertRaises(ValueError): support.seal_package(folder, self.root / 'out.zip')


if __name__ == '__main__':
    unittest.main()
