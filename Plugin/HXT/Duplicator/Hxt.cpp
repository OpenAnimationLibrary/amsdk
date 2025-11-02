// Dan  3/24/2003  \DanLP105\Plugin\HXT\Duplicator\Hxt.cpp
//

#include "StdAfx.h"
#include "Hxt.h"
#include "DupDialog.h"
#include "SDK/HProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHxtApp

BEGIN_MESSAGE_MAP(CHxtApp, CWinApp)
    //{{AFX_MSG_MAP(CWizardApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHxtApp construction

CHxtApp::CHxtApp() = default;

/////////////////////////////////////////////////////////////////////////////
// The one and only CWizardApp object

CHxtApp theApp;

/*
BOOL CHxtApp::OnDupGroup(HModelCache *hmc, HGroup *hg)
{
    m_parameters.m_hmc = hmc;
    CDupDialog dlg(&m_parameters);
    if (dlg.DoModal()!=IDOK)
        return TRUE;

    return SpinShape(hmc, hg);
}
*/

BOOL CHxtApp::OnDupGroup(HModelCache *hmc, HGroup *hg) {
    m_parameters.m_hmc = hmc;
    CDupDialog dlg(&m_parameters);
    if (dlg.DoModal() != IDOK)
        return TRUE;

    //change instances , if any, for preventing nonetheless realocation musclecp data
    const BOOL chor_changed = hmc->IsInChorOrAction();
    HModelCache *hmc_temp = nullptr;
    if (chor_changed) {
        hmc_temp = HModelCache::New("temp_dupmodel", true);
        hmc->ChangeShortCuts(hmc_temp);
    }

    CWaitCursor wait;
    SpinShape(hmc, hg);
    hmc->Update();
    if (chor_changed) {
        hmc_temp->ChangeShortCuts(hmc);
        HProject::DeleteHandle(hmc_temp);
    }
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();

    return TRUE;
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
