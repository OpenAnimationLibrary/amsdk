// Dan  11/26/2001  \Dan90\Plugin\Textures\Environment\Construc.cpp

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
    m_clip = HClipProperty::New(theApp.m_clipinfo);
    m_opacity = HFloatProperty::New(theApp.m_opacityinfo);
    m_isadditive = HBoolProperty::New(theApp.m_isadditiveinfo);
}

CustomTexture::~CustomTexture() {
    delete m_clip;
    delete m_opacity;
    delete m_isadditive;
}
