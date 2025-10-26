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

# HDecal.h

[Go to the documentation of this file.](HDecal_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  4/5/2004  \DanLP110\Include\SDK\HDecal.h
00002 
00003 #define __HDECAL_H
00004 
00005 #ifndef __HPROPERT_H
00006 #include "HPropert.h"
00007 #endif
00008 #ifndef __HIMAGE_H
00009 #include "HImage.h"
00010 #endif
00011 
00012 //*********************************************************
00013 //** HBitmap
00014 //*********************************************************
00015 class PLUGINEXPORT HBitmap : public HClip
00016 {
00017 public:
00018 };
00019 
00020 //*********************************************************
00021 //** HDecalClip
00022 //*********************************************************
00023 class PLUGINEXPORT HDecalClip : public HHashObject
00024 {
00025 public:
00026    enum { OPAQUEMAP,     TRANSPARENCYMAP,  BUMPMAP,     SPECULARSIZEMAP, SPECULARINTENSITYMAP,
00027           DIFFUSEMAP,    MIRRORMAP,        AMBIANCEMAP, COOKIECUTMAP,    DISPLACEMENTMAP,
00028           FRACTALMAP,    NEXTMAPFACTORMAP, OTHERMAP,    NORMALMAP,       /*TANGENTMAP,*/
00029           REFLECTIONMAP, WEATHERMAP };
00030    enum { REFERENCEORIGINAL, INCLUDEINPATCHMAPS };
00031 
00032    HClipProperty *GetClip();
00033    HTypeProperty *GetKind();
00034    HFloatProperty *GetPercent();
00035    HVector2Property *GetRepeat(); // old for backward compatibility, get this value out of the HClipProperty now.
00036    HBoolProperty *GetSeamless(); // old for backward compatibility, get this value out of the HClipProperty now.
00037    HTypeProperty *GetExportType();
00038    HTimeProperty *GetTime(); // old for backward compatibility, get this value out of the HClipProperty now.
00039 };
00040 
00041 //*********************************************************
00042 //** HDecalClipContainer
00043 //*********************************************************
00044 class PLUGINEXPORT HDecalClipContainer : public HHashObject
00045 {
00046 public:
00047    HDecalClip *GetChildDecalClip();
00048 };
00049 
00050 //*********************************************************
00051 //** HBasePatchUV
00052 //*********************************************************
00053 class PLUGINEXPORT HBasePatchUV : public HAnimObject
00054 {
00055 public:
00056    HPatch *GetPatch();
00057    BOOL IsPatch5UV();
00058 
00059    void SetUVs(Vector2 uvs[]);
00060    void GetUVs(Vector2 uvs[]);
00061 };
00062 
00063 //*********************************************************
00064 //** HPatchUV
00065 //*********************************************************
00066 class PLUGINEXPORT HPatchUV : public HBasePatchUV
00067 {
00068 public:
00069 };
00070 
00071 //*********************************************************
00072 //** HPatch5UV
00073 //*********************************************************
00074 class PLUGINEXPORT HPatch5UV : public HBasePatchUV
00075 {
00076 public:
00077 };
00078 
00079 //*********************************************************
00080 //** HDecalStamp
00081 //*********************************************************
00082 class PLUGINEXPORT HDecalStamp : public HHashObject
00083 {
00084 public:
00085 /*
00086  4 point       5 point
00087  
00088  0 1 2 3          00  
00089 11     4        14  01    
00090 10     5      13      02  
00091  9 8 7 6    12          03
00092             11          04
00093             10          05
00094             09  08  07  06
00095 */ 
00096 // OLD, use below
00097    HBasePatchUV *AddPatchUV(HPatch *hpatch, Vector2 uvs[]); // 12 uv's for HPatch, 15 uv's for HPatch5
00098    
00099 // New   
00100    HBasePatchUV *AddPatchUV(HPatch *hpatch, Vector uvs[]); // 12 uv's for HPatch, 15 uv's for HPatch5
00101 
00102    HBasePatchUV *GetFirstPatchUV();
00103    HBasePatchUV *GetNextPatchUV(HBasePatchUV *patchuv);
00104 };
00105 
00106 //*********************************************************
00107 //** HDecalStampContainer
00108 //*********************************************************
00109 class PLUGINEXPORT HDecalStampContainer : public HHashObject
00110 {
00111 public:
00112    HDecalStamp *GetChildDecalStamp();
00113 };
00114 
00115 class HDecalContainer;
00116 //*********************************************************
00117 //** HDecal
00118 //*********************************************************
00119 class PLUGINEXPORT HDecal : public HBitmap
00120 {
00121 public:
00122    HDecalClip *AddDecalClip(HClip *clipcache=NULL);
00123    HDecalStamp *AddDecalStamp();
00124    
00125 // Traversal
00126    HDecalClipContainer *GetChildDecalClipContainer();
00127    HDecalStampContainer *GetChildDecalStampContainer();
00128 };
00129 
00130 //*********************************************************
00131 //** HDecalContainer
00132 //*********************************************************
00133 class PLUGINEXPORT HDecalContainer : public HHashObject
00134 {
00135 public:
00136    HDecal *GetChildDecal();
00137 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
