// Dan  3/24/2003  \DanLP105\Plugin\HXT\Grid\Hxt.cpp
//

#include "StdAfx.h"
#include "Hxt.h"
#include "GridDialog.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHxtApp

BEGIN_MESSAGE_MAP(CHxtApp, CWinApp)
    //{{AFX_MSG_MAP(CHxtApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHxtApp construction

//extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/);

CHxtApp::CHxtApp() = default;

CHxtApp::~CHxtApp() = default;

/////////////////////////////////////////////////////////////////////////////
// The one and only CHxtApp object

CHxtApp theApp;

BOOL CHxtApp::OnGridWizard(HModelCache *hmc) {
    CGridDialog dlg(&m_parameters);
    if (dlg.DoModal() != IDOK)
        return TRUE;
    if (nullptr == hmc) {
        hmc = HModelCache::New();
        makegroup = FALSE;
    } else {
        makegroup = TRUE;
    }
    return NewShape(hmc);
}

BOOL CHxtApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

int CHxtApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
