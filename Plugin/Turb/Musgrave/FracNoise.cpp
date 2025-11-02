// Yves 04/11/01  \Plugins\Turb\Musgrave\FracNoise.cpp
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered

#include "StdAfx.h"
#include "Custom.h"
#include "Perlin.h"

FractalNoiseUI::~FractalNoiseUI() {
    delete m_OptionsInfo;
    delete m_TurbTypeInfo;
    delete m_OctavesInfo;
    delete m_LacunarityInfo;
    delete m_DimensionInfo;
    delete m_OffsetInfo;
    delete m_SharpnessInfo;
    delete m_PerturbInfo;
    delete m_BlendTypeInfo;
}

void FractalNoiseUI::InitProperties() {
    HTypeInfo *typeinfo;
    CString string;
    int i;

    string.LoadString(IDS_FRACTOPTIONS);
    m_OptionsInfo = HPropertyInfo::New(string, "NoiseOptions");

    // Types of noises and fractalizations
    m_TurbTypeInfoArray.SetArraySize(10);
    for (i = 0; i < 10; i++) {
        typeinfo = m_TurbTypeInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("Fractal Sum");
                string.LoadString(IDS_N_FRACSUM);
                break;
            case 1:
                typeinfo->SetMatchName("Perlin");
                string.LoadString(IDS_N_PERLIN);
                break;
            case 2:
                typeinfo->SetMatchName("Fractal Perlin");
                string.LoadString(IDS_N_FRACPERLIN);
                break;
            case 3:
                typeinfo->SetMatchName("Sine");
                string.LoadString(IDS_N_SINE);
                break;
            case 4:
                typeinfo->SetMatchName("Fractal Sine");
                string.LoadString(IDS_N_FRACSINE);
                break;
            case 5:
                typeinfo->SetMatchName("fBM");
                string.LoadString(IDS_N_FBM);
                break;
            case 6:
                typeinfo->SetMatchName("VL fBM");
                string.LoadString(IDS_N_VLFBM);
                break;
            case 7:
                typeinfo->SetMatchName("Hetero Multifractal");
                string.LoadString(IDS_N_HETEROMF);
                break;
            case 8:
                typeinfo->SetMatchName("Hybrid Multifractal");
                string.LoadString(IDS_N_HYBRIDMF);
                break;
            case 9:
                typeinfo->SetMatchName("Ridged Multifractal");
                string.LoadString(IDS_N_RIDGEDMF);
                break;
        }
        typeinfo->SetLocalizedName(string.GetBuffer());
    }
    string.LoadString(IDS_NOISEFN);
    m_TurbTypeInfo = HTypePropertyInfo::New(string, "NoiseFn", &m_TurbTypeInfoArray);
    m_TurbTypeInfo->SetDefaultIndex(0);
    m_TurbTypeInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Number of octave of fractalization
    string.LoadString(IDS_OCTAVES);
    m_OctavesInfo = HIntPropertyInfo::New(string, "Octaves");
    m_OctavesInfo->SetDefaultValue(1);
    m_OctavesInfo->SetMinValue(1);
    m_OctavesInfo->SetMaxValue(20);
    m_OctavesInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Scale of each fractal layer pattern (1/x)
    string.LoadString(IDS_LACUNARITY);
    m_LacunarityInfo = HFloatPropertyInfo::New(string, "Lacunarity");
    m_LacunarityInfo->SetDefaultValue(2.F);
    m_LacunarityInfo->SetMinValue(0.F);
    m_LacunarityInfo->SetMaxValue(100.F);
    m_LacunarityInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Scale of each fractal layer amplitude
    string.LoadString(IDS_DIMENSIONS);
    m_DimensionInfo = HFloatPropertyInfo::New(string, "Dimensions");
    m_DimensionInfo->SetDefaultValue(1.F);
    m_DimensionInfo->SetMinValue(0.F);
    m_DimensionInfo->SetMaxValue(100.F);
    m_DimensionInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Offset for Hetero and Hybrid Multifractal only
    // Raises the see level but for each fractal layer individually.
    string.LoadString(IDS_OFFSET);
    m_OffsetInfo = HPercentPropertyInfo::New(string, "Offset");
    m_OffsetInfo->SetDefaultValue(1.F);
    m_OffsetInfo->SetMinValue(0.F);
    m_OffsetInfo->SetMaxValue(1.F);
    m_OffsetInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Sharpness for Ridged Multifractal only
    string.LoadString(IDS_SHARPNESS);
    m_SharpnessInfo = HPercentPropertyInfo::New(string, "Sharpness");
    m_SharpnessInfo->SetDefaultValue(1.F);
    m_SharpnessInfo->SetMinValue(0.F);
    m_SharpnessInfo->SetMaxValue(10.F);
    m_SharpnessInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Perturbation for fBm or VL fBm only.
    // Perturbation of 1.0 is equivalent to A:M's fBm
    string.LoadString(IDS_PERTURB);
    m_PerturbInfo = HPercentPropertyInfo::New(string, "Perturbation");
    m_PerturbInfo->SetDefaultValue(1.F);
    m_PerturbInfo->SetMinValue(0.F);
    m_PerturbInfo->SetMaxValue(10.F);
    m_PerturbInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    m_BlendTypeInfoArray.SetArraySize(9);
    for (i = 0; i < 9; i++) {
        typeinfo = m_BlendTypeInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("Add");
                string.LoadString(IDS_B_ADD);
                break;
            case 1:
                typeinfo->SetMatchName("Multiply");
                string.LoadString(IDS_B_MULTIPLY);
                break;
            case 2:
                typeinfo->SetMatchName("Darken");
                string.LoadString(IDS_B_DARKEN);
                break;
            case 3:
                typeinfo->SetMatchName("Lighten");
                string.LoadString(IDS_B_LIGHTEN);
                break;
            case 4:
                typeinfo->SetMatchName("Compress");
                string.LoadString(IDS_B_COMPRESS);
                break;
            case 5:
                typeinfo->SetMatchName("Expand");
                string.LoadString(IDS_B_EXPAND);
                break;
            case 6:
                typeinfo->SetMatchName("Exclusion");
                string.LoadString(IDS_B_EXCLUSION);
                break;
            case 7:
                typeinfo->SetMatchName("Soft Light");
                string.LoadString(IDS_B_SOFTLIGHT);
                break;
            case 8:
                typeinfo->SetMatchName("Dodge");
                string.LoadString(IDS_B_DODGE);
                break;
        }
        typeinfo->SetLocalizedName(string.GetBuffer());
    }
    string.LoadString(IDS_COMBINER);
    m_BlendTypeInfo = HTypePropertyInfo::New(string, "Blend Mode", &m_BlendTypeInfoArray);
    m_BlendTypeInfo->SetDefaultIndex(0);
    m_BlendTypeInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);
}

