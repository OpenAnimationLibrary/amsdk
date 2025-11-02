// include geom.h before this
#pragma once

class PolygonalArea;

void Triangulate(Subdiv *s);
int TriangulateArea(Subdiv *s, const PolygonalArea *a);
void SetLeftFaceVal(Edge *e, int v);
