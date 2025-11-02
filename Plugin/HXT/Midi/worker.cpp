#include "StdAfx.h"
#include "Midi.h"

void CMidiApp::SaveSettings() const {
    SetRegistryValue("Midi HXT", "m_track", para->m_track);
    SetRegistryValue("Midi HXT", "m_control", para->m_control);
    SetRegistryValue("Midi HXT", "p_min", para->p_min);
    SetRegistryValue("Midi HXT", "p_max", para->p_max);
    SetRegistryValue("Midi HXT", "m_min", para->m_min);
    SetRegistryValue("Midi HXT", "m_max", para->m_max);
    SetRegistryValue("Midi HXT", "bool_prop", para->bool_prop);
    SetRegistryValue("Midi HXT", "reduce", para->reduce);
    SetRegistryValue("Midi HXT", "add_old", para->add_old);
    SetRegistryValue("Midi HXT", "m_frame_vor", para->m_frame_vor);
    SetRegistryValue("Midi HXT", "m_frame_nach", para->m_frame_nach);
    SetRegistryValue("Midi HXT", "m_hold", para->m_hold);
    SetRegistryValue("Midi HXT", "m_hold_force", para->m_hold_force);
    SetRegistryValue("Midi HXT", "m_hold_az", para->m_hold_az);
    SetRegistryValue("Midi HXT", "m_cake", para->cakewalk);
    const BYTE r_min = GetRValue(para->p_min_f);
    const BYTE g_min = GetGValue(para->p_min_f);
    const BYTE b_min = GetBValue(para->p_min_f);
    const BYTE r_max = GetRValue(para->p_max_f);
    const BYTE g_max = GetGValue(para->p_max_f);
    const BYTE b_max = GetBValue(para->p_max_f);
    SetRegistryValue("Midi HXT", "min_color_r", r_min);
    SetRegistryValue("Midi HXT", "min_color_g", g_min);
    SetRegistryValue("Midi HXT", "min_color_b", b_min);
    SetRegistryValue("Midi HXT", "max_color_r", r_max);
    SetRegistryValue("Midi HXT", "max_color_g", g_max);
    SetRegistryValue("Midi HXT", "max_color_b", b_max);
    const String temp = para->m_name.GetBuffer();
    SetRegistryString("Midi HXT", "m_name", temp);
//    return TRUE;
}

void CMidiApp::GetSettings() const {
    para->cakewalk = GetRegistryValue("Midi HXT", "m_cake", 0);
    para->m_track = GetRegistryValue("Midi HXT", "m_track", 0);
    para->m_control = GetRegistryValue("Midi HXT", "m_control", 0);
    para->p_min = GetRegistryValue("Midi HXT", "p_min", 0.F);
    para->p_max = GetRegistryValue("Midi HXT", "p_max", 100.F);
    para->m_min = GetRegistryValue("Midi HXT", "m_min", 0);
    para->m_max = GetRegistryValue("Midi HXT", "m_max", 127);
    para->bool_prop = GetRegistryValue("Midi HXT", "bool_prop", 1);
    para->reduce = GetRegistryValue("Midi HXT", "reduce", 0);
    para->add_old = GetRegistryValue("Midi HXT", "add_old", 0);
    para->m_frame_vor = GetRegistryValue("Midi HXT", "m_frame_vor", 1);
    para->m_frame_nach = GetRegistryValue("Midi HXT", "m_frame_nach", 1);
    para->m_hold = GetRegistryValue("Midi HXT", "m_hold", 0);
    para->m_hold_force = GetRegistryValue("Midi HXT", "m_hold_force", 0);
    para->m_hold_az = GetRegistryValue("Midi HXT", "m_hold_az", 1);
    const String temp = GetRegistryString("Midi HXT", "m_name", "");
    para->m_name.Format("%s", temp.Get());
    const BYTE r_min = GetRegistryValue("Midi HXT", "min_color_r", 0);
    const BYTE g_min = GetRegistryValue("Midi HXT", "min_color_g", 0);
    const BYTE b_min = GetRegistryValue("Midi HXT", "min_color_b", 0);
    const BYTE r_max = GetRegistryValue("Midi HXT", "max_color_r", 255);
    const BYTE g_max = GetRegistryValue("Midi HXT", "max_color_g", 255);
    const BYTE b_max = GetRegistryValue("Midi HXT", "max_color_b", 255);
    para->p_min_f = RGB(r_min, g_min, b_min);
    para->p_max_f = RGB(r_max, g_max, b_max);
//    return TRUE;
}

static void get_ppq_timing(MidiFile *midi_file, Parameter *para) {
    CString temp;
    unsigned long tt;

    const MidiFileTrack_t track = MidiFile_getFirstTrack(midi_file);
    for (MidiFileEvent_t midi_event = MidiFileTrack_getFirstEvent(track); midi_event; midi_event = MidiFileEvent_getNextEvent(midi_event)) {
        const long ticks = MidiFileEvent_getTick(midi_event);
        const MidiFileEventType_t eventtype = MidiFileEvent_getType(midi_event);
        if (eventtype == MIDI_FILE_EVENT_TYPE_META) {
            if (MidiFileMetaEvent_getNumber(midi_event) == 81) {
                tt = MidiFileMetaEvent_getDataLength(midi_event);
                const unsigned char *buf = MidiFileMetaEvent_getData(midi_event);
                temp.Format("%02x%02x%02x", buf[0], buf[1], buf[2]);
                sscanf_s(temp, "%x", &tt);
                const unsigned long bpm = 60000000 / tt;
                if (para->m_Tempo_az < 5000) {
                    if (para->m_Tempo_az > 0) {
                        para->m_Tempo[para->m_Tempo_az - 1].end_tick = ticks - 1;
                    }
                    para->m_Tempo[para->m_Tempo_az].beginn_tick = ticks;
                    para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond = MidiFile_getResolution(midi_file) * (bpm / 60.0);
                    para->m_Tempo[para->m_Tempo_az].m_tickSize = 1.0 / para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond;
                    para->m_Tempo_az++;
                }
            }
        }
    }
}

