// Record.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Midicontrol.h"
#include "Record.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

Record::Record(PARAMETER *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(Record)
    m_para = para;
    //}}AFX_DATA_INIT
}

void Record::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Record)
    DDX_Text(pDX, IDC_EDIT1, m_frame);
    DDV_MinMaxUInt(pDX, m_frame, 0, 36000);
    DDX_Check(pDX, IDC_CHECK1, m_deletebeforerecord);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Record, CDialog)
        //{{AFX_MSG_MAP(Record)
        ON_BN_CLICKED(IDC_BUTTON1, &Record::OnButton1)
        ON_BN_CLICKED(IDC_BUTTON2, &Record::OnButton2)
        ON_BN_CLICKED(IDC_BUTTON3, &Record::OnButton3)
        ON_BN_CLICKED(IDC_BUTTON4, &Record::OnButton4)
        ON_BN_CLICKED(IDC_RADIO1, &Record::OnRadio1)
        ON_BN_CLICKED(IDC_RADIO2, &Record::OnRadio2)
        ON_BN_CLICKED(IDC_RADIO3, &Record::OnRadio3)
        ON_BN_CLICKED(IDC_RADIO4, &Record::OnRadio4)
        ON_WM_TIMER()
        ON_WM_CLOSE()
        ON_BN_CLICKED(IDC_BUTTON6, &Record::OnButton6)
        ON_EN_CHANGE(IDC_EDIT1, &Record::OnChangeEdit1)
        ON_BN_CLICKED(IDC_CHECK1, &Record::OnCheck1)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Record 

void Record::DeleteBeforeRecord() {

    Time time, time_end;
    TimeRange time_range;
    int i;

    time.SetFrame(0, m_para->fps);
    time_end.SetFrame(m_para->end_frame, m_para->fps);
    time_range.Set(time, time_end);

    for (i = 0; i < m_para->az_control; ++i) {
        m_para->p_control[i].prop->DeleteKeys(time_range);
        if (m_para->p_control[i].objt == HOT_COLOR) {
            m_para->p_control[i].hcp->StoreValue(Time(), m_para->p_control[i].value_color[m_para->p_control[i].value_beginn],FALSE);
        } else {
            m_para->p_control[i].hfp->StoreValue(Time(), m_para->p_control[i].value[m_para->p_control[i].value_beginn],FALSE);
        }
    }
    for (i = 0; i < m_para->az_key; ++i) {
        m_para->p_key[i].prop->DeleteKeys(time_range);
        if (m_para->p_key[i].objt == HOT_COLOR) {
            m_para->p_key[i].hcp->StoreValue(Time(), m_para->p_key[i].value_color[m_para->p_key[i].value_beginn],FALSE);
        } else {
            m_para->p_key[i].hfp->StoreValue(Time(), m_para->p_key[i].value[m_para->p_key[i].value_beginn],FALSE);
        }
    }
    for (i = 0; i < m_para->az_note; ++i) {
        m_para->p_note[i].prop->DeleteKeys(time_range);
        if (m_para->p_note[i].objt == HOT_COLOR) {
            m_para->p_note[i].hcp->StoreValue(Time(), m_para->p_note[i].value_color[m_para->p_note[i].value_beginn],FALSE);
        } else {
            m_para->p_note[i].hfp->StoreValue(Time(), m_para->p_note[i].value[m_para->p_note[i].value_beginn],FALSE);
        }
    }
    force_update = 1;
    changed = 1;
}

