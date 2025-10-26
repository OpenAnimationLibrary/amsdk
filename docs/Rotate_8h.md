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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# Rotate.h File Reference

`#include "`<a href="Quaterni_8h-source.md" class="el"><code>Quaterni.h</code></a>`"`  
`#include "`<a href="Vector_8h-source.md" class="el"><code>Vector.h</code></a>`"`  

Include dependency graph for Rotate.h:

<span class="image placeholder" original-image-src="Rotate_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Rotate.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="Rotate_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Rotate.hdep_map"></span>

[Go to the source code of this file.](Rotate_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classRotate.md" class="el">Rotate</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classRotateVector.md" class="el">RotateVector</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classRotateSphere.md" class="el">RotateSphere</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classRotateEuler.md" class="el">RotateEuler</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSR.md" class="el">TSR</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classTSQ.md" class="el">TSQ</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Rotate_8h.md#e51e7496beb4bffac9c5fd06949b5257" class="el">__ROTATE_H</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="Rotate_8h.md#f32da37ad60e8aff4400819731a9d87b" class="el">VectorsToLinear</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>, const <a href="classVector.md" class="el">Vector</a> &amp;<a href="Rave_8h.md#6654c734ccab8f440ff0825eb443dc7f" class="el">v1</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="Rotate_8h.md#1798528190ee6ef81bd8773da62a651d" class="el">VectorsToAngle</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>, const <a href="classVector.md" class="el">Vector</a> &amp;<a href="Rave_8h.md#6654c734ccab8f440ff0825eb443dc7f" class="el">v1</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="Rotate_8h.md#79b3368b75355dc80fa57eb8bdb728b5" class="el">LinearToAngle</a> (float linear)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="Rotate_8h.md#19a22e2e859164b37ad268fefee7aaab" class="el">LinearToAngle360</a> (float linear)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="e51e7496beb4bffac9c5fd06949b5257" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __ROTATE_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Rotate_8h-source.md#l00003" class="el">3</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>. |

------------------------------------------------------------------------

## Function Documentation

<span id="79b3368b75355dc80fa57eb8bdb728b5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float LinearToAngle</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>linear</em></td>
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
<td><p>Definition at line <a href="Rotate_8h-source.md#l00261" class="el">261</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>.</p>
<p>References <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>.</p>
<p>Referenced by <a href="Rotate_8h-source.md#l00266" class="el">LinearToAngle360()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="19a22e2e859164b37ad268fefee7aaab" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float LinearToAngle360</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>linear</em></td>
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
<td><p>Definition at line <a href="Rotate_8h-source.md#l00266" class="el">266</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>.</p>
<p>References <a href="Rave_8h.md#51b38547609c2cb31342492287c149e1" class="el">float()</a>, and <a href="Rotate_8h-source.md#l00261" class="el">LinearToAngle()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Rotate_8h_19a22e2e859164b37ad268fefee7aaab_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Rotate_8h_19a22e2e859164b37ad268fefee7aaab_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="1798528190ee6ef81bd8773da62a651d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float VectorsToAngle</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>v</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>v1</em></td>
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
<td><p>Definition at line <a href="Rotate_8h-source.md#l00256" class="el">256</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>.</p>
<p>References <a href="Quaterni_8h-source.md#l00213" class="el">Dot()</a>, <a href="Vector_8h-source.md#l00080" class="el">Vector::Normalized()</a>, and <a href="Filecons_8h-source.md#l00033" class="el">RADIANS</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Rotate_8h_1798528190ee6ef81bd8773da62a651d_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Rotate_8h_1798528190ee6ef81bd8773da62a651d_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="f32da37ad60e8aff4400819731a9d87b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float VectorsToLinear</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>v</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>v1</em></td>
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
<td><p>Definition at line <a href="Rotate_8h-source.md#l00245" class="el">245</a> of file <a href="Rotate_8h-source.md" class="el">Rotate.h</a>.</p>
<p>References <a href="Quaterni_8h-source.md#l00213" class="el">Dot()</a>, <a href="Rave_8h.md#51b38547609c2cb31342492287c149e1" class="el">float()</a>, and <a href="Vector_8h-source.md#l00080" class="el">Vector::Normalized()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="Rotate_8h_f32da37ad60e8aff4400819731a9d87b_cgraph.gif" data-original-image-title="" data-border="0" usemap="#Rotate_8h_f32da37ad60e8aff4400819731a9d87b_cgraph_map"></span></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:49 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
