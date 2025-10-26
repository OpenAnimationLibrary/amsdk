<div class="tabs">

- [Main Page](index.md)
- [Classes](annotated.md)
- <span id="current">[Files](files.md)</span>
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [File List](files.md)
- [File Members](globals.md)

</div>

<div class="nav">

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# ColorBuf.h File Reference

`#include "FastFTOL.h"`  
`#include "`<a href="Vector_8h-source.md" class="el"><code>Vector.h</code></a>`"`  
`#include "`<a href="DataType_8h-source.md" class="el"><code>DataType.h</code></a>`"`  
`#include "`<a href="Macros_8h-source.md" class="el"><code>Macros.h</code></a>`"`  
`#include <math.h>`  

Include dependency graph for ColorBuf.h:

<span class="image placeholder" original-image-src="ColorBuf_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/ColorBuf.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="ColorBuf_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/ColorBuf.hdep_map"></span>

[Go to the source code of this file.](ColorBuf_8h-source.md)

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
&#10;<h2 id="classes">Classes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">union  </td>
<td class="memItemRight" data-valign="bottom"><a href="unionColor.md" class="el">Color</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classColorBuf.md" class="el">ColorBuf</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Simple RGB and RGBA color buffer where R, G, B and A are represented by byte values. Same as what is stored in the TGA files. <a href="classColorBuf.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="ColorBuf_8h.md#760ed0c169bbae9fdba9b884170d3748" class="el">__COLORBUF_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="ColorBuf_8h.md#8d346876c93cf5dee9b3f10a02518436" class="el">V_PI</a>   3.1415926535898</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="ColorBuf_8h.md#47096d96af44feaec31aeb07425d39ae" class="el">BACKGROUNDMASK</a>   0x00FFFFFF</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="ColorBuf_8h.md#ed29f3f6d05882df1e1c1d3ea2bc3b5f" class="el">MAXCOLOR</a>   255</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="ColorBuf_8h.md#25fda16aa10a025ab21b9019b094ef27" class="el">DEPTH24</a>   24</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="ColorBuf_8h.md#cc9b06b2ceb3dae563fbdd965382eccd" class="el">NUMMIPLEVEL</a>   4</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="ColorBuf_8h.md#fbee7200569af3790161fd41f9063bfa" class="el">MAKELUMINANCE</a>(red, green, blue)   (0.3f*red + 0.59f*green + 0.11f*blue)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="ColorBuf_8h.md#38ffd5011595ccb481c3f393f66e1d1a" class="el">GammaCorrectColBuf</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> *color, float power)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="760ed0c169bbae9fdba9b884170d3748" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __COLORBUF_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ColorBuf_8h-source.md#l00003" class="el">3</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>. |

<span id="47096d96af44feaec31aeb07425d39ae" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define BACKGROUNDMASK   0x00FFFFFF</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ColorBuf_8h-source.md#l00021" class="el">21</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>. |

<span id="25fda16aa10a025ab21b9019b094ef27" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define DEPTH24   24</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ColorBuf_8h-source.md#l00023" class="el">23</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>. |

<span id="fbee7200569af3790161fd41f9063bfa" class="anchor"></span>

\#define MAKELUMINANCE

( 

red,

green,

blue 

 ) 

   (0.3f\*red + 0.59f\*green + 0.11f\*blue)

|  |  |
|----|----|
|   | Definition at line <a href="ColorBuf_8h-source.md#l00161" class="el">161</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>. |

