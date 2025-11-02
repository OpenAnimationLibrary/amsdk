// Dan  11/26/2001  \Dan90\Plugin\Textures\Scales\Construc.cpp

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
    m_size = HVectorProperty::New(theApp.m_sizeinfo);
    m_bump = HFloatProperty::New(theApp.m_bumpinfo);
    m_edge = HFloatProperty::New(theApp.m_edgeinfo);
    m_valley = HFloatProperty::New(theApp.m_valleyinfo);
    m_rounding = HFloatProperty::New(theApp.m_roundinginfo);
    m_seed = HFloatProperty::New(theApp.m_seedinfo);
    m_slope1 = HFloatProperty::New(theApp.m_slope1info);
    m_slope2 = HFloatProperty::New(theApp.m_slope2info);
}

CustomTexture::~CustomTexture() {
    delete m_size;
    delete m_bump;
    delete m_edge;
    delete m_valley;
    delete m_rounding;
    delete m_seed;
    delete m_slope1;
    delete m_slope2;
}
