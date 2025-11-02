// Dan  11/26/2001  \Dan90\Plugin\Turb\GridTurb\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TurbApp.h"
#include "Perlin.h"
#include "Rnd.h"

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
    m_celltype = HTypeProperty::New(theApp.m_celltypeinfo);
    m_octaves = HIntProperty::New(theApp.m_octavesinfo);
    m_gridsize = HIntProperty::New(theApp.m_gridsizeinfo);
}

CustomTurbulence::~CustomTurbulence() {
    delete m_octaves;
    delete m_gridsize;
    delete m_celltype;
}
