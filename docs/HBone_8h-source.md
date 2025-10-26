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

# HBone.h

[Go to the documentation of this file.](HBone_8h.md)

<div class="fragment">

``` fragment
00001 // BC  12/1/2004  \BobL120\Include\SDK\HBone.h
00002 
00003 #define __HBONE_H
00004 
00005 #ifndef __HPROPERT_H
00006 #include "HPropert.h"
00007 #endif
00008 
00009 #ifndef _SMALLPDB
00010 
00011 enum  RollMethod { Z_SINGULARITY, Y_POLES_SINGULARITY, ROLL_HISTORY };
00012 
00013 //*********************************************************
00014 //** HBoneCache
00015 //*********************************************************
00016 class PLUGINEXPORT HBoneCache : public HHashObject
00017 {
00018 public:
00019 // Properties
00020    HTypeProperty   *GetRollMethod(); enum RollMethod { Z_SINGULARITY, Y_POLES_SINGULARITY, ROLL_HISTORY };
00021    HBoolProperty   *GetChained();
00022    HTypeProperty   *GetManipulationMethod(); enum { MANIP_STANDARD, MANIP_TRANSLATEONLY, MANIP_ROTATEONLY };
00023    //missing some
00024    HBoolCategoryProperty* GetLimitManipulators();
00025    HBoolProperty   *GetAllowXTranslate();
00026    HBoolProperty   *GetAllowYTranslate();
00027    HBoolProperty   *GetAllowZTranslate();
00028    HBoolProperty   *GetAllowXScale();
00029    HBoolProperty   *GetAllowYScale();
00030    HBoolProperty   *GetAllowZScale();
00031    HBoolProperty   *GetAllowXRotate();
00032    HBoolProperty   *GetAllowYRotate();
00033    HBoolProperty   *GetAllowZRotate();
00034    
00035    HBoolProperty   *GetStop();
00036    //new way
00037    HVectorProperty *GetPivot();
00038    HVectorProperty *GetEnd();
00039    HRotateProperty *GetRotate();//maybe needs a better name sets the angle of bone with no motion
00040    HFloatProperty  *GetLength();
00041    Vector           GetRollHandle(); // For 8.5 backward compatibility
00042    
00043    void SetBoneColor(ColorBuf &color);
00044    ColorBuf GetBoneColor();
00045 
00046    Vector *GetBounds();
00047          
00048 // Traversal
00049    HBoneCache *GetSiblingBoneCache();
00050    HBoneCache *GetChildBoneCache();
00051    HBoneCache *GetParentBoneCache();
00052 
00053 // Operations
00054    const Matrix34 &GetBoneToStandard();
00055 
00056    HBone *GetCurrentBone();  // returns the state variable containing the instance currently being drawn.
00057 };
00058 
00059 //*********************************************************
00060 //** HBoneCacheContainer
00061 //*********************************************************
00062 class PLUGINEXPORT HBoneCacheContainer : public HHashObject
00063 {
00064 public:
00065    static HBoneCacheContainer *New();
00066    HBoneCache *GetChildBoneCache();
00067 };
00068 
00069 //*********************************************************
00070 //** HBone
00071 //*********************************************************
00072 class PLUGINEXPORT HBone : public HHashObject
00073 {
00074 public:
00075 // Properties
00076    HTransformProperty *GetTransform();
00077    HTypeProperty  *GetRollMethod();
00078    HBoolProperty  *GetStop();
00079    HBoolProperty  *GetHidden();
00080    
00081    
00082 //Traversal
00083    HBone *GetSiblingBone();
00084    HBone *GetChildBone();
00085    HBone *GetParentBone();
00086    HBoneCache *GetBoneCache();
00087    
00088    Matrix34 GetLocalMatrix();
00089    Matrix34 GetGlobalMatrix();
00090    void GetLocalTSQ(Vector &translate, Vector &scale, Quaternion &quat);
00091    void GetLocalTSE(Vector &translate, Vector &scale, RotateEuler &re);
00092 
00093    void ComputeBoneDirections(Vector &bonedir, Vector &rolldir, Vector &parentbonedir, Vector &parentrolldir);
00094    const Matrix34 &GetStandardToAction();
00095 
00096    void SetLocalMatrix(Time time, const Matrix34 &matrix);
00097    void SetLocalTSQ(Time time, const Vector &translate, const Vector &scale, const Quaternion &quat);
00098    void SetLocalTSE(Time time, const Vector &translate, const Vector &scale, const RotateEuler &re);
00099    
00100    Vector *GetBounds(); //   Vector        bounds[8]; 
00101 
00102    const Matrix34 &GetBoneToStandardMatrix();
00103    const Matrix34 &GetStandardToBoneMatrix();
00104    const Matrix34 &GetModelToWorldMatrix();
00105    const Matrix34 &GetWorldToModelMatrix();
00106    const Matrix34 &GetModelToScreenMatrix();
00107    const Matrix34 &GetScreenToModelMatrix();
00108 };
00109 
00110 //*********************************************************
00111 //** HBoneContainer
00112 //*********************************************************
00113 class PLUGINEXPORT HBoneContainer : public HHashObject
00114 {
00115 public:
00116    HBone *GetChildBone();
00117 };
00118 
00119 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
