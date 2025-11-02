// Dan  3/24/2003  \DanLP105\Plugin\Textures\XRay\TexApp.cpp
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

    string.LoadString(IDS_USECURRENT);
    m_usebackinfo = HBoolPropertyInfo::New(string, "UseCurrent");
    m_usebackinfo->SetDefaultValue(FALSE);
    m_usebackinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BCOLOR);
    m_bcolorinfo = HColorPropertyInfo::New(string, "BColor");
    m_bcolorinfo->GetRed()->SetDefaultValue(0.5F);
    m_bcolorinfo->GetGreen()->SetDefaultValue(0.5F);
    m_bcolorinfo->GetBlue()->SetDefaultValue(0.5F);

    string.LoadString(IDS_FALLOFF);
    m_boinfo = HFloatPropertyInfo::New(string, "Falloff");
    m_boinfo->SetDefaultValue(1.F);
    m_boinfo->SetMinValue(0.F);
    m_boinfo->SetMaxValue(100.F);
    m_boinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_MIX);
    m_mixinfo = HFloatPropertyInfo::New(string, "Mix");
    m_mixinfo->SetDefaultValue(100.F);
    m_mixinfo->SetMinValue(0.F);
    m_mixinfo->SetMaxValue(100.F);
    m_mixinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_usebackinfo;
    delete m_bcolorinfo;
    delete m_boinfo;
    delete m_mixinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
