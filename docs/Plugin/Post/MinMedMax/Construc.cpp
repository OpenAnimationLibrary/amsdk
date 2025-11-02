// NAP  6/19/2003  \Noelsrv105\Plugin\Post\MinMedMax\Construc.cpp

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
    m_pos = HPercentProperty::New(theApp.m_posinfo);
    m_style->AddProperty(m_pos);
    m_radius = HIntProperty::New(theApp.m_radiusinfo);
    m_isround = HBoolProperty::New(theApp.m_isroundinfo);

    m_isstylechanging = FALSE;
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_pos;
    delete m_radius;
    delete m_isround;
    delete m_style;
}

bool CustomPostPlugin::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, const Time time) {
    switch (ptrmessage) {
        case PTM_VALUESTORED:
        {
            const HProperty *dueto = (HProperty *)lparam;
            if ((dueto == m_radius || dueto == m_pos) && !m_isstylechanging) {
                switch (m_style->GetValue()) {
                    case STYLE_MIN:
                        if (m_pos->GetValue() != POS_MIN)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_MED:
                        if (m_pos->GetValue() != POS_MED)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_MAX:
                        if (m_pos->GetValue() != POS_MAX)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    default: ;
                }
            } else if (dueto == m_style && !m_isstylechanging) {
                m_isstylechanging = TRUE;
                switch (m_style->GetValue()) {
                    case STYLE_MIN:
                        m_pos->StoreValue(time, POS_MIN);
                        break;
                    case STYLE_MED:
                        m_pos->StoreValue(time, POS_MED);
                        break;
                    case STYLE_MAX:
                        m_pos->StoreValue(time, POS_MAX);
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
