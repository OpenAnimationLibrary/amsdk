// Midicontrol.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Midicontrol.h"
#include "Mididevice.h"
#include "Assign.h"
#include "Record.h"

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
// CMidicontrolApp

BEGIN_MESSAGE_MAP(CMidicontrolApp, CWinApp)
        //{{AFX_MSG_MAP(CMidicontrolApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidicontrolApp Konstruktion
CMidicontrolApp::CMidicontrolApp() = default;

CMidicontrolApp::~CMidicontrolApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMidicontrolApp-Objekt

CMidicontrolApp theApp;

BOOL CMidicontrolApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMidicontrolApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CMidicontrolApp::Init() const {
    CString temp;
    char *stopstring;

    para->hproject = GetHProject();
    para->fps = para->hproject->GetFPS();
    para->first_midi_in_list_node = nullptr;
    para->midi_device = 0;
    para->midi_device_run = 0;
    para->obj_selectet = 0;
    para->ssforward = RGB(0,0,0);
    para->teiler = (unsigned int)(1000 / para->fps);
    para->end_frame = para->chor->GetTotalTime()->GetValue().GetFrame(para->fps);
    para->override = 0;
    para->embed = GetRegistryValue("Midicontrol HXT", "embed", 0);
    String forward = GetRegistryString("Midicontrol HXT", "forward", "0");
    temp.Format("%s", forward.Get());
    para->ssforward = strtoul(temp, &stopstring, 10);

    //MidiDevices suchen
    int max = midiInGetNumDevs();
    if (max > 1) {
        //Mehr als 1 Device
        Mididevice ds_dlg(para);
        if (ds_dlg.DoModal() != IDOK) {
            delete [] para;
            return TRUE;
        }
    } else {
        para->midi_device = 0;
    }

    if (para->first_midi_in_list_node == nullptr) {
        para->first_midi_in_list_node = new (midi_in_list_node);
        para->first_midi_in_list_node->midi_in_number = para->midi_device;
        para->first_midi_in_list_node->next_midi_in_list_node = nullptr;
    }

    if (para->embed)
        LoadEmbed();

    //Assign Controller
    Assign as_dlg(para);
    if (as_dlg.DoModal() != IDOK) {
        delete [] para;
        return TRUE;
    }

    SetRegistryValue("Midicontrol HXT", "embed", para->embed);
    temp.Format("%lu", para->ssforward);
    SetRegistryString("Midicontrol HXT", "forward", temp);
    if (para->embed)
        SaveEmbed();

    // Record
    Record r_dlg(para);
    if (r_dlg.DoModal() != IDOK) {
        //Keys loeschen
        DeleteKeys();
        para->hproject->SetTime(Time());
        para->chor->SetTime(Time());
        para->hproject->UpdateAllViews(TRUE);
        RefreshAllTrees();
        delete [] para;
        return TRUE;
    }

    para->hproject->SetTime(Time());
    para->chor->SetTime(Time());
    para->hproject->UpdateAllViews(TRUE);
    RefreshAllTrees();
    delete [] para;
    return TRUE;
}

BOOL CMidicontrolApp::Objectstart(HHashObject *hobject) {

    para = new PARAMETER;
    para->azobject = 1;
    para->obj = new OBJECT[1];
    para->obj[0].hobj = hobject;
    para->obj[0].name = hobject->GetName();
    para->obj[0].matchname = hobject->GetMatchName();
    para->obj[0].Filter = 0;
    //Find the properties
    para->obj[0].azprop = GetAzProp(hobject);
    //allocate properties
    para->obj[0].prop = new PROPERTIE[para->obj[0].azprop];
    GetProperties(0);
    para->chor = (HChor *)hobject->GetParent(); //gibt chor auch bei action zurueck ?! 
    const String temp = hobject->GetParent()->GetFullName();
    if (temp.Find("|Actions|") == -1) {
        para->isaction = 0;
    } else {
        para->isaction = 1;
    }

    return Init();
}

BOOL CMidicontrolApp::Chorstart(HChor *hchor) {
    para = new PARAMETER;
    Chorworking(hchor);
    para->chor = hchor;
    para->isaction = 0;
    return Init();
}
