// include geom.h before this
#pragma once

class PolygonalArea;

void Quadrify(Subdiv *s);
void QuadrifyArea(Subdiv *s, const PolygonalArea *a);
void QuadrifyAreas(Subdiv *s, const PolygonalAreaArray *areas);
