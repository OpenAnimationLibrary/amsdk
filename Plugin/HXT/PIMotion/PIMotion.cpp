// PIMotion.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "PIMotion.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

//
//	Beachten Sie!
//
//		Wird diese DLL dynamisch an die MFC-DLLs gebunden,
//		muss bei allen von dieser DLL exportierten Funktionen,
//		die MFC-Aufrufe durchführen, das Makro AFX_MANAGE_STATE
//		direkt am Beginn der Funktion eingefügt sein.
//
//		Beispiel:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState())
//		// Hier normaler Funktionsrumpf
//		}
//
//		Es ist sehr wichtig, dass dieses Makro in jeder Funktion
//		vor allen MFC-Aufrufen erscheint. Dies bedeutet, dass es
//		als erste Anweisung innerhalb der Funktion ausgeführt werden
//		muss, sogar vor jeglichen Deklarationen von Objektvariablen,
//		da ihre Konstruktoren Aufrufe in die MFC-DLL generieren
//		könnten.
//
//		Siehe MFC Technical Notes 33 und 58 für weitere
//		Details.
//

/////////////////////////////////////////////////////////////////////////////
// CPIMotionApp

BEGIN_MESSAGE_MAP(CPIMotionApp, CWinApp)
        //{{AFX_MSG_MAP(CPIMotionApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPIMotionApp Konstruktion

CPIMotionApp::CPIMotionApp() = default;

CPIMotionApp::~CPIMotionApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CPIMotionApp-Objekt

CPIMotionApp theApp;

BOOL CPIMotionApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CPIMotionApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CPIMotionApp::OnChor(HChor *htreeobject) {

    if (!htreeobject->GetChildCamera()) {
        AfxMessageBox("This plugin needs at least one camera in the chor !",MB_ICONERROR);
        return TRUE;
    }

    m_para = new PParameters;

    m_para->hchor = htreeobject;
    m_para->endframe = 0;
    m_para->startframe = 0;
    m_para->height = 0;
    m_para->width = 0;
    m_para->trackpoint = 0;
    m_para->hcam = nullptr;
    m_para->hgroup = nullptr;
    m_para->htracking = nullptr;
    m_para->fps = GetHProject()->GetFPS();
    m_para->filename = "PImotion.txt";

    PDialog dlg(m_para);
    if (dlg.DoModal() != IDOK) {
        delete m_para;
        GetHProject()->UpdateAllViews(true);
        RefreshAllTrees();
        return true;
    }
    ChorWorking(htreeobject);

    delete m_para;
    GetHProject()->UpdateAllViews(true);
    RefreshAllTrees();
    return true;
}
