//KB  2/8/2005  \Include\RenderS2.h
// ReSharper disable CppClangTidyBugproneUnhandledSelfAssignment
#pragma once
#include "ResolutionP.h"
#include "ToonProp.h"
#include "Filename.h"
#include "IntPrope.h"
#include "ClipProp.h"
#include "ShaderPr.h"
#include "ButtonPr.h"
#include "CustomRa.h"
#include "ImageIOReg.h"

void InitOutputSettingsStatics();
UINT AddOutputImageIOTypeInfo(const String &localizedname, const String &matchname, String &documentation);
void ClearOutputImageIOTypeInfo();
void SetDefaultOutputImageIOFormat(const ImageIORegistration *iio, const String &savefilter);
class Clip;
class ShaderPtr;

// ReSharper disable once CppClassCanBeFinal
class NewRenderSettings : public ContainerProperty<Property> {
public:
    CategoryProperty<TypeProperty> m_renderquality;

    enum {
        RQ_DEFAULT,
        RQ_WIREFRAME,
        RQ_SHADED,
        RQ_SHADEDWIREFRAME,
        RQ_FINAL
    };

    CategoryProperty<BoolProperty> m_ismultipass;
    TypeProperty m_typenumpasses;

    enum {
        MP_1,
        MP_2,
        MP_3,
        MP_4,
        MP_5,
        MP_9,
        MP_16,
        MP_25,
        MP_36,
        MP_49,
        MP_64,
        MP_81,
        MP_100,
        MP_121,
        MP_144,
        MP_169,
        MP_196,
        MP_225,
        MP_256
    };

    BoolProperty m_isenhanced;
    BoolProperty m_isshadows;
    CategoryProperty<BoolProperty> m_isambianceocclusion;
    PercentProperty m_ambianceocclusionquality;
    BoolProperty m_istransparentambianceocclusion;
    CategoryProperty<BoolProperty> m_ssao;
    BoolProperty m_ssao_aoonly;
    TypeProperty m_ssao_samplecount;

    enum {
        SSAO2,
        SSAO4,
        SSAO8,
        SSAO16,
        SSAO32,
        SSAO64,
        SSAO128,
        SSAO256,
        SSAO512,
        SSAO1024,
        SSAO2048,
        SSAO4096
    };

    FloatProperty m_ssao_radius;
    FloatProperty m_ssao_distance;
    FloatProperty m_ssao_gamma;
    PercentProperty m_ssao_diffusion;
    PercentProperty m_ssao_softness;
    FloatProperty m_ssao_luminfluence;
    BoolProperty m_ssao_useblur;
    FloatProperty m_ssao_blurradius;
    BoolProperty m_ssao_merge;
    BoolProperty m_ssao_cpufallback;
    CategoryProperty<BoolProperty> m_isreflections;
    IntProperty m_reflectionlevels;
    CategoryProperty<BoolProperty> m_issoftreflections;
    PercentProperty m_softreflectionquality;
    BoolProperty m_isdrawsystems;
    BoolProperty m_issubsurfacescattering;
    CategoryProperty<BoolProperty> m_isfog;
    FloatProperty m_fogstart;
    FloatProperty m_fogend;
    ClipProperty m_fogimage;
    CategoryProperty<BoolProperty> m_istoonrender;
    BoolProperty m_islinesonly;
    CategoryProperty<BoolProperty> m_isoverridelines;
    BoolProperty m_isrenderlines;
    ToonLineProperties m_toonlines;
    FloatProperty m_toonlinebias;
    CategoryProperty<BoolProperty> m_isoverrideshading;
    ToonShadingProperties m_toonshading;
    CategoryProperty<BoolProperty> m_ismotionblur;
    PercentProperty m_motionblurpercent;
    CategoryProperty<BoolProperty> m_isdof;
    FloatProperty m_focusdistance;
    FloatProperty m_doffrontdistance;
    FloatProperty m_dofbackdistance;
    CategoryProperty<BoolProperty> m_isfieldrender;
    TypeProperty m_fieldorder;

    enum {
        FIELD_ODD,
        FIELD_EVEN
    };

    CategoryProperty<BoolProperty> m_isstereo;
    FloatProperty m_stereoeyespacing;
    CategoryProperty<BoolProperty> m_useframedistance;
    FloatProperty m_framedistance;
    CategoryProperty<TypeProperty> m_stereotype;

    enum {
        FREEVIEWING,
        ANAGLYPH,
        INTERLACED
    };

    TypeProperty m_freeviewingtype;

    enum {
        PARALLEL,
        CROSSEYED
    };

    TypeProperty m_anaglyphtype;

    enum {
        ANAGLYPHPURE,
        ANAGLYPHGREY,
        ANAGLYPHCOLOR
    };

