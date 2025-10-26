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

# HAnimObject Class Reference

The father class of about all animatable objects in Animation Master. [More...](#_details)

`#include <`<a href="HHashObj_8h-source.md" class="el"><code>HHashObj.h</code></a>`>`

Inheritance diagram for HAnimObject:

<span class="image placeholder" original-image-src="classHAnimObject__inherit__graph.gif" original-image-title="" border="0" usemap="#HAnimObject__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HAnimObject:

<span class="image placeholder" original-image-src="classHAnimObject__coll__graph.gif" original-image-title="" border="0" usemap="#HAnimObject__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHAnimObject-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#9016643866e5d93362934fdb288d911a" class="el">IsCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAnimObject.md" class="el">HAnimObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#7c3338fc6e08706ddad054b1525ab709" class="el">GetCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#eb35d3d43f0898362662c5e86e43e3fb" class="el">GetFirstKey</a> (BOOL *isselected=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#0379dcc491904356edfc1e090ba496f8" class="el">GetLastKey</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#e5c702148c17c9eff98f82ef6e271b35" class="el">GetNextKey</a> (<a href="classTime.md" class="el">Time</a> time, BOOL *isselected=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#d57ca6818a68df5c0dd17e909385aeaa" class="el">GetPrevKey</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#5053985d57baafc4d758f97990c134d6" class="el">IsKey</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#668ef951fe37165d284b57859a5a9ade" class="el">CountKeys</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#7bfea42385b70e86e14242d01506fd65" class="el">DeleteKey</a> (<a href="classTime.md" class="el">Time</a> time, BOOL storeundo=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#5354f38a63c6579c1bc90386d7c75722" class="el">Reduce</a> (float error)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#ffd2c64958c237628fc3c8d613636eaf" class="el">DeleteKeys</a> (<a href="classTimeRange.md" class="el">TimeRange</a> range)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#9ea55998be0fd4ae2ea1ebe3a57ff1f9" class="el">TransformKeys</a> (<a href="classTimeRange.md" class="el">TimeRange</a> range, float scale, <a href="classTime.md" class="el">Time</a> offset, BOOL issnaptoint)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#669f182a4dd52422a310f5e3187302b4" class="el">RemoveDrivers</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHObject.md" class="el">HObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#df6befb16a611cdfcd5dadd41ce3d4cc" class="el">GetObject</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHObject.md" class="el">HObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHAnimObject.md#7f4814e03bdbe2508c6ed4160fb55d7d" class="el">GetActionObject</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

