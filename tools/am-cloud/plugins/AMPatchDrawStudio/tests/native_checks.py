"""Cross-language tests of the production native parser, not A:M construction."""
import copy
import json
from pathlib import Path
import random
import subprocess
import sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'runtime'))
from studio_core import Drawing,compile_surface,MAX_BYTES


def packet(d):
    mesh=compile_surface(d)
    return {'patchdraw_plan':1,'session':'a'*32,'serial':1,'name':d.name,'smooth':int(d.smooth),'texture':'',**{k:mesh[k] for k in ('points','uvs','splines','faces')}}


def check(executable,work):
    folder=work/'valid';folder.mkdir()
    count=0
    def save(d):
        nonlocal count
        (folder/f'{count:04d}.json').write_text(json.dumps(packet(d),separators=(',',':')),encoding='ascii');count+=1
    for mask in range(1,512):
        save(Drawing(side=3,cells={(i%3,i//3) for i in range(9) if mask>>i&1},round_outline=bool(mask%2)))
    for fragmented in (False,True):
        save(Drawing(side=64,cells={(x,y) for x in range(64) for y in range(64) if not fragmented or (x+y)%2==0}))
    for surface in ('Flat','Arch X','Arch Y','Dome','Saddle'):
        for plane in ('XY','XZ','YZ'):
            save(Drawing(side=4,cells={(x,y) for x in range(4) for y in range(4)},surface=surface,plane=plane,round_outline=True,smooth=True,rise=-23))
    run=subprocess.run([str(executable),str(folder)],capture_output=True,text=True,timeout=90)
    if run.returncode: raise AssertionError(run.stderr)
    print(run.stdout.strip())
    base=packet(Drawing(side=1,cells={(0,0)}));bad=[]
    for key,value in [('patchdraw_plan',2),('serial',0),('serial',1000000),('session','wrong'),('smooth',True),('name','bad/name'),('name','bad"name'),('texture','../outside.png'),('texture','paint-'+('b'*32)+'-000001.png'),('points',[]),('faces',[]),('uvs',[]),('splines',[])]:
        p=copy.deepcopy(base);p[key]=value;bad.append(json.dumps(p))
    p=copy.deepcopy(base);p['points'][0]=p['points'][1];bad.append(json.dumps(p))
    p=copy.deepcopy(base);p['splines'][0][0]=True;bad.append(json.dumps(p))
    p=copy.deepcopy(base);p['splines'][0].append(p['splines'][0][0]);bad.append(json.dumps(p))
    p=copy.deepcopy(base);p['faces'][0][1]=99999;bad.append(json.dumps(p))
    p=copy.deepcopy(base);p['faces'].append(p['faces'][0]);bad.append(json.dumps(p))
    p=copy.deepcopy(base);p['uvs'][0][0]=2;bad.append(json.dumps(p))
    p=copy.deepcopy(base);p['faces'][0].reverse();bad.append(json.dumps(p))
    raw=json.dumps(base);bad += ['\ufeff'+raw,raw+'x',raw[:-1]+',"name":"duplicate"}',raw[:-1]+',"unknown":0}',raw.replace('100.0','NaN'), 'x'*(MAX_BYTES+1)]
    # Ensure the nonfinite mutation is effective even when no coordinate equals 100.
    bad[-2]=raw.replace('50.0','NaN')
    for i,text in enumerate(bad):
        path=work/'invalid.json';path.write_text(text,encoding='utf-8')
        run=subprocess.run([str(executable),str(path)],capture_output=True,text=True,timeout=15)
        if run.returncode==0: raise AssertionError(f'Malformed native plan accepted: {i}')
    good=copy.deepcopy(base);good['texture']='paint-'+('a'*32)+'-000001.png'
    path=work/'paint.json';path.write_text(json.dumps(good),encoding='ascii')
    subprocess.run([str(executable),str(path)],check=True,timeout=15)
    print(f'PASS: {count+1} valid and {len(bad)} malformed native parser cases')


if __name__=='__main__':
    import tempfile
    with tempfile.TemporaryDirectory() as td: check(Path(sys.argv[1]),Path(td))
