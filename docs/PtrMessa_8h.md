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

# PtrMessa.h File Reference

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="PtrMessa_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/PtrMessa.hdep_map"></span>

[Go to the source code of this file.](PtrMessa_8h-source.md)

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
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="PtrMessa_8h.md#150409db34f9a485e644fbdcd7878895" class="el">__PTRMESSA_H</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95" class="el">PtrMessage</a> {<br />
  <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95924b407221d39e83cef72a68222e78d0" class="el">PTM_DELETED</a> = 0, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95efd37a5cdfe376198eb0860e90868cec" class="el">PTM_RENAMED</a> = 1, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f9523439f52d0fa67acc56df2c5c59896b8" class="el">PTM_VALUECHANGED</a> = 2, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f955cb9d173a701eb94d96ad7ac8303f8fa" class="el">PTM_VALUESTORED</a> = 3,<br />
  <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95c5a6d867a7a0f5d64e8f51ae67be88fb" class="el">PTM_MARKDEPENDENT</a> = 4, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95ea857729d8fd994c05a78a4c93639ae4" class="el">PTM_GETPOINTERLIST</a> = 5, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95acc72d705fc94bf5ba63959781de28a4" class="el">PTM_NULLCHANGED</a> = 6, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f958aaae912cdc00d60124ad99a7593261a" class="el">PTM_SELECTIONCHANGED</a> = 7,<br />
  <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95505b76d4bc8fefa1b2fac8a94d6e9123" class="el">PTM_FPSCHANGED</a> = 8, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95a6f7e1f8b07c028c8975479e3661d833" class="el">PTM_WORLDSTORED</a> = 9, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95463d2c12136d97bb60f4ae3d840681e3" class="el">PTM_ENDLOAD</a> = 10, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f954cb316451bbd4d44aa8ad42b38c9378e" class="el">PTM_FORCEDESCRIPTION</a> = 11,<br />
  <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f9596589ffcb3d9c0d29ea7d8d12e6493eb" class="el">PTM_BUTTONPRESSED</a> = 12, <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95d7291f2037322a9c0b4bf802bc90256a" class="el">PTM_DRAW</a> = 13<br />
}</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="150409db34f9a485e644fbdcd7878895" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __PTRMESSA_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="PtrMessa_8h-source.md#l00003" class="el">3</a> of file <a href="PtrMessa_8h-source.md" class="el">PtrMessa.h</a>. |

------------------------------------------------------------------------

## Enumeration Type Documentation

<span id="914b6f635a6e54f9671412ac4b018f95" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">enum <a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95" class="el">PtrMessage</a></td>
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
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95924b407221d39e83cef72a68222e78d0" class="anchor"></span>PTM_DELETED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95efd37a5cdfe376198eb0860e90868cec" class="anchor"></span>PTM_RENAMED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f9523439f52d0fa67acc56df2c5c59896b8" class="anchor"></span>PTM_VALUECHANGED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f955cb9d173a701eb94d96ad7ac8303f8fa" class="anchor"></span>PTM_VALUESTORED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95c5a6d867a7a0f5d64e8f51ae67be88fb" class="anchor"></span>PTM_MARKDEPENDENT</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95ea857729d8fd994c05a78a4c93639ae4" class="anchor"></span>PTM_GETPOINTERLIST</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95acc72d705fc94bf5ba63959781de28a4" class="anchor"></span>PTM_NULLCHANGED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f958aaae912cdc00d60124ad99a7593261a" class="anchor"></span>PTM_SELECTIONCHANGED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95505b76d4bc8fefa1b2fac8a94d6e9123" class="anchor"></span>PTM_FPSCHANGED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95a6f7e1f8b07c028c8975479e3661d833" class="anchor"></span>PTM_WORLDSTORED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95463d2c12136d97bb60f4ae3d840681e3" class="anchor"></span>PTM_ENDLOAD</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f954cb316451bbd4d44aa8ad42b38c9378e" class="anchor"></span>PTM_FORCEDESCRIPTION</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f9596589ffcb3d9c0d29ea7d8d12e6493eb" class="anchor"></span>PTM_BUTTONPRESSED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="914b6f635a6e54f9671412ac4b018f95d7291f2037322a9c0b4bf802bc90256a" class="anchor"></span>PTM_DRAW</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="PtrMessa_8h-source.md#l00005" class="el">5</a> of file <a href="PtrMessa_8h-source.md" class="el">PtrMessa.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:48 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
