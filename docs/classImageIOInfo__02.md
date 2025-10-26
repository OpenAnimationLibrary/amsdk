## Member Data Documentation

<span id="e1a49225531be67570e9e5c2b1844c23" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL <a href="classImageIOInfo.md#e1a49225531be67570e9e5c2b1844c23" class="el">ImageIOInfo::m_candomultiframes</a></td>
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
<td><p>Indicates if the plugin can process (read-write) multiple frames in one single file. QuickTime and AVI can obviously do that. Gif can too. But Targa can't.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00040" class="el">40</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="6a39d77b62f6c68c120e0eea077aa29c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL <a href="classImageIOInfo.md#6a39d77b62f6c68c120e0eea077aa29c" class="el">ImageIOInfo::m_canstorealpha</a></td>
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
<td><p>Indicates if the plugin can store alpha channels with the image data.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00043" class="el">43</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="2d7f2e482a3d430ed3cef9d10d01101e" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL <a href="classImageIOInfo.md#2d7f2e482a3d430ed3cef9d10d01101e" class="el">ImageIOInfo::m_canstoremultibuffers</a></td>
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
<td><p>Indicates if the plugin can store multiple buffers.</p>
<p>OpenEXR and Jpeg2000 can do that.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00045" class="el">45</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="29b11c67151569202cf1c3a9d65a8728" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL <a href="classImageIOInfo.md#29b11c67151569202cf1c3a9d65a8728" class="el">ImageIOInfo::m_canstoresound</a></td>
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
<td><p>Indicates if the plugin can store sound data. Either in the same file, with image data or on separate file.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00044" class="el">44</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="6f52298a9c8f7f05e3ce4f73c048d7d7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL <a href="classImageIOInfo.md#6f52298a9c8f7f05e3ce4f73c048d7d7" class="el">ImageIOInfo::m_canwrite</a></td>
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
<td><p>Indicates if the plugin can write to file.</p>
<p>All plugins must have read from file capability but may not write to file.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00041" class="el">41</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="8b1a6e0a755e4a16633749f7df2ee8ee" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL <a href="classImageIOInfo.md#8b1a6e0a755e4a16633749f7df2ee8ee" class="el">ImageIOInfo::m_closewrite</a></td>
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
<td><p>Indicates if the plugin needs to close animation file after saving frames.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00046" class="el">46</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="42712fe7932262f9b0df441f5d17e6d3" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> <a href="classImageIOInfo.md#42712fe7932262f9b0df441f5d17e6d3" class="el">ImageIOInfo::m_documentation</a></td>
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
<td><p>Contains a HTML string describing the plugin and its usage.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00054" class="el">54</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="de812cb8066aad908294b43ef4b363df" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="DataType_8h.md#0edad1cd854da1f522d2a35119917e84" class="el">ULONG</a> <a href="classImageIOInfo.md#de812cb8066aad908294b43ef4b363df" class="el">ImageIOInfo::m_flags</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="ImageIO_8h-source.md#l00038" class="el">38</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>. |

<span id="ceccc3cba24a6c7656cd6663c29f2c44" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">BOOL <a href="classImageIOInfo.md#ceccc3cba24a6c7656cd6663c29f2c44" class="el">ImageIOInfo::m_haswriteoptions</a></td>
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
<td><p>Indicates if the plugin provides a callable Save Options dialog box.</p>
<p>Most common Save Options dialogs are compression settings. Other common Save Option woud be bit depth.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00042" class="el">42</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="69640451775f2eb11b013ad746f709ee" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> <a href="classImageIOInfo.md#69640451775f2eb11b013ad746f709ee" class="el">ImageIOInfo::m_localizedname</a></td>
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
<td><p>Contains the name of the supported file type as displayed in the Render Option drop down list.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00052" class="el">52</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="a77ed353b00a6194a70b9a82a50a9e7b" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> <a href="classImageIOInfo.md#a77ed353b00a6194a70b9a82a50a9e7b" class="el">ImageIOInfo::m_matchname</a></td>
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
<td><p>Contains a unique name used to identify the plugin.</p>
<p>This name is stored in the project files and must be unique among plugins and may not contain spaces</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00053" class="el">53</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="40d554da81c4bf4194c061422537fbcb" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> <a href="classImageIOInfo.md#40d554da81c4bf4194c061422537fbcb" class="el">ImageIOInfo::m_openfilter</a></td>
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
<td><p>Contains OpenFile dialog file filter.</p>
<p>The format is "|Display string|filter string|Macintosh filetype||"</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
since Mac OSX 10.4, the Macintosh filetype is no longer used and my be filled with any 4 characters if the plugin is to be used with A:M v13 and later.
</dd>
</dl>
<p>Definition at line <a href="ImageIO_8h-source.md#l00049" class="el">49</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="eadebac9ea35b95867e29bfeb93fbb71" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> <a href="classImageIOInfo.md#eadebac9ea35b95867e29bfeb93fbb71" class="el">ImageIOInfo::m_savefilter</a></td>
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
<td><p>Contains Save dialog file filter.</p>
<p>The format is "|Display string|filter string|Macintosh filetype||"</p>
<dl>
<dt><strong>Note:</strong></dt>
<dd>
since Mac OSX 10.4, the Macintosh filetype is no longer used and my be filled with any 4 characters if the plugin is to be used with A:M v13 and later.
</dd>
</dl>
<p>Definition at line <a href="ImageIO_8h-source.md#l00050" class="el">50</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

<span id="8bf6399ee82c377347b5f86e7063ced5" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classString.md" class="el">String</a> <a href="classImageIOInfo.md#8bf6399ee82c377347b5f86e7063ced5" class="el">ImageIOInfo::m_suffix</a></td>
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
<td><p>Contains the prefered or most common file extension.</p>
<p>Only one extension. Do not include the dot.</p>
<p>Definition at line <a href="ImageIO_8h-source.md#l00051" class="el">51</a> of file <a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

The documentation for this class was generated from the following files:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="ImageIO_8h-source.md" class="el">ImageIO.h</a>
- C:/Dox/SDK/Comments/<a href="ImageIO_8dox.md" class="el">ImageIO.dox</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:59 2005 with [<