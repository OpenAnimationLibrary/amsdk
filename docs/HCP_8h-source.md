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

# HCP.h

[Go to the documentation of this file.](HCP_8h.md)

<div class="fragment">

``` fragment
00001 // BC  12/1/2004  \BobL120\Include\SDK\HCP.h
00002 
00003 #define __HCP_H
00004 
00005 #ifndef __HHASHOBJ_H
00006 #include "HHashObj.h"
00007 #endif
00008 
00009 #ifndef __CPINTERP_H
00010 #include "CPInterp.h"
00011 #endif
00012 
00013 #ifndef _SMALLPDB
00014 
00015 class HTranslatePropertyNoSubs;
00016 class HBiasProperty;
00017 class HCPInstance;
00018 class HSpline;
00019 class HGroupCP;
00020 class HDecalClip;
00021 class HSegmentCache;
00022 class HCPWeight;
00023 
00024 //*********************************************************
00025 //** HCP
00026 //*********************************************************
00027 class PLUGINEXPORT HCP : public HAnimObject
00028 {
00029 public:
00030    const Vector *GetPosition(); // Position of the CP, includes Muscle, and pose motion, but no Skeletal
00031    const Vector *GetModelPosition(); // Position of the CP with no motion, raw model data
00032    const Vector *GetWorldPosition(); // Position of the CP completely transformed
00033    const Vector *GetScreenPosition(); // Position of the CP completely transformed in world style coordinated, but facing the camera
00034    
00035    HCPInstance *GetCPInstance();
00036    HCPInstance *CreateCPInstance();// will return the instance if it already exists
00037    
00038    HSpline *GetSpline();
00039    HCP *GetNext();
00040    HCP *GetPrev();
00041    float GetInGamma();
00042    float GetInAlpha();
00043    float GetInMagnitude();
00044    float GetOutGamma() ;
00045    float GetOutAlpha() ;
00046    float GetOutMagnitude();
00047    Vector GetInTangent();
00048    Vector GetOutTangent();
00049    Vector GetModelInTangent();
00050    Vector GetModelOutTangent();
00051    Vector GetWorldInTangent();
00052    Vector GetWorldOutTangent();
00053    Vector GetScreenInTangent();
00054    Vector GetScreenOutTangent();
00055    HCP *GetNextAttached();
00056    HCP *GetPrevAttached();
00057    HCP *GetHead();
00058    HCPWeight *GetCPWeightHead(); //if walking through all cps should only be called when hcp == hcp->GetHead()
00059    BOOL AddToGroup( HGroupCP **gh);
00060    BOOL AddStackToGroup( HGroupCP **gh);
00061    void SetPosition( Vector *p ); // Sets the model position
00062    void SetInGamma(float fValue);
00063    void SetInAlpha(float fValue);
00064    void SetInMagnitude(float fValue);
00065    void SetOutGamma(float fValue);
00066    void SetOutAlpha(float fValue);
00067    void SetOutMagnitude(float fValue);
00068    void SetPeaked();
00069    void SetSmooth();
00070    void SetHide(BOOL bHide);
00071    void ComputeInBias(const Vector &goalit, float &alpha, float &gamma, float &magnitude);
00072    void ComputeOutBias(const Vector &goalot, float &alpha, float &gamma, float &magnitude);
00073    UINT GetID();
00074    HCPWeight *AddCPWeight(); //adds a new cpweight to the head cp
00075    void RemoveCPWeight(HCPWeight *hcpweight ); //frees handle
00076 // flags  
00077    BOOL IsLoop();
00078    BOOL IsPeaked();
00079    BOOL IsSmooth();
00080    BOOL IsHook();
00081    BOOL IsFlip();
00082    BOOL IsHide();
00083    BOOL IsGroup();
00084    BOOL IsLocked();
00085    BOOL IsEndHook();
00086    BOOL IsHookBase();
00087    HSegmentCache *GetSegmentCache();  // returns the primary owner of this control point
00088 };
00089 
00090 //*********************************************************
00091 //** HHookCP
00092 //*********************************************************
00093 class PLUGINEXPORT HHookCP : public HCP
00094 {
00095 public:
00096    float GetS();
00097 };
00098 
00099 //*********************************************************
00100 //** HCPShortcut
00101 //*********************************************************
00102 class PLUGINEXPORT HCPShortcut : public HAnimObjectShortcut
00103 {
00104 public:
00105    ULONG GetCPID();
00106    BOOL CanCompactForSaving();
00107 };
00108 
00109 //*********************************************************
00110 //** HCPInstance
00111 //*********************************************************
00112 class PLUGINEXPORT HCPInstance : public HAnimObject
00113 {
00114 public:
00115    HBiasProperty *GetInBias();
00116    HBiasProperty *GetOutBias();
00117    HTranslatePropertyNoSubs *GetPosition();
00118    
00119    HCP *GetCP();
00120 };
00121 
00122 //*********************************************************
00123 //** HGroupCP
00124 //*********************************************************
00125 class HCP;
00126 class PLUGINEXPORT HGroupCP : public HHashObject
00127 {
00128 public:
00129    HGroupCP *GetNext();
00130    HCP      *GetCP();
00131 // creation
00132    static HGroupCP *New();   
00133    void             Delete();
00134 };
00135 
00136 class HDecalClipContainer;
00137 class HAttrProperty;
00138 class HClip;
00139 class HPolyModifierShortcut;
00140 //*********************************************************
00141 //** HGroup
00142 //*********************************************************
00143 class PLUGINEXPORT HGroup : public HHashObject
00144 {
00145 public:
00146 // Properties
00147    HAttrProperty  *GetAttr();
00148 
00149    HGroupCP *GetGroupCP();
00150    Matrix34 *GetMatrix();
00151    BOOL      IsTempGroup();
00152    void      SetTempGroup(BOOL istemp);
00153    
00154    BOOL AddCP(HCP *cp);
00155    BOOL RemoveCP(HCP *cp);
00156    
00157    HDecalClipContainer *GetChildDecalClipContainer();
00158    BOOL IsPatchInGroup(HPatch *patch);
00159    BOOL IsCPInGroup(HCP *hcp);
00160    
00161    HDecalClip *CreateGroupDecal(HClip *clipcache=NULL);// Will prompt if NULL
00162    void RotateGroupImages();
00163    HPolyModifierShortcut *GetPolyModifierHead();
00164 };
00165 
00166 //*********************************************************
00167 //** HGroupContainer
00168 //*********************************************************
00169 class PLUGINEXPORT HGroupContainer : public HHashObject
00170 {
00171 public:
00172    HGroup *GetChildGroup();
00173 };
00174 
00175 //*********************************************************
00176 //** HChannelCP
00177 //*********************************************************
00178 class PLUGINEXPORT HChannelCP
00179 {
00180 public:
00181    void  operator delete( void *ptr ) { DeleteHandle( (HChannelCP *)ptr ); }
00182    static void DeleteHandle(HChannelCP *handle);
00183 
00184    CPInterpolationMethod GetInterpolationMethod();
00185    void SetInterpolationMethod(CPInterpolationMethod method);
00186    
00187 // Traversal
00188    HChannelCP *GetNext();
00189    
00190 // Operations
00191    float   GetInGamma();
00192    float   GetInMagnitude();
00193    float   GetOutGamma();
00194    float   GetOutMagnitude();
00195    void    SetInGamma(float fValue);
00196    void    SetInMagnitude(float fValue);
00197    void    SetOutGamma(float fValue);
00198    void    SetOutMagnitude(float fValue);
00199    void    SetBias(const Vector2 &goalit, const Vector2 &goalot);
00200    BOOL    IsPeaked();
00201    BOOL    IsSmooth();
00202    Time    GetTime();
00203    float   GetValue();
00204    Vector2 GetInTangent();
00205    Vector2 GetOutTangent();
00206    BOOL    IsLoop();
00207 };
00208 
00209 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