void Record::CreateChannels() const {

    [[maybe_unused]] HChannelDriver *hcc;
    int i;

    for (i = 0; i < m_para->az_control; ++i) {
        hcc = HChannelDriver::New(m_para->p_control[i].prop);
        if (m_para->p_control[i].objt == HOT_COLOR) {
            if (m_para->p_control[i].hcp) {
                m_para->p_control[i].First_value_c = (ColorVector)m_para->p_control[i].hcp->GetCOLORREF();
                m_para->p_control[i].First_is = TRUE;
            } else {
                m_para->p_control[i].First_is = FALSE;
            }
        } else {
            if (m_para->p_control[i].hfp) {
                m_para->p_control[i].First_value = m_para->p_control[i].hfp->GetValue(Time());
                m_para->p_control[i].First_is = TRUE;
            } else {
                m_para->p_control[i].First_is = FALSE;
            }
        }
    }
    for (i = 0; i < m_para->az_note; ++i) {
        hcc = HChannelDriver::New(m_para->p_note[i].prop);
        if (m_para->p_note[i].objt == HOT_COLOR) {
            if (m_para->p_note[i].hcp) {
                m_para->p_note[i].First_value_c = (ColorVector)m_para->p_note[i].hcp->GetCOLORREF();
                m_para->p_note[i].First_is = TRUE;
            } else {
                m_para->p_note[i].First_is = FALSE;
            }
        } else {
            if (m_para->p_note[i].hfp) {
                m_para->p_note[i].First_value = m_para->p_note[i].hfp->GetValue(Time());
                m_para->p_note[i].First_is = TRUE;
            } else {
                m_para->p_note[i].First_is = FALSE;
            }
        }
    }
    for (i = 0; i < m_para->az_key; ++i) {
        hcc = HChannelDriver::New(m_para->p_key[i].prop);
        if (m_para->p_key[i].objt == HOT_COLOR) {
            if (m_para->p_key[i].hcp) {
                m_para->p_key[i].First_value_c = (ColorVector)m_para->p_key[i].hcp->GetCOLORREF();
                m_para->p_key[i].First_is = TRUE;
            } else {
                m_para->p_key[i].First_is = FALSE;
            }
        } else {
            if (m_para->p_key[i].hfp) {
                m_para->p_key[i].First_value = m_para->p_key[i].hfp->GetValue(Time());
                m_para->p_key[i].First_is = TRUE;
            } else {
                m_para->p_key[i].First_is = FALSE;
            }
        }
    }
}

void Record::CBMidiOpen(HMIDIIN hMidiIn, const UINT wMsg, const DWORD dwInstance, const DWORD dwParam1, const DWORD dwParam2) {
    ((Record *)dwInstance)->MidiOpenNotify(hMidiIn, wMsg, dwParam1, dwParam2);
}

void Record::MidiOpenNotify(HMIDIIN midi_in, const UINT msg_type, const DWORD midi_msg, DWORD param2) {
    unsigned int midi_in_number;

    midiInGetID(midi_in, &midi_in_number);

    if (msg_type == MIM_DATA) {
        COLORREF itemdata = 0;
        int eventset = 0;
        union {
            DWORD dwData;
            BYTE bData[4];
        } u{};

        u.dwData = midi_msg;
        const int channel = u.bData[0] & 0x0F;
        const int pitch = u.bData[1];
        int value = u.bData[2];
        switch (u.bData[0] & 0xF0) {
            case 0x90:
            {
                itemdata = RGB(0x90,channel, pitch);
                eventset = 1;
                break;
            }
            case 0xA0:
            {
                itemdata = RGB(0xA0,channel, pitch);
                eventset = 1;
                break;
            }
            case 0xB0:
            {
                itemdata = RGB(0xB0,channel, pitch);
                eventset = 1;
                break;
            }
        }
        if (eventset && !m_para->midi_play_run) {
            int i;
            //Setting Propertie
            //Note
            for (i = 0; i < m_para->az_note; ++i) {
                if (m_para->p_note[i].driven_value == itemdata) {
                    if (m_para->override && value > 0)
                        value = 127;
                    if (m_para->p_note[i].akt_value != value) {
                        m_para->p_note[i].akt_value = value;
                        if (m_para->midi_record_run || m_para->midi_single_run)
                            m_para->p_note[i].changed = 1;
                    }
                    if (!m_para->midi_record_run && !m_para->midi_play_run) {
                        if (m_para->frame == 0)
                            m_para->p_note[i].value_beginn = value;
                        while (update_run) {
                            Sleep(10);
                        }
                        if (m_para->p_note[i].objt == HOT_COLOR) {
                            m_para->p_note[i].hcp->StoreValue(m_para->time, m_para->p_note[i].value_color[value],FALSE);
                        } else {
                            m_para->p_note[i].hfp->StoreValue(m_para->time, m_para->p_note[i].value[value],FALSE);
                        }
                        changed = 1;
                    }
                }
            }
            //Key
            for (i = 0; i < m_para->az_key; ++i) {
                if (m_para->p_key[i].driven_value == itemdata) {
                    if (m_para->p_key[i].akt_value != value) {
                        m_para->p_key[i].akt_value = value;
                        if (m_para->midi_record_run || m_para->midi_single_run)
                            m_para->p_key[i].changed = 1;
                    }
                    if (!m_para->midi_record_run && !m_para->midi_play_run) {
                        if (m_para->frame == 0)
                            m_para->p_key[i].value_beginn = value;
                        while (update_run) {
                            Sleep(10);
                        }
                        if (m_para->p_key[i].objt == HOT_COLOR) {
                            m_para->p_key[i].hcp->StoreValue(m_para->time, m_para->p_key[i].value_color[value],FALSE);
                        } else {
                            m_para->p_key[i].hfp->StoreValue(m_para->time, m_para->p_key[i].value[value],FALSE);
                        }
                        changed = 1;
                    }
                }
            }
            //Control
            for (i = 0; i < m_para->az_control; ++i) {
                if (m_para->p_control[i].driven_value == itemdata) {
                    if (m_para->p_control[i].akt_value != value) {
                        m_para->p_control[i].akt_value = value;
                        if (m_para->midi_record_run || m_para->midi_single_run)
                            m_para->p_control[i].changed = 1;
                    }
                    if (!m_para->midi_record_run && !m_para->midi_play_run) {
                        if (m_para->frame == 0)
                            m_para->p_control[i].value_beginn = value;
                        while (update_run) {
                            Sleep(10);
                        }
                        if (m_para->p_control[i].objt == HOT_COLOR) {
                            m_para->p_control[i].hcp->StoreValue(m_para->time, m_para->p_control[i].value_color[value],FALSE);
                        } else {
                            m_para->p_control[i].hfp->StoreValue(m_para->time, m_para->p_control[i].value[value],FALSE);
                        }
                        changed = 1;
                    }
                }
            }
            if (value > 0 && itemdata == m_para->ssforward && !m_para->midi_record_run && !m_para->midi_play_run) {
                if (m_para->midi_single_run) {
                    m_para->midi_single_run_changed = 1;
                } else {
                    if (m_frame < m_para->end_frame) {
                        m_frame ++;
                    } else {
                        m_frame = 0;
                    }
                    m_para->frame = m_frame;
                    m_para->midi_single_run_changed = 1;
                    changed = 1;
                }
            }
        }
    }
}

