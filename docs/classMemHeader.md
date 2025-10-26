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

# MemHeader Class Reference

`#include <`<a href="Allocate_8h-source.md" class="el"><code>Allocate.h</code></a>`>`

Collaboration diagram for MemHeader:

<span class="image placeholder" original-image-src="classMemHeader__coll__graph.gif" original-image-title="" border="0" usemap="#MemHeader__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classMemHeader-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#b958098a280b18c23495db610922ad47" class="el">FindLargestChunk</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMemHeader.md" class="el">MemHeader</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#d0cab90d8d20d57e2f2b9be52f7dd25d" class="el">next</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMemChunk.md" class="el">MemChunk</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#52206b869254dc136b272bd93218e6ca" class="el">m_freehead</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#14511f2f5564650d129ca7cabc333278" class="el">block</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#81e073b428b50247daba38531dcf412a" class="el">lower</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#0122b4c2c01ee1c698ecc309d2b8eb5a" class="el">upper</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">size_t </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#aa2d6e4f578eb0cfaba23beef76c2194" class="el">free</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">size_t </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#f7bd60b75b29d79b660a2859395c1a24" class="el">size</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">size_t </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemHeader.md#d6e15367995842c43d6c059f0cfa086d" class="el">m_largestchunk</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="Allocate_8h-source.md#l00064" class="el">64</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="b958098a280b18c23495db610922ad47" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void MemHeader::FindLargestChunk</td>
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

<span id="14511f2f5564650d129ca7cabc333278" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char* <a href="classMemHeader.md#14511f2f5564650d129ca7cabc333278" class="el">MemHeader::block</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00071" class="el">71</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="aa2d6e4f578eb0cfaba23beef76c2194" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">size_t <a href="classMemHeader.md#aa2d6e4f578eb0cfaba23beef76c2194" class="el">MemHeader::free</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00074" class="el">74</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="81e073b428b50247daba38531dcf412a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char* <a href="classMemHeader.md#81e073b428b50247daba38531dcf412a" class="el">MemHeader::lower</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00072" class="el">72</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="52206b869254dc136b272bd93218e6ca" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMemChunk.md" class="el">MemChunk</a>* <a href="classMemHeader.md#52206b869254dc136b272bd93218e6ca" class="el">MemHeader::m_freehead</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00067" class="el">67</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="d6e15367995842c43d6c059f0cfa086d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">size_t <a href="classMemHeader.md#d6e15367995842c43d6c059f0cfa086d" class="el">MemHeader::m_largestchunk</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00074" class="el">74</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="d0cab90d8d20d57e2f2b9be52f7dd25d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMemHeader.md" class="el">MemHeader</a>* <a href="classMemHeader.md#d0cab90d8d20d57e2f2b9be52f7dd25d" class="el">MemHeader::next</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00066" class="el">66</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="f7bd60b75b29d79b660a2859395c1a24" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">size_t <a href="classMemHeader.md#f7bd60b75b29d79b660a2859395c1a24" class="el">MemHeader::size</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00074" class="el">74</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

<span id="0122b4c2c01ee1c698ecc309d2b8eb5a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char* <a href="classMemHeader.md#0122b4c2c01ee1c698ecc309d2b8eb5a" class="el">MemHeader::upper</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Allocate_8h-source.md#l00073" class="el">73</a> of file <a href="Allocate_8h-source.md" class="el">Allocate.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="Allocate_8h-source.md" class="el">Allocate.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:00 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