FractalNoise::~FractalNoise() {
    if (!m_Options)
        return;
    if (m_TurbType) {
        m_Options->RemoveProperty(m_TurbType);
        delete m_TurbType;
    }
    if (m_Octaves) {
        m_Options->RemoveProperty(m_Octaves);
        delete m_Octaves;
    }
    if (m_BlendType) {
        m_Options->RemoveProperty(m_BlendType);
        delete m_BlendType;
    }
    if (m_Lacunarity) {
        m_Options->RemoveProperty(m_Lacunarity);
        delete m_Lacunarity;
    }
    if (m_Dimension) {
        m_Options->RemoveProperty(m_Dimension);
        delete m_Dimension;
    }
    if (m_Offset) {
        m_Options->RemoveProperty(m_Offset);
        delete m_Offset;
    }
    if (m_Sharpness) {
        m_Options->RemoveProperty(m_Sharpness);
        delete m_Sharpness;
    }
    if (m_Perturb) {
        m_Options->RemoveProperty(m_Perturb);
        delete m_Perturb;
    }
    delete m_Options;
}

void FractalNoise::LinkProperties(const FractalNoiseUI &UI) {
    m_Options = HCategoryProperty::New(UI.m_OptionsInfo);
    if (!m_Options)
        return;
    m_TurbType = HTypeProperty::New(UI.m_TurbTypeInfo);
    m_Options->AddProperty(m_TurbType);
    m_Octaves = HIntProperty::New(UI.m_OctavesInfo);
    m_Options->AddProperty(m_Octaves);
    m_BlendType = HTypeProperty::New(UI.m_BlendTypeInfo);
    m_Options->AddProperty(m_BlendType);
    m_Lacunarity = HFloatProperty::New(UI.m_LacunarityInfo);
    m_Options->AddProperty(m_Lacunarity);
    m_Dimension = HFloatProperty::New(UI.m_DimensionInfo);
    m_Options->AddProperty(m_Dimension);
    m_Offset = HPercentProperty::New(UI.m_OffsetInfo);
    m_Options->AddProperty(m_Offset);
    m_Sharpness = HPercentProperty::New(UI.m_SharpnessInfo);
    m_Options->AddProperty(m_Sharpness);
    m_Perturb = HPercentProperty::New(UI.m_PerturbInfo);
    m_Options->AddProperty(m_Perturb);
    BuildWeights();
}

void FractalNoise::Copy(const FractalNoise &other) {
    m_CopyOf = (FractalNoise *)&other;
    m_Max = other.m_Max;
    for (int i = 0; i < MAX_OCTAVES; i++)
        m_Weight[i] = other.m_Weight[i];
}

