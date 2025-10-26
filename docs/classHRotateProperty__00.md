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

# HRotateProperty Class Reference

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HRotateProperty:

<span class="image placeholder" original-image-src="classHRotateProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HRotateProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HRotateProperty:

<span class="image placeholder" original-image-src="classHRotateProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HRotateProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHRotateProperty-members.md)

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
&#10;<h2 id="public-types">Public Types</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a" class="el">InterpolationMethod</a> { <a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a9c54d1d76e1aadde4815d0cd8a683515" class="el">VECTORINTERP</a>, <a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a205df167d42c18af3055fe82607a7db3" class="el">EULERINTERP</a>, <a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a5b951ef080681121e56f3e3e70c8fa3e" class="el">QUATINTERP</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a" class="el">InterpolationMethod</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#047198333222b0ff74eae96bb59f4750" class="el">GetDefaultObjectInterpolationMethod</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#11078a4e531c09b807d32d8b6d1f73c3" class="el">SetDefaultObjectInterpolationMethod</a> (<a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a" class="el">InterpolationMethod</a> method)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a" class="el">InterpolationMethod</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#be9de08bf5b00769d59d68c3b473dfe3" class="el">GetDefaultBoneInterpolationMethod</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#74de5d755c68d7e2743a075e3c2317be" class="el">SetDefaultBoneInterpolationMethod</a> (<a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a" class="el">InterpolationMethod</a> method)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a" class="el">InterpolationMethod</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#5ee4180aa44e1bff730283e0a0f3d176" class="el">GetDefaultRootBoneInterpolationMethod</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#423bee6accf7145bfa64034087962a4e" class="el">SetDefaultRootBoneInterpolationMethod</a> (<a href="classHRotateProperty.md#0b60c47f6ea3ec8602efa327d93c315a" class="el">InterpolationMethod</a> method)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#327efd5d9ea06c9066f84f20ca5ae0fe" class="el">GetValue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#6e0d7bac16384f7ce07565211ecb103c" class="el">GetValue</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#cae07810914465aec837372d5cc1ed80" class="el">SetValue</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#8c6588605516bedfc64f5d4f193bd402" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;value, BOOL storeroll=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#73f3b8f78f77062bc74e2cc89eaa9949" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;value, BOOL storeroll, BOOL storeundo)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHRotateProperty.md" class="el">HRotateProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#3d9cbd41ce5e98d53ee169d9547259d7" class="el">New</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHRotateProperty.md" class="el">HRotateProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateProperty.md#b356e73a15945fe03597a00205d57b00" class="el">New</a> (<a href="classHRotatePropertyInfo.md" class="el">HRotatePropertyInfo</a> *propinfo)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

