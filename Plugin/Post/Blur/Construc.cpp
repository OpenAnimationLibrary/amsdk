// NAP  6/26/2003  \Noelsrv105\Plugin\Post\Blur\Construc.cpp

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
    m_softness = HFloatProperty::New(theApp.m_softnessinfo);
    m_style->AddProperty(m_softness);
    m_isstylechanging = FALSE;
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_softness;
    delete m_style;
}

bool CustomPostPlugin::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, const Time time) {
    switch (ptrmessage) {
        case PTM_VALUESTORED:
        {
            const HProperty *dueto = (HProperty *)lparam;
            if (dueto == m_softness && !m_isstylechanging) {
                switch (m_style->GetValue()) {
                    case STYLE_8MM:
                        if (m_softness->GetValue() != SOFTNESS_8MM)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_16MM:
                        if (m_softness->GetValue() != SOFTNESS_16MM)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_35MM:
                        if (m_softness->GetValue() != SOFTNESS_35MM)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    default: ;
                }
            } else if (dueto == m_style && !m_isstylechanging) {
                m_isstylechanging = TRUE;
                switch (m_style->GetValue()) {
                    case STYLE_8MM:
                        m_softness->StoreValue(time, SOFTNESS_8MM);
                        break;
                    case STYLE_16MM:
                        m_softness->StoreValue(time, SOFTNESS_16MM);
                        break;
                    case STYLE_35MM:
                        m_softness->StoreValue(time, SOFTNESS_35MM);
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
