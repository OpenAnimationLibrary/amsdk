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

# HFX.h

[Go to the documentation of this file.](HFX_8h.md)

<div class="fragment">

``` fragment
00001 // KB  5/15/01  \Ken90\Include\SDK\HFX.h
00002 
00003 #define __HFX_H
00004 
00005 #ifndef __HOBJECT_H
00006 #include "HObject.h"
00007 #endif
00008 
00009 #ifndef _SMALLPDB
00010 
00011 //*********************************************************
00012 //** HFXCache
00013 //*********************************************************
00014 class PLUGINEXPORT HFXCache : public HObjectCache
00015 {
00016 public:
00017    enum { SPHERE, CONE, BOX, CYLINDER };
00018 
00019    HTypeProperty      *GetType();
00020    HFloatProperty     *GetWidth();
00021    HPercentProperty   *GetWidthSoftness();
00022    HFloatProperty     *GetFalloff();
00023    HPercentProperty   *GetFalloffSoftness();
00024    HFloatProperty     *GetConeAngle();
00025 };
00026 
00027 //*********************************************************
00028 //** HFX
00029 //*********************************************************
00030 class PLUGINEXPORT HFX : public HObject
00031 {
00032 public:
00033    HFloatProperty     *GetWidth();
00034    HPercentProperty   *GetWidthSoftness();
00035    HFloatProperty     *GetFalloff();
00036    HPercentProperty   *GetFalloffSoftness();
00037    HFloatProperty     *GetConeAngle();
00038 };
00039 
00040 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
