// primitive.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "primitive.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrimitiveApp

BEGIN_MESSAGE_MAP(CPrimitiveApp, CWinApp)
        //{{AFX_MSG_MAP(CPrimitiveApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrimitiveApp Konstruktion
CPrimitiveApp::CPrimitiveApp() = default;

CPrimitiveApp::~CPrimitiveApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CPrimitiveApp-Objekt

CPrimitiveApp theApp;

BOOL CPrimitiveApp::OnPrimitiveWizard(HModelCache *hmc) {

    m_parameters.hinstance = m_hInstance;
    PDialog dlg(&m_parameters);
    if (dlg.DoModal() != IDOK)
        return TRUE;

    if (hmc == nullptr) {
        hmc = HModelCache::New(nullptr,TRUE);
    }
    return BuildModel(hmc);
}

BOOL CPrimitiveApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

int CPrimitiveApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
