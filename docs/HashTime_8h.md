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

# HashTime.h File Reference

`#include "`<a href="Macros_8h-source.md" class="el"><code>Macros.h</code></a>`"`  
`#include "`<a href="Exports_8h-source.md" class="el"><code>Exports.h</code></a>`"`  

Include dependency graph for HashTime.h:

<span class="image placeholder" original-image-src="HashTime_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/HashTime.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="HashTime_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/HashTime.hdep_map"></span>

[Go to the source code of this file.](HashTime_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTime.md" class="el">Time</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashTime_8h.md#1c598d473ca17339ef8b810382a1e9ab" class="el">__HASHTIME_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashTime_8h.md#2129f2186a4f12d7c9b1479bc4b53d75" class="el">MAX_TICKS</a>   2147483647L</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashTime_8h.md#c6d5d0f38e92c42f7dc52c421d453e7a" class="el">MAX_SECONDS</a>   MAX_TICKS/Time::TICKSPERSECOND</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashTime_8h.md#7c67d8e7d559d47d18824fda4e78ede5" class="el">MINTIME</a>   -<a href="classTime.md" class="el">Time</a>( Time::TT_MAX )</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashTime_8h.md#8579d60f7c12d24db02325f0945faae0" class="el">MAXTIME</a>   <a href="classTime.md" class="el">Time</a>( Time::TT_MAX )</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="HashTime_8h.md#1c2d377480ec416ab84486aff0e89c2b" class="el">MINTIMESTEP</a>   <a href="classTime.md" class="el">Time</a>( Time::TT_MINSTEP )</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="HashTime_8h.md#802886907cd1af67d382b4bb56e61c5b" class="el">operator *</a> (double n, <a href="classTime.md" class="el">Time</a> right)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="HashTime_8h.md#e037e95678ceb6f6f59020a246cb36de" class="el">abs</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Define Documentation

<span id="1c598d473ca17339ef8b810382a1e9ab" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define __HASHTIME_H</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="HashTime_8h-source.md#l00003" class="el">3</a> of file <a href="HashTime_8h-source.md" class="el">HashTime.h</a>. |

<span id="c6d5d0f38e92c42f7dc52c421d453e7a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define MAX_SECONDS   MAX_TICKS/Time::TICKSPERSECOND</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="HashTime_8h-source.md#l00013" class="el">13</a> of file <a href="HashTime_8h-source.md" class="el">HashTime.h</a>. |

<span id="2129f2186a4f12d7c9b1479bc4b53d75" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define MAX_TICKS   2147483647L</td>
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
<td><p>Definition at line <a href="HashTime_8h-source.md#l00012" class="el">12</a> of file <a href="HashTime_8h-source.md" class="el">HashTime.h</a>.</p>
<p>Referenced by <a href="HashTime_8h-source.md#l00303" class="el">Time::IsMax()</a>, <a href="HashTime_8h-source.md#l00308" class="el">Time::IsMin()</a>, <a href="HashTime_8h-source.md#l00288" class="el">Time::SetMax()</a>, and <a href="HashTime_8h-source.md#l00293" class="el">Time::SetMin()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="8579d60f7c12d24db02325f0945faae0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define MAXTIME   <a href="classTime.md" class="el">Time</a>( Time::TT_MAX )</td>
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
<td><p>Definition at line <a href="HashTime_8h-source.md#l00016" class="el">16</a> of file <a href="HashTime_8h-source.md" class="el">HashTime.h</a>.</p>
<p>Referenced by <a href="TimeRang_8h-source.md#l00137" class="el">TimeRange::operator+=()</a>, <a href="TimeRang_8h-source.md#l00070" class="el">TimeRange::SetForever()</a>, and <a href="TimeRang_8h-source.md#l00065" class="el">TimeRange::SetNever()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="7c67d8e7d559d47d18824fda4e78ede5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define MINTIME   -<a href="classTime.md" class="el">Time</a>( Time::TT_MAX )</td>
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
<td><p>Definition at line <a href="HashTime_8h-source.md#l00015" class="el">15</a> of file <a href="HashTime_8h-source.md" class="el">HashTime.h</a>.</p>
<p>Referenced by <a href="TimeRang_8h-source.md#l00149" class="el">TimeRange::operator-=()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="1c2d377480ec416ab84486aff0e89c2b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">#define MINTIMESTEP   <a href="classTime.md" class="el">Time</a>( Time::TT_MINSTEP )</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="HashTime_8h-source.md#l00017" class="el">17</a> of file <a href="HashTime_8h-source.md" class="el">HashTime.h</a>. |

------------------------------------------------------------------------

## Function Documentation

<span id="e037e95678ceb6f6f59020a246cb36de" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> abs</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>time</em></td>
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
<td><p>Definition at line <a href="HashTime_8h-source.md#l00326" class="el">326</a> of file <a href="HashTime_8h-source.md" class="el">HashTime.h</a>.</p>
<p>References <a href="HashTime_8h-source.md#l00203" class="el">Time::GetTicks()</a>, and <a href="HashTime_8h-source.md#l00208" class="el">Time::SetTicks()</a>.</p>
<p>Referenced by <a href="Fastftol_8h-source.md#l00032" class="el">fast_ftol_unsigned()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="HashTime_8h_e037e95678ceb6f6f59020a246cb36de_cgraph.gif" data-original-image-title="" data-border="0" usemap="#HashTime_8h_e037e95678ceb6f6f59020a246cb36de_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="802886907cd1af67d382b4bb56e61c5b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> operator *</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">double </td>
<td class="mdname" data-nowrap=""><em>n</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname" data-nowrap=""><em>right</em></td>
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
|   | Definition at line <a href="HashTime_8h-source.md#l00319" class="el">319</a> of file <a href="HashTime_8h-source.md" class="el">HashTime.h</a>. |

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:47 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
