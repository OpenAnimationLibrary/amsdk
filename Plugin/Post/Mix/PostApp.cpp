// NAP  3/3/2003  \Noel105\Plugin\Post\Add\PostApp.cpp
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

CPostApp::CPostApp(): m_percentinfo1{nullptr}, m_percentinfo2{nullptr} {}

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here

    string.LoadString(IDS_PERCENT1);
    m_percentinfo1 = HPercentPropertyInfo::New(string, "Input1Percent");
    m_percentinfo1->SetMinValue(-hash_constants::max_float);
    m_percentinfo1->SetDefaultValue(1.F);
    m_percentinfo1->SetMaxValue(hash_constants::max_float);
    m_percentinfo1->SetNotifyAnimObjectValueChanged(TRUE);
    m_percentinfo1->SetConstant(TRUE);

    string.LoadString(IDS_PERCENT2);
    m_percentinfo2 = HPercentPropertyInfo::New(string, "Input2Percent");
    m_percentinfo2->SetMinValue(-hash_constants::max_float);
    m_percentinfo2->SetDefaultValue(1.F);
    m_percentinfo2->SetMaxValue(hash_constants::max_float);
    m_percentinfo2->SetNotifyAnimObjectValueChanged(TRUE);
    m_percentinfo2->SetConstant(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_percentinfo1;
    delete m_percentinfo2;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
