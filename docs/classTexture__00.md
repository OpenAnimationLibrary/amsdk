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

# Texture Class Reference

Base class for all textures. [More...](#_details)

`#include <`<a href="Texture_8h-source.md" class="el"><code>Texture.h</code></a>`>`

Inheritance diagram for Texture:

<span class="image placeholder" original-image-src="classTexture__inherit__graph.gif" original-image-title="" border="0" usemap="#Texture__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for Texture:

<span class="image placeholder" original-image-src="classTexture__coll__graph.gif" original-image-title="" border="0" usemap="#Texture__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classTexture-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#32cd4cb5ed204a076cb7f3e52ba32efc" class="el">Texture</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#90700509771ec23b2138028847f67691" class="el">Texture</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *htreeobject)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#d184cb8013a0047c62951e5889b14cac" class="el">Evaluate</a> (const <a href="classVector.md" class="el">Vector</a> &amp;evalp, <a href="classHTexInfo.md" class="el">HTexInfo</a> *texinfo)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#f20fde302c72ec98fec2db094ae975e1" class="el">EvaluateTransparency</a> (const <a href="classVector.md" class="el">Vector</a> &amp;evalp, <a href="classHTexInfo.md" class="el">HTexInfo</a> *texinfo)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual <a href="classHObjectListNode.md" class="el">HObjectListNode</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#8ed0074dba65c5d4cb56434b6f63f890" class="el">GetPointerList</a> (HPointerPropertyBase *prop)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#955a21a0f29558a7d9cee38902b4182d" class="el">CheckOut</a> (<a href="classHHashObject.md" class="el">HHashObject</a> *cache)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#0d1cbd915a53fe344d1e8e6995431dab" class="el">OnNotifyNewProperty</a> (<a href="classHProperty.md" class="el">HProperty</a> *prop, const <a href="classString.md" class="el">String</a> &amp;matchname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHModel.md" class="el">HModel</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#e46fe26b37492b1d67d204ff30c6d1cf" class="el">GetModel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHGroup.md" class="el">HGroup</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classTexture.md#de8f964adca8147ca8c157c34aea6f7e" class="el">GetGroup</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

