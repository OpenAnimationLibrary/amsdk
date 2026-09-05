import re
from pathlib import Path
import unittest
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]


class ContractTests(unittest.TestCase):
    def test_no_host_model_editing(self):
        for name in ('AMPatchDraw.cpp','CanvasDialog.cpp','PatchDrawCore.h'):
            source = (ROOT/name).read_text()
            for token in ('HModelCache::New(', 'StartSpline(', 'AttachCPs(', 'FindPatches(', 'SaveAllToUndo(', 'SetPosition(', 'CopyExtrude('):
                self.assertNotIn(token, source, name)

    def test_no_python_process_or_global_dpi_policy(self):
        source = (ROOT/'CanvasDialog.cpp').read_text()+(ROOT/'AMPatchDraw.cpp').read_text()
        for token in ('CreateProcess', 'ShellExecute', 'SetProcessDPIAware', 'SetProcessDpiAwareness', 'SetThreadDpiAwareness', 'GetEnvironmentStrings'):
            self.assertNotIn(token,source)

    def test_expected_contexts_and_module_state(self):
        source = (ROOT/'AMPatchDraw.cpp').read_text()
        for context in ('HOT_MODEL','HOT_OBJECTS','HOT_GROUP'):
            self.assertIn(context,source)
        self.assertEqual(source.count('AFX_MANAGE_STATE'),2)
        self.assertIn('InterlockedCompareExchange',source)

    def test_create_only_export(self):
        source=(ROOT/'SavePlan.h').read_text()
        self.assertIn('CREATE_NEW',source)
        self.assertNotIn('CREATE_ALWAYS',source)
        self.assertNotIn('MOVEFILE_REPLACE_EXISTING',source)
        self.assertIn('FlushFileBuffers',source)
        self.assertIn('FileDispositionInfo',source)

    def test_project_inputs(self):
        tree=ET.parse(ROOT/'AMPatchDraw.vcxproj')
        for node in tree.iter():
            name=node.tag.rsplit('}',1)[-1]
            if name in ('ClCompile','ClInclude','ResourceCompile') and node.get('Include'):
                self.assertTrue((ROOT/node.get('Include')).is_file())
        self.assertIsNone(tree.find('.//{*}ProjectReference'))
        self.assertEqual(tree.find('.//{*}UseOfMfc').text,'Dynamic')
        self.assertEqual(tree.find('.//{*}CharacterSet').text,'MultiByte')
        self.assertEqual(tree.find('.//{*}PreferredToolArchitecture').text,'x64')

    def test_resources_are_unique(self):
        ids=re.findall(r'^#define\s+\w+\s+(\d+)\s*$',(ROOT/'resource.h').read_text(),re.M)
        self.assertEqual(len(ids),len(set(ids)))


if __name__ == '__main__':
    unittest.main()
