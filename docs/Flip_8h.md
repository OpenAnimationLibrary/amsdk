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

# Flip.h File Reference

`#include "`<a href="DataType_8h-source.md" class="el"><code>DataType.h</code></a>`"`  

Include dependency graph for Flip.h:

<span class="image placeholder" original-image-src="Flip_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Flip.h_map"></span>

[Go to the source code of this file.](Flip_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="Flip_8h.md#4df1e2e6c815ffa45250dfcee14c3b20" class="el">__FLIP_H</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Flip_8h.md#59c9d6ae80d66f8e67316116e49d3cf8" class="el">FlipShort</a> (<a href="DataType_8h.md#a35c2b02966b1563e5bf7b81b8b0cf77" class="el">SHORT</a> *short_ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Flip_8h.md#eae9e325f1597866206af30b22317ba4" class="el">FlipLong</a> (LONG *long_ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Flip_8h.md#a30815e836eff11765f46dbef534267f" class="el">FlipShort68k</a> (short *short_ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Flip_8h.md#9c1fa2655435724c979ede798c10752a" class="el">FlipLong68k</a> (<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *long_ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Flip_8h.md#99c0b0628e387234f5a8b4ee28f92583" class="el">ReverseBytes</a> (void *<a href="structTQAVGouraud.md" class="el">v</a>, int size)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Flip_8h.md#00ffe5b25e4dfecab95e407d8d46f779" class="el">FlipDouble68k</a> (double *double_ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Flip_8h.md#a339a541fa36bdfe88079c124d4c98a4" class="el">FlipLongBits</a> (<a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> *ptr)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="4df1e2e6c815ffa45250dfcee14c3b20" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __FLIP_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Flip_8h-source.md#l00003" class="el">3</a> of file <a href="Flip_8h-source.md" class="el">Flip.h</a>. |

------------------------------------------------------------------------

## Function Documentation

<span id="00ffe5b25e4dfecab95e407d8d46f779" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void FlipDouble68k</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">double * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>double_ptr</em></td>
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
<td><p>Definition at line <a href="Flip_8h-source.md#l00066" class="el">66</a> of file <a href="Flip_8h-source.md" class="el">Flip.h</a>.</p>
<p>References <a href="Flip_8h-source.md#l00051" class="el">ReverseBytes()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Flip_8h_00ffe5b25e4dfecab95e407d8d46f779_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Flip_8h_00ffe5b25e4dfecab95e407d8d46f779_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="eae9e325f1597866206af30b22317ba4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void FlipLong</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">LONG * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>long_ptr</em></td>
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
|   | Definition at line <a href="Flip_8h-source.md#l00019" class="el">19</a> of file <a href="Flip_8h-source.md" class="el">Flip.h</a>. |

<span id="9c1fa2655435724c979ede798c10752a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void FlipLong68k</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>long_ptr</em></td>
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
|   | Definition at line <a href="Flip_8h-source.md#l00040" class="el">40</a> of file <a href="Flip_8h-source.md" class="el">Flip.h</a>. |

<span id="a339a541fa36bdfe88079c124d4c98a4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void FlipLongBits</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>ptr</em></td>
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
|   | Definition at line <a href="Flip_8h-source.md#l00073" class="el">73</a> of file <a href="Flip_8h-source.md" class="el">Flip.h</a>. |

<span id="59c9d6ae80d66f8e67316116e49d3cf8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void FlipShort</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#a35c2b02966b1563e5bf7b81b8b0cf77" class="el">SHORT</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>short_ptr</em></td>
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
|   | Definition at line <a href="Flip_8h-source.md#l00009" class="el">9</a> of file <a href="Flip_8h-source.md" class="el">Flip.h</a>. |

<span id="a30815e836eff11765f46dbef534267f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void FlipShort68k</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">short * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>short_ptr</em></td>
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
|   | Definition at line <a href="Flip_8h-source.md#l00030" class="el">30</a> of file <a href="Flip_8h-source.md" class="el">Flip.h</a>. |

<span id="99c0b0628e387234f5a8b4ee28f92583" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void ReverseBytes</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void * </td>
<td class="mdname" data-nowrap=""><em>v</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>size</em></td>
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
<td><p>Definition at line <a href="Flip_8h-source.md#l00051" class="el">51</a> of file <a href="Flip_8h-source.md" class="el">Flip.h</a>.</p>
<p>Referenced by <a href="Flip_8h-source.md#l00066" class="el">FlipDouble68k()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:47 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
