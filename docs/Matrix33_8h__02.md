## Function Documentation

<span id="27ae8456c2ae140937e435ac4628672a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> Identity33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void </td>
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
|   | Definition at line <a href="Matrix33_8h-source.md#l00261" class="el">261</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>. |

<span id="662ae926e6599cad3408600afa7833da" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> RotateV33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>angle</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>axis</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00127" class="el">127</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>.</p></td>
</tr>
</tbody>
</table>

<span id="c96d639e8bbf5649cf77f857f55e6a8e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> VectorsToStandard33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>becomezdir</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>becomeydir</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00155" class="el">155</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Rave_8h.md#51b38547609c2cb31342492287c149e1" class="el">float()</a>, <a href="Vector_8h-source.md#l00027" class="el">Vector::x</a>, <a href="Vector_8h-source.md#l00027" class="el">Vector::y</a>, and <a href="Matrix33_8h-source.md#l00147" class="el">ZRotateRadians33()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix33_8h_c96d639e8bbf5649cf77f857f55e6a8e_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix33_8h_c96d639e8bbf5649cf77f857f55e6a8e_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="60694456fa864eb9fd0fbe7179d6d614" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> XRotate33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>angle</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00120" class="el">120</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>, and <a href="Matrix33_8h-source.md#l00129" class="el">XRotateRadians33()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix33_8h_60694456fa864eb9fd0fbe7179d6d614_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix33_8h_60694456fa864eb9fd0fbe7179d6d614_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="889f72090eee4546377cdce79ba1d212" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> XRotateRadians33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>anglerad</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00129" class="el">129</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Rave_8h.md#51b38547609c2cb31342492287c149e1" class="el">float()</a>.</p>
<p>Referenced by <a href="Matrix33_8h-source.md#l00120" class="el">XRotate33()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix33_8h_889f72090eee4546377cdce79ba1d212_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix33_8h_889f72090eee4546377cdce79ba1d212_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="34f0f2c3d7bf495acd1139f0e955ec43" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> YRotate33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>angle</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00121" class="el">121</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>, and <a href="Matrix33_8h-source.md#l00138" class="el">YRotateRadians33()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix33_8h_34f0f2c3d7bf495acd1139f0e955ec43_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix33_8h_34f0f2c3d7bf495acd1139f0e955ec43_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="42dffcda8f9f377df325ba611695cd1d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> YRotateRadians33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>anglerad</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00138" class="el">138</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Rave_8h.md#51b38547609c2cb31342492287c149e1" class="el">float()</a>.</p>
<p>Referenced by <a href="Matrix33_8h-source.md#l00121" class="el">YRotate33()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix33_8h_42dffcda8f9f377df325ba611695cd1d_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix33_8h_42dffcda8f9f377df325ba611695cd1d_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="9c9c0268eb98a23cd825e8ec9f82815d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> YXRotate33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>yangle</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>xangle</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00123" class="el">123</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>.</p></td>
</tr>
</tbody>
</table>

<span id="b87bf0da3b554d1b3e7ed5235e0f5923" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> YXZRotate33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>yangle</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>xangle</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>zangle</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00125" class="el">125</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>.</p></td>
</tr>
</tbody>
</table>

<span id="86a327cd77178ab1cde5454e8b4a6f6c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> ZRotate33</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>angle</em></td>
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
<td><p>Definition at line <a href="Matrix33_8h-source.md#l00122" class="el">122</a> of file <a href="Matrix33_8h-source.md" class="el">Matrix33.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>, and <a href="Matrix33_8h-source.md#l00147" class="el">ZRotateRadians33()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Matrix33_8h_86a327cd77178ab1cde5454e8b4a6f6c_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Matrix33_8h_86a327cd77178ab1cde5454e8b4a6f6c_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="4853f244734d6f957de647aa8eda2de8" class="an