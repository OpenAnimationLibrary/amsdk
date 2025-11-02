// sample.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "stdafx.h"
#include "sample.h"
//zusaetzliche Includes
#include "sample_dialog.h"
#include "F_Protos.h"
#include "Localize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
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
// CSampleApp

BEGIN_MESSAGE_MAP(CSampleApp, CWinApp)
	//{{AFX_MSG_MAP(CSampleApp)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleApp Konstruktion

CSampleApp::CSampleApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CSampleApp-Objekt

CSampleApp theApp;

BOOL CSampleApp::OnSampleWizard(HModelCache *hmc)
{
   sample_dialog dlg(NULL);
   if (dlg.DoModal()!=IDOK)
      return TRUE;

   return TRUE; //hier wird ansonsten die Funktion zurueckgegeben, die etwas bewirken soll
                // z.B. return NewShape(hmc) , zu sehen in Grid\HXT.cpp Grid\evalute.cpp
}

BOOL CSampleApp::InitInstance()
{
   SetAppLocalizationDLL(m_hInstance);
        return CWinApp::InitInstance();
}

int CSampleApp::ExitInstance()
{
   return CWinApp::ExitInstance();
}