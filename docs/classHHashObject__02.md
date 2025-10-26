## Member Function Documentation

<span id="9aa03709064628d1993ac2d7194d83cf" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHUserCategoryProperty.md" class="el">HUserCategoryProperty</a>* HHashObject::CreateUserCategoryProperty</td>
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

<span id="3da8b1d86f721bfb3262ab8f42d0b7e9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * HHashObject::GetChild</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves the <strong>First</strong> child HHashObject in the childs list independent of its type. To test for its type use <a href="classHHashObject.md#d6ea8ca9057dc82025912c710057fe09" class="el">HHashObject::GetSibling()</a>.</p>
<p>Skips user containers, and doesn't include classes not derived off HashObject (CPs)</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
Using <a href="classHHashObject.md#3da8b1d86f721bfb3262ab8f42d0b7e9" class="el">GetChild()</a>, <a href="classHHashObject.md#d6ea8ca9057dc82025912c710057fe09" class="el">GetSibling()</a>, or <a href="classHTreeObject.md#aea074b20b6f6571959609e921d58de5" class="el">GetParent()</a> will ensure that the iteration proceeds through the list in the same order as they appear in the PWS folder.
</dd>
</dl>
Here is a code snipet that will iterate through objects of type HModels in a <a href="classHChor.md" class="el">HChor</a> object.
<div class="fragment">
<pre class="fragment"><code>for (HHashObject *obj = chor-&gt;GetChild(); obj; obj=obj-&gt;GetSibling()) {
   if (obj-&gt;GetObjectType() == HOT_MODEL)
   ...
}</code></pre>
</div>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
see <a href="classHChor.md#46fe186652bb3db3b91c8c88ec5c6897" class="el">HChor::GetChildModel()</a> for an easier and more efficient way to accomplish the same iteration.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="5616a8d6197ea5f43bfb5cbf3f9b8f5e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * HHashObject::GetHeadInstance</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves the <strong>first</strong> work-object (instance) of an HHashObject.</p>
<p>Each <a href="classHObjectCache.md" class="el">HObjectCache</a> have a list of all work-object instanciated from itself anywhere in a project.</p>
<p>For example if you have a <a href="classHModelCache.md" class="el">HModelCache</a> under the Objects folder, the GetHeadInstance would return the <strong>first</strong> <a href="classHModel.md" class="el">HModel</a> (an work-objectinstance of a <a href="classHModelCache.md" class="el">HModelCache</a>) from an <strong>internal</strong> list. HModels are found in choreographies or if you are editing a <a href="classHModelCache.md" class="el">HModelCache</a> in a view. If you drop a <a href="classHModelCache.md" class="el">HModelCache</a> into a choreography, an <a href="classHModel.md" class="el">HModel</a> is created, and it is added to the internal list of checked out instances (<a href="classHHashObject.md#5616a8d6197ea5f43bfb5cbf3f9b8f5e" class="el">GetHeadInstance()</a>).</p></td>
</tr>
</tbody>
</table>

<span id="d85b49d73e45d0431b18e5a61c7e6f3f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char* HHashObject::GetName</td>
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

|  |  |
|----|----|
|   | Reimplemented in <a href="classHActionCache.md#d85b49d73e45d0431b18e5a61c7e6f3f" class="el">HActionCache</a>. |

<span id="e63536d1fd80fc0931ab7aa73d18d8c1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * HHashObject::GetNextInstance</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>instance</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves the <em>next</em> <a href="classHObject.md" class="el">HObject</a>.</p>
<p>Each <a href="classHObjectCache.md" class="el">HObjectCache</a> have a list of all instanciation of itself anywhere in a project. This member function retrieves the next instance of the object. This instance may reside anywhere in the project, choreographies, open Model or Actions views as referenced by "Shortcut to ...".</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>instance</em> </td>
<td>- Pointer to the HHashObject from which the next instance is to be retrieved.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="effdee082fe387ec5dd54c03a2e22ed0" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> HHashObject::GetObjectType</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Returns the object type</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
The <a href="classHTreeObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HTreeObject::GetObjectType()</a> should be used instead of this one. This one is an old remnent of the 8.5 SDK and have been left there so not to invalidate old plugins.
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<p><a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> for the complete list of <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> tags and their values.</p>
<p><a href="classHTreeObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HTreeObject::GetObjectType()</a></p>
</dd>
</dl>
<p>Reimplemented from <a href="classHTreeObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HTreeObject</a>.</p>
<p>Reimplemented in <a href="classHShading.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HShading</a>.</p></td>
</tr>
</tbody>
</table>

<span id="7cc7a014d4e2a101c1982a2f1b027cfe" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * HHashObject::GetParentOfType</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>ot</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Skips user containers, and doesn't include classes not derived off HashObject (CPs) |

<span id="29e1059084f6ff925a74d86aeb9e3754" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCategoryProperty.md" class="el">HCategoryProperty</a>* HHashObject::GetPluginProperties</td>
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

<span id="d6ea8ca9057dc82025912c710057fe09" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * HHashObject::GetSibling</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves the <em>Next</em> child HHashObject independent of its type in the list starting where the current HHashObject is in the list. To test for its type use <a href="classHHashObject.md#d6ea8ca9057dc82025912c710057fe09" class="el">HHashObject::GetSibling()</a>.</p>
<p>Skips user containers, and doesn't include classes not derived off HashObject (CPs)</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
See <a href="classHHashObject.md#3da8b1d86f721bfb3262ab8f42d0b7e9" class="el">HHashObject::GetChild()</a> for an example that iterates through objects in a list.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="5788d8ba32b9eb644c937edf2c937409" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * HHashObject::GetSiblingSame</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>Retrieves the <em>Next</em> child HHashObject of the same type as the current HHashObject in the list starting where the current HHashObject is in the list.</p>
<p>Skips user containers, and doesn't include classes not derived off HashObject (CPs)</p></td>
</tr>
</tbody>
</table>

<span id="9dd87d4e3e2d7a3ba397c36320e04627" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHUserCategoryProperty.md" class="el">HUserCategoryProperty</a>* HHashObject::GetUserCategoryProperty</td>
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

<span id="a42ade8055e415435caf3aa5b308373b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HHashObject::InsertChildAfterObject</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="mdname" data-nowrap=""><em>child</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="mdname" data-nowrap=""><em>after</em></td>
</