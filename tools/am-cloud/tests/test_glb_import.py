"""Compile the production GLB/quad core, then exercise binary fixtures and failures."""
import copy
import hashlib
import itertools
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


def cube_sphere(div=4):
    points=[];lookup={};faces=[]
    for axis in range(3):
        a,b=[k for k in range(3) if k!=axis]
        for sign in [-1,1]:
            for j in range(div):
                for i in range(div):
                    quad=[]
                    for u,v in [(i,j),(i+1,j),(i+1,j+1),(i,j+1)]:
                        key=[0,0,0];key[axis]=sign*div;key[a]=2*u-div;key[b]=2*v-div;key=tuple(key)
                        if key not in lookup:
                            length=math.sqrt(sum(x*x for x in key));lookup[key]=len(points);points.append(tuple(x/length for x in key))
                        quad.append(lookup[key])
                    xyz=[points[k] for k in quad];u=[xyz[1][k]-xyz[0][k] for k in range(3)];v=[xyz[2][k]-xyz[0][k] for k in range(3)]
                    normal=[u[1]*v[2]-u[2]*v[1],u[2]*v[0]-u[0]*v[2],u[0]*v[1]-u[1]*v[0]]
                    if normal[axis]*sign<0:quad.reverse()
                    faces.extend([quad[0],quad[1],quad[2],quad[0],quad[2],quad[3]])
    return points,faces


def icosphere(level=1):
    phi=(1+math.sqrt(5))/2
    points=[(0,a,b*phi) for a in (-1,1) for b in (-1,1)]+[(a,b*phi,0) for a in (-1,1) for b in (-1,1)]+[(b*phi,0,a) for a in (-1,1) for b in (-1,1)]
    faces=[]
    for face in itertools.combinations(range(12),3):
        if not all(abs(sum((points[a][k]-points[b][k])**2 for k in range(3))-4)<1e-9 for a,b in itertools.combinations(face,2)):continue
        a,b,c=[points[i] for i in face];u=[b[k]-a[k] for k in range(3)];v=[c[k]-a[k] for k in range(3)]
        normal=[u[1]*v[2]-u[2]*v[1],u[2]*v[0]-u[0]*v[2],u[0]*v[1]-u[1]*v[0]]
        faces.append(face if sum(normal[k]*a[k] for k in range(3))>0 else (face[0],face[2],face[1]))
    def unit(point):
        length=math.sqrt(sum(v*v for v in point));return tuple(v/length for v in point)
    points=[unit(p) for p in points]
    for _ in range(level):
        edges={};result=[]
        def mid(a,b):
            key=tuple(sorted((a,b)))
            if key not in edges:
                edges[key]=len(points);points.append(unit(tuple((points[a][k]+points[b][k])*.5 for k in range(3))))
            return edges[key]
        for a,b,c in faces:
            ab,bc,ca=mid(a,b),mid(b,c),mid(c,a)
            result.extend([(a,ab,ca),(ab,b,bc),(ca,bc,c),(ab,bc,ca)])
        faces=result
    return points,[v for f in faces for v in f]


def colored_mesh(points,triangles,materials):
    data,binary=fixture(points,[])
    data['bufferViews']=data['bufferViews'][:1];data['accessors']=data['accessors'][:1];data['meshes'][0]['primitives']=[]
    for material in sorted(set(materials)):
        indices=[v for face,m in zip(triangles,materials) if m==material for v in face]
        offset=len(binary);binary+=struct.pack('<'+'I'*len(indices),*indices)
        data['bufferViews'].append({'buffer':0,'byteOffset':offset,'byteLength':len(binary)-offset})
        accessor=len(data['accessors']);data['accessors'].append({'bufferView':len(data['bufferViews'])-1,'componentType':5125,'count':len(indices),'type':'SCALAR'})
        data['meshes'][0]['primitives'].append({'attributes':{'POSITION':0},'indices':accessor,'material':material})
    data['buffers'][0]['byteLength']=len(binary)
    data['materials']=[{'pbrMetallicRoughness':{'baseColorFactor':c}} for c in ([1,0,0,1],[0,0,1,1],[0,1,0,1],[1,1,0,1])]
    return data,binary


class GLBImportTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        (HERE / '.work').mkdir(exist_ok=True)
        cls.temporary = tempfile.TemporaryDirectory(dir=HERE / '.work')
        cls.work = Path(cls.temporary.name)
        cls.env = None
        sources = [str(SOURCE / name) for name in ('CoreTests.cpp', 'GLBReader.cpp', 'QuadConversion.cpp', 'SplineRouting.cpp', 'MaterialGroups.cpp', 'DensityReduction.cpp', 'third_party/meshoptimizer/simplifier.cpp', 'third_party/meshoptimizer/allocator.cpp')]
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

    def run_file(self, data=None, binary=None, raw=None, valid=True, target=0, omit=False):
        path = self.work / 'fixture.glb'
        path.write_bytes(raw if raw is not None else encode(data, binary))
        args=[str(self.executable), str(path), str(target)]
        if omit:args.append('omit')
        result = subprocess.run(args, cwd=self.work, env=self.env, capture_output=True, text=True, timeout=30 if target else 10)
        self.assertIn(result.returncode, (0, 1), result.stderr)
        self.assertNotIn('Sanitizer', result.stderr)
        if valid:
            self.assertEqual(result.returncode, 0, result.stderr)
            return json.loads(result.stdout)
        self.assertEqual(result.returncode, 1, result.stdout)
        self.assertTrue(result.stderr.strip())
        return result.stderr

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

    def test_hinge_box_single_spline_face_regression(self):
        # The owner's saved 0.1.5 model omitted the back of each 5.2 x 5.4 x
        # 6.6 mm hinge: one closed spline surrounded all four patch edges.
        # Reproduce the GLB face/vertex order without publishing the owner MDL.
        for sign in (-1,1):
            points=[];indices=[]
            for axis in range(3):
                a,b=[k for k in range(3) if k!=axis]
                for side in (-1,1):
                    quad=[]
                    for u,v in ((-1,-1),(1,-1),(1,1),(-1,1)):
                        xyz=[0.,0.,0.];xyz[axis]=side;xyz[a]=u;xyz[b]=v;quad.append(xyz)
                    normal=[(quad[1][(k+1)%3]-quad[0][(k+1)%3])*(quad[2][(k+2)%3]-quad[0][(k+2)%3])-(quad[1][(k+2)%3]-quad[0][(k+2)%3])*(quad[2][(k+1)%3]-quad[0][(k+1)%3]) for k in range(3)]
                    if normal[axis]*side<0:quad.reverse()
                    base=len(points)
                    points.extend([(x*.0026+sign*.0645,y*.0027+.008,z*.0033-.0054) for x,y,z in quad])
                    indices.extend([base,base+1,base+2,base,base+2,base+3])
            for omit in (False,True):
                with self.subTest(side=sign,omit=omit):
                    p=self.run_file(*fixture(points,indices),omit=omit)
                    self.assertEqual((p['quads'],p['vertices'],p['seam_edges'],p['omitted_triangles']),(6,8,0,0))
                    self.assertAlmostEqual(p['area'],2*(.0052*.0054+.0052*.0066+.0054*.0066),places=9)
            triangles=[indices[i:i+3] for i in range(0,len(indices),3)]
            for seed in range(12):
                random.Random(seed).shuffle(triangles)
                p=self.run_file(*fixture(points,[v for f in triangles for v in f]))
                self.assertEqual((p['quads'],p['vertices'],p['seam_edges']),(6,8,0))

    def test_box_routing_across_disconnected_rotated_solids(self):
        base,faces=cube_sphere(1);points=[];indices=[]
        for i in range(64):
            angle=i*.17;c,s=math.cos(angle),math.sin(angle);offset=len(points)
            for x,y,z in base:
                x*=.0026*math.sqrt(3);y*=.0027*math.sqrt(3);z*=.0033*math.sqrt(3)
                points.append((c*x-s*z+(i%8)*.02,y,s*x+c*z+(i//8)*.02))
            indices.extend(offset+j for j in faces)
        triangles=[indices[i:i+3] for i in range(0,len(indices),3)]
        random.Random(195).shuffle(triangles)
        p=self.run_file(*fixture(points,[v for f in triangles for v in f]))
        self.assertEqual((p['parts'],p['quads'],p['vertices'],p['surface_components']),(1,384,512,64))
        self.assertEqual((p['boundary'],p['seam_edges'],p['high_valence']),(0,0,0))
        self.assertAlmostEqual(p['area'],64*2*(.0052*.0054+.0052*.0066+.0054*.0066),places=7)

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

    def test_original_sword_imports_with_quad_seam_fallback(self):
        p=self.run_file(raw=(SOURCE/'examples/simple_sword.glb').read_bytes())
        self.assertEqual((p['triangles'],p['parts'],p['material_groups'],p['high_valence']),(2324,13,13,0))
        self.assertEqual(p['quads'],5544)
        self.assertEqual(len(p['materials']),6)
        self.assertEqual(sum(m['faces'] for m in p['materials']),p['quads'])
        self.assertGreater(p['seam_edges'],0)
        self.assertLess(p['seamed_parts'],p['parts'])
        self.assertLess(p['surface_components'],p['quads']//4)
        self.assertEqual(p['geometric_boundary'],20)

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
        self.assertEqual(p['seam_edges'],0)
        # Unpairable fans now import using matching, independently editable
        # seam boundaries, while the driver verifies every routed CP/quad.
        for n in (5,6,7,8,9,64):
            points=[(0,0,1)]+[(math.cos(i*2*math.pi/n),math.sin(i*2*math.pi/n),0) for i in range(n)]
            indices=[v for i in range(n) for v in (0,i+1,(i+1)%n+1)]
            with self.subTest(valence=n):
                p=self.run_file(*fixture(points,indices))
                self.assertEqual(p['high_valence'],0)
                self.assertGreater(p['seam_edges'],0)
                self.assertEqual(p['geometric_boundary'],2*n)
                self.assertLess(p['surface_components'],p['quads']//2)

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

    def test_curved_spheres_reconstruct_four_sided_layout(self):
        for div in (4,8):
            with self.subTest(divisions=div):
                points,indices=cube_sphere(div)
                p=self.run_file(*fixture(points,indices))
                self.assertEqual((p['quads'],p['paired'],p['subdivided']),(6*div*div,6*div*div,0))
                self.assertEqual((p['boundary'],p['high_valence'],p['three_way']),(0,0,8))
                self.assertEqual(p['seam_edges'],0)
                self.assertGreater(p['curved_pairs'],0)
                self.assertEqual(p['vertices'],len(points))
                self.assertEqual(p['min'],[-1,-1,-1]);self.assertEqual(p['max'],[1,1,1])
                # Face ordering must not turn a reconstructible sphere into a fan.
                faces=[indices[i:i+3] for i in range(0,len(indices),3)]
                random.Random(19).shuffle(faces)
                q=self.run_file(*fixture(points,[v for face in faces for v in face]))
                self.assertEqual((q['quads'],q['subdivided'],q['high_valence']),(6*div*div,0,0))

    def test_curved_pair_preserves_source_corners(self):
        points=[(0,0,0),(1,0,0),(1,1,.2),(0,1,0)]
        p=self.run_file(*fixture(points))
        self.assertEqual((p['quads'],p['vertices'],p['curved_pairs']),(1,4,1))
        self.assertEqual(p['subdivided'],0)
        self.assertAlmostEqual(p['max'][2],.2)

    def test_sharp_crease_is_not_paired(self):
        p=self.run_file(*fixture([(0,0,0),(1,0,0),(1,1,2),(0,1,0)]))
        self.assertEqual((p['paired'],p['curved_pairs'],p['quads']),(0,0,6))
        self.assertEqual(p['high_valence'],0)

    def test_pair_search_recovers_from_a_greedy_trap(self):
        points=[(-1.2,0,0),(0,-1,0),(0,1,0),(-2,1,0),(2,-1,0),(1.2,0,0)]
        indices=[0,1,2,0,2,3,1,4,5,1,5,2]
        # The central diamond is the best individual pair, but choosing it
        # strands the outer triangles. Re-pairing the region gives two quads.
        p=self.run_file(*fixture(points,indices))
        self.assertEqual((p['paired'],p['quads'],p['subdivided']),(2,2,0))
        self.assertEqual(p['vertices'],6)

    def test_shallow_fan_is_rebuilt_before_subdivision(self):
        for n in (6,8):
            points=[(0,0,.1)]+[(math.cos(i*2*math.pi/n),math.sin(i*2*math.pi/n),0) for i in range(n)]
            indices=[v for i in range(n) for v in (0,i+1,(i+1)%n+1)]
            with self.subTest(edges=n):
                p=self.run_file(*fixture(points,indices))
                self.assertEqual((p['paired'],p['quads'],p['subdivided']),(n//2,n//2,0))
                self.assertEqual(p['high_valence'],0)
                self.assertEqual(p['vertices'],len(points))

    def test_packaged_topology_examples(self):
        p=self.run_file(raw=(SOURCE/'examples/curved_quad_sphere.glb').read_bytes())
        self.assertEqual((p['quads'],p['curved_pairs'],p['subdivided'],p['high_valence']),(96,96,0,0))
        p=self.run_file(raw=(SOURCE/'examples/shallow_fan.glb').read_bytes())
        self.assertEqual((p['quads'],p['paired'],p['subdivided'],p['high_valence']),(3,3,0,0))
        p=self.run_file(raw=(SOURCE/'examples/crowded_pole.glb').read_bytes())
        self.assertEqual((p['quads'],p['high_valence'],p['seamed_parts']),(24,0,1))
        self.assertGreater(p['seam_edges'],0)
        self.assertEqual(p['geometric_boundary'],24)

    def test_icospheres_and_boundary_poles_use_seams_without_holes(self):
        for level in (1,2):
            points,indices=icosphere(level)
            faces=[indices[i:i+3] for i in range(0,len(indices),3)]
            for seed in (0,19):
                random.Random(seed).shuffle(faces)
                with self.subTest(level=level,order=seed):
                    p=self.run_file(*fixture(points,[v for f in faces for v in f]))
                    self.assertEqual((p['high_valence'],p['geometric_boundary']),(0,0))
                    self.assertLess(p['surface_components'],p['quads']//4)
        # A boundary pole has an open fan, so its sector limits differ from
        # a closed star. Geometry remains the same planar half disk.
        n=11
        points=[(0,0,0)]+[(math.cos(i*math.pi/n),math.sin(i*math.pi/n),0) for i in range(n+1)]
        indices=[v for i in range(n) for v in (0,i+1,i+2)]
        p=self.run_file(*fixture(points,indices))
        self.assertEqual(p['high_valence'],0)
        self.assertGreater(p['seam_edges'],0)
        self.assertAlmostEqual(p['area'],n*math.sin(math.pi/n)/2,places=6)
        self.assertEqual(p['geometric_boundary'],2*(n+2))

    def test_seam_fallback_preserves_alternating_colors_and_surface_area(self):
        n=12
        points=[(0,0,1)]+[(math.cos(i*2*math.pi/n),math.sin(i*2*math.pi/n),0) for i in range(n)]
        indices=[v for i in range(n) for v in (0,i+1,(i+1)%n+1)]
        data,binary=fixture(points,[])
        data['bufferViews']=data['bufferViews'][:1];data['accessors']=data['accessors'][:1]
        data['meshes'][0]['primitives']=[]
        for color in (0,1):
            selected=[v for i in range(color,n,2) for v in indices[3*i:3*i+3]]
            offset=len(binary);binary+=struct.pack('<'+'I'*len(selected),*selected)
            data['bufferViews'].append({'buffer':0,'byteOffset':offset,'byteLength':len(binary)-offset})
            data['accessors'].append({'bufferView':color+1,'componentType':5125,'count':len(selected),'type':'SCALAR'})
            data['meshes'][0]['primitives'].append({'attributes':{'POSITION':0},'indices':color+1,'material':color})
        data['buffers'][0]['byteLength']=len(binary)
        data['materials']=[{'pbrMetallicRoughness':{'baseColorFactor':c}} for c in ([1,0,0,1],[0,0,1,1])]
        p=self.run_file(data,binary)
        self.assertEqual((p['paired'],p['quads'],p['high_valence']),(0,36,0))
        self.assertEqual(p['materials'],[{'faces':18,'rgba':[1,0,0,1]},{'faces':18,'rgba':[0,0,1,1]}])
        self.assertGreater(p['seam_edges'],0)
        self.assertEqual(p['geometric_boundary'],24)
        expected=n*math.sin(math.pi/n)*math.sqrt(1+math.cos(math.pi/n)**2)
        self.assertAlmostEqual(p['area'],expected,places=6)

    def test_unrelated_vertices_still_reject_native_precision_collapse(self):
        data,binary=fixture([(0,0,0),(.00001,0,0),(.00001,.00001,0),(0,.00001,0)])
        data['nodes'][0]['translation']=[1000,0,0]
        error=self.run_file(data,binary,valid=False)
        self.assertIn('precision collapse distinct vertices',error)

    def test_vendor_identity(self):
        for directory in (SOURCE/'third_party',SOURCE/'third_party/meshoptimizer'):
            manifest=json.loads((directory/'provenance.json').read_text())
            for name,digest in manifest['sha256'].items():
                self.assertEqual(hashlib.sha256((directory/name).read_bytes()).hexdigest(),digest)

    def test_omit_unpaired_leaves_empty_and_retains_neighbor_quad(self):
        p=self.run_file(*fixture([(0,0,0),(1,0,0),(0,1,0)],[0,1,2]),omit=True)
        self.assertEqual((p['quads'],p['vertices'],p['parts'],p['omitted_triangles'],p['omitted_parts']),(0,0,0,1,1))
        p=self.run_file(raw=(SOURCE/'examples/mixed_region.glb').read_bytes(),omit=True)
        self.assertEqual((p['quads'],p['paired'],p['subdivided'],p['omitted_triangles']),(1,1,0,1))
        self.assertEqual(p['vertices'],4)
        self.assertAlmostEqual(p['area'],1)

    def test_omit_enclosed_triangle_stays_open_without_removing_quads(self):
        points=[(0,0,0),(1,0,0),(.5,1,0),(-1,-1,0),(2,-1,0),(.5,3,0)]
        quads=[(0,3,4,1),(1,4,5,2),(2,5,3,0)]
        triangles=[t for a,b,c,d in quads for t in [(a,b,c),(a,c,d)]]+[(0,1,2)]
        p=self.run_file(*colored_mesh(points,triangles,[0,0,1,1,2,2,3]),omit=True)
        self.assertEqual((p['quads'],p['paired'],p['omitted_triangles'],p['high_valence']),(3,3,1,0))
        self.assertAlmostEqual(p['area'],5.5)
        self.assertEqual(len(p['materials']),3)
        self.assertGreater(p['seam_copies'],0)

    def test_density_target_reduces_final_patch_count(self):
        data,binary=fixture(*icosphere(2))
        full=self.run_file(data,binary)
        for target in (200,100):
            with self.subTest(target=target):
                p=self.run_file(data,binary,target=target)
                self.assertEqual(p['target'],target)
                self.assertGreater(p['reduced_triangles'],0)
                self.assertLess(p['quads'],full['quads'])
                if target==200:self.assertLessEqual(p['quads'],target)
                self.assertEqual(p['density_target_met'],p['quads']<=target)
                self.assertEqual((p['high_valence'],p['geometric_boundary']),(0,0))
                self.assertEqual(p['min'],full['min']);self.assertEqual(p['max'],full['max'])
                self.assertGreater(p['area'],full['area']*.85)
        # A larger budget never adds density; zero preserves the existing build.
        self.assertEqual(self.run_file(data,binary,target=10000)['quads'],full['quads'])

    def test_density_locks_color_boundaries_and_reports_unreachable_target(self):
        data,binary=color_grid(8,[int(x>=4) for y in range(8) for x in range(8)])
        p=self.run_file(data,binary,target=32)
        self.assertGreater(p['reduced_triangles'],0)
        self.assertEqual(len(p['materials']),2)
        self.assertAlmostEqual(p['area'],64)
        self.assertEqual(p['min'],[0,0,0]);self.assertEqual(p['max'],[8,8,0])
        self.assertLessEqual(p['quads'],32)
        for area in p['material_areas']:self.assertAlmostEqual(area,32)
        cube=self.run_file(raw=(SOURCE/'examples/cube.glb').read_bytes(),target=1)
        self.assertEqual((cube['quads'],cube['target'],cube['reduced_triangles']),(6,1,0))
        self.assertFalse(cube['density_target_met'])
        error=self.run_file(*fixture(),target=100001,valid=False)
        self.assertIn('Target patches',error)

    def test_density_and_omission_options_work_together(self):
        data,binary=fixture(*icosphere(2))
        full=self.run_file(data,binary,omit=True)
        p=self.run_file(data,binary,target=80,omit=True)
        self.assertGreater(p['reduced_triangles'],0)
        self.assertGreater(p['quads'],0)
        self.assertLess(p['quads'],full['quads'])
        self.assertEqual(p['density_target_met'],p['quads']<=80)
        self.assertEqual(p['high_valence'],0)
        sword=self.run_file(raw=(SOURCE/'examples/simple_sword.glb').read_bytes(),omit=True)
        self.assertGreater(sword['omitted_triangles'],0)
        self.assertLess(sword['quads'],5544)
        self.assertEqual(sword['high_valence'],0)

    def test_color_fixture_surface_percentages(self):
        p=self.run_file(raw=(SOURCE/'examples/two_color_parts.glb').read_bytes())
        # The owner's saved MDL had correct red/blue diffuse colors but white
        # highlights at size 8000%, intensity 2000%. StoreValue expects fractions.
        expected={'specular_size':80,'specular_intensity':20,'reflectivity':0,'transparency':0}
        self.assertEqual(len(p['surface_fractions']),2)
        for surface in p['surface_fractions']:
            self.assertEqual({key:100*value for key,value in surface.items()},expected)

    def test_material_percentages_at_limits_and_midpoint(self):
        for roughness,metallic,alpha,expected in (
                (0,0,0,(5,20,0,100)),
                (1,1,1,(80,80,35,0)),
                (.5,.5,.25,(42.5,50,17.5,75))):
            with self.subTest(roughness=roughness,metallic=metallic,alpha=alpha):
                data,binary=fixture()
                data['materials']=[{'alphaMode':'BLEND','pbrMetallicRoughness':{
                    'roughnessFactor':roughness,'metallicFactor':metallic,'baseColorFactor':[1,0,0,alpha]}}]
                data['meshes'][0]['primitives'][0]['material']=0
                p=self.run_file(data,binary)
                surface=p['surface_fractions'][0]
                for key,percentage in zip(('specular_size','specular_intensity','reflectivity','transparency'),expected):
                    self.assertAlmostEqual(100*surface[key],percentage)
                    self.assertGreaterEqual(surface[key],0)
                    self.assertLessEqual(surface[key],1)

    def test_opaque_material_does_not_become_transparent(self):
        data,binary=fixture()
        data['materials']=[{'alphaMode':'OPAQUE','pbrMetallicRoughness':{'baseColorFactor':[0,0,1,.25]}}]
        data['meshes'][0]['primitives'][0]['material']=0
        p=self.run_file(data,binary)
        self.assertEqual(p['surface_fractions'][0]['transparency'],0)

if __name__=='__main__':unittest.main()
