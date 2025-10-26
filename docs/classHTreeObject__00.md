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

# HTreeObject Class Reference

The father class of about all objects in Animation Master. [More...](#_details)

`#include <`<a href="HHashObj_8h-source.md" class="el"><code>HHashObj.h</code></a>`>`

Inheritance diagram for HTreeObject:

<span class="image placeholder" original-image-src="classHTreeObject__inherit__graph.gif" original-image-title="" border="0" usemap="#HTreeObject__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHTreeObject-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#72ef2b9b6965d078e3c7f95487a82d1c" class="el">Skip</a> {<br />
  <a href="classHTreeObject.md#72ef2b9b6965d078e3c7f95487a82d1c032ca6d2ae0118b99e81fd7d7605265a" class="el">SKIPNONE</a> = 0x00, <a href="classHTreeObject.md#72ef2b9b6965d078e3c7f95487a82d1c09c194de48c4efe3054cb36eb5ae5b10" class="el">SKIPINVISIBLE</a> = 0x01, <a href="classHTreeObject.md#72ef2b9b6965d078e3c7f95487a82d1c09eff00b6f676e661b9cc0ae70929eb5" class="el">SKIPFILTERED</a> = 0x02, <a href="classHTreeObject.md#72ef2b9b6965d078e3c7f95487a82d1cb0bd5a6125fca4931e8de9d9fd5afb1e" class="el">SKIPADVANCED</a> = 0x04,<br />
  <a href="classHTreeObject.md#72ef2b9b6965d078e3c7f95487a82d1c39e3a4202385b10c1398766d63f13fdf" class="el">SKIPFOLDERS</a> = 0x08<br />
}</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#bb221cb3dea0d7da15bab04f12e0af7a" class="el">GetPropertyAt</a> (int i)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">GetObjectType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#97bbe45df6b2b139c951f179d5dc83b8" class="el">GetType</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#b2a90b0840ba0f087728d89d27353935" class="el">operator delete</a> (void *ptr)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#97be359c26ddf9186be271cb8a6a64d2" class="el">IsModified</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#1923648b89c926d018852bbb33a1af38" class="el">OnModified</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#ab3ce178e828b1b54051bd4f219e271a" class="el">FindChildByName</a> (char *matchname)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#3b0b70f3e9001b04fcec593ca1a22420" class="el">FindChildByTreeName</a> (char *treename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#b185755bbb59d784cfb72664b3e478a7" class="el">ExpandInProjectBar</a> (BOOL expand)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#9272ef733a40f9c87d994dc53788c108" class="el">RefreshInProjectBar</a> (BOOL updatenow=FALSE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#63e69ca9db004742fc04acf44c36853e" class="el">HilightInProjectBar</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#a9f532f72ce29f8555daa2c26ce32e49" class="el">GetTreeParent</a> (UINT skip=SKIPINVISIBLE|SKIPFILTERED)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#ddeb98d5cf1bdde9d31e8d13774619dd" class="el">GetTreeProgeny</a> (UINT skip=SKIPINVISIBLE|SKIPFILTERED)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#afae92abc783f082ab8db3fc5fc172b5" class="el">GetTreeSibling</a> (UINT skip=SKIPINVISIBLE|SKIPFILTERED)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#aea074b20b6f6571959609e921d58de5" class="el">GetParent</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#eb451c59cc9d433921288eea41502eac" class="el">SetParent</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *parent)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#4b29014666e184078e964ff750bdbdb2" class="el">ReassignPtr</a> (void *ptruplink, <a href="classHTreeObject.md" class="el">HTreeObject</a> *newvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAnimObject.md" class="el">HAnimObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#3d44b30ac7fcf929e97c61fa6970c5f1" class="el">GetAnimObject</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAnimObject.md" class="el">HAnimObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#5433fa82f429c17bcc63866680b58754" class="el">GetAnimObjectNotProperty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#393dff0d5bf352fbad6c3552387bca4a" class="el">GetMatchName</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#441760acf64ee395f3bf55dea6470fc6" class="el">GetFileName</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#c2d927d82e5a3a64640c06443f40bf73" class="el">GetFullName</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBone.md" class="el">HBone</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#5f4a9157eae9a56e90bf06cac20a7f54" class="el">IsBone</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#0e3e0bf6de9458606f173f745f3eb976" class="el">IsActionObjectChild</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#0dc17c1e3538a6c838d2a8f32b6b5424" class="el">InterpolateObjects</a> (<a href="classTime.md" class="el">Time</a> time, BOOL notify=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#b22bd4e7d4ee16faac11bd67d2b832c2" class="el">Interpolate</a> (<a href="classTime.md" class="el">Time</a> time, BOOL notify=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#ef935bce206a25f79efff9a115d56b17" class="el">OffInterpolate</a> (<a href="classHProperty.md" class="el">HProperty</a> *dueto)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#3cc50d1bfcedd6d4c7e0ca9d222acc3c" class="el">IsHashObject</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAnimObjectShortcut.md" class="el">HAnimObjectShortcut</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#f747ef35d50e7ed68029953a77a0cf07" class="el">IsAnimObjectShortcut</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#21cc949c5910d5dff9080d5eb6990b17" class="el">IsPropertyDriver</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#b160e6c14becfd6508929b9b834e8510" class="el">Save</a> (<a href="classHashStream.md" class="el">HashStream</a> &amp;hs)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#d133bf3e9e9bf2a3d3f5ea57ddbe9ae6" class="el">SetVisible</a> (BOOL visible)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#1c96c46e39cfcfdc3463e1817e3a618c" class="el">SetTempBit</a> (BOOL state)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#640699e574b6d3910dd388eebe21e6ec" class="el">GetTempBit</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#9af60cb77396d656df470cd8478a31f6" class="el">IsProperty</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="static-public-member-functions">Static Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">static void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHTreeObject.md#68a56f970bf31e136b0855e2de4ac987" class="el">DeleteHandle</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *handle)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

