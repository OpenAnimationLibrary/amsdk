"""One open peaked spline. Edit SPACING, save, then rerun in A:M."""
from ambridge import ModelPlan
SPACING = 10.0  # Raw model-space units, not the UI's display-unit selection.


def build():
    plan = ModelPlan('Scripted Three Point Spline')
    points = [plan.point(-SPACING, 0, 0), plan.point(0, SPACING, 0), plan.point(SPACING, 0, 0)]
    plan.spline(points)
    return plan