    TypeProperty m_anaglyphglasses;

    enum {
        REDBLUE,
        BLUERED,
        REDGREEN,
        GREENRED
    };

    TypeProperty m_interlaceorder;

    enum {
        INTERLACE_LEFT,
        INTERLACE_RIGHT
    };

    CategoryProperty<BoolProperty> m_isrendershaders;
    ShaderProperty m_diffuseshadername{ShaderProperty::ShaderType::DIFFUSE};
    ShaderProperty m_specularshadername{ShaderProperty::ShaderType::SPECULAR};
    ShaderProperty m_ambianceshadername{ShaderProperty::ShaderType::AMBIANCE};
    TypeProperty m_patchsubdivisions;

    enum {
        SUB_1,
        SUB_4,
        SUB_16,
        SUB_64,
        SUB_256,
        SUB_1024,
        SUB_4096,
        SUB_ADAPTIVE
    };

    BoolProperty m_isshowbackfacing;
    BoolProperty m_isshowdecals;
    BoolProperty m_isdisplaycps;
    BoolProperty m_isdisplaybones;
    BoolProperty m_isdisplaygrid;
    BoolProperty m_isdisplaypivot;
    CategoryProperty<BoolProperty> m_useGPU;
    BoolProperty m_gpu_eachpass;
    CategoryProperty<BoolProperty> m_gpu_blur;
    FloatProperty m_gpu_blur_radius;
    IntProperty m_gpu_blur_samples;
    BoolProperty m_gpu_blur_merge;
    CategoryProperty<BoolProperty> m_gpu_misc;
    TypeProperty m_gpu_misc_type;

    enum {
        GREYSCALE,
        SEPIA,
        NEGATIVE,
        SHARPEN,
        DILATE,
        ERODE,
        LAPLACIAN,
        PREWITT,
        SOBEL
    };

    IntProperty m_gpu_misc_samples;
    BoolProperty m_gpu_misc_merge;
    TypeProperty m_progressivepasses; //for realtime rendering

    int m_numpasses{16};        //If you change this need to change f_numpassesinfo to match
    float m_desiredgamma{1.F};  //Desired gamma correction for preview renders
    float m_currentgamma{2.2F}; //Current gamma setting of the monitor
    bool m_isinited{false};

    NewRenderSettings() noexcept = default; //MyInit OR Init( *propertyinfo ) should be called by classes that contain this or when constructed with this constructor
    NewRenderSettings(const NewRenderSettings &other) : m_desiredgamma(other.m_desiredgamma), m_currentgamma(other.m_currentgamma) {
        MyInit();             //overkill just needs parents set for sub-properties
        HashCopyBits(&other); //copies m_isnull, m_isuserproperty & m_isdynamicproperty
        *this = (NewRenderSettings &&)other;
    }

    ~NewRenderSettings() override = default;
    NewRenderSettings &operator=(NewRenderSettings &&other) noexcept;
    NewRenderSettings &operator=(const NewRenderSettings &);
    NewRenderSettings(NewRenderSettings &&) = delete;
    void MyInit();
    void SetNumPassesFromProperty();
    void LoadPrefs(const String &key) override;

    [[nodiscard]] bool IsPseudoMotionblur() const noexcept {
        return !m_ismultipass.GetValue() && m_ismotionblur.GetValue();
    }

    [[nodiscard]] bool IsPseudoDOF() const noexcept {
        return !m_ismultipass.GetValue() && m_isdof.GetValue();
    }

    [[nodiscard]] bool UseGPU() const noexcept {
        return m_useGPU.GetValue();
    }

    [[nodiscard]] bool UseGPU_Pass() const noexcept {
        return m_gpu_eachpass.GetValue();
    }

    void Init(PropertyInfo *propertyinfo, TreeObject *parent = nullptr, bool isnull = false, bool isloadpropertyinfo = false) override;
    Property *MakeCopy() noexcept override;
    void CopyProperty(const Property *prop) noexcept override;
    Property *GetPropertyAt(int i) noexcept override;
    bool OnPtrMessage(PtrMessage ptrmessage, HashPtrObject **ptruplink, LONG_PTR lparam, Time time = Time(), bool storeundo = true) override;
    int ParseArg(HashStream &hs, HashStream &ms, int id) override;
    void ShowVisibleProperties(Property *dueto = nullptr) noexcept override;
};

// ReSharper disable once CppClassCanBeFinal
class NewOutputSettings final : public ContainerProperty<Property> {
public:
    CategoryProperty<TypeProperty> m_renderformat;
    ButtonProperty m_saveoptionssettings;
    FilenameProperty m_filename;
    CategoryProperty<TypeProperty> m_rangetype;

