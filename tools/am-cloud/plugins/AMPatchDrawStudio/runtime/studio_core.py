"""Patch Draw Studio: bounded, SDK-independent surface compiler and file protocol.

The local-fan / two-by-two topology is ported from PatchDrawCore.h (v0.1).
Coordinates are not used as vertex identity at diagonal contacts. No host pointers,
network calls, shell commands, or modification of an existing model occur here.
"""
from __future__ import annotations

from collections import defaultdict, deque
from dataclasses import dataclass, field, asdict
from pathlib import Path
import json
import math
import os
import re
import time
import uuid

MAX_SIDE = 64
MAX_POINTS = 40000
MAX_SPLINES = 25000
MAX_OCCURRENCES = 80000
MAX_FACES = 16384
MAX_BYTES = 8 * 1024 * 1024
NAME = re.compile(r"[A-Za-z0-9][A-Za-z0-9 _.-]{0,39}\Z")
SURFACES = ("Flat", "Arch X", "Arch Y", "Dome", "Saddle")


def finite(value, low, high):
    if isinstance(value, bool) or not isinstance(value, (int, float)):
        raise ValueError("Expected a number, not a boolean or string")
    if not low <= value <= high or not math.isfinite(value):
        raise ValueError(f"Value must be finite and between {low} and {high}")
    return float(value)


@dataclass
class Drawing:
    side: int = 16
    width: float = 100.0
    height: float = 100.0
    surface: str = "Flat"
    rise: float = 15.0
    plane: str = "XY"
    origin: tuple[float, float, float] = (0.0, 0.0, 0.0)
    smooth: bool = True
    round_outline: bool = False
    name: str = "Shape"
    cells: set[tuple[int, int]] = field(default_factory=set)

    def validate(self):
        if type(self.side) is not int or not 1 <= self.side <= MAX_SIDE:
            raise ValueError("Drawing resolution must be 1-64 cells per side")
        finite(self.width, .01, 10000); finite(self.height, .01, 10000)
        finite(self.rise, -10000, 10000)
        if self.surface not in SURFACES or self.plane not in ("XY", "XZ", "YZ"):
            raise ValueError("Unsupported surface or construction plane")
        if not isinstance(self.origin,(tuple,list)) or len(self.origin) != 3:
            raise ValueError("Origin needs X, Y and Z")
        for value in self.origin:
            finite(value, -50000, 50000)
        if type(self.smooth) is not bool or type(self.round_outline) is not bool:
            raise ValueError("Smoothing options must be booleans")
        if not isinstance(self.name,str) or not NAME.fullmatch(self.name) or self.name.endswith(" "):
            raise ValueError("Use a name of 1-40 ASCII letters/digits, spaces, dot, dash or underscore; start with a letter/digit")
        if not isinstance(self.cells,set) or len(self.cells)>MAX_SIDE**2: raise ValueError("Invalid coverage set")
        for cell in self.cells:
            if not isinstance(cell,tuple) or len(cell) != 2 or any(type(v) is not int or not 0 <= v < self.side for v in cell):
                raise ValueError("Cell lies outside the drawing")
        return self

    def recipe(self):
        self.validate()
        data = asdict(self)
        data["cells"] = sorted(self.cells)
        data["origin"] = list(self.origin)
        data["patchdraw_recipe"] = 1
        return data

    @classmethod
    def from_recipe(cls, data):
        expected = set(cls.__dataclass_fields__) | {"patchdraw_recipe"}
        if not isinstance(data, dict) or set(data) != expected or type(data["patchdraw_recipe"]) is not int or data["patchdraw_recipe"] != 1:
            raise ValueError("Not a supported Patch Draw recipe")
        data = dict(data); del data["patchdraw_recipe"]
        cells = data["cells"]
        if not isinstance(cells, list) or len(cells) > MAX_SIDE**2:
            raise ValueError("Invalid cell list")
        if any(not isinstance(c, list) or len(c) != 2 or any(type(x) is not int for x in c) for c in cells):
            raise ValueError("Cells must be integer pairs")
        data["cells"] = {tuple(c) for c in cells}
        if len(data["cells"]) != len(cells):
            raise ValueError("Duplicate cells in recipe")
        return cls(**data).validate()

    def refine(self):
        if self.side * 2 > MAX_SIDE:
            raise ValueError("Already at maximum drawing resolution")
        self.cells = {(2*x+dx, 2*y+dy) for x,y in self.cells for dx in (0,1) for dy in (0,1)}
        self.side *= 2  # World size and texture UV layout deliberately unchanged.


