## Member Function Documentation

<span id="b280269cc0a506501eff4139cd94cb39" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
<td></td>
<td></td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">int <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::Add</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">ARG_TYPE </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>newElement</em></td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00127" class="el">127</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>References <a href="HashArra_8h-source.md#l00097" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_size</a>, and <a href="HashArra_8h-source.md#l00220" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::SetAtGrow()</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00455" class="el">UDCollection&lt; TYPE, ARG_TYPE &gt;::Add()</a>, <a href="IEModel_8h-source.md#l00387" class="el">VectorCollection::Add()</a>, and <a href="IEModel_8h-source.md#l00474" class="el">UDCollection&lt; TYPE, ARG_TYPE &gt;::AddForce()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classHashArray_b280269cc0a506501eff4139cd94cb39_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classHashArray_b280269cc0a506501eff4139cd94cb39_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="83feaa64c8e9087b27f2fe9f31eb6b18" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
<td></td>
<td></td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">TYPE &amp; <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::ElementAt</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>index</em></td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00118" class="el">118</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>References <a href="HashArra_8h-source.md#l00096" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_data</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00292" class="el">VectorCollection::ElementAt()</a>, <a href="IEModel_8h-source.md#l00300" class="el">VectorCollection::operator[]()</a>, <a href="IEModel_8h-source.md#l00242" class="el">IEPatch::~IEPatch()</a>, and <a href="IEModel_8h-source.md#l00131" class="el">IEPoly::~IEPoly()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="0c686ee0fcab422244a7c79f614c195e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
<td></td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">void <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::FreeExtra</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="HashArra_8h-source.md#l00204" class="el">204</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>References <a href="Allocate_8h.md#0edaf122805c62166f9ca67288ff9bc9" class="el">AllocExt()</a>, <a href="Allocate_8h.md#7fc37b7be38d47c3198070a04aef55ac" class="el">FreeExt()</a>, <a href="HashArra_8h-source.md#l00096" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_data</a>, <a href="HashArra_8h-source.md#l00098" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_maxsize</a>, and <a href="HashArra_8h-source.md#l00097" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_size</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00448" class="el">UDCollection&lt; IEMap, IEMap &amp; &gt;::Shrink()</a>, and <a href="IEModel_8h-source.md#l00302" class="el">VectorCollection::Shrink()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classHashArray_0c686ee0fcab422244a7c79f614c195e_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classHashArray_0c686ee0fcab422244a7c79f614c195e_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="95a7201fab22e53b513f89e23fbca949" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
<td></td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">TYPE * <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::GetArray</td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00124" class="el">124</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>References <a href="HashArra_8h-source.md#l00096" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_data</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00288" class="el">VectorCollection::GetArray()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="ddc54dfc91e8489e924df466a56ffe1e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
<td></td>
<td></td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">TYPE <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::GetAt</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>index</em></td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00115" class="el">115</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>References <a href="HashArra_8h-source.md#l00096" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_data</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00455" class="el">UDCollection&lt; TYPE, ARG_TYPE &gt;::Add()</a>, <a href="IEModel_8h-source.md#l00387" class="el">VectorCollection::Add()</a>, <a href="IEModel_8h-source.md#l00289" class="el">VectorCollection::GetAt()</a>, <a href="IEModel_8h-source.md#l00481" class="el">UDCollection&lt; TYPE, ARG_TYPE &gt;::LookUp()</a>, <a href="IEModel_8h-source.md#l00342" class="el">VectorCollection::LookUp()</a>, <a href="IEModel_8h-source.md#l00368" class="el">VectorCollection::LookUpHashKey()</a>, and <a href="IEModel_8h-source.md#l00299" class="el">VectorCollection::operator[]()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="62dae3ace05cea3c33a91593a13a57ac" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
<td></td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">TYPE <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::GetPushed</td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00312" class="el">312</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>References <a href="HashArra_8h-source.md#l00096" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_data</a>, and <a href="HashArra_8h-source.md#l00097" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_size</a>.</p></td>
</tr>
</tbody>
</table>

<span id="f2259ebe9d1c07ceb60119edb0a86416" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
<td></td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">int <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::GetSize</td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00106" class="el">106</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>References <a href="HashArra_8h-source.md#l00097" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_size</a>.</p>
<p>Referenced by <a href="IEModel_8h-source.md#l00387" class="el">VectorCollection::Add()</a>, <a href="IEModel_8h-source.md#l00307" class="el">VectorCollection::Empty()</a>, <a href="IEModel_8h-source.md#l00587" class="el">IEPolyModel::FreeData()</a>, <a href="IEModel_8h-source.md#l00603" class="el">IEPolyModel::GetNumFaces()</a>, <a href="IEModel_8h-source.md#l00290" class="el">VectorCollection::GetSize()</a>, <a href="IEModel_8h-source.md#l00342" class="el">VectorCollection::LookUp()</a>, <a href="IEModel_8h-source.md#l00368" class="el">VectorCollection::LookUpHashKey()</a>, <a href="IEModel_8h-source.md#l00148" class="el">IEPoly::operator=()</a>, <a href="IEModel_8h-source.md#l00242" class="el">IEPatch::~IEPatch()</a>, and <a href="IEModel_8h-source.md#l00131" class="el">IEPoly::~IEPoly()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="ffa41436425726208b8f55f1b7d26cbd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
<td></td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">int <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::GetUpperBound</td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00109" class="el">109</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>References <a href="HashArra_8h-source.md#l00097" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::m_size</a>.</p></td>
</tr>
</tbody>
</table>

<span id="c1a9ad8203baf81261ea98ad62b8fea0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE, class ARG_TYPE&gt;</td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">void <a href="classHashArray.md" class="el">HashArray</a>&lt; TYPE, ARG_TYPE &gt;::InsertAt</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname" data-nowrap=""><em>nIndex</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">ARG_TYPE </td>
<td class="mdname" data-nowrap=""><em>newElement</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" da