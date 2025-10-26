## Member Function Documentation

<span id="0333130ffc9187bb3ed905eb61d99832" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> ColorBuf::Alpha</td>
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
<td><p>Retrieve the alpha channel value. Return value is UBYTE so between 0 and 255.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00072" class="el">72</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="e3b99a5fe15a4330fd055c8b157ee12f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> ColorBuf::Blue</td>
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
<td><p>Retrieve the blue channel value. Return value is UBYTE so between 0 and 255.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00071" class="el">71</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="619d7deb16927463582495a28b86f235" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> ColorBuf::Color</td>
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
<td><p>Retrieve all the color and alpha channel values as a ULONG, so between 0 and 255.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00073" class="el">73</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="ColorBuf_8h-source.md#l00049" class="el">color</a>.</p></td>
</tr>
</tbody>
</table>

<span id="a021873f9867b21b3e6ea9b95e32cba8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void ColorBuf::GammaCorrect</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>power</em></td>
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
<td><p>Apply a Gamma correction to the color channels. Alpha channel is not corrected.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
Applying a Gamma correction directly on a ColorBuf instance is not recommanded because it can produce strong color aliasing where several original colors values will map to the same corrected value and several color values will be left unused resulting in loss of information. It is recommended that Gamma correction be applied from a <a href="classRGBAFloat.md" class="el">RGBAFloat</a> or <a href="classRGBAHalf.md" class="el">RGBAHalf</a> for optimal results.
</dd>
</dl>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00152" class="el">152</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="ColorBuf_8h-source.md#l00145" class="el">GammaCorrectColBuf()</a>, and <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classColorBuf_a021873f9867b21b3e6ea9b95e32cba8_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classColorBuf_a021873f9867b21b3e6ea9b95e32cba8_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="bd37cbaf06b0ce675453ece1c22dcb85" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> ColorBuf::Get</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void </td>
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
<td><p>Retrieve the normalized (from 0.0 to 1.0) color channels values.</p>
<p>Definition at line <a href="ColorBuf_8inl-source.md#l00028" class="el">28</a> of file <a href="ColorBuf_8inl-source.md" class="el">ColorBuf.inl</a>.</p>
<p>References <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="3a716da63246c77ec051591509ae7a01" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> ColorBuf::GetFactoredRGBFloat</td>
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
<td><p>Factored color values are between 0.0 and 255.0 where 0.0 represent total black and 255.0 represent a theoretical white.</p>
<p>Definition at line <a href="ColorBuf_8inl-source.md#l00034" class="el">34</a> of file <a href="ColorBuf_8inl-source.md" class="el">ColorBuf.inl</a>.</p>
<p>References <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="edabf03f9243223a1b19ec1b8e6d3a7d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBFloat.md" class="el">RGBFloat</a> ColorBuf::GetNormalizedRGBFloat</td>
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
<td><p>Normalized color values are between 0.0 and 1.0 where 0.0 represent total black and 1.0 represent a theoretical white. Note that when stored in a ColorBuf, color values can never exceed 1.0.</p>
<p>Definition at line <a href="ColorBuf_8inl-source.md#l00039" class="el">39</a> of file <a href="ColorBuf_8inl-source.md" class="el">ColorBuf.inl</a>.</p>
<p>References <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="3ff93e400445c24a8d552488a6564874" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float ColorBuf::GetOpacity</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void </td>
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
<td><p>Retrieve the normalized (from 0.0 to 1.0) alpha channel value.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00088" class="el">88</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="eb4e3e708de4af84613f52d0c8067edf" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> ColorBuf::Green</td>
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
<td><p>Retrieve the green channel value. Return value is UBYTE so between 0 and 255.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00070" class="el">70</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="299cf8813cba25caa1a8533ce7709734" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void ColorBuf::operator *=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>factor</em></td>
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
<td><p>Multiplies the current instance channel values by the factor parameter. Result is rounded to the nearest integer.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00137" class="el">137</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="937d3668c777a0e6e44b58c7567e1bb7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">ColorBuf::operator COLORREF</td>
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
<td><p>Casts a ColorBuf into a COLORREF.</p>
<p>Definition at line <a href="ColorBuf_8h-source.md#l00056" class="el">56</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="classColorBuf.md#f09cc7ee3a9a93273f4b80601cafb00c" class="el">values</a>.</p></td>
</tr>
</tbody>
</table>

<span id="2485eb54184a6269e7cf9c830c526585" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr