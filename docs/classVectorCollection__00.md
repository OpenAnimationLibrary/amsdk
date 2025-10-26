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

# VectorCollection Class Reference

`#include <`<a href="IEModel_8h-source.md" class="el"><code>IEModel.h</code></a>`>`

Collaboration diagram for VectorCollection:

<span class="image placeholder" original-image-src="classVectorCollection__coll__graph.gif" original-image-title="" border="0" usemap="#VectorCollection__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classVectorCollection-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#0ac7e1b2001abc2c00920218c910595e" class="el">VectorCollection</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#5ddee372fb723ebd6ba16c8f3e04d343" class="el">~VectorCollection</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#95a7201fab22e53b513f89e23fbca949" class="el">GetArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#ddc54dfc91e8489e924df466a56ffe1e" class="el">GetAt</a> (int index) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#f2259ebe9d1c07ceb60119edb0a86416" class="el">GetSize</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#7b8fd25de7858cfef37028cd4d8f52de" class="el">SetSize</a> (int newsize, int growby=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#83feaa64c8e9087b27f2fe9f31eb6b18" class="el">ElementAt</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#ca08bd731b2d2e2aa0fab19d799fab1c" class="el">Add</a> (<a href="classVector.md" class="el">Vector</a> &amp;vector, LONG key=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#e684ad714ddf52bc2fde6407345d248c" class="el">LookUp</a> (const <a href="classVector.md" class="el">Vector</a> &amp;vector, LONG key=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#7176e2559b8b79ee6c0e81dc443736f2" class="el">LookUpHashKey</a> (<a href="classVector.md" class="el">Vector</a> &amp;vector)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#ffc1f2756ffac4fb622cb8da822b705a" class="el">GetHashKey</a> (LONG key)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#93c5ed7513baef01b68f7c5bf3af97f4" class="el">GetHashKey</a> (const <a href="classVector.md" class="el">Vector</a> &amp;vector)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#ae22276c7490efee40cd72529c7a83b3" class="el">Empty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#91e0d6169398953942fe60c3946c79d7" class="el">operator[]</a> (int index) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#710e01c9f42500b31117688d8eaebfac" class="el">operator[]</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#04de455e490cb138d4e29fc5200447be" class="el">Shrink</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#0ac7e1b2001abc2c00920218c910595e" class="el">VectorCollection</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#5ddee372fb723ebd6ba16c8f3e04d343" class="el">~VectorCollection</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#f2259ebe9d1c07ceb60119edb0a86416" class="el">GetSize</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#7b8fd25de7858cfef37028cd4d8f52de" class="el">SetSize</a> (int newsize, int growby=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#ca08bd731b2d2e2aa0fab19d799fab1c" class="el">Add</a> (<a href="classVector.md" class="el">Vector</a> &amp;vector, LONG key=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#e684ad714ddf52bc2fde6407345d248c" class="el">LookUp</a> (const <a href="classVector.md" class="el">Vector</a> &amp;vector, LONG key=-1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#7176e2559b8b79ee6c0e81dc443736f2" class="el">LookUpHashKey</a> (<a href="classVector.md" class="el">Vector</a> &amp;vector)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#ae22276c7490efee40cd72529c7a83b3" class="el">Empty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#04de455e490cb138d4e29fc5200447be" class="el">Shrink</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#95a7201fab22e53b513f89e23fbca949" class="el">GetArray</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#ddc54dfc91e8489e924df466a56ffe1e" class="el">GetAt</a> (int index) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#83feaa64c8e9087b27f2fe9f31eb6b18" class="el">ElementAt</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#91e0d6169398953942fe60c3946c79d7" class="el">operator[]</a> (int index) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#710e01c9f42500b31117688d8eaebfac" class="el">operator[]</a> (int index)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a> &amp; &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#745f7ddee32c302c3110f18ca7a4b180" class="el">m_array</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CArray&lt; <a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a> &amp; &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#745f7ddee32c302c3110f18ca7a4b180" class="el">m_array</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-member-functions">Private Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#ffc1f2756ffac4fb622cb8da822b705a" class="el">GetHashKey</a> (LONG key)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#93c5ed7513baef01b68f7c5bf3af97f4" class="el">GetHashKey</a> (const <a href="classVector.md" class="el">Vector</a> &amp;vector)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="private-attributes">Private Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHashArray.md" class="el">HashArray</a>&lt; <a href="classHashNode.md" class="el">HashNode</a> *, <a href="classHashNode.md" class="el">HashNode</a> * &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#829264e08d8250a6eb3c1d2487799b43" class="el">m_hasharray</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">CArray&lt; <a href="classHashNode.md" class="el">HashNode</a> *, <a href="classHashNode.md" class="el">HashNode</a> * &gt; </td>
<td class="memItemRight" data-valign="bottom"><a href="classVectorCollection.md#829264e08d8250a6eb3c1d2487799b43" class="el">m_hasharray</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

