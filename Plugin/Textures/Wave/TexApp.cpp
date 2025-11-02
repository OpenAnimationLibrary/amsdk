// Dan  3/24/2003  \DanLP105\Plugin\Textures\Wave\TexApp.cpp
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

    string.LoadString(IDS_AMPLITUDE);
    m_amplitudeinfo = HFloatPropertyInfo::New(string, "Amplitude");
    m_amplitudeinfo->SetDefaultValue(5.0F);
    m_amplitudeinfo->SetMinValue(0.F);
    m_amplitudeinfo->SetMaxValue(100.F);
    m_amplitudeinfo->SetDrawWhen(HPropertyInfo::DRAWALWAYS);

    string.LoadString(IDS_WAVELENGTH);
    m_wavelengthinfo = HFloatPropertyInfo::New(string, "Wave Length");
    m_wavelengthinfo->SetDefaultValue(10.F);
    m_wavelengthinfo->SetMinValue(0.F);
    m_wavelengthinfo->SetMaxValue(100.F);
    m_wavelengthinfo->SetDrawWhen(HPropertyInfo::DRAWALWAYS);

    string.LoadString(IDS_DAMPING);
    m_dampinginfo = HFloatPropertyInfo::New(string, "Damping");
    m_dampinginfo->SetDefaultValue(80.0F);
    m_dampinginfo->SetMinValue(0.F);
    m_dampinginfo->SetMaxValue(100.F);
    m_dampinginfo->SetDrawWhen(HPropertyInfo::DRAWALWAYS);

    string.LoadString(IDS_PROPAGATE);
    m_propagateinfo = HFloatPropertyInfo::New(string, "Propagate");
    m_propagateinfo->SetDefaultValue(0.F);
    m_propagateinfo->SetMinValue(0.F);
    m_propagateinfo->SetMaxValue(90.0F);
    m_propagateinfo->SetDrawWhen(HPropertyInfo::DRAWALWAYS);

    string.LoadString(IDS_CYCLE);
    m_cycleinfo = HFloatPropertyInfo::New(string, "Cycle");
    m_cycleinfo->SetDefaultValue(15.0F);
    m_cycleinfo->SetMinValue(0.F);
    m_cycleinfo->SetMaxValue(1000.0F);
    m_cycleinfo->SetDrawWhen(HPropertyInfo::DRAWALWAYS);

    return CPluginApp::InitInstance();
}

int CTextureApp::ExitInstance() {
    // Delete Infos Here
    delete m_amplitudeinfo;
    delete m_wavelengthinfo;
    delete m_dampinginfo;
    delete m_propagateinfo;
    delete m_cycleinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTextureApp object

CTextureApp theApp;

CTextureApp &GetApp() {
    return theApp;
}
