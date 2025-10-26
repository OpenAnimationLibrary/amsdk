## Detailed Description

Defines a valid 4 point patch.

Internal Hash Patch is essentially defined by 4 Hermite splines. So there is 8 tangents around a 4 point patch. One in tangent and one Out tangent for each CP.

<div align="center">

<span class="image placeholder" original-image-src="CP-Tangents.gif" original-image-title="">CP-Tangents.gif</span>

**Relations between In tangents, Out tangents and CPs**

</div>

A Hash patch does not have the 4 central vectors called "Twist vectors" as is the case with Bezier surfaces. Instead of these twist vectors, A:M uses a heuristic to decide how to subdivide the patch based on the curviest splines first.

Starting with a HPatch, one can walk the splines by first retrieving the HCPs and then using the <a href="classHCP.md#5604a3d97e892579204bd5983c783e9c" class="el">HCP::GetSpline()</a> function.

**See also:**  
<a href="classHCP.md" class="el">HCP</a> and <a href="classHSpline.md" class="el">HSpline</a>

[PDF document describing the Hash patches.](spline.pdf)

Definition at line <a href="HPatch_8h-source.md#l00053" class="el">53</a> of file <a href="HPatch_8h-source.md" class="el">HPatch.h</a>.

------------------------------------------------------------------------

