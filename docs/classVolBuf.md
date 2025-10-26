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

# VolBuf Class Reference

`#include <`<a href="Volbuf_8h-source.md" class="el"><code>Volbuf.h</code></a>`>`

Collaboration diagram for VolBuf:

<span class="image placeholder" original-image-src="classVolBuf__coll__graph.gif" original-image-title="" border="0" usemap="#VolBuf__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classVolBuf-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classVolBuf.md#06f62341245d2bcea8e28affbb1d88cd" class="el">VolBuf</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVolBuf.md" class="el">VolBuf</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVolBuf.md#9003df30d4757a561897bc83d22a53cc" class="el">operator=</a> (const <a href="classVolBuf.md" class="el">VolBuf</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="classVolBuf.md#7a0e253c51031f467e04fa43c1a43c7d" class="el">GetTurbulenceValue</a> (const <a href="classVector.md" class="el">Vector</a> &amp;turbp)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="classVolBuf.md#9d1b5f37c7e3a27fcdd8ba8b248d8cf9" class="el">GetFallOffValue</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="classVolBuf.md#83878c91171338902e0fe0fb97a8c47a" class="el">p</a>)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classVolBuf.md#83878c91171338902e0fe0fb97a8c47a" class="el">p</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classVolBuf.md#96e9998f902ae3b77d6d213b4f5b43ba" class="el">worldp</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TurbulenceNode * </td>
<td class="memItemRight" data-valign="bottom"><a href="classVolBuf.md#4285a52ed6f19068594bbbfe0476ec08" class="el">turbnodehead</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classInfluenceShape.md" class="el">InfluenceShape</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classVolBuf.md#45d909320decdf3a4f32ef8dba3c1071" class="el">influenceshape</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="Volbuf_8h-source.md#l00014" class="el">14</a> of file <a href="Volbuf_8h-source.md" class="el">Volbuf.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="06f62341245d2bcea8e28affbb1d88cd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">VolBuf::VolBuf</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Definition at line <a href="Volbuf_8h-source.md#l00020" class="el">20</a> of file <a href="Volbuf_8h-source.md" class="el">Volbuf.h</a>.</p>
<p>References <a href="Volbuf_8h-source.md#l00018" class="el">influenceshape</a>, and <a href="Volbuf_8h-source.md#l00017" class="el">turbnodehead</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Function Documentation

<span id="9d1b5f37c7e3a27fcdd8ba8b248d8cf9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT float VolBuf::GetFallOffValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>p</em></td>
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

<span id="7a0e253c51031f467e04fa43c1a43c7d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT float VolBuf::GetTurbulenceValue</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>turbp</em></td>
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

<span id="9003df30d4757a561897bc83d22a53cc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVolBuf.md" class="el">VolBuf</a>&amp; VolBuf::operator=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVolBuf.md" class="el">VolBuf</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>other</em></td>
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
|   | Definition at line <a href="Volbuf_8h-source.md#l00022" class="el">22</a> of file <a href="Volbuf_8h-source.md" class="el">Volbuf.h</a>. |

------------------------------------------------------------------------

## Member Data Documentation

<span id="45d909320decdf3a4f32ef8dba3c1071" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classInfluenceShape.md" class="el">InfluenceShape</a>* <a href="classVolBuf.md#45d909320decdf3a4f32ef8dba3c1071" class="el">VolBuf::influenceshape</a></td>
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
<td><p>Definition at line <a href="Volbuf_8h-source.md#l00018" class="el">18</a> of file <a href="Volbuf_8h-source.md" class="el">Volbuf.h</a>.</p>
<p>Referenced by <a href="Volbuf_8h-source.md#l00020" class="el">VolBuf()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="83878c91171338902e0fe0fb97a8c47a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> <a href="classVolBuf.md#83878c91171338902e0fe0fb97a8c47a" class="el">VolBuf::p</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Volbuf_8h-source.md#l00016" class="el">16</a> of file <a href="Volbuf_8h-source.md" class="el">Volbuf.h</a>. |

<span id="4285a52ed6f19068594bbbfe0476ec08" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">TurbulenceNode* <a href="classVolBuf.md#4285a52ed6f19068594bbbfe0476ec08" class="el">VolBuf::turbnodehead</a></td>
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
<td><p>Definition at line <a href="Volbuf_8h-source.md#l00017" class="el">17</a> of file <a href="Volbuf_8h-source.md" class="el">Volbuf.h</a>.</p>
<p>Referenced by <a href="Volbuf_8h-source.md#l00020" class="el">VolBuf()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="96e9998f902ae3b77d6d213b4f5b43ba" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> <a href="classVolBuf.md#96e9998f902ae3b77d6d213b4f5b43ba" class="el">VolBuf::worldp</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Volbuf_8h-source.md#l00016" class="el">16</a> of file <a href="Volbuf_8h-source.md" class="el">Volbuf.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="Volbuf_8h-source.md" class="el">Volbuf.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:07 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
