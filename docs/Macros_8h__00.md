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

# Macros.h File Reference

`#include <math.h>`  
`#include "`<a href="Fastftol_8h-source.md" class="el"><code>Fastftol.h</code></a>`"`  

Include dependency graph for Macros.h:

<span class="image placeholder" original-image-src="Macros_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Macros.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="Macros_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/Macros.hdep_map"></span>

[Go to the source code of this file.](Macros_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classMenuDoc.md" class="el">MenuDoc</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#cfd007269cf70c4227e2e733cd9e8636" class="el">__MACROS_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#5fc5e255045de6ee86047f56ba211a51" class="el">__OS9ROS_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#1d37a64ea4e4add5f53e05796eac6119" class="el">ABS</a>(a)   (((a)&lt;0)?(-(a)):(a))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#59feb3c122aef6bc1274714d63378334" class="el">MAX</a>(a, b)   (((a)&gt;(b))?(a):(b))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#34c39f670306181866ef5b3d2e61ad72" class="el">MIN</a>(A, B)   ((A)&lt;(B)?(A):(B))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#d234c05689bfd9dde94b418b1dba86b9" class="el">ROWBYTES</a>(A)   (((A)+15)&gt;&gt;4&lt;&lt;1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#6fb2982081cee248a2b1d9639993f634" class="el">ROWWORDS</a>(A)   (((A)+15)&gt;&gt;4)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#4a3e1eaf439a8f711aa83e5a6cc1b76b" class="el">ROUNDOFF</a>(A)   (LONG)((A)&lt;(0)?((A)-.5):((A)+.5))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#29ff52b7d513aadbecee8d379b3e1d7b" class="el">ISODD</a>(A)   (A&amp;0x1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#633e51a25d61d100f5be64fbb848e353" class="el">INVERSE</a>(A)   { A.x=-A.x;A.y=-A.y;A.z=-A.z; }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#d7106fa7ff2ef46ed6913547f055f6a2" class="el">FLOOR</a>(a)   ((a)&gt;(0) ? (int)(a) : -(int)(-a))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#24a2a91ce1c395b0d626178ccdf4144b" class="el">CEILING</a>(a)   ((a)==(int)(a) ? (a) : (a)&gt;0 ? 1+(int)a : -(1+(int)(-a)))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#fd4285aeb4387dda2c03f4d96135b208" class="el">SIGN</a>(x)   ((x) &gt;= 0 ? 1 : -1)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#a273878eead34934624138fae5ff2e4d" class="el">NUMELEMENTS</a>(array)   (sizeof(array)/sizeof(array[0]))</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#ce580edfbdfedafad6a10ad9748540d7" class="el">NULLDELETE</a>(a)   { delete a; a = NULL; }</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#f9526c0abef33efac4c9ad5e9a9426c9" class="el">PADWIDTH</a>(x)   (((x)*8 + 31) &amp; (~31))/8</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#02b0da4211648559373db9255f9f0891" class="el">DOC</a>(A)   ""</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#e6e6480a9ca65fe59160a87ac886d734" class="el">MENU_DOC</a>(A, B)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#9eef548cd037fba9c87e386298f53872" class="el">DLLEXPORT</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#495073ac7cbcaab66a4aa8ab73beacea" class="el">Round</a> (float &amp;number, float modulo)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">float </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#f2652f9370c8bebd9390cf48e93a8804" class="el">RoundValue</a> (float number, float modulo)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="Rave_8h.md#f03dc93db7c58a69ed5c83e1fa49cf0e" class="el">long</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#c6c07df7f3eca3eb9b9e0b085edb9642" class="el">RoundValue</a> (double number)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#6b5e2a07d136b8f00d46862572354d4d" class="el">AddMenuDoc</a> (<a href="classMenuDoc.md" class="el">MenuDoc</a> *menudoc)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void * </td>
<td class="memItemRight" data-valign="bottom"><a href="Macros_8h.md#d0887ba082879415d738fa730634e0b8" class="el">GetMenuDocMap</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

