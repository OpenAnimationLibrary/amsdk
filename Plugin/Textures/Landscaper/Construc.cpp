// Dan  11/26/2001  \Dan90\Plugin\Textures\Landscaper\Construc.cpp

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
    m_fcolor1 = HColorProperty::New(theApp.m_fcolor1info);
    m_fcolor2 = HColorProperty::New(theApp.m_fcolor2info);
    m_fcolor3 = HColorProperty::New(theApp.m_fcolor3info);
    m_foct = HFloatProperty::New(theApp.m_foctinfo);
    m_ffreq = HFloatProperty::New(theApp.m_ffreqinfo);
    m_scolor1 = HColorProperty::New(theApp.m_scolor1info);
    m_scolor2 = HColorProperty::New(theApp.m_scolor2info);
    m_scolor3 = HColorProperty::New(theApp.m_scolor3info);
    m_soct = HFloatProperty::New(theApp.m_soctinfo);
    m_sfreq = HFloatProperty::New(theApp.m_sfreqinfo);
    m_sbump = HFloatProperty::New(theApp.m_sbumpinfo);
    m_falloff = HFloatProperty::New(theApp.m_falloffinfo);
    m_offset = HTranslateProperty::New(theApp.m_offsetinfo);
    m_scale = HScaleProperty::New(theApp.m_scaleinfo);
    m_height = HFloatProperty::New(theApp.m_heightinfo);
    m_aslope = HTypeProperty::New(theApp.m_aslopeinfo);
    m_fnt = HTypeProperty::New(theApp.m_fntinfo);
    m_snt = HTypeProperty::New(theApp.m_sntinfo);
}

CustomTexture::~CustomTexture() {
    delete m_fcolor1;
    delete m_fcolor2;
    delete m_fcolor3;
    delete m_foct;
    delete m_ffreq;
    delete m_scolor1;
    delete m_scolor2;
    delete m_scolor3;
    delete m_soct;
    delete m_sfreq;
    delete m_sbump;
    delete m_falloff;
    delete m_offset;
    delete m_scale;
    delete m_height;
    delete m_aslope;
    delete m_fnt;
    delete m_snt;
}
