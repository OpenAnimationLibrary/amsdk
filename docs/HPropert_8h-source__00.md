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

# HPropert.h

[Go to the documentation of this file.](HPropert_8h.md)

<div class="fragment">

``` fragment
00001 // BC  6/14/2005  \Master120\Include\SDK\HPropert.h
00002 //NAP Bitmap COMEBACK RGBFloat needs old ColorVector functions for backward compata
00003 #define __HPROPERT_H
00004 
00005 #ifndef _SMALLPDB
00006 
00007 #ifndef __HHASHOBJ_H
00008 #include "SDK/HHashObj.h"
00009 #endif
00010 
00011 #ifndef __DATAVALUE_H
00012 #include "DataValue.h"
00013 #endif
00014 
00015 #ifndef __COLORVEC_H
00016 #include "ColorVec.h"
00017 #endif
00018 
00019 //*********************************************************
00020 //** HPropertyInfo
00021 //*********************************************************
00022 
00023 class PLUGINEXPORT HPropertyInfo
00024 {
00025 public:
00026    enum  DrawWhen { DRAWNEVER, DRAWALWAYS, DRAWIFSHADED, DRAWIFFLARES, DRAWIFMATERIALS, DRAWIFPARTICLES };
00027    enum  VisibleWhen { VISIBLENEVER, VISIBLEALWAYS, VISIBLECACHEONLY, VISIBLEINSTANCEONLY, VISIBLESOMETIMES };
00028 
00029    static HPropertyInfo *New( const char *localizedname, const char *matchname );
00030    void  operator delete( void *ptr ) { DeleteHandle( (HPropertyInfo *)ptr ); }
00031    static void DeleteHandle(HPropertyInfo *handle);
00032    
00033    void SetLocalizedName(const char *name); // for backward comp with V9.0o and older
00034    void SetMatchName(const char *name); // for backward comp with V9.0o and older
00035    
00036    void SetLocalizedName(const String &name);
00037    void SetMatchName(const String &name);
00038    String GetLocalizedName();
00039    String GetMatchName();
00040    void SetDocumentation(const char *doc);
00041    
00042    DrawWhen GetDrawWhen();
00043    void SetDrawWhen(DrawWhen dw);
00044    
00045    VisibleWhen GetVisibleWhen();
00046    void SetVisibleWhen(VisibleWhen vw);
00047 
00048    BOOL IsConstant();
00049    void SetConstant(BOOL state); // Constant will not animate over time
00050 
00051    BOOL IsReadOnly(); // Both cache and instanes will be read only
00052    void SetReadOnly(BOOL state);
00053 
00054    BOOL IsReadOnlyOnCache(); // User will not be able to change the value on the cache, SetReadOnly should be set to FALSE if you want the instances to be able to be editied
00055    void SetReadOnlyOnCache(BOOL state);
00056 
00057    BOOL IsReadOnlyOnInstance(); // User will not be able to change the value on the instance, SetReadOnly should be set to FALSE if you want the caches to be able to be editied
00058    void SetReadOnlyOnInstance(BOOL state);
00059 
00060    BOOL IsAdvanced(); // only shows up if user has Show Advanced Proerties on
00061    void SetAdvanced(BOOL state);
00062 
00063    BOOL IsSaveProperty(); // Defaults to TRUE
00064    void SetSaveProperty(BOOL state);
00065 
00066    BOOL IsNotifyAnimObjectValueChanged();
00067    void SetNotifyAnimObjectValueChanged(BOOL state); // use this to have HxtOnPtrMessage called for your property.  This is a speed hit
00068                                                     // so only set it if you really want the function to be called
00069    BOOL IsDeletable();
00070    void SetDeletable(BOOL state);
00071 
00072    void SetCacheAnimatable( BOOL state );
00073    BOOL GetCacheAnimatable();
00074 };
00075 
00076 //*********************************************************
00077 //** HProperty
00078 //*********************************************************
00079 class HPropertyDriver;
00080 class HPropertyShortcut;
00081 
00082 class PLUGINEXPORT HProperty : public HHashObject
00083 {
00084 public:
00085    HPropertyInfo *GetPropertyInfo() const;
00086    HPropertyDriver *GetHeadDriver() const;
00087    
00088    void Show( BOOL bShow = TRUE );
00089    
00090    void SetNullable(BOOL isnullable);
00091    BOOL IsNullable();
00092    BOOL IsNull();
00093    void SetNull( BOOL state=TRUE, HAnimObject *animob=NULL );
00094    void SetIsDynamic(BOOL isdynamic);
00095    BOOL IsDynamic();
00096    
00097    HHashObject *CreateParentForDriver();
00098    HProperty *GetDriverProperty();
00099    void AddDriver(HPropertyDriver *);
00100    
00101    int Compare( const HProperty *other, BOOL dochildren=TRUE );  // 0 => EQUAL, 1 => NOT EQUAL
00102    
00103    BOOL IsDefaultValue() const;
00104    int GetIndex() const;
00105    
00106    void Copy(const HProperty *other);
00107    HPropertyShortcut *FindEmptyRelation();//should return HEmptyRelation probably
00108    HProperty *GetPropertyCache();
00109    HProperty *MakeCopy();
00110    
00111    String ToString();
00112    
00113    BOOL GetFirstRelationKey();
00114    BOOL GetNextRelationKey();
00115    BOOL GetPrevRelationKey(BOOL *pHasKey);
00116    
00117    HProperty *GetParentProperty();
00118    
00119    BOOL IsUserProperty();
00120 };
00121 
00122 //*********************************************************
00123 //** HBoolPropertyInfo
00124 //*********************************************************
00125 class PLUGINEXPORT HBoolPropertyInfo : public HPropertyInfo
00126 {
00127 public:
00128    static HBoolPropertyInfo *New( const char *localizedname, const char *matchname );
00129    void SetDefaultValue( BOOL val );
00130    BOOL GetDefaultValue() const;
00131 
00132    void SetDisplayInPoseSlider(BOOL show);
00133    BOOL GetDisplayInPoseSlider();
00134 };
00135 
00136 //*********************************************************
00137 //** HBoolProperty
00138 //*********************************************************
00139 class PLUGINEXPORT HBoolProperty : public HProperty
00140 {
00141 public:
00142    static HBoolProperty *New();
00143    static HBoolProperty *New( HBoolPropertyInfo *propinfo );
00144    BOOL GetValue() const;
00145    BOOL GetValue( Time time );
00146    void SetValue( BOOL value );
00147    void StoreValue( Time time, BOOL value, BOOL storeundo=TRUE );
00148 };
00149 
00150 //*********************************************************
00151 //** HContainerProperty
00152 //*********************************************************
00153 class PLUGINEXPORT HContainerProperty : public HProperty
00154 {
00155 public:
00156    static HContainerProperty *New();
00157    static HContainerProperty *New( HPropertyInfo *propinfo );
00158 };
00159 
00160 //*********************************************************
00161 // HCategoryProperty
00162 // Maintains an array of sub variables
00163 //*********************************************************
00164 class PLUGINEXPORT HCategoryProperty : public HContainerProperty
00165 {
00166 public:
00167    static HCategoryProperty *New();
00168    static HCategoryProperty *New( HPropertyInfo *propinfo );
00169    int AddProperty( HProperty *property );
00170    BOOL RemoveProperty( HProperty *property);
00171 };
00172 
00173 //*********************************************************
00174 //** HUserCategoryProperty
00175 //*********************************************************
00176 class PLUGINEXPORT HUserCategoryProperty : public HCategoryProperty
00177 {
00178 public:
00179    static HUserCategoryProperty *New();//Use this to add folders to other UserCategoryProperties
00180 //   If trytokeep is TRUE the property name will be the name passed in if it doesn't exist,
00181 //   otherwise it will be the name appended by a instance number of the name
00182    int AddUserProperty(HProperty *property, const String &basestring, BOOL trytokeepname=FALSE); // No PropertyInfo needed in passed in Property because it is dynamically allocated in this call
00183 };
00184 
00185 //*********************************************************
00186 //** HBoolCategoryProperty
00187 //*********************************************************
00188 class PLUGINEXPORT HBoolCategoryProperty : public HCategoryProperty
00189 {
00190 public:
00191    static HBoolCategoryProperty *New();
00192    static HBoolCategoryProperty *New( HBoolPropertyInfo *propinfo );
00193 
00194    BOOL GetValue() const;
00195    BOOL GetValue( Time time );
00196    void SetValue( BOOL value );
00197    void StoreValue( Time time, BOOL value, BOOL storeundo=TRUE );
00198 };
00199 
00200 class HTypePropertyInfo;
00201 //*********************************************************
00202 //** HTypeCategoryProperty
00203 //*********************************************************
00204 class PLUGINEXPORT HTypeCategoryProperty : public HCategoryProperty
00205 {
00206 public:
00207    static HTypeCategoryProperty *New();
00208    static HTypeCategoryProperty *New( HTypePropertyInfo *propinfo );
00209 
00210    UINT GetValue() const;
00211    UINT GetValue( Time time );
00212    void SetValue( UINT value );
00213    void StoreValue( Time time, UINT value, BOOL storeundo=TRUE );
00214 };
00215 
00216 //*********************************************************
00217 //** HAttrPropertyInfo
00218 //*********************************************************
00219 class PLUGINEXPORT HAttrPropertyInfo : public HPropertyInfo
00220 {
00221 public:
00222    static HAttrPropertyInfo *New( const char *localizedname, const char *matchname );
00223 };
00224 
00225 //*********************************************************
00226 //** HAttrProperty
00227 //*********************************************************
00228 class HColorProperty;
00229 class HFloatProperty;
00230 class HPercentProperty;
00231 class HMaterial;
00232 
00233 class PLUGINEXPORT HAttrProperty : public HContainerProperty
00234 {
00235 public:
00236    static HAttrProperty *New( HAttrPropertyInfo *propinfo );
00237    static HAttrProperty *New();
00238 
00239    HAttrProperty *GetBaseAttr();
00240       
00241    HColorProperty *GetDiffuseColor();
00242    HFloatProperty *GetDiffuseFallOff();
00243    HColorProperty *GetAmbianceColor();
00244    HColorProperty *GetAmbianceColorForRead();
00245    HFloatProperty *GetAmbiance();
00246    HColorProperty *GetSpecularColor();
00247    HColorProperty *GetSpecularColorForRead();
00248    HFloatProperty *GetSpecularSize();
00249    HFloatProperty *GetSpecularIntensity();
00250    HFloatProperty *GetRoughness();
00251    HFloatProperty *GetRoughnessScale();
00252    HFloatProperty *GetTransparency();
00253    HFloatProperty *GetDensity();
00254    HFloatProperty *GetRefraction();
00255    HFloatProperty *GetTranslucency();
00256    HFloatProperty *GetReflectivity();
00257    HPercentProperty *GetReflectiveBlend();
00258    HFloatProperty *GetReflectivityFallOff();
00259    HFloatProperty *GetRadiance();
00260    HBoolProperty  *GetGlow();
00261    BOOL IsComplex();   // tells whether a pre-composited attr is complex (Combiners etc..)
00262    BOOL IsBump();      // tells whether any of the materials on a pre-composited attr had bump on
00263    BOOL IsInvariant(); // tells whether any of the materials on a pre-composited attr were invariant
00264    BOOL IsDisplace();  // tells whether any of the materials on a pre-composited attr had displace on
00265    HMaterial *GetMaterialHead();
00266 };
00267 
00268 //*********************************************************
00269 //** HFileInfoPropertyInfo
00270 //*********************************************************
00271 class PLUGINEXPORT HFileInfoPropertyInfo : public HPropertyInfo
00272 {
00273 public:
00274 };
00275 
00276 class HFilenameProperty;
00277 class HStringProperty;
00278 //*********************************************************
00279 //** HFileInfoProperty
00280 //*********************************************************
00281 class PLUGINEXPORT HFileInfoProperty : public HContainerProperty
00282 {
00283 public:
00284    HBoolProperty     *GetEmbedded();
00285    HFilenameProperty *GetFileName();
00286    HStringProperty   *GetCreatedBy();
00287    HStringProperty   *GetLastModifiedBy();
00288    HStringProperty   *GetDescription();
00289    HStringProperty   *GetNotes();
00290 };
00291 
00292 //*********************************************************
00293 //** HFloatPropertyInfo
00294 //*********************************************************
00295 class PLUGINEXPORT HFloatPropertyInfo : public HPropertyInfo
00296 {
00297 public:
00298    enum { FF_X           = 0x0001,
00299           FF_Y           = 0x0002,
00300           FF_Z           = 0x0003,
00301 
00302           FF_RED         = 0x0008,
00303           FF_GREEN       = 0x0010,
00304           FF_BLUE        = 0x0020,
00305 
00306           FF_UNIT        = 0x0040,
00307           FF_PERCENTAGE  = 0x0080,
00308           FF_ANGLE       = 0x0100
00309         };
00310 
00311    static HFloatPropertyInfo *New( const char *localizedname, const char *matchname );
00312    void SetFactorValue( float val ); // Set Factor before calling SetDefault, SetMin or SetMax
00313    void SetModulo( float modulo );
00314    void SetDefaultValue( float val );
00315    void SetMinValue( float val );
00316    void SetMaxValue( float val );
00317    void SetFlags(UINT flags);
00318    
00319    float GetFactorValue() const;
00320    float GetDefaultValue() const;
00321    float GetMinValue() const;
00322    float GetMaxValue() const;
00323    UINT  GetFlags() const;
00324    
00325    void SetDisplayInPoseSlider(BOOL show);
00326    BOOL GetDisplayInPoseSlider();
00327 };
00328 
00329 //*********************************************************
00330 //** HFloatProperty
00331 //*********************************************************
00332 class PLUGINEXPORT HFloatProperty : public HProperty
00333 {
00334 public:
00335    static HFloatProperty *New();
00336    static HFloatProperty *New( HFloatPropertyInfo *propinfo );
00337    float GetValue() const;
00338    float GetValue( Time time );
00339    void SetValue(float value);
00340    void StoreValue(Time time, float value, BOOL storeundo = TRUE);
00341 };
00342 
00343 //*********************************************************
00344 //** HPercentPropertyInfo
00345 //*********************************************************
00346 class PLUGINEXPORT HPercentPropertyInfo : public HFloatPropertyInfo
00347 {
00348 public:
00349 
00350    static HPercentPropertyInfo *New( const char *localizedname, const char *matchname );
00351 };
00352 
00353 //*********************************************************
00354 //** HPercentProperty
00355