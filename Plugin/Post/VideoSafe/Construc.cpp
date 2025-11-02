// NAP  3/11/2003  \Noel105\Plugin\Post\VideoSafe\Construc.cpp

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

CustomPostPlugin::CustomPostPlugin(HTreeObject *treeobject) : PostPlugin(treeobject), m_tab{}, m_chroma_lim{0}, m_compos_lim{0}, m_ichroma_lim2{0}, m_icompos_lim{0}, m_gamma{0} {
    m_style = HTypeProperty::New(theApp.m_styleinfo);
    m_tabbuilt = 0;
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_style;
}
