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

# Matrix44 Class Reference

`#include <`<a href="Matrix44_8h-source.md" class="el"><code>Matrix44.h</code></a>`>`

Collaboration diagram for Matrix44:

<span class="image placeholder" original-image-src="classMatrix44__coll__graph.gif" original-image-title="" border="0" usemap="#Matrix44__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classMatrix44-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#b7f07fc20d9fb563302bdbe20e3a63b1" class="el">Matrix44</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#74415f95f46d1f45bc1cb3a2edd76649" class="el">Matrix44</a> (const <a href="classMatrix44.md" class="el">Matrix44</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#7ed18b977d65f2acde069c293eb88564" class="el">Matrix44</a> (float fill)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#cf91194718f188ff1cfe783db06940c6" class="el">Matrix44</a> (const <a href="classVector4.md" class="el">Vector4</a> &amp;<a href="structTQAVGouraud.md" class="el">v0</a>, const <a href="classVector4.md" class="el">Vector4</a> &amp;<a href="Rave_8h.md#6654c734ccab8f440ff0825eb443dc7f" class="el">v1</a>, const <a href="classVector4.md" class="el">Vector4</a> &amp;<a href="Rave_8h.md#1b267619c4812cc46ee281747884ca50" class="el">v2</a>, const <a href="classVector4.md" class="el">Vector4</a> &amp;v3)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#5a7a06e1b6b006b76edc6ca2cda75090" class="el">Matrix44</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;quat)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix44.md" class="el">Matrix44</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#e09e466b8db0deec1139be2f7a94820c" class="el">operator *=</a> (const <a href="classMatrix44.md" class="el">Matrix44</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classVector4.md" class="el">Vector4</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#c83e70d16af2690580e83e3e308baa56" class="el">operator[]</a> (int row) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector4.md" class="el">Vector4</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#f9fe1cb2b05e91781b91213489f0f8ac" class="el">operator[]</a> (int row)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#d59f462f5cf3ab5702c6813842619a2f" class="el">SetIdentity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix44.md" class="el">Matrix44</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#9be2484bb59f9757045dc03b05463ada" class="el">Transpose</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix44.md" class="el">Matrix44</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#354fb8938cd1eb77d5dd2df81f85facf" class="el">Inverse</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix44.md" class="el">Matrix44</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#2413ff849882d505f521b8e0f4b144d0" class="el">operator *</a> (const <a href="classMatrix44.md" class="el">Matrix44</a> &amp;b) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#2e6b75e015e5a1546ba0d9a4883d7f59" class="el">operator *</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector4.md" class="el">Vector4</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#822f49f7fb9326d8bacb64e75e9af185" class="el">operator *</a> (const <a href="classVector4.md" class="el">Vector4</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>) const</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-attributes">Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector4.md" class="el">Vector4</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#4c625e23a77bbd438ad6f4c0aaf1f49f" class="el">v</a> [4]</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="friends">Friends</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix44.md" class="el">Matrix44</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix44.md#18bb1c4cbd87cdeb152576c403194fc7" class="el">Identity44</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

