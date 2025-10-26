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

# Slab Class Reference

`#include <`<a href="influenc_8h-source.md" class="el"><code>influenc.h</code></a>`>`

Inheritance diagram for Slab:

<span class="image placeholder" original-image-src="classSlab__inherit__graph.gif" original-image-title="" border="0" usemap="#Slab__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for Slab:

<span class="image placeholder" original-image-src="classSlab__coll__graph.gif" original-image-title="" border="0" usemap="#Slab__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classSlab-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#0807667262db0cf8a6446bfdcada17e1" class="el">Slab</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#4d13cc462b417c4c3d4ad892112b5599" class="el">Slab</a> (float, float, float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#4c070b0557b1721beae94ed3acb8db3c" class="el">Init</a> (float, float, float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Intersect</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, const <a href="classVector.md" class="el">Vector</a> &amp;, ThreadInfo *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#3a8a40efddd68314bac0f4f5cb5d99fb" class="el">Intersect</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, const <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#8a11f22291743884b9331d9cb58e455e" class="el">Normal</a> (<a href="classHit.md" class="el">Hit</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">GetType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#b5bbca2d93358bcb0059f7f9c68ca1ea" class="el">Falloff</a> (<a href="classVector.md" class="el">Vector</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#7882a7921dd3430f5e0a1fa60aa374bd" class="el">Attract</a> (<a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#cf2ea65a3bf1134f7a05638c12a6c1bf" class="el">Vortex</a> (<a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#60d1c5feb2dc82c525ec1f9ef1a734b6" class="el">Friction</a> (<a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#3a5a7a2826e9d50e9b04343b3e2e5212" class="el">Lighting</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, float &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#213b1cfaaa04a087ae1be3374c726321" class="el">ComputeSides</a> (<a href="classVector.md" class="el">Vector</a> &amp;, float, float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#4b8349c99073588f0ccf6dd2c55a1202" class="el">Transform</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#cf5b86a14d1309ececc1cf2190d848b0" class="el">IsInside</a> (<a href="classVector.md" class="el">Vector</a> p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#1f8f3d611956246ca336e4f45fd01927" class="el">FindBounds</a> (<a href="classVector.md" class="el">Vector</a> &amp;min, <a href="classVector.md" class="el">Vector</a> &amp;max)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#adb115059e28d960fa8badfac5516667" class="el">center</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#433169d5d9bcbb6d43f0d288e68f0cad" class="el">axis</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#2fa47f7c65fec19cc163b195725e3844" class="el">length</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#4cd9304c784be800ce6d40457a146f77" class="el">softlength</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#db75ee0a80f4b8a7bc5a2df3be49eead" class="el">lengthdelta</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#534f9475dbab9d658c47f473afacb5de" class="el">halfwidth</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#bf53139efc301194dae1e87d86f18e50" class="el">softhalfwidth</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classSlab.md#9897f2e3e10aa27dfea4fdd010eb4107" class="el">halfwidthdelta</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

