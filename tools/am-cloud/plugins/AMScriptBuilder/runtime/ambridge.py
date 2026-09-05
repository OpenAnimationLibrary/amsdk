"""AMScriptBuilder plan v1. Data only: no A:M, network, pip or file writes."""
from __future__ import annotations
import json
import math
import re
import struct

MAX_BYTES = 262144
MAX_POINTS = 1024
MAX_SPLINES = 128
MAX_PER_SPLINE = 256
MAX_OCCURRENCES = 2048


def validate(plan: dict) -> dict:
    if type(plan) is not dict or set(plan) != {'am_plan', 'name', 'points', 'splines'}:
        raise ValueError('Expected exactly am_plan, name, points and splines.')
    if type(plan['am_plan']) is not int or plan['am_plan'] != 1:
        raise ValueError('Unsupported plan version.')
    name = plan['name']
    if (type(name) is not str or not re.fullmatch(r'[A-Za-z0-9 _.-]{1,64}', name)
            or name != name.strip()):
        raise ValueError('Name: 1-64 ASCII letters/digits/spaces/underscore/dot/hyphen, no edge spaces.')
    points, splines = plan['points'], plan['splines']
    if type(points) is not list or not 2 <= len(points) <= MAX_POINTS:
        raise ValueError('Expected 2-1024 logical points.')
    converted = []
    for point in points:
        if type(point) is not list or len(point) != 3:
            raise ValueError('Each point requires exactly three coordinates.')
        values = []
        for x in point:
            if type(x) not in (int, float) or abs(x) > 100000 or not math.isfinite(x):
                raise ValueError('Coordinates must be finite numbers within +/-100000 model units.')
            f = struct.unpack('<f', struct.pack('<f', x))[0]
            if x != 0 and f == 0:
                raise ValueError('Coordinate underflows SDK float range.')
            values.append(f)
        converted.append(values)
    if type(splines) is not list or not 1 <= len(splines) <= MAX_SPLINES:
        raise ValueError('Expected 1-128 open splines.')
    uses = [0] * len(points)
    edges = set()
    total = 0
    for spline in splines:
        if type(spline) is not list or not 2 <= len(spline) <= MAX_PER_SPLINE:
            raise ValueError('Each spline needs 2-256 indices.')
        total += len(spline)
        if total > MAX_OCCURRENCES:
            raise ValueError('At most 2048 CP occurrences.')
        unique = set()
        for i, index in enumerate(spline):
            if type(index) is not int or not 0 <= index < len(points):
                raise ValueError('Invalid point index.')
            if index in unique:
                raise ValueError('Repeated point in spline; loops are not supported in v1.')
            unique.add(index)
            uses[index] += 1
            if uses[index] > 2:
                raise ValueError('At most two spline occurrences per logical point.')
            if i:
                previous = spline[i - 1]
                if converted[index] == converted[previous]:
                    raise ValueError('Zero-length edge after SDK float conversion.')
                edge = tuple(sorted((index, previous)))
                if edge in edges:
                    raise ValueError('Duplicate logical edge.')
                edges.add(edge)
    if 0 in uses:
        raise ValueError('Unused logical points.')
    # Deep snapshot, not a reference to mutable user script data.
    result = {'am_plan': 1, 'name': name, 'points': [list(p) for p in points],
              'splines': [list(s) for s in splines]}
    if len(json.dumps(result, allow_nan=False, separators=(',', ':'))) > MAX_BYTES:
        raise ValueError('Plan exceeds byte limit.')
    return result


class ModelPlan:
    """Indices identify logical points; reusing an index requests attachment.

    All splines in v1 are open and peaked. Equal positions with different indices
    are deliberately not attached. Units are raw A:M model-space units.
    """
    def __init__(self, name: str):
        self.data = {'am_plan': 1, 'name': name, 'points': [], 'splines': []}

    def point(self, x: float, y: float, z: float) -> int:
        if len(self.data['points']) >= MAX_POINTS:
            raise ValueError('Too many points.')
        index = len(self.data['points'])
        self.data['points'].append([x, y, z])
        return index

    def spline(self, indices: list[int]) -> None:
        if len(self.data['splines']) >= MAX_SPLINES:
            raise ValueError('Too many splines.')
        self.data['splines'].append(list(indices))

    def to_dict(self) -> dict:
        return validate(self.data)
