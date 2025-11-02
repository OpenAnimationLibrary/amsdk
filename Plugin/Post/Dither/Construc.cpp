// NAP  3/11/2003  \Noel105\Plugin\Post\Dither\Construc.cpp

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
    m_bittype = HTypeCategoryProperty::New(theApp.m_bittypeinfo);
    m_levels = HIntProperty::New(theApp.m_levelsinfo);
    m_bittype->AddProperty(m_levels);

    m_isstylechanging = FALSE;
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_levels;
    delete m_bittype;
}

bool CustomPostPlugin::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, const Time time) {
    switch (ptrmessage) {
        case PTM_VALUESTORED:
        {
            const HProperty *dueto = (HProperty *)lparam;
            if (dueto == m_levels && !m_isstylechanging) {
                switch (m_bittype->GetValue()) {
                    case BITS_24:
                        if (m_levels->GetValue() != BITS_24_LEVELS)
                            m_bittype->StoreValue(time, BITS_CUSTOM);
                        break;
                    case BITS_16:
                        if (m_levels->GetValue() != BITS_16_LEVELS)
                            m_bittype->StoreValue(time, BITS_CUSTOM);
                        break;
                    case BITS_8:
                        if (m_levels->GetValue() != BITS_8_LEVELS)
                            m_bittype->StoreValue(time, BITS_CUSTOM);
                        break;
                    default: ;
                }
            } else if (dueto == m_bittype && !m_isstylechanging) {
                m_isstylechanging = TRUE;
                switch (m_bittype->GetValue()) {
                    case BITS_24:
                        m_levels->StoreValue(time, BITS_24_LEVELS);
                        break;
                    case BITS_16:
                        m_levels->StoreValue(time, BITS_16_LEVELS);
                        break;
                    case BITS_8:
                        m_levels->StoreValue(time, BITS_8_LEVELS);
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
