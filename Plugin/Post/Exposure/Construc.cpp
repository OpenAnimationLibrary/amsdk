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
    m_exposure = HFloatProperty::New(theApp.m_exposureinfo);
    m_brightness = HPercentProperty::New(theApp.m_brightnessinfo);
    m_contrast = HPercentProperty::New(theApp.m_contrastinfo);
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_exposure;
    delete m_brightness;
    delete m_contrast;
}
