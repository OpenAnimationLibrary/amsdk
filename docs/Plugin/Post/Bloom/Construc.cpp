// NAP  3/11/2003  \Noel105\Plugin\Post\Bloom\Construc.cpp

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
    m_strength = HPercentProperty::New(theApp.m_strengthinfo);
    m_style->AddProperty(m_strength);
    m_threshold = HPercentProperty::New(theApp.m_thresholdinfo);
    m_style->AddProperty(m_threshold);
    m_radius = HIntProperty::New(theApp.m_radiusinfo);
    m_style->AddProperty(m_radius);

    m_isstylechanging = FALSE;
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_strength;
    delete m_threshold;
    delete m_radius;
    delete m_style;
}

bool CustomPostPlugin::OnPtrMessage(const PtrMessage ptrmessage, HTreeObject **ptruplink, const LONG_PTR lparam, const Time time) {
    switch (ptrmessage) {
        case PTM_VALUESTORED:
        {
            const HProperty *dueto = (HProperty *)lparam;
            if ((dueto == m_threshold || dueto == m_strength || dueto == m_radius) && !m_isstylechanging) {
                switch (m_style->GetValue()) {
                    case STYLE_DAY:
                        if (m_threshold->GetValue() != DAY_THRESHOLD
                            || m_strength->GetValue() != DAY_STRENGTH
                            || m_radius->GetValue() != DAY_RADIUS)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    case STYLE_NIGHT:
                        if (m_threshold->GetValue() != NIGHT_THRESHOLD
                            || m_strength->GetValue() != NIGHT_STRENGTH
                            || m_radius->GetValue() != NIGHT_RADIUS)
                            m_style->StoreValue(time, STYLE_CUSTOM);
                        break;
                    default: ;
                }
            } else if (dueto == m_style && !m_isstylechanging) {
                m_isstylechanging = TRUE;
                switch (m_style->GetValue()) {
                    case STYLE_DAY:
                        m_threshold->StoreValue(time, DAY_THRESHOLD);
                        m_strength->StoreValue(time, DAY_STRENGTH);
                        m_radius->StoreValue(time, DAY_RADIUS);
                        break;
                    case STYLE_NIGHT:
                        m_threshold->StoreValue(time, NIGHT_THRESHOLD);
                        m_strength->StoreValue(time, NIGHT_STRENGTH);
                        m_radius->StoreValue(time, NIGHT_RADIUS);
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
