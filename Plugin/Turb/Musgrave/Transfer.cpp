// Yves 04/11/01  \Plugins\Turb\Musgrave\Transfer.cpp
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppClangTidyHicppMultiwayPathsCovered

#include "StdAfx.h"
#include "Custom.h"

TransfererUI::~TransfererUI() {
    delete m_OptionsInfo;
    delete m_WaveTypeInfo;
    delete m_CyclesInfo;
    delete m_TiltInfo;
    delete m_ShapeInfo;
    delete m_GainInfo;
    delete m_BiasInfo;
    delete m_HiCutoffInfo;
    delete m_LoCutoffInfo;
    delete m_SmoothInfo;
}

void TransfererUI::InitProperties() {
    CString string;

    string.LoadString(IDS_TRANSFEROPTIONS);
    m_OptionsInfo = HPropertyInfo::New(string, "TransferOptions");

    // Types of Waves
    m_WaveTypeInfoArray.SetArraySize(4);
    for (int i = 0; i < 4; i++) {
        HTypeInfo *typeinfo = m_WaveTypeInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("Linear");
                string.LoadString(IDS_T_LINEAR);
                break;
            case 1:
                typeinfo->SetMatchName("Triangular");
                string.LoadString(IDS_T_TRIANGULAR);
                break;
            case 2:
                typeinfo->SetMatchName("Sinusoidal");
                string.LoadString(IDS_T_SINUSOIDAL);
                break;
            case 3:
                typeinfo->SetMatchName("Rectangular");
                string.LoadString(IDS_T_RECTANGULAR);
                break;
        }
        typeinfo->SetLocalizedName(string.GetBuffer());
    }
    string.LoadString(IDS_WAVEFN);
    m_WaveTypeInfo = HTypePropertyInfo::New(string, "WaveFn", &m_WaveTypeInfoArray);
    m_WaveTypeInfo->SetDefaultIndex(0);
    m_WaveTypeInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Number of wave Cycles in the interval 0 to 1
    string.LoadString(IDS_CYCLES);
    m_CyclesInfo = HIntPropertyInfo::New(string, "Cycles");
    m_CyclesInfo->SetDefaultValue(1);
    m_CyclesInfo->SetMinValue(1);
    m_CyclesInfo->SetMaxValue(20);
    m_CyclesInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Wave Tilt [-1.0 .. 1.0] displayed in percent. 
    // Negative values shift center toward left
    // Positive values shift center toward right
    // 0.0 is symetrical shape. -1.0 is a descending sawtooth
    // 1.0 is a ascending sawtooth.
    string.LoadString(IDS_TILT);
    m_TiltInfo = HPercentPropertyInfo::New(string, "Tilt");
    m_TiltInfo->SetDefaultValue(0.F);
    m_TiltInfo->SetMinValue(-1.F);
    m_TiltInfo->SetMaxValue(1.F);
    m_TiltInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Wave Shape [-1.0 .. 1.0] displayed in percent.
    // Negative values gives coarse top of wave
    // Positive values gives coarse bottom of wave.
    string.LoadString(IDS_SHAPE);
    m_ShapeInfo = HPercentPropertyInfo::New(string, "Shape");
    m_ShapeInfo->SetDefaultValue(0.F);
    m_ShapeInfo->SetMinValue(-1.F);
    m_ShapeInfo->SetMaxValue(1.F);
    m_ShapeInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Output Gain
    string.LoadString(IDS_GAIN);
    m_GainInfo = HPercentPropertyInfo::New(string, "Gain");
    m_GainInfo->SetDefaultValue(1.F);
    m_GainInfo->SetMinValue(0.F);
    m_GainInfo->SetMaxValue(1000.F);
    m_GainInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Output Bias
    string.LoadString(IDS_BIAS);
    m_BiasInfo = HPercentPropertyInfo::New(string, "Bias");
    m_BiasInfo->SetDefaultValue(0.F);
    m_BiasInfo->SetMinValue(-100.F);
    m_BiasInfo->SetMaxValue(100.F);
    m_BiasInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Output High Cutoff
    string.LoadString(IDS_HICUTOFF);
    m_HiCutoffInfo = HPercentPropertyInfo::New(string, "Gain");
    m_HiCutoffInfo->SetDefaultValue(1.F);
    m_HiCutoffInfo->SetMinValue(0.F);
    m_HiCutoffInfo->SetMaxValue(1.F);
    m_HiCutoffInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Output Low Cutoff
    string.LoadString(IDS_LOCUTOFF);
    m_LoCutoffInfo = HPercentPropertyInfo::New(string, "Gain");
    m_LoCutoffInfo->SetDefaultValue(0.F);
    m_LoCutoffInfo->SetMinValue(0.F);
    m_LoCutoffInfo->SetMaxValue(1.F);
    m_LoCutoffInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    // Smoothen output values
    string.LoadString(IDS_SMOOTH);
    m_SmoothInfo = HBoolPropertyInfo::New(string, "Smooth");
    m_SmoothInfo->SetDefaultValue(TRUE);
    m_SmoothInfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);
}

