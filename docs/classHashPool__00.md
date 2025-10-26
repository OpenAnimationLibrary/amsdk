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

# HashPool Class Reference

`#include <`<a href="Allocate_8h-source.md" class="el"><code>Allocate.h</code></a>`>`

Collaboration diagram for HashPool:

<span class="image placeholder" original-image-src="classHashPool__coll__graph.gif" original-image-title="" border="0" usemap="#HashPool__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHashPool-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#8e6352c0f3dfe85d44c6ef01cf701157" class="el">HashPool</a> (<a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb" class="el">PoolType</a> type, char *name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#26ac6f957015bee405ff10d4bfcdae3e" class="el">~HashPool</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#c1a36b6050d5609570081ede27b259c4" class="el">Alloc</a> (size_t size)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#2cd192d8dfedaea44c77300443a2a9e6" class="el">Free</a> (void *p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#49a3e87dfcb34a8dc782243de471bea9" class="el">FreePool</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#a0220381b7ca4bee6ae0bc21b6f8a5fc" class="el">GetTotal</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#4b60768e769540f6a89151e8189e132a" class="el">IsEmpty</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-member-functions">Protected Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMemHeader.md" class="el">MemHeader</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#bcf5d7d515922339d0da60bdc8d77b5e" class="el">GetFreeMemHeader</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#cda9c638d7024fc5fc98cf803dff727c" class="el">MakeFreeMemHeaders</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#cc6b551d6afd92dd22c1e050d4545276" class="el">PutFreeMemHeader</a> (<a href="classMemHeader.md" class="el">MemHeader</a> *memheader)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMemHeader.md" class="el">MemHeader</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#006da3c50438af40999feead262b13bb" class="el">AllocateBlock</a> (size_t minsize)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-attributes">Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMemHeader.md" class="el">MemHeader</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#5682dc82cb16546b3707c07e46d0c21d" class="el">m_memheader</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CCriticalSection </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#ab45ae9b8fc212c509d321bcc78ff75e" class="el">m_criticalsection</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">size_t </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#6c9b5ebae49f49b8b6a037c129428774" class="el">m_total</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="Allocate_8h.md#0be386025915d7408807aa8c7ffeaadb" class="el">PoolType</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#3c3a1749e56c5a79ba7f71607cd8cd91" class="el">m_type</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#86cce5eb4063b44d1d3df906eddde135" class="el">m_name</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMemHeader.md" class="el">MemHeader</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#c6ea4b7bd17a662cce264f7609ab2e32" class="el">m_freememheaders</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashPool.md#12565d22586299f4d6a9c69fb204f6d1" class="el">m_memheaderlist</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

