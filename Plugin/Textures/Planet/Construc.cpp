// Dan  11/26/2001  \Dan90\Plugin\Textures\Planet\Construc.cpp

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
    m_featuresize = HFloatProperty::New(theApp.m_featuresizeinfo);
    m_polardist = HFloatProperty::New(theApp.m_polardistinfo);
    m_water = HFloatProperty::New(theApp.m_waterinfo);
    m_bump = HFloatProperty::New(theApp.m_bumpinfo);
    m_ice = HFloatProperty::New(theApp.m_iceinfo);
    m_freq = HFloatProperty::New(theApp.m_freqinfo);
    m_ampl = HFloatProperty::New(theApp.m_amplinfo);
    m_octaves = HFloatProperty::New(theApp.m_octavesinfo);
    m_noisemult = HFloatProperty::New(theApp.m_noisemultinfo);
    m_seed = HFloatProperty::New(theApp.m_seedinfo);
    m_offset = HFloatProperty::New(theApp.m_offsetinfo);
    m_mottlesize = HFloatProperty::New(theApp.m_mottlesizeinfo);
    m_mottlemag = HFloatProperty::New(theApp.m_mottlemaginfo);
    m_depthnoise = HFloatProperty::New(theApp.m_depthnoiseinfo);
    m_maxdepth = HFloatProperty::New(theApp.m_maxdepthinfo);
    m_snow = HFloatProperty::New(theApp.m_snowinfo);
}

CustomTexture::~CustomTexture() {
    delete m_featuresize;
    delete m_polardist;
    delete m_water;
    delete m_ice;
    delete m_bump;
    delete m_freq;
    delete m_ampl;
    delete m_octaves;
    delete m_noisemult;
    delete m_seed;
    delete m_offset;
    delete m_mottlesize;
    delete m_mottlemag;
    delete m_depthnoise;
    delete m_maxdepth;
    delete m_snow;
}
