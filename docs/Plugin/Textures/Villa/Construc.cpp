// Dan  11/26/2001  \Dan90\Plugin\Textures\Villa\Construc.cpp

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
    m_noise = HFloatProperty::New(theApp.m_noiseinfo);
    m_freq = HFloatProperty::New(theApp.m_freqinfo);
    m_fo = HFloatProperty::New(theApp.m_foinfo);
    m_bo = HBoolProperty::New(theApp.m_boinfo);
 //   m_ir = HBoolProperty::New(theApp.m_irinfo);
}

CustomTexture::~CustomTexture() {
    delete m_noise;
    delete m_freq;
    delete m_bo;
    delete m_fo;
//    delete m_ir;
}
