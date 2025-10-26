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

# RGBByte.h File Reference

`#include "`<a href="Allocate_8h-source.md" class="el"><code>Allocate.h</code></a>`"`  
`#include "FastFTOL.h"`  
`#include "`<a href="Vector_8h-source.md" class="el"><code>Vector.h</code></a>`"`  
`#include "`<a href="Macros_8h-source.md" class="el"><code>Macros.h</code></a>`"`  

Include dependency graph for RGBByte.h:

<span class="image placeholder" original-image-src="RGBByte_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/RGBByte.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="RGBByte_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/RGBByte.hdep_map"></span>

[Go to the source code of this file.](RGBByte_8h-source.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classRGBByte.md" class="el">RGBByte</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classRGBAByte.md" class="el">RGBAByte</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classYAByte.md" class="el">YAByte</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RGBByte_8h.md#1ff6f82704f985593c5aa6e76142f424" class="el">__RGBBYTE_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RGBByte_8h.md#ed29f3f6d05882df1e1c1d3ea2bc3b5f" class="el">MAXCOLOR</a>   255</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RGBByte_8h.md#f055f0d125df044d0646460940801baa" class="el">FLOATTOBYTE</a>(flt)   MAX(0,MIN(MAXCOLOR, fast_ftol_unsigned((flt) * MAXCOLOR + .5f)))</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="RGBByte_8h.md#2d056ec67e496c121db2d7190ad4c64e" class="el">GammaCorrect</a> (<a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> *color, float power)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="1ff6f82704f985593c5aa6e76142f424" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __RGBBYTE_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="RGBByte_8h-source.md#l00003" class="el">3</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>. |

<span id="f055f0d125df044d0646460940801baa" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FLOATTOBYTE</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">flt </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   MAX(0,MIN(MAXCOLOR, fast_ftol_unsigned((flt) * MAXCOLOR + .5f)))</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00025" class="el">25</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>Referenced by <a href="RGBByte_8h-source.md#l00299" class="el">YAByte::SetOpacity()</a>, and <a href="RGBByte_8h-source.md#l00205" class="el">RGBAByte::SetOpacity()</a>.</p></td>
</tr>
</tbody>
</table>

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

|  |  |
|----|----|
|   | Definition at line <a href="RGBByte_8h-source.md#l00024" class="el">24</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>. |

------------------------------------------------------------------------

## Function Documentation

<span id="2d056ec67e496c121db2d7190ad4c64e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void GammaCorrect</td>
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
<td><p>Definition at line <a href="RGBByte_8h-source.md#l00121" class="el">121</a> of file <a href="RGBByte_8h-source.md" class="el">RGBByte.h</a>.</p>
<p>References <a href="Fastftol_8h-source.md#l00018" class="el">fast_round()</a>, <a href="ColorBuf_8h-source.md#l00022" class="el">MAXCOLOR</a>, and <a href="Macros_8h-source.md#l00017" class="el">MIN</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="RGBByte_8h_2d056ec67e496c121db2d7190ad4c64e_cgraph.gif" data-original-image-title="" data-border="0" usemap="#RGBByte_8h_2d056ec67e496c121db2d7190ad4c64e_cgraph_map"></span></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:49 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