BOOL CMidiApp::GetMidiTiming() {
    long ticks;
    MidiFileEvent_t midi_event;

    switch (MidiFile_getDivisionType(midi_file)) {
        case MIDI_FILE_DIVISION_TYPE_PPQ:
        {
            get_ppq_timing(midi_file, para);
            if (para->m_Tempo_az == 1)
                para->m_Tempo_az = 0;
            break;
        }
        case MIDI_FILE_DIVISION_TYPE_SMPTE24:
        {
            para->m_Tempo[para->m_Tempo_az].beginn_tick = 0;
            para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond = MidiFile_getResolution(midi_file) * 24.0;
            para->m_Tempo[para->m_Tempo_az].m_tickSize = 1.0 / para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond;
            break;
        }
        case MIDI_FILE_DIVISION_TYPE_SMPTE25:
        {
            para->m_Tempo[para->m_Tempo_az].beginn_tick = 0;
            para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond = MidiFile_getResolution(midi_file) * 25.0;
            para->m_Tempo[para->m_Tempo_az].m_tickSize = 1.0 / para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond;
            break;
        }
        case MIDI_FILE_DIVISION_TYPE_SMPTE30DROP:
        {
            para->m_Tempo[para->m_Tempo_az].beginn_tick = 0;
            para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond = MidiFile_getResolution(midi_file) * 29.97;
            para->m_Tempo[para->m_Tempo_az].m_tickSize = 1.0 / para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond;
            break;
        }
        case MIDI_FILE_DIVISION_TYPE_SMPTE30:
        {
            para->m_Tempo[para->m_Tempo_az].beginn_tick = 0;
            para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond = MidiFile_getResolution(midi_file) * 30.0;
            para->m_Tempo[para->m_Tempo_az].m_tickSize = 1.0 / para->m_Tempo[para->m_Tempo_az].m_ticksPerSecond;
            break;
        }
        default:
            return FALSE;
    }
    if (para->m_aztrack == 0) {
        track = MidiFile_getFirstTrack(midi_file);
        midi_event = MidiFileTrack_getLastEvent(track);
        ticks = MidiFileEvent_getTick(midi_event);
    } else {
        ticks = 0;
        for (track = MidiFile_getFirstTrack(midi_file); track != nullptr; track = MidiFileTrack_getNextTrack(track)) {
            midi_event = MidiFileTrack_getLastEvent(track);
            if (const long tt = MidiFileEvent_getTick(midi_event); tt > ticks)
                ticks = tt;
        }
    }
    if (para->m_Tempo_az == 0) {
        //keine Tempowechsel
        para->m_length = ticks * para->m_Tempo[0].m_tickSize;
    } else {
        //Tempowechsel
        para->m_Tempo[para->m_Tempo_az - 1].end_tick = ticks;
        for (int i = 0; i < para->m_Tempo_az; ++i) {
            para->m_length += (para->m_Tempo[i].end_tick - para->m_Tempo[i].beginn_tick) * para->m_Tempo[i].m_tickSize;
        }
    }

    para->az_frames = ROUNDOFF(para->fps * para->m_length);
    return TRUE;
}

