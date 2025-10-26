tyInfo *GetZ();
00735    
00736    Vector GetDefaultValue() const;
00737    void SetDefaultValue(const Vector &v);
00738 };
00739 
00740 //*********************************************************
00741 //** HVectorProperty
00742 //*********************************************************
00743 class PLUGINEXPORT HVectorProperty : public HProperty
00744 {
00745 public:
00746    static HVectorProperty *New();
00747    static HVectorProperty *New(HVectorPropertyInfo *propinfo);
00748 
00749    Vector GetValue() const;
00750    Vector GetValue( Time time );
00751    void SetValue( const Vector &value );
00752    void StoreValue( Time time, const Vector &value, BOOL storeundo=TRUE );
00753    
00754    HFloatProperty *GetX();
00755    HFloatProperty *GetY();
00756    HFloatProperty *GetZ();
00757 };
00758 
00759 //*********************************************************
00760 //** HVectorPropertyNoSubsInfo
00761 //*********************************************************
00762 class PLUGINEXPORT HVectorPropertyNoSubsInfo : public HPropertyInfo
00763 {
00764 public:
00765    static HVectorPropertyNoSubsInfo *New( const char *localizedname, const char *matchname );
00766    
00767    HFloatPropertyInfo *GetX();
00768    HFloatPropertyInfo *GetY();
00769    HFloatPropertyInfo *GetZ();
00770    
00771    Vector GetDefaultValue() const;
00772    void SetDefaultValue(const Vector &v);
00773 };
00774 
00775 //*********************************************************
00776 //** HVectorPropertyNoSubs
00777 //*********************************************************
00778 class PLUGINEXPORT HVectorPropertyNoSubs : public HProperty
00779 {
00780 public:
00781    static HVectorPropertyNoSubs *New();
00782    static HVectorPropertyNoSubs *New(HVectorPropertyNoSubsInfo *propinfo);
00783 
00784    float GetXFactor() const;
00785    float GetYFactor() const;
00786    float GetZFactor() const;
00787    const Vector &GetValue() const;
00788    const Vector &GetValue(Time time);
00789    Vector GetFactoredValue() const;
00790    void SetFactoredValue( const Vector &value );
00791    void SetValue( const Vector &value );
00792    void StoreValue( Time time, const Vector &value, BOOL storeundo=TRUE );
00793 };
00794 
00795 //*********************************************************
00796 //** HVector2PropertyInfo
00797 //*********************************************************
00798 class PLUGINEXPORT HVector2PropertyInfo : public HPropertyInfo
00799 {
00800 public:
00801    static HVector2PropertyInfo *New( const char *localizedname, const char *matchname );
00802    
00803    HFloatPropertyInfo *GetX();
00804    HFloatPropertyInfo *GetY();
00805 
00806    Vector2 GetDefaultValue() const;
00807    void SetDefaultValue(const Vector2 &v);
00808 };
00809 
00810 //*********************************************************
00811 //** HVector2Property
00812 //*********************************************************
00813 class PLUGINEXPORT HVector2Property : public HProperty
00814 {
00815 public:
00816    static HVector2Property *New();
00817    static HVector2Property *New(HVector2PropertyInfo *propinfo);
00818 
00819    Vector2 GetValue(  ) const;
00820    Vector2 GetValue( Time time );
00821    void SetValue( const Vector2 &value );
00822    void StoreValue( Time time, const Vector2 &value, BOOL storeundo=TRUE );
00823    
00824    HFloatProperty *GetX();
00825    HFloatProperty *GetY();
00826 };
00827 
00828 //*********************************************************
00829 //** HColorPropertyInfo
00830 //*********************************************************
00831 class PLUGINEXPORT HColorPropertyInfo : public HVectorPropertyInfo
00832 {
00833 public:
00834    static HColorPropertyInfo *New( const char *localizedname, const char *matchname );
00835 
00836    HFloatPropertyInfo *GetRed();
00837    HFloatPropertyInfo *GetGreen();
00838    HFloatPropertyInfo *GetBlue();
00839    
00840    RGBFloat GetDefaultRGBFloatValue() const;
00841    /*don't use this one anymore*/ ColorVector GetDefaultValue() const;
00842 
00843    void SetDefaultValue(const RGBFloat &rgbfloat);
00844    /*don't use this one anymore*/ void SetDefaultValue(const ColorVector &cv);
00845 };
00846 
00847 //*********************************************************
00848 //** HColorProperty
00849 //*********************************************************
00850 class ColorBuf;
00851 class PLUGINEXPORT HColorProperty : public HVectorProperty
00852 {
00853 public:
00854    static HColorProperty *New();
00855    static HColorProperty *New(HColorPropertyInfo *propinfo);
00856 
00857    HFloatProperty *GetRed();
00858    HFloatProperty *GetGreen();
00859    HFloatProperty *GetBlue();
00860 
00861    float GetLuminance()const;
00862 
00863    COLORREF GetCOLORREF() const;
00864    RGBFloat GetFactoredRGBFloat() const;
00865    /*don't use this one anymore*/ ColorVector GetFactoredColorVector() const;
00866    
00867    RGBFloat GetNormalizedRGBFloat() const;
00868    /*don't use this one anymore*/ ColorVector GetNormalizedColorVector() const;
00869    
00870    void SetValue( const RGBFloat &value );
00871    /*don't use this one anymore*/ void SetValue( const ColorVector &value );
00872    
00873    void StoreValue( Time time, const RGBFloat &value, BOOL storeundo=TRUE );
00874    /*don't use this one anymore*/ void StoreValue( Time time, const ColorVector &value, BOOL storeundo=TRUE );
00875    
00876    void StoreValue( Time time, const ColorBuf &value, BOOL storeundo=TRUE );
00877 };
00878 
00879 //*********************************************************
00880 //** HScalePropertyInfo
00881 //*********************************************************
00882 class PLUGINEXPORT HScalePropertyInfo : public HVectorPropertyInfo
00883 {
00884 public:
00885    static HScalePropertyInfo *New( const char *localizedname, const char *matchname );
00886 };
00887 
00888 //*********************************************************
00889 //** HScaleProperty
00890 //*********************************************************
00891 class PLUGINEXPORT HScaleProperty : public HVectorProperty
00892 {
00893 public:
00894    static HScaleProperty *New();
00895    static HScaleProperty *New(HScalePropertyInfo *propinfo);
00896 };
00897 
00898 //*********************************************************
00899 //** HTranslatePropertyInfo
00900 //*********************************************************
00901 class PLUGINEXPORT HTranslatePropertyInfo : public HVectorPropertyInfo
00902 {
00903 public:
00904    static HTranslatePropertyInfo *New( const char *localizedname, const char *matchname );
00905 };
00906 
00907 //*********************************************************
00908 //** HTranslateProperty
00909 //*********************************************************
00910 class PLUGINEXPORT HTranslateProperty : public HVectorProperty
00911 {
00912 public:
00913    static HTranslateProperty *New();
00914    static HTranslateProperty *New(HTranslatePropertyInfo *propinfo);
00915 };
00916 
00917 //*********************************************************
00918 //** HTranslatePropertyNoSubs
00919 //*********************************************************
00920 class PLUGINEXPORT HTranslatePropertyNoSubs : public HVectorPropertyNoSubs
00921 {
00922 public:
00923    static HTranslateProperty *New();
00924    static HTranslateProperty *New(HTranslatePropertyInfo *propinfo);
00925 };
00926 
00927 //*********************************************************
00928 //** HObjectListNode
00929 //*********************************************************
00930 class PLUGINEXPORT HObjectListNode 
00931 {
00932 public:
00933    HObjectListNode *GetSibling();
00934    void SetSibling(HObjectListNode *);
00935 
00936    HTreeObject *GetObject();
00937    void SetObject(HTreeObject *);
00938    
00939    static HObjectListNode *New();
00940    static HObjectListNode *New( HTreeObject *obj, HObjectListNode *next );
00941 
00942    void  operator delete( void *ptr ) { DeleteHandle( (HObjectListNode *)ptr ); }
00943    static void DeleteHandle(HObjectListNode *handle);
00944 };
00945 
00946 //*********************************************************
00947 //** HPointerPropertyInfo
00948 //*********************************************************
00949 class PLUGINEXPORT HPointerPropertyInfo : public HPropertyInfo
00950 {
00951 public:
00952    static HPointerPropertyInfo *New( const char *localizedname, const char *matchname );
00953 };
00954 
00955 //*********************************************************
00956 //** HPointerProperty
00957 //*********************************************************
00958 class PLUGINEXPORT HPointerProperty : public HProperty
00959 {
00960 public:
00961    static HPointerProperty *New();
00962    static HPointerProperty *New(HPointerPropertyInfo *propinfo);
00963    HTreeObject *GetValue();
00964    void SetValue( HTreeObject *obj ); // Rarely used
00965    void StoreValue( Time time, HTreeObject *obj, BOOL storeundo=TRUE );
00966    String GetDescription();
00967    void SetDescription(const String &);
00968 };
00969 
00970 //*********************************************************
00971 //** HClipPropertyInfo
00972 //*********************************************************
00973 class PLUGINEXPORT HClipPropertyInfo : public HPointerPropertyInfo
00974 {
00975 public:
00976    static HClipPropertyInfo *New( const char *localizedname, const char *matchname );
00977    HVector2PropertyInfo *GetRepeatInfo();
00978    HTimePropertyInfo *GetTimeInfo();
00979    HBoolPropertyInfo *GetSeamlessInfo();
00980 };
00981 
00982 class HClip;
00983 //*********************************************************
00984 //** HClipProperty
00985 //*********************************************************
00986 class PLUGINEXPORT HClipProperty : public HContainerProperty
00987 {
00988 public:
00989    static HClipProperty *New();
00990    static HClipProperty *New(HClipPropertyInfo *propinfo);
00991    HClip *GetClip();
00992    
00993    HVector2Property *GetRepeat();
00994    HTimeProperty *GetTime();
00995    HBoolProperty *GetIsSeamless();
00996    
00997    int  GetWidth();
00998    int  GetHeight();
00999    BOOL ReadBitmap( float x, float y, RGBFloat *diffuse, float *opacity, float pixelwidth);
01000    /*don't use this one anymore*/ BOOL ReadBitmap( float x, float y, ColorVector *diffuse, float *opacity, float pixelwidth);
01001    
01002    BOOL ReadBumpmap( float x, float y, Vector2 &delta, float pixelwidth );
01003    BOOL LoadImage( const String &filename );
01004 };
01005 
01006 //*********************************************************
01007 //** HTexInfo
01008 //*********************************************************
01009 class PLUGINEXPORT HTexInfo 
01010 {
01011 public:
01012    HAttrProperty *GetAttr();
01013    Vector        *GetN(); // Screen Space
01014    float          GetHeight();
01015    void           SetHeight( float val );
01016    Time           GetTime();
01017    float          GetFPS();
01018    float          GetPixelWidth();
01019    Vector         GetGlobalP(); // World Space, If from a HSHader plugin, us HSHader::GetHitP rather than this.
01020    Vector         GetEye(); // Screen Space
01021    Vector         GetD(); // Screen Space
01022    Matrix34      *GetMatrix(); //Model Space To Screen Space
01023    int            GetObjectType();
01024    HObject       *GetObject();
01025    void          *GetSubObject();
01026 };
01027 
01028 //*********************************************************
01029 //** HShading
01030 //*********************************************************
01031 class PLUGINEXPORT HShading : public HProperty
01032 {
01033 public:
01034    HTexInfo    *GetTexInfo();
01035    RGBFloat *GetACol(); //these gets invalidate plugins that used to use this built for v11.1 or earlier
01036    RGBFloat *GetDCol(); //should probably rewrite with RGBFloat GetACol(), and SetACol(RGBFloat &)
01037    RGBFloat *GetSCol(); //since these invalidate anyways.
01038    Vector      *GetAway();
01039    Vector      *GetL();
01040    float        GetIntensity();
01041    float        GetLDot();
01042    float        GetEDot();
01043    int          GetObjectType();
01044    HObject     *GetObject();
01045    void        *GetSubObject();
01046    Vector       GetHitP();
01047 };
01048 
01049 //*********************************************************
01050 //** HGradientPropertyInfo
01051 //*********************************************************
01052 class PLUGINEXPORT HGradientPropertyInfo : public HPropertyInfo
01053 {
01054 public:
01055    static HGradientPropertyInfo *New( const char *localizedname, const char *matchname );
01056 };
01057 
01058 //*********************************************************
01059 //** HGradientProperty
01060 //*********************************************************
01061 class PLUGINEXPORT HGradientProperty : public HProperty
01062 {
01063 public:
01064    static HGradientProperty *New();
01065    static HGradientProperty *New(HGradientPropertyInfo *propinfo);
01066    RGBFloat GetColor( RGBFloat &diffuse, float n );
01067    /*don't use this one anymore*/ ColorVector GetColor( ColorVector &diffuse, float n );
01068 };
01069 
01070 //*********************************************************
01071 //** HDataPropertyInfo
01072 //*********************************************************
01073 class PLUGINEXPORT HDataPropertyInfo : public HPropertyInfo
01074 {
01075 public:
01076    static HDataPropertyInfo *New( const char *localizedname, const char *matchname );
01077 
01078    void SetDefaultValue( const DataValue &value );
01079    const DataValue &GetDefaultValue() const;
01080 
01081    void SetSaveCompressed( BOOL savecompressed );
01082    BOOL GetSaveCompressed() const;
01083 };
01084 
01085 //*********************************************************
01086 //** HDataProperty
01087 //*********************************************************
01088 class PLUGINEXPORT HDataProperty : public HProperty
01089 {
01090 public:
01091    static HDataProperty *New();
01092    static HDataProperty *New( HDataPropertyInfo *propinfo );
01093    const DataValue &GetValue() const;
01094    DataValue GetValue(Time time) const;
01095    void SetValue( const DataValue &value );
01096    void StoreValue(const DataValue &value, BOOL storeundo = TRUE); // Stores at Time 0
01097    void StoreValue( Time time, const DataValue &value, BOOL storeundo=TRUE );
01098 };
01099 
01100 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>
