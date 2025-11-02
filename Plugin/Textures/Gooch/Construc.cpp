// Dan  11/26/2001  \Dan90\Plugin\Textures\Gooch\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TexApp.h"

extern CTextureApp theApp;

extern "C" __declspec(dllexport) Texture *CreateTexture(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomTexture(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return TEXTUREDLLVERSION;
}

CustomTexture::CustomTexture(HTreeObject *treeobject) : Texture(treeobject) {
    m_amplitude = HFloatProperty::New(theApp.m_amplitudeinfo);
    m_useback = HBoolProperty::New(theApp.m_usebackinfo);
    m_bcolor = HColorProperty::New(theApp.m_bcolorinfo);
    m_fcolor = HColorProperty::New(theApp.m_fcolorinfo);
    m_noise = HFloatProperty::New(theApp.m_noiseinfo);
    m_freq = HFloatProperty::New(theApp.m_freqinfo);
//    m_bump = HFloatProperty::New(theApp.m_bumpinfo);
    m_mix = HFloatProperty::New(theApp.m_mixinfo);
    m_scalex = HFloatProperty::New(theApp.m_scalexinfo);
    m_scaley = HFloatProperty::New(theApp.m_scaleyinfo);
    m_light = HVectorProperty::New(theApp.m_lightinfo);
}

CustomTexture::~CustomTexture() {
    delete m_amplitude;
    delete m_useback;
    delete m_bcolor;
    delete m_fcolor;
    delete m_noise;
    delete m_freq;
//    delete m_bump;
    delete m_mix;
    delete m_scalex;
    delete m_scaley;
    delete m_light;
}
