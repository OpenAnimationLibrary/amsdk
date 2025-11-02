// Yves  10/11/2006  \Plugin\Post\Merge\Construc.cpp

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

CustomPostPlugin::CustomPostPlugin(HTreeObject *treeobject) : PostPlugin(treeobject), m_merge{0} {
    m_mergetype = HTypeCategoryProperty::New(theApp.m_mergetypeinfo);
    m_percent = HPercentProperty::New(theApp.m_percentinfo);
}

CustomPostPlugin::~CustomPostPlugin() {
    delete m_mergetype;
    delete m_percent;
}
