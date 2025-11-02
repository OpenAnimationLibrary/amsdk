// Midi.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Midi.h"
#include "poseselect.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiApp

BEGIN_MESSAGE_MAP(CMidiApp, CWinApp)
        //{{AFX_MSG_MAP(CMidiApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidiApp Konstruktion
CMidiApp::CMidiApp() = default;

CMidiApp::~CMidiApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMidiApp-Objekt

CMidiApp theApp;

static void get_tracknames(const MidiFileEvent_t midi_event, void *user_data) {
    CString temp;
    temp.Empty();
    switch (MidiFileEvent_getType(midi_event)) {
        case MIDI_FILE_EVENT_TYPE_META:
            if (MidiFileMetaEvent_getNumber(midi_event) == 3) {
                temp = MidiFileMetaEvent_getData(midi_event);
                memcpy(user_data, temp, MidiFileMetaEvent_getDataLength(midi_event));
            }
            break;
        default: ;
    }
}

BOOL CMidiApp::InitApp() {

    CString temp;
    int i = 0;
    unsigned char buf[2048];
    static char BASED_CODE szFilter[] = "Midi Files (*.mid;*.midi)|*.mid; *.midi||";
    para->m_Tempo_az = 0;
    para->m_length = 0;
    para->m_aztrack = 0;
    para->m_trackname = nullptr;
    GetSettings();

    para->fps = GetHProject()->GetFPS();
    CFileDialog cdlg(TRUE, nullptr, para->m_name, 0, szFilter, CWnd::FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() != IDOK) {
        delete para;
        return TRUE;
    }
    if (para->m_name != cdlg.GetPathName()) {
        para->m_name = cdlg.GetPathName();
        para->m_track = 0;
    }
    if ((midi_file = MidiFile_load(para->m_name.GetBuffer(para->m_name.GetLength() + 10))) == nullptr) {
        temp = "Error loading " + para->m_name + " !";
        AfxMessageBox(temp,MB_OK | MB_ICONSTOP);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        delete para;
        return true;
    }
    switch (MidiFile_getFileFormat(midi_file)) {
        case 0:
            para->m_track = 0;
            break;
        case 1:
            for (track = MidiFile_getFirstTrack(midi_file); track != nullptr; track = MidiFileTrack_getNextTrack(track))
                para->m_aztrack++;
            para->m_trackname = new CString[para->m_aztrack + 1];
            i = 0;
            for (track = MidiFile_getFirstTrack(midi_file); track != nullptr; track = MidiFileTrack_getNextTrack(track)) {
                if (i > 0) {
                    memset(buf, 0, sizeof buf);
                    MidiFileTrack_visitEvents(track, get_tracknames, buf);
                    temp.Format("Track %d %p", i, buf);
                    para->m_trackname[i] = temp;
                }
                i++;
            }
            break;
        case 2:
            temp = "False midiformat " + para->m_name + " !\n Only midifileformat type 0 and 1 supportet";
            AfxMessageBox(temp,MB_OK | MB_ICONSTOP);
            GetHProject()->UpdateAllViews(TRUE);
            RefreshAllTrees();
            delete para;
            return true;
    }
    if (MidiFile_getDivisionType(midi_file) == -1) {
        temp = "Unknown division type " + para->m_name + " !\nOnly PPQ and SMTPE supportet";
        AfxMessageBox(temp,MB_OK | MB_ICONSTOP);
        MidiFile_free(midi_file);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();

        delete [] para->m_trackname;
        delete para;
        return true;
    }
    GetMidiTiming();
    if (para->p_type == HOT_COLOR) {
        para->p_min_f = ((HColorProperty *)para->p_property)->GetCOLORREF();
    }
    para->m_midi = midi_file;
    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        MidiFile_free(midi_file);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        delete [] para->m_trackname;
        delete para;
        return true;
    }
    SaveSettings();
    frameevent = new FrameEvent[para->az_frames + 1];
    MainWorking();
    delete [] frameevent;
    MidiFile_free(midi_file);
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();

    delete [] para->m_trackname;
    delete para;
    return true;
}

BOOL CMidiApp::OnProperty(HProperty *htreeobject) {
    para = new Parameter;
    para->p_property = htreeobject;
    para->p_name = htreeobject->GetName();
    para->p_fullname = htreeobject->GetFullName();
    para->p_type = htreeobject->GetObjectType();
    para->p_iscolor = false;

    //Sonderbehandlung fuer Lichtintensitaet und alles andere 
    if (para->p_name == "Intensity") {
        if (para->p_property->GetParent()->GetObjectType() == HOT_LIGHT)
            para->p_type = HOT_PERCENT;
    }
    if (para->p_fullname.Find("Surface.DiffuseFalloff") > 0)
        para->p_type = HOT_PERCENT;
    if (para->p_fullname.Find("Surface.SpecularIntensity") > 0)
        para->p_type = HOT_PERCENT;
    if (para->p_fullname.Find("Surface.Roughness") > 0)
        para->p_type = HOT_PERCENT;
    if (para->p_fullname.Find("Surface.RoughnessScale") > 0)
        para->p_type = HOT_PERCENT;
    if (para->p_fullname.Find("Surface.Density") > 0)
        para->p_type = HOT_FLOAT;
    /*
       if (((para->p_fullname.Find("Color.Red")) >0) || ((para->p_fullname.Find("Color.Green")) >0) || ((para->p_fullname.Find("Color.Blue")) >0)) {
          para->p_iscolor = true;
          para->p_type = HOT_COLOR;
       } else {
          para->p_iscolor = false;
       }
    */
    //	para->p_iscolor = true;
    //Check ob Action
    para->isaction = 0;
    HTreeObject *parent = para->p_property->GetParent();
    if (parent->GetObjectType() == HOT_ACTION) {
        para->haction = (HAction *)parent;
        para->isaction = 1;
    } else {
        while ((parent = parent->GetParent())) {
            if (parent->GetObjectType() == HOT_ACTION) {
                para->haction = (HAction *)parent;
                para->isaction = 1;
                break;
            }
        }
    }

    return InitApp();
}

BOOL CMidiApp::OnModel(HModel *htreeobject) {
    para = new Parameter;
    para->hm_org = htreeobject;
    poseselect dlg(para);
    if (dlg.DoModal() != IDOK)
        return true;
    para->p_iscolor = FALSE;
    para->isaction = 0;
    return InitApp();
}

BOOL CMidiApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMidiApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
