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

# HashArra.h File Reference

`#include "`<a href="Allocate_8h-source.md" class="el"><code>Allocate.h</code></a>`"`  

Include dependency graph for HashArra.h:

<span class="image placeholder" original-image-src="HashArra_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/HashArra.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="HashArra_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/HashArra.hdep_map"></span>

[Go to the source code of this file.](HashArra_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void *__cdecl </td>
<td class="memItemRight" data-valign="bottom"><a href="HashArra_8h.md#1b60c2a5d043d2ccc3f19b11dbd8e1c3" class="el">operator new</a> (size_t, void *_P)</td>
</tr>
<tr>
<td colspan="2" class="memTemplParams" data-nowrap="">template&lt;class TYPE&gt;</td>
</tr>
<tr>
<td class="memTemplItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void AFXAPI </td>
<td class="memTemplItemRight" data-valign="bottom"><a href="HashArra_8h.md#e496382051f1be1ffdb2c8d806c7a6cc" class="el">HashConstructElements</a> (TYPE *pElements, int nCount)</td>
</tr>
<tr>
<td colspan="2" class="memTemplParams" data-nowrap="">template&lt;class TYPE&gt;</td>
</tr>
<tr>
<td class="memTemplItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void AFXAPI </td>
<td class="memTemplItemRight" data-valign="bottom"><a href="HashArra_8h.md#2317428b5f69c30ced46e957380bf34d" class="el">HashDestructElements</a> (TYPE *pElements, int nCount)</td>
</tr>
<tr>
<td colspan="2" class="memTemplParams" data-nowrap="">template&lt;class TYPE&gt;</td>
</tr>
<tr>
<td class="memTemplItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memTemplItemRight" data-valign="bottom"><a href="HashArra_8h.md#6440bab64308bfbd7f68a055d05f367e" class="el">ConstructTheElements</a> (TYPE *pElements, int count)</td>
</tr>
<tr>
<td colspan="2" class="memTemplParams" data-nowrap="">template&lt;class TYPE&gt;</td>
</tr>
<tr>
<td class="memTemplItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memTemplItemRight" data-valign="bottom"><a href="HashArra_8h.md#4ea54257bbc2986cd2c020017db5fb54" class="el">DestructTheElements</a> (TYPE *pElements, int count)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Function Documentation

<span id="6440bab64308bfbd7f68a055d05f367e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE&gt;</td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">void ConstructTheElements</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">TYPE * </td>
<td class="mdname" data-nowrap=""><em>pElements</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>count</em></td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00049" class="el">49</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>Referenced by <a href="HashArra_8h-source.md#l00151" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::SetSize()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="4ea54257bbc2986cd2c020017db5fb54" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE&gt;</td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">void DestructTheElements</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">TYPE * </td>
<td class="mdname" data-nowrap=""><em>pElements</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>count</em></td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00058" class="el">58</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>Referenced by <a href="HashArra_8h-source.md#l00151" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::SetSize()</a>, and <a href="HashArra_8h-source.md#l00142" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::~HashArray()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="e496382051f1be1ffdb2c8d806c7a6cc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE&gt;</td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">void AFXAPI HashConstructElements</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">TYPE * </td>
<td class="mdname" data-nowrap=""><em>pElements</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>nCount</em></td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00024" class="el">24</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>Referenced by <a href="HashArra_8h-source.md#l00228" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::InsertAt()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="2317428b5f69c30ced46e957380bf34d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td colspan="4" class="mdPrefix">template&lt;class TYPE&gt;</td>
</tr>
<tr>
<td class="md" data-nowrap="" data-valign="top">void AFXAPI HashDestructElements</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">TYPE * </td>
<td class="mdname" data-nowrap=""><em>pElements</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>nCount</em></td>
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
<td><p>Definition at line <a href="HashArra_8h-source.md#l00038" class="el">38</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>.</p>
<p>Referenced by <a href="HashArra_8h-source.md#l00228" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::InsertAt()</a>, <a href="HashArra_8h-source.md#l00294" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::Pop()</a>, and <a href="HashArra_8h-source.md#l00270" class="el">HashArray&lt; TYPE, ARG_TYPE &gt;::RemoveAt()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="1b60c2a5d043d2ccc3f19b11dbd8e1c3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void* __cdecl operator new</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">size_t </td>
<td class="mdname" data-nowrap="">,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">void * </td>
<td class="mdname" data-nowrap=""><em>_P</em></td>
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

|  |  |
|----|----|
|   | Definition at line <a href="HashArra_8h-source.md#l00014" class="el">14</a> of file <a href="HashArra_8h-source.md" class="el">HashArra.h</a>. |

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:47 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
