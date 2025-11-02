// Dan  3/24/2003  \DanLP105\Plugin\Textures\Villa\TexApp.cpp
//

#include "StdAfx.h"
#include "TexApp.h"
#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureApp

BEGIN_MESSAGE_MAP(CTextureApp, CWinApp)
    //{{AFX_MSG_MAP(CTextureApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureApp construction

CTextureApp::CTextureApp() = default;

BOOL CTextureApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;
    // New Infos here

    string.LoadString(IDS_NOISE);
    m_noiseinfo = HFloatPropertyInfo::New(string, "Reflect");
    m_noiseinfo->SetDefaultValue(50.0F);
    m_noiseinfo->SetMinValue(0.F);
    m_noiseinfo->SetMaxValue(100.F);
    m_noiseinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FREQ);
    m_freqinfo = HFloatPropertyInfo::New(string, "Refract");
    m_freqinfo->SetDefaultValue(50.0F);
    m_freqinfo->SetMinValue(0.F);
    m_freqinfo->SetMaxValue(100.F);
    m_freqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FO);
    m_foinfo = HFloatPropertyInfo::New(string, "Falloff");
    m_foinfo->SetDefaultValue(1.F);
    m_foinfo->SetMinValue(0.F);
    m_foinfo->SetMaxValue(100.F);
    m_foinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BOPAC);
    m_boinfo = HBoolPropertyInfo::New(string, "Invert");
    m_boinfo->SetDefaultValue(FALSE);
    m_boinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);
    /*
        string.LoadString(IDS_IREFLECT);
        m_irinfo = HBoolPropertyInfo::New(string, "Reflect");
        m_irinfo->SetDefaultValue(FALSE);
        m_irinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);
    */
    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_noiseinfo;
    delete m_freqinfo;
    delete m_foinfo;
    delete m_boinfo;
    //    delete m_irinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
