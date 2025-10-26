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

# xUtils.h File Reference

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="xUtils_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/xUtils.hdep_map"></span>

[Go to the source code of this file.](xUtils_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#c006d84af33c48778a0a668c3763a52e" class="el">TO_DLG</a>   FALSE</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#da2b219361d66f2216b4f66d4c1523a7" class="el">FROM_DLG</a>   TRUE</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#6a0676ee92de31388d6aef835cbbab94" class="el">SwapBytes</a>(x)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#72b5e90b6fc89392dbf364b4f9f63069" class="el">SwapBits</a>(x, y, z)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CString </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#49f081e07ee71bccdff9a1de9974428b" class="el">RandomStr</a> (DWORD min, DWORD max)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">DWORD </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#0be8ef00dbe087578bea618cfad8370a" class="el">RandomInt</a> (DWORD min, DWORD max)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#0053fa5d38853a3371dde5a8e489e3b7" class="el">RandomChar</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#6e68aed3a61e267cc3da3132e15c617b" class="el">SwapBytesX</a> (WORD *pWord)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#2817b1e31641afeab0ede5af8eb04b93" class="el">SwapBytesX</a> (short *pWord)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="xUtils_8h.md#ea341038b17696d79226febeff993825" class="el">SwapBytesX</a> (<a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> *pLong)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="da2b219361d66f2216b4f66d4c1523a7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FROM_DLG   TRUE</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xUtils_8h-source.md#l00023" class="el">23</a> of file <a href="xUtils_8h-source.md" class="el">xUtils.h</a>. |

<span id="72b5e90b6fc89392dbf364b4f9f63069" class="anchor"></span>

\#define SwapBits

( 

x,

y,

z 

 ) 

|  |  |
|----|----|
|   | Definition at line <a href="xUtils_8h-source.md#l00251" class="el">251</a> of file <a href="xUtils_8h-source.md" class="el">xUtils.h</a>. |

<span id="6a0676ee92de31388d6aef835cbbab94" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define SwapBytes</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">x </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xUtils_8h-source.md#l00250" class="el">250</a> of file <a href="xUtils_8h-source.md" class="el">xUtils.h</a>. |

<span id="c006d84af33c48778a0a668c3763a52e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define TO_DLG   FALSE</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xUtils_8h-source.md#l00022" class="el">22</a> of file <a href="xUtils_8h-source.md" class="el">xUtils.h</a>. |

------------------------------------------------------------------------

## Function Documentation

<span id="0053fa5d38853a3371dde5a8e489e3b7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char RandomChar</td>
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

<span id="0be8ef00dbe087578bea618cfad8370a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">DWORD RandomInt</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">DWORD </td>
<td class="mdname" data-nowrap=""><em>min</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">DWORD </td>
<td class="mdname" data-nowrap=""><em>max</em></td>
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

<span id="49f081e07ee71bccdff9a1de9974428b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">CString RandomStr</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">DWORD </td>
<td class="mdname" data-nowrap=""><em>min</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">DWORD </td>
<td class="mdname" data-nowrap=""><em>max</em></td>
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

<span id="ea341038b17696d79226febeff993825" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void SwapBytesX</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>pLong</em></td>
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
|   | Definition at line <a href="xUtils_8h-source.md#l00265" class="el">265</a> of file <a href="xUtils_8h-source.md" class="el">xUtils.h</a>. |

<span id="2817b1e31641afeab0ede5af8eb04b93" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void SwapBytesX</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">short * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>pWord</em></td>
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
|   | Definition at line <a href="xUtils_8h-source.md#l00259" class="el">259</a> of file <a href="xUtils_8h-source.md" class="el">xUtils.h</a>. |

<span id="6e68aed3a61e267cc3da3132e15c617b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void SwapBytesX</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">WORD * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>pWord</em></td>
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
|   | Definition at line <a href="xUtils_8h-source.md#l00253" class="el">253</a> of file <a href="xUtils_8h-source.md" class="el">xUtils.h</a>. |

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:50 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
