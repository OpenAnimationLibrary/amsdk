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

# UDCollection\< TYPE, ARG_TYPE \> Class Template Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Inheritance diagram for UDCollection\< TYPE, ARG_TYPE \>:

<span class="image placeholder" original-image-src="classUDCollection__inherit__graph.gif" original-image-title="" border="0" usemap="#UDCollection_3_01TYPE_00_01ARG__TYPE_01_4__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for UDCollection\< TYPE, ARG_TYPE \>:

<span class="image placeholder" original-image-src="classUDCollection__coll__graph.gif" original-image-title="" border="0" usemap="#UDCollection_3_01TYPE_00_01ARG__TYPE_01_4__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classUDCollection-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#5aa4f474b15a90b1ee5eb3eb59566ad5" class="el">Add</a> (ARG_TYPE newelement, LONG key=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#01b8d5c3874a2ea32bde18a03d888ea6" class="el">AddForce</a> (ARG_TYPE newelement)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#7dcb2c11693639b2788d938ede531da0" class="el">LookUp</a> (ARG_TYPE newelement, LONG key=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE * </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#95a7201fab22e53b513f89e23fbca949" class="el">GetArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#ddc54dfc91e8489e924df466a56ffe1e" class="el">GetAt</a> (int index) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#83feaa64c8e9087b27f2fe9f31eb6b18" class="el">ElementAt</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#f2259ebe9d1c07ceb60119edb0a86416" class="el">GetSize</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#7b8fd25de7858cfef37028cd4d8f52de" class="el">SetSize</a> (int newsize, int growby=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#91e0d6169398953942fe60c3946c79d7" class="el">operator[]</a> (int index) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#710e01c9f42500b31117688d8eaebfac" class="el">operator[]</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#3baf74a81ccd00c867601be0fc5e511c" class="el">SetGranularity</a> (int granularity)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#04de455e490cb138d4e29fc5200447be" class="el">Shrink</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#745f7ddee32c302c3110f18ca7a4b180" class="el">m_array</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-attributes">Private Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; LONG, LONG &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classUDCollection.md#d716da2cf3aef3fd260193ac6f316ae1" class="el">m_keyarray</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