// ReSharper disable once CppMemberFunctionMayBeConst
HProperty *FractalNoise::GetPropertyAt(int &i) {
    if (i == 0)
        return m_Options;
    i--;
    return nullptr;
}

bool FractalNoise::ParseArg(const char *label, const char *value) {
    // pre 9.0 backward compatibility
    if (_stricmp(label, "Octaves") == 0) {
        int octaves;
        [[maybe_unused]] int n1 = sscanf_s(value, "%d", &octaves);
        m_Octaves->SetValue(octaves);
        return true;
    }
    if (_stricmp(label, "TurbulenceType") == 0) {
        int turbtype;
        float lacunarity, dimension, offset, sharpness, perturb;
        [[maybe_unused]] int n1 = sscanf_s(value, "%d %f %f %f %f %f", &turbtype, &lacunarity, &dimension, &offset, &sharpness, &perturb);
        m_TurbType->SetValue(turbtype);
        m_Lacunarity->SetValue(lacunarity);
        m_Dimension->SetValue(dimension);
        m_Offset->SetValue(offset);
        m_Sharpness->SetValue(sharpness);
        m_Perturb->SetValue(perturb);
        BuildWeights();
        return true;
    }
    return false;
}

bool FractalNoise::IsUpdateWeights(HProperty *dueto) const {
    if (dueto == (HProperty *)m_Octaves || dueto == (HProperty *)m_Dimension || dueto == (HProperty *)m_Lacunarity || dueto == (HProperty *)m_BlendType)
        return true;
    if (m_CopyOf && m_CopyOf->IsUpdateWeights(dueto))
        return true;
    return false;
}

bool FractalNoise::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, Time time) {
    // ReSharper disable once CppIncompleteSwitchStatement
    switch (ptrmessage) {
        case PTM_ENDLOAD:
        case PTM_VALUECHANGED:
        case PTM_VALUESTORED:
        {
            if (IsUpdateWeights((HProperty *)lparam))
                m_WeightsDirty = true;
            return TRUE;
        }
    default:
        return FALSE;
    }
}

float FractalNoise::Evaluate(const Vector &evalp) {
    if (m_WeightsDirty)
        BuildWeights();
    float Value;
    const Vector p = evalp;
    m_Mode = m_BlendType->GetValue();
    switch (m_TurbType->GetValue()) {
        case 0:		// FractalSum
            Value = FractalSum(p);
            break;
        case 1:		// Perlin
            Value = Perlin(p);
            break;
        case 2:		// Fractal Perlin
            Value = fPerlin(p);
            break;
        case 3:		// Sine
            Value = Sine(p);
            break;
        case 4:		// Fractal Sine
            Value = fSine(p);
            break;
        case 5:		// fBM
            Value = fBM(p);
            break;
        case 6:
            Value = VLfBM(p);
            break;
        case 7:
            Value = HeteroFractal(p);
            break;
        case 8:
            Value = HybridFractal(p);
            break;
        case 9:
            Value = RidgedFractal(p);
            break;
        default:
            Value = FractalSum(p);
    }
    return Value;
}

float FractalNoise::fBM(const Vector &p) {
    Vector Delta = p;
    Delta += 0.5F;
    Perturb(Delta, Delta);
    Delta = Delta * m_Perturb->GetValue() + p;
    const float Lacunarity = m_Lacunarity->GetValue();
    const int Octaves = m_Octaves->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        Blend(Noise3(Delta) * m_Weight[m_i]);
        Delta *= Lacunarity;
    }
    return Value() + 0.5F;
}

float FractalNoise::VLfBM(const Vector &p) {
    float Freq = 1.F;
    const float Lacunarity = m_Lacunarity->GetValue();
    const float Perturb = m_Perturb->GetValue();
    const int Octaves = m_Octaves->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        Vector Delta = p * Freq + 0.5F;
        ::Perturb(Delta, Delta);
        Delta = Delta * Freq * Perturb + p;
        Blend(Noise3(Delta) * m_Weight[m_i]);
        Freq *= Lacunarity;
    }
    return Value() + 0.5F;
}

// NOTE: Hetero Hybrid Multifractal are not coded the same way as 
// in Kenton. They are a simple transformation of the original.
// They are equivalent and have better normalized output.
// Furthermore, at octave=1, they output simply Noise3 as value
// which is consistent with the other fractal implementations.

float FractalNoise::HeteroFractal(const Vector &p) {
    float Freq = 1.F;
    float Height = 1.F;
    const float Offset = (m_Offset->GetValue() - 0.5F) * 2.F;
    const float Lacunarity = m_Lacunarity->GetValue();
    const int Octaves = m_Octaves->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        Blend(Noise3(p * Freq) * m_Weight[m_i] * Height);
        Height = (Offset - a) * 2.F;
        Freq *= Lacunarity;
    }
    return Value() + 0.5F;
}

