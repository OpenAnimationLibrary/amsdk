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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2FSDK_2F.md" class="el">SDK</a>

</div>

# HHashObj.h File Reference

`#include "`<a href="HashTime_8h-source.md" class="el"><code>HashTime.h</code></a>`"`  
`#include "`<a href="Quaterni_8h-source.md" class="el"><code>Quaterni.h</code></a>`"`  
`#include "`<a href="Rotate_8h-source.md" class="el"><code>Rotate.h</code></a>`"`  
`#include "`<a href="PatchID_8h-source.md" class="el"><code>PatchID.h</code></a>`"`  
`#include "`<a href="RGBFloat_8h-source.md" class="el"><code>RGBFloat.h</code></a>`"`  
`#include "`<a href="ObjType_8h-source.md" class="el"><code>ObjType.h</code></a>`"`  
`#include "`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`"`  
`#include "`<a href="TimeRang_8h-source.md" class="el"><code>TimeRang.h</code></a>`"`  

Include dependency graph for HHashObj.h:

<span class="image placeholder" original-image-src="HHashObj_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/SDK/HHashObj.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="HHashObj_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/SDK/HHashObj.hdep_map"></span>

[Go to the source code of this file.](HHashObj_8h-source.md)

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
&#10;<h2 id="classes">Classes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md" class="el">HTreeObject</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">The father class of about all objects in Animation Master. <a href="classHTreeObject.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md" class="el">HAnimObject</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">The father class of about all animatable objects in Animation Master. <a href="classHAnimObject.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHHashObject.md" class="el">HHashObject</a></td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">Father class for all hierarchical collections of Hash objects. <a href="classHHashObject.md#_details">More...</a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObjectShortcut.md" class="el">HAnimObjectShortcut</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HHashObj_8h.md#7055cd58556177dbae63e2f1fbf502f8" class="el">__HHASHOBJ_H</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{ <a href="HHashObj_8h.md#dca29a1140aadadfd92b34a02fa516ef653dc2bd11c615cb4f219a4d1830c5db" class="el">SMPTE</a>, <a href="HHashObj_8h.md#dca29a1140aadadfd92b34a02fa516ef036429f7a46a17439207d188e46ca840" class="el">FRAMES</a>, <a href="HHashObj_8h.md#dca29a1140aadadfd92b34a02fa516efcd7c76bbb327f87b097bbfe3c3f0efe5" class="el">CELS</a> }</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="7055cd58556177dbae63e2f1fbf502f8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __HHASHOBJ_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="HHashObj_8h-source.md#l00003" class="el">3</a> of file <a href="HHashObj_8h-source.md" class="el">HHashObj.h</a>. |

------------------------------------------------------------------------

## Enumeration Type Documentation

<span id="dca29a1140aadadfd92b34a02fa516ef" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">anonymous enum</td>
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
<td><dl>
<dt><strong>Enumerator:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef653dc2bd11c615cb4f219a4d1830c5db" class="anchor"></span>SMPTE</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516ef036429f7a46a17439207d188e46ca840" class="anchor"></span>FRAMES</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="dca29a1140aadadfd92b34a02fa516efcd7c76bbb327f87b097bbfe3c3f0efe5" class="anchor"></span>CELS</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="HHashObj_8h-source.md#l00040" class="el">40</a> of file <a href="HHashObj_8h-source.md" class="el">HHashObj.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:49 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
