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

# QuadObject Class Reference

`#include <`<a href="influenc_8h-source.md" class="el"><code>influenc.h</code></a>`>`

Inheritance diagram for QuadObject:

<span class="image placeholder" original-image-src="classQuadObject__inherit__graph.gif" original-image-title="" border="0" usemap="#QuadObject__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for QuadObject:

<span class="image placeholder" original-image-src="classQuadObject__coll__graph.gif" original-image-title="" border="0" usemap="#QuadObject__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classQuadObject-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#bc715659c306f0a65069ac15e7f2d659" class="el">operator new</a> (size_t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#4bffe3bafe7317374a6eb3369ba34453" class="el">IsPatch</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">GetType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#c3c898dc00647a45cf30e65c45723946" class="el">Intersect</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, const <a href="classVector.md" class="el">Vector</a> &amp;, ThreadInfo *)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#c4fc0ecc7d5b33b72e07a25a9c9e8d4d" class="el">Collision</a> (ThreadInfo *, <a href="classVector.md" class="el">Vector</a> &amp;min, <a href="classVector.md" class="el">Vector</a> &amp;max)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#d4db60536569ed9a39b2a82c7cba5024" class="el">Normal</a> (<a href="classHit.md" class="el">Hit</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)=0</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#36c5912f6e22a8791f1e2b080fec1f7e" class="el">smin</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#bd92ac5ba2dc1a7673c98858cfbab0af" class="el">smax</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#940c5db2b6e1c6c92f011046b22732c0" class="el">tmin</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuadObject.md#5b5f9dec7e1226b2974d50c3df7a5c6b" class="el">tmax</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