<span id="ed29f3f6d05882df1e1c1d3ea2bc3b5f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define MAXCOLOR   255</td>
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
<td><p>Definition at line <a href="ColorBuf_8h-source.md#l00022" class="el">22</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>Referenced by <a href="ColorBuf_8h-source.md#l00062" class="el">ColorBuf::ColorBuf()</a>, <a href="ColorVec_8inl-source.md#l00034" class="el">ColorVectorAlpha::ColorVectorAlpha()</a>, <a href="RGBByte_8h-source.md#l00287" class="el">YAByte::GammaCorrect()</a>, <a href="RGBByte_8h-source.md#l00128" class="el">RGBByte::GammaCorrect()</a>, <a href="RGBByte_8h-source.md#l00121" class="el">GammaCorrect()</a>, <a href="ColorBuf_8h-source.md#l00145" class="el">GammaCorrectColBuf()</a>, <a href="ColorBuf_8inl-source.md#l00028" class="el">ColorBuf::Get()</a>, <a href="RGBByte_8h-source.md#l00296" class="el">YAByte::GetFloat()</a>, <a href="RGBByte_8h-source.md#l00300" class="el">YAByte::GetLuminance()</a>, <a href="RGBByte_8h-source.md#l00277" class="el">YAByte::GetNormalizedFloat()</a>, <a href="ColorBuf_8inl-source.md#l00039" class="el">ColorBuf::GetNormalizedRGBFloat()</a>, <a href="RGBByte_8h-source.md#l00298" class="el">YAByte::GetOpacity()</a>, <a href="RGBByte_8h-source.md#l00200" class="el">RGBAByte::GetOpacity()</a>, <a href="ColorBuf_8h-source.md#l00088" class="el">ColorBuf::GetOpacity()</a>, <a href="RGBByte_8h-source.md#l00305" class="el">YAByte::operator+=()</a>, <a href="RGBByte_8h-source.md#l00210" class="el">RGBAByte::operator+=()</a>, <a href="RGBByte_8h-source.md#l00079" class="el">RGBByte::operator+=()</a>, <a href="ColorBuf_8h-source.md#l00098" class="el">ColorBuf::operator+=()</a>, <a href="RGBByte_8h-source.md#l00146" class="el">RGBAByte::RGBAByte()</a>, <a href="RGBFloat_8inl-source.md#l00044" class="el">RGBAFloat::RGBAFloat()</a>, <a href="ColorBuf_8inl-source.md#l00021" class="el">ColorBuf::Set()</a>, <a href="ColorBuf_8h-source.md#l00079" class="el">ColorBuf::SetColor()</a>, <a href="RGBByte_8h-source.md#l00285" class="el">YAByte::SetLuminance()</a>, <a href="ColorBuf_8h-source.md#l00093" class="el">ColorBuf::SetOpacity()</a>, <a href="RGBByte_8h-source.md#l00252" class="el">YAByte::YAByte()</a>, and <a href="RGBFloat_8inl-source.md#l00067" class="el">YAFloat::YAFloat()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="cc9b06b2ceb3dae563fbdd965382eccd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define NUMMIPLEVEL   4</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ColorBuf_8h-source.md#l00024" class="el">24</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>. |

<span id="8d346876c93cf5dee9b3f10a02518436" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define V_PI   3.1415926535898</td>
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
<td><p>Definition at line <a href="ColorBuf_8h-source.md#l00019" class="el">19</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>Referenced by <a href="RGBFloat_8h-source.md#l00112" class="el">GetSpectrumColor()</a>, and <a href="ColorVec_8h-source.md#l00083" class="el">GetSpectrumColorVector()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Function Documentation

<span id="38ffd5011595ccb481c3f393f66e1d1a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void GammaCorrectColBuf</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> * </td>
<td class="mdname" data-nowrap=""><em>color</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>power</em></td>
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
<td><p>Definition at line <a href="ColorBuf_8h-source.md#l00145" class="el">145</a> of file <a href="ColorBuf_8h-source.md" class="el">ColorBuf.h</a>.</p>
<p>References <a href="Fastftol_8h-source.md#l00018" class="el">fast_round()</a>, <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="Macros_8h-source.md#l00017" class="el">MIN</a>.</p>
<p>Referenced by <a href="ColorBuf_8h-source.md#l00152" class="el">ColorBuf::GammaCorrect()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="ColorBuf_8h_38ffd5011595ccb481c3f393f66e1d1a_cgraph.gif" data-original-image-title="" data-border="0" usemap="#ColorBuf_8h_38ffd5011595ccb481c3f393f66e1d1a_cgraph_map"></span></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
