"""Platform-independent checks; these do not claim to compile an HXT."""
import importlib.util
import json
from pathlib import Path
import stat
import struct
import tempfile
import unittest
import zipfile

MODULE = Path(__file__).resolve().parents[1] / 'build.py'
spec = importlib.util.spec_from_file_location('am_build', MODULE)
build = importlib.util.module_from_spec(spec)
spec.loader.exec_module(build)


class BuildTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)

    def test_hash_accepts_exact_bytes(self):
        p = self.root / 'input'
        p.write_bytes(b'abc')
        build.verify_hash(p, 'ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad')

    def test_hash_rejects_other_bytes(self):
        p = self.root / 'input'
        p.write_bytes(b'abc')
        with self.assertRaises(ValueError):
            build.verify_hash(p, '0' * 64)

    def test_lock_has_full_hash_and_https(self):
        lock = json.loads((MODULE.parent / 'sdk.lock.json').read_text())
        self.assertRegex(lock['sha256'], r'^[0-9a-f]{64}$')
        self.assertTrue(lock['url'].startswith('https://www.hash.com/'))

    def zip(self, name, attrs=None):
        p = self.root / 'test.zip'
        with zipfile.ZipFile(p, 'w') as z:
            info = zipfile.ZipInfo(name)
            if attrs is not None:
                info.external_attr = attrs
            z.writestr(info, 'test')
        return p

    def test_archive_rejects_traversal(self):
        for name in ('../escape', 'folder/../../escape', 'folder\\..\\..\\escape', '/escape', 'C:/escape'):
            with self.subTest(name=name), self.assertRaises(ValueError):
                build.extract_sdk(self.zip(name), self.root / 'sdk')
        self.assertFalse((self.root / 'escape').exists())

    def test_archive_rejects_symlink(self):
        with self.assertRaises(ValueError):
            build.extract_sdk(self.zip('link', (stat.S_IFLNK | 0o777) << 16), self.root / 'sdk')

    def test_archive_requires_sdk_layout(self):
        with self.assertRaises(ValueError):
            build.extract_sdk(self.zip('not-an-sdk'), self.root / 'sdk')

    def test_archive_finds_sdk_root(self):
        p = self.root / 'sdk.zip'
        with zipfile.ZipFile(p, 'w') as z:
            z.writestr('SDK/V19_5/Include/SDK/Entry.h', '//test')
            z.writestr('SDK/V19_5/Lib/PC/Plugin_64.lib', 'test')
        self.assertEqual(build.extract_sdk(p, self.root / 'sdk'), self.root / 'sdk/SDK/V19_5')

    def pe(self, machine=0x8664, flags=0x2000, magic=0x20b):
        data = bytearray(256)
        data[:2] = b'MZ'
        struct.pack_into('<I', data, 0x3c, 128)
        data[128:132] = b'PE\0\0'
        struct.pack_into('<H', data, 132, machine)
        struct.pack_into('<H', data, 150, flags)
        struct.pack_into('<H', data, 152, magic)
        p = self.root / 'test.hxt'
        p.write_bytes(data)
        return p

    def test_pe_accepts_x64_dll(self):
        build.check_pe(self.pe())

    def test_pe_rejects_x86(self):
        with self.assertRaises(ValueError):
            build.check_pe(self.pe(machine=0x14c, magic=0x10b))

    def test_pe_rejects_executable(self):
        with self.assertRaises(ValueError):
            build.check_pe(self.pe(flags=0))

    def test_pe_rejects_truncated_file(self):
        p = self.root / 'short.hxt'
        p.write_bytes(b'MZ')
        with self.assertRaises(ValueError):
            build.check_pe(p)


if __name__ == '__main__':
    unittest.main()
