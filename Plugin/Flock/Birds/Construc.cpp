// KB  3/4/02  \Ken90\Plugin\Flock\Birds\Construc.cpp

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
    return DOC("The Birds plug-in , as the name implies, is designed for flocks of \
 birds. Each bird tries to stay close to its neighbors, and uses the motion of the \
 entire flock to decide how it flies. ");
}

CustomFlock::CustomFlock(HTreeObject *treeobject) : Flock(treeobject) {
    m_mindistance = HFloatProperty::New(theApp.m_mindistanceinfo);
    m_jitter = HIntProperty::New(theApp.m_jitterinfo);
    m_maxspeed = HFloatProperty::New(theApp.m_maxspeedinfo);
    m_acceleration = HFloatProperty::New(theApp.m_accelerationinfo);
}

CustomFlock::~CustomFlock() {
    delete m_mindistance;
    delete m_jitter;
    delete m_maxspeed;
    delete m_acceleration;
}
