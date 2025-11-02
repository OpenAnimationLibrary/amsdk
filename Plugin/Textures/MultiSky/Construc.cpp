// Dan  11/26/2001  \Dan90\Plugin\Textures\MultiSky\Construc.cpp

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
    m_height = HFloatProperty::New(theApp.m_heightinfo);
    m_cover = HFloatProperty::New(theApp.m_coverinfo);
    m_octaves = HIntProperty::New(theApp.m_octavesinfo);
    m_haze = HFloatProperty::New(theApp.m_hazeinfo);
    m_sintensity = HFloatProperty::New(theApp.m_sintensityinfo);
    m_si = HBoolProperty::New(theApp.m_siinfo);
    m_trans = HFloatProperty::New(theApp.m_transinfo);
    m_type = HTypeProperty::New(theApp.m_typeinfo);
    m_sun = HVectorProperty::New(theApp.m_suninfo);
    m_offset = HTranslateProperty::New(theApp.m_offsetinfo);
    m_scale = HScaleProperty::New(theApp.m_scaleinfo);
    m_hcolor = HColorProperty::New(theApp.m_hcolorinfo);
    m_scolor = HColorProperty::New(theApp.m_scolorinfo);
    m_c1color = HColorProperty::New(theApp.m_c1colorinfo);
    m_c2color = HColorProperty::New(theApp.m_c2colorinfo);
    m_bcolor = HColorProperty::New(theApp.m_bcolorinfo);
}

CustomTexture::~CustomTexture() {
    delete m_hcolor;
    delete m_scolor;
    delete m_c1color;
    delete m_c2color;
    delete m_bcolor;
    delete m_trans;
    delete m_height;
    delete m_cover;
    delete m_octaves;
    delete m_haze;
    delete m_sintensity;
    delete m_type;
    delete m_si;
    delete m_sun;
    delete m_offset;
    delete m_scale;
}
