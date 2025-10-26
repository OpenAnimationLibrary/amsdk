## Member Function Documentation

<span id="17f56a001b2653f1861b5630142b9bdb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL ImageIO::CanLoadImage</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>filename</em></td>
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
<td><p>This function is called to check if a file with a given filename can be read by the plugin. The function should not just check the filename extension but should also attempt to open the file and read whatever data (that is usually the file header) to make sure it is in the proper format.</p>
<p>Return TRUE if the file can be read by the plugin.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00073" class="el">73</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="6f27a575293bfb79e39aeecea8961d66" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void ImageIO::CloseWrite</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BOOL </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>hasaudio</em></td>
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
<td><p>For file format that can store multiple frames in the same file, this function is called when the total number of files have been saved.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00121" class="el">121</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>References <a href="ImageIO_8h-source.md#l00079" class="el">CloseWriteFrame()</a>, <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>, and <a href="ImageIO_8h-source.md#l00062" class="el">m_isopened</a>.</p>
<p>Here is the call graph for this function:</p>
<span class="image placeholder" data-original-image-src="classImageIO_6f27a575293bfb79e39aeecea8961d66_cgraph.gif" data-original-image-title="" data-border="0" usemap="#classImageIO_6f27a575293bfb79e39aeecea8961d66_cgraph_map"></span></td>
</tr>
</tbody>
</table>

<span id="3df7f33bf39d59d95b3c326e163fb34c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">void ImageIO::CloseWriteFrame</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">BOOL </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>hasaudio</em></td>
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
<td><p>This function is called to close a file after the total number of frames have been saved.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00079" class="el">79</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>Referenced by <a href="ImageIO_8h-source.md#l00121" class="el">CloseWrite()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="55156800eca572758197fd7700077f8d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void ImageIO::GetFilesStartEndFrame</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>filename</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int &amp; </td>
<td class="mdname" data-nowrap=""><em>start</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">int &amp; </td>
<td class="mdname" data-nowrap=""><em>end</em></td>
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

|  |  |
|----|----|
|   | Definition at line <a href="ImageIO_8h-source.md#l00074" class="el">74</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>. |

<span id="651da01e2e4561e9f8a3b1e084f56c2f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL ImageIO::GetImageIOInfo</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classImageIOInfo.md" class="el">ImageIOInfo</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>iioinfo</em></td>
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
<td><p>This function is called when the ImageIO are registered with Animation:Master. The function should fill the <a href="classImageIOInfo.md" class="el">ImageIOInfo</a> with the appropriate information.</p>
<dl>
<dt><strong>See also:</strong></dt>
<dd>
<a href="classImageIOInfo.md" class="el">ImageIOInfo</a>
</dd>
</dl>
<p>Definition at line <a href="ImageIO_8h-source.md#l00076" class="el">76</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="b5e02f4aac715fe7eeed4d85e199127d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int ImageIO::IsFileOpen</td>
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
<td><p>Should return TRUE if the file is currently open.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00081" class="el">81</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>References <a href="macwinsock_8h-source.md#l00040" class="el">FALSE</a>.</p></td>
</tr>
</tbody>
</table>

<span id="bd81ab01c395d2e7451921c3c69eb7dd" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int ImageIO::LoadFrame</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHBitmapNode.md" class="el">HBitmapNode</a> * </td>
<td class="mdname" data-nowrap=""><em>bn</em>,</td>
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
<td class="md" data-nowrap="">int </td>
<td class="mdname" data-nowrap=""><em>frame</em> = <code>-1</code>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">UINT </td>
<td class="mdname" data-nowrap=""><em>flags</em> = <code>0</code></td>
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
<td><p>This function is called to read a frame from a file.</p>
<dl>
<dt><strong>Parameters:</strong></dt>
<dd>
<table data-border="0" data-cellspacing="2" data-cellpadding="0">
<tbody>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>bn</em> </td>
<td>- The <a href="classHBitmapNode.md" class="el">HBitmapNode</a> where the frame image data should be loaded.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>filename</em> </td>
<td>- The filename where the frame image data is loaded from. The filename should be assumed to have been tested with CanLoadImage prior to calling LoadFrame.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>frame</em> </td>
<td>- Specifies the frame number to load. For file formats that can store only one frame, this parameter will be -1.</td>
</tr>
<tr>
<td data-valign="top"></td>
<td data-valign="top"><em>flags</em> </td>
<td>- Load flags. See <a href="classHBitmapNode.md" class="el">HBitmapNode</a> for a list of Load Flags. They are <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f90a3eda5885d0d1d9df4b7ca5186ab8d19" class="el">HBitmapNode::LOADDEFAULT</a>, <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f908d752d82170bc40c52648233fb4b2e92" class="el">HBitmapNode::LOADBKCOLOR</a>, <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f90c32120c146000b42843de769221473a6" class="el">HBitmapNode::LOADINFOONLY</a>, <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f9067d00896560d72e79b9aa815b703e9b0" class="el">HBitmapNode::INITIALIZE</a>, <a href="classHBitmapNode.md#a481861fff87f0ebf88ec15d9e206f906fe5a6de34947399bec1de494faffbb4" class="el">HBitmapNode::NOMODIFIEDCHECK</a> and can be OR combined.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
<p>Definition at line <a href="ImageIO_8h-source.md#l00080" class="el">80</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>References <a href="classHBitmapNode.md#dca29a1140aadadfd92b34a02fa516ef7b0d329a6efd1e7a527acf8970807616" class="el">HBitmapNode::LOAD_FAILED</a>.</p></td>
</tr>
</tbody>
</table>

<span id="564e67564668f9f9eef3ec34dd73120d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int ImageIO::OpenWriteFrame</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> </td>
<td class="mdname" data-nowrap=""><em>filename</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classHBitmapNode.md" class="el">HBitmapNode</a> * </td>
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
<td><p>This function should open the file.</p>
<p>This would also be the appropriate place to write the file header in the case of file format that allow saving multiple frames in the same file.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00077" class="el">77</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p>
<p>Referenced by <a href="ImageIO_8h-source.md#l00090" class="el">Write()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="c3cb38eb00c293dd5ea6727fdd14a47d" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL ImageIO::SetSaveOptions</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">CWnd * </td>
<td class="mdname" data-nowrap=""><em>parent</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const <a href="classString.md" class="el">String</a> &amp; </td>
<td class="mdna