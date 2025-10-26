## Member Function Documentation

<span id="a0a4b50715c542004fc6435d77305f0c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HSpline::CreateCPAfter</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname" data-nowrap=""><em>aftercp</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
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
<td><p>Creates a new <a href="classHCP.md" class="el">HCP</a> and places it after the specified <a href="classHCP.md" class="el">HCP</a> of the spline.</p>
<p>If aftercp points to the spline tail <a href="classHCP.md" class="el">HCP</a>, the result is the same as with <a href="classHSpline.md#b599fca54be6c93e9b2fe2aa1f40fd0e" class="el">CreateCPAtTail(const Vector &amp;p)</a>.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>aftercp</em> </td>
<td>- Points to the current <a href="classHCP.md" class="el">HCP</a> in the spline after which the new <a href="classHCP.md" class="el">HCP</a> will be inserted.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>p</em> </td>
<td>- Specifies the coordinate of the new control point.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="7bd5373fa4f52b6bda07da2c856726f6" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HSpline::CreateCPAtHead</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>p</em></td>
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
<td><p>Creates a new <a href="classHCP.md" class="el">HCP</a> and places it before the first <a href="classHCP.md" class="el">HCP</a> of the spline. The new <a href="classHCP.md" class="el">HCP</a> becomes the head control point.</p>
<p>If the spline is looped, the new <a href="classHCP.md" class="el">HCP</a> also becomes the tail control point.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>p</em> </td>
<td>- Specifies the coordinate of the new control point.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="b599fca54be6c93e9b2fe2aa1f40fd0e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HSpline::CreateCPAtTail</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>p</em></td>
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
<td><p>Creates a new <a href="classHCP.md" class="el">HCP</a> and places it after the last <a href="classHCP.md" class="el">HCP</a> of the spline. The new <a href="classHCP.md" class="el">HCP</a> becomes the tail control point.</p>
<p>If the spline is looped, the new <a href="classHCP.md" class="el">HCP</a> also becomes the head control point.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>p</em> </td>
<td>- Specifies the coordinate of the new control point.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="6a1920a906967f5ac97b8a3c238de8c5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HSpline::CreateCPBefore</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * </td>
<td class="mdname" data-nowrap=""><em>beforecp</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classVector.md" class="el">Vector</a> &amp; </td>
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
<td><p>Creates a new <a href="classHCP.md" class="el">HCP</a> and places it before the specified <a href="classHCP.md" class="el">HCP</a> of the spline.</p>
<p>If beforecp points to the spline head <a href="classHCP.md" class="el">HCP</a>, the result is the same as with <a href="classHSpline.md#7bd5373fa4f52b6bda07da2c856726f6" class="el">CreateCPAtHead(const Vector &amp;p)</a>.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>beforecp</em> </td>
<td>- Points to the current <a href="classHCP.md" class="el">HCP</a> in the spline before which the new <a href="classHCP.md" class="el">HCP</a> will be inserted.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>p</em> </td>
<td>- Specifies the coordinate of the new control point.</td>
</tr>
</tbody>
</table>
</dd>
</dl></td>
</tr>
</tbody>
</table>

<span id="b6a361434a2d7163a6b467370d21db94" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HSpline::DeleteCP</td>
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

|  |  |
|----|----|
|   | Deletes the specifid <a href="classHCP.md" class="el">HCP</a> from the spline and destroys it. |

<span id="f477a35df122a79dd95580efabfbcd99" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HSpline::DeleteHandle</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHSpline.md" class="el">HSpline</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>handle</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap=""><code> [static]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |                                  |
|-----|----------------------------------|
|     | Explicitly destroys the HSpline. |

<span id="d55b4a9828c87389479aeeea3f625fde" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHCP.md" class="el">HCP</a> * HSpline::GetHeadCP</td>
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
|   | Returns a pointer to the first <a href="classHCP.md" class="el">HCP</a> in the spline. |

<span id="0670dbd645d0e24b7f8f78d5c15d6aca" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">float HSpline::GetLength</td>
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

<span id="d638e82fae03cc73eaeb2c9dbf8a4924" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classHSpline.md" class="el">HSpline</a> * HSpline::GetNextSpline</td>
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
|   | Returns a pointer to teh next spline in the list of spline that composes a model. |

<span id="4e95473761f6d1b3a69e5c3063899862" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HSpline::GetPositionAndDirection</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">float </td>
<td class="mdname" data-nowrap=""><em>ease</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>position</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>direction</em></td>
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

<span id="0b59a0b77ff12ca23290e23fc9726e08" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL HSpline::MakeLooped</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BOOL </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>looped</em></td>
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
|   | Marks the Spline as looped. In essence, that creates a spline segment between the head and the tail HCPs of the spline. |

<span id="b2a90b0840ba0f087728d89d27353935" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void HSpline::operator delete</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">void * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>ptr</em></td>
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
<td><p>Destructor for the HSpline.</p>
<p>Reimplemented from <a href="classHTreeObject.md#b2a90b0840ba0f087728d89d27353935" class="el">HTreeObject</a>.</p>
<p>Definition at line <a href="HPatch_8h-source.md#l00025" class="el">25</a> of file <a href="HPatch_8h-source.md" class="el">HPatch.h</a>.</p>
<p>References <a href="classHTreeObject.md#68a56f970bf31e136b0855e2de4ac987" class="el">HTreeObject::DeleteHandle()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classHSpline_b2a90b0840ba0f087728d89d27353935_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classHSpline_b2a90b0840ba0f087728d89d27353935_cgraph_map"></span></td>
<