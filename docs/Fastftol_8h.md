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

# Fastftol.h File Reference

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="Fastftol_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Fastftol.hdep_map"></span>

[Go to the source code of this file.](Fastftol_8h-source.md)

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
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Fastftol_8h.md#49994175a1a0a86b3fe8e0293c44c209" class="el">__FASTFTOL_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Fastftol_8h.md#0fe92f34f2242547f39e8af18d762e72" class="el">ASSEMBLER_OPTIMIZATIONS</a>   1</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Fastftol_8h.md#b693d1ca081c12ef53894a6e91fc61c9" class="el">FAST_ROUND</a>(fx, x)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="Fastftol_8h.md#3e027f12e41e701ee8c67f4fdae214da" class="el">fast_round</a> (float d)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="Fastftol_8h.md#ac1eab3f0e106a34fcbd6dba5f4b647d" class="el">fast_ftol_unsigned</a> (float d)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="Fastftol_8h.md#fd3730597a0e1c7e926b9cfaa9973dda" class="el">fast_ftol_signed</a> (float d)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="Fastftol_8h.md#9f9fb221963c2bfddb25593e9cfcd220" class="el">fast_floor</a> (float d)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="Fastftol_8h.md#bb5045461d483df4c174ac9495495ae3" class="el">__declspec</a> (naked) float __fastcall InverseSqrt(float a)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="49994175a1a0a86b3fe8e0293c44c209" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __FASTFTOL_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Fastftol_8h-source.md#l00003" class="el">3</a> of file <a href="Fastftol_8h-source.md" class="el">Fastftol.h</a>. |

<span id="0fe92f34f2242547f39e8af18d762e72" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define ASSEMBLER_OPTIMIZATIONS   1</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Fastftol_8h-source.md#l00006" class="el">6</a> of file <a href="Fastftol_8h-source.md" class="el">Fastftol.h</a>. |

<span id="b693d1ca081c12ef53894a6e91fc61c9" class="anchor"></span>

\#define FAST_ROUND

( 

fx,

x 

 ) 

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p><strong>Value:</strong></p>
<div class="fragment">
<pre class="fragment"><code>{ \
      float __fx = (fx); \
      _asm fld __fx \
      _asm fistp x \
   }</code></pre>
</div>
<p>Definition at line <a href="Fastftol_8h-source.md#l00008" class="el">8</a> of file <a href="Fastftol_8h-source.md" class="el">Fastftol.h</a>.</p>
<p>Referenced by <a href="Fastftol_8h-source.md#l00018" class="el">fast_round()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Function Documentation

<span id="bb5045461d483df4c174ac9495495ae3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">__declspec</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">naked </td>
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
<td><p>Definition at line <a href="Fastftol_8h-source.md#l00122" class="el">122</a> of file <a href="Fastftol_8h-source.md" class="el">Fastftol.h</a>.</p>
<p>References <a href="Rave_8h.md#51b38547609c2cb31342492287c149e1" class="el">float()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Fastftol_8h_bb5045461d483df4c174ac9495495ae3_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Fastftol_8h_bb5045461d483df4c174ac9495495ae3_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="9f9fb221963c2bfddb25593e9cfcd220" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int fast_floor</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>d</em></td>
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
|   | Definition at line <a href="Fastftol_8h-source.md#l00086" class="el">86</a> of file <a href="Fastftol_8h-source.md" class="el">Fastftol.h</a>. |

<span id="fd3730597a0e1c7e926b9cfaa9973dda" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int fast_ftol_signed</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>d</em></td>
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
|   | Definition at line <a href="Fastftol_8h-source.md#l00053" class="el">53</a> of file <a href="Fastftol_8h-source.md" class="el">Fastftol.h</a>. |

<span id="ac1eab3f0e106a34fcbd6dba5f4b647d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int fast_ftol_unsigned</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>d</em></td>
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
<td><p>Definition at line <a href="Fastftol_8h-source.md#l00032" class="el">32</a> of file <a href="Fastftol_8h-source.md" class="el">Fastftol.h</a>.</p>
<p>References <a href="HashTime_8h-source.md#l00326" class="el">abs()</a>.</p>
<p>Referenced by <a href="ColorBuf_8inl-source.md#l00013" class="el">ColorBuf::ColorBuf()</a>, <a href="ColorBuf_8inl-source.md#l00021" class="el">ColorBuf::Set()</a>, and <a href="ColorBuf_8h-source.md#l00093" class="el">ColorBuf::SetOpacity()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Fastftol_8h_ac1eab3f0e106a34fcbd6dba5f4b647d_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Fastftol_8h_ac1eab3f0e106a34fcbd6dba5f4b647d_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="3e027f12e41e701ee8c67f4fdae214da" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int fast_round</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>d</em></td>
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
<td><p>Definition at line <a href="Fastftol_8h-source.md#l00018" class="el">18</a> of file <a href="Fastftol_8h-source.md" class="el">Fastftol.h</a>.</p>
<p>References <a href="Fastftol_8h-source.md#l00008" class="el">FAST_ROUND</a>.</p>
<p>Referenced by <a href="RGBByte_8h-source.md#l00287" class="el">YAByte::GammaCorrect()</a>, <a href="RGBByte_8h-source.md#l00128" class="el">RGBByte::GammaCorrect()</a>, <a href="RGBByte_8h-source.md#l00121" class="el">GammaCorrect()</a>, <a href="ColorBuf_8h-source.md#l00145" class="el">GammaCorrectColBuf()</a>, <a href="RGBFloat_8h-source.md#l00083" class="el">RGBFloat::GetCOLORREF()</a>, and <a href="ColorVec_8h-source.md#l00071" class="el">ColorVector::GetCOLORREF()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:47 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
