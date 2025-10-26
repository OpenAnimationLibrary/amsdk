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

# Volume.h

[Go to the documentation of this file.](Volume_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  11/27/2001  \Dan90\Include\Volume.h
00002 
00003 #define __VOLUME_H
00004 
00005 #ifndef __VOLBUF_H
00006 #include "VolBuf.h"
00007 #endif
00008 
00009 #include "DLLPlugi.h"
00010 
00011 #define VOLUMETRICDLLVERSION 2
00012 
00013 class Volumetric : public DLLPlugin {
00014 public:
00015    VolBuf m_volbuf;
00016 
00017    Volumetric() {}
00018    Volumetric(HTreeObject *treeobject) : DLLPlugin(treeobject) {}
00019 // RENDERING
00020    virtual float GetOpacity( float falloff ) = 0;
00021 };
00022 
00023 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
