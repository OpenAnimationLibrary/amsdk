// Dan  11/26/2001  \Dan90\Plugin\Textures\Eyeball\Construc.cpp

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
    m_freq = HFloatProperty::New(theApp.m_freqinfo);
    m_fref = HFloatProperty::New(theApp.m_frefinfo);
    m_fo = HFloatProperty::New(theApp.m_foinfo);
    m_bref = HFloatProperty::New(theApp.m_brefinfo);
    m_bo = HFloatProperty::New(theApp.m_boinfo);
    m_mix = HFloatProperty::New(theApp.m_mixinfo);
    m_offset = HTranslateProperty::New(theApp.m_offsetinfo);
    m_scale = HScaleProperty::New(theApp.m_scaleinfo);
    m_size = HFloatProperty::New(theApp.m_sizeinfo);
    m_sfreq = HFloatProperty::New(theApp.m_sfreqinfo);
    m_soft = HFloatProperty::New(theApp.m_softinfo);
}

CustomTexture::~CustomTexture() {
    delete m_bcolor;
    delete m_fcolor;
    delete m_freq;
    delete m_fref;
    delete m_fo;
    delete m_bref;
    delete m_bo;
    delete m_mix;
    delete m_offset;
    delete m_scale;
    delete m_size;
    delete m_sfreq;
    delete m_soft;
    delete m_useback;
}
