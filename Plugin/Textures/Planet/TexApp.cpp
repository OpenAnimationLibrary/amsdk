// Dan  3/24/2003  \DanLP105\Plugin\Textures\Planet\TexApp.cpp
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

    string.LoadString(IDS_FEATURESIZE);
    m_featuresizeinfo = HFloatPropertyInfo::New(string, "Feature Size");
    m_featuresizeinfo->SetDefaultValue(8.0F);
    m_featuresizeinfo->SetMinValue(0.F);
    m_featuresizeinfo->SetMaxValue(10000.0F);
    m_featuresizeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_POLARDISTANCE);
    m_polardistinfo = HFloatPropertyInfo::New(string, "Polar Distance");
    m_polardistinfo->SetDefaultValue(14.0F);
    m_polardistinfo->SetMinValue(0.F);
    m_polardistinfo->SetMaxValue(10000.0F);
    m_polardistinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_WATER);
    m_waterinfo = HFloatPropertyInfo::New(string, "Water");
    m_waterinfo->SetDefaultValue(50.0F);
    m_waterinfo->SetMinValue(0.F);
    m_waterinfo->SetMaxValue(100.F);
    m_waterinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_BUMPSTRENGTH);
    m_bumpinfo = HFloatPropertyInfo::New(string, "Bump Strength");
    m_bumpinfo->SetDefaultValue(50.0F);
    m_bumpinfo->SetMinValue(0.F);
    m_bumpinfo->SetMaxValue(100.F);
    m_bumpinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_ICE);
    m_iceinfo = HFloatPropertyInfo::New(string, "Ice");
    m_iceinfo->SetDefaultValue(20.0F);
    m_iceinfo->SetMinValue(0.F);
    m_iceinfo->SetMaxValue(100.F);
    m_iceinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

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
    m_octavesinfo = HFloatPropertyInfo::New(string, "Octaves");
    m_octavesinfo->SetDefaultValue(5.0F);
    m_octavesinfo->SetMinValue(0.F);
    m_octavesinfo->SetMaxValue(6.0F);
    m_octavesinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_NOISEFACTOR);
    m_noisemultinfo = HFloatPropertyInfo::New(string, "Noise Factor");
    m_noisemultinfo->SetDefaultValue(100.F);
    m_noisemultinfo->SetMinValue(0.F);
    m_noisemultinfo->SetMaxValue(200.0F);
    m_noisemultinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SEED);
    m_seedinfo = HFloatPropertyInfo::New(string, "Seed");
    m_seedinfo->SetDefaultValue(0.F);
    m_seedinfo->SetMinValue(0.F);
    m_seedinfo->SetMaxValue(16384.0F);
    m_seedinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_OFFSET);
    m_offsetinfo = HFloatPropertyInfo::New(string, "Offset");
    m_offsetinfo->SetDefaultValue(50.0F);
    m_offsetinfo->SetMinValue(0.F);
    m_offsetinfo->SetMaxValue(100.F);
    m_offsetinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_MOTTLESIZE);
    m_mottlesizeinfo = HFloatPropertyInfo::New(string, "Mottle Size");
    m_mottlesizeinfo->SetDefaultValue(10.F);
    m_mottlesizeinfo->SetMinValue(0.F);
    m_mottlesizeinfo->SetMaxValue(1000.0F);
    m_mottlesizeinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_MOTTLEMAGNITUDE);
    m_mottlemaginfo = HFloatPropertyInfo::New(string, "Mottle Magnitude");
    m_mottlemaginfo->SetDefaultValue(20.0F);
    m_mottlemaginfo->SetMinValue(0.F);
    m_mottlemaginfo->SetMaxValue(100.F);
    m_mottlemaginfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_DEPTHNOISE);
    m_depthnoiseinfo = HFloatPropertyInfo::New(string, "Depth Noise");
    m_depthnoiseinfo->SetDefaultValue(30.0F);
    m_depthnoiseinfo->SetMinValue(0.F);
    m_depthnoiseinfo->SetMaxValue(100.F);
    m_depthnoiseinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_MAXDEPTH);
    m_maxdepthinfo = HFloatPropertyInfo::New(string, "Max Depth");
    m_maxdepthinfo->SetDefaultValue(50.0F);
    m_maxdepthinfo->SetMinValue(0.F);
    m_maxdepthinfo->SetMaxValue(100.F);
    m_maxdepthinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    string.LoadString(IDS_SNOW);
    m_snowinfo = HFloatPropertyInfo::New(string, "Snow");
    m_snowinfo->SetDefaultValue(0.F);
    m_snowinfo->SetMinValue(0.F);
    m_snowinfo->SetMaxValue(100.F);
    m_snowinfo->SetDrawWhen(HPropertyInfo::DRAWIFMATERIALS);

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_featuresizeinfo;
    delete m_polardistinfo;
    delete m_waterinfo;
    delete m_iceinfo;
    delete m_bumpinfo;
    delete m_freqinfo;
    delete m_amplinfo;
    delete m_octavesinfo;
    delete m_noisemultinfo;
    delete m_seedinfo;
    delete m_offsetinfo;
    delete m_mottlesizeinfo;
    delete m_mottlemaginfo;
    delete m_depthnoiseinfo;
    delete m_maxdepthinfo;
    delete m_snowinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
