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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# RenderS2.h

[Go to the documentation of this file.](RenderS2_8h.md)

<div class="fragment">

``` fragment
00001 // KB  2/8/2005  \Include\RenderS2.h
00002 
00003 #define __RENDERS2_H
00004 
00005 #ifndef __TOONPROP_H
00006 #include "ToonProp.h"
00007 #endif
00008 #ifndef __FILENAME_H
00009 #include "Filename.h"
00010 #endif
00011 #ifndef __INTPROPE_H
00012 #include "IntPrope.h"
00013 #endif
00014 #ifndef __CLIPPROP_H
00015 #include "ClipProp.h"
00016 #endif
00017 #ifndef __SHADERPR_H
00018 #include "ShaderPr.h"
00019 #endif
00020 #ifndef __BUTTONPR_H
00021 #include "ButtonPr.h"
00022 #endif
00023 #ifndef __CUSTOMRA_H
00024 #include "CustomRa.h"
00025 #endif
00026 #ifndef __IMAGEIOREG_H
00027 #include "ImageIOReg.h"
00028 #endif
00029 
00030 #define MINFILMSOFTNESS   .1f /* @ 640 */
00031 #define MAXFILMSOFTNESS 15.0f /* @ 640 */
00032 
00033 #define FILMGRAINSIZE100ASA    0.4f
00034 #define FILMGRAINAMOUNT100ASA 20.0f/UNIT
00035 #define FILMGRAINSIZE200ASA    0.5f
00036 #define FILMGRAINAMOUNT200ASA 30.0f/UNIT
00037 #define FILMGRAINSIZE400ASA    1.0f
00038 #define FILMGRAINAMOUNT400ASA 40.0f/UNIT
00039 
00040 #define BLOOMTHRESHOLDDAY   90.0f/UNIT
00041 #define BLOOMSTRENGTHDAY    25.0f/UNIT
00042 #define BLOOMRADIUSDAY       6.0f /* @ 640 */
00043 #define BLOOMTHRESHOLDNIGHT 75.0f/UNIT
00044 #define BLOOMSTRENGTHNIGHT  30.0f/UNIT
00045 #define BLOOMRADIUSNIGHT     6.0f /* @ 640 */
00046 
00047 #define TINTLIGHTBW    RGBFloat(1.0f)
00048 #define TINTDARKBW     RGBFloat(0.0f)
00049 #define TINTPERCENTBW  1.0f
00050 
00051 #define TINTLIGHTCOBALT   RGBFloat(.282f, .090f, .803f)
00052 #define TINTDARKCOBALT    RGBFloat(0.0f)
00053 #define TINTPERCENTCOBALT 1.0f
00054 
00055 #define TINTLIGHTSEPIA   RGBFloat(.996f, .866f, .674f)
00056 #define TINTDARKSEPIA    RGBFloat(0.0f)
00057 #define TINTPERCENTSEPIA 1.0f
00058 
00059 #define TINTLIGHTXRAY   RGBFloat(0.0f)
00060 #define TINTDARKXRAY    RGBFloat(1.0f)
00061 #define TINTPERCENTXRAY 1.0f
00062 
00063 #define SOFTEN8MM  3.0f /* @ 640 */
00064 #define SOFTEN16MM 2.0f /* @ 640 */
00065 #define SOFTEN35MM 1.0f /* @ 640 */
00066 #define NUMRESPRESETS 14
00067 
00068 void InitOutputSettingsStatics();
00069 UINT AddOutputImageIOTypeInfo( String &localizedname, String &matchname, String &documentation );
00070 void ClearOutputImageIOTypeInfo();
00071 void SetDefaultOutputImageIOFormat( ImageIORegistration *iio, String &savefilter );
00072 
00073 class Clip;
00074 class ShaderPtr;
00075 
00076 class NewRenderSettings : public ContainerProperty<Property>
00077 {
00078 public:
00079    CategoryProperty<TypeProperty>   m_renderquality; enum { RQ_DEFAULT, RQ_WIREFRAME, RQ_SHADED, RQ_SHADEDWIREFRAME, RQ_FINAL };
00080    CategoryProperty<BoolProperty>   m_ismultipass;
00081      TypeProperty                     m_typenumpasses; enum { MP_1, MP_2, MP_3, MP_4, MP_5,
00082                                                               MP_9, MP_16, MP_25, MP_36, MP_49,
00083                                                               MP_64, MP_81, MP_100, MP_121, MP_144,
00084                                                               MP_169, MP_196, MP_225, MP_256 };
00085      BoolProperty                     m_isenhanced;
00086    BoolProperty                     m_isshadows;
00087    CategoryProperty<BoolProperty>   m_isreflections;
00088      IntProperty                      m_reflectionlevels;
00089      CategoryProperty<BoolProperty>   m_issoftreflections;
00090        PercentProperty                  m_softreflectionquality;
00091      
00092    BoolProperty                     m_isdrawsystems;
00093    CategoryProperty<BoolProperty>   m_isfog;
00094      FloatProperty                    m_fogstart;
00095      FloatProperty                    m_fogend;
00096      ClipProperty                     m_fogimage;
00097    CategoryProperty<BoolProperty>   m_istoonrender;
00098      BoolProperty                     m_islinesonly;
00099      CategoryProperty<BoolProperty>   m_isoverridelines;
00100        BoolProperty                     m_isrenderlines;
00101        ToonLineProperties               m_toonlines;
00102      FloatProperty                    m_toonlinebias;
00103      CategoryProperty<BoolProperty>   m_isoverrideshading;
00104        ToonShadingProperties            m_toonshading;
00105 //   CategoryProperty<BoolProperty>   m_isglobalillumination;
00106 //     IntProperty                      m_globalilluminationrays;
00107    CategoryProperty<BoolProperty>   m_ismotionblur;
00108      PercentProperty                  m_motionblurpercent;
00109    CategoryProperty<BoolProperty>   m_isdof;
00110      FloatProperty                    m_focusdistance;
00111      FloatProperty                    m_doffrontdistance;
00112      FloatProperty                    m_dofbackdistance;
00113    CategoryProperty<BoolProperty>   m_isfieldrender;
00114      TypeProperty                     m_fieldorder; enum { FIELD_ODD, FIELD_EVEN };
00115    CategoryProperty<BoolProperty>   m_isstereo;
00116      FloatProperty                    m_stereoeyespacing;
00117      CategoryProperty<BoolProperty>   m_useframedistance;
00118         FloatProperty                    m_framedistance;
00119      //CategoryProperty<TypeProperty>   m_stereotype; enum { PARALLEL, CROSSEYED, ANAGLYPH, INTERLACED }; pre 9.02
00120      CategoryProperty<TypeProperty>   m_stereotype; enum { FREEVIEWING, ANAGLYPH, INTERLACED };
00121         TypeProperty                     m_freeviewingtype; enum { PARALLEL, CROSSEYED };
00122         TypeProperty                     m_anaglyphtype; enum { ANAGLYPHPURE, ANAGLYPHGREY, ANAGLYPHCOLOR };
00123         TypeProperty                     m_anaglyphglasses; enum { REDBLUE, BLUERED, REDGREEN, GREENRED };
00124         TypeProperty                     m_interlaceorder; enum { INTERLACE_LEFT, INTERLACE_RIGHT };
00125    CategoryProperty<BoolProperty>   m_isrendershaders;
00126      ShaderProperty                   m_diffuseshadername;
00127      ShaderProperty                   m_specularshadername;
00128      ShaderProperty                   m_ambianceshadername;
00129    TypeProperty                     m_patchsubdivisions; enum { SUB_1, SUB_4, SUB_16, SUB_ADAPTIVE }; 
00130    BoolProperty                     m_isshowbackfacing;
00131    BoolProperty                     m_isshowdecals;
00132    BoolProperty                     m_isdisplaycps;
00133    BoolProperty                     m_isdisplaybones;
00134    BoolProperty                     m_isdisplaygrid;
00135    CategoryProperty<Property>       m_post;
00136      CategoryProperty<TypeProperty>   m_isfilmgrain; enum { GRAIN_NONE, GRAIN_100ASA, GRAIN_200ASA, GRAIN_400ASA, GRAIN_CUSTOM };
00137        FloatProperty                    m_filmgrainsize;
00138        PercentProperty                  m_filmgrainamount;
00139      CategoryProperty<TypeProperty>   m_isbloom; enum { BLOOM_NONE, BLOOM_DAY, BLOOM_NIGHT, BLOOM_CUSTOM };
00140        FloatProperty                    m_bloomstrength;
00141        FloatProperty                    m_bloomthreshold;
00142        FloatProperty                    m_bloomradius;
00143      CategoryProperty<TypeProperty>   m_istint; enum { TINT_NONE, TINT_BW, TINT_COBALT, TINT_SEPIA, TINT_XRAY, TINT_CUSTOM };
00144        PercentProperty                  m_tintpercent;
00145        ColorProperty                    m_tintlightcolor;
00146        ColorProperty                    m_tintdarkcolor;
00147      CategoryProperty<TypeProperty>   m_issoften; enum { SOFTEN_NONE, SOFTEN_8MM, SOFTEN_16MM, SOFTEN_35MM, SOFTEN_CUSTOM };
00148        FloatProperty                    m_softness;
00149      CategoryProperty<TypeProperty>   m_isgammaeffect; enum { GAMMA_NONE, GAMMA_MONITOR, GAMMA_NTSC, GAMMA_CUSTOM };
00150        FloatProperty                    m_gammaeffectamount;
00151      BoolProperty                     m_isdither;
00152      BoolProperty                     m_isntscsafe;
00153      BoolProperty                     m_istemporalfilter;
00154      BoolProperty                     m_isdeantialias;
00155      
00156      int m_numpasses;
00157      union {
00158          ULONG            m_flags;
00159          struct {
00160             BITFIELDS32   m_isshowfinalandrealtimeproperties : 1,
00161                           m_isinited : 1;
00162          };
00163       };
00164 
00165 
00166                      NewRenderSettings(); //MyInit OR Init( *propertyinfo ) should be called by classes that contain this or when constructed with this constructor
00167                      NewRenderSettings( NewRenderSettings &other ) :
00168                       m_diffuseshadername( ShaderProperty::DIFFUSE ),
00169                       m_specularshadername( ShaderProperty::SPECULAR ),
00170                       m_ambianceshadername( ShaderProperty::AMBIANCE )
00171                      {
00172                         MyInit(); // overkill just needs parents set for sub-properties
00173                         CopyBits(&other);  // copies m_isnull, m_isuserproperty & m_isdynamicproperty
00174                         *this = other;
00175                      }
00176    virtual          ~NewRenderSettings() {}
00177 
00178    virtual void Init( PropertyInfo *propertyinfo, TreeObject *parent=NULL, BOOL isnull=FALSE, BOOL isloadpropertyinfo=FALSE );
00179    void              MyInit();
00180 
00181    NewRenderSettings &operator = (NewRenderSettings &other);
00182 
00183    void SetNumPassesFromProperty();
00184 
00185    virtual Property *MakeCopy();
00186    virtual void Copy( const Property *property );
00187 
00188    virtual Property *GetPropertyAt( int i );
00189    virtual BOOL      OnPtrMessage( PtrMessage ptrmessage, HashPtrObject **ptruplink, LONG lparam, Time time=0);
00190    virtual int       ParseArg( HashStream &hs, HashStream &ms, LONG id );
00191    virtual void ShowVisibleProperties(Property *dueto=NULL);
00192 
00193    void LoadPrefs( const String &key );
00194    BOOL IsPseudoMotionblur() { return !m_ismultipass && m_ismotionblur; }
00195    BOOL IsPseudoDOF() { return !m_ismultipass && m_isdof; }
00196 };
00197 
00198 class NewOutputSettings : public ContainerProperty<Property>
00199 {
00200 public:
00201    CategoryProperty<TypeProperty>     m_renderformat;
00202      ButtonProperty                     m_saveoptionssettings;
00203    FilenameProperty                   m_filename;
00204    CategoryProperty<TypeProperty>     m_rangetype; enum { RANGE, CUSTOM };
00205      TimeProperty                       m_start;
00206      TimeProperty                       m_end;
00207      IntProperty                        m_step;
00208      CustomRangeProperty                m_customrange;
00209    IntProperty                        m_fps; // Currently only used by NetRender Server
00210    CategoryProperty<TypeProperty>     m_renderresolution; enum { RES_MINI, RES_LOW, RES_TGA, RES_VGA, RES_PAR, RES_DV, RES_D1NTSC, RES_D1PAL, RES_HDTV720P, RES_HDTV1080, RES_PANAVISION, RES_VISTAVISION, RES_SUPER35, RES_CUSTOM };
00211      IntProperty                        m_renderwidth;
00212      IntProperty                        m_renderheight;
00213      FloatProperty                      m_renderaspect;
00214    CategoryProperty<TypeProperty>     m_gammapreset; enum { GAMMA_NONE, GAMMA_MONITOR, GAMMA_NTSC, GAMMA_CRT, GAMMA_CUSTOM };
00215      FloatProperty                      m_gamma;
00216    BoolProperty                       m_isframeburn;
00217    CategoryProperty<Property>         m_buffers;
00218      CategoryProperty<BoolProperty>     m_isalphabuffer;
00219        FilenameProperty                   m_alphafilename;
00220      CategoryProperty<BoolProperty>     m_islightbuffers;
00221         TypeProperty                      m_lightbuffertype; enum { LIGHTBUFFERS_SINGLE, LIGHTBUFFERS_ONEORCHORS, LIGHTBUFFERS_ALL };
00222      CategoryProperty<BoolProperty>     m_isshadowbuffer;
00223        FilenameProperty                   m_shadowbufferfilename;
00224      CategoryProperty<BoolProperty>     m_isdepthbuffer;
00225        FilenameProperty                   m_depthbufferfilename;
00226      CategoryProperty<BoolProperty>     m_issurfacenormalbuffer;
00227        FilenameProperty                   m_surfacenormalbufferfilename;
00228      BoolProperty                       m_applyposteffectstorender;
00229      union {
00230          ULONG            m_flags;
00231          struct {
00232             BITFIELDS32   m_isinited : 1;
00233          };
00234       };
00235      ImageIORegistration  *m_iioreg;
00236 
00237                      NewOutputSettings() { m_flags = NULL; m_iioreg = NULL; } //MyInit OR Init( *propertyinfo ) should be called by classes that contain this or when constructed with this constructor
00238                      NewOutputSettings( NewOutputSettings &other ) 
00239                      {
00240                         m_flags = NULL;
00241                         MyInit();
00242                         CopyBits( &other );
00243                         *this = other;
00244                         SetPreferedIIO(other.m_iioreg); //NAP yves could probably just set member directly here, but I wanted an easy spot for a breakpoint for all sets
00245                      }
00246                      
00247    virtual          ~NewOutputSettings() {}
00248    NewOutputSettings &operator = (NewOutputSettings &other) 
00249    { 
00250       ContainerProperty<Property>::operator = (other);
00251       SetPreferedIIO(other.m_iioreg);
00252       return *this; 
00253    }
00254 
00255    void FormatToExtensionAndIIO();
00256    ImageIORegistration *GetImageIOReg();
00257 
00258    virtual Property *MakeCopy();
00259    virtual void Copy( const Property *property );
00260    virtual void CopyNoChildren( const Property *property );
00261    virtual void ShowVisibleProperties(Property *dueto=NULL);
00262 
00263    virtual void Init( PropertyInfo *propertyinfo, TreeObject *parent=NULL, BOOL isnull=FALSE, BOOL isloadpropertyinfo=FALSE );
00264    void              MyInit();
00265 
00266    virtual Property *GetPropertyAt( int i );
00267    virtual BOOL      OnPtrMessage( PtrMessage ptrmessage, HashPtrObject **ptruplink, LONG lparam, Time time=0 );
00268 
00269    void LoadPrefs( const String &key );
00270    vo