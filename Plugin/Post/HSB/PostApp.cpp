// YP  10/02/2005  \Yves120\Plugin\Post\Exposure\PostApp.cpp
//

#include "StdAfx.h"
#include "PostApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostApp

BEGIN_MESSAGE_MAP(CPostApp, CWinApp)
        //{{AFX_MSG_MAP(CPostApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostApp construction

CPostApp::CPostApp(): m_hueinfo{nullptr}, m_saturationinfo{nullptr}, m_exposureinfo{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    string.LoadString(IDS_HUE);
    m_hueinfo = HFloatPropertyInfo::New(string, "Hue");
    m_hueinfo->SetMinValue(-180.0F);
    m_hueinfo->SetMaxValue(180.0F);
    m_hueinfo->SetDefaultValue(0.F);
    m_hueinfo->SetConstant(TRUE);

    string.LoadString(IDS_SATURATION);
    m_saturationinfo = HPercentPropertyInfo::New(string, "Saturation");
    m_saturationinfo->SetMaxValue(4.0F);
    m_saturationinfo->SetDefaultValue(1.F);
    m_saturationinfo->SetConstant(TRUE);
    // m_brightnessinfo->SetNotifyAnimObjectValueChanged( TRUE );

    string.LoadString(IDS_EXPOSURE);
    m_exposureinfo = HFloatPropertyInfo::New(string, "Exposure");
    m_exposureinfo->SetMinValue(-8.0F);
    m_exposureinfo->SetMaxValue(8.0F);
    m_exposureinfo->SetDefaultValue(0.F);
    m_exposureinfo->SetConstant(TRUE);
    // m_contrastinfo->SetNotifyAnimObjectValueChanged( TRUE );

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_hueinfo;
    delete m_saturationinfo;
    delete m_exposureinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
