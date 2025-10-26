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

# IETriModel Class Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Inheritance diagram for IETriModel:

<span class="image placeholder" original-image-src="classIETriModel__inherit__graph.gif" original-image-title="" border="0" usemap="#IETriModel__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for IETriModel:

<span class="image placeholder" original-image-src="classIETriModel__coll__graph.gif" original-image-title="" border="0" usemap="#IETriModel__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classIETriModel-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#283100fb28cb1148657de22f24527fc9" class="el">IETriModel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#ef8ab89b66164ca474734b0670ffadd7" class="el">IETriModel</a> (const <a href="classIETriModel.md" class="el">IETriModel</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIETriModel.md" class="el">IETriModel</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#1b37ef5bfa79111f0a11a18590a63272" class="el">operator=</a> (const <a href="classIETriModel.md" class="el">IETriModel</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#448ffa19e00f106a108b0eaf52603042" class="el">~IETriModel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#f14b970389c12e1f2042f114847ebef7" class="el">FreeData</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#99712cfce3529b5479ca47ea92742879" class="el">Init</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#b2f66e2517de65e5240659db78c4c1ed" class="el">SetNumEdges</a> (int i)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#2da5a51849163e7398430b64f7830261" class="el">GetNumEdges</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#20baa2fc60c7f945bbd199e103a37a4e" class="el">SetNumFaces</a> (int numfaces)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#053ca74957dc32b73fac28c350ef6839" class="el">BuildEdges</a> (BOOL deleteold=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#705795b9fe03879d3839acebe21a7ede" class="el">setNumEdges</a> (int numEdges)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classIEPoly.md" class="el">IEPoly</a>, <a href="classIEPoly.md" class="el">IEPoly</a> &amp; &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#fb2d2d0cc63b0854a8d03ff937825247" class="el">m_polyclassarray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classIEEdge.md" class="el">IEEdge</a>, <a href="classIEEdge.md" class="el">IEEdge</a> &amp; &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#cdec876bacc1b1c330e928f27d996d7d" class="el">m_edges</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int * </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#1ed29043fe32641bf0c908e810310d31" class="el">m_edgeindex</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="friends">Friends</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#1473746026c949ae65482d16db247c6d" class="el">Triangulate</a> (const <a href="classIEPolyModel.md" class="el">IEPolyModel</a> &amp;mesh, <a href="classIETriModel.md" class="el">IETriModel</a> &amp;tmesh)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#2fb0d0e93b346781ea0d600f661da8dc" class="el">LoopSubdivideStep</a> (const <a href="classIETriModel.md" class="el">IETriModel</a> &amp;mesh, <a href="classIETriModel.md" class="el">IETriModel</a> &amp;smesh)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIETriModel.md#0214c42193d7cd2ab9c021060c79ed73" class="el">LoopSubdivide</a> (<a href="classIETriModel.md" class="el">IETriModel</a> &amp;mesh, <a href="classIETriModel.md" class="el">IETriModel</a> &amp;smesh, int numSteps)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

