// Dan  11/26/2001  \Dan90\Plugin\Textures\Lake\Construc.cpp

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
    m_useback = HBoolProperty::New(theApp.m_usebackinfo);
    m_bcolor = HColorProperty::New(theApp.m_bcolorinfo);
    m_fcolor = HColorProperty::New(theApp.m_fcolorinfo);
    m_bref = HFloatProperty::New(theApp.m_brefinfo);
    m_bo = HFloatProperty::New(theApp.m_boinfo);
    m_fref = HFloatProperty::New(theApp.m_frefinfo);
    m_fo = HFloatProperty::New(theApp.m_foinfo);
    m_noise = HFloatProperty::New(theApp.m_noiseinfo);
    m_bump = HFloatProperty::New(theApp.m_bumpinfo);
    m_amplitude = HFloatProperty::New(theApp.m_amplitudeinfo);
    m_mix = HFloatProperty::New(theApp.m_mixinfo);
    m_offset = HTranslateProperty::New(theApp.m_offsetinfo);
    m_scale = HScaleProperty::New(theApp.m_scaleinfo);
    m_wo = HFloatProperty::New(theApp.m_woinfo);
    m_wamp = HFloatProperty::New(theApp.m_wampinfo);
    m_wlac = HFloatProperty::New(theApp.m_wlacinfo);
    m_wgain = HFloatProperty::New(theApp.m_wgaininfo);
}

CustomTexture::~CustomTexture() {
    delete m_useback;
    delete m_bcolor;
    delete m_fcolor;
    delete m_bref;
    delete m_bo;
    delete m_fref;
    delete m_fo;
    delete m_noise;
    delete m_bump;
    delete m_amplitude;
    delete m_mix;
    delete m_offset;
    delete m_scale;
    delete m_wo;
    delete m_wamp;
    delete m_wlac;
    delete m_wgain;
}
