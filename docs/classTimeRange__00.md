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

# TimeRange Class Reference

`#include <`<a href="TimeRang_8h-source.md" class="el"><code>TimeRang.h</code></a>`>`

Collaboration diagram for TimeRange:

<span class="image placeholder" original-image-src="classTimeRange__coll__graph.gif" original-image-title="" border="0" usemap="#TimeRange__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classTimeRange-members.md)

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
&#10;<h2 id="public-types">Public Types</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#066dddcb7c14ac5b7d9d72ed110d49aa" class="el">RangeType</a> { <a href="classTimeRange.md#066dddcb7c14ac5b7d9d72ed110d49aa14dfaf5aa87f8e377bc7ba09bc94b3b7" class="el">RT_NEVER</a>, <a href="classTimeRange.md#066dddcb7c14ac5b7d9d72ed110d49aa73836c2e85228cbdb9606a260e34a81d" class="el">RT_FOREVER</a> }</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#dd100f41868586840051e37b735580ea" class="el">TimeRange</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#9729f93feb8e3d7db0c991afefe0d687" class="el">TimeRange</a> (<a href="classTimeRange.md#066dddcb7c14ac5b7d9d72ed110d49aa" class="el">RangeType</a> rt)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#0679aea0a37d3a85b2847b2f4410ba9a" class="el">TimeRange</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#263f1d6fbc61dfa27a4f463133b2b605" class="el">TimeRange</a> (const <a href="classTimeRange.md" class="el">TimeRange</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#965138f73bb25fe4eca95aab0ae5dfd9" class="el">TimeRange</a> (<a href="classTime.md" class="el">Time</a> start, <a href="classTime.md" class="el">Time</a> end)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#f966e20e49bcca03e3120961a68e8534" class="el">~TimeRange</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTimeRange.md" class="el">TimeRange</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#65ee0e9c39bd5ca37a63476ad2878503" class="el">operator=</a> (const <a href="classTimeRange.md" class="el">TimeRange</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#f087d8ac81ee659028a2ae0589f744d4" class="el">Set</a> (<a href="classTime.md" class="el">Time</a> start, <a href="classTime.md" class="el">Time</a> end)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#42da6dd1acca4b9633ff4ff13c9be522" class="el">SetNever</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#2dadd5e2d68894806a8e28757c1a3118" class="el">SetForever</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#70a8806ccc79c5fa10cceb22ae1ad3bc" class="el">GetLength</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#683e38cb80848d1178fd39a29bfe9866" class="el">IsValid</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#f1c65f6ebe6045430943661391edfd35" class="el">IsIntersect</a> (const <a href="classTimeRange.md" class="el">TimeRange</a> &amp;range) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#7b26eadcec1e56ec635d7a434c568d68" class="el">IsTimeInRange</a> (<a href="classTime.md" class="el">Time</a> time) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#624be9af091a84fd1932f2ddbb77de1d" class="el">IsTimeWithinRange</a> (<a href="classTime.md" class="el">Time</a> time) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#873182ea25734b68d614b4dcc7fe6b6c" class="el">IsRangeInRange</a> (const <a href="classTimeRange.md" class="el">TimeRange</a> &amp;range) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#752df20a22feca5250d9fa17959ca4ed" class="el">IsActiveHere</a> (<a href="classTime.md" class="el">Time</a> time) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#87b61bfa22c09f6948f00a8c69ecc8fa" class="el">operator==</a> (const <a href="classTimeRange.md" class="el">TimeRange</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#ed6147ff836fe68438185995068a8fd2" class="el">operator!=</a> (const <a href="classTimeRange.md" class="el">TimeRange</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#c3b06a55c2cfc3b723096e059beeb5a5" class="el">operator|=</a> (const <a href="classTimeRange.md" class="el">TimeRange</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#1bcfbc1ac5b14398db1e296a1b5ea9a7" class="el">operator|=</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#cb055d345732194514cbd2d7335f7c02" class="el">operator &amp;=</a> (const <a href="classTimeRange.md" class="el">TimeRange</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#0d78b079e3961ec7620232d45525d2db" class="el">operator &amp;=</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#c6466ed2573a4ff6a9dfe65b6d097c43" class="el">operator+=</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTimeRange.md" class="el">TimeRange</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#6d4c1b6d6ec20d1c55f6fd81634599a7" class="el">operator+</a> (<a href="classTime.md" class="el">Time</a> time) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#3231ec285340b417a78c32b8e3bcc8bc" class="el">operator-=</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTimeRange.md" class="el">TimeRange</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#055c36a74e0e5d4bc88856d6e50cc7a3" class="el">operator-</a> (<a href="classTime.md" class="el">Time</a> time) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#f0a6578888719766e4dab83e2b7f36f8" class="el">operator *=</a> (float n)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTimeRange.md" class="el">TimeRange</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#1f1fc2325bbbdf3ac389ceb5ca43f1b6" class="el">operator *</a> (float n) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#dd18a2ba14af8e8e3d1c6dfc27bd5b79" class="el">Union</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#0a27f82745897daefc1926344619da70" class="el">IsInstance</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#95a91412907506f30b4e92c4d5db99fc" class="el">m_start</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classTimeRange.md#b306b69592d5e95d9f1732f97e938c8e" class="el">m_end</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

