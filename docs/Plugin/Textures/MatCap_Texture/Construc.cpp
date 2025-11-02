// Dan  11/26/2001  \Dan90\Plugin\Textures\Crumple\Construc.cpp

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
//    m_intensity = HFloatProperty::New(theApp.m_intensityinfo);
    m_opacity = HFloatProperty::New(theApp.m_opacityinfo);
    m_additiv = HBoolProperty::New(theApp.m_additivinfo);
//    m_decal = HPointerProperty::New(theApp.m_decalinfo);
}

CustomTexture::~CustomTexture() {
    delete m_clip;
//    delete m_intensity;
    delete m_opacity;
    delete m_additiv;
//    delete m_decal;
}
