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

# PatchID5 Class Reference

`#include <`<a href="PatchID_8h-source.md" class="el"><code>PatchID.h</code></a>`>`

Inheritance diagram for PatchID5:

<span class="image placeholder" original-image-src="classPatchID5__inherit__graph.gif" original-image-title="" border="0" usemap="#PatchID5__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for PatchID5:

<span class="image placeholder" original-image-src="classPatchID5__coll__graph.gif" original-image-title="" border="0" usemap="#PatchID5__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classPatchID5-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classPatchID5.md#2f6e58cbb09b55f6d134454b5fe0d03a" class="el">PatchID5</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchID5.md#873b0fed072730b62bc1a827cb9bdc89" class="el">PatchID5</a> (UINT id1, UINT id2, UINT id3, UINT id4, UINT id5)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchID5.md#ef517b326757b71623f5708cd039e6e2" class="el">operator==</a> (const <a href="classPatchID5.md" class="el">PatchID5</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classPatchID5.md" class="el">PatchID5</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchID5.md#672098e03b7154cd19a49fda38c8f690" class="el">operator=</a> (const <a href="classPatchID.md" class="el">PatchID</a> &amp;other)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classPatchID5.md#aede70a150f458fcb7f75b7c0be84cf5" class="el">m_id5</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="PatchID_8h-source.md#l00033" class="el">33</a> of file <a href="PatchID_8h-source.md" class="el">PatchID.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="2f6e58cbb09b55f6d134454b5fe0d03a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PatchID5::PatchID5</td>
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
|   | Definition at line <a href="PatchID_8h-source.md#l00037" class="el">37</a> of file <a href="PatchID_8h-source.md" class="el">PatchID.h</a>. |

<span id="873b0fed072730b62bc1a827cb9bdc89" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PatchID5::PatchID5</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">UINT </td>
<td class="mdname" data-nowrap=""><em>id1</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>id2</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>id3</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>id4</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>id5</em></td>
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
<td><p>Definition at line <a href="PatchID_8h-source.md#l00038" class="el">38</a> of file <a href="PatchID_8h-source.md" class="el">PatchID.h</a>.</p>
<p>References <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id1</a>, <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id2</a>, <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id3</a>, <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id4</a>, and <a href="PatchID_8h-source.md#l00035" class="el">m_id5</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Function Documentation

<span id="672098e03b7154cd19a49fda38c8f690" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classPatchID5.md" class="el">PatchID5</a>&amp; PatchID5::operator=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classPatchID.md" class="el">PatchID</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>other</em></td>
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
<td><p>Definition at line <a href="PatchID_8h-source.md#l00056" class="el">56</a> of file <a href="PatchID_8h-source.md" class="el">PatchID.h</a>.</p>
<p>References <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id1</a>, <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id2</a>, <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id3</a>, and <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id4</a>.</p></td>
</tr>
</tbody>
</table>

<span id="ef517b326757b71623f5708cd039e6e2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL PatchID5::operator==</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classPatchID5.md" class="el">PatchID5</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>other</em></td>
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
<td><p>Definition at line <a href="PatchID_8h-source.md#l00047" class="el">47</a> of file <a href="PatchID_8h-source.md" class="el">PatchID.h</a>.</p>
<p>References <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id1</a>, <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id2</a>, <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id3</a>, <a href="PatchID_8h-source.md#l00012" class="el">PatchID::m_id4</a>, and <a href="PatchID_8h-source.md#l00035" class="el">m_id5</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Data Documentation

<span id="aede70a150f458fcb7f75b7c0be84cf5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> <a href="classPatchID5.md#aede70a150f458fcb7f75b7c0be84cf5" class="el">PatchID5::m_id5</a></td>
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
<td><p>Definition at line <a href="PatchID_8h-source.md#l00035" class="el">35</a> of file <a href="PatchID_8h-source.md" class="el">PatchID.h</a>.</p>
<p>Referenced by <a href="PatchID_8h-source.md#l00047" class="el">operator==()</a>, and <a href="PatchID_8h-source.md#l00038" class="el">PatchID5()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="PatchID_8h-source.md" class="el">PatchID.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:01 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
