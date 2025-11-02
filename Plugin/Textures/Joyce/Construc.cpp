// RC  1/28/2002  \HRandy90\Plugin\Textures\Joyce\Construc.cpp

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
    m_papercolor = HColorProperty::New(theApp.m_papercolorinfo);
    m_pencilcolor = HColorProperty::New(theApp.m_pencilcolorinfo);
    m_washcolor = HColorProperty::New(theApp.m_washcolorinfo);
    m_dark1color = HColorProperty::New(theApp.m_dark1colorinfo);
    m_dark2color = HColorProperty::New(theApp.m_dark2colorinfo);
    m_pencilnoise = HFloatProperty::New(theApp.m_pencilnoiseinfo);
    m_pencilfreq = HFloatProperty::New(theApp.m_pencilfreqinfo);
    m_pencilsize = HFloatProperty::New(theApp.m_pencilsizeinfo);
    m_washnoise = HFloatProperty::New(theApp.m_washnoiseinfo);
    m_washfreq = HFloatProperty::New(theApp.m_washfreqinfo);
    m_washsize = HFloatProperty::New(theApp.m_washsizeinfo);
    m_dark1noise = HFloatProperty::New(theApp.m_dark1noiseinfo);
    m_dark1freq = HFloatProperty::New(theApp.m_dark1freqinfo);
    m_dark1size = HFloatProperty::New(theApp.m_dark1sizeinfo);
    m_dark2noise = HFloatProperty::New(theApp.m_dark2noiseinfo);
    m_dark2freq = HFloatProperty::New(theApp.m_dark2freqinfo);
    m_dark2size = HFloatProperty::New(theApp.m_dark2sizeinfo);
    m_mix = HFloatProperty::New(theApp.m_mixinfo);
    m_freq = HFloatProperty::New(theApp.m_freqinfo);
    m_light = HVectorProperty::New(theApp.m_lightinfo);
    m_bitmap = HClipProperty::New(theApp.m_bitmapinfo);

    m_filename.Empty();
}

CustomTexture::~CustomTexture() {
    delete m_papercolor;
    delete m_pencilcolor;
    delete m_washcolor;
    delete m_dark1color;
    delete m_dark2color;
    delete m_pencilnoise;
    delete m_pencilfreq;
    delete m_pencilsize;
    delete m_washnoise;
    delete m_washfreq;
    delete m_washsize;
    delete m_dark1noise;
    delete m_dark1freq;
    delete m_dark1size;
    delete m_dark2noise;
    delete m_dark2freq;
    delete m_dark2size;
    delete m_light;
    delete m_mix;
    delete m_freq;
    delete m_bitmap;
}
