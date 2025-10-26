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

# HProject Class Reference

`#include <`<a href="HProject_8h-source.md" class="el"><code>HProject.h</code></a>`>`

Inheritance diagram for HProject:

<span class="image placeholder" original-image-src="classHProject__inherit__graph.gif" original-image-title="" border="0" usemap="#HProject__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HProject:

<span class="image placeholder" original-image-src="classHProject__coll__graph.gif" original-image-title="" border="0" usemap="#HProject__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHProject-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#f75eb1966cf590131ff7dd48a1efb58b" class="el">GetFPS</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHObjectCacheContainer.md" class="el">HObjectCacheContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#3dbd0ec4d4d3cd42582654935125b876" class="el">GetChildObjectCacheContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHClipCacheContainer.md" class="el">HClipCacheContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#5b0bf418fc07e0e581eb3290f8982e9f" class="el">GetChildClipCacheContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHMaterialCacheContainer.md" class="el">HMaterialCacheContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#52f003383b557df15780e435166e1dc8" class="el">GetChildMaterialCacheContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHActionCacheContainer.md" class="el">HActionCacheContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#4527f510a2c2745187ed70404d5a61af" class="el">GetChildActionCacheContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHChorContainer.md" class="el">HChorContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#0b74b2b9ceb1851b4e619a5dc1cc8c1d" class="el">GetChildChorContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHClip.md" class="el">HClip</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#3b1aec4d87f1cb57c9c6f0750a4ca885" class="el">AddClip</a> (const <a href="classString.md" class="el">String</a> &amp;filename, BOOL issequence)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#334df6f17d7464715bbb7ac48ceabb91" class="el">DeselectAll</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#434480fdb3c0c105e6cc0569f3e14c84" class="el">SetTime</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHProject.md#b79517715dc3d93ea57e73b26f15d410" class="el">UpdateAllViews</a> (BOOL force=FALSE)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="HProject_8h-source.md#l00083" class="el">83</a> of file <a href="HProject_8h-source.md" class="el">HProject.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="3b1aec4d87f1cb57c9c6f0750a4ca885" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHClip.md" class="el">HClip</a> * HProject::AddClip</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>filename</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">BOOL </td>
<td class="mdname" data-nowrap=""><em>issequence</em></td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Adds a Image or Animation file to the "Images" folder.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>filename</em> </td>
<td>- File name of the image or animation.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>issequence</em> </td>
<td>- when TRUE, allows sequential number images to be treated as an animation.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Returns:</strong></dt>
<dd>
pointer to the newly added clip.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="334df6f17d7464715bbb7ac48ceabb91" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HProject::DeselectAll</td>
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

<span id="4527f510a2c2745187ed70404d5a61af" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHActionCacheContainer.md" class="el">HActionCacheContainer</a>* HProject::GetChildActionCacheContainer</td>
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

<span id="0b74b2b9ceb1851b4e619a5dc1cc8c1d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHChorContainer.md" class="el">HChorContainer</a>* HProject::GetChildChorContainer</td>
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

<span id="5b0bf418fc07e0e581eb3290f8982e9f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHClipCacheContainer.md" class="el">HClipCacheContainer</a> * HProject::GetChildClipCacheContainer</td>
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

|     |                          |
|-----|--------------------------|
|     | Gets the "Images" folder |

<span id="52f003383b557df15780e435166e1dc8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHMaterialCacheContainer.md" class="el">HMaterialCacheContainer</a> * HProject::GetChildMaterialCacheContainer</td>
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

|     |                             |
|-----|-----------------------------|
|     | Gets the "Materials" folder |

<span id="3dbd0ec4d4d3cd42582654935125b876" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHObjectCacheContainer.md" class="el">HObjectCacheContainer</a>* HProject::GetChildObjectCacheContainer</td>
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

<span id="f75eb1966cf590131ff7dd48a1efb58b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HProject::GetFPS</td>
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

<span id="434480fdb3c0c105e6cc0569f3e14c84" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HProject::SetTime</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>time</em></td>
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

<span id="b79517715dc3d93ea57e73b26f15d410" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HProject::UpdateAllViews</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BOOL </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>force</em> = <code>FALSE</code></td>
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

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HProject_8h-source.md" class="el">HProject.h</a>
- C:/Dox/SDK/Comments/<a href="Project_8dox.md" class="el">Project.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:57 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
