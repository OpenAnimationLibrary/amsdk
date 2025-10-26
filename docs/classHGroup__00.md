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

# HGroup Class Reference

A HGroup is the group itself, rather than the group elements. [More...](#_details)

`#include <`<a href="HCP_8h-source.md" class="el"><code>HCP.h</code></a>`>`

Inheritance diagram for HGroup:

<span class="image placeholder" original-image-src="classHGroup__inherit__graph.gif" original-image-title="" border="0" usemap="#HGroup__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HGroup:

<span class="image placeholder" original-image-src="classHGroup__coll__graph.gif" original-image-title="" border="0" usemap="#HGroup__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHGroup-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAttrProperty.md" class="el">HAttrProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#b092f4dc2c9bdb7c92b4d4b1c90e2c37" class="el">GetAttr</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHGroupCP.md" class="el">HGroupCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#543cdcb8eb32d17eee3ea3942412c7cb" class="el">GetGroupCP</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Returns a pointer to the first <a href="classHGroupCP.md" class="el">HGroupCP</a> in this group. <a href="#543cdcb8eb32d17eee3ea3942412c7cb"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#9d27380717631a4457c44ea0f3091f55" class="el">GetMatrix</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Returns a pointer to the matrix associated with this group. <a href="#9d27380717631a4457c44ea0f3091f55"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#dc5d58b76c30199920587d2ca7d2ea6c" class="el">IsTempGroup</a> ()</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Returns TRUE if the group is a temporary group. <a href="#dc5d58b76c30199920587d2ca7d2ea6c"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#842b825fc9bf8694e13afbd925d926b8" class="el">SetTempGroup</a> (BOOL istemp)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Sets the temporary status of the group. <a href="#842b825fc9bf8694e13afbd925d926b8"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#4ff589b5c7c35db8f45b4e72cac94ed7" class="el">AddCP</a> (<a href="classHCP.md" class="el">HCP</a> *cp)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Adds a control point to the group. <a href="#4ff589b5c7c35db8f45b4e72cac94ed7"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#54fee57af796519305b78404dc09aa51" class="el">RemoveCP</a> (<a href="classHCP.md" class="el">HCP</a> *cp)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Removes the CP from he group. <a href="#54fee57af796519305b78404dc09aa51"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDecalClipContainer.md" class="el">HDecalClipContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#c0573b3e1e96aa5e6275d0da484f86bf" class="el">GetChildDecalClipContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#4bbc506b77cafc9ff7749d931319076a" class="el">IsPatchInGroup</a> (<a href="classHPatch.md" class="el">HPatch</a> *patch)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#84a81eb52575b3658bb96eaae21efb90" class="el">IsCPInGroup</a> (<a href="classHCP.md" class="el">HCP</a> *hcp)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Returns TRUE if the CP is a member of the group. <a href="#84a81eb52575b3658bb96eaae21efb90"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDecalClip.md" class="el">HDecalClip</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#316d21565321bd88ec9884dd0e6f7c6f" class="el">CreateGroupDecal</a> (<a href="classHClip.md" class="el">HClip</a> *clipcache=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#c914749c38847431ffc67569a560560c" class="el">RotateGroupImages</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPolyModifierShortcut.md" class="el">HPolyModifierShortcut</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHGroup.md#09046f194bf799572d19efa6607b53c4" class="el">GetPolyModifierHead</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

