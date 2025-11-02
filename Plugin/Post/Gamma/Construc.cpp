// NAP  3/11/2003  \Noel105\Plugin\Post\Gamma\Construc.cpp

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
    m_gamma = HFloatProperty::New(theApp.m_gammainfo);
    m_style->AddProperty(m_gamma);

    m_isstylechanging = FALSE;
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_gamma;
    delete m_style;
}

bool CustomPostPlugin::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, const Time time) {
    switch (ptrmessage) {
        case PTM_VALUESTORED:
        {
            const HProperty *dueto = (HProperty *)lparam;
            if (dueto == m_gamma && !m_isstylechanging) {
                switch (m_style->GetValue()) {
                    case STYLE_NONE:
                        if (m_gamma->GetValue() != GAMMA_NONE)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_MONITOR:
                        if (m_gamma->GetValue() != GAMMA_MONITOR)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_NTSC:
                        if (m_gamma->GetValue() != GAMMA_NTSC)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    default: ;
                }
            } else if (dueto == m_style && !m_isstylechanging) {
                m_isstylechanging = TRUE;
                switch (m_style->GetValue()) {
                    case STYLE_NONE:
                        m_gamma->StoreValue(time, GAMMA_NONE);
                        break;
                    case STYLE_MONITOR:
                        m_gamma->StoreValue(time, GAMMA_MONITOR);
                        break;
                    case STYLE_NTSC:
                        m_gamma->StoreValue(time, GAMMA_NTSC);
                        break;
                    default: ;
                }
                m_isstylechanging = FALSE;
            }
        }
        default: ;
    }
    return FALSE;
}
