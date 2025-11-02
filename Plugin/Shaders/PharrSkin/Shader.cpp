// Yves 10-12-2006  \Plugin\Shaders\PharrSkin\Shader.cpp
//

#include "StdAfx.h"
#include "Shader.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
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

CShaderApp::CShaderApp(): m_iorinfo{nullptr}, m_thicknessinfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString String;

    String.LoadString(IDS_IOR);
    m_iorinfo = HPercentPropertyInfo::New(String, "SkinIOR");
    m_iorinfo->SetDefaultValue(1.4f);
    m_iorinfo->SetMinValue(1.F);
    m_iorinfo->SetMaxValue(2.F);

    String.LoadString(IDS_THICKNESS);
    m_thicknessinfo = HPercentPropertyInfo::New(String, "SkinThickness");
    m_thicknessinfo->SetDefaultValue(1.5f);
    m_thicknessinfo->SetMinValue(0.1f);
    m_thicknessinfo->SetMaxValue(5.0f);

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_iorinfo;
    delete m_thicknessinfo;
    return CPluginApp::ExitInstance();
}

CShaderApp &GetApp() {
    return theApp;
}
