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

# FlockBuf Class Reference

`#include <`<a href="FlockBuf_8h-source.md" class="el"><code>FlockBuf.h</code></a>`>`

Collaboration diagram for FlockBuf:

<span class="image placeholder" original-image-src="classFlockBuf__coll__graph.gif" original-image-title="" border="0" usemap="#FlockBuf__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classFlockBuf-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#29480e91b531ca99bdbc7120c892410f" class="el">FlockBuf</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#04d7f3fea5ac09a7a3fef8458ca273cc" class="el">~FlockBuf</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classFlockBuf.md" class="el">FlockBuf</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#a3697208f4541da5551916476326e64a" class="el">operator=</a> (const <a href="classFlockBuf.md" class="el">FlockBuf</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classPeerBox.md" class="el">PeerBox</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#0761e147b6ffe2175fb6299a09b2681d" class="el">CreatePeerBoxList</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#742066a694a72f0cd0d336ddd3a4726d" class="el">DistributeBoids</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#c8c5920f412942d4afff32534e28c8d2" class="el">InitBoidList</a> (int num)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#1539917264b5bf0b0576b981f9ba1312" class="el">Clear</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#9d1b5f37c7e3a27fcdd8ba8b248d8cf9" class="el">GetFallOffValue</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="classFlockBuf.md#83878c91171338902e0fe0fb97a8c47a" class="el">p</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classBoid.md" class="el">Boid</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#67a6bea759f62503eb7be1357a87eca7" class="el">FindClosestNeighbor</a> (<a href="classBoid.md" class="el">Boid</a> *boid, <a href="classBoid.md" class="el">Boid</a> *excludedboid)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#83878c91171338902e0fe0fb97a8c47a" class="el">p</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#96e9998f902ae3b77d6d213b4f5b43ba" class="el">worldp</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#c18df01a522f8c312f53040e31cb7633" class="el">worlddirection</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#b82109c78f0d13653a9f00801d397a36" class="el">prevpos</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#0bb100ec331c433faf4bb679606861c4" class="el">ulbounds</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#faa8c45bc2b8846635d687596170e4ce" class="el">lrbounds</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#c6e49c4484a247898f7060c08ddbea6b" class="el">pbwidth</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#f6e7f6f1911ff5f91ff70a57009be41a" class="el">pbheight</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#e63d0e2bf7a99c3ea7a6978e0633718e" class="el">pbdepth</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classInfluenceShape.md" class="el">InfluenceShape</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#45d909320decdf3a4f32ef8dba3c1071" class="el">influenceshape</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#200c1eead926e8b4332b7cf0ceff49cb" class="el">subdiv</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#6ec30e7ab15fd6c269d2deed8a18b280" class="el">numboids</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classBoid.md" class="el">Boid</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#c2cd2871e1985bdb650f159f907ea785" class="el">boids</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classPeerBox.md" class="el">PeerBox</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#0325cfc032f4c760e576e9494e15bdd0" class="el">peerboxlist</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#56cf036bb7e034c1500fa2af3a15aab5" class="el">prevframe</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlockBuf.md#3f2cabb5768270bb90220e72bd03b7a6" class="el">m_maxactionoffset</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

