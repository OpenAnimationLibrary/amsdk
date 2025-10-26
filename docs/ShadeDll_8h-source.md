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

# ShadeDll.h

[Go to the documentation of this file.](ShadeDll_8h.md)

<div class="fragment">

``` fragment
00001 // KB  8/27/2003  \Ken110\Include\ShadeDll.h
00002 
00003 #ifndef __SHADERDLL_H
00004 #define __SHADERDLL_H
00005 
00006 #include "DLLPlugi.h"
00007 
00008 #define SHADERDLLVERSION 1
00009 class HShading;
00010 
00011 class Shader : public DLLPlugin {
00012 public:
00013 
00014    Shader(HTreeObject *treeobject) : DLLPlugin(treeobject) {}
00015    virtual const char       *GetShaderDiffuseFilters() = 0;
00016    virtual const char       *GetShaderSpecularFilters() = 0;
00017   // RENDERING
00018    virtual void GetDiffuse( HShading *shading ) = 0;
00019    virtual BOOL GetSpecular( HShading *shading, const RGBFloat &lightcolor ) = 0;
00020 };
00021 
00022 class Shader2 : public Shader {
00023 public:
00024    Shader2(HTreeObject *treeobject) : Shader(treeobject) {}
00025    virtual const char       *GetShaderAmbianceFilters() = 0;
00026    virtual void GetAmbiance( HShading *shading ) = 0;
00027 };
00028 
00029 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