int GetMidiFrame(const long ticks, const Parameter *para) {
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

BOOL CMidiApp::GetMidiFrameEvents() {
    int i, j, velo, frame, x;
    long ticks;
    MidiFileEvent_t midi_event;
    MidiFileEventType_t eventtype;

    for (i = 0; i <= para->az_frames; ++i) {
        for (j = 0; j < 130; ++j) {
            frameevent[i].velo[j] = 0;
        }
    }

    if (int note; para->m_track > 0) {
        track = MidiFile_getFirstTrack(midi_file);
        for (i = 0; i < para->m_track; ++i) {
            track = MidiFileTrack_getNextTrack(track);
        }
        for (midi_event = MidiFileTrack_getFirstEvent(track); midi_event; midi_event = MidiFileEvent_getNextEvent(midi_event)) {
            ticks = MidiFileEvent_getTick(midi_event);
            eventtype = MidiFileEvent_getType(midi_event);
            switch (eventtype) {
                case MIDI_FILE_EVENT_TYPE_NOTE_ON:
                    frame = GetMidiFrame(ticks, para);
                    note = MidiFileNoteOnEvent_getNote(midi_event);
                    velo = MidiFileNoteOnEvent_getVelocity(midi_event); //Lautstaerke
                    if (velo > frameevent[frame].velo[note]) {
                        frameevent[frame].velo[note] = velo;
                    }
                //Workaround fuer Midifiles ohne Note Off Event
                    if (velo == 0) {
                        if (para->m_hold) {
                            x = -1;
                            for (j = frame; j > frame - para->m_hold_az; j--) {
                                if (frameevent[j].velo[note] > 0) {
                                    x = j;
                                    j = frame - para->m_hold_az;
                                }
                            }
                            if (x == -1) {
                                frameevent[frame].velo[note] = -1;
                            } else {
                                frameevent[x + para->m_hold_az].velo[note] = -1;
                            }
                        } else {
                            frameevent[frame].velo[note] = -1;
                        }
                    }
                    break;
                case MIDI_FILE_EVENT_TYPE_NOTE_OFF:
                    frame = GetMidiFrame(ticks, para);
                    note = MidiFileNoteOffEvent_getNote(midi_event);
                    velo = MidiFileNoteOffEvent_getVelocity(midi_event);
                    if (para->m_hold) {
                        x = -1;
                        for (j = frame; j > frame - para->m_hold_az; j--) {
                            if (frameevent[j].velo[note] > 0) {
                                x = j;
                                j = frame - para->m_hold_az;
                            }
                        }
                        if (x == -1) {
                            frameevent[frame].velo[note] = -1;
                        } else {
                            frameevent[x + para->m_hold_az].velo[note] = -1;
                        }
                    } else {
                        frameevent[frame].velo[note] = -1;
                    }
                    break;
                default:;
            }
        }
    } else {
        for (track = MidiFile_getFirstTrack(midi_file); track != nullptr; track = MidiFileTrack_getNextTrack(track)) {
            for (midi_event = MidiFileTrack_getFirstEvent(track); midi_event; midi_event = MidiFileEvent_getNextEvent(midi_event)) {
                ticks = MidiFileEvent_getTick(midi_event);
                eventtype = MidiFileEvent_getType(midi_event);
                switch (eventtype) {
                    case MIDI_FILE_EVENT_TYPE_NOTE_ON:
                        frame = GetMidiFrame(ticks, para);
                        note = MidiFileNoteOnEvent_getNote(midi_event);
                        velo = MidiFileNoteOnEvent_getVelocity(midi_event); //Lautstaerke
                        if (velo > frameevent[frame].velo[note]) {
                            frameevent[frame].velo[note] = velo;
                        }
                    //Workaround fuer Midifiles ohne Note Off Event
                        if (velo == 0) {
                            if (para->m_hold) {
                                x = -1;
                                for (j = frame; j > frame - para->m_hold_az; j--) {
                                    if (frameevent[j].velo[note] > 0) {
                                        x = j;
                                        j = frame - para->m_hold_az;
                                    }
                                }
                                if (x == -1) {
                                    frameevent[frame].velo[note] = -1;
                                } else {
                                    frameevent[x + para->m_hold_az].velo[note] = -1;
                                }
                            } else {
                                frameevent[frame].velo[note] = -1;
                            }
                        }
                        break;
                    case MIDI_FILE_EVENT_TYPE_NOTE_OFF:
                        frame = GetMidiFrame(ticks, para);
                        note = MidiFileNoteOffEvent_getNote(midi_event);
                        velo = MidiFileNoteOffEvent_getVelocity(midi_event);
                        if (para->m_hold) {
                            x = -1;
                            for (j = frame; j > frame - para->m_hold_az; j--) {
                                if (frameevent[j].velo[note] > 0) {
                                    x = j;
                                    j = frame - para->m_hold_az;
                                }
                            }
                            if (x == -1) {
                                frameevent[frame].velo[note] = -1;
                            } else {
                                frameevent[x + para->m_hold_az].velo[note] = -1;
                            }
                        } else {
                            frameevent[frame].velo[note] = -1;
                        }
                        break;
                    default:;
                }
            }
        }
    }

    //Noten ausschreiben ueber Frames
    for (j = 0; j <= 127; ++j) {
        for (i = 0; i <= para->az_frames; ++i) {
            if (frameevent[i].velo[j] > 0) {
                velo = frameevent[i].velo[j];
                i++;
                while (frameevent[i].velo[j] != -1) {
                    if (frameevent[i].velo[j] != velo && frameevent[i].velo[j] > 0)
                        velo = frameevent[i].velo[j];
                    frameevent[i].velo[j] = velo;
                    i++;
                    if (i == para->az_frames)
                        break;
                }
                frameevent[i].velo[j] = 0;
            }
        }
    }
    //Hold Force
    if (para->m_hold_force) {
        for (j = 0; j <= 127; ++j) {
            for (i = 0; i <= para->az_frames - para->m_hold_az; ++i) {
                if (frameevent[i].velo[j] > 0) {
                    i += para->m_hold_az;
                    while (frameevent[i].velo[j] > 0 && i <= para->az_frames) {
                        frameevent[i].velo[j] = 0;
                        i++;
                    }
                }
            }
        }
    }
    //Hoechste Lautstaerke per Frame
    for (i = 0; i <= para->az_frames; ++i) {
        for (j = 0; j <= 127; ++j) {
            if (frameevent[i].velo[j] > 0) {
                if (frameevent[i].velo[j] > frameevent[i].velo[128])
                    frameevent[i].velo[128] = frameevent[i].velo[j];
            }
        }
    }
    // Fuer Debugging
    /*	
       FileStream fs;
       fs.Open( "C:\\noten.txt", FileMode::HS_ASCII);
        for (i = 0;i <= para->az_frames;++i) {
            fs << "Frame" << i << nl;
    //		fs << "Frame" << i << tab << "Velo " << frameevent[i].velo[128] << nl;
            for (j = 74;j <= 86; ++j) {
                fs << frameevent[i].velo[j] << tab;
            }
            fs << nl;
        }
        fs << nl;
       fs.Close();
    */
    return TRUE;
}

BOOL CMidiApp::MainWorking() {
    int i, j, minimum;
    int old_value_int, old_counter;
    float store_f, old_value;
    Time time;
    HFloatProperty *hfp;
    HColorProperty *hcp;
    HIntProperty *hip;
    HBoolProperty *hbp;
    ColorBuf col_buf;
    BYTE r_min, g_min, b_min;
    BYTE r_max, g_max, b_max;
    BYTE r_store, g_store, b_store;
    float schritt_r, schritt_g, schritt_b;
    int store_i, store_b_old, azf;
    Store_float *store_float;
    Store_int *store_int;
    Store_color *store_color;
    Store_bool *store_bool;
    HChor *akt_chor = nullptr;
    TimeRange time_range;
    HPropertyDriver *hpd = nullptr;
    HProgressBar *progbar = nullptr;
    double counter, akt_count;

    //Fuer Actions
    HTimeProperty *htp_a = nullptr;
    HTimeRangeProperty *htrp_a = nullptr;
    Time a_time[6];

    CWaitCursor wait;

    progbar = GetProgressBar();
    if (progbar) {
        progbar->Initialize();
        progbar->SetMessage1("Midi");
        progbar->SetMessage2("Read midi");
        progbar->SetProgress(0);
    }

    GetMidiFrameEvents();
    if (progbar)
        progbar->SetProgress(33);
    if (progbar)
        progbar->SetMessage2("Calculate");

    HTreeObject *parent = para->p_property->GetParent();
    if (parent->GetObjectType() == HOT_CHOR) {
        akt_chor = (HChor *)parent;
    } else {
        while ((parent = parent->GetParent())) {
            if (parent->GetObjectType() == HOT_CHOR) {
                akt_chor = (HChor *)parent;
                break;
            }
        }
    }

    if (para->isaction) {
        //Keys lesen
        htp_a = para->haction->GetCycleLength();
        a_time[0] = htp_a->GetValue();
        htp_a->SetValue(a_time[0]);
        htrp_a = para->haction->GetCropRange();
        htp_a = htrp_a->GetStart();
        a_time[1] = htp_a->GetValue();
        htp_a = htrp_a->GetEnd();
        a_time[2] = htp_a->GetValue();
        htrp_a = para->haction->GetChorRange();
        htp_a = htrp_a->GetStart();
        a_time[3] = htp_a->GetValue();
        htp_a = htrp_a->GetEnd();
        a_time[4] = htp_a->GetValue();
    }

    if (akt_chor) {
        hpd = para->p_property->GetHeadDriver();
        time.SetFrame(0, para->fps);
        Time time_end = akt_chor->GetTotalTime()->GetValue();
        time_range.Set(time, time_end);
    }

    float schrittweite = (para->p_max - para->p_min) / (para->m_max - para->m_min);
    int u = 0;
    switch (para->p_type) {
        //	case HOT_PERCENTPROPERTY:
        case HOT_PERCENT:
            store_float = new Store_float[para->az_frames + 1];
            hfp = (HFloatProperty *)para->p_property;
            time.SetFrame(0, para->fps);
            old_value = hfp->GetValue(time);
            switch (para->m_control) {
                case 0:
                    //Note low, Note high
                    minimum = para->m_min;
                    if (minimum < 0)
                        minimum = 0;
                    for (i = 0; i < para->az_frames; ++i) {
                        store_f = 0.;
                        for (j = minimum; j <= para->m_max; ++j) {
                            if (frameevent[i].velo[j] > 0)
                                store_f = (float)j - para->m_min;
                        }
                        store_f = (store_f * schrittweite + para->p_min) / 100;
                        if (para->add_old)
                            store_f += old_value;
                        store_float[i].wert = store_f;
                        store_float[i].setzen = TRUE;
                    }
                    break;
                case 1:
                    //Note high
                    for (i = 0; i < para->az_frames; ++i) {
                        store_float[i].setzen = TRUE;
                        if (frameevent[i].velo[para->m_max] > 0) {
                            store_float[i].wert = para->p_max / 100;
                        } else {
                            if (para->p_min != 0) {
                                store_float[i].wert = para->p_min / 100;
                            } else {
                                store_float[i].wert = 0.;
                            }
                        }
                        if (para->add_old)
                            store_float[i].wert += old_value;
                    }
                //von min -> max
                    if (para->m_frame_vor > 1) {
                        for (i = 0; i < para->az_frames - para->m_frame_vor; ++i) {
                            if (store_float[i].wert < store_float[i + para->m_frame_vor].wert) {
                                store_b_old = 0;
                                for (j = i; j < i + para->m_frame_vor; ++j) {
                                    if (store_float[i].wert == store_float[j].wert)
                                        store_b_old++;
                                }
                                if (store_b_old == para->m_frame_vor) {
                                    for (j = i + 1; j < i + para->m_frame_vor; ++j) {
                                        store_float[j].setzen = FALSE;
                                    }
                                }
                            }
                        }
                    }
                //von max -> min
                //wenn nicht mehr genuegend Innerframes keine Action
                    if (para->m_frame_nach > 1) {
                        for (i = para->az_frames; i > para->m_frame_nach; i--) {
                            if (store_float[i].wert < store_float[i - para->m_frame_nach].wert) {
                                store_b_old = 0;
                                for (j = i; j > i - para->m_frame_nach; j--) {
                                    if (store_float[i].wert == store_float[j].wert && store_float[j].setzen)
                                        store_b_old++;
                                }
                                if (store_b_old == para->m_frame_nach) {
                                    for (j = i - 1; j > i - para->m_frame_nach; j--) {
                                        store_float[j].setzen = FALSE;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    //Volume
                    for (i = 0; i < para->az_frames; ++i) {
                        if (frameevent[i].velo[128] > para->m_max) {
                            store_f = (para->m_max - para->m_min) * schrittweite + para->p_min;
                        } else {
                            store_f = (frameevent[i].velo[128] - para->m_min) * schrittweite + para->p_min;
                        }
                        store_f /= 100;
                        if (para->add_old)
                            store_f += old_value;
                        store_float[i].wert = store_f;
                        store_float[i].setzen = TRUE;
                    }
                    break;
            }
            switch (para->reduce) {
                case 0:
                    break;
                case 1:
                    // Frames ausduennen 2 cp stehen lassen Interpolation Spline
                    for (i = 2; i < para->az_frames - 2; ++i) {
                        if (store_float[i].wert == store_float[i - 1].wert && store_float[i].wert == store_float[i - 2].wert && store_float[i].wert == store_float[i + 1].wert && store_float[i].wert == store_float[i + 2].wert)
                            store_float[i].setzen = false;
                    }
                    break;
                case 2:
                    // Frames ausduennen 1 cp stehen lassen Interpolation linear
                    for (i = 1; i < para->az_frames - 1; ++i) {
                        if (store_float[i].wert == store_float[i - 1].wert && store_float[i].wert == store_float[i + 1].wert)
                            store_float[i].setzen = false;
                    }
                    break;
            }
            if (progbar)
                progbar->SetProgress(66);
        // Zaehlen der zu setzenden Keyframes
            azf = 0;
            for (i = 1; i < para->az_frames; ++i) {
                if (store_float[i].setzen)
                    azf++;
            }
            counter = 100. / azf;
            akt_count = 0;
            old_counter = 0;
            if (hpd && (para->reduce > 0 || para->m_control == 1))
                hpd->DeleteKeys(time_range);
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Write keyframes");
            time.SetFrame(0, para->fps);
            hfp->StoreValue(time, store_float[0].wert, TRUE);
            if (progbar)
                progbar->SetProgress(0);
            for (i = 1; i < para->az_frames; ++i) {
                if (store_float[i].setzen) {
                    if (progbar) {
                        if (old_counter != (int)akt_count) {
                            old_counter = (int)akt_count;
                            progbar->SetProgress(old_counter);
                        }
                    }
                    akt_count += counter;
                    time.SetFrame(i, para->fps);
                    hfp->StoreValue(time, store_float[i].wert, FALSE);
                }
            }
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Finished");
            delete [] store_float;
            break;
        case HOT_EULERFLOAT:
        case HOT_FLOAT:
            store_float = new Store_float[para->az_frames + 1];
            hfp = (HFloatProperty *)para->p_property;
            old_value = hfp->GetValue(time);
            if (para->p_iscolor) {
                if (para->p_min < 0)
                    para->p_min = 0;
                if (para->p_max > 255)
                    para->p_max = 255;
                schrittweite = (para->p_max - para->p_min) / (para->m_max - para->m_min);
            }
            switch (para->m_control) {
                case 0:
                    minimum = para->m_min;
                    if (minimum < 0)
                        minimum = 0;
                    for (i = 0; i < para->az_frames; ++i) {
                        store_f = 0.;
                        for (j = minimum; j <= para->m_max; ++j) {
                            if (frameevent[i].velo[j] > 0)
                                store_f = (float)j - para->m_min;
                        }
                        if (para->p_iscolor) {
                            if (store_f < 0)
                                store_f = 0;
                            store_f = store_f * schrittweite + para->p_min;
                            store_f /= 255;
                            if (para->add_old)
                                store_f += old_value;
                            if (store_f > 1)
                                store_f = 1;
                        } else {
                            store_f = store_f * schrittweite + para->p_min;
                            if (para->p_fullname.Find("ConeAngle") > 0) {
                                store_f /= 2;
                                if (store_f < 0.005)
                                    store_f = 0.005F;
                            }
                            if (para->add_old)
                                store_f += old_value;
                        }
                        store_float[i].wert = store_f;
                        store_float[i].setzen = TRUE;
                    }
                    break;
                case 1:
                    //Note high
                    for (i = 0; i < para->az_frames; ++i) {
                        store_float[i].setzen = TRUE;
                        if (frameevent[i].velo[para->m_max] > 0) {
                            store_float[i].wert = para->p_max;
                        } else {
                            if (para->p_min != 0) {
                                store_float[i].wert = para->p_min;
                            } else {
                                store_float[i].wert = 0.;
                            }
                        }
                        if (para->p_iscolor) {
                            store_float[i].wert /= 255;
                            if (para->add_old)
                                store_float[i].wert += old_value;
                            if (store_float[i].wert > 1)
                                store_float[i].wert = 1;
                        } else {
                            if (para->p_fullname.Find("ConeAngle") > 0) {
                                store_float[i].wert /= 2;
                                if (store_float[i].wert < 0.005)
                                    store_float[i].wert = 0.005F;
                            }
                            if (para->add_old)
                                store_float[i].wert += old_value;
                        }
                    }
                //von min -> max
                    if (para->m_frame_vor > 1) {
                        for (i = 0; i < para->az_frames - para->m_frame_vor; ++i) {
                            if (store_float[i].wert < store_float[i + para->m_frame_vor].wert) {
                                store_b_old = 0;
                                for (j = i; j < i + para->m_frame_vor; ++j) {
                                    if (store_float[i].wert == store_float[j].wert)
                                        store_b_old++;
                                }
                                if (store_b_old == para->m_frame_vor) {
                                    for (j = i + 1; j < i + para->m_frame_vor; ++j) {
                                        store_float[j].setzen = FALSE;
                                    }
                                }
                            }
                        }
                    }
                //von max -> min
                //wenn nicht mehr genuegend Innerframes keine Action
                    if (para->m_frame_nach > 1) {
                        for (i = para->az_frames; i > para->m_frame_nach; i--) {
                            if (store_float[i].wert < store_float[i - para->m_frame_nach].wert) {
                                store_b_old = 0;
                                for (j = i; j > i - para->m_frame_nach; j--) {
                                    if (store_float[i].wert == store_float[j].wert && store_float[j].setzen)
                                        store_b_old++;
                                }
                                if (store_b_old == para->m_frame_nach) {
                                    for (j = i - 1; j > i - para->m_frame_nach; j--) {
                                        store_float[j].setzen = FALSE;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    for (i = 0; i < para->az_frames; ++i) {
                        if (para->p_iscolor) {
                            if (frameevent[i].velo[128] > para->m_max) {
                                store_f = (para->m_max - para->m_min) * schrittweite + para->p_min;
                            } else {
                                store_f = (frameevent[i].velo[128] - para->m_min) * schrittweite + para->p_min;
                            }
                            store_f /= 255;
                            if (para->add_old)
                                store_f += old_value;
                            if (store_f > 1)
                                store_f = 1;
                        } else {
                            if (frameevent[i].velo[128] > para->m_max) {
                                store_f = (para->m_max - para->m_min) * schrittweite + para->p_min;
                            } else {
                                store_f = (frameevent[i].velo[128] - para->m_min) * schrittweite + para->p_min;
                            }
                            if (para->p_fullname.Find("ConeAngle") > 0) {
                                store_f /= 2;
                                if (store_f < 0.005)
                                    store_f = 0.005F;
                            }
                            if (para->add_old)
                                store_f += old_value;
                        }
                        store_float[i].wert = store_f;
                        store_float[i].setzen = TRUE;
                    }
                    break;
            }
            switch (para->reduce) {
                case 0:
                    break;
                case 1:
                    // Frames ausduennen 2 cp stehen lassen Interpolation Spline
                    for (i = 2; i < para->az_frames - 2; ++i) {
                        if (store_float[i].wert == store_float[i - 1].wert && store_float[i].wert == store_float[i - 2].wert && store_float[i].wert == store_float[i + 1].wert && store_float[i].wert == store_float[i + 2].wert)
                            store_float[i].setzen = false;
                    }
                    break;
                case 2:
                    // Frames ausduennen 1 cp stehen lassen Interpolation linear
                    for (i = 1; i < para->az_frames - 1; ++i) {
                        if (store_float[i].wert == store_float[i - 1].wert && store_float[i].wert == store_float[i + 1].wert) {
                            store_float[i].setzen = false;
                        }
                    }
                    break;
            }
            if (progbar)
                progbar->SetProgress(66);
            if (hpd && (para->reduce > 0 || para->m_control == 1))
                hpd->DeleteKeys(time_range);
        //Keyframes zaehlen
            azf = 0;
            for (i = 1; i < para->az_frames; ++i) {
                if (store_float[i].setzen)
                    azf++;
            }
            counter = 100. / azf;
            akt_count = 0;
            old_counter = 0;
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Write keyframes");
            time.SetFrame(0, para->fps);
            hfp->StoreValue(time, store_float[0].wert, TRUE);
            if (progbar)
                progbar->SetProgress(0);
            for (i = 1; i < para->az_frames; ++i) {
                if (store_float[i].setzen) {
                    if (progbar) {
                        if (old_counter != (int)akt_count) {
                            old_counter = (int)akt_count;
                            progbar->SetProgress(old_counter);
                        }
                    }
                    akt_count += counter;
                    time.SetFrame(i, para->fps);
                    hfp->StoreValue(time, store_float[i].wert, FALSE);
                }
            }
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Finished");
            delete [] store_float;
            break;
        case HOT_INTEGER:
            store_int = new Store_int[para->az_frames + 1];
            hip = (HIntProperty *)para->p_property;
            old_value_int = hip->GetValue(time);
            switch (para->m_control) {
                case 0:
                    minimum = para->m_min;
                    if (minimum < 0)
                        minimum = 0;
                    for (i = 0; i < para->az_frames; ++i) {
                        store_f = 0.;
                        for (j = minimum; j <= para->m_max; ++j) {
                            if (frameevent[i].velo[j] > 0)
                                store_f = (float)j - para->m_min;
                        }
                        store_f = store_f * schrittweite + para->p_min;
                        if (para->add_old)
                            store_f += old_value_int;
                        store_int[i].wert = ROUNDOFF(store_f);
                        store_int[i].setzen = TRUE;
                    }
                    break;
                case 1:
                    //Note high
                    for (i = 0; i < para->az_frames; ++i) {
                        store_int[i].setzen = TRUE;
                        if (frameevent[i].velo[para->m_max] > 0) {
                            store_int[i].wert = ROUNDOFF(para->p_max);
                        } else {
                            if (para->p_min != 0) {
                                store_int[i].wert = ROUNDOFF(para->p_min);
                            } else {
                                store_int[i].wert = 0;
                            }
                        }
                        if (para->add_old)
                            store_int[i].wert += old_value_int;
                    }
                //von min -> max
                    if (para->m_frame_vor > 1) {
                        for (i = 0; i < para->az_frames - para->m_frame_vor; ++i) {
                            if (store_int[i].wert < store_int[i + para->m_frame_vor].wert) {
                                store_b_old = 0;
                                for (j = i; j < i + para->m_frame_vor; ++j) {
                                    if (store_int[i].wert == store_int[j].wert)
                                        store_b_old++;
                                }
                                if (store_b_old == para->m_frame_vor) {
                                    for (j = i + 1; j < i + para->m_frame_vor; ++j) {
                                        store_int[j].setzen = FALSE;
                                    }
                                }
                            }
                        }
                    }
                //von max -> min
                //wenn nicht mehr genuegend Innerframes keine Action
                    if (para->m_frame_nach > 1) {
                        for (i = para->az_frames; i > para->m_frame_nach; i--) {
                            if (store_int[i].wert < store_int[i - para->m_frame_nach].wert) {
                                store_b_old = 0;
                                for (j = i; j > i - para->m_frame_nach; j--) {
                                    if (store_int[i].wert == store_int[j].wert && store_int[j].setzen)
                                        store_b_old++;
                                }
                                if (store_b_old == para->m_frame_nach) {
                                    for (j = i - 1; j > i - para->m_frame_nach; j--) {
                                        store_int[j].setzen = FALSE;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    for (i = 0; i < para->az_frames; ++i) {
                        if (frameevent[i].velo[128] > para->m_max) {
                            store_f = (para->m_max - para->m_min) * schrittweite + para->p_min;
                        } else {
                            store_f = (frameevent[i].velo[128] - para->m_min) * schrittweite + para->p_min;
                        }
                        if (store_f > para->p_max)
                            store_f = para->p_max;
                        if (para->add_old)
                            store_f += old_value_int;
                        store_int[i].wert = ROUNDOFF(store_f);
                        store_int[i].setzen = TRUE;
                    }
                    break;
            }
            switch (para->reduce) {
                case 0:
                    break;
                case 1:
                    // Frames ausduennen 2 cp stehen lassen Interpolation Spline
                    for (i = 2; i < para->az_frames - 2; ++i) {
                        if (store_int[i].wert == store_int[i - 1].wert && store_int[i].wert == store_int[i - 2].wert && store_int[i].wert == store_int[i + 1].wert && store_int[i].wert == store_int[i + 2].wert)
                            store_int[i].setzen = false;
                    }
                    break;
                case 2:
                    // Frames ausduennen 1 cp stehen lassen Interpolation linear
                    for (i = 1; i < para->az_frames - 1; ++i) {
                        if (store_int[i].wert == store_int[i - 1].wert && store_int[i].wert == store_int[i + 1].wert) {
                            store_int[i].setzen = false;
                        }
                    }
                    break;
            }
            if (progbar)
                progbar->SetProgress(66);
        //Keyframes zaehlen
            azf = 0;
            for (i = 1; i < para->az_frames; ++i) {
                if (store_int[i].setzen)
                    azf++;
            }
            counter = 100. / azf;
            akt_count = 0;
            old_counter = 0;
            if (hpd && (para->reduce > 0 || para->m_control == 1))
                hpd->DeleteKeys(time_range);
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Write keyframes");
            time.SetFrame(0, para->fps);
            hip->StoreValue(time, store_int[0].wert, TRUE);
            if (progbar)
                progbar->SetProgress(0);
            for (i = 1; i < para->az_frames; ++i) {
                if (store_int[i].setzen) {
                    if (progbar) {
                        if (old_counter != (int)akt_count) {
                            old_counter = (int)akt_count;
                            progbar->SetProgress(old_counter);
                        }
                    }
                    akt_count += counter;
                    time.SetFrame(i, para->fps);
                    hip->StoreValue(time, store_int[i].wert, FALSE);
                }
            }
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Finished");
            delete [] store_int;
            break;
        case HOT_COLOR:
            // Problem nur erster Driver wird geloescht
            store_color = new Store_color[para->az_frames + 1];
            hcp = (HColorProperty *)para->p_property;
        //		hcp->CreateParentForDriver();
            r_min = GetRValue(para->p_min_f);
            g_min = GetGValue(para->p_min_f);
            b_min = GetBValue(para->p_min_f);
            r_max = GetRValue(para->p_max_f);
            g_max = GetGValue(para->p_max_f);
            b_max = GetBValue(para->p_max_f);
            schritt_r = (r_max - r_min) / (float)(para->m_max - para->m_min);
            if (schritt_r < 0)
                schritt_r *= -1;
            schritt_g = (g_max - g_min) / (float)(para->m_max - para->m_min);
            if (schritt_g < 0)
                schritt_g *= -1;
            schritt_b = (b_max - b_min) / (float)(para->m_max - para->m_min);
            if (schritt_b < 0)
                schritt_b *= -1;
            switch (para->m_control) {
                case 0:
                    minimum = para->m_min;
                    if (minimum < 0)
                        minimum = 0;
                    for (i = 0; i < para->az_frames; ++i) {
                        store_i = 0;
                        for (j = minimum; j <= para->m_max; ++j) {
                            if (frameevent[i].velo[j] > 0) {
                                store_i = j - para->m_min;
                                if (para->p_max_f < para->p_min_f)
                                    store_i *= -1;
                            }
                        }
                        store_f = store_i * schritt_r + r_min;
                        r_store = (BYTE)ROUNDOFF(store_f);
                        store_f = store_i * schritt_g + g_min;
                        g_store = (BYTE)ROUNDOFF(store_f);
                        store_f = store_i * schritt_b + b_min;
                        b_store = (BYTE)ROUNDOFF(store_f);
                        col_buf = ColorBuf(r_store, g_store, b_store);
                        store_color[i].wert = col_buf;
                        store_color[i].setzen = TRUE;
                    }
                    break;
                case 1:
                    //Note high
                    for (i = 0; i < para->az_frames; ++i) {
                        store_color[i].setzen = TRUE;
                        if (frameevent[i].velo[para->m_max] > 0) {
                            col_buf = ColorBuf(r_max, g_max, b_max);
                            store_color[i].wert = col_buf;
                        } else {
                            if (para->p_min_f != 0) {
                                col_buf = ColorBuf(r_min, g_min, b_min);
                                store_color[i].wert = col_buf;
                            } else {
                                col_buf = ColorBuf(0, 0, 0);
                                store_color[i].wert = col_buf;
                            }
                        }
                    }
                //von min -> max
                    if (para->m_frame_vor > 1) {
                        for (i = 0; i < para->az_frames - para->m_frame_vor; ++i) {
                            if (store_color[i].wert < store_color[i + para->m_frame_vor].wert) {
                                store_b_old = 0;
                                for (j = i; j < i + para->m_frame_vor; ++j) {
                                    if (store_color[i].wert == store_color[j].wert)
                                        store_b_old++;
                                }
                                if (store_b_old == para->m_frame_vor) {
                                    for (j = i + 1; j < i + para->m_frame_vor; ++j) {
                                        store_color[j].setzen = FALSE;
                                    }
                                }
                            }
                        }
                    }
                //von max -> min
                //wenn nicht mehr genuegend Innerframes keine Action
                    if (para->m_frame_nach > 1) {
                        for (i = para->az_frames; i > para->m_frame_nach; i--) {
                            if (store_color[i].wert < store_color[i - para->m_frame_nach].wert) {
                                store_b_old = 0;
                                for (j = i; j > i - para->m_frame_nach; j--) {
                                    if (store_color[i].wert == store_color[j].wert && store_color[j].setzen)
                                        store_b_old++;
                                }
                                if (store_b_old == para->m_frame_nach) {
                                    for (j = i - 1; j > i - para->m_frame_nach; j--) {
                                        store_color[j].setzen = FALSE;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    for (i = 0; i < para->az_frames; ++i) {
                        if (frameevent[i].velo[128] > para->m_max) {
                            store_i = para->m_max - para->m_min;
                        } else {
                            store_i = frameevent[i].velo[128] - para->m_min;
                        }
                        store_f = store_i * schritt_r + r_min;
                        r_store = (BYTE)ROUNDOFF(store_f);
                        store_f = store_i * schritt_g + g_min;
                        g_store = (BYTE)ROUNDOFF(store_f);
                        store_f = store_i * schritt_b + b_min;
                        b_store = (BYTE)ROUNDOFF(store_f);
                        col_buf = ColorBuf(r_store, g_store, b_store);
                        store_color[i].wert = col_buf;
                        store_color[i].setzen = TRUE;
                    }
                    break;
            }
            switch (para->reduce) {
                case 0:
                    break;
                case 1:
                    // Frames ausduennen 2 cp stehen lassen Interpolation Spline
                    for (i = 2; i < para->az_frames - 2; ++i) {
                        if (store_color[i].wert == store_color[i - 1].wert && store_color[i].wert == store_color[i - 2].wert && store_color[i].wert == store_color[i + 1].wert && store_color[i].wert == store_color[i + 2].wert)
                            store_color[i].setzen = false;
                    }
                    break;
                case 2:
                    // Frames ausduennen 1 cp stehen lassen Interpolation linear
                    for (i = 1; i < para->az_frames - 1; ++i) {
                        if (store_color[i].wert == store_color[i - 1].wert && store_color[i].wert == store_color[i + 1].wert) {
                            store_color[i].setzen = false;
                        }
                    }
                    break;
            }
            if (progbar)
                progbar->SetProgress(66);
            if (hpd && (para->reduce > 0 || para->m_control == 1)) {
                //hoffentlich nur die 3 Farbkeys ...
                for (hpd = para->p_property->GetHeadDriver(); hpd; hpd = hpd->GetNextDriver()) {
                    hpd->DeleteKeys(time_range);
                }
            }
        //Keyframes zaehlen
            azf = 0;
            for (i = 1; i < para->az_frames; ++i) {
                if (store_color[i].setzen)
                    azf++;
            }
            counter = 100. / azf;
            old_counter = 0;
            akt_count = 0;
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Write keyframes");
            time.SetFrame(0, para->fps);
            hcp->StoreValue(time, store_color[0].wert, FALSE);
            if (progbar)
                progbar->SetProgress(0);
            for (i = 1; i < para->az_frames; ++i) {
                if (store_color[i].setzen) {
                    if (progbar) {
                        if (old_counter != (int)akt_count) {
                            old_counter = (int)akt_count;
                            progbar->SetProgress(old_counter);
                        }
                    }
                    akt_count += counter;
                    time.SetFrame(i, para->fps);
                    hcp->StoreValue(time, store_color[i].wert, FALSE);
                }
            }
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Finished");
            delete [] store_color;
            break;
        case HOT_BOOL:
            hbp = (HBoolProperty *)para->p_property;
            store_bool = new Store_bool[para->az_frames + 1];
            switch (para->m_control) {
                case 0:
                    for (i = 0; i < para->az_frames; ++i) {
                        store_i = FALSE;
                        for (j = para->m_min; j <= para->m_max; ++j) {
                            if (frameevent[i].velo[j] > 0) {
                                store_i = TRUE;
                                j = para->m_max;
                            }
                        }
                        if (store_i) {
                            if (para->bool_prop) {
                                store_bool[i].wert = TRUE;
                                store_bool[i].setzen = TRUE;
                            } else {
                                store_bool[i].wert = FALSE;
                                store_bool[i].setzen = TRUE;
                            }
                        } else {
                            if (para->bool_prop) {
                                store_bool[i].wert = FALSE;
                                store_bool[i].setzen = TRUE;
                            } else {
                                store_bool[i].wert = TRUE;
                                store_bool[i].setzen = TRUE;
                            }
                        }
                    }
                    break;
                case 1:
                    for (i = 0; i < para->az_frames; ++i) {
                        store_i = FALSE;
                        if (frameevent[i].velo[para->m_max] > 0)
                            store_i = TRUE;
                        if (store_i) {
                            if (para->bool_prop) {
                                store_bool[i].wert = TRUE;
                                store_bool[i].setzen = TRUE;
                            } else {
                                store_bool[i].wert = FALSE;
                                store_bool[i].setzen = TRUE;
                            }
                        } else {
                            if (para->bool_prop) {
                                store_bool[i].wert = FALSE;
                                store_bool[i].setzen = TRUE;
                            } else {
                                store_bool[i].wert = TRUE;
                                store_bool[i].setzen = TRUE;
                            }
                        }
                    }
                    break;
                case 2:
                    for (i = 0; i < para->az_frames; ++i) {
                        store_i = FALSE;
                        if (frameevent[i].velo[128] > para->m_min && frameevent[i].velo[128] < para->m_max)
                            store_i = TRUE;
                        if (store_i) {
                            if (para->bool_prop) {
                                store_bool[i].wert = TRUE;
                                store_bool[i].setzen = TRUE;
                            } else {
                                store_bool[i].wert = FALSE;
                                store_bool[i].setzen = TRUE;
                            }
                        } else {
                            if (para->bool_prop) {
                                store_bool[i].wert = FALSE;
                                store_bool[i].setzen = TRUE;
                            } else {
                                store_bool[i].wert = TRUE;
                                store_bool[i].setzen = TRUE;
                            }
                        }
                    }
                    break;
            }
            if (progbar)
                progbar->SetProgress(66);
            for (i = 1; i < para->az_frames; ++i, ++u) {
                if (store_bool[i].wert == store_bool[u].wert)
                    store_bool[i].setzen = false;
            }
        //Keyframes zaehlen
            azf = 0;
            for (i = 1; i < para->az_frames; ++i) {
                if (store_bool[i].setzen)
                    azf++;
            }
            counter = 100. / azf;
            old_counter = 0;
            akt_count = 0;
            if (hpd)
                hpd->DeleteKeys(time_range);
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Write keyframes");
            time.SetFrame(0, para->fps);
            hbp->StoreValue(time, store_bool[0].wert, TRUE);
            if (progbar)
                progbar->SetProgress(0);
            for (i = 1; i < para->az_frames; ++i) {
                if (store_bool[i].setzen) {
                    if (progbar) {
                        if (old_counter != (int)akt_count) {
                            old_counter = (int)akt_count;
                            progbar->SetProgress(old_counter);
                        }
                    }
                    akt_count += counter;
                    time.SetFrame(i, para->fps);
                    hbp->StoreValue(time, store_bool[i].wert, FALSE);
                }
            }
            if (progbar)
                progbar->SetProgress(100);
            if (progbar)
                progbar->SetMessage2("Finished");
            delete [] store_bool;
            break;
        default:;
    }

    if (para->isaction) {
        //Keys setzen
        htp_a = para->haction->GetCycleLength();
        htp_a->SetValue(a_time[0]);
        htrp_a = para->haction->GetCropRange();
        htp_a = htrp_a->GetStart();
        htp_a->SetValue(a_time[1]);
        htp_a = htrp_a->GetEnd();
        htp_a->SetValue(a_time[2]);
        htrp_a = para->haction->GetChorRange();
        htp_a = htrp_a->GetStart();
        htp_a->SetValue(a_time[3]);
        htp_a = htrp_a->GetEnd();
        htp_a->SetValue(a_time[4]);
    }
    if (progbar)
        progbar->Uninitialize();

    return TRUE;
}
