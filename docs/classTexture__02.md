## Constructor & Destructor Documentation

<span id="32cd4cb5ed204a076cb7f3e52ba32efc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">Texture::Texture</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="Texture_8h-source.md#l00018" class="el">18</a> of file <a href="Texture_8h-source.md" class="el">Texture.h</a>. |

<span id="90700509771ec23b2138028847f67691" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">Texture::Texture</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>htreeobject</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline]</code></td>
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
<td><dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>htreeobject</em> </td>
<td>- is a pointer to the plugins owner. It is the class that the Texture is member of. It is the actual class you see in the PWS tree. The constructor only uses it to set the member variable m_treeobject. This member is used for ReAssignPtr. This is also the pointer returned by <a href="classDLLPlugin.md#3ba36241b4d77d9ed655a45db06da58f" class="el">GetOwner()</a>.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classDLLPlugin.md#c4c3b643593ffd04799c247889aeeaa5" class="el">DLLPlugin::DLLPlugin</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *htreeobject)
</dd>
</dl>
<p>Definition at line <a href="Texture_8h-source.md#l00019" class="el">19</a> of file <a href="Texture_8h-source.md" class="el">Texture.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

