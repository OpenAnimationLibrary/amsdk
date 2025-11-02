// NAP  3/11/2003  \Noel105\Plugin\Post\Add\Construc.cpp

#include "stdafx.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

extern "C" __declspec(dllexport) PostPlugin *CreatePostPlugin(HTreeObject *treeobject)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState())
   return new CustomPostPlugin(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   return POSTDLLVERSION;
}

CustomPostPlugin::CustomPostPlugin(HTreeObject *treeobject) : PostPlugin(treeobject)
{
   m_percent1 = HPercentProperty::New( theApp.m_percentinfo1 );
   m_percent2 = HPercentProperty::New( theApp.m_percentinfo2 );
   m_percent3 = HPercentProperty::New( theApp.m_percentinfo3 );
}

CustomPostPlugin::~CustomPostPlugin()
{
   delete m_percent1;
   delete m_percent2;
   delete m_percent3;
}

