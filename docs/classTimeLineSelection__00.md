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

# TimeLineSelection Class Reference

`#include <`<a href="TimeRang_8h-source.md" class="el"><code>TimeRang.h</code></a>`>`

Collaboration diagram for TimeLineSelection:

<span class="image placeholder" original-image-src="classTimeLineSelection__coll__graph.gif" original-image-title="" border="0" usemap="#TimeLineSelection__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classTimeLineSelection-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#cd376e17e508d3f29975697814ff449b" class="el">TimeLineSelection</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#324cd17335c94fb232d3c1352ee5a763" class="el">TimeLineSelection</a> (const <a href="classTimeLineSelection.md" class="el">TimeLineSelection</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#850904462249f4319e883ddf630348c5" class="el">TimeLineSelection</a> (<a href="classTime.md" class="el">Time</a> start, <a href="classTime.md" class="el">Time</a> end)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#74e5a74f2b6c561f012a89e682e0eee6" class="el">Clear</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#7c16cc8e178703ab28300682cd6d953f" class="el">operator+=</a> (const <a href="classTimeLineSelection.md" class="el">TimeLineSelection</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#057edeae4d113624221647f5b27784f4" class="el">operator+=</a> (int line)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#52a7838c51c8970267d61e2e857579cd" class="el">operator=</a> (const <a href="classTimeLineSelection.md" class="el">TimeLineSelection</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#1877edadf2af785b8e0a7067136645e4" class="el">IsInSelection</a> (int line)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTimeRange.md" class="el">TimeRange</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#6960ab498e518d04874502b91a8f1fe5" class="el">m_timerange</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CArray&lt; int, int &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeLineSelection.md#015020961ff08e8e5b10f79c4b0fdf09" class="el">m_linearray</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

