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

# Cone Class Reference

`#include <`<a href="influenc_8h-source.md" class="el"><code>influenc.h</code></a>`>`

Inheritance diagram for Cone:

<span class="image placeholder" original-image-src="classCone__inherit__graph.gif" original-image-title="" border="0" usemap="#Cone__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for Cone:

<span class="image placeholder" original-image-src="classCone__coll__graph.gif" original-image-title="" border="0" usemap="#Cone__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classCone-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#79be0724714e1e6d8ac1ba4c7cc34be9" class="el">Cone</a> (float, float, float, float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#f97d7f3970d3dcc1d686cefefb74fd9a" class="el">Init</a> (float, float, float, float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#ebc1dd006469e892a02410cbfdd1d3ec" class="el">Intersect</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, const <a href="classVector.md" class="el">Vector</a> &amp;, ThreadInfo *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#3a8a40efddd68314bac0f4f5cb5d99fb" class="el">Intersect</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, const <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#8a11f22291743884b9331d9cb58e455e" class="el">Normal</a> (<a href="classHit.md" class="el">Hit</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">GetType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#b5bbca2d93358bcb0059f7f9c68ca1ea" class="el">Falloff</a> (<a href="classVector.md" class="el">Vector</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#7882a7921dd3430f5e0a1fa60aa374bd" class="el">Attract</a> (<a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#cf2ea65a3bf1134f7a05638c12a6c1bf" class="el">Vortex</a> (<a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#60d1c5feb2dc82c525ec1f9ef1a734b6" class="el">Friction</a> (<a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a>, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#3a5a7a2826e9d50e9b04343b3e2e5212" class="el">Lighting</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, float &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#863d00ecaa895fef07eee8d995926179" class="el">LightingNoCap</a> (const <a href="classVector.md" class="el">Vector</a> &amp;p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#4b8349c99073588f0ccf6dd2c55a1202" class="el">Transform</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#14f58eced1f257e8631ad9ee9283aa9f" class="el">Transform</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;<a href="classInfluenceShape.md#a5ee57887ab68b45e635e12623ba1432" class="el">screenmatrix</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#0993799c2834e0fd9f64c613e9809f7c" class="el">IsVisible</a> (<a href="classVector.md" class="el">Vector</a>, const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;, float, float, float(*GetVolumetricZ)(int, int))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#cf5b86a14d1309ececc1cf2190d848b0" class="el">IsInside</a> (<a href="classVector.md" class="el">Vector</a> p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#1f8f3d611956246ca336e4f45fd01927" class="el">FindBounds</a> (<a href="classVector.md" class="el">Vector</a> &amp;min, <a href="classVector.md" class="el">Vector</a> &amp;max)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#593616de15330c0fb2d55e55410bf994" class="el">base</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#433169d5d9bcbb6d43f0d288e68f0cad" class="el">axis</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#12eed695da2603129952d6b66cacf68d" class="el">capbase</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#899186f7879ef9f1cf011b415f548c03" class="el">angle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#9676add240beb55103452291bfbc07b7" class="el">halfangle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#1ea9a7041ffad7425f6b8759df72a98c" class="el">tanangle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#576684e928473076151e43f70eaaa987" class="el">tananglesqr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#fc021d54683383e5078ab9fefc4d53c8" class="el">radius</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#5e60f9ac029dca2a61e24022f8093355" class="el">endradius</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#739c635f64a6eca606593bef57a674c6" class="el">deltaangle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#3d791e43c8d5561e36bd09bacc097517" class="el">cap</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#2fa47f7c65fec19cc163b195725e3844" class="el">length</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#a47af4ad1faba99be2b99b4f7c2bf05d" class="el">lengthsqr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#96412bc770c088f9b34dc5b4441b7bef" class="el">costotalangle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#535c96109c40130b2631c56f22d3bff7" class="el">softness</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#4b2c16a98dbeba087f963642c0b3eba6" class="el">cossoftangle</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#9a098739ebccbb2beb925a1addf63824" class="el">falloffdistance</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#480bbfb58eec35a1faf2785276b01fc0" class="el">falloffdistancedelta</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#5dbc98dcc983a70728bd082d1a47546e" class="el">S</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#987bcab01b929eb2c07877b224215c92" class="el">beta</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classCone.md#d20caec3b48a1eef164cb4ca81ba2587" class="el">L</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

