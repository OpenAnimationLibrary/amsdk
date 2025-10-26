<div class="tabs">

- [Main Page](index.md)
- [Classes](annotated.md)
- <span id="current">[Files](files.md)</span>
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [File List](files.md)
- [File Members](globals.md)

</div>

<div class="nav">

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# Matrix34.h File Reference

`#include "`<a href="Matrix44_8h-source.md" class="el"><code>Matrix44.h</code></a>`"`  
`#include "`<a href="Matrix33_8h-source.md" class="el"><code>Matrix33.h</code></a>`"`  
`#include "`<a href="Rotate_8h-source.md" class="el"><code>Rotate.h</code></a>`"`  

Include dependency graph for Matrix34.h:

<span class="image placeholder" original-image-src="Matrix34_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Matrix34.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="Matrix34_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Matrix34.hdep_map"></span>

[Go to the source code of this file.](Matrix34_8h-source.md)

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
&#10;<h2 id="classes">Classes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classMatrix34.md" class="el">Matrix34</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#840773f9e5364b95d0a623450fa3027e" class="el">operator *</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>, const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#53bc1bcf2b063d55351688384d17998b" class="el">YXZRotate</a> (float yangle, float xangle, float zangle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#cc49a8715c21e919bc629b6fdbd486a7" class="el">RotateV</a> (float angle, const <a href="classVector.md" class="el">Vector</a> &amp;axis)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#bbce79da2370f9e02fed127f9c4d3c64" class="el">XRotate</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#1308c15d4e6251301d2115f1e2058e55" class="el">YRotate</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#2c944781e9a46e4bdf64db38dfff32fb" class="el">ZRotate</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#f57d590b1c44db757c91c7dd9790ba2e" class="el">CreateEulerMatrix</a> (const <a href="classRotate.md" class="el">Rotate</a> &amp;rotate)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#3f6d2e3ea3f27d02aa95c019e94840f9" class="el">TransformVector</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;matrix, <a href="classVector.md" class="el">Vector</a> &amp;p)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#a9e9d4b367969631692f3073684568ac" class="el">Identity34</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix44.md" class="el">Matrix44</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#1f67edc0a5af6e7b22daea08712d44d6" class="el">ToMatrix44</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix44.md" class="el">Matrix44</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#c64f1bdcb8c4bdc1751f08c185369751" class="el">ToMatrix44</a> (const <a href="classMatrix33.md" class="el">Matrix33</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#593ddd99bc0c69f4c8d8d32a394d2e76" class="el">ToMatrix33</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix33.md" class="el">Matrix33</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#c93fe4af36147fe6a797312f81e764f5" class="el">ToMatrix33</a> (const <a href="classMatrix44.md" class="el">Matrix44</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#0d513a874dfb689f1a0f6cd2af63ddcd" class="el">ToMatrix34</a> (const <a href="classMatrix44.md" class="el">Matrix44</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#c4b1ff6e9c551581f4feed6eff7c7079" class="el">ToMatrix34</a> (const <a href="classMatrix33.md" class="el">Matrix33</a> &amp;m)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#3e7e34ea827694cc86db2598b7a5fdcd" class="el">VectorsToStandard</a> (const <a href="classVector.md" class="el">Vector</a> &amp;becomezdir, const <a href="classVector.md" class="el">Vector</a> &amp;becomeydir)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#ac7d11f3570f7c43f6029349705ab9f1" class="el">StandardToVectors</a> (const <a href="classVector.md" class="el">Vector</a> &amp;newzdir, const <a href="classVector.md" class="el">Vector</a> &amp;newydir)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#d2f1ab41a7ee2044dfc0b016d7f62075" class="el">Translatef</a> (float x, float y, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#d2d3a3c8450ced346e378811824bd194" class="el">TranslateV</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#85ad183cd6e45377da219513d7ac2487" class="el">Scalef</a> (float x, float y, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#90daeb8672a3c3f34ac377f3b0474d7d" class="el">ScaleV</a> (const <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#6d9ecae044b2f972995de8fdec41e29f" class="el">Rotatef</a> (float angle, float x, float y, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#78a6ec4b4452a9f66bf15500bca8ba12" class="el">TransformVectorNoTranslate</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;m, <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#0e8a14e7048a862f4a3905a9e7fe0283" class="el">XRotateRadians</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#6c24d2cf7d82e6cedc87fd9049cf717a" class="el">YRotateRadians</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classMatrix34.md" class="el">Matrix34</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Matrix34_8h.md#f6f959eb3a4f086ed4191637171b32e3" class="el">ZRotateRadians</a> (float anglerad)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

