// NAP  9/11/2003  \Noelsrv105\Plugin\Post\FrameBurn\Construc.cpp

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
    m_fontscale = HPercentProperty::New(theApp.m_fontscaleinfo);
    m_opacity = HPercentProperty::New(theApp.m_opacityinfo);
    m_displayname = HBoolProperty::New(theApp.m_displaynameinfo);
    m_displayshadow = HBoolProperty::New(theApp.m_displayshadowinfo);
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_fontscale;
    delete m_opacity;
    delete m_displayname;
    delete m_displayshadow;
}

bool CustomPostPlugin::OnPtrMessage(PtrMessage ptrmessage, HTreeObject **ptruplink, LONG_PTR lparam, const Time time) {
    return FALSE;
}
