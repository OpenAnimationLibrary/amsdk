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

# IEPolyModel Class Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Inheritance diagram for IEPolyModel:

<span class="image placeholder" original-image-src="classIEPolyModel__inherit__graph.gif" original-image-title="" border="0" usemap="#IEPolyModel__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for IEPolyModel:

<span class="image placeholder" original-image-src="classIEPolyModel__coll__graph.gif" original-image-title="" border="0" usemap="#IEPolyModel__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classIEPolyModel-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#e8ec72b6dfafcebfb4ae0f39519cc6de" class="el">IEPolyModel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#6c618a2d7941968b36a72acaae63fb1f" class="el">IEPolyModel</a> (const <a href="classIEPolyModel.md" class="el">IEPolyModel</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIEPolyModel.md" class="el">IEPolyModel</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#c2a37a14999a70041c97a5689b202208" class="el">operator=</a> (const <a href="classIEPolyModel.md" class="el">IEPolyModel</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#54caf5f28ae0df11f0711130c4ff8c81" class="el">~IEPolyModel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#f14b970389c12e1f2042f114847ebef7" class="el">FreeData</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#5dd8e91227244156e3d515ea17c49639" class="el">BuildNormalList</a> (float angletolerance)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#3e09e4e37d71bb7f9642f9cdf3993857" class="el">BuildNormalList</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#648dbe0ff154458a3037d4f1a490084a" class="el">GetNumVerts</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#ab7bd8026c6d5497b2be10a33fb80e09" class="el">SetNumVerts</a> (int i)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#f3d701e65827c2aa0ae4ab983c8d61a1" class="el">GetNumFaces</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#20baa2fc60c7f945bbd199e103a37a4e" class="el">SetNumFaces</a> (int numfaces)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#575a4986a38164da357d9ec46208822f" class="el">GetNumNormals</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#14411380fc34eb4334dfe70aeb794911" class="el">SetNumNormals</a> (int i)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#472e44e189abbc79deb52a9ccf01d4b4" class="el">getNumVerts</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#92a34c22492ff079fed6e5f2183c5093" class="el">getNumFaces</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#fc47a538eb2a94e3fde8b62d6f012a35" class="el">getFaceVertex</a> (int face, int <a href="structTQAVGouraud.md" class="el">v</a>)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classIEPoly.md" class="el">IEPoly</a> *, <a href="classIEPoly.md" class="el">IEPoly</a> * &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#5de202adeb76fa5900f08f14d016a10a" class="el">m_polyarray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVectorCollection.md" class="el">VectorCollection</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEPolyModel.md#e82420e6aaa828723462f1b512e02ce0" class="el">m_normallist</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

