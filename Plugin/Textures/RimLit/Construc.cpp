// Dan  11/26/2001  \Dan90\Plugin\Textures\RimLit\Construc.cpp

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
    m_bcolor = HColorProperty::New(theApp.m_bcolorinfo);
    m_light = HVectorProperty::New(theApp.m_lightinfo);
    m_fo = HFloatProperty::New(theApp.m_foinfo);
    m_mix = HFloatProperty::New(theApp.m_mixinfo);

}

CustomTexture::~CustomTexture() {
    delete m_bcolor;
    delete m_light;
    delete m_fo;
    delete m_mix;
}
