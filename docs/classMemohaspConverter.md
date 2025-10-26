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

# MemohaspConverter Class Reference

`#include <`<a href="Timehasp_8h-source.md" class="el"><code>Timehasp.h</code></a>`>`

Collaboration diagram for MemohaspConverter:

<span class="image placeholder" original-image-src="classMemohaspConverter__coll__graph.gif" original-image-title="" border="0" usemap="#MemohaspConverter__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classMemohaspConverter-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md#f2444cade762ecfa849245db43a86046" class="el">MemohaspConverter</a> (const <a href="classTimeHasp.md" class="el">TimeHasp</a> &amp;key)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md#ddc8ba617c04b521a8fd13609aa21b5b" class="el">~MemohaspConverter</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md#159aab9a056e5a5a2531a328d834241f" class="el">operator bool</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HASP_EXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md#a965883961563262207f6156a0f1496c" class="el">Restore</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-member-functions">Private Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md#eb9b4f06e929d66209faef3769e79d05" class="el">MemohaspConverter</a> (const <a href="classMemohaspConverter.md" class="el">MemohaspConverter</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMemohaspConverter.md" class="el">MemohaspConverter</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md#df960baf4f136d5857a27760424766e1" class="el">operator=</a> (const <a href="classMemohaspConverter.md" class="el">MemohaspConverter</a> &amp;)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-attributes">Private Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classTimeHasp.md" class="el">TimeHasp</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md#326c06328813b0030847b99a605990f3" class="el">pkey</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">bool </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md#befde6e50dbc157f3963dde221712959" class="el">converted</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="Timehasp_8h-source.md#l00085" class="el">85</a> of file <a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="f2444cade762ecfa849245db43a86046" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">HASP_EXPORT MemohaspConverter::MemohaspConverter</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classTimeHasp.md" class="el">TimeHasp</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>key</em></td>
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

<span id="ddc8ba617c04b521a8fd13609aa21b5b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">HASP_EXPORT MemohaspConverter::~MemohaspConverter</td>
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

<span id="eb9b4f06e929d66209faef3769e79d05" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">MemohaspConverter::MemohaspConverter</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classMemohaspConverter.md" class="el">MemohaspConverter</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [private]</code></td>
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

<span id="159aab9a056e5a5a2531a328d834241f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">MemohaspConverter::operator bool</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const<code> [inline]</code></td>
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
<td><p>Definition at line <a href="Timehasp_8h-source.md#l00093" class="el">93</a> of file <a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>.</p>
<p>References <a href="Timehasp_8h-source.md#l00102" class="el">converted</a>.</p></td>
</tr>
</tbody>
</table>

<span id="df960baf4f136d5857a27760424766e1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classMemohaspConverter.md" class="el">MemohaspConverter</a>&amp; MemohaspConverter::operator=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classMemohaspConverter.md" class="el">MemohaspConverter</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [private]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="a965883961563262207f6156a0f1496c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">HASP_EXPORT void MemohaspConverter::Restore</td>
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

<span id="befde6e50dbc157f3963dde221712959" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">bool <a href="classMemohaspConverter.md#befde6e50dbc157f3963dde221712959" class="el">MemohaspConverter::converted</a><code> [private]</code></td>
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
<td><p>Definition at line <a href="Timehasp_8h-source.md#l00102" class="el">102</a> of file <a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>.</p>
<p>Referenced by <a href="Timehasp_8h-source.md#l00093" class="el">operator bool()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="326c06328813b0030847b99a605990f3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">const <a href="classTimeHasp.md" class="el">TimeHasp</a>* <a href="classMemohaspConverter.md#326c06328813b0030847b99a605990f3" class="el">MemohaspConverter::pkey</a><code> [private]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Timehasp_8h-source.md#l00101" class="el">101</a> of file <a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:00 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
