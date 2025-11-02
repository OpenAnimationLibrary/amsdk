// YP  06/06/2006  Plugin\Post\Denoise\Construct.cpp

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
    m_alpha = HFloatProperty::New(theApp.m_alphainfo);
    m_sigma = HFloatProperty::New(theApp.m_sigmainfo);
    m_p = HFloatProperty::New(theApp.m_pinfo);
    m_anisotropy = HPercentProperty::New(theApp.m_anisotropyinfo);
    m_iter = HIntProperty::New(theApp.m_iterinfo);
    m_dt = HFloatProperty::New(theApp.m_dtinfo);
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_alpha;
    delete m_sigma;
    delete m_p;
    delete m_anisotropy;
    delete m_iter;
    delete m_dt;
}
