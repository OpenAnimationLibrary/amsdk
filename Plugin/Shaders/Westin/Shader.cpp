// Yves  2005/11/24  \Master13.0\Plugin\Shaders\Westin\Shader.cpp
//

#include "StdAfx.h"
#include "StrClass.h"
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

CShaderApp::CShaderApp(): m_IsPerpendicularInfo{nullptr}, m_AlignmentInfo{nullptr}, m_IsIsotropicInfo{nullptr}, m_AxisBoneInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;

    string.LoadString(IDS_ISPERPENDICULAR);
    m_IsPerpendicularInfo = HBoolPropertyInfo::New(string, "IsPerpendicular");
    m_IsPerpendicularInfo->SetDefaultValue(GetRegistryValue(TRUE, "Westin SHD", "IsPerpendicular", FALSE));

    // Types of Tangent orientations
    m_TypeInfoArray.SetArraySize(3);
    for (int i = 0; i < 3; ++i) {
        HTypeInfo *typeinfo = m_TypeInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("Tangent Vector");
                string.LoadString(IDS_N_TANGENTVECT);
                break;
            case 1:
                typeinfo->SetMatchName("Up Vector");
                string.LoadString(IDS_N_UPVECT);
                break;
            case 2:
                typeinfo->SetMatchName("Axis Vector");
                string.LoadString(IDS_N_AXISVECT);
                break;
            default:
                break;
        }
        typeinfo->SetLocalizedName((String)string);
    }
    string.LoadString(IDS_ALIGNMENT);
    m_AlignmentInfo = HTypePropertyInfo::New(string, "TangentAlignment", &m_TypeInfoArray);
    m_AlignmentInfo->SetDefaultIndex(GetRegistryValue(TRUE, "Westin SHD", "Alignment", 0));

    string.LoadString(IDS_ISISOTROPIC);
    m_IsIsotropicInfo = HBoolPropertyInfo::New(string, "IsIsotropic");
    m_IsIsotropicInfo->SetDefaultValue(GetRegistryValue(TRUE, "Westin SHD", "IsIsotropic", FALSE));

    string.LoadString(IDS_AXISBONE);
    m_AxisBoneInfo = HPointerPropertyInfo::New(string, "BoneAxis");

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_IsPerpendicularInfo;
    delete m_AlignmentInfo;
    delete m_IsIsotropicInfo;
    delete m_AxisBoneInfo;
    return CPluginApp::ExitInstance();
}

CShaderApp &GetApp() {
    return theApp;
}
