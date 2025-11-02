// KB  6/7/00  \Ken85\Plugin\Wizards\Grid\Wizard.cpp
//

#include "StdAfx.h"
#include "Wizard.h"
#include "WizardDialog.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizardApp

BEGIN_MESSAGE_MAP(CWizardApp, CWinApp)
    //{{AFX_MSG_MAP(CWizardApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardApp construction
CWizardApp::CWizardApp() = default;

CWizardApp::~CWizardApp() = default;

/////////////////////////////////////////////////////////////////////////////
// The one and only CWizardApp object

CWizardApp theApp;

BOOL CWizardApp::OnGridWizard(HModelCache *hmc) {
    CWizardDialog dlg(&m_parameters);
    if (dlg.DoModal() != IDOK)
        return TRUE;
    if (nullptr == hmc) {
        hmc = HModelCache::New();
        makegroup = FALSE;
    } else {
        makegroup = TRUE;
    }
    return NewShape(hmc, &dlg);
}

BOOL CWizardApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

int CWizardApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
