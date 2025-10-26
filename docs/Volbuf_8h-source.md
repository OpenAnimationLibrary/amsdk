<div class="tabs">

- [Main Page](index.md)
- [Classes](annotated.md)
- <span id="current">[Files](files.md)</span>
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [File List](files.md)
- [File Members](globals.md)

</div>

<div class="nav">

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# Volbuf.h

[Go to the documentation of this file.](Volbuf_8h.md)

<div class="fragment">

``` fragment
00001 // MH  16 Jul 1998
00002 
00003 #define __VOLBUF_H
00004 
00005 #ifndef __EXPORTS_H
00006 #include "Exports.h"
00007 #endif
00008 #ifndef __VECTOR_H
00009 #include "Vector.h"
00010 #endif
00011 
00012 class TurbulenceNode;
00013 class InfluenceShape;
00014 class VolBuf {
00015 public:
00016    Vector          p, worldp;
00017    TurbulenceNode  *turbnodehead;
00018    InfluenceShape  *influenceshape;
00019 
00020    VolBuf() { turbnodehead = NULL; influenceshape = NULL; }
00021 
00022    VolBuf &operator = ( const VolBuf &other ) {
00023 //      don't allow volbuf members to be copied.
00024       return *this;
00025    }
00026 
00027    PLUGINEXPORT float GetTurbulenceValue(const Vector &turbp);
00028    PLUGINEXPORT float GetFallOffValue(const Vector &p);
00029 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