    enum RangeType : uint8_t {
        RANGE,
        CUSTOM
    };

    TimeProperty m_start;
    TimeProperty m_end;
    IntProperty m_step;
    CustomRangeProperty m_customrange;
    IntProperty m_fps; //Currently only used by NetRender Server
    ResolutionProperty m_renderresolution;
    CategoryProperty<TypeProperty> m_gammapreset;

    /* declared in ImageIO.h
    enum {
        GAMMA_NONE,
        GAMMA_MONITOR,
        GAMMA_NTSC,
        GAMMA_CRT,
        GAMMA_CUSTOM
    };
     */

    FloatProperty m_gamma;
    CategoryProperty<Property> m_buffers;
    BoolProperty m_isalphabuffer;
    CategoryProperty<BoolProperty> m_islightbuffers;
    TypeProperty m_lightbuffertype;

    enum LightBuffers : uint8_t {
        LIGHTBUFFERS_SINGLE,
        LIGHTBUFFERS_ONEORCHORS,
        LIGHTBUFFERS_ALL
    };

    BoolProperty m_isshadowbuffer;
    BoolProperty m_isdepthbuffer;
    BoolProperty m_issurfacenormalbuffer;
    BoolProperty m_applyposteffectstorender;
    BoolProperty m_savebuffersexternal;
    BoolProperty m_savelightbuffersexternal;
    BoolProperty m_saveunpremultiplied;

    ImageIORegistration *m_iioreg{nullptr};
    bool m_isinited{false};
    bool m_rendertofile{false};

    NewOutputSettings() noexcept = default; //MyInit OR Init( *propertyinfo ) should be called by classes that contain this or when constructed with this constructor
    NewOutputSettings(const NewOutputSettings &other) {
        MyInit();
        HashCopyBits(&other);
        *this = other;
        SetPreferedIIO(other.m_iioreg); //NAP yves could probably just set member directly here, but I wanted an easy spot for a breakpoint for all sets
    }

/*
     NewOutputSettings(const NewOutputSettings &other) {
        MyInit();
        HashCopyBits(&other);
        *this = other;
        SetPreferedIIO(other.m_iioreg); //NAP yves could probably just set member directly here, but I wanted an easy spot for a breakpoint for all sets
    }

 */
    ~NewOutputSettings() override = default;

    NewOutputSettings &operator=(const NewOutputSettings &other) noexcept {
        if (this == &other)
            return *this;
        ContainerProperty::operator=(other);
        SetPreferedIIO(other.m_iioreg);
        m_rendertofile = other.m_rendertofile;
        return *this;
    }

    NewOutputSettings &operator=(NewOutputSettings &&other) noexcept {
        ContainerProperty::operator=(other);
        SetPreferedIIO(other.m_iioreg);
        m_rendertofile = other.m_rendertofile;
        return *this;
    }


    NewOutputSettings(NewOutputSettings &&other) = delete;

    void MyInit();
    void FormatToExtensionAndIIO();
    ImageIORegistration *GetImageIOReg();
    bool GetIsAlphaBuffer();
    void LoadPrefs(const String &key) override;
    void SetFormatFromExtension();

    [[nodiscard]] ImageIORegistration *GetPreferedIIO() const noexcept {
        return m_iioreg;
    }

    void SetPreferedIIO(ImageIORegistration *iioreg) noexcept {
        m_iioreg = iioreg;
    }

    Property *MakeCopy() noexcept override;
    void CopyProperty(const Property *prop) noexcept override;
    void CopyNoChildren(const Property *prop) noexcept override;
    void ShowVisibleProperties(Property *dueto = nullptr) noexcept override;
    void Init(PropertyInfo *propertyinfo, TreeObject *parent = nullptr, bool isnull = false, bool isloadpropertyinfo = false) override;
    Property *GetPropertyAt(int i) noexcept override;
    bool OnPtrMessage(PtrMessage ptrmessage, HashPtrObject **ptruplink, LONG_PTR lparam, Time time = Time(), bool storeundo = true) override;
};

class RenderFormatTypePropertyInfo final : public TypePropertyInfo {
public:
    RenderFormatTypePropertyInfo(const int index, const char *documentation, const int stringid, TypeInfo typearray[], const UINT count, const Label &label, const UINT defaultindex = 0, const DrawWhen drawwhen = DRAWALWAYS,
                                 const VisibleWhen visiblewhen = VISIBLEALWAYS, const UINT type = 0) noexcept : TypePropertyInfo(index, documentation, stringid, typearray, count, label, defaultindex, drawwhen, visiblewhen, type) {}

    bool Save(HashStream &hs, bool isforcesave) override;
    int ParseArg(HashStream &hs, HashStream &ms, int id) override;
};