BOOL Record::StartMidiIn() {
    midi_in_list_node *midi_in_list_node;
    for (midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = midi_in_list_node->next_midi_in_list_node) {
        if (midiInOpen(&midi_in_list_node->midi_in, midi_in_list_node->midi_in_number, (DWORD_PTR)CBMidiOpen, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) {
            AfxMessageBox("Cannot open MIDI input port.",MB_OK | MB_ICONSTOP);
            return FALSE;
        }
    }
    m_para->midi_device_run = 1;
    for (midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = midi_in_list_node->next_midi_in_list_node) {
        midiInStart(midi_in_list_node->midi_in);
    }
    return TRUE;
}

void Record::StopMidiIn() const {
    midi_in_list_node *next_midi_in_list_node;

    for (const midi_in_list_node *midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = next_midi_in_list_node) {
        next_midi_in_list_node = midi_in_list_node->next_midi_in_list_node;
        midiInStop(midi_in_list_node->midi_in);
        midiInClose(midi_in_list_node->midi_in);
    }
    m_para->midi_device_run = 0;
//    return TRUE;
}

void Record::DisableAll() const {
    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON4);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON6);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDOK);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDCANCEL);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO1);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO2);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO3);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO4);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_CHECK1);
    id1->EnableWindow(FALSE);
    auto *id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
    id2->EnableWindow(FALSE);
}

void Record::EnableAll() const {
    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON4);
    if (m_para->ssforward == 0) {
        id1->EnableWindow(FALSE);
    } else {
        id1->EnableWindow(TRUE);
    }
    id1 = (CButton *)GetDlgItem(IDC_BUTTON6);
    id1->EnableWindow(FALSE);
    id1 = (CButton *)GetDlgItem(IDOK);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDCANCEL);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO1);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO2);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO3);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO4);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_CHECK1);
    id1->EnableWindow(TRUE);
    auto *id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
    id2->EnableWindow(TRUE);
}

