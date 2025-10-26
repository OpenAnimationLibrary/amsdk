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

# TSR Class Reference

`#include <`<a href="Rotate_8h-source.md" class="el"><code>Rotate.h</code></a>`>`

Collaboration diagram for TSR:

<span class="image placeholder" original-image-src="classTSR__coll__graph.gif" original-image-title="" border="0" usemap="#TSR__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classTSR-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTSR.md#76778c3a6f621cd10d92dc726bad0084" class="el">SetDefault</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSR.md#fc46e26a907870744758b76166150f62" class="el">translate</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSR.md#0cb47aeb6e5f9323f0969e628c4e59f5" class="el">scale</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classRotateVector.md" class="el">RotateVector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSR.md#6f8c8a49f740bca52653317a42933f8c" class="el">rotate</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="friends">Friends</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSR.md#e45dbf6bb333be620e633d2f32f6a8fe" class="el">operator!=</a> (const <a href="classTSR.md" class="el">TSR</a> &amp;a, const <a href="classTSR.md" class="el">TSR</a> &amp;b)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="Rotate_8h-source.md#l00080" class="el">80</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="76778c3a6f621cd10d92dc726bad0084" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void TSR::SetDefault</td>
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
<td><p>Definition at line <a href="Rotate_8h-source.md#l00088" class="el">88</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>.</p>
<p>References <a href="Vector_8h-source.md#l00298" class="el">Vector::Set()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classTSR_76778c3a6f621cd10d92dc726bad0084_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classTSR_76778c3a6f621cd10d92dc726bad0084_cgraph_map"></span></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Friends And Related Function Documentation

<span id="e45dbf6bb333be620e633d2f32f6a8fe" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int operator!=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classTSR.md" class="el">TSR</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>a</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classTSR.md" class="el">TSR</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>b</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [friend]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Rotate_8h-source.md#l00086" class="el">86</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>. |

------------------------------------------------------------------------

## Member Data Documentation

<span id="6f8c8a49f740bca52653317a42933f8c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classRotateVector.md" class="el">RotateVector</a> <a href="classTSR.md#6f8c8a49f740bca52653317a42933f8c" class="el">TSR::rotate</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Rotate_8h-source.md#l00084" class="el">84</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>. |

<span id="0cb47aeb6e5f9323f0969e628c4e59f5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> <a href="classTSR.md#0cb47aeb6e5f9323f0969e628c4e59f5" class="el">TSR::scale</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Rotate_8h-source.md#l00083" class="el">83</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>. |

<span id="fc46e26a907870744758b76166150f62" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> <a href="classTSR.md#fc46e26a907870744758b76166150f62" class="el">TSR::translate</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Rotate_8h-source.md#l00082" class="el">82</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="Rotate_8h-source.md" class="el">Rotate.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:04 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
