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

# HPropDri.h

[Go to the documentation of this file.](HPropDri_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  8/4/2004  \DanLP110\Include\SDK\HPropDri.h
00002 
00003 #define __HPROPDRI_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HHASHOBJ_H
00008 #include "HHashObj.h"
00009 #endif
00010 
00011 #ifndef __HCP_H
00012 #include "SDK/HCP.h"
00013 #endif
00014 
00015 #ifndef __TIMERANG_H
00016 #include "TimeRang.h"
00017 #endif
00018 
00019 class HAction;
00020 class HActionCache;
00021 class HDriverShortcut;
00022 class HConstraint;
00023 
00024 //*********************************************************
00025 //** HPropertyDriver
00026 //*********************************************************
00027 class PLUGINEXPORT HPropertyDriver : public HHashObject
00028 {
00029 public:
00030    HProperty *GetProperty();
00031    
00032    // A Property can have multiple list of Drivers on them coming from different relationships, Actions, or choractions.
00033    // Use GetNextActionDriver to get a HeadDriver of a property to get to the next header driver of a different
00034    // Action applied to the property.
00035    HPropertyDriver *GetNextActionDriver();
00036 
00037    // Use GetNextDriver to walk through all the drivers for all action applied to
00038    // the property.
00039    HPropertyDriver *GetNextDriver();
00040    
00041    // GetNextDriverForAction will simply walk all driver applied to the property for
00042    // the one action
00043    HPropertyDriver *GetNextDriverForAction(); 
00044    
00045    // Action this driver came from
00046    HAction *GetAction();
00047 
00048    HPropertyDriver *GetDriver(); // Gets the actual driver is this is actually a drivershortcut
00049    
00050    BOOL IsSimpleDriverShortcut();
00051    void SetProperty(HProperty *);
00052    HDriverShortcut *NewShortcut(HActionCache *);
00053    int GetNumSubDrivers(); // This is used for Properties like TranslateDriversNoSubs, and BiasDrivers
00054    HPropertyDriver *GetSubDriverAt( int i ); //This is used for Properties like TranslateDriversNoSubs, and BiasDrivers
00055 
00056    HProperty *FindPropertyFromDriver(BOOL cacheok=FALSE);
00057    
00058    HPropertyDriver *MakeCopy();
00059    void Copy(HPropertyDriver *other);
00060    void CopyKeys(HPropertyDriver *other, HAction *action=NULL);
00061    
00062    HConstraint *IsConstraint();
00063    BOOL IsStorageDriver();
00064    
00065    BOOL AddSelfAppliedDrivers();
00066 };
00067 
00068 //*********************************************************
00069 //** HDriverShortcut
00070 //*********************************************************
00071 class PLUGINEXPORT HDriverShortcut : public HPropertyDriver
00072 {
00073 public:
00074    HPropertyDriver *GetDriver();
00075    HActionCache *GetActionCache();
00076 };
00077 
00078 //*********************************************************
00079 //** HRotateDriverShortcut
00080 //*********************************************************
00081 class PLUGINEXPORT HRotateDriverShortcut : public HDriverShortcut
00082 {
00083 public:
00084    
00085    Quaternion GetParentCompensation();
00086    void SetParentCompensation(Quaternion &quat);
00087    
00088    BOOL HasParentCompensation();
00089    void SetParentCompensation(BOOL state);
00090 };
00091 
00092 //*********************************************************
00093 //** HAttrDriver
00094 //*********************************************************
00095 class PLUGINEXPORT HAttrDriver : public HPropertyDriver
00096 {
00097 public:
00098    static HAttrDriver *New(HProperty *parent);
00099 };
00100 
00101 //*********************************************************
00102 //** HBiasDriver
00103 //*********************************************************
00104 class PLUGINEXPORT HBiasDriver : public HPropertyDriver
00105 {
00106 public:
00107 };
00108 
00109 //*********************************************************
00110 //** HConstDriver
00111 //*********************************************************
00112 class PLUGINEXPORT HConstDriver : public HPropertyDriver
00113 {
00114 public:
00115    static HConstDriver *New(HProperty *parent);
00116    HProperty* GetValue();
00117 };
00118 
00119 //*********************************************************
00120 //** HPropertyShortcut
00121 //*********************************************************
00122 class PLUGINEXPORT HPropertyShortcut : public HPropertyDriver
00123 {
00124 public:
00125    static HPropertyShortcut *New(HProperty *parent);
00126 };
00127 
00128 //*********************************************************
00129 //** HFloatDriver
00130 //*********************************************************
00131 class PLUGINEXPORT HFloatDriver : public HPropertyDriver
00132 {
00133 public:
00134   float GetValue( Time time, TimeRange &validrange );
00135   float GetValue( Time time );
00136   void StoreValue( Time time, float value, BOOL storeundo = TRUE );
00137 };
00138 
00139 //*********************************************************
00140 //** HChannelDriver
00141 //*********************************************************
00142 class PLUGINEXPORT HChannelDriver : public HFloatDriver
00143 {
00144 public:
00145    static HChannelDriver *New(HProperty *parent);
00146 
00147    CPInterpolationMethod GetInterpolationMethod() const;
00148    void SetInterpolationMethod(CPInterpolationMethod);
00149    
00150    ExtrapolationMethod GetPreExtrapolationMethod() const;
00151    void SetPreExtrapolationMethod(ExtrapolationMethod);
00152    
00153    ExtrapolationMethod GetPostExtrapolationMethod() const;
00154    void SetPostExtrapolationMethod(ExtrapolationMethod);
00155    
00156    HChannelCP *GetHeadCP();
00157    HChannelCP *GetTailCP();
00158    HChannelCP *GetCPFromTime( Time time );
00159    
00160    float GetValue( Time time, TimeRange *validrange=NULL );
00161 };
00162 
00163 //*********************************************************
00164 //** HTimeBasedKey
00165 //*********************************************************
00166 class HTimeProperty;
00167 class PLUGINEXPORT HTimeBasedKey : public HConstDriver
00168 {
00169 public:
00170    HTimeProperty *GetTime();
00171    HTimeBasedKey *GetNextKey();
00172    HTimeBasedKey *GetPrevKey();
00173 };
00174 
00175 //*********************************************************
00176 //** HTimeBasedDriver
00177 //*********************************************************
00178 class PLUGINEXPORT HTimeBasedDriver : public HPropertyDriver
00179 {
00180 public:
00181    HTimeBasedKey *GetFirstKeyObject();
00182    HTimeBasedKey *GetLastKeyObject();
00183    HTimeBasedKey *GetKeyFromTime(Time time);
00184 };
00185 
00186 //*********************************************************
00187 //** HRelationMDShortcut
00188 //*********************************************************
00189 class PLUGINEXPORT HRelationMDShortcut : public HPropertyDriver
00190 {
00191 public:
00192 };
00193 
00194 //*********************************************************
00195 //** HExpression
00196 //*********************************************************
00197 class PLUGINEXPORT HExpression : public HPropertyDriver
00198 {
00199 public:
00200    enum { OK, CANTTOKENIZE, NORIGHTPARENTHESIS, UNKNOWNSYMBOL,
00201     DIVISIONBYZERO, NOLEFTPARENTHESIS, NOCOMMA, OUTOFRANGE, MUSTBEFLOAT,
00202     BADTYPESFORADD, BADTYPESFORMULTIPLY, INCORRECTTYPE, MUSTBETIME,
00203     BADTYPESFORCOMPARE, BADTYPESFORAND, BADTYPESFOROR, BADTYPEFORNOT,
00204     MUSTBEBOOL, MUSTBEVECTOR, MISSINGPARAMETER, MUSTBETRANSFORM }; //error codes
00205     
00206    String GetExpressionString();
00207    int SetExpressionString(const String &str);// returns error code
00208 };
00209 
00210 //*********************************************************
00211 //** HRotateDriver
00212 //*********************************************************
00213 class PLUGINEXPORT HRotateDriver : public HPropertyDriver
00214 {
00215 public:
00216    void ComputeBoneDirections(Vector &bonedir, Vector &rolldir, 
00217     Vector &parentbonedir, Vector &parentrolldir) const; //Obsolete   
00218    void ComputeBoneToParent(const Vector &bonedir, const Vector &rolldir, 
00219     const Vector &parentbonedir, const Vector &parentrolldir); //Obsolete   
00220    
00221    Quaternion GetBoneToParent();
00222    void SetBoneToParent(const Quaternion &quat);
00223 
00224    Quaternion GetParentToBone();
00225    void SetParentToBone(const Quaternion &quat);
00226    
00227    Quaternion GetValue( Time time, TimeRange &validrange );
00228    Quaternion GetValue( Time time );
00229    void StoreValue(Time time,  Quaternion &quat, BOOL storeundo=TRUE);
00230 };
00231 
00232 //*********************************************************
00233 //** HEulerRotateDriver
00234 //*********************************************************
00235 class PLUGINEXPORT HEulerRotateDriver : public HRotateDriver
00236 {
00237 public:
00238    static HEulerRotateDriver *New(HProperty *parent);
00239    RotateEuler GetValue( Time time, TimeRange &validrange );
00240    RotateEuler GetValue( Time time );
00241    void StoreValue(Time time, RotateEuler &value, BOOL storeundo=TRUE);
00242 
00243    HFloatDriver *GetX();
00244    HFloatDriver *GetY();
00245    HFloatDriver *GetZ();
00246 };
00247 
00248 //*********************************************************
00249 //** HQuaternionRotateDriver
00250 //*********************************************************
00251 class PLUGINEXPORT HQuaternionRotateDriver : public HRotateDriver
00252 {
00253 public:
00254    static HQuaternionRotateDriver *New(HProperty *parent);
00255    Quaternion GetValue( Time time, TimeRange &validrange );
00256    Quaternion GetValue( Time time );
00257    void StoreValue(Time time,  Quaternion &quat, BOOL storeundo=TRUE);
00258    
00259    HFloatDriver *GetX();
00260    HFloatDriver *GetY();
00261    HFloatDriver *GetZ();
00262    HFloatDriver *GetW();
00263 };
00264 
00265 //*********************************************************
00266 //** HVectorRotateDriver
00267 //*********************************************************
00268 class PLUGINEXPORT HVectorRotateDriver : public HRotateDriver
00269 {
00270 public:
00271    static HVectorRotateDriver *New(HProperty *parent);
00272    RotateVector GetValue( Time time, TimeRange &validrange );
00273    RotateVector GetValue( Time time );
00274    void StoreValue(Time time, RotateVector &value, BOOL storeundo=TRUE);
00275    
00276    HFloatDriver *GetX();
00277    HFloatDriver *GetY();
00278    HFloatDriver *GetZ();
00279    HFloatDriver *GetRoll();
00280 };
00281 
00282 //*********************************************************
00283 //** HTransformDriver
00284 //*********************************************************
00285 class PLUGINEXPORT HTransformDriver : public HPropertyDriver
00286 {
00287 public:
00288    static HTransformDriver *New(HProperty *parent);
00289 };
00290 
00291 //*********************************************************
00292 //** HVectorDriverNoSubs
00293 //*********************************************************
00294 class PLUGINEXPORT HVectorDriverNoSubs : public HPropertyDriver
00295 {
00296 public:
00297    static HVectorDriverNoSubs *New(HProperty *parent);
00298    Vector GetValue( Time time, TimeRange &validrange );
00299    Vector GetValue( Time time  );
00300 };
00301 
00302 //*********************************************************
00303 //** HTranslateDriverNoSubs
00304 //*********************************************************
00305 class PLUGINEXPORT HTranslateDriverNoSubs : public HVectorDriverNoSubs
00306 {
00307 public:
00308    static HTranslateDriverNoSubs *New(HProperty *parent);
00309 };
00310 
00311 //*********************************************************
00312 //** HVector2Driver
00313 //*********************************************************
00314 class PLUGINEXPORT HVector2Driver : public HPropertyDriver
00315 {
00316 public:
00317    static HVector2Driver *New(HProperty *parent);
00318 };
00319 
00320 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
