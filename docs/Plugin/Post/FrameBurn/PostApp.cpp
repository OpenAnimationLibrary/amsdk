// NAP  9/11/2003  \Noelsrv105\Plugin\Post\FrameBurn\PostApp.cpp
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

CPostApp::CPostApp() = default;

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    // New Infos here
    CString string;
    string.LoadString(IDS_FONTSCALE);
    m_fontscaleinfo = HPercentPropertyInfo::New(string, "FontScale");
    m_fontscaleinfo->SetMinValue(0.F);
    m_fontscaleinfo->SetDefaultValue(1.F);
    m_fontscaleinfo->SetMaxValue(1000.F);
    m_fontscaleinfo->SetConstant(TRUE);

    m_opacityinfo = HPercentPropertyInfo::New("Opacity", "Opacity");
    m_opacityinfo->SetMinValue(0.01F);
    m_opacityinfo->SetDefaultValue(0.75F);
    m_opacityinfo->SetMaxValue(1.F);
    m_opacityinfo->SetConstant(TRUE);

    m_displaynameinfo = HBoolPropertyInfo::New("Display name", "DisplayName");
    m_displaynameinfo->SetDefaultValue(TRUE);
    m_displayshadowinfo = HBoolPropertyInfo::New("With shadows", "WithShadows");
    m_displayshadowinfo->SetDefaultValue(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_fontscaleinfo;
    delete m_opacityinfo;
    delete m_displaynameinfo;
    delete m_displayshadowinfo;
    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
