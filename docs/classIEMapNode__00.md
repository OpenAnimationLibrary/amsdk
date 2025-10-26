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

# IEMapNode Class Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Inheritance diagram for IEMapNode:

<span class="image placeholder" original-image-src="classIEMapNode__inherit__graph.gif" original-image-title="" border="0" usemap="#IEMapNode__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for IEMapNode:

<span class="image placeholder" original-image-src="classIEMapNode__coll__graph.gif" original-image-title="" border="0" usemap="#IEMapNode__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classIEMapNode-members.md)

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
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef58e39218e7d46cf6d3688c77b54fe0ed" class="el">COLORMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef30058bb40a02f493eb7226490b5c9033" class="el">TRANSPARENCYMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef8596d9ab1eb8701a578ab2a802d1c659" class="el">BUMPMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516efbf1640edd4c8833729c1f91ed4c2cd07" class="el">SPECULARSIZEMAP</a>,<br />
  <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef07923aa3cbb7e35db841f0bd0f5ff1b4" class="el">DIFFUSEMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef31cc53854474781115e4154d5d9528a0" class="el">MIRRORMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef8b4267ddf1bbe44640df2b1b22172349" class="el">AMBIANCEMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516efde0be64020a00dcc980192c37345b76c" class="el">COOKIECUTMAP</a>,<br />
  <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516efd1812210c91a2902a6db9a4b327b700a" class="el">DISPLACEMENTMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef5489fa96a5731b139dad6aadb2f27944" class="el">FRACTALMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef9cb41a98439a1d606679d74325596ad7" class="el">SPECULARINTENSITYMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef0deaa599f106e237adc71e6efab50b47" class="el">NEXTMAPFACTORMAP</a>,<br />
  <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef486cca3be8c4485744b882670d0191e1" class="el">OTHERMAP</a>, <a href="classIEMapNode.md#dca29a1140aadadfd92b34a02fa516ef3bc7c53890f15cfc66994f0ac00de9b9" class="el">NORMALMAP</a><br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#9f60677f2a266e79213a2297ac81af61" class="el">IEMapNode</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIEMapNode.md" class="el">IEMapNode</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#fcea5ca5ad5ee9c8f63a336608f75e53" class="el">operator=</a> (const <a href="classIEMapNode.md" class="el">IEMapNode</a> &amp;other)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#3b2aff5cd1a2382d7dedd0af9426b63e" class="el">m_mapid</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#8b668b2f236f418c7e424146d0ad56dd" class="el">m_percent</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector2.md" class="el">Vector2</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#8e50036d0fe95814c984f6264db744ab" class="el">m_repeat</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector2.md" class="el">Vector2</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#9bce89748d9dcd1d3878f6f32af47be3" class="el">m_uv</a> [4]</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#de812cb8066aad908294b43ef4b363df" class="el">m_flags</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#66d68980660a982fc401607c239f54e2" class="el">m_kind</a>: 4</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#ce14c53704fd003d5011642d042497e9" class="el">m_isseamless</a>: 1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEMapNode.md#044fbf2fad7f5c3591e88ee0e53a16d0" class="el">m_isgroupdecal</a>: 1</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