BOOL Record::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CString temp;

    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
    const HMODULE hmodul = GetModuleHandle("Midicontrol.hxt");
    HICON hicon = ::LoadIcon(hmodul,MAKEINTRESOURCE(IDI_ICON1));
    id1->SetIcon(hicon);

    id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
    hicon = ::LoadIcon(hmodul,MAKEINTRESOURCE(IDI_ICON2));
    id1->SetIcon(hicon);

    id1 = (CButton *)GetDlgItem(IDC_RADIO1);
    id1->SetCheck(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO2);
    id1->SetCheck(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO3);
    id1->SetCheck(FALSE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO4);
    id1->SetCheck(TRUE);
    temp.Format("%d", (int)m_para->fps);
    SetDlgItemText(IDC_RADIO4, temp);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON6);
    id1->EnableWindow(FALSE);

    if (m_para->ssforward == 0) {
        id1 = (CButton *)GetDlgItem(IDC_BUTTON4);
        id1->EnableWindow(FALSE);
    }
    m_para->time = 0;
    m_para->frame = 0;
    m_para->midi_record_run = 0;
    m_para->midi_play_run = 0;
    m_para->midi_single_run = 0;
    changed = 0;
    update_run = 0;
    force_update = 0;

    CreateChannels();
    StartMidiIn();
    m_para->hproject->SetTime(m_para->time);
    timer_id = SetTimer(IDT_TIMER3, 25, nullptr);
    //	timer_id = Record::SetTimer(IDT_TIMER3,10,nullptr); //10 ms
    if (timer_id == 0)
        AfxMessageBox("Starting Timer fails",MB_OK);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Record::OnButton1() {
    //Rewind
    m_frame = 0;
    UpdateData(FALSE);
    m_para->frame = m_frame;
    m_para->time.SetFrame(m_para->frame, m_para->fps);
    m_para->hproject->SetTime(m_para->time);
    if (m_para->chor)
        m_para->chor->SetTime(m_para->time);
    force_update = 1;
    changed = 1;
}

void Record::OnButton2() {
    //Play
    DisableAll();
    if (m_frame >= m_para->end_frame) {
        m_para->time = 0;
        m_frame = 0;
        m_para->frame = m_frame;
        m_para->hproject->SetTime(m_para->time);
        if (m_para->chor)
            m_para->chor->SetTime(m_para->time);
        changed = 1;
    }
    m_para->midi_play_run = 1;
    timer_id = SetTimer(IDT_TIMER2, m_para->teiler, nullptr);
    if (timer_id == 0)
        AfxMessageBox("Starting Timer fails",MB_OK);
}

void Record::OnButton3() {
    //Record
    if (m_deletebeforerecord)
        DeleteBeforeRecord();
    DisableAll();
    m_para->midi_record_run = 1;
    timer_id = SetTimer(IDT_TIMER1, m_para->teiler, nullptr);
    if (timer_id == 0)
        AfxMessageBox("Starting Timer fails",MB_OK);
}

void Record::OnButton4() {
    //Record SingleStep
    if (m_deletebeforerecord)
        DeleteBeforeRecord();
    DisableAll();
    m_para->midi_single_run = 1;
    m_para->midi_single_run_changed = 0;
    timer_id = SetTimer(IDT_TIMER1, 200, nullptr);
    if (timer_id == 0)
        AfxMessageBox("Starting Timer fails",MB_OK);
}

void Record::OnButton6() {
    //Stop Play/Record
    if (m_para->midi_record_run) {
        m_para->midi_record_run = 0;
        if (m_para->frame > m_para->end_frame)
            m_para->end_frame = (float)m_para->frame;
        //		SetFirstFrame(FALSE);
    }
    if (m_para->midi_single_run) {
        m_para->midi_single_run = 0;
        if (m_para->frame > m_para->end_frame)
            m_para->end_frame = (float)m_para->frame;
        //		SetFirstFrame(FALSE);
    }
    m_para->midi_play_run = 0;
    KillTimer(IDT_TIMER1);
    KillTimer(IDT_TIMER2);
    EnableAll();
}

void Record::OnRadio1()  {
    //1 fps
    m_para->teiler = 1000;
}

void Record::OnRadio2()  {
    //5 fps
    m_para->teiler = 200;
}

void Record::OnRadio3()  {
    //10 fps
    m_para->teiler = 100;
}

