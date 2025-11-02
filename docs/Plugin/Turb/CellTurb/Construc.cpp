// KB  10/26/2004  \Plugin\Turb\CellTurb\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "TurbApp.h"
#include "SDK/Misc.h"
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
    m_threshold = HFloatProperty::New(theApp.m_thresholdinfo);
    m_oct = HIntProperty::New(theApp.m_octinfo);
    m_density = HFloatProperty::New(theApp.m_densityinfo);
    m_euclid = HBoolProperty::New(theApp.m_euclidinfo);
}

CustomTurbulence::~CustomTurbulence() {
    delete m_celltype;
    delete m_threshold;
    delete m_oct;
    delete m_density;
    delete m_euclid;
}

bool CustomTurbulence::ParseArg(const char *label, const char *value) {
    // pre 9.0 backward compatability
    //	if (stricmp(label, "Type")==0 && isdigit(*value)) {//deprecated
    if (_stricmp(label, "Type") == 0 && isdigit(*value)) {
        const int celltype = atoi_replace(value);
        m_celltype->StoreValue(Time(), celltype);
        return TRUE;
    }
    return FALSE;
}