Transferer::~Transferer() {
    if (m_WaveType) {
        if (m_Options)
            m_Options->RemoveProperty(m_WaveType);
        delete m_WaveType;
    }
    if (m_Cycles) {
        if (m_Options)
            m_Options->RemoveProperty(m_Cycles);
        delete m_Cycles;
    }
    if (m_Tilt) {
        if (m_Options)
            m_Options->RemoveProperty(m_Tilt);
        delete m_Tilt;
    }
    if (m_Shape) {
        if (m_Options)
            m_Options->RemoveProperty(m_Shape);
        delete m_Shape;
    }
    if (m_Gain) {
        if (m_Options)
            m_Options->RemoveProperty(m_Gain);
        delete m_Gain;
    }
    if (m_Bias) {
        if (m_Options)
            m_Options->RemoveProperty(m_Bias);
        delete m_Bias;
    }
    if (m_HiCutoff) {
        if (m_Options)
            m_Options->RemoveProperty(m_HiCutoff);
        delete m_HiCutoff;
    }
    if (m_LoCutoff) {
        if (m_Options)
            m_Options->RemoveProperty(m_LoCutoff);
        delete m_LoCutoff;
    }
    if (m_Smooth) {
        if (m_Options)
            m_Options->RemoveProperty(m_Smooth);
        delete m_Smooth;
    }

    delete m_Options;
}

void Transferer::LinkProperties(const TransfererUI &UI) {
    m_Options = HCategoryProperty::New(UI.m_OptionsInfo);
    m_WaveType = HTypeProperty::New(UI.m_WaveTypeInfo);
    m_Options->AddProperty(m_WaveType);
    m_Cycles = HIntProperty::New(UI.m_CyclesInfo);
    m_Options->AddProperty(m_Cycles);
    m_Tilt = HPercentProperty::New(UI.m_TiltInfo);
    m_Options->AddProperty(m_Tilt);
    m_Shape = HPercentProperty::New(UI.m_ShapeInfo);
    m_Options->AddProperty(m_Shape);
    m_Gain = HPercentProperty::New(UI.m_GainInfo);
    m_Options->AddProperty(m_Gain);
    m_Bias = HPercentProperty::New(UI.m_BiasInfo);
    m_Options->AddProperty(m_Bias);
    m_HiCutoff = HPercentProperty::New(UI.m_HiCutoffInfo);
    m_Options->AddProperty(m_HiCutoff);
    m_LoCutoff = HPercentProperty::New(UI.m_LoCutoffInfo);
    m_Options->AddProperty(m_LoCutoff);
    m_Smooth = HBoolProperty::New(UI.m_SmoothInfo);
    m_Options->AddProperty(m_Smooth);
}

// ReSharper disable once CppMemberFunctionMayBeConst
HProperty *Transferer::GetPropertyAt(int &i) {
    if (i == 0)
        return m_Options;
    i--;
    return nullptr;
}

// ReSharper disable once CppMemberFunctionMayBeConst
bool Transferer::ParseArg(const char *label, const char *value) {
    // pre 9.0 backward compatibility
    if (_stricmp(label, "GainBias") == 0) {
        float gain, bias;
        [[maybe_unused]] int temp = sscanf_s(value, "%f %f", &gain, &bias);
        m_Gain->SetValue(gain);
        m_Bias->SetValue(bias);
        return true;
    }
    if (_stricmp(label, "LoHiCutoff") == 0) {
        float locutoff, hicutoff;
        int smooth;
        [[maybe_unused]] int temp = sscanf_s(value, "%f %f %d", &locutoff, &hicutoff, &smooth);
        m_LoCutoff->SetValue(locutoff);
        m_HiCutoff->SetValue(hicutoff);
        m_Smooth->SetValue(smooth != 0);
        return true;
    }
    return false;
}

float Transferer::Transfer(float Value) const {
    switch (m_WaveType->GetValue()) {
        case 1:
            Value = TriangularWave(Value);
            break;
        case 2:
            Value = SinusoidalWave(Value);
            break;
        case 3:
            Value = RectangularWave(Value);
            break;
    }
    Value = (Value + m_Bias->GetValue() - 0.5F) * m_Gain->GetValue() + 0.5F;
    const float lo = m_LoCutoff->GetValue();
    const float hi = m_HiCutoff->GetValue();
    if (Value < lo)
        return 0.F;
    if (Value > hi)
        return 1.F;
    Value = (Value - lo) / (hi - lo);
    if (m_Smooth->GetValue())
        Value = Value * Value * (3.F - 2.F * Value);
    return Value;
}

// The following 3 wave functions are inspired by Christophe Schlick
// "Wave Generators for Computer Graphics" in Graphics Gems V, 
// Academic Press, 1995, pp 367-374.

float Transferer::TriangularWave(float Value) const {
    // Value is input in [0.0,1.0]
    Value *= m_Cycles->GetValue();
    const int i = (int)floor(Value);
    Value -= i;
    // Tilt is entered in [-1.0:+1.0] and must be scaled in [0.0,1.0]
    const float Tilt = m_Tilt->GetValue() / 2.F + .5F;
    if (Value <= Tilt)
        if (Tilt != 0.F)
            Value /= Tilt;
        else
            return 1.F;
    else if (Tilt != 1.F)
        Value = (.5F - (Value - .5F)) / (1.F - Tilt);
    else
        return 0.F;
    const float Shape = m_Shape->GetValue();
    if (Shape < 0.F)
        return (Value + Shape * Value) / (1.F + Shape * Value);
    if (Shape > 0.F)
        return Value / (1.F - Shape + Shape * Value);
    return Value;
}

float Transferer::RectangularWave(float Value) const {
    Value = TriangularWave(Value);
//	Value = Value < 0.5F ? 0.F : 1.F;
    // Smooth Square wave.
    Value = (Value - .5F) * 10.F - .5F;
    Value = Value < 0.F ? 0.F : Value > 1.F ? 1.F : Value;
    Value *= Value * (3.F - Value - Value);
    return Value;
}

float Transferer::SinusoidalWave(float Value) const {
    Value = TriangularWave(Value);
    Value *= Value * (3.F - Value - Value);
    return Value;
}
