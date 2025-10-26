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

# Quaterni.h File Reference

`#include "FileCons.h"`  
`#include "`<a href="Vector_8h-source.md" class="el"><code>Vector.h</code></a>`"`  

Include dependency graph for Quaterni.h:

<span class="image placeholder" original-image-src="Quaterni_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Quaterni.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="Quaterni_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Quaterni.hdep_map"></span>

[Go to the source code of this file.](Quaterni_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classQuaternion.md" class="el">Quaternion</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#5ded92490cedb87bbeaed9f7dec95a84" class="el">__QUATERNI_H</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#886801291d0b13c7836ad19a19fd48b9" class="el">IdentityQ</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#53f2b9ac633e0057a6afa297f42f06f2" class="el">TransformVector</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;q, <a href="classVector.md" class="el">Vector</a> &amp;<a href="structTQAVGouraud.md" class="el">v</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#7a2ab26ca21ece08d92e9f46b6c96470" class="el">Dot</a> (const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;a, const <a href="classQuaternion.md" class="el">Quaternion</a> &amp;b)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#16f0ee948800b237780f9b7b38068efd" class="el">RotateVQ</a> (float angle, const <a href="classVector.md" class="el">Vector</a> &amp;axis)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#743e737bdf4b64049d0fc6a7462b7705" class="el">XRotateRadiansQ</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#38fb50c3e8021718935a2c0d31d3e0c9" class="el">YRotateRadiansQ</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#ff71241ae6be61adcf84d2928dbcf427" class="el">ZRotateRadiansQ</a> (float anglerad)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#b10b0c1dc6c1e5ae2f185fcaed561f72" class="el">XRotateQ</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#0494837754cefe126a0141ef97a25397" class="el">YRotateQ</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#607ad8fd2d40d33e969c1f26e52d3da6" class="el">ZRotateQ</a> (float angle)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#82fccd3c598fca3058e2afb5ecf1b2de" class="el">YXZRotateRadiansQ</a> (float y, float x, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#10bb912c8ad0fe8894cdebae08af1577" class="el">YXRotateRadiansQ</a> (float y, float x)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#75d5db2f8a49daaa5afb22cb1eaef5b5" class="el">YXZRotateQ</a> (float y, float x, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#87257da5e304f3560131d39f8d74b275" class="el">YXRotateQ</a> (float y, float x)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#aefc203c35d02b9b7b4071b8fe1e4c4c" class="el">XYZRotateQ</a> (float x, float y, float z)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#51692f9c4b5b036d3c3cfd78d99053c8" class="el">XYRotateQ</a> (float x, float y)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classQuaternion.md" class="el">Quaternion</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Quaterni_8h.md#dcbdf5fc577cb21a8807236a1eb23e78" class="el">VectorsToStandardQ</a> (const <a href="classVector.md" class="el">Vector</a> &amp;becomezdir, const <a href="classVector.md" class="el">Vector</a> &amp;becomeydir)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

