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

# HPropertyInfo Class Reference

Father class for all property UI contexts. [More...](#_details)

`#include <`<a href="HPropert_8h-source.md" class="el"><code>HPropert.h</code></a>`>`

Inheritance diagram for HPropertyInfo:

<span class="image placeholder" original-image-src="classHPropertyInfo__inherit__graph.gif" original-image-title="" border="0" usemap="#HPropertyInfo__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHPropertyInfo-members.md)

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
&#10;<h2 id="public-types">Public Types</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3b" class="el">DrawWhen</a> {<br />
  <a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3be0ff367e611bbdad74cb43f7a48fb9e9" class="el">DRAWNEVER</a>, <a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3b090563064c468a940a62ce66b7aecb98" class="el">DRAWALWAYS</a>, <a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3b3d509dabac59020987fbd1c560cdc261" class="el">DRAWIFSHADED</a>, <a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3bc7f2c4e5d9940cfff3aaa220b1c9e383" class="el">DRAWIFFLARES</a>,<br />
  <a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3bb3bc3a06f2d8f2c01cb89403763477b1" class="el">DRAWIFMATERIALS</a>, <a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3bfccd94c2ee6df6af6f1c6ebe98c4fde2" class="el">DRAWIFPARTICLES</a><br />
}</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">enum  </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691c" class="el">VisibleWhen</a> {<br />
  <a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691c709f05c44cffd50c472d8528ee62eaff" class="el">VISIBLENEVER</a>, <a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691cd0990d9c1c5727acf1261eca1ae80e28" class="el">VISIBLEALWAYS</a>, <a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691cfb9db43723463c3ec7b1ba44bf80f0f4" class="el">VISIBLECACHEONLY</a>, <a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691cb7b3d7ebfb29c2d85a4fcc8e7e6fa16f" class="el">VISIBLEINSTANCEONLY</a>,<br />
  <a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691c45be275b9431f252ff844c56ac02388a" class="el">VISIBLESOMETIMES</a><br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#b2a90b0840ba0f087728d89d27353935" class="el">operator delete</a> (void *ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#bdacc650d76c0dae25171fcd41afc353" class="el">SetLocalizedName</a> (const char *name)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">For backward comp with V9.0o and older. <a href="#bdacc650d76c0dae25171fcd41afc353"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#a76daf6ed0e6a62af293abac832e595f" class="el">SetMatchName</a> (const char *name)</td>
</tr>
<tr>
<td class="mdescLeft"> </td>
<td class="mdescRight">For backward comp with V9.0o and older. <a href="#a76daf6ed0e6a62af293abac832e595f"></a><br />
</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#4dce5307ede3d5604253f33f01fc5759" class="el">SetLocalizedName</a> (const <a href="classString.md" class="el">String</a> &amp;name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#d222813c102967a2e9e21c84e4f1a53d" class="el">SetMatchName</a> (const <a href="classString.md" class="el">String</a> &amp;name)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#b20555c3a22c000aa894a5fd5f157507" class="el">GetLocalizedName</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#393dff0d5bf352fbad6c3552387bca4a" class="el">GetMatchName</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#15fc9483600eeabdc3f6d8c5a81f4214" class="el">SetDocumentation</a> (const char *doc)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3b" class="el">DrawWhen</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#4df6d0366bb8d5a8d632f42996e5da3b" class="el">GetDrawWhen</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#c89057a96b3fcfb41b37d8d04fddf81d" class="el">SetDrawWhen</a> (<a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3b" class="el">DrawWhen</a> dw)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691c" class="el">VisibleWhen</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#f0713d14f95bec4f16e992b844fb24a5" class="el">GetVisibleWhen</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#0167de075e18bec49d7a4ffd63687bbd" class="el">SetVisibleWhen</a> (<a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691c" class="el">VisibleWhen</a> vw)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#8739f2690f2cf3191ffec83d39023a84" class="el">IsConstant</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#cfe6bc1fd0c74b6add85c048ff949cf8" class="el">SetConstant</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#e4a8dfca918163cef57e727aedd80818" class="el">IsReadOnly</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#58b80564347504a8271e0de3932d97f8" class="el">SetReadOnly</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#a7f273e225834b15f2e9a91c2bbaaddb" class="el">IsReadOnlyOnCache</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#1e9f7b397dcd54124cc2cece899d889e" class="el">SetReadOnlyOnCache</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#589aebd2db39f6d258d94c7dded1881b" class="el">IsReadOnlyOnInstance</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#9b22eae709aa6aa81190e6a13273e1bc" class="el">SetReadOnlyOnInstance</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#2f25cde5b7d9a82482357aa4ca89b47e" class="el">IsAdvanced</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#378263fcbc9e7fb8b413e4a3ca5ab841" class="el">SetAdvanced</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#6e24fdb0e365e5b03bd17f81fd9c8d05" class="el">IsSaveProperty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#28d2e2b5ddd8487ae17e42ce4811e026" class="el">SetSaveProperty</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#32e78a8eddb09c184dcfea83e6139fa7" class="el">IsNotifyAnimObjectValueChanged</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#30cd45504515931e33091c62895648af" class="el">SetNotifyAnimObjectValueChanged</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#0084d87c59410a05561124c9b752eee7" class="el">IsDeletable</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#9b75614283e248eef2a0ebd5d6874e39" class="el">SetDeletable</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#3399f52d67378a5b8ff49d028f85086a" class="el">SetCacheAnimatable</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#e868fc50a92d0c85b9175dd1bef3a97f" class="el">GetCacheAnimatable</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static <a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#3184c8fe6d6f9a3b2284ddcadfd1424f" class="el">New</a> (const char *localizedname, const char *matchname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyInfo.md#422e55dc717919d35e7452ab4c1bc05e" class="el">DeleteHandle</a> (<a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> *handle)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

