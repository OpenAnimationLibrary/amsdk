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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2FSDK_2F.md" class="el">SDK</a>

</div>

# Misc.h File Reference

`#include "`<a href="Exports_8h-source.md" class="el"><code>Exports.h</code></a>`"`  
`#include "`<a href="ColorBuf_8h-source.md" class="el"><code>ColorBuf.h</code></a>`"`  
`#include "`<a href="ColorBuf_8inl-source.md" class="el"><code>ColorBuf.inl</code></a>`"`  

Include dependency graph for Misc.h:

<span class="image placeholder" original-image-src="Misc_8h__incl.gif" original-image-title="" border="0" usemap="#C:/Program Files/Hash Inc/AM120SDK/Include/SDK/Misc.h_map"></span>

[Go to the source code of this file.](Misc_8h-source.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classCPluginApp.md" class="el">CPluginApp</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">class  </td>
<td class="memItemRight" data-valign="bottom"><a href="classCPluginDialog.md" class="el">CPluginDialog</a></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="functions">Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT HWND </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#4c40258e2e0a3679b6b7cd96e08b9927" class="el">GetMainApplicationWnd</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT int </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#054d9983599e0442f5b0e25d3347ae6a" class="el">GetTimeMode</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT float </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#5db845325ae1cba1f3535d56f4398f1f" class="el">GetTurbulence</a> (const <a href="classVector.md" class="el">Vector</a> &amp;vec)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#90497273cc876107e1d86d4e4ffd1371" class="el">DeleteIEModel</a> (<a href="classIEModel.md" class="el">IEModel</a> *iemodel)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT CWnd * </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#f382f91909e6bf085f219b5155a0441f" class="el">GetPanel</a> (const <a href="classString.md" class="el">String</a> &amp;name, BOOL ensurevisible=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#b84f3b8738f778bc8837cffee71d45e6" class="el">IsInNetRender</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT <a href="classColorBuf.md" class="el">ColorBuf</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#fc6924e340caba21b0013af9762303e5" class="el">GetColor</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT void </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#375d062614d6ff939c820df8739f848a" class="el">RefreshAllTrees</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">PLUGINEXPORT BitmapNode * </td>
<td class="memItemRight" data-valign="bottom"><a href="Misc_8h.md#cc0727a8d73f682119ede6a88fb14fc0" class="el">BrowseImage</a> (const <a href="classString.md" class="el">String</a> &amp;title, <a href="classString.md" class="el">String</a> &amp;filename)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Function Documentation

<span id="cc0727a8d73f682119ede6a88fb14fc0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT BitmapNode* BrowseImage</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>title</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>filename</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="90497273cc876107e1d86d4e4ffd1371" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT void DeleteIEModel</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEModel.md" class="el">IEModel</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>iemodel</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="fc6924e340caba21b0013af9762303e5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT <a href="classColorBuf.md" class="el">ColorBuf</a> GetColor</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>index</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="4c40258e2e0a3679b6b7cd96e08b9927" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT HWND GetMainApplicationWnd</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="f382f91909e6bf085f219b5155a0441f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT CWnd* GetPanel</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>name</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">BOOL </td>
<td class="mdname" data-nowrap=""><em>ensurevisible</em> = <code>TRUE</code></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="054d9983599e0442f5b0e25d3347ae6a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT int GetTimeMode</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="5db845325ae1cba1f3535d56f4398f1f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT float GetTurbulence</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>vec</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="b84f3b8738f778bc8837cffee71d45e6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT BOOL IsInNetRender</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="375d062614d6ff939c820df8739f848a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">PLUGINEXPORT void RefreshAllTrees</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:50 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
