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

# Quaternion Class Reference

`#include <`<a href="Quaterni_8h-source.md" class="el"><code>Quaterni.h</code></a>`>`

Collaboration diagram for Quaternion:

<span class="image placeholder" original-image-src="classQuaternion__coll__graph.gif" original-image-title="" border="0" usemap="#Quaternion__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classQuaternion-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#74da500a74f7f7e5d7ab2881a106b7b8" class="el">Quaternion</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#57f45955d8500ffb7b4005030f09c4e8" class="el">Quaternion</a> (const <a href="classMatrix33.md" class="el">Matrix33</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#d6c9066dfa2533e83d84b9126433ea5f" class="el">Quaternion</a> (const <a href="classMatrix34.md" class="el">Matrix34</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#148cec8d05987da31f6fc45b2240315f" class="el">Quaternion</a> (const <a href="classVector.md" class="el">Vector</a> &amp;vec, float scalar)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#96ca1fd1a4bbc175d9f20a9f7f824b5e" class="el">Quaternion</a> (float x, float y, float z, float s)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#91ad3bf1e80e7a42f49cae5eeed5855a" class="el">Quaternion</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;q)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#96fe9762b1fb0efeeb0f773a23b586dd" class="el">Quaternion</a> (float scalar)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#cb8013c3a1eddf6b0f6808dd5126704d" class="el">Quaternion</a> (float radangle, const <a href="classVector.md" class="el">Vector</a> &amp;axis)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#fe0f12bdf365a564bec5156aab14fb4d" class="el">Quaternion</a> (const <a href="classRotateVector.md" class="el">RotateVector</a> &amp;rv)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#a99552adccd85315856c0cff860f5458" class="el">Quaternion</a> (const <a href="classRotateSphere.md" class="el">RotateSphere</a> &amp;rs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#49081a82917851ca1a7546575f565160" class="el">Quaternion</a> (const <a href="classRotateSphere.md" class="el">RotateSphere</a> &amp;rs, Bone *bone)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#a57fed1f67dbd4ed69ce5bbec88f946d" class="el">Quaternion</a> (const <a href="classRotateEuler.md" class="el">RotateEuler</a> &amp;re)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#f16617ae0e8e80bbb873e7c18d38fdd5" class="el">Quaternion</a> (const <a href="classRotateEuler.md" class="el">RotateEuler</a> &amp;re, BOOL isyxz)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#a760b29b6476e4e4752cebeb525da3ea" class="el">GetV</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#e866a207c4a0d6c19660b8b07eecc027" class="el">GetW</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#69a47c77c12313611da1cb933aa80481" class="el">SetV</a> (const <a href="classVector.md" class="el">Vector</a> &amp;vec)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#f6343ae4e5910dffc15948a424579d85" class="el">SetV</a> (int index, float value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#ddf8bacb3d77487a2297f3f754881d20" class="el">SetW</a> (float scalar)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#a21a34341c3875a582994e14d7d246de" class="el">Set</a> (float x, float y, float z, float pw)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#ba52930814165e884b7791e7a15d875c" class="el">Set</a> (<a href="classVector.md" class="el">Vector</a> pv, float pw)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#cbf480e0d41e4d79a3884f5f771a0508" class="el">Set</a> (float fillvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#d59f462f5cf3ab5702c6813842619a2f" class="el">SetIdentity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#de47ca08dac306ef3fc3bec670a913c0" class="el">GetXAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#558eaf2afb73de18b7c3af680cb49785" class="el">GetYAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#c3333f6ac3cff5098d7d24026186cdc6" class="el">GetZAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#02c0ed9626e35facfab79829fbb65b91" class="el">GetAngle</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#db5d9e28ee32f8a47fc1a1eb9017d642" class="el">GetAxis</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#b079b86b9631d2839b160e1c2dd12945" class="el">SetAngleAxis</a> (float radangle, const <a href="classVector.md" class="el">Vector</a> &amp;axis)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#f227e3de1ac12ade4ca53f700045fb5a" class="el">Norm</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#a1bfc4d0824ba8647f770a929c13e4d1" class="el">Normalize</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#bd373bc3c3b4668a605503e54777902e" class="el">Normalized</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#6a5aefd58b4881253e4e0563c2984e0f" class="el">NormalizeLength</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#483998695f1bc366658a8163cea03aff" class="el">Conjugate</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#354fb8938cd1eb77d5dd2df81f85facf" class="el">Inverse</a> () const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#501ef41cbae624e66dc2b6dfe89f38ff" class="el">Negate</a> (void)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#2c7a0650161ae2554bcb061c523a268a" class="el">IsIdentity</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#62c99e23c7ba7b3a9caca0a98fda0261" class="el">operator==</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;a) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#7ba0e7793ec8ecacfb86869ddf620fc3" class="el">operator!=</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;a) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#ba8ae2852f7d9942ee9eb86906a9edd4" class="el">operator *=</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;q)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#69beae508cd8025dbd0d419ee219aa98" class="el">operator *=</a> (float scalar)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#e3998ea11d9c9a3436831ead71516687" class="el">operator/=</a> (float scalar)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#e4a6b0b0d672e04ce17043eee3e7a6be" class="el">operator+=</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;q2)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#628a6faa4ba425cf087bcc104c2d7c82" class="el">operator-=</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;q2)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#a64d9bfa47acb5b02cdfeef8360d38fe" class="el">operator-</a> (void) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float &amp; </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#afa3b3be64f86f689de4bf05a470fc17" class="el">operator[]</a> (int i)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#56bd1e633f412f07706e05b60f9eb2bc" class="el">operator[]</a> (int i) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md#df8d20f5cdf2f1ccfb05c2a4a3249742" class="el">operator *</a> (const <a href="classQuaternion.md"