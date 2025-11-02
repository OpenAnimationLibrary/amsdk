// Dan  4/26/2004  \DanLP110\Plugin\Post\VideoSafe\PostApp.cpp
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

CPostApp::CPostApp(): m_styleinfo{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_styletypes.SetArraySize(NUM_STYLES);
    m_styletypes[STYLE_NTSC]->SetMatchName("NTSC");
    string.LoadString(IDS_NTSC);
    m_styletypes[STYLE_NTSC]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_PAL]->SetMatchName("PAL");
    string.LoadString(IDS_PAL);
    m_styletypes[STYLE_PAL]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_VIDEOFORMAT);
    m_styleinfo = HTypePropertyInfo::New(string, "Format", &m_styletypes);
    m_styleinfo->SetDefaultIndex(STYLE_NTSC);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    delete m_styleinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
