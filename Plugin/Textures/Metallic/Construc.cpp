// Dan  11/26/2001  \Dan90\Plugin\Textures\Metallic\Construc.cpp

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
    m_da = HFloatProperty::New(theApp.m_dainfo);
    m_df = HFloatProperty::New(theApp.m_dfinfo);
    m_dt = HFloatProperty::New(theApp.m_dtinfo);
    m_tx = HFloatProperty::New(theApp.m_txinfo);
    m_ty = HFloatProperty::New(theApp.m_tyinfo);
    m_light = HVectorProperty::New(theApp.m_lightinfo);
    m_rough = HFloatProperty::New(theApp.m_roughinfo);
    m_useback = HBoolProperty::New(theApp.m_usebackinfo);
    m_bcolor = HColorProperty::New(theApp.m_bcolorinfo);
    m_fcolor = HColorProperty::New(theApp.m_fcolorinfo);
    m_fref = HFloatProperty::New(theApp.m_frefinfo);
    m_fo = HFloatProperty::New(theApp.m_foinfo);
    m_bo = HFloatProperty::New(theApp.m_boinfo);
    m_fuzz = HFloatProperty::New(theApp.m_fuzzinfo);
    m_xs = HFloatProperty::New(theApp.m_xsinfo);
    m_ys = HFloatProperty::New(theApp.m_ysinfo);
    m_pencil = HFloatProperty::New(theApp.m_pencilinfo);
    m_mix = HFloatProperty::New(theApp.m_mixinfo);
    m_bitmap = HClipProperty::New(theApp.m_bitmapinfo);
}

CustomTexture::~CustomTexture() {
    delete m_light;
    delete m_rough;
    delete m_useback;
    delete m_bcolor;
    delete m_fcolor;
    delete m_fref;
    delete m_fo;
    delete m_bo;
    delete m_fuzz;
    delete m_xs;
    delete m_ys;
    delete m_pencil;
    delete m_mix;
    delete m_da;
    delete m_df;
    delete m_dt;
    delete m_tx;
    delete m_ty;
    delete m_bitmap;
}
