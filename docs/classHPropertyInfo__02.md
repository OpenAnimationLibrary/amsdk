## Member Enumeration Documentation

<span id="938bb49d7705f658d715e113fbec5a3b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">enum <a href="classHPropertyInfo.md#938bb49d7705f658d715e113fbec5a3b" class="el">HPropertyInfo::DrawWhen</a></td>
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
<td><p>Controls when the property will be displayed in the PWS for the user to enter values.</p>
<p>From the SDK point of view, a plugin possess a list of properties which are all grouped together inside a property panel. The panel is displayable by clicking on the little expand triangle that is visible on a node of the PWS tree.</p>
<p>A plugin property pannel may be accessible from different context. For example, the properties for a turbulence plugin may be accessible from a material node, from a material shortcut on a model or on a group and from a material shortcut on a model shortcut in choreography. For some particular properties, it may be desirable to let the user modify them only when inside a material node for instance.</p>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPropertyInfo.md#4df6d0366bb8d5a8d632f42996e5da3b" class="el">HPropertyInfo::GetDrawWhen</a>, <a href="classHPropertyInfo.md#c89057a96b3fcfb41b37d8d04fddf81d" class="el">HPropertyInfo::SetDrawWhen</a>
</dd>
</dl>
<dl>
<dt><strong>Enumerator:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"><em><span id="938bb49d7705f658d715e113fbec5a3be0ff367e611bbdad74cb43f7a48fb9e9" class="anchor"></span>DRAWNEVER</em> </td>
<td>The property will never be displayed in the PWS. This can be used for a plugin to store values that might be retrieved from call to call.</td>
</tr>
<tr>
<td data-valign="top"><em><span id="938bb49d7705f658d715e113fbec5a3b090563064c468a940a62ce66b7aecb98" class="anchor"></span>DRAWALWAYS</em> </td>
<td>The property will always be displayed in the PWS, no matter the context in which the property panel is displayed.</td>
</tr>
<tr>
<td data-valign="top"><em><span id="938bb49d7705f658d715e113fbec5a3b3d509dabac59020987fbd1c560cdc261" class="anchor"></span>DRAWIFSHADED</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="938bb49d7705f658d715e113fbec5a3bc7f2c4e5d9940cfff3aaa220b1c9e383" class="anchor"></span>DRAWIFFLARES</em> </td>
<td></td>
</tr>
<tr>
<td data-valign="top"><em><span id="938bb49d7705f658d715e113fbec5a3bb3bc3a06f2d8f2c01cb89403763477b1" class="anchor"></span>DRAWIFMATERIALS</em> </td>
<td>The property will only be displayed if the property panel is displayed inside a material node. It will not be displayed when the property panel is inside a material shortcut on a model or group or is inside a material shortcut on a model shortcut in choreography.</td>
</tr>
<tr>
<td data-valign="top"><em><span id="938bb49d7705f658d715e113fbec5a3bfccd94c2ee6df6af6f1c6ebe98c4fde2" class="anchor"></span>DRAWIFPARTICLES</em> </td>
<td></td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="HPropert_8h-source.md#l00026" class="el">26</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="c466cc39b9102b48474e59155142691c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">enum <a href="classHPropertyInfo.md#c466cc39b9102b48474e59155142691c" class="el">HPropertyInfo::VisibleWhen</a></td>
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
<td><p>Controls how a plugin can switch visibility of a property in the PWS for the user to enter values.</p>
<p>This is different than DrawWhen in that VisibleWhen imposes restriction on the actions of <a href="classHProperty.md#e272a91d689ceb51c964a4d8be8b3503" class="el">HProperty::Show</a> during plugin execution.</p>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPropertyInfo.md#f0713d14f95bec4f16e992b844fb24a5" class="el">HPropertyInfo::GetVisibleWhen</a>, <a href="classHPropertyInfo.md#0167de075e18bec49d7a4ffd63687bbd" class="el">HPropertyInfo::SetVisibleWhen</a>
</dd>
</dl>
<dl>
<dt><strong>Enumerator:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"><em><span id="c466cc39b9102b48474e59155142691c709f05c44cffd50c472d8528ee62eaff" class="anchor"></span>VISIBLENEVER</em> </td>
<td>The property will never be visible. Even when HProperty::Show(TRUE) is called.</td>
</tr>
<tr>
<td data-valign="top"><em><span id="c466cc39b9102b48474e59155142691cd0990d9c1c5727acf1261eca1ae80e28" class="anchor"></span>VISIBLEALWAYS</em> </td>
<td>The property will always be visible. Even when HProperty::Show(FALSE) is called. This is the default visibility behavior.</td>
</tr>
<tr>
<td data-valign="top"><em><span id="c466cc39b9102b48474e59155142691cfb9db43723463c3ec7b1ba44bf80f0f4" class="anchor"></span>VISIBLECACHEONLY</em> </td>
<td>The property will be visible or hidden only when the property pannel is in the original model, material, etc. It will not be visible and cannot be made visible when on an instance of a model, a material, etc.</td>
</tr>
<tr>
<td data-valign="top"><em><span id="c466cc39b9102b48474e59155142691cb7b3d7ebfb29c2d85a4fcc8e7e6fa16f" class="anchor"></span>VISIBLEINSTANCEONLY</em> </td>
<td>The property may only be made visible or hidden when the property pannel is on an instance (a shortcut) of an original model, material, etc. It will not be visible and cannot be made visible when on an original model, material, etc.</td>
</tr>
<tr>
<td data-valign="top"><em><span id="c466cc39b9102b48474e59155142691c45be275b9431f252ff844c56ac02388a" class="anchor"></span>VISIBLESOMETIMES</em> </td>
<td>The property may be visible or hidden as required by the plugin internal status by calling <a href="classHProperty.md#e272a91d689ceb51c964a4d8be8b3503" class="el">HProperty::Show</a>.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="HPropert_8h-source.md#l00027" class="el">27</a> of file <a href="HPropert_8h-source.md" class="el">HPropert.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

