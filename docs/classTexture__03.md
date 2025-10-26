## Member Function Documentation

<span id="955a21a0f29558a7d9cee38902b4182d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void Texture::CheckOut</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHHashObject.md" class="el">HHashObject</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>cache</em></td>
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
<td><p>/note Don't use this function. It will be removed in a future version.</p>
<p>Definition at line <a href="Texture_8h-source.md#l00025" class="el">25</a> of file <a href="Texture_8h-source.md" class="el">Texture.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="d184cb8013a0047c62951e5889b14cac" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL Texture::Evaluate</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>evalp</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHTexInfo.md" class="el">HTexInfo</a> * </td>
<td class="mdname" data-nowrap=""><em>texinfo</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
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
<td><p>Every time a surface is encountered during rendering that has your texture on it, Evaluate is called. This gives you the ability to set what the surface's parameters are.</p>
<p>It is important to note that these textures are not "Shaders". The shading is still done after you have returned from Evaluate. You simply get to dictate what the surface is made of.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>evalp</em> </td>
<td>- The 3D coordinate that you should evaluate is passed to you in the form of a <a href="classVector.md" class="el">Vector</a>. This 3D coordinate is the coordinate as computed on the cached object surface. This means that the render time world coordinate on an object surface is reverse transformed to the cached surface. This prevents the texture from floating on the surface as the surface is being deformed from muscle or skeletal actions.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>texinfo</em> </td>
<td>- All of the surface's parameters are sent to you in the texinfo variable. You may set any value in the <a href="classHTexInfo.md" class="el">HTexInfo</a>.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHObjectCache.md" class="el">HObjectCache</a> for a description of cached objects.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="f20fde302c72ec98fec2db094ae975e1" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL Texture::EvaluateTransparency</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>evalp</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHTexInfo.md" class="el">HTexInfo</a> * </td>
<td class="mdname" data-nowrap=""><em>texinfo</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
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
<td><p>When a scene is rendered, it's done in two passes. The first pass determines what is visible, and the second pass shades the visible objects. During this first pass, it is not necessary to evaluate all of the textures. But it is important to know if something is transparent. So for speed's sake, we call another form of the Evaluate funcion, EvaluateTransparency. If your texture has no possible way of setting transparency, simply return TRUE. Otherwise write as little code as it takes to evaluate the transparency at the given evalp.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
Don't worry about any other members of the TexInfo or <a href="classAttr.md" class="el">Attr</a> classes for this pass.
</dd>
</dl>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>evalp</em> </td>
<td>- The 3D coordinate that you should evaluate is passed to you in the form of a <a href="classVector.md" class="el">Vector</a>. This 3D coordinate is the coordinate as computed on the cached object surface. This means that the render time world coordinate on an object surface is reverse transformed to the cached surface. This prevents the texture from floating on the surface as the surface is being deformed from muscle or skeletal actions.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>texinfo</em> </td>
<td>- All of the surface's parameters are sent to you in the texinfo variable. Don't worry about any other members of the TexInfo or <a href="classAttr.md" class="el">Attr</a> classes for this pass.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHObjectCache.md" class="el">HObjectCache</a> for a description of cached objects.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="de8f964adca8147ca8c157c34aea6f7e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHGroup.md" class="el">HGroup</a> * Texture::GetGroup</td>
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
<td><p>Gets to that <a href="classHGroup.md" class="el">HGroup</a> where the Texture instance is currently applied to.</p>
<p>The returned pointer may be NULL if the Texture is only part of a material or if the Texture is directly applied to the model and not to a group.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
There may be several instances of a given Texture plugin. One on a material, one dropped on an object, one dropped on a group of an object. But also, when an object is dropped in a Choreography. In the cases where the Texture is dropped onto a group and then the model is dropped into a choreography, the two different Texture instances will receive different pointers. One HGroup* points to a <a href="classHGroup.md" class="el">HGroup</a> on the cache object while the other points to the <a href="classHGroup.md" class="el">HGroup</a> on the model instance that is dropped in the choreography. You can determine which is which by calling IsCache() of by repetitively calling GetParent() untill you reach an HOT_CHOR or ends to a NULL pointer.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="e46fe26b37492b1d67d204ff30c6d1cf" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHModel.md" class="el">HModel</a> * Texture::GetModel</td>
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
<td><p>Gets to that <a href="classHModel.md" class="el">HModel</a> where the Texture instance is currently applied to.</p>
<p>The returned pointer may be NULL if the Texture is only part of a material.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
There may be several instances of a given Texture plugin. One on a material, one dropped on an object, one dropped on a group of an object. But also, when an object is dropped in a Choreography. In the cases where the Texture is dropped onto a model and then the model is dropped into a choreography, the two different Texture instances will receive different pointers. One HModel* points to a cache object while the other points to the model instance that is dropped in the choreography. You can determine which is which by calling IsCache() of by repetitively calling GetParent() untill you reach an HOT_CHOR or ends to a NULL pointer.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="8ed0074dba65c5d4cb56434b6f63f890" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHObjectListNode.md" class="el">HObjectListNode</a> * Texture::GetPointerList</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">HPointerPropertyBase * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>prop</em></td>
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
<td><p>When the user clicks on a <a href="classHPointerProperty.md" class="el">HPointerProperty</a> inside one of the properties defined by the plugin user interace, this function is called to retrieve the list of pointers to objects in the PWS that will be displayed in the drop-down list.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>prop</em> </td>
<td>- points to one of the <a href="classHPointerProperty.md" class="el">HPointerProperty</a> defined in your plugin interface. You can use this pointer to determine which <a href="classHPointerProperty.md" class="el">HPointerProperty</a> the call relates to and decide what to fill the <a href="classHObjectListNode.md" class="el">HObjectListNode</a> with.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPointerPropertyInfo.md" class="el">HPointerPropertyInfo</a> and <a href="classHPointerProperty.md" class="el">HPointerProperty</a>
</dd>
</dl>
<p>Definition at line <a href="Texture_8h-source.md#l00024" class="el">24</a> of file <a href="Texture_8h-source.md" class="el">Texture.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="0d1cbd915a53fe344d1e8e6995431dab" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void Texture::OnNotifyNewProperty</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * </td>
<td class="mdname" data-nowrap=""><em>prop</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>matchname</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline, virtual]</code></td>
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
<td><p>If your plugin allows the user to add custom properties, this function will be called the custom property is created, when the project is loaded or when additional instances of the plugin are later created. This allows you to save a poiner to the custom property for quick access when processing.</p>
<p>Definition at line <a href="Texture_8h-source.md#l00026" class="el">26</a> of file <a href="Texture_8h-source.md" class="el">Texture.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="Texture_8h-source.md" class="el">Texture.h</a>
- C:/Dox/SDK/Comments/<a href="Texture_8dox.md" class="el">Texture.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this docume