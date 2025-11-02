// Dan  3/24/2003  \DanLP105\Plugin\Textures\Crumple\TexApp.cpp
//

#include "StdAfx.h"
#include "TexApp.h"

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

BOOL CTextureApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    string.LoadString(IDS_SIZE);
    m_sizeinfo = HScalePropertyInfo::New(string, "Size");
    m_sizeinfo->GetX()->SetDefaultValue(5.0F);
    m_sizeinfo->GetX()->SetMinValue(0.F);
    m_sizeinfo->GetX()->SetMaxValue(10000.0F);
    m_sizeinfo->GetY()->SetDefaultValue(5.0F);
    m_sizeinfo->GetY()->SetMinValue(0.F);
    m_sizeinfo->GetY()->SetMaxValue(10000.0F);
    m_sizeinfo->GetZ()->SetDefaultValue(5.0F);
    m_sizeinfo->GetZ()->SetMinValue(0.F);
    m_sizeinfo->GetZ()->SetMaxValue(10000.0F);

    string.LoadString(IDS_BUMPSIZE);
    m_bumpinfo = HFloatPropertyInfo::New(string, "Bump Size");
    m_bumpinfo->SetDefaultValue(60.0F);
    m_bumpinfo->SetMinValue(0.F);
    m_bumpinfo->SetMaxValue(100.F);
    m_bumpinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_FREQUENCYFACTOR);
    m_freqinfo = HFloatPropertyInfo::New(string, "Frequency Factor");
    m_freqinfo->SetDefaultValue(220.0F);
    m_freqinfo->SetMinValue(0.F);
    m_freqinfo->SetMaxValue(1000.0F);
    m_freqinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_AMPLITUDEFACTOR);
    m_amplinfo = HFloatPropertyInfo::New(string, "Amplitude Factor");
    m_amplinfo->SetDefaultValue(50.0F);
    m_amplinfo->SetMinValue(0.F);
    m_amplinfo->SetMaxValue(100.F);
    m_amplinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_OCTAVES);
    m_octavesinfo = HIntPropertyInfo::New(string, "Octaves");
    m_octavesinfo->SetDefaultValue(3);
    m_octavesinfo->SetMinValue(1);
    m_octavesinfo->SetMaxValue(6);
    m_octavesinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_WEIGHT);
    m_weightinfo = HFloatPropertyInfo::New(string, "Weight");
    m_weightinfo->SetDefaultValue(50.0F);
    m_weightinfo->SetMinValue(0.F);
    m_weightinfo->SetMaxValue(100.F);
    m_weightinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SEED);
    m_seedinfo = HFloatPropertyInfo::New(string, "Seed");
    m_seedinfo->SetDefaultValue(0.F);
    m_seedinfo->SetMinValue(0.F);
    m_seedinfo->SetMaxValue(16384.0F);
    m_seedinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    delete m_sizeinfo;
    delete m_bumpinfo;
    delete m_freqinfo;
    delete m_amplinfo;
    delete m_weightinfo;
    delete m_seedinfo;
    delete m_octavesinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CTextureApp construction

CTextureApp::CTextureApp() = default;

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
