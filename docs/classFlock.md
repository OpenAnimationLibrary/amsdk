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

# Flock Class Reference

`#include <`<a href="flockdll_8h-source.md" class="el"><code>flockdll.h</code></a>`>`

Inheritance diagram for Flock:

<span class="image placeholder" original-image-src="classFlock__inherit__graph.gif" original-image-title="" border="0" usemap="#Flock__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for Flock:

<span class="image placeholder" original-image-src="classFlock__coll__graph.gif" original-image-title="" border="0" usemap="#Flock__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classFlock-members.md)

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
<td class="memItemRight" data-valign="bottom"><a href="classFlock.md#ed5c4b65746bf4afc8e378a7c91a1bca" class="el">Flock</a> (<a href="classHTreeObject.md" class="el">HTreeObject</a> *htreeobject)</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlock.md#869ee02436aa026cfcdb35afba4930e9" class="el">InitParticlePos</a> (int id, <a href="classTSQ.md" class="el">TSQ</a> &amp;tsq, <a href="classTime.md" class="el">Time</a> &amp;actionoffset)=0</td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top">virtual void </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlock.md#5afcb70464093b0e23001c84c042961c" class="el">UpdateParticlePos</a> (int id, <a href="classTSQ.md" class="el">TSQ</a> &amp;tsq, <a href="classVector.md" class="el">Vector</a> &amp;d, float frametime)=0</td>
</tr>
<tr>
<td colspan="2"><br />
&#10;<h2 id="public-attributes">Public Attributes</h2></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classFlockBuf.md" class="el">FlockBuf</a> </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlock.md#d6b7f69b704f962a7acf071386e96cad" class="el">m_flockbuf</a></td>
</tr>
<tr>
<td class="memItemLeft" style="text-align: right;" data-nowrap="" data-valign="top"><a href="classFlock.md" class="el">Flock</a> * </td>
<td class="memItemRight" data-valign="bottom"><a href="classFlock.md#38aa181256d0cbe8644426c655cfe693" class="el">m_nextflock</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

Definition at line <a href="flockdll_8h-source.md#l00022" class="el">22</a> of file <a href="flockdll_8h-source.md" class="el">flockdll.h</a>.

------------------------------------------------------------------------

## Constructor & Destructor Documentation

<span id="ed5c4b65746bf4afc8e378a7c91a1bca" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">Flock::Flock</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top"><a href="classHTreeObject.md" class="el">HTreeObject</a> * </td>
<td class="mdname1" data-valign="top" data-nowrap=""><em>htreeobject</em></td>
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
|   | Definition at line <a href="flockdll_8h-source.md#l00028" class="el">28</a> of file <a href="flockdll_8h-source.md" class="el">flockdll.h</a>. |

------------------------------------------------------------------------

## Member Function Documentation

<span id="869ee02436aa026cfcdb35afba4930e9" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void Flock::InitParticlePos</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname" data-nowrap=""><em>id</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classTSQ.md" class="el">TSQ</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>tsq</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classTime.md" class="el">Time</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>actionoffset</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

<span id="5afcb70464093b0e23001c84c042961c" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top">virtual void Flock::UpdateParticlePos</td>
<td class="md" data-valign="top">( </td>
<td class="md" data-nowrap="" data-valign="top">int </td>
<td class="mdname" data-nowrap=""><em>id</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classTSQ.md" class="el">TSQ</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>tsq</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap=""><a href="classVector.md" class="el">Vector</a> &amp; </td>
<td class="mdname" data-nowrap=""><em>d</em>,</td>
</tr>
<tr>
<td class="md" style="text-align: right;" data-nowrap=""></td>
<td class="md"></td>
<td class="md" data-nowrap="">float </td>
<td class="mdname" data-nowrap=""><em>frametime</em></td>
</tr>
<tr>
<td class="md"></td>
<td class="md">) </td>
<td colspan="2" class="md"><code> [pure virtual]</code></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|     |     |
|-----|-----|
|     |     |

------------------------------------------------------------------------

## Member Data Documentation

<span id="d6b7f69b704f962a7acf071386e96cad" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classFlockBuf.md" class="el">FlockBuf</a> <a href="classFlock.md#d6b7f69b704f962a7acf071386e96cad" class="el">Flock::m_flockbuf</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="flockdll_8h-source.md#l00025" class="el">25</a> of file <a href="flockdll_8h-source.md" class="el">flockdll.h</a>. |

<span id="38aa181256d0cbe8644426c655cfe693" class="anchor"></span>

<table class="mdTable" data-cellpadding="2" data-cellspacing="0">
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr>
<td class="mdRow"><table data-cellpadding="0" data-cellspacing="0" data-border="0">
<tbody>
<tr>
<td class="md" data-nowrap="" data-valign="top"><a href="classFlock.md" class="el">Flock</a>* <a href="classFlock.md#38aa181256d0cbe8644426c655cfe693" class="el">Flock::m_nextflock</a></td>
</tr>
</tbody>
</table></td>
</tr>
</tbody>
</table>

|  |  |
|----|----|
|   | Definition at line <a href="flockdll_8h-source.md#l00026" class="el">26</a> of file <a href="flockdll_8h-source.md" class="el">flockdll.h</a>. |

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/<a href="flockdll_8h-source.md" class="el">flockdll.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:51 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
