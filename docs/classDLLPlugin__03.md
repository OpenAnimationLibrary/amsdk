## Member Function Documentation

<span id="15cf01877da7e4c74c262bd2f93db934" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void DLLPlugin::Copy</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classDLLPlugin.md" class="el">DLLPlugin</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>other</em></td>
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
<td><p>This function is called any time the plugin "cache" is changed. Its purpose is to give you the chance to copy any member variables to the instances of the plugin. An example might be the seamless flag on a projection map, here's what that code looks like.</p>
<div class="fragment">
<pre class="fragment"><code>void CustomTexture::Copy( const DLLPlugin &amp;other )
{
  CustomTexture *cache = &amp;(CustomTexture &amp;)other;
  isseamless = cache-&gt;isseamless;
}</code></pre>
</div>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00038" class="el">38</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="faa943acf7066d63ea9ac4e11ff85d67" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char * DLLPlugin::GetClassName</td>
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
<td><p>Your company name and a plugin description (separated by a "\\") should be returned by this function (for example, return <code>"Hash\\BBall"</code>. This string is used as a unique identifier to reload this plugin upon the Project being reloaded by Animation Master. Because the descriptive name received by loading the string resource for the ID returned by <a href="classDLLPlugin.md#53f5bbacfebc29c12c9900ce8ca09827" class="el">GetNameID()</a> is localized, it cannot be used for comparison purposes. This string should not be localized, remaining the same no matter what language the machine may be using.</p>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00045" class="el">45</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>Referenced by <a href="ImageIO_8h-source.md#l00090" class="el">ImageIO::Write()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="6e2cb2131a42b53ee9686db143d92532" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">UINT DLLPlugin::GetIconID</td>
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
<td><p>The resource ID for your plugin's icon should be returned by this function. A 32x32 and a 16x16 version should be created for the icon. The larger of the two will be shown as a preview for your plugin in the available plugin attribute pannel. When your plugin is chosen, it's small icon becomes visible in the Project Workspace.</p>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00042" class="el">42</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="53f5bbacfebc29c12c9900ce8ca09827" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">UINT DLLPlugin::GetNameID</td>
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
<td><p>This should be the resource ID of a string resource for the name of your plugin. An ID is used rather than text to aid in localization.</p>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00044" class="el">44</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="68cef93ef1d645582bbfe362c654eedd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual int DLLPlugin::GetNumProperties</td>
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
<td><p>Definition at line <a href="DLLPlugi_8h-source.md#l00048" class="el">48</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="DLLPlugi_8h-source.md#l00047" class="el">GetPropertyAt()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDLLPlugin_68cef93ef1d645582bbfe362c654eedd_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDLLPlugin_68cef93ef1d645582bbfe362c654eedd_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="3ba36241b4d77d9ed655a45db06da58f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a>* DLLPlugin::GetOwner</td>
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
<td><p>Definition at line <a href="DLLPlugi_8h-source.md#l00039" class="el">39</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="DLLPlugi_8h-source.md#l00024" class="el">m_treeobject</a>.</p></td>
</tr>
</tbody>
</table>

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
<td class="md" data-nowrap="" data-valign="top"><a href="classHProperty.md" class="el">HProperty</a> * DLLPlugin::GetPropertyAt</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>i</em></td>
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
<td><p>In order for a property to show in plugin property panel of the PWS, the <a href="classHProperty.md" class="el">HProperty</a> derived class must be assigned an index.</p>
<p>GetPropertyAt is continuously called until you return NULL. The count parameter 'i' starts out at zero on the first call, and increments for each subsequent call. For each property you wish to add to the property panel, you return the pointer to the apporpriate <a href="classHProperty.md" class="el">HProperty</a> derived class instance. For example:</p>
<div class="fragment">
<pre class="fragment"><code>HProperty *CustomTurbulence::GetPropertyAt( int i )
{
   switch (i) {
      case 0:
         return m_octaves;
      case 1:
         return m_density;
      case 2:
         return m_diameter;
      case 3:
         return m_euclid;
      default:
         return NULL;
   }
}</code></pre>
</div>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>i</em> </td>
<td>- The index value corresponds to the position of the property UI in the panel.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Returns:</strong></dt>
<dd>
<strong>You</strong> must return A pointer to the <a href="classHProperty.md" class="el">HProperty</a> derived class instance associated to the index position;
</dd>
</dl>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
<strong>important</strong> Whenever a group of properties have been added into a <a href="classHCategoryProperty.md" class="el">HCategoryProperty</a>, the <a href="classHCategoryProperty.md" class="el">HCategoryProperty</a> variable needs to be returned by GetPropertyAt call but <strong>not</strong> the properties included in the category.
</dd>
</dl>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00047" class="el">47</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>Referenced by <a href="DLLPlugi_8h-source.md#l00048" class="el">GetNumProperties()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="0bb0af24d1de05b3362b600b7aca58a7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual <a href="classHTreeObject.md" class="el">HTreeObject</a>** DLLPlugin::GetPtrAt</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>index</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="DLLPlugi_8h-source.md#l00061" class="el">61</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>. |

<span id="d95600d5402a0637aac3c6741ad7c0cb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void DLLPlugin::Init</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>time</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="DLLPlugi_8h-source.md#l00037" class="el">37</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>. |

<span id="99712cfce3529b5479ca47ea92742879" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void DLLPlugin::Init</td>
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
<td><p>Definition at line <a href="DLLPlugi_8h-source.md#l00066" class="el">66</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="DLLPlugi_8h-source.md#l00023" class="el">m_hresource</a>.</p>
<p>Referenced by <a href="DLLPlugi_8h-source.md#l00031" class="el">DLLPlugin()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="57d3749c1756078f9ed1b4f3942141f7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual BOOL DLLPlugin::OnNotifyEndProjectLoad</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>productversion</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [inline, virtual]</cod