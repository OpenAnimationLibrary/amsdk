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

# StrClass.h File Reference

`#include "`<a href="Macros_8h-source.md" class="el"><code>Macros.h</code></a>`"`  
`#include "`<a href="Allocate_8h-source.md" class="el"><code>Allocate.h</code></a>`"`  

Include dependency graph for StrClass.h:

<span class="image placeholder" original-image-src="StrClass_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/StrClass.h_map"></span>

This graph shows which files directly or indirectly include this file:

<span class="image placeholder" original-image-src="StrClass_8h__dep__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/StrClass.hdep_map"></span>

[Go to the source code of this file.](StrClass_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classString.md" class="el">String</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#75182ea92150576691f96b546330a5a8" class="el">STRINGALLOC</a>(baz)   (char *)AllocString((size_t)baz )</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#53d272522fb64973a9e71b09c7e331ea" class="el">STRINGFREE</a>(baz)   {if (baz){FreeString( baz );baz=NULL;}}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#3cdd16839fb5a19ff51dd8efe478b664" class="el">STRINGSIZE</a>   255</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#08740970037c32e369a340edff5ee020" class="el">periodch</a>   '.'</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#05e90b43292790d8fa940429d9ae928c" class="el">periodch_r</a>   ((char)255)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#5d022a7657859b0ea8bdbe2ddd37745e" class="el">pathch_r</a>   ((char)254)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#a256f5e4cdf3abe0d20d2ad4cc6e8ea2" class="el">quotech</a>   '\"'</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#49fcb56cc604cef7b1ad1b9a4ce5e150" class="el">NATIVESEPARATOR</a>   '\\'</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="enumerations">Enumerations</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom">{<br />
  <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516effb16e9af9a972ad5e609b2051ada933e" class="el">UNIT_NONE</a>, <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516ef05594708361f400d4bfd169b63e921d2" class="el">UNIT_CENTIMETERS</a>, <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516ef9021c34360cb3da4c65952d3b9224584" class="el">UNIT_METERS</a>, <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516efd496798c237b6ce27ce8a7a513778ca8" class="el">UNIT_FEET</a>,<br />
  <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516efa15b8ba5d6b6e71a50801d97a14d1062" class="el">UNIT_INCHES</a>, <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516ef9cddd0c4a4388ddd3bc947196d4f131b" class="el">UNIT_FEETANDINCHES</a>, <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516efcb712fc57e95be16a109c311801bf14e" class="el">UNIT_PERCENTAGE</a>, <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516ef56ca00a327533645f7d4e728989db31f" class="el">UNIT_ANGLE</a>,<br />
  <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516efffb9b84378f64e2fdfabb8c248d8235f" class="el">UNIT_SMPTE</a>, <a href="StrClass_8h.md#dca29a1140aadadfd92b34a02fa516ef456068a4af4d940522acc556374a9795" class="el">UNIT_FRAMES</a><br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#8350f9e65c858259d639e60f260ad590" class="el">operator+</a> (const <a href="classString.md" class="el">String</a> &amp;left, const <a href="classString.md" class="el">String</a> &amp;right)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#19b6f87fa0329f833f2571e1adb29422" class="el">FormatTime</a> (LONG sec, BOOL force=FALSE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#cb74eb4b1a6779b2d1ffccdbdf41b408" class="el">StripOffName</a> (<a href="classString.md" class="el">String</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#c463b431173ccaf195958e810dcb6135" class="el">AddNameToPath</a> (<a href="classString.md" class="el">String</a> &amp;, const <a href="classString.md" class="el">String</a> &amp;)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#ba666830fc8faf08bcfaec74519629f6" class="el">CombineNameToPath</a> (const <a href="classString.md" class="el">String</a> &amp;path, const <a href="classString.md" class="el">String</a> &amp;name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#3b709aae47a6bc6f1613ee5bc306d28b" class="el">AddNameToExeDirectory</a> (<a href="classString.md" class="el">String</a> name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#f6660d10f9f9f5611510ec1990c190b6" class="el">AddNameToDataDirectory</a> (<a href="classString.md" class="el">String</a> name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#e9bc356ae5b39159119d72432350ce74" class="el">FreeAppPath</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT void AFXAPI </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#36d7403a1ca06cae6bb9e0230f8e9d0f" class="el">DDX_Text</a> (CDataExchange *pDX, int nIDC, <a href="classString.md" class="el">String</a> &amp;value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#d697487f8b05562afff432aac4857d7a" class="el">NativeToUniversal</a> (const <a href="classString.md" class="el">String</a> &amp;nativepath)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">FILEIOEXPORT <a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#6e7ab9d06a53cfbcaa2f813068bb2df0" class="el">UniversalToNative</a> (const <a href="classString.md" class="el">String</a> &amp;puniversalpath)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT int </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#f3b2bff2dad7f1c1039f0261ebb541fa" class="el">GetMeasurementUnits</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#bd008f0bf6d7ed800610e7203fbb6d7d" class="el">SetMeasurementUnits</a> (int pmeasurementunits)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT CString </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#adf7fca1238cbfa18ec486f87d696bd1" class="el">UnitToString</a> (float cm, int pmeasurementunits=-1, int fps=-1, float modulo=.01f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void AFXAPI </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#940e76784280fcc32132b7cf6ec715d3" class="el">DDX_Unit</a> (CDataExchange *pDX, int nIDC, float &amp;cm)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void AFXAPI </td>
<td class="memItemRight" data-valign="bottom"><a href="StrClass_8h.md#692f612c69160568c27b9e933dfe4e40" class="el">DDV_MinMaxUnit</a> (CDataExchange *pDX, float const &amp;value, float minVal, float maxVal)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

