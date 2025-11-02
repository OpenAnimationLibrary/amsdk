// Yves  2006-05-15  \Master13.0\Plugin\Shaders\Environment\Shader.cpp
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

CShaderApp::CShaderApp(): m_ClipInfo{nullptr}, m_MappingInfo{nullptr}, m_ExposureInfo{nullptr}, m_AxisBoneInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here

    string.LoadString(IDS_CLIP);
    m_ClipInfo = HClipPropertyInfo::New(string, "Bitmap");
    m_ClipInfo->SetDocumentation(DOC("Image used as radiance map."));

    m_MappingInfoArray.SetArraySize(4);
    for (int i = 0; i < 4; ++i) {
        HTypeInfo *typeinfo = m_MappingInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("Latitude Longitude");
                string.LoadString(IDS_LATITUDELONGITUDE);
                break;
            case 1:
                typeinfo->SetMatchName("Light Probe");
                string.LoadString(IDS_LIGHTPROBE);
                break;
            case 2:
                typeinfo->SetMatchName("Mirrored Sphere");
                string.LoadString(IDS_MIRROREDSPHERE);
                break;
            case 3:
                typeinfo->SetMatchName("Cube Map");
                string.LoadString(IDS_CUBEMAP);
                break;
            default:
                break;
        }
        typeinfo->SetLocalizedName((String)string);
    }
    string.LoadString(IDS_MAPTYPE);
    m_MappingInfo = HTypePropertyInfo::New(string, "MappingType", &m_MappingInfoArray);
    m_MappingInfo->SetDefaultIndex(GetRegistryValue(TRUE, "Environment SHD", "Mapping", 0));

    string.LoadString(IDS_EXPOSURE);
    m_ExposureInfo = HFloatPropertyInfo::New(string, "Exposure");
    m_ExposureInfo->SetDefaultValue(0.F);
    m_ExposureInfo->SetMinValue(-16.0f);
    m_ExposureInfo->SetMaxValue(16.0f);
    m_ExposureInfo->SetDocumentation(DOC("The Exposure value allows you to brighten or darken the radiance map."));

    string.LoadString(IDS_AXISBONE);
    m_AxisBoneInfo = HPointerPropertyInfo::New(string, "BoneAxis");

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_ClipInfo;
    delete m_MappingInfo;
    delete m_ExposureInfo;
    delete m_AxisBoneInfo;

    return CPluginApp::ExitInstance();
}
