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

# VertexInfo Class Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Collaboration diagram for VertexInfo:

<span class="image placeholder" original-image-src="classVertexInfo__coll__graph.gif" original-image-title="" border="0" usemap="#VertexInfo__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classVertexInfo-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classVertexInfo.md#89fa2a8f9b65284fc34a3851e23257ac" class="el">RemoveAll</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classHPatch.md" class="el">HPatch</a> *, <a href="classHPatch.md" class="el">HPatch</a> * &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVertexInfo.md#a1ff2be303e179d9f66102b60c0433d6" class="el">m_patcharray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classVector2.md" class="el">Vector2</a>, <a href="classVector2.md" class="el">Vector2</a> &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVertexInfo.md#6ca10a78e4dd988e224fc6230c3f8b81" class="el">m_uvarray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classHCP.md" class="el">HCP</a> *, <a href="classHCP.md" class="el">HCP</a> * &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVertexInfo.md#5e2c20a1b06ee04de2ff5a1d4d5565a9" class="el">m_cparray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classHGroup.md" class="el">HGroup</a> *, <a href="classHGroup.md" class="el">HGroup</a> * &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVertexInfo.md#5cfbd3060812eefed40b5d9b36a98136" class="el">m_grouparray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; char, char &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVertexInfo.md#e07ca002572ac0f5e60b0f078918f562" class="el">m_attachedarray</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="IEModel_8h-source.md#l00794" class="el">794</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="89fa2a8f9b65284fc34a3851e23257ac" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void VertexInfo::RemoveAll</td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00805" class="el">805</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00803" class="el">m_attachedarray</a>, <a href="IEModel_8h-source.md#l00799" class="el">m_cparray</a>, <a href="IEModel_8h-source.md#l00802" class="el">m_grouparray</a>, <a href="IEModel_8h-source.md#l00797" class="el">m_patcharray</a>, <a href="IEModel_8h-source.md#l00798" class="el">m_uvarray</a>, and <a href="HashArra_8h-source.md#l00112" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::RemoveAll()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classVertexInfo_89fa2a8f9b65284fc34a3851e23257ac_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classVertexInfo_89fa2a8f9b65284fc34a3851e23257ac_cgraph_map"></span></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Data Documentation

<span id="e07ca002572ac0f5e60b0f078918f562" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt;char, char&gt; <a href="classVertexInfo.md#e07ca002572ac0f5e60b0f078918f562" class="el">VertexInfo::m_attachedarray</a></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00803" class="el">803</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00805" class="el">RemoveAll()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="5e2c20a1b06ee04de2ff5a1d4d5565a9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt;<a href="classHCP.md" class="el">HCP</a> *, <a href="classHCP.md" class="el">HCP</a> *&gt; <a href="classVertexInfo.md#5e2c20a1b06ee04de2ff5a1d4d5565a9" class="el">VertexInfo::m_cparray</a></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00799" class="el">799</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00805" class="el">RemoveAll()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="5cfbd3060812eefed40b5d9b36a98136" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt;<a href="classHGroup.md" class="el">HGroup</a> *, <a href="classHGroup.md" class="el">HGroup</a> *&gt; <a href="classVertexInfo.md#5cfbd3060812eefed40b5d9b36a98136" class="el">VertexInfo::m_grouparray</a></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00802" class="el">802</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00805" class="el">RemoveAll()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="a1ff2be303e179d9f66102b60c0433d6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt;<a href="classHPatch.md" class="el">HPatch</a> *, <a href="classHPatch.md" class="el">HPatch</a> *&gt; <a href="classVertexInfo.md#a1ff2be303e179d9f66102b60c0433d6" class="el">VertexInfo::m_patcharray</a></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00797" class="el">797</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00805" class="el">RemoveAll()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="6ca10a78e4dd988e224fc6230c3f8b81" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt;<a href="classVector2.md" class="el">Vector2</a>, <a href="classVector2.md" class="el">Vector2</a>&gt; <a href="classVertexInfo.md#6ca10a78e4dd988e224fc6230c3f8b81" class="el">VertexInfo::m_uvarray</a></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00798" class="el">798</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00805" class="el">RemoveAll()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="IEModel_8h-source.md" class="el">IEModel.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:06 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
