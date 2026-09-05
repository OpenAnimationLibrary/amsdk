import importlib.util
from pathlib import Path
import unittest

MODULE = Path(__file__).resolve().parents[1] / 'examples' / 'find_5point_candidates.py'
spec = importlib.util.spec_from_file_location('find5', MODULE)
find5 = importlib.util.module_from_spec(spec)
spec.loader.exec_module(find5)


def plan(points, splines):
    return {'am_plan': 1, 'name': 'test', 'points': points, 'splines': splines}


class FivePointCandidateTests(unittest.TestCase):
    def test_simple_pentagon_found_once(self):
        p = [[0, 0, 0], [1, 0, 0], [2, 1, 0], [1, 2, 0], [0, 1, 0]]
        result = find5.find_five_point_candidates(plan(p, [[0, 1], [1, 2], [2, 3], [3, 4], [4, 0]]))
        self.assertEqual([candidate['points'] for candidate in result], [[0, 1, 2, 3, 4]])

    def test_rotation_and_reverse_are_deduplicated(self):
        p = [[0, 0, 0]] * 5
        result = find5.find_five_point_candidates(plan(p, [[0, 1, 2, 3, 4], [4, 0]]))
        self.assertEqual(len(result), 1)

    def test_chord_rejects_candidate(self):
        p = [[0, 0, 0]] * 5
        splines = [[0, 1, 2, 3, 4], [4, 0], [0, 2]]
        self.assertEqual(find5.find_five_point_candidates(plan(p, splines)), [])

    def test_four_and_six_cycles_not_reported(self):
        p = [[0, 0, 0]] * 10
        splines = [[0, 1, 2, 3], [3, 0], [4, 5, 6, 7, 8, 9], [9, 4]]
        self.assertEqual(find5.find_five_point_candidates(plan(p, splines)), [])

    def test_disconnected_extra_geometry_does_not_hide_candidate(self):
        p = [[0, 0, 0]] * 7
        splines = [[0, 1, 2, 3, 4], [4, 0], [5, 6]]
        result = find5.find_five_point_candidates(plan(p, splines))
        self.assertEqual(len(result), 1)

    def test_bad_index_rejected(self):
        with self.assertRaises(ValueError):
            find5.find_five_point_candidates(plan([[0, 0, 0]], [[0, 1]]))


if __name__ == '__main__':
    unittest.main()
