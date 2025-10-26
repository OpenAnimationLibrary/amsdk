## Member Function Documentation

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
<td class="md" data-nowrap="" data-valign="top">half RGBHalf::Blue</td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00057" class="el">57</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="RGBHalf_8h-source.md#l00020" class="el">m_blue</a>.</p>
<p>Referenced by <a href="RGBHalf_8h-source.md#l00220" class="el">RGBAHalf::Blue()</a>, <a href="RGBHalf_8h-source.md#l00065" class="el">Max()</a>, <a href="RGBHalf_8h-source.md#l00132" class="el">operator *=()</a>, <a href="RGBHalf_8h-source.md#l00156" class="el">operator+()</a>, <a href="RGBHalf_8h-source.md#l00116" class="el">operator+=()</a>, <a href="RGBHalf_8h-source.md#l00124" class="el">operator-=()</a>, <a href="RGBHalf_8h-source.md#l00108" class="el">operator=()</a>, <a href="RGBFloat_8inl-source.md#l00021" class="el">RGBFloat::RGBFloat()</a>, and <a href="RGBFloat_8inl-source.md#l00093" class="el">YAFloat::YAFloat()</a>.</p></td>
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
<td class="md" data-nowrap="" data-valign="top">BOOL RGBHalf::CheckOffBound</td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00081" class="el">81</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>, and <a href="macwinsock_8h-source.md#l00036" class="el">TRUE</a>.</p>
<p>Referenced by <a href="RGBHalf_8h-source.md#l00237" class="el">RGBAHalf::CheckOffBound()</a>.</p></td>
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
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBHalf.md" class="el">RGBHalf</a> RGBHalf::GammaCorrect</td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00071" class="el">71</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="RGBHalf_8h-source.md#l00020" class="el">m_blue</a>, <a href="RGBHalf_8h-source.md#l00020" class="el">m_green</a>, <a href="RGBHalf_8h-source.md#l00020" class="el">m_red</a>, and <a href="RGBHalf_8h-source.md#l00059" class="el">Set()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classRGBHalf_a021873f9867b21b3e6ea9b95e32cba8_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classRGBHalf_a021873f9867b21b3e6ea9b95e32cba8_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="1adeff3d89e145a11e66b2186b132972" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float RGBHalf::GetLuminance</td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00070" class="el">70</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="RGBHalf_8h-source.md#l00020" class="el">m_blue</a>, <a href="RGBHalf_8h-source.md#l00020" class="el">m_green</a>, and <a href="RGBHalf_8h-source.md#l00020" class="el">m_red</a>.</p></td>
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
<td class="md" data-nowrap="" data-valign="top">half RGBHalf::Green</td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00056" class="el">56</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="RGBHalf_8h-source.md#l00020" class="el">m_green</a>.</p>
<p>Referenced by <a href="RGBHalf_8h-source.md#l00219" class="el">RGBAHalf::Green()</a>, <a href="RGBHalf_8h-source.md#l00065" class="el">Max()</a>, <a href="RGBHalf_8h-source.md#l00132" class="el">operator *=()</a>, <a href="RGBHalf_8h-source.md#l00156" class="el">operator+()</a>, <a href="RGBHalf_8h-source.md#l00116" class="el">operator+=()</a>, <a href="RGBHalf_8h-source.md#l00124" class="el">operator-=()</a>, <a href="RGBHalf_8h-source.md#l00108" class="el">operator=()</a>, <a href="RGBFloat_8inl-source.md#l00021" class="el">RGBFloat::RGBFloat()</a>, and <a href="RGBFloat_8inl-source.md#l00093" class="el">YAFloat::YAFloat()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="3f8f93af3f366d214c4c1c5b3b801683" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void RGBHalf::Max</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>max</em></td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00065" class="el">65</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="RGBHalf_8h-source.md#l00057" class="el">Blue()</a>, <a href="RGBHalf_8h-source.md#l00056" class="el">Green()</a>, <a href="Macros_8h-source.md#l00017" class="el">MIN</a>, <a href="RGBHalf_8h-source.md#l00055" class="el">Red()</a>, <a href="RGBHalf_8h-source.md#l00063" class="el">SetBlue()</a>, <a href="RGBHalf_8h-source.md#l00062" class="el">SetGreen()</a>, and <a href="RGBHalf_8h-source.md#l00061" class="el">SetRed()</a>.</p>
<p>Referenced by <a href="RGBHalf_8h-source.md#l00232" class="el">RGBAHalf::Max()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classRGBHalf_3f8f93af3f366d214c4c1c5b3b801683_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classRGBHalf_3f8f93af3f366d214c4c1c5b3b801683_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="ab251d56c3e469072bbcfe45d6ad0ac7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBHalf.md" class="el">RGBHalf</a> RGBHalf::operator *</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>s</em></td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00044" class="el">44</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="RGBHalf_8h-source.md#l00021" class="el">RGBHalf()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classRGBHalf_ab251d56c3e469072bbcfe45d6ad0ac7_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classRGBHalf_ab251d56c3e469072bbcfe45d6ad0ac7_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="f65e2e617e0140de6cc7e17f1bfa912b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBHalf.md" class="el">RGBHalf</a> RGBHalf::operator *</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classRGBHalf.md" class="el">RGBHalf</a> &amp; </td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00043" class="el">43</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="RGBHalf_8h-source.md#l00021" class="el">RGBHalf()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classRGBHalf_f65e2e617e0140de6cc7e17f1bfa912b_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classRGBHalf_f65e2e617e0140de6cc7e17f1bfa912b_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="36ff113e25ff93350facfeac60cdf34b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBHalf.md" class="el">RGBHalf</a> &amp; RGBHalf::operator *=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00140" class="el">140</a> of file <a href="RGBHalf_8h-source.md" class="el">RGBHalf.h</a>.</p>
<p>References <a href="RGBHalf_8h-source.md#l00020" class="el">m_blue</a>, <a href="RGBHalf_8h-source.md#l00020" class="el">m_green</a>, and <a href="RGBHalf_8h-source.md#l00020" class="el">m_red</a>.</p></td>
</tr>
</tbody>
</table>

<span id="6584f4d395e1a5d74c16aeb039485c3a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRGBHalf.md" class="el">RGBHalf</a> &amp; RGBHalf::operator *=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classRGBHalf.md" class="el">RGBHalf</a> &amp; </td>
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
<td><p>Definition at line <a href="RGBHalf_8h-source.md#l00132" class="el">132</a> of file <a href="RGBHalf_8h-source.md"