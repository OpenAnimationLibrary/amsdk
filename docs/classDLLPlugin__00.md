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

# DLLPlugin Class Reference

base class for all A:M plugins. [More...](#_details)

`#include <`<a href="DLLPlugi_8h-source.md" class="el"><code>DLLPlugi.h</code></a>`>`

Inheritance diagram for DLLPlugin:

<span class="image placeholder" original-image-src="classDLLPlugin__inherit__graph.gif" original-image-title="" border="0" usemap="#DLLPlugin__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for DLLPlugin:

<span class="image placeholder" original-image-src="classDLLPlugin__coll__graph.gif" original-image-title="" border="0" usemap="#DLLPlugin__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classDLLPlugin-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#c4c3b643593ffd04799c247889aeeaa5" class="el">DLLPlugin</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#f0e90a77fb25e2cad7dc99af718caa0a" class="el">DLLPlugin</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *treeobject)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#c5d1960463d887d6a763c22f2adbcc34" class="el">~DLLPlugin</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#99712cfce3529b5479ca47ea92742879" class="el">Init</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#d95600d5402a0637aac3c6741ad7c0cb" class="el">Init</a> (<a href="classTime.md" class="el">Time</a> time)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#15cf01877da7e4c74c262bd2f93db934" class="el">Copy</a> (const <a href="classDLLPlugin.md" class="el">DLLPlugin</a> &amp;other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#3ba36241b4d77d9ed655a45db06da58f" class="el">GetOwner</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#6e2cb2131a42b53ee9686db143d92532" class="el">GetIconID</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual UINT </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#53f5bbacfebc29c12c9900ce8ca09827" class="el">GetNameID</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#faa943acf7066d63ea9ac4e11ff85d67" class="el">GetClassName</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual <a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#bb221cb3dea0d7da15bab04f12e0af7a" class="el">GetPropertyAt</a> (int i)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#68cef93ef1d645582bbfe362c654eedd" class="el">GetNumProperties</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#1d8d03ad8d186f5d578439342a6f9b41" class="el">Save</a> (char *&amp;label, char *&amp;value, int count)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#a9daf3263af811a5aef6fda8f5533075" class="el">ParseArg</a> (const char *label, const char *value)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#57d3749c1756078f9ed1b4f3942141f7" class="el">OnNotifyEndProjectLoad</a> (float productversion)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual <a href="classHTreeObject.md" class="el">HTreeObject</a> ** </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#0bb0af24d1de05b3362b600b7aca58a7" class="el">GetPtrAt</a> (int index)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#4b29014666e184078e964ff750bdbdb2" class="el">ReassignPtr</a> (void *ptruplink, <a href="classHTreeObject.md" class="el">HTreeObject</a> *newvalue)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#a4ccb53d5129585318973cb0c14b7a4f" class="el">OnPtrMessage</a> (<a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95" class="el">PtrMessage</a> ptrmessage, <a href="classHTreeObject.md" class="el">HTreeObject</a> **ptruplink, LONG lparam, <a href="classTime.md" class="el">Time</a> time=0)</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">HINSTANCE </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#636e970e82fa4a8dbbf22b759c78b235" class="el">m_hresource</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classDLLPlugin.md#60eb10b42a32155c20e29b186a75fd14" class="el">m_treeobject</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

