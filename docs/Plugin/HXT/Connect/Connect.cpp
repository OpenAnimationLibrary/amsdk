// Connect.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Connect.h"
#include "Dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectApp

BEGIN_MESSAGE_MAP(CConnectApp, CWinApp)
        //{{AFX_MSG_MAP(CConnectApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectApp Konstruktion
CConnectApp::CConnectApp() = default;

CConnectApp::~CConnectApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CConnectApp-Objekt

CConnectApp theApp;

BOOL CConnectApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CConnectApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CConnectApp::OnModel(HModelCache *hmc) {

    para = new PARA;
    para->tol = GetRegistryValue("Connect HXT", "Tolerance", 0.01F);
    para->min_toleranz = GetRegistryValue("Connect HXT", "Min Tolerance", 1e12F);
    para->modus = GetRegistryValue("Connect HXT", "Modus", true);
    Dialog dlg1(para);
    if (dlg1.DoModal() != IDOK) {
        GetHProject()->UpdateAllViews(true);
        return true;
    }
    SetRegistryValue("Connect HXT", "Tolerance", para->tol);
    SetRegistryValue("Connect HXT", "Min Tolerance", para->min_toleranz);
    SetRegistryValue("Connect HXT", "Modus", para->modus);
    if (para->modus) {
        return ModelWorking(hmc);
    }
    return ModelCPWorking(hmc);
}