void Record::OnRadio4()  {
    //user fps
    m_para->teiler = (unsigned int)(1000 / m_para->fps);
}

void Record::OnTimer(const UINT_PTR nIDEvent) {
    int i;
    switch (nIDEvent) {
        case IDT_TIMER1:
        {
            if (m_para->midi_record_run) {

                for (i = 0; i < m_para->az_note; ++i) {
                    if (m_para->p_note[i].changed) {
                        if (m_para->p_note[i].objt == HOT_COLOR) {
                            m_para->p_note[i].hcp->StoreValue(m_para->time, m_para->p_note[i].value_color[m_para->p_note[i].akt_value],FALSE);
                        } else {
                            m_para->p_note[i].hfp->StoreValue(m_para->time, m_para->p_note[i].value[m_para->p_note[i].akt_value],FALSE);
                        }
                        m_para->p_note[i].changed = 0;
                    }
                }
                for (i = 0; i < m_para->az_key; ++i) {
                    if (m_para->p_key[i].changed) {
                        if (m_para->p_key[i].objt == HOT_COLOR) {
                            m_para->p_key[i].hcp->StoreValue(m_para->time, m_para->p_key[i].value_color[m_para->p_key[i].akt_value],FALSE);
                        } else {
                            m_para->p_key[i].hfp->StoreValue(m_para->time, m_para->p_key[i].value[m_para->p_key[i].akt_value],FALSE);
                        }
                        m_para->p_key[i].changed = 0;
                    }
                }
                for (i = 0; i < m_para->az_control; ++i) {
                    if (m_para->p_control[i].changed) {
                        if (m_para->p_control[i].objt == HOT_COLOR) {
                            m_para->p_control[i].hcp->StoreValue(m_para->time, m_para->p_control[i].value_color[m_para->p_control[i].akt_value],FALSE);
                        } else {
                            m_para->p_control[i].hfp->StoreValue(m_para->time, m_para->p_control[i].value[m_para->p_control[i].akt_value],FALSE);
                        }
                        m_para->p_control[i].changed = 0;
                    }
                }

                m_frame ++;
                m_para->frame = m_frame;
                m_para->time.SetFrame(m_para->frame, m_para->fps);
                m_para->hproject->SetTime(m_para->time);
                if (m_para->chor)
                    m_para->chor->SetTime(m_para->time);
                UpdateData(false);
                changed = 1;
            }
            if (m_para->midi_single_run) {
                if (m_para->midi_single_run_changed) {
                    for (i = 0; i < m_para->az_note; ++i) {
                        if (m_para->p_note[i].changed) {
                            if (m_para->p_note[i].objt == HOT_COLOR) {
                                m_para->p_note[i].hcp->StoreValue(m_para->time, m_para->p_note[i].value_color[m_para->p_note[i].akt_value],FALSE);
                            } else {
                                m_para->p_note[i].hfp->StoreValue(m_para->time, m_para->p_note[i].value[m_para->p_note[i].akt_value],FALSE);
                            }
                            m_para->p_note[i].changed = 0;
                        }
                    }
                    for (i = 0; i < m_para->az_key; ++i) {
                        if (m_para->p_key[i].changed) {
                            if (m_para->p_key[i].objt == HOT_COLOR) {
                                m_para->p_key[i].hcp->StoreValue(m_para->time, m_para->p_key[i].value_color[m_para->p_key[i].akt_value],FALSE);
                            } else {
                                m_para->p_key[i].hfp->StoreValue(m_para->time, m_para->p_key[i].value[m_para->p_key[i].akt_value],FALSE);
                            }
                            m_para->p_key[i].changed = 0;
                        }
                    }
                    for (i = 0; i < m_para->az_control; ++i) {
                        if (m_para->p_control[i].changed) {
                            if (m_para->p_control[i].objt == HOT_COLOR) {
                                m_para->p_control[i].hcp->StoreValue(m_para->time, m_para->p_control[i].value_color[m_para->p_control[i].akt_value],FALSE);
                            } else {
                                m_para->p_control[i].hfp->StoreValue(m_para->time, m_para->p_control[i].value[m_para->p_control[i].akt_value],FALSE);
                            }
                            m_para->p_control[i].changed = 0;
                        }
                    }
                    m_frame ++;
                    m_para->frame = m_frame;
                    m_para->time.SetFrame(m_para->frame, m_para->fps);
                    m_para->hproject->SetTime(m_para->time);
                    if (m_para->chor)
                        m_para->chor->SetTime(m_para->time);
                    UpdateData(false);
                    m_para->midi_single_run_changed = 0;
                    changed = 1;
                }
            }
        }
        break;
        case IDT_TIMER2:
            while (update_run) {
                Sleep(10);
            }
            m_frame ++;
            m_para->frame = m_frame;
            m_para->time.SetFrame(m_para->frame, m_para->fps);
            m_para->hproject->SetTime(m_para->time);
            if (m_para->chor)
                m_para->chor->SetTime(m_para->time);
            changed = 1;
            UpdateData(false);
            if (m_para->frame == m_para->end_frame) {
                KillTimer(IDT_TIMER2);
                EnableAll();
                m_para->midi_play_run = 0;
                changed = 1;
            }
            break;
        case IDT_TIMER3:
            if (changed) {
                update_run = 1;
                if (m_para->midi_single_run_changed && !m_para->midi_single_run) {
                    m_para->time.SetFrame(m_para->frame, m_para->fps);
                    m_para->hproject->SetTime(m_para->time);
                    if (m_para->chor)
                        m_para->chor->SetTime(m_para->time);
                    UpdateData(false);
                    m_para->midi_single_run_changed = 0;
                }
                m_para->hproject->UpdateAllViews(TRUE);
                changed = 0;
                update_run = 0;
            }
            break;
        default:
            break;
    }

    CDialog::OnTimer(nIDEvent);
}

