// KB  2/4/2003  \Ken105\Plugin\Shaders\Gradient\Shader.cpp
//

#include "stdafx.h"
#include "Shader.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShaderApp

BEGIN_MESSAGE_MAP(CShaderApp, CWinApp)
	//{{AFX_MSG_MAP(CShaderApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardApp construction

CShaderApp::CShaderApp()
{
}

CShaderApp::~CShaderApp()
{
}

BOOL CShaderApp::InitInstance() 
{
   m_RayDistanceInfo = HFloatPropertyInfo::New("max. distance for the rays", "distance" );
   m_RayDistanceInfo->SetDefaultValue(1000.0f);
   m_RayDistanceInfo->SetMinValue(0.1f);
   m_RayDistanceInfo->SetMaxValue(100000.0f);
   m_SamplesInfo = HIntPropertyInfo::New("Number of samples", "samples");
   m_SamplesInfo->SetDefaultValue(64);
   m_SamplesInfo->SetMinValue(4);
   m_SamplesInfo->SetMaxValue(10000);
   return CWinApp::InitInstance();
}

int CShaderApp::ExitInstance() 
{
   delete m_RayDistanceInfo;
   delete m_SamplesInfo;
   return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

CShaderApp &GetApp()
{
   return theApp;
}