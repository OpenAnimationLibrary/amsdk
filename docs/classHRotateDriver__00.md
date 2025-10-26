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

# HRotateDriver Class Reference

`#include <`<a href="HPropDri_8h-source.md" class="el"><code>HPropDri.h</code></a>`>`

Inheritance diagram for HRotateDriver:

<span class="image placeholder" original-image-src="classHRotateDriver__inherit__graph.gif" original-image-title="" border="0" usemap="#HRotateDriver__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HRotateDriver:

<span class="image placeholder" original-image-src="classHRotateDriver__coll__graph.gif" original-image-title="" border="0" usemap="#HRotateDriver__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHRotateDriver-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#82e41526af32455b282b19d4b558c2de" class="el">ComputeBoneDirections</a> (<a href="classVector.md" class="el">Vector</a> &amp;bonedir, <a href="classVector.md" class="el">Vector</a> &amp;rolldir, <a href="classVector.md" class="el">Vector</a> &amp;parentbonedir, <a href="classVector.md" class="el">Vector</a> &amp;parentrolldir) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#8e3e53cce6a2bef2bc31e8da9fb0b900" class="el">ComputeBoneToParent</a> (const <a href="classVector.md" class="el">Vector</a> &amp;bonedir, const <a href="classVector.md" class="el">Vector</a> &amp;rolldir, const <a href="classVector.md" class="el">Vector</a> &amp;parentbonedir, const <a href="classVector.md" class="el">Vector</a> &amp;parentrolldir)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#6047863b29b2a19bb9baf95571988669" class="el">GetBoneToParent</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#0f3e58785e4f3aa40169071a5715d21f" class="el">SetBoneToParent</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;quat)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#c5fb51d7487d07f0bcbe41578dd2989e" class="el">GetParentToBone</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#a499fa7b57ff4669e8a2c66623410d8e" class="el">SetParentToBone</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;quat)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#f4d0f117515fbf3c6fc9a0b14e80d738" class="el">GetValue</a> (<a href="classTime.md" class="el">Time</a> time, <a href="classTimeRange.md" class="el">TimeRange</a> &amp;validrange)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#6e0d7bac16384f7ce07565211ecb103c" class="el">GetValue</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHRotateDriver.md#7850d2d5e9d4d0c39b15e83940a048d1" class="el">StoreValue</a> (<a href="classTime.md" class="el">Time</a> time, <a href="classQuaternion.md" class="el">Quaternion</a> &amp;quat, BOOL storeundo=TRUE)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

