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

# Matrix34 Class Reference

`#include <`<a href="Matrix34_8h-source.md" class="el"><code>Matrix34.h</code></a>`>`

Collaboration diagram for Matrix34:

<span class="image placeholder" original-image-src="classMatrix34__coll__graph.gif" original-image-title="" border="0" usemap="#Matrix34__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classMatrix34-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#b7df3480a5b0aefec571740eeba65703" class="el">Matrix34</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#a6e8d357b4c9468d22edf4983d5324e6" class="el">Matrix34</a> (const <a href="classVector4.md" class="el">Vector4</a> &amp;, const <a href="classVector4.md" class="el">Vector4</a> &amp;, const <a href="classVector4.md" class="el">Vector4</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#39ee6fefceb3d81a599efe0ebc4ddf9a" class="el">Matrix34</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#dd6ef5d21555392a40bd5a4c63de13f9" class="el">Matrix34</a> (float fillvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#e6e45ccdd56be82cb058490e303a6764" class="el">Matrix34</a> (const <a href="classRotateVector.md" class="el">RotateVector</a> &amp;rotate)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#22fe3675076def08f0392013cacea7e2" class="el">Matrix34</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#f3b899dc18fdb6fd42b6c279b066c7ed" class="el">Matrix34</a> (const <a href="classRotateEuler.md" class="el">RotateEuler</a> &amp;re)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#2270c00abe385727a594aa8d4bc89d36" class="el">Matrix34</a> (const <a href="classTSQ.md" class="el">TSQ</a> &amp;tsq)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#0a0e176d147b6c7af661b93d25691285" class="el">SetIdentity</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#f0738c4e8f53227f03b0cf659b625304" class="el">InitBottomRow</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#b57a2c04a471b23866f63acf6c99727a" class="el">operator *=</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classVector4.md" class="el">Vector4</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#c83e70d16af2690580e83e3e308baa56" class="el">operator[]</a> (int row) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector4.md" class="el">Vector4</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#f9fe1cb2b05e91781b91213489f0f8ac" class="el">operator[]</a> (int row)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#bde1ab21f6cc9658ef27fd981f9158c4" class="el">Set</a> (const <a href="classVector4.md" class="el">Vector4</a> &amp;a, const <a href="classVector4.md" class="el">Vector4</a> &amp;b, const <a href="classVector4.md" class="el">Vector4</a> &amp;c)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#d59f462f5cf3ab5702c6813842619a2f" class="el">SetIdentity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#5634d8f5dbdf22e72677fccda12e43df" class="el">Transpose</a> (void) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#52f76e697bcd441f768d94a75f9af147" class="el">Inverse</a> (void) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#708b3b3b8999da237597816d9d535297" class="el">SetTranslate</a> (const <a href="classVector.md" class="el">Vector</a> &amp;t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#9d51537b211615615122aaa2eddd119d" class="el">GetTranslate</a> (void) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#2b1748712a605cdea8efd63a19fcc239" class="el">NoTranslate</a> (void) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#47a98f3db5918c55c1f9f97bd9af2803" class="el">GetScaleMatrix</a> (void) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#573e021e042c84d57d90a02725880580" class="el">GetScaleVector</a> (void) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#9867b8784fe304cb3a6d78adf089961b" class="el">operator==</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;a) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#aba8e7213c48155d705b223ba7220525" class="el">operator!=</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;a) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#de47ca08dac306ef3fc3bec670a913c0" class="el">GetXAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#558eaf2afb73de18b7c3af680cb49785" class="el">GetYAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#c3333f6ac3cff5098d7d24026186cdc6" class="el">GetZAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#39b143160532af71c070633523a16e7b" class="el">operator *</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#d35f5856c5a143b96123afe5befee5d3" class="el">operator *</a> (const <a href="classVector.md" class="el">Vector</a> &amp;) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#632951364224f535b63ffa8b9c7ed431" class="el">InvertRotateTranslate</a> () const</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-attributes">Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector4.md" class="el">Vector4</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#f493789db894265c54fa31d991268ab8" class="el">v</a> [3]</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="friends">Friends</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#840773f9e5364b95d0a623450fa3027e" class="el">operator *</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>, const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#a9e9d4b367969631692f3073684568ac" class="el">Identity34</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#d2f1ab41a7ee2044dfc0b016d7f62075" class="el">Translatef</a> (float x, float y, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#d2d3a3c8450ced346e378811824bd194" class="el">TranslateV</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#85ad183cd6e45377da219513d7ac2487" class="el">Scalef</a> (float x, float y, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#90daeb8672a3c3f34ac377f3b0474d7d" class="el">ScaleV</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#9c8818c91a3780c41e48380281591da0" class="el">RotateVRadians</a> (float angle, const <a href="classVector.md" class="el">Vector</a> &amp;axis)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#6d9ecae044b2f972995de8fdec41e29f" class="el">Rotatef</a> (float angle, float x, float y, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#e73d9c69d35f373186e10150139fdbfb" class="el">Rotate2V</a> (const <a href="classVector.md" class="el">Vector</a> &amp;from, const <a href="classVector.md" class="el">Vector</a> &amp;to)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#0e8a14e7048a862f4a3905a9e7fe0283" class="el">XRotateRadians</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md#6c24d2cf7d82e6cedc87fd9049cf717a" class="el">YRotateRadians</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="c