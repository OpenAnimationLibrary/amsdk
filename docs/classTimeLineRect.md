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

# TimeLineRect Class Reference

`#include <`<a href="TimeRang_8h-source.md" class="el"><code>TimeRang.h</code></a>`>`

Collaboration diagram for TimeLineRect:

<span class="image placeholder" original-image-src="classTimeLineRect__coll__graph.gif" original-image-title="" border="0" usemap="#TimeLineRect__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classTimeLineRect-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineRect.md#a9a7b339b29b86ae3f2e340b09a490bc" class="el">TimeLineRect</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineRect.md#b33193c4d4897bf60dbff71ffa484bc9" class="el">TimeLineRect</a> (<a href="classTime.md" class="el">Time</a> start, <a href="classTime.md" class="el">Time</a> end, int top=BIG_INT, int bottom=-BIG_INT)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineRect.md#74e5a74f2b6c561f012a89e682e0eee6" class="el">Clear</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineRect.md#b492f8075004cff5ff0be76df5a9d65c" class="el">operator|=</a> (const <a href="classTimeLineRect.md" class="el">TimeLineRect</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineRect.md#823e5ac9d2032d643cbbd5a38efa546a" class="el">operator|=</a> (const <a href="classTimeLineSelection.md" class="el">TimeLineSelection</a> &amp;other)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTimeRange.md" class="el">TimeRange</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineRect.md#6960ab498e518d04874502b91a8f1fe5" class="el">m_timerange</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineRect.md#97652ccd4b6be5c6ebc67de2028d93e8" class="el">m_top</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineRect.md#716aefbb109228322db6f1a84a3c27f1" class="el">m_bottom</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="TimeRang_8h-source.md#l00241" class="el">241</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="a9a7b339b29b86ae3f2e340b09a490bc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">TimeLineRect::TimeLineRect</td>
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
<td><p>Definition at line <a href="TimeRang_8h-source.md#l00247" class="el">247</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>.</p>
<p>References <a href="DataType_8h-source.md#l00016" class="el">BIG_INT</a>.</p></td>
</tr>
</tbody>
</table>

<span id="b33193c4d4897bf60dbff71ffa484bc9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">TimeLineRect::TimeLineRect</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname" data-nowrap=""><em>start</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname" data-nowrap=""><em>end</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>top</em> = <code>BIG_INT</code>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>bottom</em> = <code>-BIG_INT</code></td>
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
|   | Definition at line <a href="TimeRang_8h-source.md#l00253" class="el">253</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>. |

------------------------------------------------------------------------

## Member Function Documentation

<span id="74e5a74f2b6c561f012a89e682e0eee6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void TimeLineRect::Clear</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void </td>
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
<td><p>Definition at line <a href="TimeRang_8h-source.md#l00261" class="el">261</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>.</p>
<p>References <a href="DataType_8h-source.md#l00016" class="el">BIG_INT</a>.</p></td>
</tr>
</tbody>
</table>

<span id="823e5ac9d2032d643cbbd5a38efa546a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void TimeLineRect::operator|=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classTimeLineSelection.md" class="el">TimeLineSelection</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>other</em></td>
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
<td><p>Definition at line <a href="TimeRang_8h-source.md#l00276" class="el">276</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>.</p>
<p>References <a href="TimeRang_8h-source.md#l00187" class="el">TimeLineSelection::m_linearray</a>, <a href="TimeRang_8h-source.md#l00186" class="el">TimeLineSelection::m_timerange</a>, <a href="Macros_8h-source.md#l00015" class="el">MAX</a>, and <a href="Macros_8h-source.md#l00017" class="el">MIN</a>.</p></td>
</tr>
</tbody>
</table>

<span id="b492f8075004cff5ff0be76df5a9d65c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void TimeLineRect::operator|=</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classTimeLineRect.md" class="el">TimeLineRect</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>other</em></td>
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
<td><p>Definition at line <a href="TimeRang_8h-source.md#l00268" class="el">268</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>.</p>
<p>References <a href="TimeRang_8h-source.md#l00245" class="el">m_bottom</a>, <a href="TimeRang_8h-source.md#l00244" class="el">m_timerange</a>, <a href="TimeRang_8h-source.md#l00245" class="el">m_top</a>, <a href="Macros_8h-source.md#l00015" class="el">MAX</a>, and <a href="Macros_8h-source.md#l00017" class="el">MIN</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Data Documentation

<span id="716aefbb109228322db6f1a84a3c27f1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int <a href="classTimeLineRect.md#716aefbb109228322db6f1a84a3c27f1" class="el">TimeLineRect::m_bottom</a></td>
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
<td><p>Definition at line <a href="TimeRang_8h-source.md#l00245" class="el">245</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>.</p>
<p>Referenced by <a href="TimeRang_8h-source.md#l00268" class="el">operator|=()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="6960ab498e518d04874502b91a8f1fe5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classTimeRange.md" class="el">TimeRange</a> <a href="classTimeLineRect.md#6960ab498e518d04874502b91a8f1fe5" class="el">TimeLineRect::m_timerange</a></td>
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
<td><p>Definition at line <a href="TimeRang_8h-source.md#l00244" class="el">244</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>.</p>
<p>Referenced by <a href="TimeRang_8h-source.md#l00268" class="el">operator|=()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="97652ccd4b6be5c6ebc67de2028d93e8" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int <a href="classTimeLineRect.md#97652ccd4b6be5c6ebc67de2028d93e8" class="el">TimeLineRect::m_top</a></td>
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
<td><p>Definition at line <a href="TimeRang_8h-source.md#l00245" class="el">245</a> of file <a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>.</p>
<p>Referenced by <a href="TimeRang_8h-source.md#l00268" class="el">operator|=()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="TimeRang_8h-source.md" class="el">TimeRang.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:47:04 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
