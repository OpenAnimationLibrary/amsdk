" class="md"></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="390eb24b93794a767462e20175f3f444" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">static <a href="classHModelCache.md" class="el">HModelCache</a>* HModelCache::New</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const char * </td>
<td class="mdname" data-nowrap=""><em>name</em> = <code>NULL</code>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">BOOL </td>
<td class="mdname" data-nowrap=""><em>embedded</em> = <code>TRUE</code></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [static]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="5ae587b117fac3011b74cdcf10606bdd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHModel.md" class="el">HModel</a> * HModelCache::NewInstance</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHChor.md" class="el">HChor</a> * </td>
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
<td><p>This creates a new instance of a model and associates it with the <a href="classHChor.md" class="el">HChor</a>. But the resulting <a href="classHModel.md" class="el">HModel</a> pointer is only in existance inside the plugin. To actually insert the instance into the <a href="classHChor.md" class="el">HChor</a> the <a href="classHModel.md" class="el">HModel</a> pointer must be inserted into the <a href="classHChor.md" class="el">HChor</a> structure with a call to HChor::InsertChild(), otherwise you can work with the newly created instance in the chor, but the instance will disapear when the plugin exits.</p>
<p>Example:</p>
<div class="fragment">
<pre class="fragment"><code>   HChor *chor;
   HModelCache *hmc_new;
   HModel *working = hmc_new-&gt;NewInstance(chor);
   chor-&gt;InsertChildAtTail(working,TRUE);</code></pre>
</div></td>
</tr>
</tbody>
</table>

<span id="0d2a874c7c7e4f27501d024babf73b7e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HModelCache::SetChanged</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BOOL </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>modified</em> = <code>TRUE</code></td>
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

<span id="cfd844a8aa1817b4a0da30a7779decd2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHSpline.md" class="el">HSpline</a> * HModelCache::StartSpline</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classVector.md" class="el">Vector</a> * </td>
<td class="mdname" data-nowrap=""><em>p1</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> * </td>
<td class="mdname" data-nowrap=""><em>p2</em></td>
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
<td><p>Returns a pointer to the new <a href="classHSpline.md" class="el">HSpline</a> that is created with the two control point positions passed in. Since a legal spline must have a least two control points, you must use this function to create new splines. You can add subsequent control points with HCP::AddCP().</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>p1</em> </td>
<td>- position for the first <a href="classHCP.md" class="el">HCP</a> in the spline.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>p2</em> </td>
<td>- position for the second <a href="classHCP.md" class="el">HCP</a> in the spline.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HModel_8h-source.md" class="el">HModel.h</a>
- C:/Dox/SDK/Comments/<a href="HModel_8dox.md" class="el">HModel.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:56 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
