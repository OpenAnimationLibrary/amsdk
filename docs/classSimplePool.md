<div class="tabs">

- [Main Page](index.md)
- <span id="current">[Classes](annotated.md)</span>
- [Files](files.md)
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [Class List](annotated.md)
- [Alphabetical List](classes.md)
- [Class Hierarchy](hierarchy.md)
- [Class Members](functions.md)

</div>

# SimplePool Class Reference

`#include <`<a href="Allocate_8h-source.md" class="el"><code>Allocate.h</code></a>`>`

Collaboration diagram for SimplePool:

<span class="image placeholder" original-image-src="classSimplePool__coll__graph.gif" original-image-title="" border="0" usemap="#SimplePool__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classSimplePool-members.md)

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
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#f80f1eb2f178ce55e4c3b6f66819a616" class="el">SimplePool</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#e99e5306db341157e7b46509a3644d1c" class="el">~SimplePool</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#c1a36b6050d5609570081ede27b259c4" class="el">Alloc</a> (size_t size)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#49a3e87dfcb34a8dc782243de471bea9" class="el">FreePool</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#723c2e35b3e2fa578261be72c871f300" class="el">Reset</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">size_t </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#a0220381b7ca4bee6ae0bc21b6f8a5fc" class="el">GetTotal</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#53ec6eeccd7f17654dd9c37302676315" class="el">AllocShitLoad</a> (LONG size)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classSimpleChunk.md" class="el">SimpleChunk</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#de025bd11225a5649d6067a7a294cfb8" class="el">m_chunk</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">size_t </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#6c9b5ebae49f49b8b6a037c129428774" class="el">m_total</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">size_t </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#edb9994036741c55a4a4fa6653a7d8bb" class="el">m_amount</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#d69ddb9a1b8e956eada83f688ce2cb2b" class="el">m_ptr</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CCriticalSection </td>
<td class="memItemRight" data-valign="bottom"><a href="classSimplePool.md#ab45ae9b8fc212c509d321bcc78ff75e" class="el">m_criticalsection</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="Allocate_8h-source.md#l00121" class="el">121</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="f80f1eb2f178ce55e4c3b6f66819a616" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">SimplePool::SimplePool</td>
<td class="md" data-valign="top">( </td>
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

<span id="e99e5306db341157e7b46509a3644d1c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">SimplePool::~SimplePool</td>
<td class="md" data-valign="top">( </td>
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

------------------------------------------------------------------------

## Member Function Documentation

<span id="c1a36b6050d5609570081ede27b259c4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void* SimplePool::Alloc</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">size_t </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>size</em></td>
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

<span id="53ec6eeccd7f17654dd9c37302676315" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void SimplePool::AllocShitLoad</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">LONG </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>size</em></td>
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

<span id="49a3e87dfcb34a8dc782243de471bea9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void SimplePool::FreePool</td>
<td class="md" data-valign="top">( </td>
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

<span id="a0220381b7ca4bee6ae0bc21b6f8a5fc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">size_t SimplePool::GetTotal</td>
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

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00139" class="el">139</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="723c2e35b3e2fa578261be72c871f300" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void SimplePool::Reset</td>
<td class="md" data-valign="top">( </td>
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

------------------------------------------------------------------------

## Member Data Documentation

<span id="edb9994036741c55a4a4fa6653a7d8bb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">size_t <a href="classSimplePool.md#edb9994036741c55a4a4fa6653a7d8bb" class="el">SimplePool::m_amount</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00125" class="el">125</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="de025bd11225a5649d6067a7a294cfb8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classSimpleChunk.md" class="el">SimpleChunk</a>* <a href="classSimplePool.md#de025bd11225a5649d6067a7a294cfb8" class="el">SimplePool::m_chunk</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00124" class="el">124</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="ab45ae9b8fc212c509d321bcc78ff75e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">CCriticalSection <a href="classSimplePool.md#ab45ae9b8fc212c509d321bcc78ff75e" class="el">SimplePool::m_criticalsection</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00130" class="el">130</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="d69ddb9a1b8e956eada83f688ce2cb2b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#6df7643c26cd4b455d883d8fae3d6bf1" class="el">UBYTE</a>* <a href="classSimplePool.md#d69ddb9a1b8e956eada83f688ce2cb2b" class="el">SimplePool::m_ptr</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00126" class="el">126</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="6c9b5ebae49f49b8b6a037c129428774" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">size_t <a href="classSimplePool.md#6c9b5ebae49f49b8b6a037c129428774" class="el">SimplePool::m_total</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00125" class="el">125</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="Allocate_8h-source.md" class="el">Allocate.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:03 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
