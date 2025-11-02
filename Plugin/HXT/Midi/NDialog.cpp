// NDialog.cpp: Implementierungsdatei
//
#include "StdAfx.h"
#include "Midi.h"
#include "NDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

NDialog::NDialog(Parameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(NDialog)
    // HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
    m_parameters = parameters;
    //}}AFX_DATA_INIT
}

void NDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(NDialog)
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(NDialog, CDialog)
    //{{AFX_MSG_MAP(NDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten NDialog 
int GetMidiFrame1(const long ticks, const Parameter *para) {

    if (para->m_Tempo_az == 0) {
        return ROUNDOFF(ticks * para->m_Tempo[0].m_tickSize * para->fps);
    }
    double length = 0;
    for (int i = 0; i < para->m_Tempo_az; ++i) {
        if (ticks <= para->m_Tempo[i].end_tick) {
            length += (ticks - para->m_Tempo[i].beginn_tick) * para->m_Tempo[i].m_tickSize;
            return ROUNDOFF(para->fps * length);
        }
        length += (para->m_Tempo[i].end_tick - para->m_Tempo[i].beginn_tick) * para->m_Tempo[i].m_tickSize;
    }
    return 0;
}

BOOL NDialog::GetMidiFrameEvents() {
    int i, note, velo, frame;
    long ticks;
    MidiFileEvent_t midi_event;
    MidiFileEventType_t eventtype;
    MidiFileTrack_t track1;
    CString temp, temp1;
    unsigned char buf[2048];
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST2);
    temp.Format("Frame%5sEvent%5sNote%5sVol", " ", " ", " ");
    id1->AddString(temp);
    id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    if (m_parameters->m_track > 0) {
        track1 = MidiFile_getFirstTrack(m_parameters->m_midi);
        for (i = 0; i < m_parameters->m_track; ++i) {
            track1 = MidiFileTrack_getNextTrack(track1);
        }
        for (midi_event = MidiFileTrack_getFirstEvent(track1); midi_event; midi_event = MidiFileEvent_getNextEvent(midi_event)) {
            ticks = MidiFileEvent_getTick(midi_event);
            eventtype = MidiFileEvent_getType(midi_event);
            switch (eventtype) {
                case MIDI_FILE_EVENT_TYPE_META:
                    if (MidiFileMetaEvent_getNumber(midi_event) == 3) {
                        memset(buf, 0, sizeof buf);
                        temp1.Empty();
                        temp1 = MidiFileMetaEvent_getData(midi_event);
                        memcpy(buf, temp1, MidiFileMetaEvent_getDataLength(midi_event));
                        temp.Format("*** Track %d %p ***", i, buf);
                        id1->AddString(temp);
                    }
                    break;
                case MIDI_FILE_EVENT_TYPE_NOTE_ON:
                    frame = GetMidiFrame1(ticks, m_parameters);
                    note = MidiFileNoteOnEvent_getNote(midi_event);
                    velo = MidiFileNoteOnEvent_getVelocity(midi_event); //Lautstaerke
                    temp.Format("%05d%5sNote on  %5s%5s%03d", frame, " ", mnote[note].GetBuffer(), " ", velo);
                    id1->AddString(temp);
                    break;
                case MIDI_FILE_EVENT_TYPE_NOTE_OFF:
                    frame = GetMidiFrame1(ticks, m_parameters);
                    note = MidiFileNoteOffEvent_getNote(midi_event);
                    velo = MidiFileNoteOffEvent_getVelocity(midi_event);
                    temp.Format("%05d%5sNote off %5s%5s%03d", frame, " ", mnote[note].GetBuffer(), " ", velo);
                    id1->AddString(temp);
                    break;
                default: ;
            }
        }
    } else {
        i = 0;
        for (track1 = MidiFile_getFirstTrack(m_parameters->m_midi); track1 != nullptr; track1 = MidiFileTrack_getNextTrack(track1)) {
            for (midi_event = MidiFileTrack_getFirstEvent(track1); midi_event; midi_event = MidiFileEvent_getNextEvent(midi_event)) {
                ticks = MidiFileEvent_getTick(midi_event);
                eventtype = MidiFileEvent_getType(midi_event);
                switch (eventtype) {
                    case MIDI_FILE_EVENT_TYPE_META:
                        if (MidiFileMetaEvent_getNumber(midi_event) == 3) {
                            memset(buf, 0, sizeof buf);
                            temp1.Empty();
                            temp1 = MidiFileMetaEvent_getData(midi_event);
                            memcpy(buf, temp1, MidiFileMetaEvent_getDataLength(midi_event));
                            temp.Format("*** Track %d %p ***", i, buf);
                            id1->AddString(temp);
                        }
                        break;
                    case MIDI_FILE_EVENT_TYPE_NOTE_ON:
                        frame = GetMidiFrame1(ticks, m_parameters);
                        note = MidiFileNoteOnEvent_getNote(midi_event);
                        velo = MidiFileNoteOnEvent_getVelocity(midi_event); //Lautstaerke
                        temp.Format("%05d%5sNote on  %5s%5s%03d", frame, " ", mnote[note].GetBuffer(), " ", velo);
                        id1->AddString(temp);
                        break;
                    case MIDI_FILE_EVENT_TYPE_NOTE_OFF:
                        frame = GetMidiFrame1(ticks, m_parameters);
                        note = MidiFileNoteOffEvent_getNote(midi_event);
                        velo = MidiFileNoteOffEvent_getVelocity(midi_event);
                        temp.Format("%05d%5sNote off %5s%5s%03d", frame, " ", mnote[note].GetBuffer(), " ", velo);
                        id1->AddString(temp);
                        break;
                    default: ;
                }
            }
            i++;
        }
    }
    return TRUE;
}

BOOL NDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    int k;
    const CString Keys[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    const CString Keys1[12] = {"C", "Db", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};
    int j = 0;
    if (m_parameters->cakewalk) {
        k = 0;
    } else {
        k = -2;
    }
    for (int i = 0; i < 128; ++i) {
        mnote[i].Format(" %d", k);
        if (m_parameters->cakewalk) {
            mnote[i] = Keys1[j] + mnote[i];
            //			mnote[i].Format("%s %d",Keys1[j],k);
        } else {
            mnote[i] = Keys[j] + mnote[i];
            //			mnote[i].Format("%s %d",Keys[j],k);
        }
        j++;
        if (j == 12) {
            j = 0;
            k++;
        }
    }

    GetMidiFrameEvents();
    // TODO: Zusõtzliche Initialisierung hier einf³gen

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur³ckgeben
}
