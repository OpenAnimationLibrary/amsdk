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

# IEBone Class Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Collaboration diagram for IEBone:

<span class="image placeholder" original-image-src="classIEBone__coll__graph.gif" original-image-title="" border="0" usemap="#IEBone__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classIEBone-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classIEBone.md#cfa37a1a1c112db25f4ea32820c67834" class="el">IEBone</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIEBone.md" class="el">IEBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEBone.md#58ab29703c7904ab27d31e4be77f8ef3" class="el">m_child</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classIEBone.md" class="el">IEBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEBone.md#c778e699d3ca45676d45aab752d6e386" class="el">m_sibling</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEBone.md#ce8785f7d4587a5968f088b366c90f2d" class="el">m_name</a> [256]</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEBone.md#5f4cd0210d7c06f678c031ac2eac21de" class="el">m_pivotpos</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEBone.md#26eaa8d133516b5a0cd24e52040ce2f3" class="el">m_endpos</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEBone.md#a179ae04caf1b8563690d0660c6f9d6e" class="el">m_rollpos</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; LONG, LONG &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classIEBone.md#be440eac7ffbf627d4de9f203063e7fe" class="el">m_vertexidarray</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="IEModel_8h-source.md#l00250" class="el">250</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="cfa37a1a1c112db25f4ea32820c67834" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">IEBone::IEBone</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="IEModel_8h-source.md#l00261" class="el">261</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00253" class="el">m_child</a>, and <a href="IEModel_8h-source.md#l00253" class="el">m_sibling</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Data Documentation

<span id="58ab29703c7904ab27d31e4be77f8ef3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEBone.md" class="el">IEBone</a>* <a href="classIEBone.md#58ab29703c7904ab27d31e4be77f8ef3" class="el">IEBone::m_child</a></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00253" class="el">253</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00525" class="el">IEModel::DeleteBoneBranch()</a>, and <a href="IEModel_8h-source.md#l00261" class="el">IEBone()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="26eaa8d133516b5a0cd24e52040ce2f3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> <a href="classIEBone.md#26eaa8d133516b5a0cd24e52040ce2f3" class="el">IEBone::m_endpos</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00258" class="el">258</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="ce8785f7d4587a5968f088b366c90f2d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char <a href="classIEBone.md#ce8785f7d4587a5968f088b366c90f2d" class="el">IEBone::m_name</a>[256]</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00254" class="el">254</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="5f4cd0210d7c06f678c031ac2eac21de" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> <a href="classIEBone.md#5f4cd0210d7c06f678c031ac2eac21de" class="el">IEBone::m_pivotpos</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00258" class="el">258</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="a179ae04caf1b8563690d0660c6f9d6e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> <a href="classIEBone.md#a179ae04caf1b8563690d0660c6f9d6e" class="el">IEBone::m_rollpos</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00258" class="el">258</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

<span id="c778e699d3ca45676d45aab752d6e386" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEBone.md" class="el">IEBone</a> * <a href="classIEBone.md#c778e699d3ca45676d45aab752d6e386" class="el">IEBone::m_sibling</a></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00253" class="el">253</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00525" class="el">IEModel::DeleteBoneBranch()</a>, and <a href="IEModel_8h-source.md#l00261" class="el">IEBone()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="be440eac7ffbf627d4de9f203063e7fe" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt;LONG, LONG&gt; <a href="classIEBone.md#be440eac7ffbf627d4de9f203063e7fe" class="el">IEBone::m_vertexidarray</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="IEModel_8h-source.md#l00259" class="el">259</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="IEModel_8h-source.md" class="el">IEModel.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:59 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
