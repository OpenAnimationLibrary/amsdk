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

# HColorProperty Class Reference

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HColorProperty:

<span class="image placeholder" original-image-src="classHColorProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HColorProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HColorProperty:

<span class="image placeholder" original-image-src="classHColorProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HColorProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHColorProperty-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#00a162882e174049b3c7ac02c05d9ed7" class="el">GetRed</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#169456be0e4656dfbe07e065311de071" class="el">GetGreen</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHFloatProperty.md" class="el">HFloatProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#06c99b2141cb0db93b393092bb7d96ec" class="el">GetBlue</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#1adeff3d89e145a11e66b2186b132972" class="el">GetLuminance</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">COLORREF </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#2e039378f2c428024241d2407189a3cd" class="el">GetCOLORREF</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#3a716da63246c77ec051591509ae7a01" class="el">GetFactoredRGBFloat</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classColorVector.md" class="el">ColorVector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#1961b900ac804c0c854314bd5ee83a57" class="el">GetFactoredColorVector</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#edabf03f9243223a1b19ec1b8e6d3a7d" class="el">GetNormalizedRGBFloat</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classColorVector.md" class="el">ColorVector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#80c49a1b902376cc5e1475a83b19a9c8" class="el">GetNormalizedColorVector</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#d113c0fe69eaa7d9dc433d40e14f7430" class="el">SetValue</a> (const <a href="classRGBFloat.md" class="el">RGBFloat</a> &amp;value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#25f159b212521a97bce189c0f5d1d3ed" class="el">SetValue</a> (const <a href="classColorVector.md" class="el">ColorVector</a> &amp;value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#df0340bc37c647dcdf819fae1d4a8f13" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classRGBFloat.md" class="el">RGBFloat</a> &amp;value, BOOL storeundo=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#6408c538613f96dcb000367bd0fd12e8" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classColorVector.md" class="el">ColorVector</a> &amp;value, BOOL storeundo=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#53b50b9e3c8ec8d0182f59bec5a833db" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classColorBuf.md" class="el">ColorBuf</a> &amp;value, BOOL storeundo=TRUE)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHColorProperty.md" class="el">HColorProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHColorProperty.md#4ad1b5cffc0d55d63d862ee92424777e" class="el">New</a> (<a href="classHColorPropertyInfo.md" class="el">HColorPropertyInfo</a> *propinfo)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

