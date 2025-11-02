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

CPostApp::CPostApp(): m_exposureinfo{nullptr}, m_brightnessinfo{nullptr}, m_contrastinfo{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    string.LoadString(IDS_EXPOSURE);
    m_exposureinfo = HFloatPropertyInfo::New(string, "Exposure");
    m_exposureinfo->SetMinValue(-8.0F);
    m_exposureinfo->SetMaxValue(8.0F);
    m_exposureinfo->SetDefaultValue(0.F);
    m_exposureinfo->SetConstant(TRUE);

    string.LoadString(IDS_BRIGHTNESS);
    m_brightnessinfo = HPercentPropertyInfo::New(string, "Brightness");
    m_brightnessinfo->SetDefaultValue(0.5F);
    m_brightnessinfo->SetConstant(TRUE);
    // m_brightnessinfo->SetNotifyAnimObjectValueChanged( TRUE );

    string.LoadString(IDS_CONTRAST);
    m_contrastinfo = HPercentPropertyInfo::New(string, "Contrast");
    m_contrastinfo->SetDefaultValue(0.5F);
    m_contrastinfo->SetConstant(TRUE);
    // m_contrastinfo->SetNotifyAnimObjectValueChanged( TRUE );

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_exposureinfo;
    delete m_brightnessinfo;
    delete m_contrastinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
