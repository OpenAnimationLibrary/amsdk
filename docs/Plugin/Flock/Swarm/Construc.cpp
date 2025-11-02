// KB  6/13/2003  \Ken105\Plugin\Flock\Swarm\Construc.cpp

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
    return DOC("The Swarm plug-in is designed for the kind of motion observed for \
 flies and bees.The \
 members of a swarm have no formation or cohesion, but rather fly around \
 a centralized region. ");
}

CustomFlock::CustomFlock(HTreeObject *treeobject) : Flock(treeobject) {
    m_mindistance = HFloatProperty::New(theApp.m_mindistanceinfo);
    m_jitter = HIntProperty::New(theApp.m_jitterinfo);
    m_maxspeed = HFloatProperty::New(theApp.m_maxspeedinfo);
    m_acceleration = HFloatProperty::New(theApp.m_accelerationinfo);
    m_lasttimeframe = 0.F;
}

CustomFlock::~CustomFlock() {
    delete m_mindistance;
    delete m_jitter;
    delete m_maxspeed;
    delete m_acceleration;
}
