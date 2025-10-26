<div class="tabs">

- [Main Page](index.md)
- <span id="current">[Classes](annotated.md)</span>
- [Files](files.md)
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [Class List](annotated.md)
- [Alphabetical List](classes.md)
- [Class Hierarchy](hierarchy.md)
- [Class Members](functions.md)

</div>

# ImageIO Class Reference

`#include <`<a href="ImageIO_8h-source.md" class="el"><code>ImageIO.h</code></a>`>`

Inheritance diagram for ImageIO:

<span class="image placeholder" original-image-src="classImageIO__inherit__graph.gif" original-image-title="" border="0" usemap="#ImageIO__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for ImageIO:

<span class="image placeholder" original-image-src="classImageIO__coll__graph.gif" original-image-title="" border="0" usemap="#ImageIO__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classImageIO-members.md)

<table data-border="0" data-cellpadding="0" data-cellspacing="0">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr>
<td></td>
<td></td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-member-functions">Public Member Functions</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#d1a0dccc92d93340c703e4165437b3aa" class="el">ImageIO</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#cc318a80070b22d3f1c1d4b84658d602" class="el">ImageIO</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *htreeobject)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#a0f84a5f45adce795e9e709f52b6d5cc" class="el">Write</a> (<a href="classHBitmapNode.md" class="el">HBitmapNode</a> *bn, <a href="classHOutputInfo.md" class="el">HOutputInfo</a> *outputinfoconst, const <a href="classString.md" class="el">String</a> &amp;filename, short *wavedata, BOOL hasaudio)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">void </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#6f27a575293bfb79e39aeecea8961d66" class="el">CloseWrite</a> (BOOL hasaudio)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#17f56a001b2653f1861b5630142b9bdb" class="el">CanLoadImage</a> (const <a href="classString.md" class="el">String</a> &amp;filename)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#55156800eca572758197fd7700077f8d" class="el">GetFilesStartEndFrame</a> (const <a href="classString.md" class="el">String</a> &amp;filename, int &amp;start, int &amp;end)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#c3cb38eb00c293dd5ea6727fdd14a47d" class="el">SetSaveOptions</a> (CWnd *parent, const <a href="classString.md" class="el">String</a> &amp;extension, float fps)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#651da01e2e4561e9f8a3b1e084f56c2f" class="el">GetImageIOInfo</a> (<a href="classImageIOInfo.md" class="el">ImageIOInfo</a> &amp;iioinfo)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#564e67564668f9f9eef3ec34dd73120d" class="el">OpenWriteFrame</a> (<a href="classString.md" class="el">String</a> filename, <a href="classHBitmapNode.md" class="el">HBitmapNode</a> *bn, <a href="classHOutputInfo.md" class="el">HOutputInfo</a> *outputinfo, BOOL hasaudio)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#1a5e64211835e97b625450f3b94ab38f" class="el">WriteFrame</a> (<a href="classHBitmapNode.md" class="el">HBitmapNode</a> *bn, <a href="classHOutputInfo.md" class="el">HOutputInfo</a> *outputinfo, const <a href="classString.md" class="el">String</a> &amp;filename, short *wavedata, BOOL hasaudio)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#3df7f33bf39d59d95b3c326e163fb34c" class="el">CloseWriteFrame</a> (BOOL hasaudio)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#bd81ab01c395d2e7451921c3c69eb7dd" class="el">LoadFrame</a> (<a href="classHBitmapNode.md" class="el">HBitmapNode</a> *bn, const <a href="classString.md" class="el">String</a> &amp;filename, int frame=-1, UINT <a href="Rave_8h.md#4e5868d676cb634aa75b125a0f741abf" class="el">flags</a>=0)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual int </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#b5e02f4aac715fe7eeed4d85e199127d" class="el">IsFileOpen</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">BOOL </td>
<td class="memItemRight" data-valign="bottom"><a href="classImageIO.md#5ff383d974993eb3eb84eb891dcaca18" class="el">m_isopened</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

