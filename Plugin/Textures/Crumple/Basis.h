#pragma once

void Voronoi3(const Vector *pos, // input position
              Vector *tocell1, // output position 1
              Vector *tocell2, // output position 2
              double *dist1, // output distance 1
              double *dist2); // output distance 2
/*
void linear_blend(double val, 
			      double start,
				  double end,
				  miColor *col1,
				  miColor *col2,
				  miColor *outcol);

void quad_blend (double index, 
				 double mid1val,
				 double mid2val,
				 miBoolean domid1,
				 miBoolean domid2,
				 miColor *col1,
				 miColor *col2,
				 miColor *mid1,
				 miColor *mid2,
				 miColor *result);
*/
double smoothstep(double a, double b, double x);
double linearstep(double a, double b, double x);
