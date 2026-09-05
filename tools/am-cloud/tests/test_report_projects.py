"""Check standalone report projects and read-only API guardrails (not a host test)."""
from pathlib import Path
import re
import unittest
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1] / 'plugins'
NAMES = ('AMModelReport', 'AMSelectionReport')


class ReportProjectTests(unittest.TestCase):
    def test_project_names_and_unique_guids(self):
        guids = set()
        for name in NAMES:
            with self.subTest(name=name):
                folder = ROOT / name
                tree = ET.parse(folder / (name + '.vcxproj'))
                guids.add(tree.find('.//{*}ProjectGuid').text)
                self.assertEqual(tree.find('.//{*}RootNamespace').text, name)
                for item in tree.findall('.//*[@Include]'):
                    if item.tag.rsplit('}', 1)[-1] in ('ClCompile', 'ClInclude', 'ResourceCompile'):
                        self.assertTrue((folder / item.attrib['Include']).is_file(), item.attrib['Include'])
        self.assertEqual(len(guids), 2)

    def test_report_sources_have_no_model_editing_calls(self):
        # A narrow regression guard against accidental editing API use, not proof
        # of arbitrary code safety or absence of SDK-internal side effects.
        sources = [ROOT / n / (n + '.cpp') for n in NAMES]
        sources += [ROOT / 'ReadOnlyReports/ReportCommon.h']
        banned = r'->(?:SetPosition|SetChanged|OnModified|OffModified|FindPatches|Update|MakeCurrent|CreateGroup|AddCP|RemoveCP|CopyExtrude|DeleteCP|Save)\s*\('
        for path in sources:
            with self.subTest(file=path.name):
                self.assertIsNone(re.search(banned, path.read_text(encoding='utf-8')))


if __name__ == '__main__':
    unittest.main()
