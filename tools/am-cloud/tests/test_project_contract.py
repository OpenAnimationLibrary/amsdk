"""Protect the MSBuild evaluation order which a Windows build validated."""
from pathlib import Path
import unittest
import xml.etree.ElementTree as ET

HERE = Path(__file__).resolve().parents[1]


class ProjectContractTests(unittest.TestCase):
    def setUp(self):
        self.project = ET.parse(HERE / 'plugins/AMBuildSmoke/AMBuildSmoke.vcxproj').getroot()

    def test_hxt_extensions_override_cpp_props_defaults(self):
        children = list(self.project)
        imported = next(i for i, e in enumerate(children) if e.tag.endswith('Import')
                        and e.get('Project', '').endswith('Microsoft.Cpp.props'))
        extensions = [(i, e.find('{*}TargetExt').text) for i, e in enumerate(children)
                      if e.find('{*}TargetExt') is not None]
        self.assertEqual([value for _, value in extensions], ['.hxt', '.hxtd'])
        self.assertTrue(all(i > imported for i, _ in extensions))
        self.assertEqual(self.project.find('.//{*}Link/{*}OutputFile').text, '$(TargetPath)')

    def test_native_host_tools_and_nonincremental_link(self):
        self.assertEqual(self.project.find('.//{*}PreferredToolArchitecture').text, 'x64')
        self.assertEqual(self.project.find('.//{*}LinkIncremental').text, 'false')
        self.assertEqual(self.project.find('.//{*}TargetPath').text,
                         '$(OutDir)$(TargetName)$(TargetExt)')


if __name__ == '__main__':
    unittest.main()
