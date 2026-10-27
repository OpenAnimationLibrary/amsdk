import sys
import tempfile
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from build_support import audit_warnings

class MakeGroupWarnings(unittest.TestCase):
    def test_review_is_required(self):
        with tempfile.TemporaryDirectory() as directory:
            sdk = Path(directory)
            line = f"{sdk / 'Include/RGBByte.h'}(138,18): warning C4244: float to byte"
            with self.assertRaises(ValueError):
                audit_warnings(line, sdk)
            self.assertEqual(audit_warnings(line, sdk, reviewed_rgb=True), [line])

    def test_only_exact_locked_locations(self):
        with tempfile.TemporaryDirectory() as directory:
            sdk = Path(directory)
            header = sdk / 'Include/RGBByte.h'
            for row, col in ((138,18), (139,20), (140,19), (299,20), (473,24), (474,20)):
                line = f"{header}({row},{col}): warning C4244: float to byte"
                self.assertEqual(audit_warnings(line, sdk, reviewed_rgb=True), [line])
            for suffix in ("(138,19): warning C4244", "(300,20): warning C4244",
                           "(138,18): warning C4996"):
                with self.assertRaises(ValueError):
                    audit_warnings(str(header) + suffix + ": unexpected", sdk, reviewed_rgb=True)
            for header in (sdk / 'RGBByte.h', sdk / 'Include/other.h'):
                with self.assertRaises(ValueError):
                    audit_warnings(f"{header}(138,18): warning C4244: unexpected", sdk, reviewed_rgb=True)

if __name__ == '__main__':
    unittest.main()
