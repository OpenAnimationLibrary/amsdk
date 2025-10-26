## Member Function Documentation

<span id="68a56f970bf31e136b0855e2de4ac987" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static void HTreeObject::DeleteHandle</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>handle</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [static]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Referenced by <a href="HPatch_8h-source.md#l00025" class="el">HSpline::operator delete()</a>. |

<span id="b185755bbb59d784cfb72664b3e478a7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HTreeObject::ExpandInProjectBar</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BOOL </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>expand</em></td>
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

<span id="ab3ce178e828b1b54051bd4f219e271a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * HTreeObject::FindChildByName</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">char * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>matchname</em></td>
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
<td><p>Returns a pointer to an object in the PWS tree whose name match the passed argument. Usefull for finding a specific object or folder.</p>
<p>Once an object is returned, its actual type may be retrieved with GetObjectType</p>
<p>Examples:</p>
<div class="fragment">
<pre class="fragment"><code>hac-&gt;FindChildByName(&quot;Splines&quot;);
hac-&gt;FindChildByName(&quot;Bones&quot;);
hac-&gt;FindChildByName(&quot;Untitled&quot;);</code></pre>
</div>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHTreeObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HTreeObject::GetObjectType</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="3b0b70f3e9001b04fcec593ca1a22420" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a>* HTreeObject::FindChildByTreeName</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">char * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>treename</em></td>
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

<span id="3d44b30ac7fcf929e97c61fa6970c5f1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAnimObject.md" class="el">HAnimObject</a>* HTreeObject::GetAnimObject</td>
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
|   | Reimplemented in <a href="classHAnimObjectShortcut.md#3d44b30ac7fcf929e97c61fa6970c5f1" class="el">HAnimObjectShortcut</a>. |

<span id="5433fa82f429c17bcc63866680b58754" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHAnimObject.md" class="el">HAnimObject</a> * HTreeObject::GetAnimObjectNotProperty</td>
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
<td><p>You can call GetAnimObjectNotProperty to get the actual object that the shader is on. The object returned by GetAnimObjectNotProperty should be either the <a href="classHModelCache.md" class="el">HModelCache</a>, <a href="classHGroup.md" class="el">HGroup</a>, or a <a href="classHCameraCache.md" class="el">HCameraCache</a>.</p>
<p>It is safe to cast the <a href="classHAnimObject.md" class="el">HAnimObject</a> returned to an <a href="classHHashObject.md" class="el">HHashObject</a>, or the prefered way, to an HTreeObject in ordet to call its <a href="classHTreeObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">GetObjectType()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="441760acf64ee395f3bf55dea6470fc6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> HTreeObject::GetFileName</td>
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
|   | Reimplemented in <a href="classHBufferShortcut.md#441760acf64ee395f3bf55dea6470fc6" class="el">HBufferShortcut</a>, and <a href="classHFileInfoProperty.md#441760acf64ee395f3bf55dea6470fc6" class="el">HFileInfoProperty</a>. |

<span id="c2d927d82e5a3a64640c06443f40bf73" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> HTreeObject::GetFullName</td>
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

<span id="393dff0d5bf352fbad6c3552387bca4a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> HTreeObject::GetMatchName</td>
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
<td class="md" data-nowrap="" data-valign="top"><a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> HTreeObject::GetObjectType</td>
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
<dt><strong>See also:</strong></dt>
<dd>
<p><a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> for the complete list of <a href="ObjType_8h.md#b74c375731dc50c662d6ce08befe2db0" class="el">ObjectType</a> tags and their values.</p>
<p><a href="classHTreeObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HTreeObject::GetObjectType()</a></p>
</dd>
</dl>
<p>Reimplemented in <a href="classHHashObject.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HHashObject</a>, and <a href="classHShading.md#effdee082fe387ec5dd54c03a2e22ed0" class="el">HShading</a>.</p></td>
</tr>
</tbody>
</table>

<span id="aea074b20b6f6571959609e921d58de5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * HTreeObject::GetParent</td>
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
|   | Skips user containers, and doesn't include classes not derived off HashObject (CPs) |

<span id="bb221cb3dea0d7da15bab04f12e0af7a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a>* HTreeObject::GetPropertyAt</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>i</em></td>
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

<span id="640699e574b6d3910dd388eebe21e6ec" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HTreeObject::GetTempBit</td>
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

<span id="a9f532f72ce29f8555daa2c26ce32e49" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * HTreeObject::GetTreeParent</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">UINT </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>skip</em> = <code>SKIPINVISIBLE|SKIPFILTERED</code></td>
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
|   | Along with GetTreeProgeny and GetTreeSibling These 3 functions allow to walk the complete tree hierarchy and skip possible objects based on paramatwers passed in. |

<span id="ddeb98d5cf1bdde9d31e8d13774619dd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * HTreeObject::GetTreeProgeny</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">UINT </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>skip</em> = <code>SKIPINVISIBLE|SKIPFILTERED</code></td>
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
|   | Along with GetTreeParent and GetTreeSibling These 3 functions allow to walk the complete tree hierarchy and skip possible objects based on paramatwers passed in. |

<span id="afae92abc783f082ab8db3fc5fc172b5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * HTreeObject::GetTreeSibling</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">UINT </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>skip</em> = <code>SKIPINVISIBLE|SKIPFILTERED</code></td>
<td class="md" data-valign="top"> )