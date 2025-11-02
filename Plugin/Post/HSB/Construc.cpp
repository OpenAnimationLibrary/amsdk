// YP  10/02/2005  \Yves120\Plugin\Post\Exposure\Construc.cpp

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
    m_hue = HFloatProperty::New(theApp.m_hueinfo);
    m_saturation = HPercentProperty::New(theApp.m_saturationinfo);
    m_exposure = HFloatProperty::New(theApp.m_exposureinfo);
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_hue;
    delete m_saturation;
    delete m_exposure;
}
