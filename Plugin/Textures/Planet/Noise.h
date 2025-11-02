#pragma once

double Noise3(double x, double y, double z);
double Noise3Node(Vector EPoint); // -1 to +1 but grabs node pt.
Vector VNoise3Node(Vector EPoint);
float smoothstep(float a, float b, float x);
void Voronoi3(Vector pos, // input Vec3
              Vector *cell1, // ouput Vec3 nearest
              Vector *cell2, // ouput Vec3 second
              double *dist1, // nearest distance ^2
              double *dist2); // second nearest dist ^2

void init_noiz_tbl();
