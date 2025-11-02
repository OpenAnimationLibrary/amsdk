// NAP  3/11/2003  \Noel105\Plugin\Post\FilmGrain\Construc.cpp

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
    m_size = HPercentProperty::New(theApp.m_sizeinfo);
    m_style->AddProperty(m_size);
    m_amount = HPercentProperty::New(theApp.m_amountinfo);
    m_style->AddProperty(m_amount);

    m_isstylechanging = FALSE;
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_amount;
    delete m_size;
    delete m_style;
}

bool CustomPostPlugin::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, const Time time) {
    switch (ptrmessage) {
        case PTM_VALUESTORED:
        {
            const HProperty *dueto = (HProperty *)lparam;
            if ((dueto == m_size || dueto == m_amount) && !m_isstylechanging) {
                switch (m_style->GetValue()) {
                    case STYLE_100ASA:
                        if (m_amount->GetValue() != FILMGRAINAMOUNT100ASA || m_size->GetValue() != FILMGRAINSIZE100ASA)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_200ASA:
                        if (m_amount->GetValue() != FILMGRAINAMOUNT200ASA || m_size->GetValue() != FILMGRAINSIZE200ASA)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_400ASA:
                        if (m_amount->GetValue() != FILMGRAINAMOUNT400ASA || m_size->GetValue() != FILMGRAINSIZE400ASA)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    default: ;
                }
            } else if (dueto == m_style && !m_isstylechanging) {
                m_isstylechanging = TRUE;
                switch (m_style->GetValue()) {
                    case STYLE_100ASA:
                        m_amount->StoreValue(time, FILMGRAINAMOUNT100ASA);
                        m_size->StoreValue(time, FILMGRAINSIZE100ASA);
                        break;
                    case STYLE_200ASA:
                        m_amount->StoreValue(time, FILMGRAINAMOUNT200ASA);
                        m_size->StoreValue(time, FILMGRAINSIZE200ASA);
                        break;
                    case STYLE_400ASA:
                        m_amount->StoreValue(time, FILMGRAINAMOUNT400ASA);
                        m_size->StoreValue(time, FILMGRAINSIZE400ASA);
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
