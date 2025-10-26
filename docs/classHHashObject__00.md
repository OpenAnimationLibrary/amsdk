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

# HHashObject Class Reference

Father class for all hierarchical collections of Hash objects. [More...](#_details)

`#include <`<a href="HHashObj_8h-source.md" class="el"><code>HHashObj.h</code></a>`>`

Inheritance diagram for HHashObject:

<span class="image placeholder" original-image-src="classHHashObject__inherit__graph.gif" original-image-title="" border="0" usemap="#HHashObject__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HHashObject:

<span class="image placeholder" original-image-src="classHHashObject__coll__graph.gif" original-image-title="" border="0" usemap="#HHashObject__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHHashObject-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#d85b49d73e45d0431b18e5a61c7e6f3f" class="el">GetName</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#7f64499486374a6a28d8e1f7f70783cc" class="el">SetName</a> (const char *name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">GetObjectType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#10cdf81d35cde6c49e8a699b74aa5482" class="el">IsKindOfBoneCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#3da8b1d86f721bfb3262ab8f42d0b7e9" class="el">GetChild</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#24e19ce2b036b4d67d5b2ec0817ebdc4" class="el">SetChild</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#d6ea8ca9057dc82025912c710057fe09" class="el">GetSibling</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#efd04a26a8bc6bd1afcfd97c10d3083c" class="el">SetSibling</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *sibling)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#5788d8ba32b9eb644c937edf2c937409" class="el">GetSiblingSame</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#7cc7a014d4e2a101c1982a2f1b027cfe" class="el">GetParentOfType</a> (<a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> ot)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#5616a8d6197ea5f43bfb5cbf3f9b8f5e" class="el">GetHeadInstance</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Retrieves the <strong>first</strong> work-object (instance) of an HHashObject. <a href="#5616a8d6197ea5f43bfb5cbf3f9b8f5e"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#e63536d1fd80fc0931ab7aa73d18d8c1" class="el">GetNextInstance</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *instance)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Retrieves the <em>next</em> <a href="classHObject.md" class="el">HObject</a>. <a href="#e63536d1fd80fc0931ab7aa73d18d8c1"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCategoryProperty.md" class="el">HCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#29e1059084f6ff925a74d86aeb9e3754" class="el">GetPluginProperties</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHUserCategoryProperty.md" class="el">HUserCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#9aa03709064628d1993ac2d7194d83cf" class="el">CreateUserCategoryProperty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHUserCategoryProperty.md" class="el">HUserCategoryProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#9dd87d4e3e2d7a3ba397c36320e04627" class="el">GetUserCategoryProperty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#f2d2000e6260ea8ab06a3f02a584bedc" class="el">InsertChildAtTail</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child, BOOL modify=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#47582aa91076a78c11195600c5e7b695" class="el">InsertChildAtHead</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#f35eb4f169883fe9880e3f067175f067" class="el">InsertChildAtTailOfType</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#79d9f3da581d6ce06860fb2929ed2c91" class="el">InsertChildAtHeadOfType</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#a42ade8055e415435caf3aa5b308373b" class="el">InsertChildAfterObject</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child, <a href="classHHashObject.md" class="el">HHashObject</a> *after)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#06f1f72c7b32b64359b27695aa63a301" class="el">InsertChildAlpha</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child, BOOL modify=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#ba2b2332d726c87d6c2c39ac21123a71" class="el">InsertChildOfTypeAlpha</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#20d5f0165a9679a8d9c3c01d38fbadb6" class="el">InsertSibling</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *child)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#d7aa1f6c10b8e3edef464e01f98dabd1" class="el">Unstitch</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#ad8830b8fe793bf6204f8f9837b6e3b7" class="el">UnstitchWithChildren</a> (BOOL markparentmodified=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#a3ac19480844c50f1325365d248712da" class="el">Move</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *parent, <a href="classHHashObject.md" class="el">HHashObject</a> *oldersibling, BOOL select=TRUE, BOOL markparentmodified=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#38b5d23f7de2c1a7071ae9c13d6008c5" class="el">MoveWithChildren</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *parent, <a href="classHHashObject.md" class="el">HHashObject</a> *oldersibling, BOOL select=TRUE, BOOL markparentmodified=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md#51734f01ad2f7170df53482a2c27fbce" class="el">MarkViewsNeedDrawn</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

