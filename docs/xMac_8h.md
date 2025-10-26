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

# xMac.h File Reference

`#include <afxwin.h>`  
`#include <afxext.h>`  
`#include <mmsystem.h>`  
`#include <vfw.h>`  
`#include <io.h>`  
`#include <direct.h>`  
`#include <`<a href="xMfcExt_8h-source.md" class="el"><code>xMfcExt.h</code></a>`>`  

Include dependency graph for xMac.h:

<span class="image placeholder" original-image-src="xMac_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/xMac.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="xMac_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/xMac.hdep_map"></span>

[Go to the source code of this file.](xMac_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="xMac_8h.md#313b9beb293e20463353a09fbdb5fcf5" class="el">XMAC_API</a>   AFX_EXT_API</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xMac_8h.md#be973f3b9cd0f96efe06caeae575e65a" class="el">XMAC_CLASS</a>   AFX_EXT_CLASS</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xMac_8h.md#8b6b863089b8d510e0aed08ecb63ffde" class="el">_CPX_LIB</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xMac_8h.md#9e8a7dc0ef08d28155c9a3c5f288185d" class="el">FREE_MEMORY</a>(mem)   if(mem) { free(mem); mem = 0; }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xMac_8h.md#6911bd865119e1eb21c02af5ad598ccc" class="el">DELETE_OBJECT</a>(obj)   if(obj) { delete obj; obj = 0; }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xMac_8h.md#d072750a9baf66f22ca21dd432b29df2" class="el">DELETE_ARRAY</a>(obj)   if(obj) { delete [] obj; obj = 0; }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="xMac_8h.md#1f90fc3644053f66ceeccf45d78e6fc0" class="el">DELETE_GDIOBJ</a>(obj)   if(obj) { DeleteObject(obj); obj = 0; }</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="8b6b863089b8d510e0aed08ecb63ffde" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define _CPX_LIB</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xMac_8h-source.md#l00025" class="el">25</a> of file <a href="xMac_8h-source.md" class="el">xMac.h</a>. |

<span id="d072750a9baf66f22ca21dd432b29df2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define DELETE_ARRAY</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">obj </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   if(obj) { delete [] obj; obj = 0; }</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xMac_8h-source.md#l00029" class="el">29</a> of file <a href="xMac_8h-source.md" class="el">xMac.h</a>. |

<span id="1f90fc3644053f66ceeccf45d78e6fc0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define DELETE_GDIOBJ</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">obj </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   if(obj) { DeleteObject(obj); obj = 0; }</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xMac_8h-source.md#l00030" class="el">30</a> of file <a href="xMac_8h-source.md" class="el">xMac.h</a>. |

<span id="6911bd865119e1eb21c02af5ad598ccc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define DELETE_OBJECT</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">obj </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   if(obj) { delete obj; obj = 0; }</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xMac_8h-source.md#l00028" class="el">28</a> of file <a href="xMac_8h-source.md" class="el">xMac.h</a>. |

<span id="9e8a7dc0ef08d28155c9a3c5f288185d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define FREE_MEMORY</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">mem </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">   if(mem) { free(mem); mem = 0; }</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xMac_8h-source.md#l00027" class="el">27</a> of file <a href="xMac_8h-source.md" class="el">xMac.h</a>. |

<span id="313b9beb293e20463353a09fbdb5fcf5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define XMAC_API   AFX_EXT_API</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xMac_8h-source.md#l00021" class="el">21</a> of file <a href="xMac_8h-source.md" class="el">xMac.h</a>. |

<span id="be973f3b9cd0f96efe06caeae575e65a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define XMAC_CLASS   AFX_EXT_CLASS</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="xMac_8h-source.md#l00022" class="el">22</a> of file <a href="xMac_8h-source.md" class="el">xMac.h</a>. |

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:50 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
