e></td>
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
<td><p>Definition at line <a href="DLLPlugi_8h-source.md#l00058" class="el">58</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00036" class="el">TRUE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="a4ccb53d5129585318973cb0c14b7a4f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL DLLPlugin::OnPtrMessage</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="PtrMessa_8h.md#914b6f635a6e54f9671412ac4b018f95" class="el">PtrMessage</a> </td>
<td class="mdname" data-nowrap=""><em>ptrmessage</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHTreeObject.md" class="el">HTreeObject</a> ** </td>
<td class="mdname" data-nowrap=""><em>ptruplink</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">LONG </td>
<td class="mdname" data-nowrap=""><em>lparam</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classTime.md" class="el">Time</a> </td>
<td class="mdname" data-nowrap=""><em>time</em> = <code>0</code></td>
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
<td><p>When a user clicks within the property control you will receive a call to your virtual OnPtrMessage function.</p>
<div class="fragment">
<pre class="fragment"><code>BOOL CustomTexture::OnPtrMessage(PtrMessage ptrmessage, HTreeObject
**ptruplink, LONG lparam, Time time)
{
   int i=0;
   switch (ptrmessage )
   {
      case PTM_VALUESTORED: {
         HProperty *dueto = (HProperty*)lparam;
         if (dueto == m_buttonproperty) { // use your properties address here
                         ...
         }
         return TRUE;
      }
      case PTM_DELETED:
         m_mygroup = NULL;
         return TRUE;
      case PTM_RENAMED:
          // Group was renamed, might do something here
          return TRUE;
   return FALSE;
}</code></pre>
</div>
<p>If anyone ever deletes the hgroup, the hgroup will notify all of its dependences (classes that called ReassignPtr with it as a parameter) that hgroup is being deleted. It does this through the OnPtrMessage virtual function in your DllPlugin class.</p>
<p>So lets say the user deletes the hgroup in the interface that your plugin has a pointer to. Your DLLPlugin class will receive an OnPtrMessage call that will notify you that the group was deleted.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>ptrmessage</em> </td>
<td>- is set to one of the predefined in PtrMessage.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>ptruplink</em> </td>
<td>-</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>lparam</em> </td>
<td>- Holds the <a href="classHProperty.md" class="el">HProperty</a> object address (must be casted to the actual object type). If ptrmessage is of type PTM_FPSCHANGED then this parameter points to that new FPS value.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>time</em> </td>
<td>-</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
PtrMessages are listed in file <a href="PtrMessa_8h.md" class="el">PtrMessa.h</a>.
</dd>
</dl>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00063" class="el">63</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="a9daf3263af811a5aef6fda8f5533075" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL DLLPlugin::ParseArg</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const char * </td>
<td class="mdname" data-nowrap=""><em>label</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const char * </td>
<td class="mdname" data-nowrap=""><em>value</em></td>
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
<td><p>Reading saved values back in is the job of ParseArg.</p>
<p>ParseArg is called for each line within the plugin parameters portion of a material file that the standard parser does not understand. This gives you the chance to handle the loading of this data. If you did parse the label, and decide it is one of yours, you should return TRUE, otherwise return FALSE. Here is an example of how to read what we wrote out in the previous example:</p>
<div class="fragment">
<pre class="fragment"><code>BOOL CustomTexture::ParseArg( const char *label, const char *value )
{
   if (strcmp(label, &quot;ShowPreview&quot;) == 0) {
      showpreview = (strcmp(value, &quot;ON&quot;) == 0);
      return TRUE;
   }
   return FALSE;
}</code></pre>
</div>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
<p>ParseArg is called when a v8.5 or earlier file is loaded or when a property not handled by the <a href="classHProperty.md" class="el">HProperty</a> and <a href="classHPropertyInfo.md" class="el">HPropertyInfo</a> derived classes.</p>
<p>Because the standard parser will stop calling this member function whenever it encounters a label that it recognize, the use of standard reserved parser words such as "Ambiance" for instance should be avoided. It is better to customize your labels by appending or prepending some letters such as your initials for example.</p>
</dd>
</dl>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00057" class="el">57</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="4b29014666e184078e964ff750bdbdb2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL DLLPlugin::ReassignPtr</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void * </td>
<td class="mdname" data-nowrap=""><em>ptruplink</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="mdname" data-nowrap=""><em>newvalue</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [inline]</code></td>
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
<td><p>ReassignPtr adds information to the assigned object that states that your class has a pointer to it. This information may be used later through calls to OnPtrMessage to let the plugin know that something have happened to the referenced object.</p>
<p>Lets say you have this member variable in your CustumTexture class:</p>
<div class="fragment">
<pre class="fragment"><code>HGroup *m_mygroup;</code></pre>
</div>
<p>You can call</p>
<div class="fragment">
<pre class="fragment"><code>ReassignPtr(&amp;m_mygroup,  hgroup);</code></pre>
</div>
<p>This will set m_mygroup to hgroup. You do this rather than m_mygroup = group. What ReassignPtr actually does is adds information to the hgroup that states that your class has a pointer to it.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
You do not have to explicitly assign your ptruplinks to NULL if you used <a href="classDLLPlugin.md#0bb0af24d1de05b3362b600b7aca58a7" class="el">DLLPlugin::GetPtrAt</a> properly.
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classDLLPlugin.md#0bb0af24d1de05b3362b600b7aca58a7" class="el">DLLPlugin::GetPtrAt</a> (int index)
</dd>
</dl>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>ptruplink</em> </td>
<td>- pointer to the local object pointer which holds the address of the referenced object.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>newvalue</em> </td>
<td>- Pointer to the object which is assigned to ptruplink</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00062" class="el">62</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="DLLPlugi_8h-source.md#l00024" class="el">m_treeobject</a>, and <a href="classHTreeObject.md#4b29014666e184078e964ff750bdbdb2" class="el">HTreeObject::ReassignPtr()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classDLLPlugin_4b29014666e184078e964ff750bdbdb2_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classDLLPlugin_4b29014666e184078e964ff750bdbdb2_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="1d8d03ad8d186f5d578439342a6f9b41" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL DLLPlugin::Save</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">char *&amp; </td>
<td class="mdname" data-nowrap=""><em>label</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">char *&amp; </td>
<td class="mdname" data-nowrap=""><em>value</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>count</em></td>
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
<td><p>When a plugin specific parameter set is saved to disk, the Save function is called to write out your custom data. Some common examples of things written in this function are boolean variables, and filenames.</p>
<p>Save is continuously called until you return FALSE. The count variable starts out at zero on the first call, and increments for each subsequent call. For each item you wish to write you fill the label and value variables with the appropriate text. For example:</p>
<div class="fragment">
<pre class="fragment"><code>BOOL CustomTexture::Save( char *&amp;label, char *&amp;value, int count )
{
  switch (count) {
  case 0:
     label = &quot;ShowPreview&quot;;
     value = showpreview ? &quot;ON&quot; : &quot;OFF&quot;;
     return TRUE;
  }
  return FALSE;
}</code></pre>
</div>
<p>This would write a line out in the material file that says "ShowPreview=ON". You would add more cases for each line you wish to write out.</p>
<p>Labels should be choosen so that they are not mistaken with any typical reserved labels in the A:M files. See CustomTexture::ParseArg for an explanation.</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
The Save function should be used for any data that are not properties derived from <a href="classHProperty.md" class="el">HProperty</a> <strong>and</strong> associated with a derived class of <a href="classHPropertyInfo.md" class="el">HPropertyInfo</a>. For <a href="classHProperty.md" class="el">HProperty</a> associated to an <a href="classHPropertyInfo.md" class="el">HPropertyInfo</a>. the values are automatically stored using the MatchName as tag.
</dd>
</dl>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHPropertyInfo.md" class="el">HPropertyInfo</a>
</dd>
</dl>
<p>Definition at line <a href="DLLPlugi_8h-source.md#l00056" class="el">56</a> of file <a href="DLLPlugi_8h-source.md" class="el">DLLPlugi.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

