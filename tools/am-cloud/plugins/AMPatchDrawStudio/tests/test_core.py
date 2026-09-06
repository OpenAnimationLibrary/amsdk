"""Portable compiler/protocol tests. They do not execute the A:M host."""
import copy
import itertools
import json
from pathlib import Path
import random
import sys
import tempfile
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from studio_core import Drawing, Session, compile_surface, sweep, strict_json, atomic_json, MAX_BYTES


def check_mesh(test,mesh):
    faces=mesh['faces']; points=mesh['points']; adjacency=[set() for _ in points]
    uses=[0]*len(points); edges=set()
    for run in mesh['splines']:
        test.assertEqual(len(run),len(set(run)))
        test.assertLessEqual(len(run),129)
        for a in run: uses[a]+=1
        for a,b in zip(run,run[1:]):
            edge=tuple(sorted((a,b))); test.assertNotIn(edge,edges); edges.add(edge)
            adjacency[a].add(b); adjacency[b].add(a)
    test.assertTrue(all(v==2 for v in uses))
    # Independent enumeration of every simple four-cycle: no unpainted hole
    # may accidentally become an extra quad through the spline graph.
    cycles=set()
    for a,neighbours in enumerate(adjacency):
        for b,d in itertools.combinations(neighbours,2):
            for c in adjacency[b]&adjacency[d]:
                if c!=a: cycles.add(tuple(sorted((a,b,c,d))))
    test.assertEqual(cycles,{tuple(sorted(face)) for face in faces})
    for face in faces:
        test.assertEqual(len(set(face)),4)
        test.assertTrue(all(tuple(sorted((a,b))) in edges for a,b in zip(face,face[1:]+face[:1])))
    test.assertEqual(mesh['occurrences'],sum(uses))


