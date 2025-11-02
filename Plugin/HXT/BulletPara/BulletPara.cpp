// BulletPara.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "BulletPara.h"
#include "PDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBulletParaApp

BEGIN_MESSAGE_MAP(CBulletParaApp, CWinApp)
    //{{AFX_MSG_MAP(CBulletParaApp)
    // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBulletParaApp Konstruktion

/////////////////////////////////////////////////////////////////////////////
// Das einzige CBulletParaApp-Objekt

CBulletParaApp theApp;

BOOL CBulletParaApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CBulletParaApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CBulletParaApp::OnChor(HChor *hchor) {

    PDialog pdlg(hchor);

    if (pdlg.DoModal() != IDOK) {
        return TRUE;
    }
    //   GetHProject()->UpdateAllViews(TRUE);
    //   RefreshAllTrees();
    return TRUE;

}
