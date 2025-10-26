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

# HObject Class Reference

An HObject is a work copy of a <a href="classHObjectCache.md" class="el">HObjectCache</a> to allow modification by an Action or a Choreography. [More...](#_details)

`#include <`<a href="HObject_8h-source.md" class="el"><code>HObject.h</code></a>`>`

Inheritance diagram for HObject:

<span class="image placeholder" original-image-src="classHObject__inherit__graph.gif" original-image-title="" border="0" usemap="#HObject__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HObject:

<span class="image placeholder" original-image-src="classHObject__coll__graph.gif" original-image-title="" border="0" usemap="#HObject__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHObject-members.md)

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
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#35f3dc77ccac3f834ebd4e0a0a634782" class="el">GetActive</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHChor.md" class="el">HChor</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#3712f9fe6343f54d507bf46f0976750f" class="el">GetChor</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHActionShortcutContainer.md" class="el">HActionShortcutContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#6e3ed8ca902fe81cbadaf2f39054a244" class="el">GetActionShortcutContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHRelationContainer.md" class="el">HRelationContainer</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#c4150697ec530e523dabefe3686b3f65" class="el">GetRelationContainer</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAction.md" class="el">HAction</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#836af377f3b1c132519a40fe335d3573" class="el">GetCurrentChorAction</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHObject.md" class="el">HObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#6665b8570e1d186b28465261dc966038" class="el">MakeCopy</a> (BOOL insertintochor=TRUE)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#2f78bb78a01e73e7f0965cb127e2d9b4" class="el">SetIsActionDeleted</a> (BOOL bState)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#e83a4dd9d146565313cbd515c3a79817" class="el">IsActionDeleted</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classHAnimObject.md" class="el">HAnimObject</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHObject.md#2456ea7603fff8c80fe478bc5bb205d9" class="el">FindAnimObjectFromCache</a> (<a href="classHAnimObject.md" class="el">HAnimObject</a> *key)</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

An HObject is a work copy of a <a href="classHObjectCache.md" class="el">HObjectCache</a> to allow modification by an Action or a Choreography.

A:M differenciates between an object that you find in the Objects folder in the PWS and references to the object that you find in Actions or Choreographies folders of the PWS for example and named "Shortcut to ...". While the actual object found in the Objects folder of the PWS is a <a href="classHObjectCache.md" class="el">HObjectCache</a> or a cache for short, any "Shortcut to ..." instance is an HObject. Thus if you drop a <a href="classHObjectCache.md" class="el">HObjectCache</a> into a choreography, an HObject is created, and it is added to the internal list of checked out HObject. When an object is being edited in a window, an HObject is aslo created and it is the HObject that is being displayed and edited. In other words, you must have an <a href="classHModel.md" class="el">HModel</a> of an <a href="classHModelCache.md" class="el">HModelCache</a> to draw it on the screen.

So the HObject or any derived classes contain a work copy of the original <a href="classHObjectCache.md" class="el">HObjectCache</a> where any attributes or components may be overriden or redefined or dynamicaly recomputed according to some action performed on it at some given time. The <a href="classHObjectCache.md" class="el">HObjectCache</a> will always stay unchanged while the HObject will change as the animation goes or as specific requirements of a shortcut are redefined.

**See also:**  
<a href="classHObjectCache.md" class="el">HObjectCache</a> fo a descrition of its realtion to HObject

Definition at line <a href="HObject_8h-source.md#l00027" class="el">27</a> of file <a href="HObject_8h-source.md" class="el">HObject.h</a>.

------------------------------------------------------------------------

## Member Function Documentation

<span id="2456ea7603fff8c80fe478bc5bb205d9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAnimObject.md" class="el">HAnimObject</a>* HObject::FindAnimObjectFromCache</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAnimObject.md" class="el">HAnimObject</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>key</em></td>
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

<span id="6e3ed8ca902fe81cbadaf2f39054a244" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHActionShortcutContainer.md" class="el">HActionShortcutContainer</a>* HObject::GetActionShortcutContainer</td>
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

<span id="35f3dc77ccac3f834ebd4e0a0a634782" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHBoolProperty.md" class="el">HBoolProperty</a>* HObject::GetActive</td>
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

<span id="3712f9fe6343f54d507bf46f0976750f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHChor.md" class="el">HChor</a>* HObject::GetChor</td>
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

<span id="836af377f3b1c132519a40fe335d3573" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAction.md" class="el">HAction</a>* HObject::GetCurrentChorAction</td>
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

<span id="c4150697ec530e523dabefe3686b3f65" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHRelationContainer.md" class="el">HRelationContainer</a>* HObject::GetRelationContainer</td>
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

<span id="e83a4dd9d146565313cbd515c3a79817" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HObject::IsActionDeleted</td>
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

<span id="6665b8570e1d186b28465261dc966038" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHObject.md" class="el">HObject</a>* HObject::MakeCopy</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BOOL </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>insertintochor</em> = <code>TRUE</code></td>
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

<span id="2f78bb78a01e73e7f0965cb127e2d9b4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HObject::SetIsActionDeleted</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BOOL </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>bState</em></td>
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

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HObject_8h-source.md" class="el">HObject.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:56 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
