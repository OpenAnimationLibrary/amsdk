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

# HObjectCache Class Reference

An object cache contains the actual common information about an object. [More...](#_details)

`#include <`<a href="HObject_8h-source.md" class="el"><code>HObject.h</code></a>`>`

Inheritance diagram for HObjectCache:

<span class="image placeholder" original-image-src="classHObjectCache__inherit__graph.gif" original-image-title="" border="0" usemap="#HObjectCache__inherit__map">Inheritance graph</span>

\[[legend](graph_legend.md)\]

Collaboration diagram for HObjectCache:

<span class="image placeholder" original-image-src="classHObjectCache__coll__graph.gif" original-image-title="" border="0" usemap="#HObjectCache__coll__map">Collaboration graph</span>

\[[legend](graph_legend.md)\]

[List of all members.](classHObjectCache-members.md)

|     |
|-----|
|     |

------------------------------------------------------------------------

<span id="_details"></span>

## Detailed Description

An object cache contains the actual common information about an object.

A:M differenciates between an object that you find in the Objects folder in the PWS and rerefences to the object that you find in Actions or Choreographies folders of the PWS for example and named "Shortcut to ...". The actual object found in the Objects folder of the PWS is a HObjectCache or a cache for short.

So the HObjectCache or any derived classes contain the original definition and attributes of an object. It acts as a reference definition from which any later modifications (like for an Action) are based. Every HObjectCache have an internal list of every checked out <a href="classHObject.md" class="el">HObject</a> currently instanciated in a project.

Less obvious is the fact that when an object is displayed in a view to allow the user to edit it, an <a href="classHObject.md" class="el">HObject</a> is created from the HObjectCache and the <a href="classHObject.md" class="el">HObject</a> is the one displayed.

**See also:**  
<a href="classHObject.md" class="el">HObject</a> for a description of its use and its relation to an HObjectCache.

Definition at line <a href="HObject_8h-source.md#l00019" class="el">19</a> of file <a href="HObject_8h-source.md" class="el">HObject.h</a>.

------------------------------------------------------------------------

The documentation for this class was generated from the following file:

- C:/Program Files/Hash Inc/AM120SDK/Include/SDK/<a href="HObject_8h-source.md" class="el">HObject.h</a>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:56 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
