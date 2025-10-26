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

# HPatch.h

[Go to the documentation of this file.](HPatch_8h.md)

<div class="fragment">

``` fragment
00001 // BC  12/20/2004  \BobL120\Include\SDK\HPatch.h
00002 
00003 #define __HPATCH_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 //*********************************************************
00008 //** HSpline
00009 //*********************************************************
00010 class HCP;
00011 
00012 class PLUGINEXPORT HSpline : public HAnimObject
00013 {
00014 public:
00015    HCP *GetHeadCP();
00016    HSpline *GetNextSpline();
00017    
00018    HCP *CreateCPAtHead(const Vector &p);
00019    HCP *CreateCPAtTail(const Vector &p);
00020    HCP *CreateCPBefore(HCP *beforecp, const Vector &p);
00021    HCP *CreateCPAfter(HCP *aftercp, const Vector &p);
00022    BOOL DeleteCP(HCP *cp);
00023    BOOL MakeLooped(BOOL looped);
00024 
00025    void  operator delete( void *ptr ) { DeleteHandle( (HSpline *)ptr ); }
00026    static void DeleteHandle(HSpline *handle);
00027 
00028    float GetLength();
00029    BOOL GetPositionAndDirection( float ease, Vector &position, Vector &direction );
00030 };
00031 
00032 //*********************************************************
00033 //** HSplineInstance
00034 //*********************************************************
00035 class PLUGINEXPORT HSplineInstance : public HAnimObject
00036 {
00037 public:
00038    HSpline *GetSpline();
00039 };
00040 
00041 //*********************************************************
00042 //** HSplineContainer
00043 //*********************************************************
00044 class PLUGINEXPORT HSplineContainer : public HHashObject
00045 {
00046 public:
00047    HSpline *GetChildSpline();
00048 };
00049 
00050 //*********************************************************
00051 //** HPatch
00052 //*********************************************************
00053 class PLUGINEXPORT HPatch
00054 {
00055 public:
00056    void  operator delete( void *ptr ) { DeleteHandle( (HPatch *)ptr ); }
00057    static void DeleteHandle(HPatch *handle);
00058 
00059    HCP *GetCP1();
00060    HCP *GetCP2();
00061    HCP *GetCP3();
00062    HCP *GetCP4();
00063    
00064    Vector &GetIT1();
00065    Vector &GetOT1();
00066    Vector &GetIT2();
00067    Vector &GetOT2();
00068    Vector &GetIT3();
00069    Vector &GetOT3();
00070    Vector &GetIT4();
00071    Vector &GetOT4();
00072    
00073 // flags
00074    BOOL IsFlipV1();
00075    BOOL IsFlipV2();
00076    BOOL IsFlipV3();
00077    BOOL IsFlipV4();
00078    BOOL IsHook1();
00079    BOOL IsHook2();
00080    BOOL IsHook3();
00081    BOOL IsHook4();
00082    BOOL IsUseHook1();
00083    BOOL IsUseHook2();
00084    BOOL IsUseHook3();
00085    BOOL IsUseHook4();
00086    BOOL IsEndHook1();
00087    BOOL IsEndHook2();
00088    BOOL IsEndHook3();
00089    BOOL IsEndHook4();
00090    BOOL IsHookData1();
00091    BOOL IsHookData2();
00092    BOOL IsHookData3();
00093    BOOL IsHookData4();
00094    
00095    int GetGroupImageRotation();
00096    PatchID GetPatchID();
00097    HAttrProperty *GetCompositedAttr();
00098    HAttrProperty *GetAttr();
00099    int GetNumPoints();
00100    void GetPatchPoints(Vector *p); // 12 points if 4 point patch,  15 points if 5 point patch
00101    void ReverseNormal();
00102    Vector GetPointOnPatch( float s, float t );
00103    Vector GetPointNormalOnPatch( float s, float t, Vector &normal );
00104 };
00105 
00106 //*********************************************************
00107 //** HPatch5
00108 //*********************************************************
00109 class PLUGINEXPORT HPatch5 : public HPatch
00110 {
00111 public:
00112    HPatch5 *GetNextPatch5();
00113    HCP *GetCP5();
00114    Vector &GetIT5();
00115    Vector &GetOT5();
00116    PatchID5 GetPatchID();
00117    BOOL IsFlipV5();
00118 };
00119 
00120 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
