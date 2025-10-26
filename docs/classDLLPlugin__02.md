## Constructor & Destructor Documentation

<span id="c4c3b643593ffd04799c247889aeeaa5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">DLLPlugin::DLLPlugin</td>
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

<table data-cellspacing="5" data-cellpadding="0" data-border="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td> </td>
<td><p>The constructor is where all the per-instance initialization is done for the texture. I say per-instance because within a given scene, a new copy of your plugin is created for every object it is applied to. This allows for time-based textures, for example, that are different on a per-instance basis.</p>
<p>There are however certain things that should not be instanced, but rather declared static within your derived class. Anything that is constant between all instances should be done this way to preserve memory, and sometimes initialization time. The most common case of this is a noise table in a texture derived class, which could be declared as a member variable somewhere in your class something like this.</p>
<div class="fragment">
<pre class="fragment"><code>static short noiz_tbl[MAXX][MAXY][MAXZ];</code></pre>
</div>
<p>The constructor would then initialize it only if it hasn't already been done. Saving time and memory.</p>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00031" class="el">31</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="DLLPlugi_8h-source.md#l00066" class="el">Init()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDLLPlugin_c4c3b643593ffd04799c247889aeeaa5_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDLLPlugin_c4c3b643593ffd04799c247889aeeaa5_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="f0e90a77fb25e2cad7dc99af718caa0a" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">DLLPlugin::DLLPlugin</td>
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
<td>- is a pointer to the plugins owner. It is the class that the plugin is member of. It is the actual class you see in the PWS tree. The constructor only uses it to set the member variable m_treeobject. This member is used for ReAssignPtr. This is also the pointer returned by <a href="classDLLPlugin.md#3ba36241b4d77d9ed655a45db06da58f" class="el">GetOwner()</a>.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classDLLPlugin.md#c4c3b643593ffd04799c247889aeeaa5" class="el">DLLPlugin::DLLPlugin()</a>
</dd>
</dl>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00032" class="el">32</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="DLLPlugi_8h-source.md#l00066" class="el">Init()</a>, and <a href="DLLPlugi_8h-source.md#l00024" class="el">m_treeobject</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDLLPlugin_f0e90a77fb25e2cad7dc99af718caa0a_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDLLPlugin_f0e90a77fb25e2cad7dc99af718caa0a_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="c5d1960463d887d6a763c22f2adbcc34" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">DLLPlugin::~DLLPlugin</td>
<td class="md" data-valign="top">( </td>
<td class="mdname1" data-valign="top" data-nowrap=""></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
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
<td><p>Any allocations made by your plugin should be freed here.</p>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00033" class="el">33</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

