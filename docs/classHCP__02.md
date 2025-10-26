## Detailed Description

A HCP represents a model Control Point you see in Animation Master, the building block of splines.

A HCP can link to the previous and next CP in a <a href="classHSpline.md" class="el">HSpline</a>. HCPs can also be attached to other HCPs to form a stack. To the user, attached HCPs appear to be only one HCP, where more than one spline intersect. When a HCP is attached to another HCP, the position of the control point is stored in the first HCP in the stack, which is called the head.

**About** **Bias** **and** **Magnitude**

Bias and Magnitude control the shape of the spline as it goes through the control point. Bias is made up of Gamma and Alpha.

Gamma is the angle of the spline as it goes in and out of the control point in the plane defined by the current control point and the previous and next control points. The range of Gamma can be from -180 to 180 degrees.

Alpha is similar to Gamma, except that it control the angle of the spline along the plane perpendicular to the patch's surface. The default values of Gamma and Alpha are normally zero.

Magnitude controls the amount of curve of the spline as it passes through the control point. The default value is 1.0, and a value of 0.0 creates a sharp point.

Basically the tangents are adjusted every time the vertices move. The default tangents can be calculated by subtracting the previous vertex from the next vertex and normalizing it.

<div class="fragment">

``` fragment
p1 = previous vertex
p2 = this vertex
p3 = next vertex.

a = (p2-p1).Norm();
b = (p3-p1).Norm();
c = (p3-p1).Norm();
default input magnitude for p2 = a/((a+b)/c)
default output magnitude for p2 = b/((a+b)/c)
```

</div>

**Note:**  
Since v8.0, the above pseudocode is not exact anymore. The tangents are not calculated by (p3-p1).Normalize() anymore. It is more complex, and much, much better. It isn't perfect, but as perfect as A:M can allow. The restrictions are that the tangents on a given point are calculated by the positions of the previous and next vertex. The choice to abide by this is to simplify editing.

Then the non default magnitude, alpha, and gamma are added on top of these default calculated tangents. The non default values are the once entered in AM by the user in the CP properties.

Magnitude can simply be muliplied by the default magnitude. Ex. If the user enters 150 for magnitude, simply multiply the default mag by 1.5.

To solve the gamma for p2, you define a plane created by p1, p2, p3. Gamma is entered in degrees. A close representation would be rotating the tangent in degrees starting at its calculated default tangent location along the plane decribed above. But for efficiency purpose, instead of rotating the tangent in degrees, we linearly interpolate the gamma along a line starting at the tangent to a location 90 degrees from the tangent. Then the new tangent would intersect this point on that line. So 0, 45, and 90 degrees will give you the exact same result as rotating the angle, but the in betweens will differ slighly. You might not care to do the linear part because rotating is pretty close.

Alpha is similar to gamma, but you must look at neighboring splines. You can only adjust alpha if there is a junction of two splines through a vertex. Cross the two vertices to net the normal that the alpha value will rotate around.

**End** **tangent** **calculation**

Here is how to calculate the input tangent into P2, if P2 is the end point on a spline P2, P3, P4, P5, etc.

<div align="center">

<span class="image placeholder" original-image-src="Tangent.gif" original-image-title="">Tangent.gif</span>

**End tangent calculation illustrations**

</div>

<div class="fragment">

``` fragment
Functions
float Vector.Norm() // length of vector;
void Vector.Normalized() // normalized vector
// Vector * Vector represents dot product

T3 (P2s new input tangent)
// L1: Length from P2 to P3.
L1 = (P3-P2).Norm()
// T1: L1s length along line segment P2 P4.          
T1 = (P4-P2).Normalized() * L1
// T2: T1 Projected onto line segment P2 P3. 
T2 = ((T1-P2) * (P3-P2).Normalized()) * (P3-P2).Normalized()
// T3: The mirror of T1 across P2 P3.     
T3 = T2 + (T2-T1)
Cos A1 = (P3-P2) .Normalized() * (T3-P2).Normalized()
Cos A2 = ((P2+P4)/2  P3).Normalized() * (P2-P3).Normalized()

If A1 > A2 (cos A1 < cos A2) // We must cap A1s angle
   P2+((P3-(P2+P4)/2).Normalized() *L1)
```

</div>

This is the new location of T3. We found by capping the angle of A1, to be no larger than A2, it significantly helped the appearance of the spline. One of our goals of calculating the new tangent (T3) was to preserve its distance from P2, which is L1. If angle A1 is greater than angle A2, then an easy way to adjust T3 so that A1 is the same as A2 is to use the normalized vector A2 to the midpoint of P2P4 and multiply by it the length L1 and add it to P2. This is guarateed to make angle A1 the same as A2 because they are opposite angles of an intersection between two parallel lines.

**Peaked** **CPs**

Peak points are treated differently. Their tangents actually lie on the line between its vertex and the adjoining vertex. End points are a little trickier. They actually take into consideration the previous two vertices.

Definition at line <a href="HCP_8h-source.md#l00027" class="el">27</a> of file <a href="HCP_8h-source.md" class="el">HCP.h</a>.

------------------------------------------------------------------------

