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

# HLight.h

[Go to the documentation of this file.](HLight_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  12/9/2002  \Dan100\Include\SDK\HLight.h
00002 
00003 #define __HLIGHT_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HVOLFX_H
00008 #include "HVolFX.h"
00009 #endif
00010 
00011 class HLight;
00012 class HLightCache;
00013 //*********************************************************
00014 //** HLightListNode
00015 //*********************************************************
00016 class PLUGINEXPORT HLightListNode : public HHashObject
00017 {
00018 public:
00019    HLight *GetLight();
00020    HLightListNode *GetNextLightListNode();
00021 };
00022 
00023 //*********************************************************
00024 //** HLightCacheContainer
00025 //*********************************************************
00026 class PLUGINEXPORT HLightCacheContainer : public HHashObject
00027 {
00028 public:
00029    HLightCache *GetChildLightCache();
00030 };
00031 
00032 //*********************************************************
00033 //** HLightCache
00034 //*********************************************************
00035 class PLUGINEXPORT HLightCache : public HVolFXCache
00036 {
00037 public:
00038    HFloatProperty *GetIntensity();
00039    HBoolProperty *GetDiffuse();
00040    HBoolProperty *GetSpecular();
00041    HBoolCategoryProperty *GetVolumetric();
00042    HBoolCategoryProperty *GetCastShadows();
00043    HTypeProperty *GetShadowType(); enum { RAYTRACED, ZBUFFERED };
00044    HIntProperty *GetShadowRaysCast();
00045    HFloatProperty *GetShadowRayBias();
00046    HFloatProperty *GetShadowMapSoftness();
00047    HFloatProperty *GetShadowMapDarkness();
00048    HColorProperty *GetShadowMapTint();
00049    HTypeProperty *GetShadowMapRes(); enum {SM_256, SM_512, SM_1024, SM_2048 };
00050    HFloatProperty *GetShadowMapBias();
00051 //   HLensFlareProperty *GetLensFlare();
00052    HFileInfoProperty *GetFileInfo();
00053 };
00054 
00055 //*********************************************************
00056 //** HLightContainer
00057 //*********************************************************
00058 class PLUGINEXPORT HLightContainer : public HHashObject
00059 {
00060 public:
00061    HLight *GetChildLight();
00062 };
00063 
00064 //*********************************************************
00065 //** HLight
00066 //*********************************************************
00067 class PLUGINEXPORT HLight : public HVolFX
00068 {
00069 public:
00070    HFloatProperty *GetIntensity();
00071    HBoolProperty *GetDiffuse();
00072    HBoolProperty *GetSpecular();
00073    HBoolCategoryProperty *GetVolumetric();
00074    HBoolCategoryProperty *GetCastShadows();
00075    HIntProperty *GetShadowRaysCast();
00076    HFloatProperty *GetShadowRayBias();
00077    HFloatProperty *GetShadowMapSoftness();
00078    HFloatProperty *GetShadowMapDarkness();
00079    HColorProperty *GetShadowMapTint();
00080    HTypeProperty *GetShadowMapRes();
00081    HFloatProperty *GetShadowMapBias();
00082 //   HLensFlareProperty *GetLensFlare();
00083    HBoolProperty *GetLightAll();
00084    
00085    HLight *GetNextLightInChor();// use with HChor::GetChildLight()
00086 };
00087 
00088 
00089 /*
00090 TODO
00091    Rotoscope
00092    Material
00093    Lensflare
00094 */   
00095 
00096 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
