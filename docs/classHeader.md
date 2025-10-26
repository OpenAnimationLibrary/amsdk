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

# Header Class Reference

`#include <`<a href="HashFile_8h-source.md" class="el"><code>HashFile.h</code></a>`>`

[List of all members.](classHeader-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classHeader.md#777f199c02d671d60e29181666913b75" class="el">Header</a> ()</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHeader.md#1e9a538b55239c160c7e173263b495a2" class="el">Header</a> (LONG <a href="classHeader.md#b80bb7740288fda1f201890375a60c8f" class="el">id</a>)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"> </td>
<td class="memItemRight" data-valign="bottom"><a href="classHeader.md#7e1e47cef747dbe40e11c0e9977e9284" class="el">Header</a> (LONG pid, const char *buffer)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">int </td>
<td class="memItemRight" data-valign="bottom"><a href="classHeader.md#c1a8934b07635d2b1a44825b566c2bac" class="el">operator==</a> (const <a href="classHeader.md" class="el">Header</a> &amp;header) const</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char * </td>
<td class="memItemRight" data-valign="bottom"><a href="classHeader.md#59cee462c5e06d883260d21037a3ebd7" class="el">GetText</a> ()</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">LONG </td>
<td class="memItemRight" data-valign="bottom"><a href="classHeader.md#b80bb7740288fda1f201890375a60c8f" class="el">id</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">char </td>
<td class="memItemRight" data-valign="bottom"><a href="classHeader.md#db24aa3dd51cdbac058c4ac7e2be395c" class="el">string</a> [80]</td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="HashFile_8h-source.md#l00085" class="el">85</a> of file <a href="HashFile_8h-source.md" class="el">HashFile.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="777f199c02d671d60e29181666913b75" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">Header::Header</td>
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

|  |  |
|----|----|
|   | Definition at line <a href="HashFile_8h-source.md#l00090" class="el">90</a> of file <a href="HashFile_8h-source.md" class="el">HashFile.h</a>. |

<span id="1e9a538b55239c160c7e173263b495a2" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">Header::Header</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">LONG </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>id</em></td>
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

<span id="7e1e47cef747dbe40e11c0e9977e9284" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">Header::Header</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">LONG </td>
<td class="mdname" data-nowrap=""><em>pid</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">const char * </td>
<td class="mdname" data-nowrap=""><em>buffer</em></td>
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

|  |  |
|----|----|
|   | Definition at line <a href="HashFile_8h-source.md#l00092" class="el">92</a> of file <a href="HashFile_8h-source.md" class="el">HashFile.h</a>. |

------------------------------------------------------------------------

## Member Function Documentation

<span id="59cee462c5e06d883260d21037a3ebd7" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char* Header::GetText</td>
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

|  |  |
|----|----|
|   | Definition at line <a href="HashFile_8h-source.md#l00098" class="el">98</a> of file <a href="HashFile_8h-source.md" class="el">HashFile.h</a>. |

<span id="c1a8934b07635d2b1a44825b566c2bac" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">int Header::operator==</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">const <a href="classHeader.md" class="el">Header</a> &amp; </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>header</em></td>
<td class="md" data-valign="top"> ) </td>
<td class="md" data-nowrap="">const<code> [inline]</code></td>
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
<td><p>Definition at line <a href="HashFile_8h-source.md#l00097" class="el">97</a> of file <a href="HashFile_8h-source.md" class="el">HashFile.h</a>.</p>
<p>References <a href="HashFile_8h-source.md#l00087" class="el">id</a>.</p></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

## Member Data Documentation

<span id="b80bb7740288fda1f201890375a60c8f" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">LONG <a href="classHeader.md#b80bb7740288fda1f201890375a60c8f" class="el">Header::id</a></td>
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
<td><p>Definition at line <a href="HashFile_8h-source.md#l00087" class="el">87</a> of file <a href="HashFile_8h-source.md" class="el">HashFile.h</a>.</p>
<p>Referenced by <a href="HashFile_8h-source.md#l00097" class="el">operator==()</a>.</p></td>
</tr>
</tbody>
</table>

<span id="db24aa3dd51cdbac058c4ac7e2be395c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">char <a href="classHeader.md#db24aa3dd51cdbac058c4ac7e2be395c" class="el">Header::string</a>[80]</td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="HashFile_8h-source.md#l00088" class="el">88</a> of file <a href="HashFile_8h-source.md" class="el">HashFile.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="HashFile_8h-source.md" class="el">HashFile.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:55 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
