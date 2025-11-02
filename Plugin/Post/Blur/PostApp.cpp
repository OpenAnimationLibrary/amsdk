// NAP  3/3/2003  \Noel105\Plugin\Post\Blur\PostApp.cpp
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

CPostApp::CPostApp(): m_styleinfo{nullptr}, m_softnessinfo{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_styletypes.SetArraySize(NUM_STYLES);
    m_styletypes[STYLE_8MM]->SetMatchName("8MM");
    string.LoadString(IDS_8MM);
    m_styletypes[STYLE_8MM]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_16MM]->SetMatchName("16MM");
    string.LoadString(IDS_16MM);
    m_styletypes[STYLE_16MM]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_35MM]->SetMatchName("35MM");
    string.LoadString(IDS_35MM);
    m_styletypes[STYLE_35MM]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_CUSTOM]->SetMatchName("Custom");
    string.LoadString(IDS_CUSTOM);
    m_styletypes[STYLE_CUSTOM]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_STYLE);
    m_styleinfo = HTypePropertyInfo::New(string, "Style", &m_styletypes);
    m_styleinfo->SetDefaultIndex(STYLE_8MM);

    string.LoadString(IDS_SOFTNESS);
    m_softnessinfo = HFloatPropertyInfo::New(string, "Softness");
    m_softnessinfo->SetDefaultValue(10.F);
    m_softnessinfo->SetMinValue(0.F);
    m_softnessinfo->SetMaxValue(100.0F);
    m_softnessinfo->SetDocumentation("Min Value 0 Max Value 100");
    m_softnessinfo->SetConstant(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_softnessinfo;
    delete m_styleinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
