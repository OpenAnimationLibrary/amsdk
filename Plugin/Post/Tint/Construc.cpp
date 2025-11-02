// NAP  3/11/2003  \Noel105\Plugin\Post\Tint\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

extern "C" __declspec(dllexport) PostPlugin *CreatePostPlugin(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomPostPlugin(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return POSTDLLVERSION;
}

CustomPostPlugin::CustomPostPlugin(HTreeObject *treeobject) : PostPlugin(treeobject) {
    m_style = HTypeCategoryProperty::New(theApp.m_styleinfo);
    m_lightcolor = HColorProperty::New(theApp.m_lightcolorinfo);
    m_style->AddProperty(m_lightcolor);
    m_darkcolor = HColorProperty::New(theApp.m_darkcolorinfo);
    m_style->AddProperty(m_darkcolor);
    m_percent = HPercentProperty::New(theApp.m_percentinfo);
    m_style->AddProperty(m_percent);
    m_isstylechanging = FALSE;
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_lightcolor;
    delete m_darkcolor;
    delete m_percent;
    delete m_style;
}

bool CustomPostPlugin::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, const Time time) {
    if (ptrmessage == PTM_VALUESTORED) {
        const HProperty *dueto = (HProperty*)lparam;
        if ((dueto == m_percent || dueto == m_lightcolor || dueto == m_darkcolor) && !m_isstylechanging) {
            switch (m_style->GetValue()) {
            case STYLE_BW:
                if (m_percent->GetValue() != BW_PERCENT || m_lightcolor->GetNormalizedRGBFloat() != BW_LIGHT || m_darkcolor->GetNormalizedRGBFloat() != BW_DARK)
                    m_style->StoreValue(time, STYLE_CUSTOM);
                break;
            case STYLE_COBALT:
                if (m_percent->GetValue() != COBALT_PERCENT || m_lightcolor->GetNormalizedRGBFloat() != COBALT_LIGHT || m_darkcolor->GetNormalizedRGBFloat() != COBALT_DARK)
                    m_style->StoreValue(time, STYLE_CUSTOM);
                break;
            case STYLE_SEPIA:
                if (m_percent->GetValue() != SEPIA_PERCENT || m_lightcolor->GetNormalizedRGBFloat() != SEPIA_LIGHT || m_darkcolor->GetNormalizedRGBFloat() != SEPIA_DARK)
                    m_style->StoreValue(time, STYLE_CUSTOM);
                break;
            case STYLE_XRAY:
                if (m_percent->GetValue() != XRAY_PERCENT || m_lightcolor->GetNormalizedRGBFloat() != XRAY_LIGHT || m_darkcolor->GetNormalizedRGBFloat() != XRAY_DARK)
                    m_style->StoreValue(time, STYLE_CUSTOM);
                break;
            }
        } else {
            if (dueto == m_style && !m_isstylechanging) {
                m_isstylechanging = TRUE;
                switch (m_style->GetValue()) {
                case STYLE_BW:
                    m_percent->StoreValue(time, BW_PERCENT);
                    m_lightcolor->StoreValue(time, BW_LIGHT);
                    m_darkcolor->StoreValue(time, BW_DARK);
                    break;
                case STYLE_COBALT:
                    m_percent->StoreValue(time, COBALT_PERCENT);
                    m_lightcolor->StoreValue(time, COBALT_LIGHT);
                    m_darkcolor->StoreValue(time, COBALT_DARK);
                    break;
                case STYLE_SEPIA:
                    m_percent->StoreValue(time, SEPIA_PERCENT);
                    m_lightcolor->StoreValue(time, SEPIA_LIGHT);
                    m_darkcolor->StoreValue(time, SEPIA_DARK);
                    break;
                case STYLE_XRAY:
                    m_percent->StoreValue(time, XRAY_PERCENT);
                    m_lightcolor->StoreValue(time, XRAY_LIGHT);
                    m_darkcolor->StoreValue(time, XRAY_DARK);
                    break;
                }
                m_isstylechanging = FALSE;
            }
        }
    }
    return FALSE;
}
