## Member Function Documentation

<span id="0adf64967594d26c3c57a82b12eadaa6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HModelCache::AddCP</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname" data-nowrap=""><em>cp</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> * </td>
<td class="mdname" data-nowrap=""><em>p</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
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
<td><p>Returns a pointer to the <a href="classHCP.md" class="el">HCP</a> that is created and linked to after the prevcp that is passed in. The position of the new <a href="classHCP.md" class="el">HCP</a> is set to the vector p. Note: NEVER use <a href="classHModelCache.md#0adf64967594d26c3c57a82b12eadaa6" class="el">AddCP()</a> to create a new spline. New splines must be created with <a href="classHModelCache.md#cfd844a8aa1817b4a0da30a7779decd2" class="el">StartSpline()</a>, and subsequent HCPs should be added with <a href="classHModelCache.md#0adf64967594d26c3c57a82b12eadaa6" class="el">AddCP()</a>;</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>cp</em> </td>
<td>- (prevcp) address of the <a href="classHCP.md" class="el">HCP</a> you are adding to.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>p</em> </td>
<td>- position of the new <a href="classHCP.md" class="el">HCP</a> that is to be created.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="a02eeaa5a8558bf3b9dc55ac177ca914" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHDecal.md" class="el">HDecal</a> * HModelCache::AddDecal</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHClip.md" class="el">HClip</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>clipcache</em> = <code>NULL</code></td>
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
<td><p>Adds a Decal. Will create the "decals folder" if it doesn't exist.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>clipcache</em> </td>
<td>- If NULL, a prompt will be displayed to the user.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="0c31ead7f3f8068e74a36881cea3ad61" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHSegmentCache.md" class="el">HSegmentCache</a> * HModelCache::AddSegment</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHBoneCache.md" class="el">HBoneCache</a> * </td>
<td class="mdname" data-nowrap=""><em>parentbonecache</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHBoneCache.md" class="el">HBoneCache</a> * </td>
<td class="mdname" data-nowrap=""><em>afterbonecache</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>name</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">COLORREF </td>
<td class="mdname" data-nowrap=""><em>color</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
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
<td><p>Creates a new bone and places it on the bones tree as child of parentbonecache and right after the afterbonecache. Will also create the <a href="classHBoneCacheContainer.md" class="el">HBoneCacheContainer</a> and an <a href="classHSegmentCache.md" class="el">HSegmentCache</a> where controlled CPs may be added</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>parentbonecache</em> </td>
<td>- Parent of which the new bone will be a child. May be NULL in which case, the new bone is added at the model root level.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>afterbonecache</em> </td>
<td>- The new bone will be added right after this bone</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>name</em> </td>
<td>- the name of the new bone</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>color</em> </td>
<td>- the color of the new bone. Use global function GetColor to get a color according to the number of bones in the model</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Returns:</strong></dt>
<dd>
A pointer to a new <a href="classHSegmentCache.md" class="el">HSegmentCache</a> for the newly created hBoneCache.
</dd>
</dl>
Example:
<div class="fragment">
<pre class="fragment"><code>modelcache-&gt;AddSegment(NULL, NULL, &quot;Bone1&quot;, GetColor(modelcache-&gt;CountBones()));</code></pre>
</div>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classHSegmentCache.md" class="el">HSegmentCache</a>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="931f4a900a59171fe3089af15a767151" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HModelCache::AddToTemporaryGroup</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHGroupCP.md" class="el">HGroupCP</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>gh</em></td>
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
<td><p>This function adds a group of control points to the model's "Untitled" temporary group. You pass in the first <a href="classHGroupCP.md" class="el">HGroupCP</a> of a group to wish to add to the temporary group. This group will be selected when you exit the plugin. The group that is passed into this function will be freed.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>gh</em> </td>
<td>- pointer to the first <a href="classHGroupCP.md" class="el">HGroupCP</a> in the group to add to the temporary group.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="3274cac44dceb79feb800a2740b72cfa" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HModelCache::AttachCPs</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname" data-nowrap=""><em>cp1</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname" data-nowrap=""><em>cp2</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
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
<td><p>Returns whether the two attached control points create a loop. This is TRUE if cp1 and cp2 are the beginning and the end of the same spline. If a loop is created, a number of things happen. If cp2 is the first control point in the spline, the spline is reversed before the loop is made. The last control point in the spline gets deleted (make sure you keep this in mind if you are performing operations on HCPs after they are attached (check the return value to see if a loop was made). Also, the control point before the last control point has its IsLoop flag set, and its GetNext() pointer set to the first <a href="classHCP.md" class="el">HCP</a> in the spline. If the attach operation does not create a loop, then the two HCPs are stacked, and added to their attached control point list. They are also linked to the <a href="classHCP.md#ad476f918ab900fe4392b98ac13e95e1" class="el">HCP::GetHead()</a> which stores the position for all of the control points that are attached to each other.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>cp1</em> </td>
<td>- first control point to attach</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>cp2</em> </td>
<td>- second control point to attach</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
If you use AttachCPs in such a way as to cause a loopback, be careful not to add the tail CP to any <a href="classHGroup.md" class="el">HGroup</a> that you are accumulating, as something happens to that CP after the attach that will cause a crash if you've added it to the group.
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="04a3514a8a2555882dfaea1e07f22293" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HModelCache::AttachHook</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname" data-nowrap=""><em>cp1</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname" data-nowrap=""><em>cp2</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>s</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="81689c896bfdda6a29b2ca764db49ee2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HModelCache::BreakSpline</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>cp</em></td>
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

<span id="884009ddaf9a12edc15dc05801123d73" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEPolyModel.md" class="el">IEPolyModel</a>* HModelCache::BuildExportModel</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEPolyModelParms.md" class="el">IEPolyModelParms</a> * </td>
<td class="mdname" data-nowrap=""><em>iemp</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const char * </td>
<td class="mdname" data-nowrap=""><em>modelmapfilename</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="48d1e14b70895baa8e21bb74074152f4" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classIEPatchModel.md" class="el">IEPatchModel</a>* HModelCache::BuildExportModel</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="cl