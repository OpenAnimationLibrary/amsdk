// DeleteKeys.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "DeleteKeys.h"
#include "PDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteKeysApp

BEGIN_MESSAGE_MAP(CDeleteKeysApp, CWinApp)
        //{{AFX_MSG_MAP(CDeleteKeysApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteKeysApp Konstruktion

CDeleteKeysApp::CDeleteKeysApp() = default;

CDeleteKeysApp::~CDeleteKeysApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CDeleteKeysApp-Objekt

CDeleteKeysApp theApp;

BOOL CDeleteKeysApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CDeleteKeysApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CDeleteKeysApp::OnChor(HChor *hchor) {

    PDialog pdlg(hchor);

    if (pdlg.DoModal() != IDOK) {
        return TRUE;
    }
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;

}
