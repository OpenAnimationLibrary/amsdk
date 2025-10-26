<div class="tabs">

- [Main Page](index.md)
- <span id="current">[Classes](annotated.md)</span>
- [Files](files.md)
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [Class List](annotated.md)
- [Alphabetical List](classes.md)
- [Class Hierarchy](hierarchy.md)
- [Class Members](functions.md)

</div>

# DisplaceQuadrangle Class Reference

`#include <`<a href="influenc_8h-source.md" class="el"><code>influenc.h</code></a>`>`

Inheritance diagram for DisplaceQuadrangle:

<span class="image placeholder" original-image-src="classDisplaceQuadrangle__inherit__graph.gif" original-image-title="" border="0" usemap="#DisplaceQuadrangle__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for DisplaceQuadrangle:

<span class="image placeholder" original-image-src="classDisplaceQuadrangle__coll__graph.gif" original-image-title="" border="0" usemap="#DisplaceQuadrangle__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classDisplaceQuadrangle-members.md)

<table data-border="0" data-cellpadding="0" data-cellspacing="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td></td>
<td></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classDisplaceQuadrangle.md#3077783a0b5663fb002105127ca24dd9" class="el">DisplaceQuadrangle</a> (<a href="classVector.md" class="el">Vector</a> &amp;p1, <a href="classVector.md" class="el">Vector</a> &amp;p2, <a href="classVector.md" class="el">Vector</a> &amp;p3, <a href="classVector.md" class="el">Vector</a> &amp;p4, float <a href="classQuadObject.md#36c5912f6e22a8791f1e2b080fec1f7e" class="el">smin</a>, float <a href="classQuadObject.md#bd92ac5ba2dc1a7673c98858cfbab0af" class="el">smax</a>, float <a href="classQuadObject.md#940c5db2b6e1c6c92f011046b22732c0" class="el">tmin</a>, float <a href="classQuadObject.md#5b5f9dec7e1226b2974d50c3df7a5c6b" class="el">tmax</a>, <a href="classVector.md" class="el">Vector</a> &amp;pn1, <a href="classVector.md" class="el">Vector</a> &amp;pn2, <a href="classVector.md" class="el">Vector</a> &amp;pn3, <a href="classVector.md" class="el">Vector</a> &amp;pn4, int <a href="classQuadrangle.md#c19693bf3397e41bd09a2c8ab0fbe79f" class="el">polyid</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classDisplaceQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">Normal</a> (<a href="classHit.md" class="el">Hit</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="influenc_8h-source.md#l00070" class="el">70</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="3077783a0b5663fb002105127ca24dd9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">DisplaceQuadrangle::DisplaceQuadrangle</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>p1</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>p2</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>p3</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>p4</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>smin</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>smax</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>tmin</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>tmax</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>pn1</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>pn2</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>pn3</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>pn4</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>polyid</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="influenc_8h-source.md#l00072" class="el">72</a> of file <a href="influenc_8h-source.md" class="el">influenc.h</a>. |

------------------------------------------------------------------------

## Member Function Documentation

<span id="8a11f22291743884b9331d9cb58e455e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void DisplaceQuadrangle::Normal</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHit.md" class="el">Hit</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Reimplemented from <a href="classFractalQuadrangle.md#8a11f22291743884b9331d9cb58e455e" class="el">FractalQuadrangle</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="influenc_8h-source.md" class="el">influenc.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:51 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
