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
    m_size = HScaleProperty::New(theApp.m_sizeinfo);
    m_bump = HFloatProperty::New(theApp.m_bumpinfo);
    m_freq = HFloatProperty::New(theApp.m_freqinfo);
    m_ampl = HFloatProperty::New(theApp.m_amplinfo);
    m_octaves = HIntProperty::New(theApp.m_octavesinfo);
    m_weight = HFloatProperty::New(theApp.m_weightinfo);
    m_seed = HFloatProperty::New(theApp.m_seedinfo);
}

CustomTexture::~CustomTexture() {
    delete m_size;
    delete m_bump;
    delete m_freq;
    delete m_ampl;
    delete m_weight;
    delete m_seed;
    delete m_octaves;
}
