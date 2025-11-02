// Yves  2005-11-22  \Master13.0\Plugin\Shaders\PlanetGlow\Construc.cpp

#include "StdAfx.h"
#include "Shader.h"
#include "Custom.h"

extern CShaderApp theApp;

extern "C" __declspec(dllexport) Shader *CreateShader(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomShader(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return SHADERDLLVERSION;
}

CustomShader::CustomShader(HTreeObject *treeobject) : Shader(treeobject) {
    m_Falloff = HPercentProperty::New(theApp.m_FalloffInfo);
    m_Glow = HPercentProperty::New(theApp.m_GlowInfo);
    m_Fade = HPercentProperty::New(theApp.m_FadeInfo);
    m_Xparency = HPercentProperty::New(theApp.m_XparencyInfo);
    m_LoColor = HColorProperty::New(theApp.m_LoColorInfo);
    m_HiColor = HColorProperty::New(theApp.m_HiColorInfo);
}

CustomShader::~CustomShader() {
    delete m_Falloff;
    delete m_Glow;
    delete m_Fade;
    delete m_Xparency;
    delete m_LoColor;
    delete m_HiColor;
}

// Pre v9.0 files compatibility
bool CustomShader::ParseArg(const char *label, const char *value) {
    float data;
    float red, green, blue;

    if (strcmp(label, "PlanetFallOff") == 0) {
        [[maybe_unused]] int temp = sscanf_s(value, "%f", &data);
        m_Falloff->SetValue(data);
        return true;
    }
    if (strcmp(label, "PlanetGlow") == 0) {
        [[maybe_unused]] int temp = sscanf_s(value, "%f", &data);
        m_Glow->SetValue(data);
        return true;
    }
    if (strcmp(label, "PlanetFade") == 0) {
        [[maybe_unused]] int temp = sscanf_s(value, "%f", &data);
        m_Fade->SetValue(data);
        return true;
    }
    if (strcmp(label, "PlanetTransparency") == 0) {
        [[maybe_unused]] int temp = sscanf_s(value, "%f", &data);
        m_Xparency->SetValue(data);
        return true;
    }
    if (strcmp(label, "PlanetHiColor") == 0) {
        [[maybe_unused]] int temp = sscanf_s(value, "%f %f %f", &red, &green, &blue);
        m_HiColor->SetValue(RGBFloat(red, green, blue));
        return true;
    }
    if (strcmp(label, "PlanetLowColor") == 0) {
        [[maybe_unused]] int temp = sscanf_s(value, "%f %f %f", &red, &green, &blue);
        m_LoColor->SetValue(RGBFloat(red, green, blue));
        return true;
    }
    return false;
}
