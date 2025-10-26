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

# Matrix33 Class Reference

`#include <`<a href="Matrix33_8h-source.md" class="el"><code>Matrix33.h</code></a>`>`

Collaboration diagram for Matrix33:

<span class="image placeholder" original-image-src="classMatrix33__coll__graph.gif" original-image-title="" border="0" usemap="#Matrix33__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classMatrix33-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#5d541b57470b6b5699423cdf14288296" class="el">Matrix33</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#4c73a920e61b8e058a45d78d276e84e7" class="el">Matrix33</a> (const <a href="classMatrix33.md" class="el">Matrix33</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#78a74365d5e9ee2e7ce087c745abea87" class="el">Matrix33</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;q)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#2a2322a712ec5467e62b027b1b029306" class="el">Matrix33</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v0</a>, const <a href="classVector.md" class="el">Vector</a> &amp;<a href="Rave_8h.md#6654c734ccab8f440ff0825eb443dc7f" class="el">v1</a>, const <a href="classVector.md" class="el">Vector</a> &amp;<a href="Rave_8h.md#1b267619c4812cc46ee281747884ca50" class="el">v2</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#5343ef2e0dbe7ff10c34d849f51fb0b4" class="el">Matrix33</a> (float fill)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#88d6927c5c485766716c80dd53abfb04" class="el">operator=</a> (const <a href="classMatrix33.md" class="el">Matrix33</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#dea9a2d7300dfb1c2f03dcfeb4add49d" class="el">operator *=</a> (const <a href="classMatrix33.md" class="el">Matrix33</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#c83e70d16af2690580e83e3e308baa56" class="el">operator[]</a> (int row) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#f9fe1cb2b05e91781b91213489f0f8ac" class="el">operator[]</a> (int row)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#d59f462f5cf3ab5702c6813842619a2f" class="el">SetIdentity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#9be2484bb59f9757045dc03b05463ada" class="el">Transpose</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#9e6f899e0e0ac233a46bfbdd1ce01541" class="el">TransposeSelf</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#354fb8938cd1eb77d5dd2df81f85facf" class="el">Inverse</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#de47ca08dac306ef3fc3bec670a913c0" class="el">GetXAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#558eaf2afb73de18b7c3af680cb49785" class="el">GetYAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#c3333f6ac3cff5098d7d24026186cdc6" class="el">GetZAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#e96e17f3da6ecb36714bcd394dcfa614" class="el">operator *</a> (const <a href="classMatrix33.md" class="el">Matrix33</a> &amp;b) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#2e6b75e015e5a1546ba0d9a4883d7f59" class="el">operator *</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#aeaa5e9b85f5001254bd22e4792ae77a" class="el">Set</a> (float fill)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#6023d3237a5f0c776ec6b3b6bf0b6a2e" class="el">SetTranslate</a> (const <a href="classVector2.md" class="el">Vector2</a> &amp;t)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#9f72d8178e7d0c85c91e4fbbd67b47ce" class="el">MakeOrthogonal</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="protected-attributes">Protected Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#f493789db894265c54fa31d991268ab8" class="el">v</a> [3]</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="friends">Friends</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classVector2.md" class="el">Vector2</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#f15cd4952b22c771c6a75fd123912b71" class="el">operator *</a> (const <a href="classMatrix33.md" class="el">Matrix33</a> &amp;m, const <a href="classVector2.md" class="el">Vector2</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#27ae8456c2ae140937e435ac4628672a" class="el">Identity33</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#6d8713f8f25beebaa0d19efd802fdb6b" class="el">RotateVRadians33</a> (float angle, const <a href="classVector.md" class="el">Vector</a> &amp;axis)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#13f5334907b5d416d961751ad3ac4070" class="el">XYRotateRadians33</a> (float xangle, float yangle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#ddcac8a2a717aff88afe853d94ff5e1a" class="el">YXRotateRadians33</a> (float yangle, float xangle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#89d582fba019a45a775572f3b4167cb6" class="el">ZXRotateRadians33</a> (float zangle, float xangle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#5a7925340763ed12816f8d8b31920c7d" class="el">YXZRotateRadians33</a> (float yangle, float xangle, float zangle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#acb01a82f76220c50a5ad50c3aa2606f" class="el">ZXZRotateRadians33</a> (float zangl1, float xangle, float zangl2)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#60694456fa864eb9fd0fbe7179d6d614" class="el">XRotate33</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#34f0f2c3d7bf495acd1139f0e955ec43" class="el">YRotate33</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#86a327cd77178ab1cde5454e8b4a6f6c" class="el">ZRotate33</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#9c9c0268eb98a23cd825e8ec9f82815d" class="el">YXRotate33</a> (float yangle, float xangle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#7814ee8a34666d68ebc117e6107fe191" class="el">ZXRotate33</a> (float zangle, float xangle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#b87bf0da3b554d1b3e7ed5235e0f5923" class="el">YXZRotate33</a> (float yangle, float xangle, float zangle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#71d1ac961dee820d368d53e79adf65a8" class="el">ZXZRotate33</a> (float zangl1, float xangle, float zangl2)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#662ae926e6599cad3408600afa7833da" class="el">RotateV33</a> (float angle, const <a href="classVector.md" class="el">Vector</a> &amp;axis)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">MATRIXEXPORT <a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#bef8283f7cb54eb6226eb684b3e41813" class="el">Rotate2V33</a> (const <a href="classVector.md" class="el">Vector</a> &amp;from, const <a href="classVector.md" class="el">Vector</a> &amp;to)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#889f72090eee4546377cdce79ba1d212" class="el">XRotateRadians33</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#42dffcda8f9f377df325ba611695cd1d" class="el">YRotateRadians33</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix33.md#4853f244734d6f957de647aa8eda2de8" class="el">ZRotateRadians33</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a hre