void Record::OnClose() {

    KillTimer(IDT_TIMER1);
    KillTimer(IDT_TIMER2);
    KillTimer(IDT_TIMER3);
    if (m_para->midi_device_run)
        StopMidiIn();
    CDialog::OnClose();
}

void Record::OnOK() {
    KillTimer(IDT_TIMER1);
    KillTimer(IDT_TIMER2);
    KillTimer(IDT_TIMER3);
    if (m_para->midi_device_run)
        StopMidiIn();
    SetFirstFrame(TRUE);
    CPluginDialog::OnOK();
}

void Record::OnCancel() {

    KillTimer(IDT_TIMER1);
    KillTimer(IDT_TIMER2);
    KillTimer(IDT_TIMER3);
    if (m_para->midi_device_run)
        StopMidiIn();
    CPluginDialog::OnCancel();
}

void Record::OnChangeEdit1() {
    UpdateData(TRUE);
    m_para->frame = m_frame;
    m_para->time.SetFrame(m_para->frame, m_para->fps);
    m_para->hproject->SetTime(m_para->time);
    if (m_para->chor)
        m_para->chor->SetTime(m_para->time);
    force_update = 1;
    changed = 1;
}

void Record::SetFirstFrame(const BOOL store) const {
    int i;
    for (i = 0; i < m_para->az_control; ++i) {
        if (m_para->p_control[i].objt == HOT_COLOR) {
            m_para->p_control[i].hcp->StoreValue(Time(), m_para->p_control[i].value_color[m_para->p_control[i].value_beginn], store);
        } else {
            m_para->p_control[i].hfp->StoreValue(Time(), m_para->p_control[i].value[m_para->p_control[i].value_beginn], store);
        }
    }
    for (i = 0; i < m_para->az_key; ++i) {
        if (m_para->p_key[i].objt == HOT_COLOR) {
            m_para->p_key[i].hcp->StoreValue(Time(), m_para->p_key[i].value_color[m_para->p_key[i].value_beginn], store);
        } else {
            m_para->p_key[i].hfp->StoreValue(Time(), m_para->p_key[i].value[m_para->p_key[i].value_beginn], store);
        }
    }
    for (i = 0; i < m_para->az_note; ++i) {
        if (m_para->p_note[i].objt == HOT_COLOR) {
            m_para->p_note[i].hcp->StoreValue(Time(), m_para->p_note[i].value_color[m_para->p_note[i].value_beginn], store);
        } else {
            m_para->p_note[i].hfp->StoreValue(Time(), m_para->p_note[i].value[m_para->p_note[i].value_beginn], store);
        }
    }
}

void Record::OnCheck1() {
    UpdateData(TRUE);
}
