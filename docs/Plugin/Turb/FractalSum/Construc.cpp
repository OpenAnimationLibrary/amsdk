// Dan  11/26/2001  \Dan90\Plugin\Turb\FractalSum\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TurbApp.h"

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
    m_octaves = HIntProperty::New(theApp.m_octavesinfo);
}

CustomTurbulence::~CustomTurbulence() {
    delete m_octaves;
}
