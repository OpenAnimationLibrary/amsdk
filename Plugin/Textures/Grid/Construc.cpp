// Dan  11/26/2001  \Dan90\Plugin\Textures\Grid\Construc.cpp

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
    m_lcolor = HColorProperty::New(theApp.m_lcolorinfo);
    m_transp = HFloatProperty::New(theApp.m_transpinfo);
    m_gtype = HTypeProperty::New(theApp.m_gtypeinfo);
    m_origin = HVectorProperty::New(theApp.m_origininfo);
    m_width = HVectorProperty::New(theApp.m_widthinfo);
    m_interval = HVectorProperty::New(theApp.m_intervalinfo);
}

CustomTexture::~CustomTexture() {
    delete m_lcolor;
    delete m_transp;
    delete m_gtype;
    delete m_origin;
    delete m_width;
    delete m_interval;
}
