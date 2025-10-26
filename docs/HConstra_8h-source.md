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

# HConstra.h

[Go to the documentation of this file.](HConstra_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  6/16/2004  \DanLP115\Include\SDK\HConstra.h
00002 
00003 #define __HCONSTRA_H
00004 
00005 #ifndef __HPROPDRI_H
00006 #include "SDK/HPropDri.h"
00007 #endif
00008 
00009 class PLUGINEXPORT HConstraint : public HPropertyDriver
00010 {
00011 public:
00012    HPercentProperty *GetEnforcement();
00013    HBoolProperty *GetIsBeforeAction();
00014    HBoolProperty *GetLockOffsets();
00015    
00016    HPointerProperty *GetTarget1(); //for HOneTargetConstraints
00017    HPointerProperty *GetTarget2(); //for HTwoTargetConstraints
00018 };
00019 
00020 class PLUGINEXPORT HOneTargetConstraint : public HConstraint
00021 {
00022 public:
00023    HTimeProperty *GetLag();
00024    HPointerProperty *GetBone();
00025 };
00026 
00027 class PLUGINEXPORT HTwoTargetConstraint : public HOneTargetConstraint
00028 {
00029 public:
00030    HPointerProperty *GetBone2();
00031 };
00032 
00033 class PLUGINEXPORT HAimAtConstraint : public HOneTargetConstraint
00034 {
00035 public:
00036    static HAimAtConstraint *New();
00037    
00038    HBoolProperty      *GetScaleToReach();
00039    HBoolProperty      *GetScaleZOnly();
00040    HRotateProperty    *GetRotateOffset();
00041    HTranslateProperty *GetTranslateOffset();
00042 };
00043 
00044 class PLUGINEXPORT HKinematicConstraint : public HAimAtConstraint
00045 {
00046 public:
00047    static HKinematicConstraint *New();
00048 
00049    HBoolCategoryProperty  *GetSupportLimitsDamping();
00050    HBoolProperty          *GetComputeRoll();
00051    HBoolProperty          *GetStoreHints();
00052 };
00053 
00054 class PLUGINEXPORT HOrientLikeConstraint : public HOneTargetConstraint
00055 {
00056 public:
00057    static HOrientLikeConstraint *New();
00058 
00059    HBoolProperty *GetIsStoreRoll();
00060    HRotateProperty *GetRotateOffset();
00061 };
00062 
00063 class PLUGINEXPORT HTranslateToConstraint : public HOneTargetConstraint
00064 {
00065 public:
00066    static HTranslateToConstraint *New();
00067 
00068    HTranslateProperty *GetTranslateOffset();
00069 };
00070 
00071 class PLUGINEXPORT HEulerLimits : public HConstraint
00072 {
00073 public:
00074    static HEulerLimits *New();
00075 
00076    HVectorProperty *GetMinEuler();
00077    HVectorProperty *GetMaxEuler();
00078    HFloatProperty *GetIKDamping();
00079 };
00080 
00081 class PLUGINEXPORT HSphericalLimits : public HConstraint
00082 {
00083 public:
00084    static HSphericalLimits *New();
00085 
00086    HVectorProperty *GetMinSphere();
00087    HVectorProperty *GetMaxSphere();
00088    HFloatProperty *GetIKDamping();
00089 };
00090 
00091 class PLUGINEXPORT HTranslateLimits : public HConstraint
00092 {
00093 public:
00094    static HTranslateLimits *New();
00095 
00096    HTranslateProperty *GetMinTranslate();
00097    HTranslateProperty *GetMaxTranslate();
00098 };
00099 
00100 class PLUGINEXPORT HRollLikeConstraint : public HOneTargetConstraint
00101 {
00102 public:
00103    static HRollLikeConstraint *New();
00104 
00105    HFloatProperty *GetRollOffset();
00106    HFloatProperty *GetRollScale();
00107 };
00108 
00109 class PLUGINEXPORT HAimRollAtConstraint : public HOneTargetConstraint
00110 {
00111 public:
00112    static HAimRollAtConstraint *New();
00113 
00114    HTranslateProperty *GetTranslateOffset();
00115    HFloatProperty *GetRollOffset();
00116 };
00117 
00118 class PLUGINEXPORT HPathConstraint : public HConstraint
00119 {
00120 public:
00121    static HPathConstraint *New();
00122 
00123    HTimeProperty *GetLag();
00124    HPointerProperty *GetSplineInstance();// returns an HSplineInstance
00125    HBoolProperty *GetIsTranslateOnly();
00126    HBoolProperty *GetIsStoreRoll();
00127    HPercentProperty *GetEase();
00128    HTranslateProperty *GetTranslateOffset();
00129    HRotateProperty *GetRotateOffset();
00130 };
00131 
00132 class PLUGINEXPORT HScaleLikeConstraint : public HOneTargetConstraint
00133 {
00134 public:
00135    static HScaleLikeConstraint *New();
00136 
00137    HFloatProperty *GetScaleScale();
00138    HFloatProperty *GetScaleOffset();
00139 };
00140 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
