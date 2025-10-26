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
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> YAByte::Alpha</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00282" class="el">282</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="RGBByte_8h-source.md#l00250" class="el">m_alpha</a>.</p></td>
</tr>
</tbody>
</table>

<span id="774af4359d10952f3403a874a91b01f7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL YAByte::CheckOffBound</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>lobound</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>hibound</em></td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00302" class="el">302</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
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
<td class="md" data-nowrap="" data-valign="top"><a href="classYAByte.md" class="el">YAByte</a> YAByte::GammaCorrect</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00287" class="el">287</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="Fastftol_8h-source.md#l00018" class="el">fast_round()</a>, <a href="RGBByte_8h-source.md#l00250" class="el">m_alpha</a>, <a href="RGBByte_8h-source.md#l00249" class="el">m_luminance</a>, <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="Macros_8h-source.md#l00017" class="el">MIN</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classYAByte_a021873f9867b21b3e6ea9b95e32cba8_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classYAByte_a021873f9867b21b3e6ea9b95e32cba8_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="b8454ebbd52c20bd6eb0319e1043bb23" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float YAByte::GetFactoredFloat</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00276" class="el">276</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="RGBByte_8h-source.md#l00249" class="el">m_luminance</a>.</p></td>
</tr>
</tbody>
</table>

<span id="93e0d19b981a2284db1c05d534aeffa2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classYAFloat.md" class="el">YAFloat</a> YAByte::GetFactoredRGBAFloat</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="38f09f32b4c6f6cd09cb6f07c1fb5430" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float YAByte::GetFloat</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00296" class="el">296</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="RGBByte_8h-source.md#l00249" class="el">m_luminance</a>, and <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>.</p></td>
</tr>
</tbody>
</table>

<span id="0e6dd67023a184fb372932e655b56d1c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float YAByte::GetLuminance</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00300" class="el">300</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="RGBByte_8h-source.md#l00249" class="el">m_luminance</a>, and <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>.</p></td>
</tr>
</tbody>
</table>

<span id="300e66e25eaece252a7aa4e96f7d9139" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float YAByte::GetNormalizedFloat</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00277" class="el">277</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="RGBByte_8h-source.md#l00249" class="el">m_luminance</a>, and <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>.</p></td>
</tr>
</tbody>
</table>

<span id="ad10fc78115110de8a428f1216677c1e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classYAFloat.md" class="el">YAFloat</a> YAByte::GetNormalizedRGBAFloat</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

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
<td class="md" data-nowrap="" data-valign="top">float YAByte::GetOpacity</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00298" class="el">298</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="RGBByte_8h-source.md#l00250" class="el">m_alpha</a>, and <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>.</p></td>
</tr>
</tbody>
</table>

<span id="48d242596d846e42555ee8962e7d27ac" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classYAFloat.md" class="el">YAFloat</a> YAByte::GetYAFloat</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="c51367eb7743b6262c9bc2469cb3b543" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> YAByte::Luminance</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00281" class="el">281</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="RGBByte_8h-source.md#l00249" class="el">m_luminance</a>.</p></td>
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
<td class="md" data-nowrap="" data-valign="top"><a href="classYAByte.md" class="el">YAByte</a> &amp; YAByte::operator *=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const  </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>float</em></td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00333" class="el">333</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="RGBByte_8h-source.md#l00250" class="el">m_alpha</a>, and <a href="RGBByte_8h-source.md#l00249" class="el">m_luminance</a>.</p></td>
</tr>
</tbody>
</table>

<span id="b2a90b0840ba0f087728d89d27353935" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void YAByte::operator delete</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>ptr</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></