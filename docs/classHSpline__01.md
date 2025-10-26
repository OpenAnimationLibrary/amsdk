## Detailed Description

The HSpline class represents the spline curves that contain HCPs and that are stitched together to make the patch based models.

**Note:**  
Most operations that affect HSplines are actually performed on HCPs.

Model files store a list of splines. These splines are Bezier splines. A spline is a list of vertices and each vertex has an input/output tangent control vertice which is computed based on the alpha/gamma/magnitude values. Once these splines are loaded, a heuristic traverses them and determines valid 3 and 4 vertex patches.

Internal Hash Patch is essentially defined by 4 Hermite splines. Unlike the Bezier spline where the tangents are defined from control vectors which have absolute coordinates, Hermite splines are defined from CPs and tangent vectors for each CP. There are two tangents on each CP: the In tangent and the Out tangent. For smooth CPs, the In tangent and the Out tangent are in excact opposed direction.

Generally when you want to walk a spline you will use the HSpline member function <a href="classHSpline.md#d55b4a9828c87389479aeeea3f625fde" class="el">GetHeadCP()</a> to get the first <a href="classHCP.md" class="el">HCP</a> in the HSpline, and use <a href="classHCP.md#0d4ba4036cc2dcca8c73cdde356797cd" class="el">HCP::GetNext()</a> to walk to the end. If the spline is looped, make sure to use the <a href="classHCP.md#9cbcca8dca730418dadff034cb15ac2e" class="el">HCP::IsLoop()</a> function to find the last <a href="classHCP.md" class="el">HCP</a> in the spline.

**See also:**  
<a href="classHCP.md" class="el">HCP</a>

<!-- -->

**Note:**  
All splines have a minimum of two control points.

Definition at line <a href="HPatch_8h-source.md#l00012" class="el">12</a> of file <a href="HPatch_8h-source.md" class="el">HPatch.h</a>.

------------------------------------------------------------------------

