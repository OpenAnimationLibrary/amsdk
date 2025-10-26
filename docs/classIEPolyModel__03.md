## Member Function Documentation

<span id="3e09e4e37d71bb7f9642f9cdf3993857" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT void IEPolyModel::BuildNormalList</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Referenced by <a href="IEModel_8h-source.md#l00587" class="el">FreeData()</a>. |

<span id="5dd8e91227244156e3d515ea17c49639" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT void IEPolyModel::BuildNormalList</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>angletolerance</em></td>
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

<span id="f14b970389c12e1f2042f114847ebef7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void IEPolyModel::FreeData</td>
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
<td><p>Reimplemented in <a href="classIETriModel.md#f14b970389c12e1f2042f114847ebef7" class="el">IETriModel</a>.</p>
<p>Definition at line <a href="IEModel_8h-source.md#l00587" class="el">587</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="classIEPolyModel.md#3e09e4e37d71bb7f9642f9cdf3993857" class="el">BuildNormalList()</a>, <a href="HashArra_8h-source.md#l00106" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::GetSize()</a>, <a href="IEModel_8h-source.md#l00558" class="el">m_polyarray</a>, and <a href="Exports_8h-source.md#l00044" class="el">PLUGINEXPORT</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00583" class="el">~IEPolyModel()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classIEPolyModel_f14b970389c12e1f2042f114847ebef7_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classIEPolyModel_f14b970389c12e1f2042f114847ebef7_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="fc47a538eb2a94e3fde8b62d6f012a35" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int IEPolyModel::getFaceVertex</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname" data-nowrap=""><em>face</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>v</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00625" class="el">625</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00558" class="el">m_polyarray</a>.</p></td>
</tr>
</tbody>
</table>

<span id="92a34c22492ff079fed6e5f2183c5093" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int IEPolyModel::getNumFaces</td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00624" class="el">624</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00603" class="el">GetNumFaces()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classIEPolyModel_92a34c22492ff079fed6e5f2183c5093_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classIEPolyModel_92a34c22492ff079fed6e5f2183c5093_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="f3d701e65827c2aa0ae4ab983c8d61a1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int IEPolyModel::GetNumFaces</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const<code> [inline]</code></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00603" class="el">603</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="HashArra_8h-source.md#l00106" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::GetSize()</a>, and <a href="IEModel_8h-source.md#l00558" class="el">m_polyarray</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00624" class="el">getNumFaces()</a>, <a href="IEModel_8h-source.md#l00655" class="el">IETriModel::operator=()</a>, and <a href="IEModel_8h-source.md#l00569" class="el">operator=()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classIEPolyModel_f3d701e65827c2aa0ae4ab983c8d61a1_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classIEPolyModel_f3d701e65827c2aa0ae4ab983c8d61a1_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="575a4986a38164da357d9ec46208822f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int IEPolyModel::GetNumNormals</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const<code> [inline]</code></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00613" class="el">613</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00290" class="el">VectorCollection::GetSize()</a>, and <a href="IEModel_8h-source.md#l00559" class="el">m_normallist</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classIEPolyModel_575a4986a38164da357d9ec46208822f_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classIEPolyModel_575a4986a38164da357d9ec46208822f_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="472e44e189abbc79deb52a9ccf01d4b4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int IEPolyModel::getNumVerts</td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00623" class="el">623</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00595" class="el">GetNumVerts()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classIEPolyModel_472e44e189abbc79deb52a9ccf01d4b4_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classIEPolyModel_472e44e189abbc79deb52a9ccf01d4b4_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="648dbe0ff154458a3037d4f1a490084a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int IEPolyModel::GetNumVerts</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const<code> [inline]</code></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00595" class="el">595</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00290" class="el">VectorCollection::GetSize()</a>, and <a href="IEModel_8h-source.md#l00504" class="el">IEModel::m_vertexlist</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00623" class="el">getNumVerts()</a>, <a href="IEModel_8h-source.md#l00655" class="el">IETriModel::operator=()</a>, and <a href="IEModel_8h-source.md#l00569" class="el">operator=()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classIEPolyModel_648dbe0ff154458a3037d4f1a490084a_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classIEPolyModel_648dbe0ff154458a3037d4f1a490084a_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="c2a37a14999a70041c97a5689b202208" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEPolyModel.md" class="el">IEPolyModel</a>&amp; IEPolyModel::operator=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classIEPolyModel.md" class="el">IEPolyModel</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>other</em></td>
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
<td><p>Definition at line <a href="IEModel_8h-source.md#l00569" class="el">569</a> of file <a href="IEModel_8h-source.md" class="el">IEModel.h</a>.</p>
<p>References <a href="IEModel_8h-source.md#l00603" class="el">GetNumFaces()</a>, <a href="IEModel_8h-source.md#l00595" class="el">GetNumVerts()</a>, <a href="IEModel_8h-source.md#l00558" class="el">m_polyarray</a>, <a href="IEModel_8h-source.md#l00118" class="el">IEPoly::m_vertexid</a>, <a href="IEModel_8h-source.md#l00504" class="el">IEModel::m_vertexlist</a>, <a href="IEModel_8h-source.md#l00607" class="el">SetNumFaces()</a>, and <a href="IEModel_8h-source.md#l00599" class="el">SetNumVerts()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classIEPolyModel_c2a37a14999a70041c97a5689b202208_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classIEPolyModel_c2a37a14999a70041c97a5689b202208_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="20baa2fc60c7f945bbd199e103a37a4e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void IEPolyModel::SetNumFaces</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>numfaces</em></td>
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
<col style="width: 