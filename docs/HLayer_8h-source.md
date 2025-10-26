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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2FSDK_2F.md" class="el">SDK</a>

</div>

# HLayer.h

[Go to the documentation of this file.](HLayer_8h.md)

<div class="fragment">

``` fragment
00001 // KB  5/15/01  \Ken90\Include\SDK\HLayer.h
00002 
00003 #define __HLAYER_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HMODEL_H
00008 #include "HModel.h"
00009 #endif
00010 
00011 
00012 //*********************************************************
00013 //** HLayerCache
00014 //*********************************************************
00015 class PLUGINEXPORT HLayerCache : public HModelCache
00016 {
00017 public:
00018 // Properties
00019 };
00020 
00021 //*********************************************************
00022 //** HLayer
00023 //*********************************************************
00024 class PLUGINEXPORT HLayer : public HModel
00025 {
00026 public:
00027 // Properties
00028 };
00029 
00030 
00031 /*
00032   TODO
00033     Clip stuff
00034 */
00035 
00036 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
