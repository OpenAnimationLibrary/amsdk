// Setposition.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Setposition.h"
#include "posdlg.h"
#include "posdlg1.h"

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
// CSetpositionApp

BEGIN_MESSAGE_MAP(CSetpositionApp, CWinApp)
        //{{AFX_MSG_MAP(CSetpositionApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetpositionApp Konstruktion

CSetpositionApp::CSetpositionApp() = default;

CSetpositionApp::~CSetpositionApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CSetpositionApp-Objekt

CSetpositionApp theApp;

BOOL CSetpositionApp::OnSetGroup(HModelCache *hmc, HGroup *gh) {
    m_parameters.m_x = FALSE;
    m_parameters.m_y = FALSE;
    m_parameters.m_z = FALSE;
    m_parameters.mirror_x = FALSE;
    m_parameters.mirror_y = FALSE;
    m_parameters.mirror_z = FALSE;
    m_parameters.translate_bone.x = 0.F;
    m_parameters.translate_bone.y = 0.F;
    m_parameters.translate_bone.z = 0.F;
    m_parameters.cp_group = FALSE;

    posdlg dlg(&m_parameters);
    if (dlg.DoModal() != IDOK)
        return true;

    return SetPosition(hmc, gh);
}

BOOL CSetpositionApp::OnSetBone(HModelCache *hmc, HBone *hb) {
    posdlg1 dlg(&m_parameters);
    if (dlg.DoModal() != IDOK)
        return true;

    if (!m_parameters.translate && !m_parameters.rotate)
        return true;
    return SetBone(hmc, hb);
}

BOOL CSetpositionApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CSetpositionApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
