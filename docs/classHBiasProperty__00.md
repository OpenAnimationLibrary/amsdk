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

# HBiasProperty Class Reference

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HBiasProperty:

<span class="image placeholder" original-image-src="classHBiasProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HBiasProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HBiasProperty:

<span class="image placeholder" original-image-src="classHBiasProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HBiasProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHBiasProperty-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#1cebcc853c64378c396fde5f987094ce" class="el">GetAlpha</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#afcb03ef1c1eb4a4681aed36e60d82ee" class="el">GetGamma</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#5715efd38fabd06ca6180ac5f2090aa6" class="el">GetMagnitude</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#803f846d761b615430a35a07a4710601" class="el">SetAlpha</a> (float num)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#7042759c986c1e73513913b03db1bd4a" class="el">SetGamma</a> (float num)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#405ecad4f6241d645e9cc1526a83deaa" class="el">SetMagnitude</a> (float num)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#36beff620f42675c1bda7e9b868b74e4" class="el">GetValue</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#6e0d7bac16384f7ce07565211ecb103c" class="el">GetValue</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#cb3eaab0e8657c040d8709c85b0441fa" class="el">GetFactoredValue</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#211cab0010b115e42c5829678a67dfed" class="el">SetFactoredValue</a> (const <a href="classVector.md" class="el">Vector</a> &amp;value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#aeb9fbd1267e4a3a406426fb5d62186c" class="el">SetValue</a> (const <a href="classVector.md" class="el">Vector</a> &amp;value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#bd90692a54c366f51a5a0208b704538a" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classVector.md" class="el">Vector</a> &amp;value, BOOL storeundo=TRUE)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHBiasProperty.md" class="el">HBiasProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHBiasProperty.md" class="el">HBiasProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHBiasProperty.md#07a99bcc031eba110a5807c370f1c851" class="el">New</a> (<a href="classHBiasPropertyInfo.md" class="el">HBiasPropertyInfo</a> *propinfo)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

