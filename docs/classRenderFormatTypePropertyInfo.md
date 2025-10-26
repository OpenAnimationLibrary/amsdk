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

# RenderFormatTypePropertyInfo Class Reference

`#include <`<a href="RenderS2_8h-source.md" class="el"><code>RenderS2.h</code></a>`>`

[List of all members.](classRenderFormatTypePropertyInfo-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classRenderFormatTypePropertyInfo.md#394f21a9815040c27bacaa060546c21f" class="el">RenderFormatTypePropertyInfo</a> (UINT index, char *documentation, UINT stringid, TypeInfo typearray[], UINT count, const <a href="classLabel.md" class="el">Label</a> &amp;label, UINT defaultindex=0, DrawWhen drawwhen=DRAWALWAYS, VisibleWhen visiblewhen=VISIBLEALWAYS, UINT type=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classRenderFormatTypePropertyInfo.md#c0f3f11ba2cb2a06726b90551e0a3c9e" class="el">Save</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs, BOOL isforcesave)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classRenderFormatTypePropertyInfo.md#a2fcc48f12ddead20de0eb7243ed5aee" class="el">ParseArg</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs, <a href="classHashStream.md" class="el">HashStream</a> &amp;ms, LONG id)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="RenderS2_8h-source.md#l00277" class="el">277</a> of file <a href="RenderS2_8h-source.md" class="el">RenderS2.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="394f21a9815040c27bacaa060546c21f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">RenderFormatTypePropertyInfo::RenderFormatTypePropertyInfo</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">UINT </td>
<td class="mdname" data-nowrap=""><em>index</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">char * </td>
<td class="mdname" data-nowrap=""><em>documentation</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>stringid</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">TypeInfo </td>
<td class="mdname" data-nowrap=""><em>typearray</em>[],</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>count</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classLabel.md" class="el">Label</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>label</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>defaultindex</em> = <code>0</code>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">DrawWhen </td>
<td class="mdname" data-nowrap=""><em>drawwhen</em> = <code>DRAWALWAYS</code>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">VisibleWhen </td>
<td class="mdname" data-nowrap=""><em>visiblewhen</em> = <code>VISIBLEALWAYS</code>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>type</em> = <code>0</code></td>
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
|   | Definition at line <a href="RenderS2_8h-source.md#l00280" class="el">280</a> of file <a href="RenderS2_8h-source.md" class="el">RenderS2.h</a>. |

------------------------------------------------------------------------

## Member Function Documentation

<span id="a2fcc48f12ddead20de0eb7243ed5aee" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual int RenderFormatTypePropertyInfo::ParseArg</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>hs</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>ms</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">LONG </td>
<td class="mdname" data-nowrap=""><em>id</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="c0f3f11ba2cb2a06726b90551e0a3c9e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL RenderFormatTypePropertyInfo::Save</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHashStream.md" class="el">HashStream</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>hs</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">BOOL </td>
<td class="mdname" data-nowrap=""><em>isforcesave</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [virtual]</code></td>
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

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="RenderS2_8h-source.md" class="el">RenderS2.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:02 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
