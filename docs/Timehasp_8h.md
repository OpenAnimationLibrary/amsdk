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

# Timehasp.h File Reference

`#include <time.h>`  
`#include "loclhasp.h"`  
`#include "haspmem.h"`  

Include dependency graph for Timehasp.h:

<span class="image placeholder" original-image-src="Timehasp_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Timehasp.h_map"></span>

[Go to the source code of this file.](Timehasp_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTimeHasp.md" class="el">TimeHasp</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classMemohaspConverter.md" class="el">MemohaspConverter</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspDate.md" class="el">TimehaspDate</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimehaspTime.md" class="el">TimehaspTime</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Timehasp_8h.md#334e30ee012a73bb87ca114759497ca5" class="el">TIMEHASP_H_</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="typedefs">Typedefs</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">typedef int </td>
<td class="memItemRight" data-valign="bottom"><a href="Timehasp_8h.md#834a8a3407d572b6106767f26cd29098" class="el">THDay</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Timehasp_8h.md#30ac26c81bc9e5b7d6aafbcd82a211ab" class="el">THYear</a> { <a href="Timehasp_8h.md#30ac26c81bc9e5b7d6aafbcd82a211abf85f87228f385f0efae0b0ebc56e1c2d" class="el">TH_MINYEAR</a> = 1992, <a href="Timehasp_8h.md#30ac26c81bc9e5b7d6aafbcd82a211ab3958664b5f9418aeffbc8f21a254bdd8" class="el">TH_MAXYEAR</a> = 2091 }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d" class="el">THMonth</a> {<br />
  <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d3e5bcdecf5bde81aef21ea29f8ab7417" class="el">TH_JAN</a> = 1, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d17043fb8bb57510893e952091003af8e" class="el">TH_FEB</a> = 2, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3de37e830b4c25b6ab4c9d4619100f23f3" class="el">TH_MAR</a> = 3, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d9769dff9439c1e59275bacf1f1e23b7a" class="el">TH_APR</a> = 4,<br />
  <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d1951511b1faa3fab3f3f7b1c85213855" class="el">TH_MAY</a> = 5, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3ddb88c4cc82f83d0adbd93b3cbe890e65" class="el">TH_JUN</a> = 6, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d6d33ea41b16fb863424420eb0f7e9db6" class="el">TH_JUL</a> = 7, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d86c4f5b56d058972095bebc558035c70" class="el">TH_AUG</a> = 8,<br />
  <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d0c2c54c0d3abca0f2227eeb8b94f980e" class="el">TH_SEP</a> = 9, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d5b5a47b2341e57acfb6c5267cca601d6" class="el">TH_OCT</a> = 10, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3da9b7ccf15c8b934e832a5e72fe78e305" class="el">TH_NOV</a> = 11, <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3dfa16026000a9b74995812fc7fa402549" class="el">TH_DEC</a> = 12<br />
}</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="334e30ee012a73bb87ca114759497ca5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define TIMEHASP_H_</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Timehasp_8h-source.md#l00008" class="el">8</a> of file <a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>. |

------------------------------------------------------------------------

## Typedef Documentation

<span id="834a8a3407d572b6106767f26cd29098" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">typedef int <a href="Timehasp_8h.md#834a8a3407d572b6106767f26cd29098" class="el">THDay</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Timehasp_8h-source.md#l00115" class="el">115</a> of file <a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>. |

------------------------------------------------------------------------

## Enumeration Type Documentation

<span id="8def57c7506e3bdbc69fa1e59061fb3d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">enum <a href="Timehasp_8h.md#8def57c7506e3bdbc69fa1e59061fb3d" class="el">THMonth</a></td>
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
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3d3e5bcdecf5bde81aef21ea29f8ab7417" class="anchor"></span>TH_JAN</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3d17043fb8bb57510893e952091003af8e" class="anchor"></span>TH_FEB</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3de37e830b4c25b6ab4c9d4619100f23f3" class="anchor"></span>TH_MAR</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3d9769dff9439c1e59275bacf1f1e23b7a" class="anchor"></span>TH_APR</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3d1951511b1faa3fab3f3f7b1c85213855" class="anchor"></span>TH_MAY</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3ddb88c4cc82f83d0adbd93b3cbe890e65" class="anchor"></span>TH_JUN</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3d6d33ea41b16fb863424420eb0f7e9db6" class="anchor"></span>TH_JUL</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3d86c4f5b56d058972095bebc558035c70" class="anchor"></span>TH_AUG</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3d0c2c54c0d3abca0f2227eeb8b94f980e" class="anchor"></span>TH_SEP</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3d5b5a47b2341e57acfb6c5267cca601d6" class="anchor"></span>TH_OCT</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3da9b7ccf15c8b934e832a5e72fe78e305" class="anchor"></span>TH_NOV</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="8def57c7506e3bdbc69fa1e59061fb3dfa16026000a9b74995812fc7fa402549" class="anchor"></span>TH_DEC</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="Timehasp_8h-source.md#l00123" class="el">123</a> of file <a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="30ac26c81bc9e5b7d6aafbcd82a211ab" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">enum <a href="Timehasp_8h.md#30ac26c81bc9e5b7d6aafbcd82a211ab" class="el">THYear</a></td>
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
<td data-valign="top"><em><span id="30ac26c81bc9e5b7d6aafbcd82a211abf85f87228f385f0efae0b0ebc56e1c2d" class="anchor"></span>TH_MINYEAR</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="30ac26c81bc9e5b7d6aafbcd82a211ab3958664b5f9418aeffbc8f21a254bdd8" class="anchor"></span>TH_MAXYEAR</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="Timehasp_8h-source.md#l00117" class="el">117</a> of file <a href="Timehasp_8h-source.md" class="el">Timehasp.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:50 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
