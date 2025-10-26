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

# HProperty Class Reference

Father class for all property holder classes. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HProperty:

<span class="image placeholder" original-image-src="classHProperty__inherit__graph.gif" original-image-title="" border="0" usemap="#HProperty__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HProperty:

<span class="image placeholder" original-image-src="classHProperty__coll__graph.gif" original-image-title="" border="0" usemap="#HProperty__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHProperty-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#a167263e48531bb247a0dfe151f06374" class="el">GetPropertyInfo</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#aafeb5ae520b32c14d80d1faa2b37f46" class="el">GetHeadDriver</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#e272a91d689ceb51c964a4d8be8b3503" class="el">Show</a> (BOOL bShow=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#cbd61dc08126db414ea7665d12ac6e87" class="el">SetNullable</a> (BOOL isnullable)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#39be410879dc697502dc708221a16544" class="el">IsNullable</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#bbdda942caac43d3abb79c31ec881793" class="el">IsNull</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#7fae027df1e9f03516cac6434a37f2c1" class="el">SetNull</a> (BOOL state=TRUE, <a href="classHAnimObject.md" class="el">HAnimObject</a> *animob=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#b7e486ef33869678bc3671ddfc0da589" class="el">SetIsDynamic</a> (BOOL isdynamic)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#347f1de0b06c6c220a0f05cfb800d4ed" class="el">IsDynamic</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#a8dbb7c29be5adc51f16fbf12d7c9064" class="el">CreateParentForDriver</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#361bdbb10b12db23b670784af8950de4" class="el">GetDriverProperty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#f1514556df549f59e560e1fa611655ec" class="el">AddDriver</a> (<a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#89cffb72b400d2f75659533e612c429b" class="el">Compare</a> (const <a href="classHProperty.md" class="el">HProperty</a> *other, BOOL dochildren=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#aa7830eb0ae25a6605210b5545b2c5be" class="el">IsDefaultValue</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#98afe20a55c27565ee7f70859b43234b" class="el">GetIndex</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#9e0b1cdfd2c81ce9be03bd72369e3fcd" class="el">Copy</a> (const <a href="classHProperty.md" class="el">HProperty</a> *other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyShortcut.md" class="el">HPropertyShortcut</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#ece23aff44071265008947a1a4d11e56" class="el">FindEmptyRelation</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#006335268b1cff30a7b483d3e88bec45" class="el">GetPropertyCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#f05155d66a18c82acfa7d871654a2cb2" class="el">MakeCopy</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#8f7304ffb50104f28d4825809432e60d" class="el">ToString</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#0e9cd12ca2642b6ec64f88bf1848d150" class="el">GetFirstRelationKey</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#94b83658b5d0ebbc9ea3c5e71760973f" class="el">GetNextRelationKey</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#5a776390a6476e5c4a18f470b04b2a73" class="el">GetPrevRelationKey</a> (BOOL *pHasKey)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#0e4ab7cefeb8e99025b6059ce810b503" class="el">GetParentProperty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProperty.md#d441229b35627850670c2a4c538689a6" class="el">IsUserProperty</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