float FractalNoise::HybridFractal(const Vector &p) {
    float Weight = 1.F;
    float Freq = 1.F;
    const float Lacunarity = m_Lacunarity->GetValue();
    const int Octaves = m_Octaves->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        const float Signal = Noise3(p * Freq) * m_Weight[m_i];
        Blend(Signal * Weight);
        Weight *= Signal + 0.5F;
        Freq *= Lacunarity;
    }
    return Value() + 0.5F;
}

float FractalNoise::RidgedFractal(const Vector &p) {
    float Weight = 1.F;
    float Freq = 1.F;
    const float Lacunarity = m_Lacunarity->GetValue();
    const float Sharpness = m_Sharpness->GetValue();
    const int Octaves = m_Octaves->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        constexpr float Gain = 2.F;
        float Signal = Noise3(p * Freq) * 2.F;
        Signal = Signal < 0.F ? 1.F + Signal : 1.F - Signal;
        Signal = hash_math::pow(Signal, Sharpness) * Weight;
        Blend(Signal * m_Weight[m_i]);
        Weight = Signal * Gain;
        Weight = MIN(1.F, MAX(0.F, Weight));
        Freq *= Lacunarity;
    }
    return Value();// + 0.5F ;
}

float FractalNoise::FractalSum(const Vector &p) {
    float Freq = 1.F;
    const float Lacunarity = m_Lacunarity->GetValue();
    const int Octaves = m_Octaves->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        const float Noise = Noise3(p * Freq);
        Blend(Noise * m_Weight[m_i]);
        Freq *= Lacunarity;
    }
    return Value() + 0.5F;
}

float FractalNoise::Perlin(const Vector &p) {
    float Freq = 1.F;
    const float Lacunarity = m_Lacunarity->GetValue();
    const int Octaves = m_Octaves->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        Blend((float)fabs(Noise3(p * Freq) * m_Weight[m_i] * 2.0));
        Freq *= Lacunarity;
    }
    return Value();
}

float FractalNoise::Sine(const Vector &p) {
    float Freq = 1.F;
    const float Lacunarity = m_Lacunarity->GetValue();
    const int Octaves = m_Octaves->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        Blend((float)sin(Noise3(p * Freq) * 6.283185307) * m_Weight[m_i]);
        Freq *= Lacunarity;
    }
    return Value() * -0.5F + 0.5F;
}

float FractalNoise::fPerlin(const Vector &p) {
    return hash_math::abs(FractalSum(p) * 2.F - 1.F);
}

float FractalNoise::fSine(const Vector &p) {
    return hash_math::sin((double)FractalSum(p) * 6.283185307) * 0.5F + 0.5F;
}

void FractalNoise::BuildWeights() {
    float Freq = 1.F;
    const int Octaves = m_Octaves->GetValue();
    const float Dimension = m_Dimension->GetValue();   // 1.F
    const float Lacunarity = m_Lacunarity->GetValue(); // 2.F
    for (m_i = 0; m_i < Octaves; m_i++) {
        m_Weight[m_i] = hash_math::pow(Freq, -1.F / Dimension);
        Freq *= Lacunarity;
    }
    m_Mode = m_BlendType->GetValue();
    for (m_i = 0; m_i < Octaves; m_i++) {
        Blend(m_Weight[m_i]);
    }
    m_Max = a;
    m_WeightsDirty = TRUE;
}

float FractalNoise::Blend(const float b) {
    if (!m_i) {
        a = b;
        return a;
    }
    switch (m_Mode + IDS_B_ADD) {
        case IDS_B_ADD:
            a = a + b;
            return a;
        case IDS_B_MULTIPLY:
            a = a * b;
            return a;
        case IDS_B_DARKEN:
            a = a < b ? a : b;
            return a;
        case IDS_B_LIGHTEN:
            a = a > b ? a : b;
            return a;
        case IDS_B_COMPRESS:
            if (a >= 0.F)
                a = fabs(b) < fabs(a) ? b : a;
            else
                a = fabs(b) > fabs(a) ? b : a;
            return a;
        case IDS_B_EXPAND:
            if (a >= 0.F)
                a = a > b ? a : b;
            else
                a = a < b ? a : b;
            return a;
        case IDS_B_EXCLUSION:
            a = a + b - 2.F * a * b;
            return a;
        case IDS_B_SOFTLIGHT:
            a = 2.F * a * b + a * a - 2.F * a * a * b;
            return a;
        case IDS_B_DODGE:
            a = (a + 0.5F) / (1.F - b) - 0.5F;
            return a;
    }
    a = a + b;
    return a;
}
