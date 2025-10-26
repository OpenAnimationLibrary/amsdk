me" data-nowrap=""><em>extension</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>fps</em></td>
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
<td><p>This function is called when the user wants to change some save settings. Traditional save settings would be compression, bit-depth, etc.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00075" class="el">75</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="a0f84a5f45adce795e9e709f52b6d5cc" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int ImageIO::Write</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHBitmapNode.md" class="el">HBitmapNode</a> * </td>
<td class="mdname" data-nowrap=""><em>bn</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHOutputInfo.md" class="el">HOutputInfo</a> * </td>
<td class="mdname" data-nowrap=""><em>outputinfoconst</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>filename</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">short * </td>
<td class="mdname" data-nowrap=""><em>wavedata</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">BOOL </td>
<td class="mdname" data-nowrap=""><em>hasaudio</em></td>
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
<td><p>This function is called when a Frame or an image is ready to be saved to file. The file is opened first if it is not already open.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>bn</em> </td>
<td>- Points to the <a href="classHBitmapNode.md" class="el">HBitmapNode</a> that contains the image data, that is all the channels and buffers, to be saved.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>outputinfoconst</em> </td>
<td>- Points to the <a href="classHOutputInfo.md" class="el">HOutputInfo</a> that contains all the metadata that may be stored with the image data.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>filename</em> </td>
<td>- is the fully qualified filename where the data should be saved.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>wavedata</em> </td>
<td>- points to an array of sound data.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>hasaudio</em> </td>
<td>- TRUE if the frame is accompanied with sound data.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="ImageIO_8h-source.md#l00090" class="el">90</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>References <a href="DLLPlugi_8h-source.md#l00045" class="el">DLLPlugin::GetClassName()</a>, <a href="ImageIO_8h-source.md#l00062" class="el">m_isopened</a>, <a href="ImageIO_8h-source.md#l00077" class="el">OpenWriteFrame()</a>, <a href="macwinsock_8h-source.md#l00036" class="el">TRUE</a>, <a href="classHBitmapNode.md#68986ab776eb5d6b5a809a1c005a73006ffd8aa558c1ab84ddc0a01e4f14ed0d" class="el">HBitmapNode::WRITE_ERROR</a>, and <a href="ImageIO_8h-source.md#l00078" class="el">WriteFrame()</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classImageIO_a0f84a5f45adce795e9e709f52b6d5cc_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classImageIO_a0f84a5f45adce795e9e709f52b6d5cc_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="1a5e64211835e97b625450f3b94ab38f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int ImageIO::WriteFrame</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHBitmapNode.md" class="el">HBitmapNode</a> * </td>
<td class="mdname" data-nowrap=""><em>bn</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHOutputInfo.md" class="el">HOutputInfo</a> * </td>
<td class="mdname" data-nowrap=""><em>outputinfo</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>filename</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">short * </td>
<td class="mdname" data-nowrap=""><em>wavedata</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">BOOL </td>
<td class="mdname" data-nowrap=""><em>hasaudio</em></td>
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
<td><p>This function is called to save a frame to the file. The file is expected to be already opened when this function is called.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00078" class="el">78</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>References <a href="classHBitmapNode.md#68986ab776eb5d6b5a809a1c005a73001ecc89dbe4cbc5edea13ce47f5e4bbab" class="el">HBitmapNode::WRITE_NORESULT</a>.</p>
<p>Referenced by <a href="ImageIO_8h-source.md#l00090" class="el">Write()</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

