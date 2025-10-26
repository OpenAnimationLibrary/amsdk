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

# IEPoly Class Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Collaboration diagram for IEPoly:

<span class="image placeholder" original-image-src="classIEPoly__coll__graph.gif" original-image-title="" border="0" usemap="#IEPoly__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classIEPoly-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#8648a43e1f6d2aad77fc60f3f75d1bae" class="el">IEPoly</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#e5c58507d0ab47d1d8ac126feffbfcdf" class="el">IEPoly</a> (<a href="classHPatch.md" class="el">HPatch</a> *patch)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#3ae2ac2b9b8974f84922bcb3130352f6" class="el">~IEPoly</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#99712cfce3529b5479ca47ea92742879" class="el">Init</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIEPoly.md" class="el">IEPoly</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#4918c5ca38f12bbdd431b627690e6630" class="el">operator=</a> (const <a href="classIEPoly.md" class="el">IEPoly</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#01ede8b4a54e94c697652f6ebdb53944" class="el">SetVerts</a> (int <a href="structTQAVGouraud.md" class="el">v0</a>, int <a href="Rave_8h.md#6654c734ccab8f440ff0825eb443dc7f" class="el">v1</a>, int <a href="Rave_8h.md#1b267619c4812cc46ee281747884ca50" class="el">v2</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#c2251fc22ff57ef1f8661836a4856678" class="el">SetVerts</a> (int <a href="structTQAVGouraud.md" class="el">v0</a>, int <a href="Rave_8h.md#6654c734ccab8f440ff0825eb443dc7f" class="el">v1</a>, int <a href="Rave_8h.md#1b267619c4812cc46ee281747884ca50" class="el">v2</a>, int v3)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#b163078c3e3d54ef43cd485705578527" class="el">IsTri</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#e9a8ddbd1be04e5aaff0fa2ae74fed26" class="el">IsQuad</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classIEMapNode.md" class="el">IEMapNode</a> *, <a href="classIEMapNode.md" class="el">IEMapNode</a> * &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#facc693853ee22aa40695ff21efecbdd" class="el">m_mapnodearray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#ab848e4cb26a8aeced0d766bc9c2d811" class="el">m_attrid</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#ec21a530074d93e6d3c5883b04543a87" class="el">m_vertexid</a> [4]</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#6b5ed913dc8f1aaa7311421ebabc6cb1" class="el">m_normalid</a> [4]</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPatch.md" class="el">HPatch</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPoly.md#0af5376991509a658ac7143de365c068" class="el">m_origpatch</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

