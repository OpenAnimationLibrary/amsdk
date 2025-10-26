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

# Perlin.h File Reference

`#include "`<a href="Exports_8h-source.md" class="el"><code>Exports.h</code></a>`"`  

Include dependency graph for Perlin.h:

<span class="image placeholder" original-image-src="Perlin_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Perlin.h_map"></span>

[Go to the source code of this file.](Perlin_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#ff73e351cc4e7893b5bb87b22f1e930e" class="el">LERP</a>(t, a, b)   ( a + t * (b - a) )</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#53e6f9d0cd94e8bf6b79b48469431982" class="el">Perturb</a> (const <a href="classVector.md" class="el">Vector</a> &amp;p, <a href="classVector.md" class="el">Vector</a> &amp;delta)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#d120adef0070a473056c1a6062eba86a" class="el">Noise3</a> (const <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#f5325459209a7b9f439dbab956f2fba4" class="el">Contrast</a> (float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#85a41874026763bcfa322bdfcf9a3595" class="el">Brighten</a> (float, float)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#fcd9fa3736b0fdd30a5bd041ddebebf0" class="el">InitPerlinNoise</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#ef0915d76720d18fe04f413d0aa9015a" class="el">FreePerlinNoise</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#203d135e5fab0876eab8a0479296957d" class="el">FractalTurb</a> (const <a href="classVector.md" class="el">Vector</a> &amp;p, int octaves)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="Perlin_8h.md#13c2a0c6a46c67b1614329c3030ba522" class="el">Noise3ForSampling</a> (const <a href="classVector.md" class="el">Vector</a> &amp;)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="ff73e351cc4e7893b5bb87b22f1e930e" class="anchor"></span>

\#define LERP

( 

t,

a,

b 

 ) 

   ( a + t \* (b - a) )

|  |  |
|----|----|
|   | Definition at line <a href="Perlin_8h-source.md#l00007" class="el">7</a> of file <a href="Perlin_8h-source.md" class="el">Perlin.h</a>. |

------------------------------------------------------------------------

## Function Documentation

<span id="85a41874026763bcfa322bdfcf9a3595" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT float Brighten</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="f5325459209a7b9f439dbab956f2fba4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT float Contrast</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="203d135e5fab0876eab8a0479296957d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT float FractalTurb</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>p</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>octaves</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="ef0915d76720d18fe04f413d0aa9015a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT void FreePerlinNoise</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="fcd9fa3736b0fdd30a5bd041ddebebf0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT void InitPerlinNoise</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="d120adef0070a473056c1a6062eba86a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT float Noise3</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="13c2a0c6a46c67b1614329c3030ba522" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT float Noise3ForSampling</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="53e6f9d0cd94e8bf6b79b48469431982" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT void Perturb</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>p</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>delta</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:48 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
