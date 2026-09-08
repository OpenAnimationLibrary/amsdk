"""Compile the production GLB/quad core, then exercise binary fixtures and failures."""
import copy
import hashlib
import json
import math
import os
from pathlib import Path
import random
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parents[1]
SOURCE = HERE / 'plugins/AMGLBImport'
sys.path.insert(0, str(HERE))
from build import visual_studio_environment


def fixture(points=None, indices=None):
    points = points or [(0, 0, 0), (1, 0, 0), (1, 1, 0), (0, 1, 0)]
    if indices is None:
        indices = [0, 1, 2, 0, 2, 3]
    binary = b''.join(struct.pack('<3f', *p) for p in points)
    offset = len(binary)
    binary += struct.pack('<' + 'I' * len(indices), *indices)
    data = {'asset': {'version': '2.0'}, 'buffers': [{'byteLength': len(binary)}],
            'bufferViews': [{'buffer': 0, 'byteLength': offset},
                            {'buffer': 0, 'byteOffset': offset, 'byteLength': len(indices) * 4}],
            'accessors': [{'bufferView': 0, 'componentType': 5126, 'count': len(points), 'type': 'VEC3'},
                          {'bufferView': 1, 'componentType': 5125, 'count': len(indices), 'type': 'SCALAR'}],
            'meshes': [{'primitives': [{'attributes': {'POSITION': 0}, 'indices': 1}]}],
            'nodes': [{'mesh': 0, 'name': 'Test part'}], 'scenes': [{'nodes': [0]}], 'scene': 0}
    return data, binary


def encode(data, binary):
    header = json.dumps(data, separators=(',', ':')).encode()
    header += b' ' * (-len(header) % 4)
    binary += b'\0' * (-len(binary) % 4)
    return struct.pack('<III', 0x46546C67, 2, 28 + len(header) + len(binary)) + struct.pack('<II', len(header), 0x4E4F534A) + header + struct.pack('<II', len(binary), 0x004E4942) + binary


