## Member Function Documentation

<span id="72762c1c420cb029764351e6745f6ba0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void* DataValue::AllocateData</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>length</em></td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00071" class="el">71</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="Allocate_8h.md#0edaf122805c62166f9ca67288ff9bc9" class="el">AllocExt()</a>, <a href="Allocate_8h.md#7fc37b7be38d47c3198070a04aef55ac" class="el">FreeExt()</a>, <a href="DataValue_8h-source.md#l00012" class="el">m_data</a>, and <a href="DataValue_8h-source.md#l00013" class="el">m_length</a>.</p>
<p>Referenced by <a href="DataValue_8h-source.md#l00043" class="el">operator=()</a>, and <a href="DataValue_8h-source.md#l00063" class="el">SetData()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDataValue_72762c1c420cb029764351e6745f6ba0_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDataValue_72762c1c420cb029764351e6745f6ba0_cgraph_map"></span></td>
</tr>
</tbody>
</table>

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
<td class="md" data-nowrap="" data-valign="top">void DataValue::FreeData</td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00091" class="el">91</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="Allocate_8h.md#7fc37b7be38d47c3198070a04aef55ac" class="el">FreeExt()</a>, <a href="DataValue_8h-source.md#l00012" class="el">m_data</a>, and <a href="DataValue_8h-source.md#l00013" class="el">m_length</a>.</p>
<p>Referenced by <a href="DataValue_8h-source.md#l00032" class="el">~DataValue()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDataValue_f14b970389c12e1f2042f114847ebef7_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDataValue_f14b970389c12e1f2042f114847ebef7_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="af6880ba6c41dcbb683182f9a7afcd99" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void* DataValue::GetData</td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00062" class="el">62</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="DataValue_8h-source.md#l00012" class="el">m_data</a>.</p></td>
</tr>
</tbody>
</table>

<span id="70a8806ccc79c5fa10cceb22ae1ad3bc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int DataValue::GetLength</td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00069" class="el">69</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="DataValue_8h-source.md#l00013" class="el">m_length</a>.</p>
<p>Referenced by <a href="DataValue_8h-source.md#l00043" class="el">operator=()</a>, and <a href="DataValue_8h-source.md#l00051" class="el">operator==()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="99712cfce3529b5479ca47ea92742879" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void DataValue::Init</td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00037" class="el">37</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="DataValue_8h-source.md#l00012" class="el">m_data</a>, and <a href="DataValue_8h-source.md#l00013" class="el">m_length</a>.</p>
<p>Referenced by <a href="DataValue_8h-source.md#l00015" class="el">DataValue()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="4b60768e769540f6a89151e8189e132a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL DataValue::IsEmpty</td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00100" class="el">100</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="DataValue_8h-source.md#l00013" class="el">m_length</a>.</p></td>
</tr>
</tbody>
</table>

<span id="9ccf1309510e2d2410b66c873a9dec13" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classDataValue.md" class="el">DataValue</a>&amp; DataValue::operator=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classDataValue.md" class="el">DataValue</a> &amp; </td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00043" class="el">43</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="DataValue_8h-source.md#l00071" class="el">AllocateData()</a>, <a href="DataValue_8h-source.md#l00069" class="el">GetLength()</a>, <a href="DataValue_8h-source.md#l00012" class="el">m_data</a>, and <a href="DataValue_8h-source.md#l00013" class="el">m_length</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDataValue_9ccf1309510e2d2410b66c873a9dec13_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDataValue_9ccf1309510e2d2410b66c873a9dec13_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="17bafad8a4b7c410baef55f7a63ddf1a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int DataValue::operator==</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classDataValue.md" class="el">DataValue</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>other</em></td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00051" class="el">51</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="DataValue_8h-source.md#l00069" class="el">GetLength()</a>, <a href="DataValue_8h-source.md#l00012" class="el">m_data</a>, and <a href="DataValue_8h-source.md#l00013" class="el">m_length</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDataValue_17bafad8a4b7c410baef55f7a63ddf1a_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDataValue_17bafad8a4b7c410baef55f7a63ddf1a_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="515260f321f0211ea2a84c190dc56cac" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void DataValue::SetData</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BYTE * </td>
<td class="mdname" data-nowrap=""><em>data</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>length</em></td>
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
<td><p>Definition at line <a href="DataValue_8h-source.md#l00063" class="el">63</a> of file <a href="DataValue_8h-source.md" class="el">DataValue.h</a>.</p>
<p>References <a href="DataValue_8h-source.md#l00071" class="el">AllocateData()</a>, <a href="DataValue_8h-source.md#l00012" class="el">m_data</a>, and <a href="DataValue_8h-source.md#l00013" class="el">m_length</a>.</p>
<p>Referenced by <a href="DataValue_8h-source.md#l00020" class="el">DataValue()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDataValue_515260f321f0211ea2a84c190dc56cac_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDataValue_515260f321f0211ea2a84c190dc56cac_cgraph_map"></span></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

