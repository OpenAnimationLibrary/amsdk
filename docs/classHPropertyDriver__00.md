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

# HPropertyDriver Class Reference

`#include <`<a href="HPropDri_8h-source.md" class="el"><code>HPropDri.h</code></a>`>`

Inheritance diagram for HPropertyDriver:

<span class="image placeholder" original-image-src="classHPropertyDriver__inherit__graph.gif" original-image-title="" border="0" usemap="#HPropertyDriver__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HPropertyDriver:

<span class="image placeholder" original-image-src="classHPropertyDriver__coll__graph.gif" original-image-title="" border="0" usemap="#HPropertyDriver__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHPropertyDriver-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#7ca16012963ff962f295e142301537a2" class="el">GetProperty</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#f162c52f37a5e031f0a9528b7e528fd4" class="el">GetNextActionDriver</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#2fcc6ba10ec1afbd9c48cf04357c76d4" class="el">GetNextDriver</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#788a07372b7c850149069d81f18e9570" class="el">GetNextDriverForAction</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAction.md" class="el">HAction</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#56dd0811694e27ed2495e6e948cd4882" class="el">GetAction</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#0e55ce9f7f49e0609606104a5fe9d62e" class="el">GetDriver</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#e96c90b36308469b8ee11c9e5b4db357" class="el">IsSimpleDriverShortcut</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#0ccaf013ef5ff17991c689fb63123137" class="el">SetProperty</a> (<a href="classHProperty.md" class="el">HProperty</a> *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHDriverShortcut.md" class="el">HDriverShortcut</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#36284b3ed7f982f4500f96aef1091055" class="el">NewShortcut</a> (<a href="classHActionCache.md" class="el">HActionCache</a> *)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#dd1325cca892fb4d916acbbfd56bfa8c" class="el">GetNumSubDrivers</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#329144a024ed1993c6682d689e4fc883" class="el">GetSubDriverAt</a> (int i)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#a02bf24f1544d0ac18bc9e83cfd2d9ad" class="el">FindPropertyFromDriver</a> (BOOL cacheok=FALSE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#f05155d66a18c82acfa7d871654a2cb2" class="el">MakeCopy</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#6a6b3aaeead57d96b6b9b208295c2d68" class="el">Copy</a> (<a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> *other)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#55741612fcd65e7480fa2d8042a0e08c" class="el">CopyKeys</a> (<a href="classHPropertyDriver.md" class="el">HPropertyDriver</a> *other, <a href="classHAction.md" class="el">HAction</a> *action=NULL)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHConstraint.md" class="el">HConstraint</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#d731ed98aa0cb2e89c6e73bd86749cf9" class="el">IsConstraint</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#ef28896311723d57c205b82f0412e70b" class="el">IsStorageDriver</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHPropertyDriver.md#16ee1ed8b3789f12b4fd6aad1a53f6ed" class="el">AddSelfAppliedDrivers</a> ()</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

