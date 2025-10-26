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

# HMaterial.h

[Go to the documentation of this file.](HMaterial_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  12/11/2002  \Dan100\Include\SDK\HMaterial.h
00002 
00003 #define __HMATERIAL_H
00004 
00005 #ifndef __HHASHOBJ_H
00006 #include "HHashObj.h"
00007 #endif
00008 
00009 class Texture;
00010 
00011 //*********************************************************
00012 //** HMaterialCache
00013 //*********************************************************
00014 class PLUGINEXPORT HMaterialCache : public HHashObject
00015 {
00016 public:
00017    HFileInfoProperty *GetFileInfo();
00018    HTransformProperty *GetTransform();
00019    HFloatProperty *GetBumpPercent();
00020    HFloatProperty *GetDisplacePercent();
00021    HBoolProperty *GetIsGlobalAxis();
00022 };
00023 
00024 //*********************************************************
00025 //** HMaterial
00026 //*********************************************************
00027 class PLUGINEXPORT HMaterial : public HHashObject
00028 {
00029 public:
00030    HTransformProperty *GetTransform();
00031    HFloatProperty *GetBumpPercent();
00032    HFloatProperty *GetDisplacePercent();
00033    HBoolProperty *GetIsGlobalAxis();
00034 };
00035 
00036 //*********************************************************
00037 //** HMaterialNode
00038 //*********************************************************
00039 class PLUGINEXPORT HMaterialNode : public HHashObject
00040 {
00041 public:
00042    char *GetClassName();
00043 };
00044 
00045 //*********************************************************
00046 //** HTextureNode
00047 //*********************************************************
00048 class PLUGINEXPORT HTextureNode : public HMaterialNode
00049 {
00050 public:
00051    Texture *GetTexture();
00052 };
00053 
00054 //*********************************************************
00055 //** HGradientNode
00056 //*********************************************************
00057 class PLUGINEXPORT HGradientNode : public HMaterialNode
00058 {
00059 public:
00060    HTranslateProperty *GetStart();
00061    HTranslateProperty *GetEnd();
00062    HFloatProperty *GetEdgeThreshold();
00063 };
00064 
00065 //*********************************************************
00066 //** HSphericalNode
00067 //*********************************************************
00068 class PLUGINEXPORT HSphericalNode : public HMaterialNode
00069 {
00070 public:
00071    HTranslateProperty *GetTranslate();
00072    HScaleProperty     *GetScale();
00073    HPercentProperty   *GetBlur();
00074    HFloatProperty     *GetRing1Size();
00075    HFloatProperty     *GetRing2Size();
00076 };
00077 
00078 //*********************************************************
00079 //** HCheckerNode
00080 //*********************************************************
00081 class PLUGINEXPORT HCheckerNode : public HMaterialNode
00082 {
00083 public:
00084    HTranslateProperty *GetTranslate();
00085    HScaleProperty     *GetScale();
00086    HPercentProperty   *GetBlur();
00087 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