class CoreTests(unittest.TestCase):
    def test_all_three_by_three_masks(self):
        for mask in range(512):
            d=Drawing(side=3,cells={(i%3,i//3) for i in range(9) if mask>>i&1})
            mesh=compile_surface(d); self.assertEqual(len(mesh['faces']),len(d.cells)*4); check_mesh(self,mesh)

    def test_seeded_masks(self):
        rng=random.Random(1905)
        for _ in range(512):
            d=Drawing(side=4,cells={(x,y) for x in range(4) for y in range(4) if rng.randrange(2)})
            check_mesh(self,compile_surface(d))

    def test_ring_and_diagonal_islands(self):
        ring=Drawing(side=3,cells={(x,y) for x in range(3) for y in range(3)}-{(1,1)})
        p=compile_surface(ring)
        self.assertEqual((len(p['points']),len(p['splines']),p['occurrences'],p['holes']),(48,16,96,1))
        d=Drawing(side=2,cells={(0,0),(1,1)})
        p=compile_surface(d);self.assertEqual(p['component_count'],2);self.assertEqual(len(p['points']),18)

    def test_full_high_resolution(self):
        d=Drawing(side=64,cells={(x,y) for x in range(64) for y in range(64)})
        p=compile_surface(d); check_mesh(self,p)
        self.assertEqual((len(p['faces']),len(p['points']),len(p['splines']),p['occurrences']),(16384,16641,258,33282))

    def test_fragmented_high_resolution(self):
        d=Drawing(side=64,cells={(x,y) for x in range(64) for y in range(64) if (x+y)%2==0})
        p=compile_surface(d);check_mesh(self,p)
        self.assertEqual((p['component_count'],len(p['points']),len(p['splines']),p['occurrences']),(2048,18432,12288,36864))

    def test_profiles_and_planes(self):
        d=Drawing(side=3,cells={(x,y) for x in range(3) for y in range(3)})
        flat=compile_surface(d)
        for surface in ('Flat','Arch X','Arch Y','Dome','Saddle'):
            for plane in ('XY','XZ','YZ'):
                d.surface=surface;d.plane=plane;d.rise=-8;d.round_outline=True
                p=compile_surface(d);check_mesh(self,p)
                self.assertEqual(p['faces'],flat['faces']);self.assertEqual(p['uvs'],flat['uvs'])
                if surface!='Flat':self.assertNotEqual(p['points'],flat['points'])

    def test_outline_preserves_connectivity(self):
        for mask in range(1,512):
            d=Drawing(side=3,cells={(i%3,i//3) for i in range(9) if mask>>i&1})
            p=compile_surface(d);d.round_outline=True;q=compile_surface(d)
            self.assertEqual((p['faces'],p['splines']),(q['faces'],q['splines']))

    def test_refine_same_world_size(self):
        d=Drawing(side=4,width=88,height=17,cells={(x,y) for x in range(4) for y in range(4)})
        p=compile_surface(d);d.refine();q=compile_surface(d)
        self.assertEqual(len(q['faces']),len(p['faces'])*4)
        self.assertEqual((d.width,d.height),(88,17))
        for axis in range(3):
            self.assertEqual((min(v[axis] for v in p['points']),max(v[axis] for v in p['points'])),(min(v[axis] for v in q['points']),max(v[axis] for v in q['points'])))
        d.side=64
        with self.assertRaises(ValueError):d.refine()

    def test_sweep_and_erase(self):
        d=Drawing(side=64);sweep(d,(.5,.5),(63.5,63.5),.25)
        self.assertTrue(all((i,i) in d.cells for i in range(64)))
        old=set(d.cells);sweep(d,(.5,.5),(63.5,63.5),.25);self.assertEqual(d.cells,old)
        sweep(d,(.5,.5),(63.5,63.5),.25,True);self.assertFalse(d.cells)
        sweep(d,(-99,-99),(-99,99),.25);self.assertFalse(d.cells)

    def test_recipe_roundtrip(self):
        d=Drawing(side=3,cells={(0,0),(2,2)},surface='Dome',smooth=False)
        e=Drawing.from_recipe(json.loads(json.dumps(d.recipe())))
        self.assertEqual(e.recipe(),d.recipe())

    def test_invalid_recipes(self):
        base=Drawing().recipe()
        for key,value in [('side',65),('side',True),('width',0),('height',float('nan')),('rise',1e10),('origin',None),('origin',[0,0,True]),('smooth',1),('name','a/b'),('name','"'),('name',None),('cells',[[0,0],[0,0]]),('cells',[[True,1]]),('cells',[[100,1]])]:
            data=copy.deepcopy(base);data[key]=value
            with self.subTest(key=key,value=value),self.assertRaises(ValueError):Drawing.from_recipe(data)
        with self.assertRaises(ValueError): Drawing.from_recipe({**base,'unknown':1})

    def test_json_rejects_duplicate_nonfinite_and_deep_data(self):
        for text in ('{"x":0,"x":1}','{"x":NaN}', '['*2000+']'*2000):
            with self.assertRaises(ValueError):strict_json(text)
        with self.assertRaises(ValueError): strict_json(' '*MAX_BYTES+'x')

    def test_session_and_atomic_preservation(self):
        with tempfile.TemporaryDirectory() as td:
            a=Session(Path(td));b=Session(Path(td));self.assertNotEqual(a.token,b.token)
            self.assertEqual(a.connection.read_bytes(),b'PATCHDRAW-STUDIO/1\n'+a.token.encode()+b'\n')
            d=Drawing(side=1,cells={(0,0)});mesh=compile_surface(d)
            packet=a.packet(d,mesh,'texture-000001.png');self.assertEqual(packet['serial'],1)
            path=a.path/'request.json';atomic_json(path,packet,False);raw=path.read_bytes()
            with self.assertRaises(FileExistsError):atomic_json(path,{'different':1},False)
            self.assertEqual(raw,path.read_bytes());self.assertFalse(list(a.path.glob('*.tmp')))
            a.packet(d,mesh,'');self.assertEqual(a.serial,2)


if __name__=='__main__': unittest.main()
