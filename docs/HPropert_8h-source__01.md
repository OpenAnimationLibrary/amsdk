 //*********************************************************
00356 class PLUGINEXPORT HPercentProperty : public HFloatProperty
00357 {
00358 public:
00359    static HPercentProperty *New();
00360    static HPercentProperty *New( HPercentPropertyInfo *propinfo );
00361 };
00362 
00363 //*********************************************************
00364 //** HIntPropertyInfo
00365 //*********************************************************
00366 class PLUGINEXPORT HIntPropertyInfo : public HPropertyInfo
00367 {
00368 public:
00369    static HIntPropertyInfo *New( const char *localizedname, const char *matchname );
00370    void SetDefaultValue( int val );
00371    void SetMinValue( int val );
00372    void SetMaxValue( int val );
00373 
00374    int GetDefaultValue() const;
00375    int GetMinValue() const;
00376    int GetMaxValue() const;
00377 };
00378 
00379 //*********************************************************
00380 //** HIntProperty
00381 //*********************************************************
00382 class PLUGINEXPORT HIntProperty : public HProperty
00383 {
00384 public:
00385    static HIntProperty *New();
00386    static HIntProperty *New( HIntPropertyInfo *propinfo );
00387    int GetValue() const;
00388    int GetValue( Time time );
00389    void SetValue(int value);
00390    void StoreValue(Time time, int value, BOOL storeundo = TRUE);
00391 };
00392 
00393 //*********************************************************
00394 //** HRotatePropertyInfo
00395 //*********************************************************
00396 class PLUGINEXPORT HRotatePropertyInfo : public HPropertyInfo
00397 {
00398 public:
00399    static HRotatePropertyInfo *New( const char *localizedname, const char *matchname );
00400 };
00401 
00402 //*********************************************************
00403 //** HRotateProperty
00404 //*********************************************************
00405 class PLUGINEXPORT HRotateProperty : public HProperty
00406 {
00407 public:
00408    enum InterpolationMethod { VECTORINTERP, EULERINTERP, QUATINTERP };
00409 
00410    static HRotateProperty *New();
00411    static HRotateProperty *New( HRotatePropertyInfo *propinfo );
00412    
00413    InterpolationMethod GetDefaultObjectInterpolationMethod();
00414    void SetDefaultObjectInterpolationMethod(InterpolationMethod method);
00415    InterpolationMethod GetDefaultBoneInterpolationMethod();
00416    void SetDefaultBoneInterpolationMethod(InterpolationMethod method);
00417    InterpolationMethod GetDefaultRootBoneInterpolationMethod();
00418    void SetDefaultRootBoneInterpolationMethod(InterpolationMethod method);
00419    
00420    const Quaternion &GetValue() const;
00421    const Quaternion &GetValue( Time time );
00422    void SetValue( const Quaternion &value );
00423    void StoreValue( Time time, const Quaternion &value, BOOL storeroll=TRUE);// old for Backward compatibility, Defaults TRUE for StoreUndo
00424    void StoreValue( Time time, const Quaternion &value, BOOL storeroll, BOOL storeundo);
00425 };
00426 
00427 //*********************************************************
00428 //** HButtonPropertyInfo
00429 //*********************************************************
00430 class PLUGINEXPORT HButtonPropertyInfo : public HPropertyInfo
00431 {
00432 public:
00433    static HButtonPropertyInfo *New( const char *localizedname, const char *matchname );
00434    
00435    void SetButtonText(const char *);
00436    const char *GetButtonText() const;
00437 };
00438 
00439 //*********************************************************
00440 //** HButtonProperty
00441 //*********************************************************
00442 class PLUGINEXPORT HButtonProperty : public HProperty
00443 {
00444 public:
00445    static HButtonProperty *New();
00446    static HButtonProperty *New( HButtonPropertyInfo *propinfo );
00447 
00448    void SetButtonText(const char *); // Use this over the ones in ButtonPropertyInfo if you need to change the text on different instances of the property
00449    const char *GetButtonText() const;
00450    void Press();
00451 };
00452 
00453 //*********************************************************
00454 //** HBiasPropertyInfo
00455 //*********************************************************
00456 class PLUGINEXPORT HBiasPropertyInfo : public HPropertyInfo
00457 {
00458 public:
00459    static HBiasPropertyInfo *New( const char *localizedname, const char *matchname );
00460    
00461    HFloatPropertyInfo *GetAlphaPropertyInfo();
00462    HFloatPropertyInfo *GetGammaPropertyInfo();
00463    HFloatPropertyInfo *GetMagnitudePropertyInfo();
00464 };
00465 
00466 //*********************************************************
00467 //** HBiasProperty
00468 //*********************************************************
00469 class PLUGINEXPORT HBiasProperty : public HProperty
00470 {
00471 public:
00472    static HBiasProperty *New();
00473    static HBiasProperty *New( HBiasPropertyInfo *propinfo );
00474 
00475    float GetAlpha();
00476    float GetGamma();
00477    float GetMagnitude();
00478    void SetAlpha( float num );
00479    void SetGamma( float num );
00480    void SetMagnitude( float num );
00481 
00482    const Vector &GetValue();
00483    const Vector &GetValue(Time time);
00484    Vector GetFactoredValue();
00485 
00486    void SetFactoredValue( const Vector &value );
00487    void SetValue( const Vector &value );
00488    void StoreValue( Time time, const Vector &value, BOOL storeundo=TRUE );
00489 };
00490 
00491 //*********************************************************
00492 //** HStringPropertyInfo
00493 //*********************************************************
00494 class PLUGINEXPORT HStringPropertyInfo : public HPropertyInfo
00495 {
00496 public:
00497    static HStringPropertyInfo *New( const char *localizedname, const char *matchname );
00498    void SetDefaultValue( const char *value );
00499    void SetIllegalChars( const char *value );
00500    const char *GetDefaultValue() const;
00501    const char *GetIllegalChars() const;
00502 };
00503 
00504 //*********************************************************
00505 //** HStringProperty
00506 //*********************************************************
00507 class PLUGINEXPORT HStringProperty : public HProperty
00508 {
00509 public:
00510    static HStringProperty *New();
00511    static HStringProperty *New( HStringPropertyInfo *propinfo );
00512    const char *GetValue() const;
00513    void SetValue( const char *value );
00514    void StoreValue(const char *value, BOOL storeundo = TRUE);
00515 };
00516 
00517 //*********************************************************
00518 //** HFilenamePropertyInfo
00519 //*********************************************************
00520 class PLUGINEXPORT HFilenamePropertyInfo : public HStringPropertyInfo
00521 {
00522 public:
00523    static HFilenamePropertyInfo *New( const char *localizedname, const char *matchname );
00524    void SetFileDialogTitle( const char *value );
00525    void SetFileDialogFilter( const char *value );
00526    void SetDefaultExtension( const char *value );
00527    void SetIsOpenDialog( BOOL isopendialog );
00528    const char *GetFileDialogTitle() const;
00529    const char *GetFileDialogFilter() const;
00530    const char *GetDefaultExtension() const;
00531    BOOL IsOpenDialog() const;
00532    BOOL IsPromptForMissingFileOnLoad();
00533    void SetIsPromptForMissingFileOnLoad(BOOL state);
00534 };
00535 
00536 //*********************************************************
00537 //** HFilenameProperty
00538 //*********************************************************
00539 class PLUGINEXPORT HFilenameProperty : public HStringProperty
00540 {
00541 public:
00542    static HFilenameProperty *New();
00543    static HFilenameProperty *New( HFilenamePropertyInfo *propinfo );
00544 };
00545 
00546 //*********************************************************
00547 //** HDirPropertyInfo
00548 //*********************************************************
00549 class PLUGINEXPORT HDirPropertyInfo : public HStringPropertyInfo
00550 {
00551 public:
00552    static HDirPropertyInfo *New( const char *localizedname, const char *matchname );
00553    void SetFileDialogTitle( const char *value );
00554    const char *GetFileDialogTitle() const;
00555 };
00556 
00557 //*********************************************************
00558 //** HDirProperty
00559 //*********************************************************
00560 class PLUGINEXPORT HDirProperty : public HStringProperty
00561 {
00562 public:
00563    static HDirProperty *New();
00564    static HDirProperty *New( HDirPropertyInfo *propinfo );
00565 };
00566 
00567 //*********************************************************
00568 //** HTimePropertyInfo
00569 //*********************************************************
00570 class PLUGINEXPORT HTimePropertyInfo : public HPropertyInfo
00571 {
00572 public:
00573    static HTimePropertyInfo *New( const char *localizedname, const char *matchname );
00574    void SetDefaultValue( Time val );
00575    void SetMinValue( Time val );
00576    void SetMaxValue( Time val );
00577 
00578    Time GetDefaultValue() const;
00579    Time GetMinValue() const;
00580    Time GetMaxValue() const;
00581 };
00582 
00583 //*********************************************************
00584 //** HTimeProperty
00585 //*********************************************************
00586 class PLUGINEXPORT HTimeProperty : public HProperty
00587 {
00588 public:
00589    static HTimeProperty *New();
00590    static HTimeProperty *New( HTimePropertyInfo *propinfo );
00591    Time GetValue() const;
00592    Time GetValue(Time time);
00593    void SetValue(Time value);
00594    void StoreValue(Time time, Time value, BOOL storeundo = TRUE);
00595 };
00596 
00597 //*********************************************************
00598 //** HTimeRangePropertyInfo
00599 //*********************************************************
00600 class PLUGINEXPORT HTimeRangePropertyInfo : public HPropertyInfo
00601 {
00602 public:
00603    static HTimeRangePropertyInfo *New( const char *localizedname, const char *matchname );
00604 };
00605 
00606 //*********************************************************
00607 //** HTimeRangeProperty
00608 //*********************************************************
00609 class PLUGINEXPORT HTimeRangeProperty : public HContainerProperty
00610 {
00611 public:
00612    static HTimeRangeProperty *New();
00613    static HTimeRangeProperty *New( HTimeRangePropertyInfo *propinfo );
00614    HTimeProperty *GetStart();
00615    HTimeProperty *GetEnd();
00616 };
00617 
00618 //*********************************************************
00619 //** HTransformPropertyInfo
00620 //*********************************************************
00621 class PLUGINEXPORT HTransformPropertyInfo : public HPropertyInfo
00622 {
00623 public:
00624    static HTransformPropertyInfo *New( const char *localizedname, const char *matchname );
00625 };
00626 
00627 class HTranslateProperty;
00628 class HScaleProperty;
00629 class HRotateProperty;
00630 //*********************************************************
00631 //** HTransformProperty
00632 //*********************************************************
00633 class PLUGINEXPORT HTransformProperty : public HProperty
00634 {
00635 public:
00636    static HTransformProperty *New();
00637    static HTransformProperty *New( HTransformPropertyInfo *propinfo );
00638    HTranslateProperty *GetTranslate();
00639    HScaleProperty *GetScale();
00640    HRotateProperty *GetRotate();
00641    TSQ GetTSQ() const;
00642 };
00643 
00644 class HTypeInfo;
00645 //*********************************************************
00646 //** TypeInfoArray
00647 //*********************************************************
00648 class PLUGINEXPORT TypeInfoArray
00649 {
00650 private:
00651    HTypeInfo *m_typeinfoarray;
00652    int m_count;
00653 
00654    void AllocArray(HTypeInfo **array, int count);
00655    void DeleteArray(HTypeInfo *array);
00656    HTypeInfo *ElementAt(HTypeInfo *array, int index);
00657 
00658 public:
00659    TypeInfoArray() {
00660       m_typeinfoarray = NULL;
00661       m_count = 0;
00662    }
00663    ~TypeInfoArray() {
00664       DeleteArray(m_typeinfoarray);
00665    }
00666    void SetArraySize(int count) { 
00667       DeleteArray(m_typeinfoarray);
00668       AllocArray(&m_typeinfoarray, count);
00669       m_count = count;
00670    }
00671    void DeleteArray() { 
00672       DeleteArray(m_typeinfoarray);
00673       m_typeinfoarray = NULL;
00674       m_count = 0;
00675    }
00676    HTypeInfo *operator [] ( int index ) { return ElementAt(m_typeinfoarray, index); }
00677 
00678 // Internal use only
00679    HTypeInfo *GetTypeInfoArrayData() { return m_typeinfoarray; }
00680    int GetCount() const { return m_count; }
00681 };
00682 
00683 //*********************************************************
00684 //** HTypeInfo
00685 //*********************************************************
00686 class PLUGINEXPORT HTypeInfo
00687 {
00688 public:
00689    String GetMatchName() const;
00690    String GetLocalizedName() const;
00691    void SetMatchName(const String &name);
00692    void SetLocalizedName(const String &name);
00693    void SetMatchName(const char *);  // Old for backward Compatibility with version 9.0o and older
00694    void SetLocalizedName(const char *);  // Old for backward Compatibility with version 9.0o and older
00695 };
00696 
00697 //*********************************************************
00698 //** HTypePropertyInfo
00699 //*********************************************************
00700 class PLUGINEXPORT HTypePropertyInfo : public HPropertyInfo
00701 {
00702 public:
00703    static HTypePropertyInfo *New( const char *localizedname, const char *matchname, TypeInfoArray *typeinfoarray );
00704    
00705    void SetDefaultIndex(UINT index);
00706    UINT GetDefaultIndex() const;   
00707 };
00708 
00709 //*********************************************************
00710 //** HTypeProperty
00711 //*********************************************************
00712 class PLUGINEXPORT HTypeProperty : public HProperty
00713 {
00714 public:
00715    static HTypeProperty *New();
00716    static HTypeProperty *New( HTypePropertyInfo *propinfo );
00717    
00718    UINT GetValue() const;
00719    UINT GetValue( Time time );
00720    void SetValue( UINT value );
00721    void StoreValue( Time time, UINT value, BOOL storeundo = TRUE);
00722 };
00723 
00724 //*********************************************************
00725 //** HVectorPropertyInfo
00726 //*********************************************************
00727 class PLUGINEXPORT HVectorPropertyInfo : public HPropertyInfo
00728 {
00729 public:
00730    static HVectorPropertyInfo *New( const char *localizedname, const char *matchname );
00731    
00732    HFloatPropertyInfo *GetX();
00733    HFloatPropertyInfo *GetY();
00734    HFloatProper