def color_grid(size=3, colors=None):
    points=[(x,y,0) for y in range(size+1) for x in range(size+1)]
    data,binary=fixture(points,[])
    data['bufferViews']=data['bufferViews'][:1]
    data['accessors']=data['accessors'][:1]
    data['meshes'][0]['primitives']=[]
    colors=colors if colors is not None else [int(x==size//2 and y==size//2) for y in range(size) for x in range(size)]
    for material in sorted(set(colors)):
        indices=[]
        for y in range(size):
            for x in range(size):
                if colors[y*size+x]!=material:continue
                a=y*(size+1)+x
                indices.extend([a,a+1,a+size+2,a,a+size+2,a+size+1])
        offset=len(binary);binary+=struct.pack('<'+'I'*len(indices),*indices)
        data['bufferViews'].append({'buffer':0,'byteOffset':offset,'byteLength':len(binary)-offset})
        accessor=len(data['accessors'])
        data['accessors'].append({'bufferView':len(data['bufferViews'])-1,'componentType':5125,'count':len(indices),'type':'SCALAR'})
        data['meshes'][0]['primitives'].append({'attributes':{'POSITION':0},'indices':accessor,'material':material})
    data['buffers'][0]['byteLength']=len(binary)
    data['materials']=[{'name':name,'pbrMetallicRoughness':{'baseColorFactor':color,'metallicFactor':0,'roughnessFactor':1}} for name,color in [('Red',[1,0,0,1]),('Blue',[0,0,1,1]),('Green',[0,1,0,1])]]
    return data,binary


class GLBImportTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        (HERE / '.work').mkdir(exist_ok=True)
        cls.temporary = tempfile.TemporaryDirectory(dir=HERE / '.work')
        cls.work = Path(cls.temporary.name)
        cls.env = None
        sources = [str(SOURCE / name) for name in ('CoreTests.cpp', 'GLBReader.cpp', 'QuadConversion.cpp', 'SplineRouting.cpp', 'MaterialGroups.cpp')]
        if os.name == 'nt':
            cls.env, _ = visual_studio_environment(cls.work, json.loads((HERE / 'toolchain.lock.json').read_text()))
            compiler = shutil.which('cl.exe', path=cls.env['PATH'])
            cls.executable = cls.work / 'core-tests.exe'
            command = [compiler, '/nologo', '/EHsc', '/std:c++20', '/W4', '/WX', '/sdl', *sources, '/Fe:' + str(cls.executable)]
        else:
            compiler = shutil.which('g++') or shutil.which('clang++')
            if not compiler:
                raise RuntimeError('A C++20 compiler is required for GLB tests')
            cls.executable = cls.work / 'core-tests'
            flags = ['-fsanitize=address,undefined', '-fno-omit-frame-pointer', '-g'] if os.environ.get('AM_GLB_SANITIZE') else []
            command = [compiler, '-std=c++20', '-Wall', '-Wextra', '-Werror', *flags, *sources, '-o', str(cls.executable)]
        result = subprocess.run(command, cwd=cls.work, env=cls.env, capture_output=True, text=True, timeout=120)
        if result.returncode:
            raise RuntimeError(result.stdout + result.stderr)

    @classmethod
    def tearDownClass(cls):
        cls.temporary.cleanup()

    def run_file(self, data=None, binary=None, raw=None, valid=True):
        path = self.work / 'fixture.glb'
        path.write_bytes(raw if raw is not None else encode(data, binary))
        result = subprocess.run([str(self.executable), str(path)], cwd=self.work, env=self.env, capture_output=True, text=True, timeout=10)
        self.assertIn(result.returncode, (0, 1), result.stderr)
        self.assertNotIn('Sanitizer', result.stderr)
        if valid:
            self.assertEqual(result.returncode, 0, result.stderr)
            return json.loads(result.stdout)
        self.assertEqual(result.returncode, 1, result.stdout)
        self.assertTrue(result.stderr.strip())

    def test_quad_reconstruction_and_area(self):
        p = self.run_file(*fixture())
        self.assertEqual((p['triangles'], p['quads'], p['paired'], p['vertices'], p['boundary']), (2, 1, 1, 4, 4))
        self.assertAlmostEqual(p['area'], 1)

    def test_single_triangle_three_quads(self):
        p = self.run_file(*fixture(indices=[0, 1, 2]))
        self.assertEqual((p['quads'], p['vertices'], p['boundary']), (3, 7, 6))
        self.assertAlmostEqual(p['area'], .5)
        self.assertEqual((p['three_way'], p['high_valence']), (4, 0))

    def test_mixed_region_has_shared_midpoints(self):
        data, binary = fixture(points=[(0,0,0),(1,0,0),(1,1,0),(0,1,0),(2,1,0)], indices=[0,1,2,0,2,3,1,4,2])
        p = self.run_file(data, binary)
        self.assertEqual((p['paired'], p['quads'], p['boundary']), (1, 7, 10))
        self.assertAlmostEqual(p['area'], 1.5)
        # Euler disk identity would fail with unshared internal edge midpoints.
        self.assertEqual(p['vertices'] - (4*p['quads']+p['boundary'])//2 + p['quads'], 1)

    def test_material_boundary_not_dissolved(self):
        data, binary = fixture()
        data['materials'] = [{'pbrMetallicRoughness': {'baseColorFactor': [1,0,0,1]}}, {}]
        data['bufferViews'][1]['byteLength'] = 12
        data['bufferViews'].append({'buffer':0,'byteOffset':60,'byteLength':12})
        data['accessors'][1]['count'] = 3
        data['accessors'].append({'bufferView':2,'componentType':5125,'count':3,'type':'SCALAR'})
        data['meshes'][0]['primitives'][0]['material'] = 0
        data['meshes'][0]['primitives'].append({'attributes':{'POSITION':0},'indices':2,'material':1})
        p = self.run_file(data,binary)
        self.assertEqual((p['paired'],p['quads'],p['boundary']), (0,6,8))
        self.assertAlmostEqual(p['area'],1)
        self.assertEqual(p['materials'], [{'faces':3,'rgba':[1,0,0,1]}, {'faces':3,'rgba':[.8,.8,.8,1]}])

    def test_nonindexed_strip_fan_and_instancing(self):
        data,binary = fixture(points=[(0,0,0),(1,0,0),(1,1,0)],indices=[0,1,2])
        del data['meshes'][0]['primitives'][0]['indices']
        self.assertEqual(self.run_file(data,binary)['quads'],3)
        for mode,indices in ((5,[0,1,3,2]),(6,[0,1,2,3])):
            data,binary = fixture(indices=indices)
            data['meshes'][0]['primitives'][0]['mode']=mode
            self.assertEqual(self.run_file(data,binary)['quads'],1)
        data,binary=fixture()
        data['nodes']=[{'mesh':0,'translation':[2,3,4],'scale':[-2,1,1]},{'mesh':0,'translation':[10,0,0]}]
        data['scenes'][0]['nodes']=[0,1]
        p=self.run_file(data,binary)
        self.assertEqual((p['parts'],p['quads'],p['area']),(2,2,3))
        self.assertEqual(p['min'],[0,0,0]);self.assertEqual(p['max'],[11,4,4])

    def test_sparse_positions(self):
        data,binary=fixture()
        data['accessors'][0].pop('bufferView')
        offset=len(binary)
        binary+=bytes([0,1,2,3])
        data['buffers'][0]['byteLength']=len(binary)
        data['bufferViews'].append({'buffer':0,'byteOffset':offset,'byteLength':4})
        data['accessors'][0]['sparse']={'count':4,'indices':{'bufferView':2,'componentType':5121},'values':{'bufferView':0}}
        self.assertEqual(self.run_file(data,binary)['quads'],1)
        self.run_file(data,binary[:-4]+bytes([0,2,1,3]),valid=False)

    def test_uv_and_normal_seams_not_dissolved(self):
        for kind,components,values in (
            ('TEXCOORD_0',2,[(0,0),(1,0),(1,1),(.2,0),(1,1),(0,1)]),
            ('NORMAL',3,[(0,0,1)]*3+[(0,1,1)]*3)):
            data,binary=fixture(points=[(0,0,0),(1,0,0),(1,1,0),(0,0,0),(1,1,0),(0,1,0)],indices=[0,1,2,3,4,5])
            offset=len(binary)
            binary+=b''.join(struct.pack('<'+'f'*components,*v) for v in values)
            data['buffers'][0]['byteLength']=len(binary)
            data['bufferViews'].append({'buffer':0,'byteOffset':offset,'byteLength':len(binary)-offset})
            data['accessors'].append({'bufferView':2,'componentType':5126,'count':6,'type':'VEC'+str(components)})
            data['meshes'][0]['primitives'][0]['attributes'][kind]=2
            with self.subTest(kind=kind):
                p=self.run_file(data,binary)
                self.assertEqual((p['paired'],p['quads'],p['boundary']),(0,6,8))

    def test_closed_cube(self):
        p=self.run_file(raw=(SOURCE/'examples/cube.glb').read_bytes())
        self.assertEqual((p['triangles'],p['quads'],p['vertices'],p['boundary'],p['area']),(12,6,8,0,6))

    def test_nonmanifold_and_duplicate_faces_rejected(self):
        cases=[([(0,0,0),(1,0,0),(1,1,0),(0,1,0)],[0,1,2,0,1,2]),
               ([(0,0,0),(1,0,0),(1,1,0),(0,1,0)],[0,1,2,0,3,2]),
               ([(0,0,0),(1,0,0),(0,1,0),(-1,0,0),(0,-1,0)],[0,1,2,0,3,4]),
               ([(0,0,0),(1,0,0),(0,1,0),(0,-1,0),(0,0,1)],[0,1,2,1,0,3,0,1,4])]
        for points,indices in cases:
            with self.subTest(indices=indices):self.run_file(*fixture(points,indices),valid=False)

    def test_invalid_or_unsupported_inputs(self):
        data,binary=fixture()
        changes=[lambda d:d.update(extensionsRequired=['KHR_draco_mesh_compression']),
                 lambda d:d['buffers'][0].update(uri='secret.bin'),
                 lambda d:d['accessors'][0].update(count=2**62),
                 lambda d:d['accessors'][0].update(byteOffset=2**63),
                 lambda d:d['bufferViews'][0].update(byteLength=2**63),
                 lambda d:d['nodes'][0].update(children=[0]),
                 lambda d:d['nodes'][0].update(scale=[0,1,1]),
                 lambda d:d['meshes'][0]['primitives'][0].update(mode=1),
                 lambda d:d['meshes'][0]['primitives'][0].update(targets=[{'POSITION':0}]),
                 lambda d:d.update(materials=[{'pbrMetallicRoughness':{'metallicFactor':2}}])]
        for i,change in enumerate(changes):
            d=copy.deepcopy(data);change(d)
            with self.subTest(case=i):self.run_file(d,binary,valid=False)
        self.run_file(data,struct.pack('<f',float('nan'))+binary[4:],valid=False)
        self.run_file(data,binary[:-4]+struct.pack('<I',99),valid=False)
        raw=encode(data,binary)
        for n in (0,12,20,len(raw)-1):self.run_file(raw=raw[:n],valid=False)

    def test_deterministic_malformed_corpus(self):
        data,binary=fixture();original=encode(data,binary);rng=random.Random(20260908)
        for i in range(80):
            raw=bytearray(original)
            for _ in range(3):raw[rng.randrange(len(raw))]=rng.randrange(256)
            path=self.work/'mutant.glb';path.write_bytes(raw)
            result=subprocess.run([str(self.executable),str(path)],cwd=self.work,env=self.env,capture_output=True,text=True,timeout=5)
            self.assertIn(result.returncode,(0,1),f'mutation {i}: {result.stderr}')
            self.assertNotIn('Sanitizer',result.stderr)

    def test_sword_reference(self):
        p=self.run_file(raw=(SOURCE/'examples/simple_sword.glb').read_bytes())
        self.assertEqual((p['triangles'],p['parts'],p['quads'],p['paired'],p['vertices'],p['boundary']),(2324,13,5202,684,5236,20))
        self.assertAlmostEqual(p['area'],.30014627789,places=8)
        self.assertEqual((p['three_way'],p['high_valence']),(1068,906))
        self.assertEqual(p['material_groups'],13)

    def test_named_parts_keep_explicit_colors_without_unused_default(self):
        data,binary=fixture()
        data['materials']=[{'pbrMetallicRoughness':{'baseColorFactor':color}} for color in ([1,0,0,1],[0,0,1,.5])]
        data['materials'][1]['alphaMode']='BLEND'
        data['meshes'][0]['primitives'][0]['material']=0
        data['meshes'].append(copy.deepcopy(data['meshes'][0]))
        data['meshes'][1]['primitives'][0]['material']=1
        data['nodes']=[{'mesh':0,'name':'Red'},{'mesh':1,'name':'Blue','translation':[2,0,0]}]
        data['scenes'][0]['nodes']=[0,1]
        p=self.run_file(data,binary)
        self.assertEqual(p['parts'],2)
        self.assertEqual(p['materials'],[{'faces':1,'rgba':[1,0,0,1]},{'faces':1,'rgba':[0,0,1,.5]}])

    def test_spline_routing_on_regular_grid_and_poles(self):
        points=[(x,y,0) for y in range(5) for x in range(5)]
        indices=[]
        for y in range(4):
            for x in range(4):
                a=y*5+x
                indices.extend([a,a+1,a+6,a,a+6,a+5])
        p=self.run_file(*fixture(points,indices))
        self.assertEqual((p['quads'],p['high_valence']),(16,0))
        self.assertAlmostEqual(p['area'],16)
        # Nonplanar fans retain source poles. The production driver independently
        # checks every routed edge and the two-CP rule at all degree 3/4 vertices.
        for n in (5,6,7,8,9):
            points=[(0,0,1)]+[(math.cos(i*2*math.pi/n),math.sin(i*2*math.pi/n),0) for i in range(n)]
            indices=[v for i in range(n) for v in (0,i+1,(i+1)%n+1)]
            with self.subTest(valence=n):
                p=self.run_file(*fixture(points,indices))
                self.assertEqual((p['high_valence'],p['quads']),(1,3*n))
                self.assertEqual(p['min'][2],0);self.assertEqual(p['max'][2],1)

    def test_material_groups_do_not_enclose_another_color(self):
        p=self.run_file(*color_grid())
        self.assertEqual(p['quads'],9)
        self.assertEqual(p['materials'],[{'faces':8,'rgba':[1,0,0,1]},{'faces':1,'rgba':[0,0,1,1]}])
        # One combined red CP group would also enclose the blue center. The
        # production driver independently verifies each group's induced faces.
        self.assertGreater(p['material_groups'],2)
        rng=random.Random(20260908)
        for i in range(12):
            colors=[rng.randrange(3) for _ in range(25)]
            with self.subTest(pattern=i):
                p=self.run_file(*color_grid(5,colors))
                self.assertEqual(p['quads'],25)
                self.assertEqual(p['high_valence'],0)

    def test_packaged_color_regressions(self):
        p=self.run_file(raw=(SOURCE/'examples/two_color_parts.glb').read_bytes())
        self.assertEqual((p['parts'],p['material_groups']),(2,2))
        self.assertEqual(p['materials'],[{'faces':1,'rgba':[1,0,0,1]},{'faces':1,'rgba':[0,0,1,1]}])
        p=self.run_file(raw=(SOURCE/'examples/color_boundary.glb').read_bytes())
        self.assertEqual(p['quads'],9)
        self.assertGreater(p['material_groups'],2)

    def test_vendor_identity(self):
        manifest=json.loads((SOURCE/'third_party/provenance.json').read_text())
        for name,digest in manifest['sha256'].items():
            self.assertEqual(hashlib.sha256((SOURCE/'third_party'/name).read_bytes()).hexdigest(),digest)

if __name__=='__main__':unittest.main()
