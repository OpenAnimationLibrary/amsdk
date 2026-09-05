"""3x3 logical points; six open splines; 18 CP occurrences; nine attachments.

Expected result: four planar quads after A:M patch discovery. Confirm in A:M;
JSON validation alone cannot certify native patch creation.
"""
from ambridge import ModelPlan
ROWS = 3
COLUMNS = 3
SPACING = 10.0


def build():
    if not 2 <= ROWS <= 16 or not 2 <= COLUMNS <= 16:
        raise ValueError('Example limits rows/columns to 2-16.')
    plan = ModelPlan('Scripted Grid')
    points = [[plan.point(c * SPACING, r * SPACING, 0) for c in range(COLUMNS)] for r in range(ROWS)]
    for row in points:
        plan.spline(row)
    for c in range(COLUMNS):
        plan.spline([points[r][c] for r in range(ROWS)])
    return plan
