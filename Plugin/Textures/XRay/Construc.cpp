// Dan  11/26/2001  \Dan90\Plugin\Textures\XRay\Construc.cpp

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
    m_bo = HFloatProperty::New(theApp.m_boinfo);
    m_mix = HFloatProperty::New(theApp.m_mixinfo);
}

CustomTexture::~CustomTexture() {
    delete m_useback;
    delete m_bcolor;
    delete m_bo;
    delete m_mix;
}
