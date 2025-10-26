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

# HashArray\< TYPE, ARG_TYPE \> Class Template Reference

`#include <`<a href="HashArra_8h-source.md" class="el"><code>HashArra.h</code></a>`>`

Inheritance diagram for HashArray\< TYPE, ARG_TYPE \>:

<span class="image placeholder" original-image-src="classHashArray__inherit__graph.gif" original-image-title="" border="0" usemap="#HashArray_3_01TYPE_00_01ARG__TYPE_01_4__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HashArray\< TYPE, ARG_TYPE \>:

<span class="image placeholder" original-image-src="classHashArray__coll__graph.gif" original-image-title="" border="0" usemap="#HashArray_3_01TYPE_00_01ARG__TYPE_01_4__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHashArray-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#51815e3ebc38221eeeb50e5d8670da15" class="el">HashArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#f2259ebe9d1c07ceb60119edb0a86416" class="el">GetSize</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#ffa41436425726208b8f55f1b7d26cbd" class="el">GetUpperBound</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#7b8fd25de7858cfef37028cd4d8f52de" class="el">SetSize</a> (int newsize, int growby=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#0c686ee0fcab422244a7c79f614c195e" class="el">FreeExtra</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#89fa2a8f9b65284fc34a3851e23257ac" class="el">RemoveAll</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#ddc54dfc91e8489e924df466a56ffe1e" class="el">GetAt</a> (int index) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#83feaa64c8e9087b27f2fe9f31eb6b18" class="el">ElementAt</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#ae58b8d561ba0c7c62197e408365bcf2" class="el">SetAt</a> (int index, ARG_TYPE newElement)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#c1a9ad8203baf81261ea98ad62b8fea0" class="el">InsertAt</a> (int nIndex, ARG_TYPE newElement, int nCount=1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#c95ee83888ea1ce0de90a127d77c8005" class="el">RemoveAt</a> (int index, int count=1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#91e0d6169398953942fe60c3946c79d7" class="el">operator[]</a> (int index) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#710e01c9f42500b31117688d8eaebfac" class="el">operator[]</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#95a7201fab22e53b513f89e23fbca949" class="el">GetArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#28d335e89d123bd2e395bce24803db1d" class="el">SetAtGrow</a> (int index, ARG_TYPE newElement)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#b280269cc0a506501eff4139cd94cb39" class="el">Add</a> (ARG_TYPE newElement)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#4837df53e4b490e7c377c14c56ee53c1" class="el">Push</a> (ARG_TYPE newElement)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#d1c27744cd9d2228848f688e85b9b6b0" class="el">Pop</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#62dae3ace05cea3c33a91593a13a57ac" class="el">GetPushed</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#3baf74a81ccd00c867601be0fc5e511c" class="el">SetGranularity</a> (int granularity)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#35948becbefe23b48716a0700ac76e50" class="el">~HashArray</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-attributes">Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">TYPE * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#bf9e3c21a24d9d5a3de1ffb33d6efe5d" class="el">m_data</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#4c0dac8d4560d73747781d633a4f250d" class="el">m_size</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#b49c56ab606e2039b8fdb36bfbfeb75f" class="el">m_maxsize</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHashArray.md#c1b68821c76d6f50867d3b378e82cba8" class="el">m_growby</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

