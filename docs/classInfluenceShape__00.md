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

# InfluenceShape Class Reference

`#include <`<a href="influenc_8h-source.md" class="el"><code>influenc.h</code></a>`>`

Inheritance diagram for InfluenceShape:

<span class="image placeholder" original-image-src="classInfluenceShape__inherit__graph.gif" original-image-title="" border="0" usemap="#InfluenceShape__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for InfluenceShape:

<span class="image placeholder" original-image-src="classInfluenceShape__coll__graph.gif" original-image-title="" border="0" usemap="#InfluenceShape__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classInfluenceShape-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#e976136b845128b8c3ffc6df95689a1b" class="el">SetMatrices</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#69c0e794ea931eadcfa6bd26a668bfce" class="el">InfluenceShape</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#295b20d009018e2440e3b3ab2d053928" class="el">GetAttenuation</a> (float d)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#7490d5dd0cac19f83890f8b849062bc1" class="el">SetAttenuation</a> (float attenuation)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual float </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#02e6db22f790c52d2b24411be1f0581a" class="el">Falloff</a> (<a href="classVector.md" class="el">Vector</a>)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual <a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#ed465fcabfc74d46120708c749bd1cb1" class="el">Attract</a> (<a href="classVector.md" class="el">Vector</a>, float)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual <a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#8fb905b10b0a894a9e053a0648139da0" class="el">Vortex</a> (<a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a>, float)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual <a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#b8901bf3e1a17ce3905d633600d9a41f" class="el">Friction</a> (<a href="classVector.md" class="el">Vector</a>, <a href="classVector.md" class="el">Vector</a>, float)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual float </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#537d66a6bbd42ad08263de580a2b2ed5" class="el">Lighting</a> (const <a href="classVector.md" class="el">Vector</a> &amp;, <a href="classVector.md" class="el">Vector</a> &amp;, float &amp;)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual float </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#863d00ecaa895fef07eee8d995926179" class="el">LightingNoCap</a> (const <a href="classVector.md" class="el">Vector</a> &amp;p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#598208f3fbafd245609ae9fc5cb320a1" class="el">Transform</a> ()=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#d15806044fc54bed18e5ebcc9fec450f" class="el">IsInside</a> (<a href="classVector.md" class="el">Vector</a> p)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#747a5ea3a354d8d9cc6ce1138eacc6ce" class="el">FindBounds</a> (<a href="classVector.md" class="el">Vector</a> &amp;min, <a href="classVector.md" class="el">Vector</a> &amp;max)=0</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">Bone * </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#a57fc812a9521b8c0ede9a2724351a55" class="el">bone</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#c566097eca4afce9fbc6163180f328eb" class="el">worldmatrix</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#e63ec5cd1c3a74c36c45f4c1e2524ae6" class="el">worldinverse</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#a5ee57887ab68b45e635e12623ba1432" class="el">screenmatrix</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#ba7a4b02666c3118a86ddb75ecb809e2" class="el">screeninverse</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#44eb61281bf6a480ec9aeb4bb182bc52" class="el">steadyscreenmatrix</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#7a1a343404f3fab290d884351454c3b9" class="el">m_k0</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#b33ad3849b8bb8ef848fcfc75ea143e6" class="el">m_k2</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classInfluenceShape.md#7d5e2f9ec5ee7c5f0fe731f5d737905f" class="el">m_k1</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

