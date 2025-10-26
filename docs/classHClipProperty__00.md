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

# HClipProperty Class Reference

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HClipProperty:

<span class="image placeholder" original-image-src="classHClipProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HClipProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HClipProperty:

<span class="image placeholder" original-image-src="classHClipProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HClipProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHClipProperty-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHClip.md" class="el">HClip</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#4099b93fbb1994b7ba7326f91b04bc5b" class="el">GetClip</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHVector2Property.md" class="el">HVector2Property</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#ed5a8933e7f4f6c7e901c44a3360cc4d" class="el">GetRepeat</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTimeProperty.md" class="el">HTimeProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#e9dda391e2c3dedde6558ffcc4071026" class="el">GetTime</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#c19cf16b49f0e987676aca0596b9a36b" class="el">GetIsSeamless</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#ce2848c68165384ff92043fdf7f975ff" class="el">GetWidth</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#35170f8abe223996b6ba9a0ee517f031" class="el">GetHeight</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#ca1082dbcc5c8b901a20217ec807126a" class="el">ReadBitmap</a> (float x, float y, <a href="classRGBFloat.md" class="el">RGBFloat</a> *diffuse, float *opacity, float pixelwidth)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#77ac82e852b4b80d35a721f165a09810" class="el">ReadBitmap</a> (float x, float y, <a href="classColorVector.md" class="el">ColorVector</a> *diffuse, float *opacity, float pixelwidth)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#ad204355a7fa5e0532f764267dc09c67" class="el">ReadBumpmap</a> (float x, float y, <a href="classVector2.md" class="el">Vector2</a> &amp;delta, float pixelwidth)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#f04471868625f80e54f18fc3709af2ce" class="el">LoadImage</a> (const <a href="classString.md" class="el">String</a> &amp;filename)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHClipProperty.md" class="el">HClipProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHClipProperty.md" class="el">HClipProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHClipProperty.md#1729ddaa8ad04ecce9458dbcadca27a4" class="el">New</a> (<a href="classHClipPropertyInfo.md" class="el">HClipPropertyInfo</a> *propinfo)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

