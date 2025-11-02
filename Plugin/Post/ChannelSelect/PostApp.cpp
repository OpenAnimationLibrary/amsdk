// Yves  10/11/2006  \Master14.0\Plugin\Post\ChannelSelect\PostApp.cpp
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

CPostApp::CPostApp(): m_channeltypeinfo{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_channeltypes.SetArraySize(4);
    m_channeltypes[0]->SetMatchName("Red");
    string.LoadString(IDS_RCHANNEL);
    m_channeltypes[0]->SetLocalizedName(string.GetBuffer());
    m_channeltypes[1]->SetMatchName("Green");
    string.LoadString(IDS_GCHANNEL);
    m_channeltypes[1]->SetLocalizedName(string.GetBuffer());
    m_channeltypes[2]->SetMatchName("Blue");
    string.LoadString(IDS_BCHANNEL);
    m_channeltypes[2]->SetLocalizedName(string.GetBuffer());
    m_channeltypes[3]->SetMatchName("Alpha");
    string.LoadString(IDS_ACHANNEL);
    m_channeltypes[3]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_SELECT);
    m_channeltypeinfo = HTypePropertyInfo::New(string, "ChannelSelected", &m_channeltypes);
    m_channeltypeinfo->SetDefaultIndex(0);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    delete m_channeltypeinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
