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

# HVolFX.h

[Go to the documentation of this file.](HVolFX_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  12/10/2002  \Dan100\Include\SDK\HVolFX.h
00002 
00003 #define __HVolFX_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HFX_H
00008 #include "HFX.h"
00009 #endif
00010 
00011 //*********************************************************
00012 //** HVolFXCache
00013 //*********************************************************
00014 class PLUGINEXPORT HVolFXCache : public HFXCache
00015 {
00016 public:
00017    HColorProperty     *GetColor();
00018    HFloatProperty     *GetQuality();
00019    HFloatProperty     *GetBrightness();
00020    HFloatProperty     *GetContrast();
00021 };
00022 
00023 //*********************************************************
00024 //** HVolFX
00025 //*********************************************************
00026 class PLUGINEXPORT HVolFX : public HFX
00027 {
00028 public:
00029    HColorProperty     *GetColor();
00030    HFloatProperty     *GetQuality();
00031    HFloatProperty     *GetBrightness();
00032    HFloatProperty     *GetContrast();
00033 };
00034 
00035 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
