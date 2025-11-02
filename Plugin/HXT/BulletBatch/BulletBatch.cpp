// BulletBatch.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "BulletBatch.h"
#include "PDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBulletBatchApp

BEGIN_MESSAGE_MAP(CBulletBatchApp, CWinApp)
    //{{AFX_MSG_MAP(CBulletBatchApp)
    // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBulletBatchApp Konstruktion

/////////////////////////////////////////////////////////////////////////////
// Das einzige CBulletBatchApp-Objekt

CBulletBatchApp theApp;

BOOL CBulletBatchApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CBulletBatchApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CBulletBatchApp::OnChor(HChor *hchor) {

    PDialog pdlg(hchor);

    if (pdlg.DoModal() != IDOK) {
        return TRUE;
    }
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return TRUE;

}