def compile_surface(d: Drawing):
    d.validate()
    fine = {(2*x+dx, 2*y+dy) for x,y in d.cells for dx in (0,1) for dy in (0,1)}
    around = defaultdict(set)
    for x,y in fine:
        for v in ((x,y), (x+1,y), (x+1,y+1), (x,y+1)):
            around[v].add((x,y))
    vertices, identity = [], {}
    for vertex, incident in sorted(around.items()):
        remaining = set(incident)
        while remaining:
            start = min(remaining); remaining.remove(start)
            fan, todo = [start], [start]
            while todo:
                x,y = todo.pop()
                for q in ((x-1,y), (x+1,y), (x,y-1), (x,y+1)):
                    if q in remaining:
                        remaining.remove(q); fan.append(q); todo.append(q)
            index = len(vertices); vertices.append(vertex)
            for face in fan:
                identity[vertex, face] = index
    faces, face_cells = [], sorted(fine)
    uses = defaultdict(int)
    for x,y in face_cells:
        face = [identity[v,(x,y)] for v in ((x,y),(x+1,y),(x+1,y+1),(x,y+1))]
        faces.append(face)
        for a,b in zip(face, face[1:] + face[:1]):
            uses[tuple(sorted((a,b)))] += 1
    adjacency = [[] for _ in vertices]
    boundary = [[] for _ in vertices]
    for (a,b), count in uses.items():
        if count not in (1,2):
            raise ValueError("Nonmanifold edge")
        adjacency[a].append(b); adjacency[b].append(a)
        if count == 1:
            boundary[a].append(b); boundary[b].append(a)
    if any(len(row) not in (0,2) for row in boundary):
        raise ValueError("Nonmanifold boundary")
    components = [-1] * len(vertices)
    count = 0
    for start in range(len(vertices)):
        if components[start] >= 0:
            continue
        todo = [start]; components[start] = count
        while todo:
            for q in adjacency[todo.pop()]:
                if components[q] < 0:
                    components[q] = count; todo.append(q)
        count += 1
    splines = []
    for axis in (0,1):
        following, previous = {}, {}
        for a,b in sorted(uses):
            if vertices[a][1-axis] != vertices[b][1-axis]:
                continue
            if vertices[a][axis] > vertices[b][axis]:
                a,b = b,a
            if a in following or b in previous:
                raise ValueError("Ambiguous spline run")
            following[a] = b; previous[b] = a
        for start in sorted(set(following) - set(previous)):
            run = [start]
            while run[-1] in following:
                run.append(following[run[-1]])
                if len(run) > len(vertices):
                    raise ValueError("Spline cycle")
            splines.append(run)
    occurrences = sum(map(len, splines))
    if len(vertices) > MAX_POINTS or len(splines) > MAX_SPLINES or occurrences > MAX_OCCURRENCES or len(faces) > MAX_FACES:
        raise ValueError("Native geometry budget exceeded; reduce resolution or fragmentation")
    positions = [[float(x), float(y)] for x,y in vertices]
    if d.round_outline:
        # Limited boundary relaxation, never a change to face/edge connectivity.
        # Check every proposed pass for oriented positive-area quads.
        for _ in range(4):
            next_positions = [p[:] for p in positions]
            for i, row in enumerate(boundary):
                if row:
                    for axis in (0,1):
                        next_positions[i][axis] = .7*positions[i][axis] + .15*sum(positions[j][axis] for j in row)
            def positive(face):
                pts = [next_positions[i] for i in face]
                return all((pts[(j+1)%4][0]-pts[j][0])*(pts[(j+2)%4][1]-pts[(j+1)%4][1]) -
                           (pts[(j+1)%4][1]-pts[j][1])*(pts[(j+2)%4][0]-pts[(j+1)%4][0]) > 1e-7 for j in range(4))
            if not all(positive(f) for f in faces):
                break
            positions = next_positions
    points = []
    for x,y in positions:
        u,v = x/d.side - 1, y/d.side - 1
        px,py = u*d.width/2, v*d.height/2
        h = {"Flat": 0, "Arch X": 1-u*u, "Arch Y": 1-v*v,
             "Dome": (1-u*u)*(1-v*v), "Saddle": u*u-v*v}[d.surface] * d.rise
        p = (px,py,h) if d.plane == "XY" else (px,h,-py) if d.plane == "XZ" else (h,px,py)
        points.append([round(p[i] + d.origin[i], 7) for i in range(3)])
    uvs = [[x/(2*d.side), 1-y/(2*d.side)] for x,y in vertices]  # Pillow origin: top left.
    return {"points": points, "uvs": uvs, "splines": splines, "faces": faces,
            "face_cells": face_cells, "components": components, "component_count": count,
            "holes": count-len(vertices)+len(uses)-len(faces), "occurrences": occurrences}


