import copy
import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'runtime'))
from ambridge import ModelPlan, validate

SUPPORTED = {(3, 11), (3, 12)}
BASE = {'am_plan': 1, 'name': 'Test', 'points': [[0, 0, 0], [10, 0, 0], [20, 10, 0]], 'splines': [[0, 1, 2]]}

class PlanTests(unittest.TestCase):
    def test_good_and_snapshot(self):
        result = validate(BASE)
        result['points'][0][0] = 1
        self.assertEqual(BASE['points'][0][0], 0)

    def test_point_indices(self):
        p = ModelPlan('Example')
        self.assertEqual(p.point(0, 0, 0), 0)
        self.assertEqual(p.point(10, 0, 0), 1)
        p.spline([0, 1])
        self.assertEqual(p.to_dict()['splines'], [[0, 1]])

    def test_version_and_fields(self):
        for value in [None, [], {}, {**BASE, 'am_plan': True}, {**BASE, 'am_plan': 1.0}, {**BASE, 'extra': 1}]:
            with self.subTest(value=value), self.assertRaises(ValueError): validate(value)

    def test_coordinates(self):
        for x in [True, None, '0', float('nan'), float('inf'), 100001, -100001, 10**1000, 1e-99]:
            plan = copy.deepcopy(BASE); plan['points'][0][0] = x
            with self.subTest(value=x), self.assertRaises(ValueError): validate(plan)

    def test_float_collapsed_edge(self):
        plan = copy.deepcopy(BASE); plan['points'][2] = [10.00000001, 0, 0]
        with self.assertRaises(ValueError): validate(plan)

    def test_names(self):
        for name in ['', 'A'*65, ' Bad', 'Bad ', 'bad/name', 'a\nb', '\u65e5', 'a"b']:
            with self.subTest(name=name), self.assertRaises(ValueError): validate({**BASE, 'name': name})

    def test_indices_and_topology(self):
        for s in [[], [[]], [[0]], [[0,1]], [[0,1,3]], [[0,1,0]], [[0,1.0,2]], [[0,True,2]], [[0,1,2],[1,0]], [[0,1],[0,2],[0,1]]]:
            with self.subTest(s=s), self.assertRaises(ValueError): validate({**BASE, 'splines': s})

    def test_explicit_attachment(self):
        self.assertEqual(validate({**BASE, 'splines': [[0,1],[1,2]]})['splines'], [[0,1],[1,2]])

    def test_caps(self):
        p = ModelPlan('Test')
        for i in range(1024): p.point(i, 0, 0)
        with self.assertRaises(ValueError): p.point(1024,0,0)
        for i in range(128): p.spline([0,1])
        with self.assertRaises(ValueError): p.spline([0,1])
        with self.assertRaises(ValueError): validate({**BASE, 'splines': [list(range(257))]})

    def test_examples(self):
        for name, points, splines in [('three_point_spline',3,1), ('grid',9,6)]:
            spec = importlib.util.spec_from_file_location(name, ROOT / 'examples' / (name + '.py'))
            module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
            plan = module.build().to_dict()
            self.assertEqual(len(plan['points']), points); self.assertEqual(len(plan['splines']), splines)
            fixture = json.loads((ROOT/'examples'/(name+'.json')).read_text())
            self.assertEqual(plan, fixture)

@unittest.skipUnless(sys.version_info[:2] in SUPPORTED and sys.implementation.name == 'cpython',
                     'Execution requires supported CPython; exercised in Windows CI')
class RunnerTests(unittest.TestCase):
    def run_source(self, source):
        with tempfile.TemporaryDirectory() as temp:
            script = Path(temp) / 'script with spaces.py'; script.write_text(source, encoding='utf8')
            return subprocess.run([sys.executable, '-I', '-S', '-B', '-X', 'utf8', str(ROOT/'runtime/runner.py'), str(script)], capture_output=True, timeout=5)

    def test_runner_success_and_log_separation(self):
        result = self.run_source('from ambridge import ModelPlan\ndef build():\n print("diagnostic")\n p=ModelPlan("Test");p.point(0,0,0);p.point(1,0,0);p.spline([0,1]);return p\n')
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertEqual(json.loads(result.stdout)['name'],'Test')
        self.assertIn(b'diagnostic', result.stderr)

    def test_runner_rejects_bad_scripts(self):
        for text in ['no such syntax!', 'x=1', 'def build(): return {}', 'def build(): raise ValueError("broken")']:
            with self.subTest(text=text):
                result=self.run_source(text); self.assertNotEqual(result.returncode,0); self.assertFalse(result.stdout)

    def test_new_namespace_each_run(self):
        for _ in range(2):
            result=self.run_source('counter=0\ndef build():\n global counter\n counter+=1\n return '+repr(BASE)+'\n')
            self.assertEqual(result.returncode,0)

class VersionTests(unittest.TestCase):
    @unittest.skipIf(sys.version_info[:2] in SUPPORTED and sys.implementation.name == 'cpython',
                     'This interpreter is supported')
    def test_other_runtime_is_rejected(self):
        result = subprocess.run([sys.executable, '-I', '-S', '-B', str(ROOT/'runtime/runner.py'), str(ROOT/'examples/grid.py')], capture_output=True, timeout=5)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn(b'CPython 3.11 or 3.12', result.stderr)
        self.assertFalse(result.stdout)

if __name__ == '__main__': unittest.main()
