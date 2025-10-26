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

# IEModel Class Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Inheritance diagram for IEModel:

<span class="image placeholder" original-image-src="classIEModel__inherit__graph.gif" original-image-title="" border="0" usemap="#IEModel__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for IEModel:

<span class="image placeholder" original-image-src="classIEModel__coll__graph.gif" original-image-title="" border="0" usemap="#IEModel__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classIEModel-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#1704f215522a4e3eb2f01e42bf22dcda" class="el">IEModel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#c76c70b158459549429cbbb61792047b" class="el">~IEModel</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#0904cdb2842af35fade19da70cac2691" class="el">DeleteBoneBranch</a> (<a href="classIEBone.md" class="el">IEBone</a> *bone)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#cbf64e2e811fed07c5ca8bbc87cb766e" class="el">Draw</a> (RenderInfo *renderinfo)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#d06dfcee00fec3f8a6ca17f92b12f6ed" class="el">GetVertexArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#79cec0ce7382dd48154a0130151dc1cf" class="el">GetVertex</a> (int i)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVectorCollection.md" class="el">VectorCollection</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#0835fcbd3ca674be1eb3a38eb81968ef" class="el">m_vertexlist</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classUDCollection.md" class="el">UDCollection</a>&lt; <a href="classIEMap.md" class="el">IEMap</a>, <a href="classIEMap.md" class="el">IEMap</a> &amp; &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#2c29d9d6852876ce79b41be5f204c533" class="el">m_maplist</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classUDCollection.md" class="el">UDCollection</a>&lt; <a href="classAttr.md" class="el">Attr</a>, <a href="classAttr.md" class="el">Attr</a> &amp; &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#eec3d7883aed266556a1ea8f88dc4a69" class="el">m_attrlist</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIEBone.md" class="el">IEBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEModel.md#e40d843b55fcb8c7e2803a15e87622cc" class="el">m_bonehead</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="IEModel_8h-source.md#l00501" class="el">501</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="1704f215522a4e3eb2f01e42bf22dcda" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">IEModel::IEModel</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00510" class="el">510</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="c76c70b158459549429cbbb61792047b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual IEModel::~IEModel</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00516" class="el">516</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

------------------------------------------------------------------------

## Member Function Documentation

<span id="0904cdb2842af35fade19da70cac2691" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void IEModel::DeleteBoneBranch</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEBone.md" class="el">IEBone</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>bone</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="IEModel_8h-source.md#l00525" class="el">525</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00253" class="el">IEBone::m_child</a>, and <a href="IEModel_8h-source.md#l00253" class="el">IEBone::m_sibling</a>.</p></td>
</tr>
</tbody>
</table>

<span id="cbf64e2e811fed07c5ca8bbc87cb766e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void IEModel::Draw</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">RenderInfo * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>renderinfo</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="79cec0ce7382dd48154a0130151dc1cf" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a>&amp; IEModel::GetVertex</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>i</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00522" class="el">522</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="d06dfcee00fec3f8a6ca17f92b12f6ed" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a>* IEModel::GetVertexArray</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00521" class="el">521</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

------------------------------------------------------------------------

## Member Data Documentation

<span id="eec3d7883aed266556a1ea8f88dc4a69" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classUDCollection.md" class="el">UDCollection</a>&lt;<a href="classAttr.md" class="el">Attr</a>, <a href="classAttr.md" class="el">Attr</a> &amp;&gt; <a href="classIEModel.md#eec3d7883aed266556a1ea8f88dc4a69" class="el">IEModel::m_attrlist</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00506" class="el">506</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="e40d843b55fcb8c7e2803a15e87622cc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEBone.md" class="el">IEBone</a>* <a href="classIEModel.md#e40d843b55fcb8c7e2803a15e87622cc" class="el">IEModel::m_bonehead</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00508" class="el">508</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="2c29d9d6852876ce79b41be5f204c533" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classUDCollection.md" class="el">UDCollection</a>&lt;<a href="classIEMap.md" class="el">IEMap</a>, <a href="classIEMap.md" class="el">IEMap</a> &amp;&gt; <a href="classIEModel.md#2c29d9d6852876ce79b41be5f204c533" class="el">IEModel::m_maplist</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00505" class="el">505</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="0835fcbd3ca674be1eb3a38eb81968ef" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVectorCollection.md" class="el">VectorCollection</a> <a href="classIEModel.md#0835fcbd3ca674be1eb3a38eb81968ef" class="el">IEModel::m_vertexlist</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="IEModel_8h-source.md#l00504" class="el">504</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00595" class="el">IEPolyModel::GetNumVerts()</a>, <a href="IEModel_8h-source.md#l00655" class="el">IETriModel::operator=()</a>, <a href="IEModel_8h-source.md#l00569" class="el">IEPolyModel::operator=()</a>, and <a href="IEModel_8h-source.md#l00599" class="el">IEPolyModel::SetNumVerts()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="IEModel_8h-source.md" class="el">IEModel.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:59 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
