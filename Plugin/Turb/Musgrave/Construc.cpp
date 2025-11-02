// Yves Poissant 09-2003 \Extended Noise\Construc.cpp
#include "StdAfx.h"
#include "Custom.h"
#include "TurbApp.h"
//#include "Rnd.h"

extern CTurbApp theApp;

extern "C" __declspec(dllexport) Turbulence *CreateTurbulence(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomTurbulence(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return TURBULENCEDLLVERSION;
}

CustomTurbulence::CustomTurbulence(HTreeObject *treeobject) : Turbulence(treeobject) {
    if (treeobject) {
        m_FractalNoiser.LinkProperties(theApp.m_NoiserUI);
        m_Transferer.LinkProperties(theApp.m_TransfererUI);
        m_Sampler.LinkProperties(theApp.m_SamplerUI);
        ResetDebug();
    }
}

CustomTurbulence::~CustomTurbulence() = default;

bool CustomTurbulence::ParseArg(const char *label, const char *value) {
    if (m_FractalNoiser.ParseArg(label, value))
        return true;
    return m_Transferer.ParseArg(label, value);
}

void CustomTurbulence::SaveHisto(const float val) {
    if (val > d_Max)
        d_Max = val;
    if (val < d_Min)
        d_Min = val;
}

void CustomTurbulence::ResetDebug() {
    d_Min = 1.0e35F;
    d_Max = -1.0e35F;
}
