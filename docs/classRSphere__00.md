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

# RSphere Class Reference

`#include <`<a href="influenc_8h-source.md" class="el"><code>influenc.h</code></a>`>`

Inheritance diagram for RSphere:

<span class="image placeholder" original-image-src="classRSphere__inherit__graph.gif" original-image-title="" border="0" usemap="#RSphere__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for RSphere:

<span class="image placeholder" original-image-src="classRSphere__coll__graph.gif" original-image-title="" border="0" usemap="#RSphere__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classRSphere-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#636fe41915358c2ccf43d3f16fa290ab" class="el">RSphere</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#5e096254ad77fd1d0c9a78c8b679224f" class="el">RSphere</a> (float, float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#edbcb285d8008c27561169c5c06ff29d" class="el">Init</a> (float, float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Intersect</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, const <a href="classVector.md" class="el">Vector</a> &amp;, ThreadInfo *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#3a8a40efddd68314bac0f4f5cb5d99fb" class="el">Intersect</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, const <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#8a11f22291743884b9331d9cb58e455e" class="el">Normal</a> (<a href="classHit.md" class="el">Hit</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">GetType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#b5bbca2d93358bcb0059f7f9c68ca1ea" class="el">Falloff</a> (<a href="classVector.md" class="el">Vector</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#7882a7921dd3430f5e0a1fa60aa374bd" class="el">Attract</a> (<a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#cf2ea65a3bf1134f7a05638c12a6c1bf" class="el">Vortex</a> (<a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#60d1c5feb2dc82c525ec1f9ef1a734b6" class="el">Friction</a> (<a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#3a5a7a2826e9d50e9b04343b3e2e5212" class="el">Lighting</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, float &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#4b8349c99073588f0ccf6dd2c55a1202" class="el">Transform</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#cf5b86a14d1309ececc1cf2190d848b0" class="el">IsInside</a> (<a href="classVector.md" class="el">Vector</a> p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#1f8f3d611956246ca336e4f45fd01927" class="el">FindBounds</a> (<a href="classVector.md" class="el">Vector</a> &amp;min, <a href="classVector.md" class="el">Vector</a> &amp;max)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#adb115059e28d960fa8badfac5516667" class="el">center</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#fc021d54683383e5078ab9fefc4d53c8" class="el">radius</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#9412f6bc1eb7062c2c85b62daefca994" class="el">radiussqr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#9a098739ebccbb2beb925a1addf63824" class="el">falloffdistance</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#713de4549f65b5aa973d4daad99a0d16" class="el">falloffdistancesqr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#044f4c255ee2b04cee19959f28705d75" class="el">softfalloffdistance</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#480bbfb58eec35a1faf2785276b01fc0" class="el">falloffdistancedelta</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#5dbc98dcc983a70728bd082d1a47546e" class="el">S</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#987bcab01b929eb2c07877b224215c92" class="el">beta</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classRSphere.md#d20caec3b48a1eef164cb4ca81ba2587" class="el">L</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

