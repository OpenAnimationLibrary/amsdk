import sys
import tempfile
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from build_support import audit_warnings


class FontWiz2Warnings(unittest.TestCase):
    def test_exact_locked_rgb_locations_only(self):
        with tempfile.TemporaryDirectory() as folder:
            sdk = Path(folder)
            header = sdk / 'Include/RGBByte.h'
            for row, column in ((138, 18), (139, 20), (140, 19), (299, 20), (473, 24), (474, 20)):
                line = f"{header}({row},{column}): warning C4244: compound float-to-byte assignment"
                self.assertEqual(audit_warnings(line, sdk), [line])
            for location in ('(138,19)', '(300,20)'):
                with self.assertRaises(ValueError):
                    audit_warnings(f'{header}{location}: warning C4244: unexpected', sdk)
            with self.assertRaises(ValueError):
                audit_warnings(f'{header}(138,18): warning C4996: unexpected', sdk)
