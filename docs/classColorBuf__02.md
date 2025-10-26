## Constructor & Destructor Documentation

<span id="99e2887344e07f414aa3a4914e815a45" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">ColorBuf::ColorBuf</td>
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
<td><p>Creates an instance of a ColorBuf where the initial color is black and the alpha channel is fully opaque.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00062" class="el">62</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="ColorBuf_8h-source.md#l00049" class="el">color</a>, <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="12193a668cd16d0e496fee9b99faa33d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">ColorBuf::ColorBuf</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">LONG </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>col</em></td>
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
<td><p>Creates an instance of a ColorBuf. The color is copied from the col parameter. The alpha channel is fully opaque.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
If col parameter contained valid alpha channel values, it was discarded by the constructor.
</dd>
</dl>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00063" class="el">63</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="ColorBuf_8h-source.md#l00049" class="el">color</a>, <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="a54f386c09bfdd0c512b26ca38752205" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">ColorBuf::ColorBuf</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="mdname" data-nowrap=""><em>pred</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="mdname" data-nowrap=""><em>pgreen</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="mdname" data-nowrap=""><em>pblue</em></td>
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
<td><p>Creates an instance of a ColorBuf. The color channels are copied from the parameters and the alpha channel is fully opaque.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00064" class="el">64</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="f22227be93524420a17d925f89004a08" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">ColorBuf::ColorBuf</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="mdname" data-nowrap=""><em>pred</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="mdname" data-nowrap=""><em>pgreen</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="mdname" data-nowrap=""><em>pblue</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> </td>
<td class="mdname" data-nowrap=""><em>palpha</em></td>
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
<td><p>Creates an instance of a ColorBuf. The colors and alpha channels are copied from the parameters.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00065" class="el">65</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="78f92abbc4e45930c92b0c17e462b1b0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">ColorBuf::ColorBuf</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">COLORREF </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>c</em></td>
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
<td><p>Creates an instance of a ColorBuf. The color is copied from the c parameter. The alpha channel is fully opaque.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
If c parameter contained valid alpha channel values, it was discarded by the constructor.
</dd>
</dl>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00066" class="el">66</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="8d9b7ca6430ee525350352f4072e7a2e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">ColorBuf::ColorBuf</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classRGBAFloat.md" class="el">RGBAFloat</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>color</em></td>
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
<td><p>Creates an instance of a ColorBuf. The colors and alpha channels are set from the color parameter which is interpreted as being normalized. That is color and alpha channel values of 1.0 is mapped to 255.</p>
<p>Definition at line <a href="ColorBuf_8inl-source.md#l00013" class="el">13</a> of file <a href="ColorBuf_8inl-source.md" class="el">ColorBuf.inl</a>.</p>
<p>References <a href="RGBFloat_8h-source.md#l00159" class="el">RGBAFloat::Alpha()</a>, <a href="RGBFloat_8h-source.md#l00158" class="el">RGBAFloat::Blue()</a>, <a href="Fastftol_8h-source.md#l00032" class="el">fast_ftol_unsigned()</a>, <a href="RGBFloat_8h-source.md#l00157" class="el">RGBAFloat::Green()</a>, <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, <a href="Macros_8h-source.md#l00017" class="el">MIN</a>, <a href="RGBFloat_8h-source.md#l00156" class="el">RGBAFloat::Red()</a>, and <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classColorBuf_8d9b7ca6430ee525350352f4072e7a2e_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classColorBuf_8d9b7ca6430ee525350352f4072e7a2e_cgraph_map"></span></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

