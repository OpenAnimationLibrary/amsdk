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

# HPatch5 Class Reference

Defines a valid 5 point patch. [More...](#_details)

`#include <`<a href="HPatch_8h-source.md" class="el"><code>HPatch.h</code></a>`>`

Inheritance diagram for HPatch5:

<span class="image placeholder" original-image-src="classHPatch5__inherit__graph.gif" original-image-title="" border="0" usemap="#HPatch5__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HPatch5:

<span class="image placeholder" original-image-src="classHPatch5__coll__graph.gif" original-image-title="" border="0" usemap="#HPatch5__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHPatch5-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPatch5.md" class="el">HPatch5</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPatch5.md#3aefc5015037cd7766500ec393ddfe7c" class="el">GetNextPatch5</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPatch5.md#710472d5fefd8fc24370df0ba54af6d6" class="el">GetCP5</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPatch5.md#4737f3399d99c55bb04a5a6106ce37e3" class="el">GetIT5</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPatch5.md#e37a61d52f55d0c92e28ca1db3d53b31" class="el">GetOT5</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classPatchID5.md" class="el">PatchID5</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPatch5.md#696720de90c3aed9cd0adff5a4fac831" class="el">GetPatchID</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPatch5.md#eaa3cea754b6acb01ef4d92329bf9906" class="el">IsFlipV5</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Defines a valid 5 point patch.

**See also:**  
<a href="classHPatch.md" class="el">HPatch</a>

Definition at line <a href="HPatch_8h-source.md#l00109" class="el">109</a> of file <a href="HPatch_8h-source.md" class="el">HPatch.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="710472d5fefd8fc24370df0ba54af6d6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HPatch5::GetCP5</td>
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

|  |  |
|----|----|
|   | Returns a pointer to the fifth <a href="classHCP.md" class="el">HCP</a> in the list of 5 CPs that defines the 5pts patch. |

<span id="4737f3399d99c55bb04a5a6106ce37e3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; HPatch5::GetIT5</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns a <a href="classVector.md" class="el">Vector</a> that is the In tangent to the fifth <a href="classHCP.md" class="el">HCP</a> in the list of 5 CPs that defines the 5pts patch.</p>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#2d63252b29a507b4eca3a0d4768c199e" class="el">HPatch::GetOT1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="3aefc5015037cd7766500ec393ddfe7c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHPatch5.md" class="el">HPatch5</a> * HPatch5::GetNextPatch5</td>
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

|  |  |
|----|----|
|   | Returns a pointer to the next HPatch5 in the list of patches that compose a model. |

<span id="e37a61d52f55d0c92e28ca1db3d53b31" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; HPatch5::GetOT5</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns a <a href="classVector.md" class="el">Vector</a> that is the Out tangent to the fifth <a href="classHCP.md" class="el">HCP</a> in the list of 5 CPs that defines the 5pts patch.</p>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPatch.md#2d63252b29a507b4eca3a0d4768c199e" class="el">HPatch::GetOT1()</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="696720de90c3aed9cd0adff5a4fac831" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classPatchID5.md" class="el">PatchID5</a> HPatch5::GetPatchID</td>
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

|  |  |
|----|----|
|   | Reimplemented from <a href="classHPatch.md#696720de90c3aed9cd0adff5a4fac831" class="el">HPatch</a>. |

<span id="eaa3cea754b6acb01ef4d92329bf9906" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HPatch5::IsFlipV5</td>
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

|  |  |
|----|----|
|   | If TRUE, means that to traverse to the next vertex you must use GetNext() instead of GetPrev() -- the spline is leading to the next vertex instead of back from it. |

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HPatch_8h-source.md" class="el">HPatch.h</a>
- C:/Dox/SDK/Comments/<a href="HPatch_8dox.md" class="el">HPatch.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:56 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
