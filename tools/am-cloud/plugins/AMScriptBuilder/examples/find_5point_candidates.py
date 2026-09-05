#!/usr/bin/env python3
"""Find five-sided patch candidates in an AMScriptBuilder v1 JSON plan.

This analyzes PLAN TOPOLOGY ONLY. It does not inspect A:M, call the SDK, or prove
that A:M will create an HPatch5. The native authority remains
HModelCache::FindPatches() followed by GetHeadPatch5().

A candidate is reported when five distinct logical points form a chordless
5-cycle in the undirected edge graph implied by adjacent point indices in the
plan's open splines. Reverse/rotated duplicates are collapsed.

Usage:
    python find_5point_candidates.py path/to/model.json
    python find_5point_candidates.py path/to/model.json --json
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Iterable


def _canonical_cycle(cycle: Iterable[int]) -> tuple[int, ...]:
    values = tuple(cycle)
    if len(values) != 5 or len(set(values)) != 5:
        raise ValueError("Expected five distinct vertices.")
    variants = []
    for direction in (values, tuple(reversed(values))):
        for offset in range(5):
            variants.append(direction[offset:] + direction[:offset])
    return min(variants)


def _graph(plan: dict) -> tuple[list[list[float]], dict[int, set[int]]]:
    if type(plan) is not dict:
        raise ValueError("Plan must be a JSON object.")
    if plan.get("am_plan") != 1:
        raise ValueError("Only AMScriptBuilder plan version 1 is supported.")
    points = plan.get("points")
    splines = plan.get("splines")
    if type(points) is not list or type(splines) is not list:
        raise ValueError("Plan requires points and splines arrays.")
    if len(points) > 1024 or len(splines) > 128:
        raise ValueError("Plan exceeds AMScriptBuilder v1 topology limits.")
    adjacency = {index: set() for index in range(len(points))}
    for spline in splines:
        if type(spline) is not list or not 2 <= len(spline) <= 256:
            raise ValueError("Every spline must contain 2-256 point indices.")
        for a, b in zip(spline, spline[1:]):
            if type(a) is not int or type(b) is not int:
                raise ValueError("Spline indices must be integers.")
            if not 0 <= a < len(points) or not 0 <= b < len(points):
                raise ValueError("Spline index is outside points array.")
            if a == b:
                raise ValueError("Self edges are not supported.")
            adjacency[a].add(b)
            adjacency[b].add(a)
    return points, adjacency


def find_five_point_candidates(plan: dict) -> list[dict]:
    points, adjacency = _graph(plan)
    cycles: set[tuple[int, ...]] = set()

    # Depth is fixed at five, so this remains bounded by the plan limits rather
    # than using a general unbounded cycle-enumeration algorithm.
    for start in adjacency:
        stack: list[tuple[int, tuple[int, ...]]] = [(start, (start,))]
        while stack:
            current, path = stack.pop()
            if len(path) == 5:
                if start in adjacency[current]:
                    cycle = _canonical_cycle(path)
                    # A 5-point boundary candidate must not contain an internal
                    # graph chord among its five boundary vertices.
                    chord = False
                    for i, a in enumerate(cycle):
                        permitted = {cycle[(i - 1) % 5], cycle[(i + 1) % 5]}
                        if any(b in adjacency[a] and b not in permitted
                               for b in cycle if b != a):
                            chord = True
                            break
                    if not chord:
                        cycles.add(cycle)
                continue
            for neighbor in adjacency[current]:
                if neighbor == start or neighbor in path:
                    continue
                # Canonical pruning: every cycle is discovered from its lowest
                # numbered vertex, avoiding large duplicate search branches.
                if neighbor < start:
                    continue
                stack.append((neighbor, path + (neighbor,)))

    return [
        {
            "points": list(cycle),
            "positions": [points[index] for index in cycle],
        }
        for cycle in sorted(cycles)
    ]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("plan", type=Path, help="AMScriptBuilder v1 JSON plan")
    parser.add_argument("--json", action="store_true",
                        help="emit machine-readable candidate data")
    args = parser.parse_args()
    data = json.loads(args.plan.read_text(encoding="utf-8"))
    candidates = find_five_point_candidates(data)
    if args.json:
        print(json.dumps({"candidate_count": len(candidates),
                          "candidates": candidates}, indent=2))
    else:
        print(f"Five-point patch candidates: {len(candidates)}")
        for number, candidate in enumerate(candidates, 1):
            indices = ", ".join(str(value) for value in candidate["points"])
            print(f"  {number}: points [{indices}]")
        print("Candidate topology only; confirm actual HPatch5 results in A:M.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
