// Dan  3/2/01  \Dan90\Plugin\Shaders\Phong\Shader.cpp
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

CShaderApp::CShaderApp(): m_AttenuationInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

#define NPRESETS 2

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;

    // Anisotropy presets
    m_AttenuationInfoArray.SetArraySize(NPRESETS);
    for (int i = 0; i < NPRESETS; ++i) {
        HTypeInfo *typeinfo = m_AttenuationInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("CookTorrance");
                string.LoadString(IDS_COOKTORRANCE);
                break;
            case 1:
                typeinfo->SetMatchName("Sancer");
                string.LoadString(IDS_SANCER);
                break;
            default: 
                break;

        }
        typeinfo->SetLocalizedName((String)string);
    }
    string.LoadString(IDS_ATTENUATION);
    m_AttenuationInfo = HTypePropertyInfo::New(string, "GeometricAttenuation", &m_AttenuationInfoArray);
    m_AttenuationInfo->SetDefaultIndex(GetRegistryValue(TRUE, "Blinn SHD", "Attenuation", 0));

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_AttenuationInfo;
    return CPluginApp::ExitInstance();
}
