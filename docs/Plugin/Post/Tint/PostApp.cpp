// NAP  3/3/2003  \Noel105\Plugin\Post\Tint\PostApp.cpp
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

CPostApp::CPostApp(): m_styleinfo{nullptr}, m_lightcolorinfo{nullptr}, m_darkcolorinfo{nullptr}, m_percentinfo{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_styletypes.SetArraySize(NUM_STYLES);
    m_styletypes[STYLE_BW]->SetMatchName("BW");
    string.LoadString(IDS_BW);
    m_styletypes[STYLE_BW]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_COBALT]->SetMatchName("Cobalt");
    string.LoadString(IDS_COBALT);
    m_styletypes[STYLE_COBALT]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_SEPIA]->SetMatchName("Sepia");
    string.LoadString(IDS_SEPIA);
    m_styletypes[STYLE_SEPIA]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_XRAY]->SetMatchName("XRay");
    string.LoadString(IDS_XRAY);
    m_styletypes[STYLE_XRAY]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_RAINBOW]->SetMatchName("Rainbow");
    string.LoadString(IDS_RAINBOW);
    m_styletypes[STYLE_RAINBOW]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_CUSTOM]->SetMatchName("Custom");
    string.LoadString(IDS_CUSTOM);
    m_styletypes[STYLE_CUSTOM]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_STYLE);
    m_styleinfo = HTypePropertyInfo::New(string, "Style", &m_styletypes);
    m_styleinfo->SetDefaultIndex(STYLE_BW);

    string.LoadString(IDS_LIGHTCOLOR);
    m_lightcolorinfo = HColorPropertyInfo::New(string, "LightColor");
    m_lightcolorinfo->GetRed()->SetDefaultValue(1.F);
    m_lightcolorinfo->GetGreen()->SetDefaultValue(1.F);
    m_lightcolorinfo->GetBlue()->SetDefaultValue(1.F);
    m_lightcolorinfo->SetNotifyAnimObjectValueChanged(TRUE);
    m_lightcolorinfo->SetConstant(TRUE);

    string.LoadString(IDS_DARKCOLOR);
    m_darkcolorinfo = HColorPropertyInfo::New(string, "DarkColor");
    m_darkcolorinfo->GetRed()->SetDefaultValue(0.F);
    m_darkcolorinfo->GetGreen()->SetDefaultValue(0.F);
    m_darkcolorinfo->GetBlue()->SetDefaultValue(0.F);
    m_darkcolorinfo->SetNotifyAnimObjectValueChanged(TRUE);
    m_darkcolorinfo->SetConstant(TRUE);

    string.LoadString(IDS_PERCENT);
    m_percentinfo = HPercentPropertyInfo::New(string, "Percent");
    m_percentinfo->SetDefaultValue(1.F);
    //   m_percentinfo->SetNotifyAnimObjectValueChanged( TRUE );
    //   m_percentinfo->SetConstant(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_lightcolorinfo;
    delete m_darkcolorinfo;
    delete m_percentinfo;
    delete m_styleinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
