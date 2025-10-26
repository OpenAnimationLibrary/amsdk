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

# RenderS2.h File Reference

`#include "ToonProp.h"`  
`#include "Filename.h"`  
`#include "IntPrope.h"`  
`#include "ClipProp.h"`  
`#include "ShaderPr.h"`  
`#include "ButtonPr.h"`  
`#include "CustomRa.h"`  
`#include "ImageIOReg.h"`  

Include dependency graph for RenderS2.h:

<span class="image placeholder" original-image-src="RenderS2_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/RenderS2.h_map"></span>

[Go to the source code of this file.](RenderS2_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classNewRenderSettings.md" class="el">NewRenderSettings</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classNewOutputSettings.md" class="el">NewOutputSettings</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classRenderFormatTypePropertyInfo.md" class="el">RenderFormatTypePropertyInfo</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="defines">Defines</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#b928872797099cd379005dd24f887fae" class="el">__RENDERS2_H</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#c60510600244fe809546959054c81a56" class="el">MINFILMSOFTNESS</a>   .1f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#39f53946abfb981bb3090e7d4393d2da" class="el">MAXFILMSOFTNESS</a>   15.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#f1a929380769612185117e55cf94ba2f" class="el">FILMGRAINSIZE100ASA</a>   0.4f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#404a57d03003bdef4b7d4aeeaf373f83" class="el">FILMGRAINAMOUNT100ASA</a>   20.0f/UNIT</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#424a36c544928a2edf802cc577742d6c" class="el">FILMGRAINSIZE200ASA</a>   0.5f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#830f5aa8ca6c8cb1860cf8d272350eb4" class="el">FILMGRAINAMOUNT200ASA</a>   30.0f/UNIT</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#babb6b5511628563f8831ef13380bd1c" class="el">FILMGRAINSIZE400ASA</a>   1.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#4515d84a3aa191615d2939b14af45c98" class="el">FILMGRAINAMOUNT400ASA</a>   40.0f/UNIT</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#d21c80576973f2b68a96ea2dd8c49c79" class="el">BLOOMTHRESHOLDDAY</a>   90.0f/UNIT</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#288cd4baf31937452a34773df933ffe1" class="el">BLOOMSTRENGTHDAY</a>   25.0f/UNIT</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#ef5048050e6434a0906f753af5c66abf" class="el">BLOOMRADIUSDAY</a>   6.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#e25136993d40f46e0739e0259cbb5224" class="el">BLOOMTHRESHOLDNIGHT</a>   75.0f/UNIT</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#293855ac8d64a6389ce9ba4c04fbe4a9" class="el">BLOOMSTRENGTHNIGHT</a>   30.0f/UNIT</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#f64f75fd6749eb676f611b0fbbe37f81" class="el">BLOOMRADIUSNIGHT</a>   6.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#5370e7d7d308aa6c1d9a25d20727a0b7" class="el">TINTLIGHTBW</a>   <a href="classRGBFloat.md" class="el">RGBFloat</a>(1.0f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#61f0972e501986e378fd9a27c1a93b4d" class="el">TINTDARKBW</a>   <a href="classRGBFloat.md" class="el">RGBFloat</a>(0.0f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#e89e15318785758cdc13bba58aa55da5" class="el">TINTPERCENTBW</a>   1.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#3243b65701811a9aa06924ce6d6021cf" class="el">TINTLIGHTCOBALT</a>   <a href="classRGBFloat.md" class="el">RGBFloat</a>(.282f, .090f, .803f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#f78f0cf36c0df20cdd0f210e07823c89" class="el">TINTDARKCOBALT</a>   <a href="classRGBFloat.md" class="el">RGBFloat</a>(0.0f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#957d372fb10be97ea304d8b5d406e2e9" class="el">TINTPERCENTCOBALT</a>   1.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#8cec7af8a49dd4f8fab17843b1581271" class="el">TINTLIGHTSEPIA</a>   <a href="classRGBFloat.md" class="el">RGBFloat</a>(.996f, .866f, .674f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#e60256db36813f69957cddbf7a2fa19c" class="el">TINTDARKSEPIA</a>   <a href="classRGBFloat.md" class="el">RGBFloat</a>(0.0f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#468cd765e37454762aaad6d6b2749034" class="el">TINTPERCENTSEPIA</a>   1.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#4a9585996406a6ba3aa226d3be6a2f55" class="el">TINTLIGHTXRAY</a>   <a href="classRGBFloat.md" class="el">RGBFloat</a>(0.0f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#d1791acc7c2f667d2e26fe839a5563cb" class="el">TINTDARKXRAY</a>   <a href="classRGBFloat.md" class="el">RGBFloat</a>(1.0f)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#461c4b951fa2f3867b99644e3d726322" class="el">TINTPERCENTXRAY</a>   1.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#302bfbcc4aa0fe1c02487e052189ce6e" class="el">SOFTEN8MM</a>   3.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#2ec0b8205c8ef6e1bae4d51b741326a9" class="el">SOFTEN16MM</a>   2.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#08d0ad8a4ec15e52fedcd3f46bf46cef" class="el">SOFTEN35MM</a>   1.0f</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">#define </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#7f40f8ac6b3432d64da23c524dea9e93" class="el">NUMRESPRESETS</a>   14</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#ad0747174ca7025af387e72dcbe83032" class="el">InitOutputSettingsStatics</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#72677c9ef3a97b4aee49ca197c4ff359" class="el">AddOutputImageIOTypeInfo</a> (<a href="classString.md" class="el">String</a> &amp;localizedname, <a href="classString.md" class="el">String</a> &amp;matchname, <a href="classString.md" class="el">String</a> &amp;documentation)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#0a61fa3ec3e90242a8949c8e16835b88" class="el">ClearOutputImageIOTypeInfo</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="RenderS2_8h.md#d6bc416beab738eef919c669da9a5b66" class="el">SetDefaultOutputImageIOFormat</a> (ImageIORegistration *iio, <a href="classString.md" class="el">String</a> &amp;savefilter)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

