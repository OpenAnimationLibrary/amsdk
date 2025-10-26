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

# TypeInfoArray Class Reference

Holds the list of choices that appears in a drop-down list. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Collaboration diagram for TypeInfoArray:

<span class="image placeholder" original-image-src="classTypeInfoArray__coll__graph.gif" original-image-title="" border="0" usemap="#TypeInfoArray__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classTypeInfoArray-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#7a74c129e234166445351403652c0127" class="el">TypeInfoArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#ff52c81ba6093a82d4a1d52ad9f36573" class="el">~TypeInfoArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#2d0da56af9511708a056c1eeff45ab79" class="el">SetArraySize</a> (int count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#549d5af52e1cbb850bc5c8a6a7ca2b23" class="el">DeleteArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeInfo.md" class="el">HTypeInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#710e01c9f42500b31117688d8eaebfac" class="el">operator[]</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeInfo.md" class="el">HTypeInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#862eedba6863c45675862fa7b08bd228" class="el">GetTypeInfoArrayData</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#8d99671fb9af5f4eb292b2c60d3d7618" class="el">GetCount</a> () const</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-member-functions">Private Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#4113b099cf16bf45bcec295da6d060e6" class="el">AllocArray</a> (<a href="classHTypeInfo.md" class="el">HTypeInfo</a> **array, int count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#33f09f1b320643fde48e2714a201d7f1" class="el">DeleteArray</a> (<a href="classHTypeInfo.md" class="el">HTypeInfo</a> *array)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeInfo.md" class="el">HTypeInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#9ab6fb60dd59b31cc7d2be8446343fa2" class="el">ElementAt</a> (<a href="classHTypeInfo.md" class="el">HTypeInfo</a> *array, int index)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-attributes">Private Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTypeInfo.md" class="el">HTypeInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#bc82f1f8924433ecc381fdb77fb1b2a4" class="el">m_typeinfoarray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTypeInfoArray.md#3eb8303a090aa0a072e815d64a0f1cbc" class="el">m_count</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

