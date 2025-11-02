// Dan  3/24/2003  \DanLP105\Plugin\Textures\Scales\TexApp.cpp
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

    string.LoadString(IDS_SIZE);
    m_sizeinfo = HVectorPropertyInfo::New(string, "Size");
    m_sizeinfo->GetX()->SetDefaultValue(10.F);
    m_sizeinfo->GetX()->SetMinValue(0.F);
    m_sizeinfo->GetX()->SetMaxValue(10000.0F);
    m_sizeinfo->GetY()->SetDefaultValue(10.F);
    m_sizeinfo->GetY()->SetMinValue(0.F);
    m_sizeinfo->GetY()->SetMaxValue(10000.0F);
    m_sizeinfo->GetZ()->SetDefaultValue(10.F);
    m_sizeinfo->GetZ()->SetMinValue(0.F);
    m_sizeinfo->GetZ()->SetMaxValue(10000.0F);

    string.LoadString(IDS_BUMPSIZE);
    m_bumpinfo = HFloatPropertyInfo::New(string, "Bump Size");
    m_bumpinfo->SetDefaultValue(60.0F);
    m_bumpinfo->SetMinValue(0.F);
    m_bumpinfo->SetMaxValue(100.F);
    m_bumpinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_EDGE);
    m_edgeinfo = HFloatPropertyInfo::New(string, "Edge");
    m_edgeinfo->SetDefaultValue(10.F);
    m_edgeinfo->SetMinValue(0.F);
    m_edgeinfo->SetMaxValue(100.F);
    m_edgeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_VALLEY);
    m_valleyinfo = HFloatPropertyInfo::New(string, "Valley");
    m_valleyinfo->SetDefaultValue(0.F);
    m_valleyinfo->SetMinValue(0.F);
    m_valleyinfo->SetMaxValue(100.F);
    m_valleyinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_ROUNDING);
    m_roundinginfo = HFloatPropertyInfo::New(string, "Rounding");
    m_roundinginfo->SetDefaultValue(100.F);
    m_roundinginfo->SetMinValue(0.F);
    m_roundinginfo->SetMaxValue(200.0F);
    m_roundinginfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SEED);
    m_seedinfo = HFloatPropertyInfo::New(string, "Seed");
    m_seedinfo->SetDefaultValue(0.F);
    m_seedinfo->SetMinValue(0.F);
    m_seedinfo->SetMaxValue(16384.0F);
    m_seedinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SLOPE1);
    m_slope1info = HFloatPropertyInfo::New(string, "Slope 1");
    m_slope1info->SetDefaultValue(50.0F);
    m_slope1info->SetMinValue(0.F);
    m_slope1info->SetMaxValue(100.F);
    m_slope1info->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SLOPE2);
    m_slope2info = HFloatPropertyInfo::New(string, "Slope 2");
    m_slope2info->SetDefaultValue(50.0F);
    m_slope2info->SetMinValue(0.F);
    m_slope2info->SetMaxValue(100.F);
    m_slope2info->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_sizeinfo;
    delete m_bumpinfo;
    delete m_edgeinfo;
    delete m_valleyinfo;
    delete m_roundinginfo;
    delete m_seedinfo;
    delete m_slope1info;
    delete m_slope2info;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
