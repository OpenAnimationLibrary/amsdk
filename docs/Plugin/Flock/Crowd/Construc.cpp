// KB  3/4/02  \Ken90\Plugin\Flock\Crowd\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "flockapp.h"

extern CFlockApp theApp;

extern "C" __declspec(dllexport) Flock *CreateFlocking(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomFlock(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return FLOCKDLLVERSION;
}

extern "C" __declspec(dllexport) const char *GetDocumentation() {
    return DOC(
        "Crowd is a special kind of flock intended for groups of characters or \
 plants that are on a surface like the ground. The \
 members are distributed in the flock region in a flat plane. When \
 a Flock Surface Constraint </a>is \
 applied to the flock, the members of the flock can all be placed on an \
 uneven surface. Unlike \
 the birds and swarm flocks, the members of the flock will not move within \
 the flock. But \
 you can still apply an action to the members."
    );
}

CustomFlock::CustomFlock(HTreeObject *treeobject) : Flock(treeobject) {

    m_mindistance = HFloatProperty::New(theApp.m_mindistanceinfo);
    m_xzscaleoffset = HFloatProperty::New(theApp.m_xzscaleoffsetinfo);
    m_yscaleoffset = HFloatProperty::New(theApp.m_yscaleoffsetinfo);
    m_rolloffset = HFloatProperty::New(theApp.m_rolloffsetinfo);
    m_proportional = HBoolProperty::New(theApp.m_proportionalinfo);
}

CustomFlock::~CustomFlock() {
    delete m_mindistance;
    delete m_xzscaleoffset;
    delete m_yscaleoffset;
    delete m_rolloffset;
    delete m_proportional;
}