def squared_segment_box(a, b, x, y):
    """Squared distance from a segment to a closed unit box (swept brush)."""
    lo,hi,intersects = 0.0,1.0,True
    for axis, minimum in ((0,x),(1,y)):
        delta = b[axis]-a[axis]
        if delta == 0:
            intersects &= minimum <= a[axis] <= minimum+1
        else:
            first,last = sorted(((minimum-a[axis])/delta,(minimum+1-a[axis])/delta))
            lo,hi = max(lo,first),min(hi,last)
    if intersects and lo <= hi:
        return 0.0
    def box(p):
        return (p[0]-max(x,min(x+1,p[0])))**2 + (p[1]-max(y,min(y+1,p[1])))**2
    den = sum((b[i]-a[i])**2 for i in (0,1))
    def segment(p):
        t = max(0,min(1,sum((p[i]-a[i])*(b[i]-a[i]) for i in (0,1))/den)) if den else 0
        return sum((p[i]-a[i]-t*(b[i]-a[i]))**2 for i in (0,1))
    return min(box(a),box(b),*(segment(p) for p in ((x,y),(x+1,y),(x+1,y+1),(x,y+1))))


def sweep(d, a, b, radius, erase=False):
    radius = finite(radius, .125, 8)
    for p in (a,b):
        for v in p:
            finite(v,-1e6,1e6)
    x0=max(0,math.floor(min(a[0],b[0])-radius)); x1=min(d.side,math.ceil(max(a[0],b[0])+radius))
    y0=max(0,math.floor(min(a[1],b[1])-radius)); y1=min(d.side,math.ceil(max(a[1],b[1])+radius))
    for y in range(y0,y1):
        for x in range(x0,x1):
            if squared_segment_box(a,b,x,y) < radius*radius:
                if erase: d.cells.discard((x,y))
                else: d.cells.add((x,y))


def strict_json(text):
    if len(text.encode("utf-8")) > MAX_BYTES:
        raise ValueError("File exceeds 8 MiB")
    depth=0; quoted=False; escaped=False
    for c in text:
        if quoted:
            if escaped: escaped=False
            elif c=="\\": escaped=True
            elif c=='"': quoted=False
        elif c=='"': quoted=True
        elif c in "[{":
            depth+=1
            if depth>32: raise ValueError("Excessive JSON nesting")
        elif c in "]}": depth-=1
    def pairs(items):
        result = {}
        for k,v in items:
            if k in result: raise ValueError("Duplicate JSON field: " + k)
            result[k]=v
        return result
    try:
        return json.loads(text, object_pairs_hook=pairs, parse_constant=lambda _: (_ for _ in ()).throw(ValueError("Nonfinite JSON")))
    except RecursionError as exc:
        raise ValueError("Excessive JSON nesting") from exc


def atomic_json(path: Path, data, replace=True):
    raw = json.dumps(data, ensure_ascii=True, allow_nan=False, separators=(",",":")).encode("ascii")
    if len(raw) > MAX_BYTES:
        raise ValueError("Serialized data exceeds 8 MiB")
    temporary = path.with_name(path.name + "." + uuid.uuid4().hex + ".tmp")
    created=False
    try:
        with temporary.open("xb") as f:
            created=True
            f.write(raw); f.flush(); os.fsync(f.fileno())
        if not replace and path.exists():
            raise FileExistsError(path)
        os.replace(temporary,path)
    finally:
        if created: temporary.unlink(missing_ok=True)


class Session:
    """A fresh persistent workspace. Texture snapshots are never cleaned on exit."""
    def __init__(self, parent: Path):
        self.token = uuid.uuid4().hex
        self.path = parent / (time.strftime("PatchDraw-%Y%m%d-%H%M%S-") + self.token[:8])
        self.path.mkdir(parents=False, exist_ok=False)
        self.connection = self.path / "connection.pdstudio"
        self.connection.write_text("PATCHDRAW-STUDIO/1\n"+self.token+"\n",encoding="ascii",newline="\n")
        self.serial = 0

    def packet(self, drawing, geometry, texture):
        self.serial += 1
        if self.serial > 999999: raise ValueError("Start a new Studio session")
        if not geometry["faces"]: raise ValueError("Draw a surface first")
        return {"patchdraw_plan":1,"session":self.token,"serial":self.serial,
                "name":drawing.name,"smooth":int(drawing.smooth),"texture":texture,
                **{k: geometry[k] for k in ("points","uvs","splines","faces")}}
