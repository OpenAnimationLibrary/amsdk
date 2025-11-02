// NAP  3/3/2003  \Noel105\Plugin\Post\MinMedMax\PostApp.cpp
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

CPostApp::CPostApp(): m_styleinfo{nullptr}, m_posinfo{nullptr}, m_radiusinfo{nullptr}, m_isroundinfo{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_styletypes.SetArraySize(NUM_STYLES);
    m_styletypes[STYLE_MIN]->SetMatchName("Minimum");
    string.LoadString(IDS_MINIMUM);
    m_styletypes[STYLE_MIN]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_MED]->SetMatchName("Medium");
    string.LoadString(IDS_MEDIUM);
    m_styletypes[STYLE_MED]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_MAX]->SetMatchName("Maximum");
    string.LoadString(IDS_MAXIMUM);
    m_styletypes[STYLE_MAX]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_CUSTOM]->SetMatchName("Custom");
    string.LoadString(IDS_CUSTOM);
    m_styletypes[STYLE_CUSTOM]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_STYLE);
    m_styleinfo = HTypePropertyInfo::New(string, "Style", &m_styletypes);
    m_styleinfo->SetDefaultIndex(STYLE_MED);
    string.LoadString(IDS_MINMEDMAXPOS);
    m_posinfo = HPercentPropertyInfo::New(string, "Pos");
    m_posinfo->SetDefaultValue(POS_MED);
    m_posinfo->SetConstant(TRUE);

    string.LoadString(IDS_RADIUS);
    m_radiusinfo = HIntPropertyInfo::New(string, "Radius");
    m_radiusinfo->SetDefaultValue(1);
    m_radiusinfo->SetMinValue(1);
    m_radiusinfo->SetMaxValue(24);
    m_radiusinfo->SetConstant(TRUE);

    string.LoadString(IDS_ROUND);
    m_isroundinfo = HBoolPropertyInfo::New(string, "Round");
    m_isroundinfo->SetDefaultValue(TRUE);
    m_isroundinfo->SetConstant(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_radiusinfo;
    delete m_isroundinfo;
    delete m_posinfo;
    delete m_styleinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
