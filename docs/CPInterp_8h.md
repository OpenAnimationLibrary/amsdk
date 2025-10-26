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

# CPInterp.h File Reference

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="CPInterp_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/SDK/CPInterp.hdep_map"></span>

[Go to the source code of this file.](CPInterp_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="CPInterp_8h.md#03229d6a04af4cd238f81bddedb57adb" class="el">__CPINTERP_H</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e8236" class="el">CPInterpolationMethod</a> {<br />
  <a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e82363446352f49230ee512f872bbe62e1b15" class="el">CPI_DEFAULT</a>, <a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e82369ca09e57d8bf23d2d797b05741dbc04b" class="el">CPI_HOLD</a>, <a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e8236d5fc1e67f4a2aa1d10c6032545b13980" class="el">CPI_LINEAR</a>, <a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e82363a58ac79f2907ec04ef0c70d020ae33f" class="el">CPI_SPLINE</a>,<br />
  <a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e8236f58104ec48ff3f15fce2da18f8e0deb0" class="el">CPI_ZEROSLOPE</a><br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af" class="el">ExtrapolationMethod</a> {<br />
  <a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af0ffeeb7f0e1cfa231e4356ffb4bb9aa7" class="el">EXT_RESET</a>, <a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1afdd2b8ee163d5d382b9b5001ef2a3e7ae" class="el">EXT_HOLD</a>, <a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af3a47c63df5cce880b2c363a65cf22666" class="el">EXT_REPEAT</a>, <a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af0ba3f7d3d54c16b438c1e1b9245b5de4" class="el">EXT_PINGPONG</a>,<br />
  <a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1afeb3986d6cfd0b4400b173c57286f68ed" class="el">EXT_ACCUMULATE</a>, <a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af82a04545983ac409a40583ac67d1a206" class="el">EXT_LINEAR</a><br />
}</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="03229d6a04af4cd238f81bddedb57adb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __CPINTERP_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="CPInterp_8h-source.md#l00003" class="el">3</a> of file <a href="CPInterp_8h-source.md" class="el">CPInterp.h</a>. |

------------------------------------------------------------------------

## Enumeration Type Documentation

<span id="9294a500dc6f913ae6b63633fa4e8236" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">enum <a href="CPInterp_8h.md#9294a500dc6f913ae6b63633fa4e8236" class="el">CPInterpolationMethod</a></td>
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
<td data-valign="top"><em><span id="9294a500dc6f913ae6b63633fa4e82363446352f49230ee512f872bbe62e1b15" class="anchor"></span>CPI_DEFAULT</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="9294a500dc6f913ae6b63633fa4e82369ca09e57d8bf23d2d797b05741dbc04b" class="anchor"></span>CPI_HOLD</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="9294a500dc6f913ae6b63633fa4e8236d5fc1e67f4a2aa1d10c6032545b13980" class="anchor"></span>CPI_LINEAR</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="9294a500dc6f913ae6b63633fa4e82363a58ac79f2907ec04ef0c70d020ae33f" class="anchor"></span>CPI_SPLINE</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="9294a500dc6f913ae6b63633fa4e8236f58104ec48ff3f15fce2da18f8e0deb0" class="anchor"></span>CPI_ZEROSLOPE</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="CPInterp_8h-source.md#l00005" class="el">5</a> of file <a href="CPInterp_8h-source.md" class="el">CPInterp.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="a9ebaf7fd7d5c61ab5c70c443b15f1af" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">enum <a href="CPInterp_8h.md#a9ebaf7fd7d5c61ab5c70c443b15f1af" class="el">ExtrapolationMethod</a></td>
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
<td data-valign="top"><em><span id="a9ebaf7fd7d5c61ab5c70c443b15f1af0ffeeb7f0e1cfa231e4356ffb4bb9aa7" class="anchor"></span>EXT_RESET</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="a9ebaf7fd7d5c61ab5c70c443b15f1afdd2b8ee163d5d382b9b5001ef2a3e7ae" class="anchor"></span>EXT_HOLD</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="a9ebaf7fd7d5c61ab5c70c443b15f1af3a47c63df5cce880b2c363a65cf22666" class="anchor"></span>EXT_REPEAT</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="a9ebaf7fd7d5c61ab5c70c443b15f1af0ba3f7d3d54c16b438c1e1b9245b5de4" class="anchor"></span>EXT_PINGPONG</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="a9ebaf7fd7d5c61ab5c70c443b15f1afeb3986d6cfd0b4400b173c57286f68ed" class="anchor"></span>EXT_ACCUMULATE</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="a9ebaf7fd7d5c61ab5c70c443b15f1af82a04545983ac409a40583ac67d1a206" class="anchor"></span>EXT_LINEAR</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="CPInterp_8h-source.md#l00006" class="el">6</a> of file <a href="CPInterp_8h-source.md" class="el">CPInterp.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:49 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
