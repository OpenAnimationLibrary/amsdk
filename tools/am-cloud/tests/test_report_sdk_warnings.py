"""Exact additional SDK warning acceptance; no blanket source suppression."""
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from build_support import audit_warnings


class ReportSDKWarningTests(unittest.TestCase):
    def test_reviewed_rgbbyte_locations(self):
        with tempfile.TemporaryDirectory() as temp:
            sdk = Path(temp) / 'SDK'
            for row, column in ((138, 18), (139, 20), (140, 19), (299, 20), (473, 24), (474, 20)):
                with self.subTest(row=row):
                    text = f'{sdk / "Include/RGBByte.h"}({row},{column}): warning C4244: fixture'
                    self.assertEqual(len(audit_warnings(text, sdk)), 1)

    def test_unreviewed_rgbbyte_warning_rejected(self):
        with tempfile.TemporaryDirectory() as temp:
            sdk = Path(temp) / 'SDK'
            for relative, row, column, code in (
                ('Include/RGBByte.h', 141, 19, 'C4244'),
                ('Include/RGBByte.h', 138, 19, 'C4244'),
                ('Include/RGBByte.h', 138, 18, 'C4996'),
                ('RGBByte.h', 138, 18, 'C4244')):
                with self.subTest(case=(relative, row, column, code)), self.assertRaises(ValueError):
                    audit_warnings(f'{sdk / relative}({row},{column}): warning {code}: fixture', sdk)


if __name__ == '__main__':
    unittest.main()
