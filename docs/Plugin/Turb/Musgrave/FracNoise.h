// Yves 04/11/01  \Plugins\Turb\Musgrave\FracNoise.h
#pragma once

#define MAX_OCTAVES 20

class FractalNoiseUI {
public:
    TypeInfoArray m_TurbTypeInfoArray;
    HPropertyInfo *m_OptionsInfo;
    HTypePropertyInfo *m_TurbTypeInfo;
    HIntPropertyInfo *m_OctavesInfo;
    HFloatPropertyInfo *m_LacunarityInfo;
    HFloatPropertyInfo *m_DimensionInfo;
    HPercentPropertyInfo *m_OffsetInfo;
    HPercentPropertyInfo *m_SharpnessInfo;
    HPercentPropertyInfo *m_PerturbInfo;
    TypeInfoArray m_BlendTypeInfoArray;
    HTypePropertyInfo *m_BlendTypeInfo;

    FractalNoiseUI() noexcept = default;
    ~FractalNoiseUI();

    FractalNoiseUI(const FractalNoiseUI&) = delete;
    FractalNoiseUI &operator= (const FractalNoiseUI&) = delete; 
    FractalNoiseUI(FractalNoiseUI &&) = delete; 
    FractalNoiseUI &operator=(FractalNoiseUI &&) = delete;

    void InitProperties();
};

class FractalNoise {
public:
    HCategoryProperty *m_Options{nullptr};
    HTypeProperty *m_TurbType{nullptr};
    HIntProperty *m_Octaves{nullptr};
    HFloatProperty *m_Lacunarity{nullptr};
    HFloatProperty *m_Dimension{nullptr};
    HFloatProperty *m_Offset{nullptr};
    HFloatProperty *m_Sharpness{nullptr};
    HFloatProperty *m_Perturb{nullptr};
    HTypeProperty *m_BlendType{nullptr};

    float m_Weight[MAX_OCTAVES]{};
    float a{0};
    float m_Max{0};
    int m_Mode{0};
    int m_i{0};
    FractalNoise *m_CopyOf{nullptr};
    bool m_WeightsDirty{false};

    FractalNoise() noexcept = default;
    ~FractalNoise();

    FractalNoise(const FractalNoise&) = delete;
    FractalNoise &operator= (const FractalNoise&) = delete; 
    FractalNoise(FractalNoise &&) = delete; 
    FractalNoise &operator=(FractalNoise &&) = delete;

    void LinkProperties(const FractalNoiseUI &UI);
    HProperty *GetPropertyAt(int &i);
    bool ParseArg(const char *label, const char *value);
    bool OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, Time time);
    void BuildWeights();
    float Evaluate(const Vector &evalp);
    // FractalTurb returns a value between 0.0 and 1.0 defined in exports

    float FractalSum(const Vector &p);
    float fPerlin(const Vector &p);
    float Perlin(const Vector &p);
    float fSine(const Vector &p);
    float Sine(const Vector &p);
    float fBM(const Vector &p);
    float VLfBM(const Vector &p);
    float HeteroFractal(const Vector &p);
    float HybridFractal(const Vector &p);
    float RidgedFractal(const Vector &p);
    float Blend(float b);

    [[nodiscard]] float Value() const {
        return a / m_Max;
    }

    void Copy(const FractalNoise &other);
    bool IsUpdateWeights(HProperty *dueto) const;
};
