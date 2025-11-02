// Assign.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Midicontrol.h"
#include "Assign.h"
#include "viewassigned.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

Assign::Assign(PARAMETER *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(Assign)
    m_para = para;
    //}}AFX_DATA_INIT
}

void Assign::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Assign)
    DDX_Text(pDX, IDC_EDIT1, m_min_val);
    DDX_Text(pDX, IDC_EDIT2, m_max_val);
    DDX_Check(pDX, IDC_CHECK2, m_para->embed);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Assign, CDialog)
    //{{AFX_MSG_MAP(Assign)
    ON_BN_CLICKED(IDC_RADIO1, &Assign::OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &Assign::OnRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &Assign::OnRadio3)
    ON_BN_CLICKED(IDC_RADIO4, &Assign::OnRadio4)
    ON_BN_CLICKED(IDC_RADIO5, &Assign::OnRadio5)
    ON_CBN_SELENDOK(IDC_COMBO1, &Assign::OnSelendokCombo1)
    ON_CBN_SELENDOK(IDC_COMBO2, &Assign::OnSelendokCombo2)
    ON_WM_DRAWITEM()
    ON_BN_CLICKED(IDC_BUTTON1, &Assign::OnButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &Assign::OnButton2)
    ON_EN_CHANGE(IDC_EDIT1, &Assign::OnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT2, &Assign::OnChangeEdit2)
    ON_BN_CLICKED(IDC_BUTTON6, &Assign::OnButton6)
    ON_BN_CLICKED(IDC_BUTTON3, &Assign::OnButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &Assign::OnButton4)
    ON_BN_CLICKED(IDC_RADIO6, &Assign::OnRadio6)
    ON_BN_CLICKED(IDC_RADIO7, &Assign::OnRadio7)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON7, &Assign::OnButton7)
    ON_BN_CLICKED(IDC_BUTTON8, &Assign::OnButton8)
    ON_BN_CLICKED(IDC_BUTTON9, &Assign::OnButton9)
    ON_BN_CLICKED(IDC_BUTTON10, &Assign::OnButton10)
    ON_BN_CLICKED(IDC_CHECK1, &Assign::OnCheck1)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Assign 

void Assign::CBMidiOpen2(HMIDIIN hMidiIn, const UINT wMsg, const DWORD dwInstance, const DWORD dwParam1, const DWORD dwParam2) {
    ((Assign *)dwInstance)->MidiOpenNotify2(hMidiIn, wMsg, dwParam1, dwParam2);
}

void Assign::MidiOpenNotify2(HMIDIIN midi_in, const UINT msg_type, const DWORD midi_msg, DWORD param2) {
    unsigned int midi_in_number;

    midiInGetID(midi_in, &midi_in_number);

    if (msg_type == MIM_DATA) {
        union {
            DWORD dwData;
            BYTE bData[4];
        } u{};

        u.dwData = midi_msg;

        switch (u.bData[0] & 0xF0) {
            case 0x90:
            {
                const COLORREF itemdata = RGB(0x90, u.bData[0] & 0x0F, u.bData[1]);
                if (itemdata != m_para->ssforward) {
                    CString temp;
                    m_para->ssforward = itemdata;
                    temp.Format("Note On | Channel %2d | Pitch %3d", u.bData[0] & 0x0F, u.bData[1]);
                    SetDlgItemText(IDC_STATIC_FOR, temp);
                }
                break;
            }
        }
    }
}

void Assign::UpdateControllerRun() {

    CString temp;
    const CComboBox *id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id2->GetCurSel();
    const int index = id2->GetItemData(i);

    m_para->obj[m_para->obj_selectet].prop[index].driven_value[0] = GetRValue(m_para->aktcontroller);
    m_para->obj[m_para->obj_selectet].prop[index].driven_value[1] = GetGValue(m_para->aktcontroller);
    m_para->obj[m_para->obj_selectet].prop[index].driven_value[2] = GetBValue(m_para->aktcontroller);

    switch (m_para->obj[m_para->obj_selectet].prop[index].driven_value[0]) {
        case 0x90:
        {
            temp.Format("Note On          | Channel %2d | Pitch    %3d", m_para->obj[m_para->obj_selectet].prop[index].driven_value[1], m_para->obj[m_para->obj_selectet].prop[index].driven_value[2]);
            break;
        }
        case 0xA0:
        {
            temp.Format("Key Pressure     | Channel %2d | Pitch    %3d", m_para->obj[m_para->obj_selectet].prop[index].driven_value[1], m_para->obj[m_para->obj_selectet].prop[index].driven_value[2]);
            break;
        }
        case 0xB0:
        {
            temp.Format("Control Change   | Channel %2d | Number   %3d", m_para->obj[m_para->obj_selectet].prop[index].driven_value[1], m_para->obj[m_para->obj_selectet].prop[index].driven_value[2]);
            break;
        }
        default:
            temp.Format("");
    }
    SetDlgItemText(IDC_STATIC_CONTROLLER, temp);
}

void Assign::CBMidiOpen(HMIDIIN hMidiIn, const UINT wMsg, const DWORD dwInstance, const DWORD dwParam1, const DWORD dwParam2) {
    ((Assign *)dwInstance)->MidiOpenNotify(hMidiIn, wMsg, dwParam1, dwParam2);
}

void Assign::MidiOpenNotify(HMIDIIN midi_in, const UINT msg_type, const DWORD midi_msg, DWORD param2) {
    unsigned int midi_in_number;

    midiInGetID(midi_in, &midi_in_number);

    if (msg_type == MIM_DATA) {
        COLORREF itemdata;
        union {
            DWORD dwData;
            BYTE bData[4];
        } u{};

        u.dwData = midi_msg;

        switch (u.bData[0] & 0xF0) {
            case 0x90:
            {
                itemdata = RGB(0x90, u.bData[0] & 0x0F, u.bData[1]);
                if (itemdata != m_para->aktcontroller) {
                    m_para->aktcontroller = itemdata;
                    UpdateControllerRun();
                }
                break;
            }
            case 0xA0:
            {
                itemdata = RGB(0xA0, u.bData[0] & 0x0F, u.bData[1]);
                if (itemdata != m_para->aktcontroller) {
                    m_para->aktcontroller = itemdata;
                    UpdateControllerRun();
                }
                break;
            }
            case 0xB0:
            {
                itemdata = RGB(0xB0, u.bData[0] & 0x0F, u.bData[1]);
                if (itemdata != m_para->aktcontroller) {
                    m_para->aktcontroller = itemdata;
                    UpdateControllerRun();
                }
                break;
            }
        }
    }
}

void Assign::UpdateLB2() {
    CButton *id2;
    CEdit *id3;
    CStatic *id4;
    CString temp;

    const CComboBox *id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id1->GetCurSel();
    const int index = id1->GetItemData(i);

    // Value
    if (m_para->obj[m_para->obj_selectet].prop[index].objt == HOT_COLOR) {
        id2 = (CButton *)GetDlgItem(IDC_BUTTON1);
        id2->ShowWindow(TRUE);
        id2->Invalidate(TRUE);
        id2 = (CButton *)GetDlgItem(IDC_BUTTON2);
        id2->ShowWindow(TRUE);
        id2->Invalidate(TRUE);
        id2 = (CButton *)GetDlgItem(IDC_BUTTON5);
        id2->ShowWindow(TRUE);
        id2->Invalidate(TRUE);
        id3 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id3->ShowWindow(FALSE);
        id3 = (CEdit *)GetDlgItem(IDC_EDIT2);
        id3->ShowWindow(FALSE);
        id4 = (CStatic *)GetDlgItem(IDC_STATIC_ACT);
        id4->ShowWindow(FALSE);
    } else {
        id2 = (CButton *)GetDlgItem(IDC_BUTTON1);
        id2->ShowWindow(FALSE);
        id2 = (CButton *)GetDlgItem(IDC_BUTTON2);
        id2->ShowWindow(FALSE);
        id2 = (CButton *)GetDlgItem(IDC_BUTTON5);
        id2->ShowWindow(FALSE);
        id3 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id3->ShowWindow(TRUE);
        id3 = (CEdit *)GetDlgItem(IDC_EDIT2);
        id3->ShowWindow(TRUE);
        id4 = (CStatic *)GetDlgItem(IDC_STATIC_ACT);
        id4->ShowWindow(TRUE);
        temp.Format("%.3f", m_para->obj[m_para->obj_selectet].prop[index].org_value);
        SetDlgItemText(IDC_STATIC_ACT, temp);
        m_min_val = m_para->obj[m_para->obj_selectet].prop[index].min_value;
        m_max_val = m_para->obj[m_para->obj_selectet].prop[index].max_value;
        UpdateData(FALSE);
    }

    // Controller
    if (m_para->obj[m_para->obj_selectet].prop[index].driven) {
        // Controller selektiert
        id2 = (CButton *)GetDlgItem(IDC_RADIO6);
        id2->SetCheck(FALSE);
        id2 = (CButton *)GetDlgItem(IDC_RADIO7);
        id2->SetCheck(TRUE);
        id2 = (CButton *)GetDlgItem(IDC_BUTTON3);
        id2->EnableWindow(TRUE);
        id2 = (CButton *)GetDlgItem(IDC_BUTTON4);
        id2->EnableWindow(FALSE);
        id4 = (CStatic *)GetDlgItem(IDC_STATIC_CONTROLLER);
        id4->ShowWindow(TRUE);
        id4 = (CStatic *)GetDlgItem(IDC_STATIC_TIME);
        id4->ShowWindow(TRUE);
        switch (m_para->obj[m_para->obj_selectet].prop[index].driven_value[0]) {
            case 0x90:
            {
                temp.Format("Note On          | Channel %2d | Pitch    %3d", m_para->obj[m_para->obj_selectet].prop[index].driven_value[1], m_para->obj[m_para->obj_selectet].prop[index].driven_value[2]);
                break;
            }
            case 0xA0:
            {
                temp.Format("Key Pressure     | Channel %2d | Pitch    %3d", m_para->obj[m_para->obj_selectet].prop[index].driven_value[1], m_para->obj[m_para->obj_selectet].prop[index].driven_value[2]);
                break;
            }
            case 0xB0:
            {
                temp.Format("Control Change   | Channel %2d | Number   %3d", m_para->obj[m_para->obj_selectet].prop[index].driven_value[1], m_para->obj[m_para->obj_selectet].prop[index].driven_value[2]);
                break;
            }
            default:
                temp.Format("");
        }
        SetDlgItemText(IDC_STATIC_CONTROLLER, temp);
    } else {
        // Kein Controller
        id2 = (CButton *)GetDlgItem(IDC_RADIO6);
        id2->SetCheck(TRUE);
        id2 = (CButton *)GetDlgItem(IDC_RADIO7);
        id2->SetCheck(FALSE);
        id2 = (CButton *)GetDlgItem(IDC_BUTTON3);
        id2->EnableWindow(FALSE);
        id2 = (CButton *)GetDlgItem(IDC_BUTTON4);
        id2->EnableWindow(FALSE);
        id4 = (CStatic *)GetDlgItem(IDC_STATIC_CONTROLLER);
        id4->ShowWindow(FALSE);
        id4 = (CStatic *)GetDlgItem(IDC_STATIC_TIME);
        id4->ShowWindow(FALSE);
    }

}

void Assign::FillLB2() {
    CButton *id2;
    int index, i;
    CString temp;

    temp.Format("%d Properties", m_para->obj[m_para->obj_selectet].azprop);
    SetDlgItemText(IDC_STATIC_PROP, temp);

    bool surface = false;
    bool transform = false;
    bool color = false;
    bool pose = false;
    for (i = 0; i < m_para->obj[m_para->obj_selectet].azprop; ++i) {
        switch (m_para->obj[m_para->obj_selectet].prop[i].matchtype) {
            case 1:
                transform = true;
                break;
            case 2:
                color = true;
                break;
            case 3:
                surface = true;
                break;
            case 4:
                pose = true;
                break;
        }
    }

    if (!transform) {
        id2 = (CButton *)GetDlgItem(IDC_RADIO3);
        id2->EnableWindow(FALSE);
    } else {
        id2 = (CButton *)GetDlgItem(IDC_RADIO3);
        id2->EnableWindow(TRUE);
    }
    if (!color) {
        id2 = (CButton *)GetDlgItem(IDC_RADIO5);
        id2->EnableWindow(FALSE);
    } else {
        id2 = (CButton *)GetDlgItem(IDC_RADIO5);
        id2->EnableWindow(TRUE);
    }
    if (!surface) {
        id2 = (CButton *)GetDlgItem(IDC_RADIO4);
        id2->EnableWindow(FALSE);
    } else {
        id2 = (CButton *)GetDlgItem(IDC_RADIO4);
        id2->EnableWindow(TRUE);
    }
    if (!pose) {
        id2 = (CButton *)GetDlgItem(IDC_RADIO2);
        id2->EnableWindow(FALSE);
    } else {
        id2 = (CButton *)GetDlgItem(IDC_RADIO2);
        id2->EnableWindow(TRUE);
    }

    auto *id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    id1->ResetContent();
    switch (m_para->obj[m_para->obj_selectet].Filter) {
        case 0:
            for (i = 0; i < m_para->obj[m_para->obj_selectet].azprop; ++i) {
                index = id1->AddString(m_para->obj[m_para->obj_selectet].prop[i].name);
                id1->SetItemData(index, i);
            }
            break;
        case 1:
            for (i = 0; i < m_para->obj[m_para->obj_selectet].azprop; ++i) {
                if (m_para->obj[m_para->obj_selectet].prop[i].matchtype == 1) {
                    index = id1->AddString(m_para->obj[m_para->obj_selectet].prop[i].name);
                    id1->SetItemData(index, i);
                }
            }
            break;
        case 2:
            for (i = 0; i < m_para->obj[m_para->obj_selectet].azprop; ++i) {
                if (m_para->obj[m_para->obj_selectet].prop[i].matchtype == 2) {
                    index = id1->AddString(m_para->obj[m_para->obj_selectet].prop[i].name);
                    id1->SetItemData(index, i);
                }
            }
            break;
        case 3:
            for (i = 0; i < m_para->obj[m_para->obj_selectet].azprop; ++i) {
                if (m_para->obj[m_para->obj_selectet].prop[i].matchtype == 3) {
                    index = id1->AddString(m_para->obj[m_para->obj_selectet].prop[i].name);
                    id1->SetItemData(index, i);
                }
            }
            break;
        case 4:
            for (i = 0; i < m_para->obj[m_para->obj_selectet].azprop; ++i) {
                if (m_para->obj[m_para->obj_selectet].prop[i].matchtype == 4) {
                    index = id1->AddString(m_para->obj[m_para->obj_selectet].prop[i].name);
                    id1->SetItemData(index, i);
                }
            }
            break;
    }
    id1->SetCurSel(0);
    UpdateLB2();
}

BOOL Assign::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    CButton *id2;

    auto *id1 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    if (m_para->azobject == 1) {
        id1->AddString(m_para->obj[0].name);
        id1->EnableWindow(FALSE);
    } else {
        for (int i = 0; i < m_para->azobject; ++i) {
            id1->AddString(m_para->obj[i].name);
        }
    }
    id1->SetCurSel(m_para->obj_selectet);
    switch (m_para->obj[m_para->obj_selectet].Filter) {
        case 0:
            id2 = (CButton *)GetDlgItem(IDC_RADIO1);
            id2->SetCheck(TRUE);
            break;
        case 1:
            id2 = (CButton *)GetDlgItem(IDC_RADIO3);
            id2->SetCheck(TRUE);
            break;
        case 2:
            id2 = (CButton *)GetDlgItem(IDC_RADIO5);
            id2->SetCheck(TRUE);
            break;
        case 3:
            id2 = (CButton *)GetDlgItem(IDC_RADIO4);
            id2->SetCheck(TRUE);
            break;
        case 4:
            id2 = (CButton *)GetDlgItem(IDC_RADIO2);
            id2->SetCheck(TRUE);
            break;
    }
    id2 = (CButton *)GetDlgItem(IDC_CHECK1);
    if (m_para->override) {
        id2->SetCheck(TRUE);
    } else {
        id2->SetCheck(FALSE);
    }
    if (m_para->ssforward != 0) {
        CString temp;
        temp.Format("Note On | Channel %2d | Pitch %3d",GetGValue(m_para->ssforward), GetBValue(m_para->ssforward));
        SetDlgItemText(IDC_STATIC_FOR, temp);
    }

    FillLB2();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Assign::OnRadio1() {
    m_para->obj[m_para->obj_selectet].Filter = 0;
    FillLB2();
}

void Assign::OnRadio2() {
    m_para->obj[m_para->obj_selectet].Filter = 4;
    FillLB2();
}

void Assign::OnRadio3() {
    m_para->obj[m_para->obj_selectet].Filter = 1;
    FillLB2();
}

void Assign::OnRadio4() {
    m_para->obj[m_para->obj_selectet].Filter = 3;
    FillLB2();
}

void Assign::OnRadio5() {
    m_para->obj[m_para->obj_selectet].Filter = 2;
    FillLB2();
}

void Assign::OnSelendokCombo1() {
    CButton *id2;

    const CComboBox *id1 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    m_para->obj_selectet = id1->GetCurSel();
    switch (m_para->obj[m_para->obj_selectet].Filter) {
        case 0:
            id2 = (CButton *)GetDlgItem(IDC_RADIO1);
            id2->SetCheck(TRUE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO2);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO3);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO4);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO5);
            id2->SetCheck(FALSE);
            break;
        case 1:
            id2 = (CButton *)GetDlgItem(IDC_RADIO3);
            id2->SetCheck(TRUE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO2);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO1);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO4);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO5);
            id2->SetCheck(FALSE);
            break;
        case 2:
            id2 = (CButton *)GetDlgItem(IDC_RADIO5);
            id2->SetCheck(TRUE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO2);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO3);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO4);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO1);
            id2->SetCheck(FALSE);
            break;
        case 3:
            id2 = (CButton *)GetDlgItem(IDC_RADIO4);
            id2->SetCheck(TRUE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO2);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO3);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO1);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO5);
            id2->SetCheck(FALSE);
            break;
        case 4:
            id2 = (CButton *)GetDlgItem(IDC_RADIO2);
            id2->SetCheck(TRUE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO1);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO3);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO4);
            id2->SetCheck(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO5);
            id2->SetCheck(FALSE);
            break;
    }
    FillLB2();
}

void Assign::OnSelendokCombo2() {
    UpdateLB2();
}

void Assign::OnDrawItem(const int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) {
    if (nIDCtl == IDC_BUTTON1) {

        const CComboBox *id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
        const int i = id1->GetCurSel();
        const int index = id1->GetItemData(i);

        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        CRect rect = lpDrawItemStruct->rcItem;
        const UINT state = lpDrawItemStruct->itemState;
        if (state & ODS_SELECTED)
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
        else
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

        rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
        pDC->FillSolidRect(rect, m_para->obj[m_para->obj_selectet].prop[index].min_value_color);
    }
    if (nIDCtl == IDC_BUTTON2) {

        const CComboBox *id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
        const int i = id1->GetCurSel();
        const int index = id1->GetItemData(i);

        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        CRect rect = lpDrawItemStruct->rcItem;
        const UINT state = lpDrawItemStruct->itemState;
        if (state & ODS_SELECTED)
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
        else
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

        rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
        pDC->FillSolidRect(rect, m_para->obj[m_para->obj_selectet].prop[index].max_value_color);
    }
    if (nIDCtl == IDC_BUTTON5) {

        const CComboBox *id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
        const int i = id1->GetCurSel();
        const int index = id1->GetItemData(i);

        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        CRect rect = lpDrawItemStruct->rcItem;
        const UINT state = lpDrawItemStruct->itemState;
        if (state & ODS_SELECTED)
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
        else
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

        rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
        pDC->FillSolidRect(rect, m_para->obj[m_para->obj_selectet].prop[index].org_value_color);
    }

    CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void Assign::OnButton1() {
    const CComboBox *id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id2->GetCurSel();
    const int index = id2->GetItemData(i);

    CColorDialog cdlg(m_para->obj[m_para->obj_selectet].prop[index].min_value_color, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        m_para->obj[m_para->obj_selectet].prop[index].min_value_color = cdlg.GetColor();
        auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
        id1->Invalidate(TRUE);
    }

}

void Assign::OnButton2() {
    const CComboBox *id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id2->GetCurSel();
    const int index = id2->GetItemData(i);

    CColorDialog cdlg(m_para->obj[m_para->obj_selectet].prop[index].max_value_color, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        m_para->obj[m_para->obj_selectet].prop[index].max_value_color = cdlg.GetColor();
        auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
        id1->Invalidate(TRUE);
    }
}

void Assign::OnChangeEdit1() {
    const CComboBox *id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id2->GetCurSel();
    const int index = id2->GetItemData(i);
    UpdateData(TRUE);
    m_para->obj[m_para->obj_selectet].prop[index].min_value = m_min_val;
}

void Assign::OnChangeEdit2() {
    const CComboBox *id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id2->GetCurSel();
    const int index = id2->GetItemData(i);
    UpdateData(TRUE);
    m_para->obj[m_para->obj_selectet].prop[index].max_value = m_max_val;
}

void Assign::OnButton6() {
    const CComboBox *id3 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id3->GetCurSel();
    const int index = id3->GetItemData(i);
    const CWnd *cwnd = GetFocus();
    if (cwnd->GetDlgCtrlID() == IDC_EDIT1) {
        auto *id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
        id1->SetFocus();
    } else {
        if (cwnd->GetDlgCtrlID() == IDC_EDIT2) {
            CButton *id2;
            if (m_para->obj[m_para->obj_selectet].prop[index].driven) {
                id2 = (CButton *)GetDlgItem(IDC_RADIO7);
                id2->SetFocus();
            } else {
                id2 = (CButton *)GetDlgItem(IDC_RADIO6);
                id2->SetFocus();
            }
        }
    }
}

void Assign::OnRadio6() {
    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
    id1->EnableWindow(FALSE);
    const CComboBox *id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id2->GetCurSel();
    const int index = id2->GetItemData(i);
    m_para->obj[m_para->obj_selectet].prop[index].driven = 0;
    m_para->obj[m_para->obj_selectet].prop[index].driven_value[0] = 0;
    m_para->obj[m_para->obj_selectet].prop[index].driven_value[1] = 0;
    m_para->obj[m_para->obj_selectet].prop[index].driven_value[2] = 0;
    auto *id3 = (CStatic *)GetDlgItem(IDC_STATIC_CONTROLLER);
    id3->ShowWindow(FALSE);
    id3 = (CStatic *)GetDlgItem(IDC_STATIC_TIME);
    id3->ShowWindow(FALSE);

}

void Assign::OnRadio7() {
    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
    id1->EnableWindow(TRUE);
    const CComboBox *id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int i = id2->GetCurSel();
    const int index = id2->GetItemData(i);
    m_para->obj[m_para->obj_selectet].prop[index].driven = 1;
    auto *id3 = (CStatic *)GetDlgItem(IDC_STATIC_CONTROLLER);
    id3->ShowWindow(TRUE);
    id3 = (CStatic *)GetDlgItem(IDC_STATIC_TIME);
    id3->ShowWindow(TRUE);
    SetDlgItemText(IDC_STATIC_CONTROLLER, "");
    m_para->aktcontroller = RGB(0, 0, 0);
}

void Assign::OnButton3() {
    midi_in_list_node *midi_in_list_node;
    int not_stop = 1;

    for (midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = midi_in_list_node->next_midi_in_list_node) {
        if (midiInOpen(&midi_in_list_node->midi_in, midi_in_list_node->midi_in_number, (DWORD_PTR)CBMidiOpen, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) {
            AfxMessageBox("Cannot open MIDI input port.",MB_OK | MB_ICONSTOP);
            not_stop = 0;
        }
    }
    if (not_stop) {
        auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON7);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON8);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON9);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON10);
        id1->EnableWindow(FALSE);
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
        id1 = (CButton *)GetDlgItem(IDC_RADIO5);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO6);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO7);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_CHECK1);
        id1->EnableWindow(FALSE);
        auto *id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
        id2->EnableWindow(FALSE);
        id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
        id2->EnableWindow(FALSE);
        auto *id3 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id3->EnableWindow(FALSE);
        id3 = (CEdit *)GetDlgItem(IDC_EDIT2);
        id3->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON4);
        id1->EnableWindow(TRUE);
        for (midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = midi_in_list_node->next_midi_in_list_node) {
            midiInStart(midi_in_list_node->midi_in);
        }
        m_para->midi_device_run = 1;
        SetTimer(IDT_TIMER2, 30000, nullptr);
        zaehler = 30;
        SetTimer(IDT_TIMER1, 1000, nullptr);
    }
}

void Assign::OnButton4() {
    CComboBox *id2;
    midi_in_list_node *next_midi_in_list_node;

    KillTimer(IDT_TIMER1);
    KillTimer(IDT_TIMER2);
    for (const midi_in_list_node *midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = next_midi_in_list_node) {
        next_midi_in_list_node = midi_in_list_node->next_midi_in_list_node;
        midiInStop(midi_in_list_node->midi_in);
        midiInClose(midi_in_list_node->midi_in);
    }
    m_para->midi_device_run = 0;
    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON7);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON8);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON9);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON10);
    id1->EnableWindow(TRUE);
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
    id1 = (CButton *)GetDlgItem(IDC_RADIO5);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO6);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_RADIO7);
    id1->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_CHECK1);
    id1->EnableWindow(TRUE);
    if (m_para->azobject > 1) {
        id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
        id2->EnableWindow(TRUE);
    }
    id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    id2->EnableWindow(TRUE);
    auto *id3 = (CEdit *)GetDlgItem(IDC_EDIT1);
    id3->EnableWindow(TRUE);
    id3 = (CEdit *)GetDlgItem(IDC_EDIT2);
    id3->EnableWindow(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_BUTTON4);
    id1->EnableWindow(FALSE);
    SetDlgItemText(IDC_STATIC_TIME, "30 seconds left");
}

void Assign::OnTimer(const UINT_PTR nIDEvent) {
    // TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
    CButton *id1;
    CComboBox *id2;
    CEdit *id3;
    CStatic *id4;
    int i, index;
    midi_in_list_node *midi_in_list_node, *next_midi_in_list_node;
    CString temp;
    switch (nIDEvent) {
        case IDT_TIMER1:
            zaehler --;
            temp.Format("%d seconds left", zaehler);
            SetDlgItemText(IDC_STATIC_TIME, temp);
            break;
        case IDT_TIMER2:
            KillTimer(IDT_TIMER1);
            KillTimer(IDT_TIMER2);
            for (midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = next_midi_in_list_node) {
                next_midi_in_list_node = midi_in_list_node->next_midi_in_list_node;
                midiInStop(midi_in_list_node->midi_in);
                midiInClose(midi_in_list_node->midi_in);
            }
            m_para->midi_device_run = 0;
            id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON7);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON8);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON9);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON10);
            id1->EnableWindow(TRUE);
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
            id1 = (CButton *)GetDlgItem(IDC_RADIO5);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_RADIO6);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_RADIO7);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_CHECK1);
            id1->EnableWindow(TRUE);
            if (m_para->azobject > 1) {
                id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
                id2->EnableWindow(TRUE);
            }
            id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
            id2->EnableWindow(TRUE);
            id3 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id3->EnableWindow(TRUE);
            id3 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id3->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON4);
            id1->EnableWindow(FALSE);
            SetDlgItemText(IDC_STATIC_TIME, "30 seconds left");
            break;
        case IDT_TIMER3:
            KillTimer(IDT_TIMER1);
            KillTimer(IDT_TIMER3);
            for (midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = next_midi_in_list_node) {
                next_midi_in_list_node = midi_in_list_node->next_midi_in_list_node;
                midiInStop(midi_in_list_node->midi_in);
                midiInClose(midi_in_list_node->midi_in);
            }
            m_para->midi_device_run = 0;
            id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON7);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON8);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON9);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON10);
            id1->EnableWindow(TRUE);
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
            id1 = (CButton *)GetDlgItem(IDC_RADIO5);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_RADIO6);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_RADIO7);
            id1->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_CHECK1);
            id1->EnableWindow(TRUE);
            if (m_para->azobject > 1) {
                id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
                id2->EnableWindow(TRUE);
            }
            id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
            id2->EnableWindow(TRUE);
            i = id2->GetCurSel();
            index = id2->GetItemData(i);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
            if (m_para->obj[m_para->obj_selectet].prop[index].driven) {
                id1->EnableWindow(TRUE);
            } else {
                id1->EnableWindow(FALSE);
            }
            id3 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id3->EnableWindow(TRUE);
            id3 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id3->EnableWindow(TRUE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON4);
            id1->EnableWindow(FALSE);
            SetDlgItemText(IDC_STATIC_TIME, "30 seconds left");
            id4 = (CStatic *)GetDlgItem(IDC_STATIC_TIME);
            id4->ShowWindow(FALSE);
    }
    CDialog::OnTimer(nIDEvent);
}

void Assign::OnButton7() {
    midi_in_list_node *midi_in_list_node;
    int not_stop = 1;

    for (midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = midi_in_list_node->next_midi_in_list_node) {
        if (midiInOpen(&midi_in_list_node->midi_in, midi_in_list_node->midi_in_number, (DWORD_PTR)CBMidiOpen2, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) {
            AfxMessageBox("Cannot open MIDI input port.",MB_OK | MB_ICONSTOP);
            not_stop = 0;
        }
    }
    if (not_stop) {
        auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON7);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON8);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON9);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON10);
        id1->EnableWindow(FALSE);
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
        id1 = (CButton *)GetDlgItem(IDC_RADIO5);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO6);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO7);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_CHECK1);
        id1->EnableWindow(FALSE);
        auto *id2 = (CComboBox *)GetDlgItem(IDC_COMBO1);
        id2->EnableWindow(FALSE);
        id2 = (CComboBox *)GetDlgItem(IDC_COMBO2);
        id2->EnableWindow(FALSE);
        auto *id3 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id3->EnableWindow(FALSE);
        id3 = (CEdit *)GetDlgItem(IDC_EDIT2);
        id3->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_BUTTON4);
        id1->EnableWindow(TRUE);
        SetDlgItemText(IDC_STATIC_TIME, "10 seconds left");
        for (midi_in_list_node = m_para->first_midi_in_list_node; midi_in_list_node != nullptr; midi_in_list_node = midi_in_list_node->next_midi_in_list_node) {
            midiInStart(midi_in_list_node->midi_in);
        }
        m_para->midi_device_run = 1;
        zaehler = 10;
        auto *id4 = (CStatic *)GetDlgItem(IDC_STATIC_TIME);
        id4->ShowWindow(TRUE);
        SetTimer(IDT_TIMER3, 10000, nullptr);
        SetTimer(IDT_TIMER1, 1000, nullptr);
    }
}

void Assign::OnButton9() {
    //Save
    static char BASED_CODE szFilter[] = "Text Files (*.txt)|*.txt|";
    CString temp;

    String temp1 = m_para->hproject->GetFileName();
    String temp2 = temp1.Left(temp1.ReverseFind('.')) + ".txt";
    temp.Format("%s", temp2.Get());
    CFileDialog cdlg(FALSE, nullptr, temp, 0, szFilter, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        FileStream fs;
        temp = cdlg.GetPathName();
        temp2 = (String)temp;
        fs.Open(temp2, FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
        fs << "ssforward " << m_para->ssforward << nl;
        for (int i = 0; i < m_para->azobject; ++i) {
            for (int j = 0; j < m_para->obj[i].azprop; ++j) {
                if (m_para->obj[i].prop[j].driven) {
                    if (m_para->obj[i].prop[j].objt == HOT_COLOR) {
                        fs << m_para->obj[i].prop[j].min_value_color << " ";
                        fs << m_para->obj[i].prop[j].max_value_color << " ";
                    } else {
                        fs << m_para->obj[i].prop[j].min_value << " ";
                        fs << m_para->obj[i].prop[j].max_value << " ";
                    }
                    fs << m_para->obj[i].prop[j].driven_value[0] << " ";
                    fs << m_para->obj[i].prop[j].driven_value[1] << " ";
                    fs << m_para->obj[i].prop[j].driven_value[2] << " ";
                    fs << m_para->obj[i].prop[j].Fullname << nl;
                }
            }
        }
        fs.Close();
    }

}

void Assign::OnButton10() {
    //Load
    static char BASED_CODE szFilter[] = "Text Files (*.txt)|*.txt|";
    CString temp;
    char *stopstring;

    String temp1 = m_para->hproject->GetFileName();
    String temp2 = temp1.Left(temp1.ReverseFind('.')) + ".txt";
    temp.Format("%s", temp2.Get());
    CFileDialog cdlg(TRUE, nullptr, temp, 0, szFilter, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        FileStream fs;
        temp = cdlg.GetPathName();
        temp2 = (String)temp;
        fs.Open(temp2, FileMode::HS_ASCII | FileMode::HS_LOAD | FileMode::HS_DONTPROGRESS);
        fs.ReadLine(temp1);
        if (temp1.Find("ssforward") == -1) {
            AfxMessageBox("Not a definition file",MB_OK | MB_ICONSTOP);
            fs.Close();
        } else {
            int i;
            String temp3[6];
            temp2 = temp1.StrTok(" ");
            temp.Format("%s", temp1.Get());
            m_para->ssforward = strtoul(temp, &stopstring, 10);
            while (fs.ReadLine(temp1)) {
                if (temp1.GetLength() > 1) {
                    for (i = 0; i < 5; ++i) {
                        temp3[i] = temp1.StrTok(" ");
                    }
                    temp3[5] = temp1.Left(temp1.GetLength() - 1);
                    bool found = false;
                    for (i = 0; i < m_para->azobject; ++i) {
                        for (int j = 0; j < m_para->obj[i].azprop; ++j) {
                            if (temp3[5] == m_para->obj[i].prop[j].Fullname) {
                                if (m_para->obj[i].prop[j].objt == HOT_COLOR) {
                                    temp.Format("%s", temp3[0].Get());
                                    m_para->obj[i].prop[j].min_value_color = strtoul(temp, &stopstring, 10);
                                    temp.Format("%s", temp3[1].Get());
                                    m_para->obj[i].prop[j].max_value_color = strtoul(temp, &stopstring, 10);
                                } else {
                                    temp.Format("%s", temp3[0].Get());
                                    m_para->obj[i].prop[j].min_value = strtod(temp, &stopstring);
                                    temp.Format("%s", temp3[1].Get());
                                    m_para->obj[i].prop[j].max_value = strtod(temp, &stopstring);
                                }
                                temp.Format("%s", temp3[2].Get());
                                m_para->obj[i].prop[j].driven_value[0] = atoi_replace(temp);
                                temp.Format("%s", temp3[3].Get());
                                m_para->obj[i].prop[j].driven_value[1] = atoi_replace(temp);
                                temp.Format("%s", temp3[4].Get());
                                m_para->obj[i].prop[j].driven_value[2] = atoi_replace(temp);
                                m_para->obj[i].prop[j].driven = 1;
                                found = true;
                                break;
                            }
                        }
                        if (found)
                            break;
                    }
                }
            }
            fs.Close();
            temp.Format("Note On | Channel %2d | Pitch %3d",GetGValue(m_para->ssforward), GetBValue(m_para->ssforward));
            SetDlgItemText(IDC_STATIC_FOR, temp);
            UpdateLB2();
        }
    }
}

void Assign::OnOK() {
    int i, j, note, control, x, iscolor;
    double schritt;
    BYTE r_min, g_min, b_min;
    BYTE r_max, g_max, b_max;
    BYTE r_store, g_store, b_store;
    int schritt_r, schritt_g, schritt_b;

    UpdateData(true);
    int key = note = control = 0;
    m_para->az_control = m_para->az_key = m_para->az_note = 0;
    for (i = 0; i < m_para->azobject; ++i) {
        for (j = 0; j < m_para->obj[i].azprop; ++j) {
            if (m_para->obj[i].prop[j].driven) {
                switch (m_para->obj[i].prop[j].driven_value[0]) {
                    case 0x90:
                        m_para->az_note ++;
                        break;
                    case 0xA0:
                        m_para->az_key ++;
                        break;
                    case 0xB0:
                        m_para->az_control ++;
                        break;
                }
            }
        }
    }

    if (m_para->az_note > 0)
        m_para->p_note = new PROPERTIE2[m_para->az_note + 1];
    if (m_para->az_key > 0)
        m_para->p_key = new PROPERTIE2[m_para->az_key + 1];
    if (m_para->az_control > 0)
        m_para->p_control = new PROPERTIE2[m_para->az_control + 1];

    for (i = 0; i < m_para->azobject; ++i) {
        for (j = 0; j < m_para->obj[i].azprop; ++j) {
            if (m_para->obj[i].prop[j].driven) {
                if (m_para->obj[i].prop[j].Fullname.Find("Surface.DiffuseFalloff") > 0)
                    m_para->obj[i].prop[j].objt = HOT_PERCENT;
                if (m_para->obj[i].prop[j].Fullname.Find("Surface.SpecularIntensity") > 0)
                    m_para->obj[i].prop[j].objt = HOT_PERCENT;
                if (m_para->obj[i].prop[j].Fullname.Find("Surface.Roughness") > 0)
                    m_para->obj[i].prop[j].objt = HOT_PERCENT;
                if (m_para->obj[i].prop[j].Fullname.Find("Surface.RoughnessScale") > 0)
                    m_para->obj[i].prop[j].objt = HOT_PERCENT;
                if (m_para->obj[i].prop[j].Fullname.Find("Surface.Density") > 0)
                    m_para->obj[i].prop[j].objt = HOT_FLOAT;
                if (m_para->obj[i].prop[j].Fullname.Find("Intensity") > 0) {
                    if (m_para->obj[i].hobj->GetObjectType() == HOT_LIGHT)
                        m_para->obj[i].prop[j].objt = HOT_PERCENT;
                }
                if (m_para->obj[i].prop[j].Fullname.Find("Color.Red") > 0 || m_para->obj[i].prop[j].Fullname.Find("Color.Green") > 0 || m_para->obj[i].prop[j].Fullname.Find("Color.Blue") > 0) {
                    iscolor = 1;
                } else {
                    iscolor = 0;
                }
                switch (m_para->obj[i].prop[j].driven_value[0]) {
                    case 0x90:
                    {
                        m_para->p_note[note].prop = m_para->obj[i].prop[j].prop;
                        m_para->p_note[note].objt = m_para->obj[i].prop[j].objt;
                        m_para->p_note[note].ispose = m_para->obj[i].prop[j].ispose;
                        m_para->p_note[note].akt_value = 0;
                        m_para->p_note[note].value_beginn = 0;
                        m_para->p_note[note].driven_value = RGB(m_para->obj[i].prop[j].driven_value[0], m_para->obj[i].prop[j].driven_value[1], m_para->obj[i].prop[j].driven_value[2]);
                        switch (m_para->obj[i].prop[j].objt) {
                            case HOT_FLOAT:
                            {
                                if (iscolor) {
                                    if (m_para->obj[i].prop[j].min_value < 0)
                                        m_para->obj[i].prop[j].min_value = 0;
                                    if (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value > 255)
                                        m_para->obj[i].prop[j].max_value = m_para->obj[i].prop[j].min_value + 255;
                                    schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                    for (x = 0; x < 128; ++x) {
                                        m_para->p_note[note].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                    }
                                } else {
                                    schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                    for (x = 0; x < 128; ++x) {
                                        m_para->p_note[note].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                    }
                                }
                                m_para->p_note[note].hfp = (HFloatProperty *)m_para->p_note[note].prop;
                            }
                            break;
                            case HOT_EULERFLOAT:
                            {
                                schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                for (x = 0; x < 128; ++x) {
                                    m_para->p_note[note].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                }
                                m_para->p_note[note].hfp = (HFloatProperty *)m_para->p_note[note].prop;
                            }
                            break;
                            case HOT_PERCENT:
                            {
                                schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                for (x = 0; x < 128; ++x) {
                                    m_para->p_note[note].value[x] = (float)((schritt * x + m_para->obj[i].prop[j].min_value) / 100);
                                }
                                m_para->p_note[note].hfp = (HFloatProperty *)m_para->p_note[note].prop;
                            }
                            break;
                            case HOT_COLOR:
                            {
                                r_min = GetRValue(m_para->obj[i].prop[j].min_value_color);
                                g_min = GetGValue(m_para->obj[i].prop[j].min_value_color);
                                b_min = GetBValue(m_para->obj[i].prop[j].min_value_color);
                                r_max = GetRValue(m_para->obj[i].prop[j].max_value_color);
                                g_max = GetGValue(m_para->obj[i].prop[j].max_value_color);
                                b_max = GetBValue(m_para->obj[i].prop[j].max_value_color);
                                schritt_r = (r_max - r_min) / 127;
                                if (schritt_r < 0)
                                    schritt_r *= -1;
                                schritt_g = (g_max - g_min) / 127;
                                if (schritt_g < 0)
                                    schritt_g *= -1;
                                schritt_b = (b_max - b_min) / 127;
                                if (schritt_b < 0)
                                    schritt_b *= -1;
                                for (x = 0; x < 128; ++x) {
                                    r_store = (BYTE)ROUNDOFF(x * schritt_r + r_min);
                                    g_store = (BYTE)ROUNDOFF(x * schritt_g + g_min);
                                    b_store = (BYTE)ROUNDOFF(x * schritt_b + b_min);
                                    m_para->p_note[note].value_color[x] = ColorBuf(r_store, g_store, b_store);
                                    m_para->p_note[note].hfp = (HFloatProperty *)m_para->p_note[note].prop;
                                }
                                m_para->p_note[note].hcp = (HColorProperty *)m_para->p_note[note].prop;
                            }
                            break;
                            default:
   break;
                        }
                        note ++;
                    }
                    break;
                    case 0xA0:
                    {
                        m_para->p_key[key].prop = m_para->obj[i].prop[j].prop;
                        m_para->p_key[key].objt = m_para->obj[i].prop[j].objt;
                        m_para->p_key[key].ispose = m_para->obj[i].prop[j].ispose;
                        m_para->p_key[key].akt_value = 0;
                        m_para->p_key[key].value_beginn = 0;
                        m_para->p_key[key].driven_value = RGB(m_para->obj[i].prop[j].driven_value[0], m_para->obj[i].prop[j].driven_value[1], m_para->obj[i].prop[j].driven_value[2]);
                        switch (m_para->obj[i].prop[j].objt) {
                            case HOT_FLOAT:
                            {
                                if (iscolor) {
                                    if (m_para->obj[i].prop[j].min_value < 0)
                                        m_para->obj[i].prop[j].min_value = 0;
                                    if (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value > 255)
                                        m_para->obj[i].prop[j].max_value = m_para->obj[i].prop[j].min_value + 255;
                                    schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                    for (x = 0; x < 128; ++x) {
                                        m_para->p_key[key].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                    }
                                } else {
                                    schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                    for (x = 0; x < 128; ++x) {
                                        m_para->p_key[key].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                    }
                                }
                                m_para->p_key[key].hfp = (HFloatProperty *)m_para->p_key[key].prop;
                            }
                            break;
                            case HOT_EULERFLOAT:
                            {
                                schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                for (x = 0; x < 128; ++x) {
                                    m_para->p_key[key].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                }
                                m_para->p_key[key].hfp = (HFloatProperty *)m_para->p_key[key].prop;
                            }
                            break;
                            case HOT_PERCENT:
                            {
                                schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                for (x = 0; x < 128; ++x) {
                                    m_para->p_key[key].value[x] = (float)((schritt * x + m_para->obj[i].prop[j].min_value) / 100);
                                }
                                m_para->p_key[key].hfp = (HFloatProperty *)m_para->p_key[key].prop;
                            }
                            break;
                            case HOT_COLOR:
                            {
                                r_min = GetRValue(m_para->obj[i].prop[j].min_value_color);
                                g_min = GetGValue(m_para->obj[i].prop[j].min_value_color);
                                b_min = GetBValue(m_para->obj[i].prop[j].min_value_color);
                                r_max = GetRValue(m_para->obj[i].prop[j].max_value_color);
                                g_max = GetGValue(m_para->obj[i].prop[j].max_value_color);
                                b_max = GetBValue(m_para->obj[i].prop[j].max_value_color);
                                schritt_r = (r_max - r_min) / 127;
                                if (schritt_r < 0)
                                    schritt_r *= -1;
                                schritt_g = (g_max - g_min) / 127;
                                if (schritt_g < 0)
                                    schritt_g *= -1;
                                schritt_b = (b_max - b_min) / 127;
                                if (schritt_b < 0)
                                    schritt_b *= -1;
                                for (x = 0; x < 128; ++x) {
                                    r_store = (BYTE)ROUNDOFF(x * schritt_r + r_min);
                                    g_store = (BYTE)ROUNDOFF(x * schritt_g + g_min);
                                    b_store = (BYTE)ROUNDOFF(x * schritt_b + b_min);
                                    m_para->p_key[key].value_color[x] = ColorBuf(r_store, g_store, b_store);
                                }
                                m_para->p_key[key].hcp = (HColorProperty *)m_para->p_key[key].prop;
                            }
                            break;
                            default:
   break;
                        }
                        key ++;
                    }
                    break;
                    case 0xB0:
                    {
                        m_para->p_control[control].prop = m_para->obj[i].prop[j].prop;
                        m_para->p_control[control].objt = m_para->obj[i].prop[j].objt;
                        m_para->p_control[control].ispose = m_para->obj[i].prop[j].ispose;
                        m_para->p_control[control].akt_value = 0;
                        m_para->p_control[control].value_beginn = 0;
                        m_para->p_control[control].changed = 0;
                        m_para->p_control[control].driven_value = RGB(m_para->obj[i].prop[j].driven_value[0], m_para->obj[i].prop[j].driven_value[1], m_para->obj[i].prop[j].driven_value[2]);
                        switch (m_para->obj[i].prop[j].objt) {
                            case HOT_FLOAT:
                            {
                                if (iscolor) {
                                    if (m_para->obj[i].prop[j].min_value < 0)
                                        m_para->obj[i].prop[j].min_value = 0;
                                    if (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value > 255)
                                        m_para->obj[i].prop[j].max_value = m_para->obj[i].prop[j].min_value + 255;
                                    schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                    for (x = 0; x < 128; ++x) {
                                        m_para->p_control[control].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                    }
                                } else {
                                    schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                    for (x = 0; x < 128; ++x) {
                                        m_para->p_control[control].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                    }
                                }
                                m_para->p_control[control].hfp = (HFloatProperty *)m_para->p_control[control].prop;
                            }
                            break;
                            case HOT_EULERFLOAT:
                            {
                                schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                for (x = 0; x < 128; ++x) {
                                    m_para->p_control[control].value[x] = (float)(schritt * x + m_para->obj[i].prop[j].min_value);
                                }
                                m_para->p_control[control].hfp = (HFloatProperty *)m_para->p_control[control].prop;
                            }
                            break;
                            case HOT_PERCENT:
                            {
                                schritt = (m_para->obj[i].prop[j].max_value - m_para->obj[i].prop[j].min_value) / 127;
                                for (x = 0; x < 128; ++x) {
                                    m_para->p_control[control].value[x] = (float)((schritt * x + m_para->obj[i].prop[j].min_value) / 100);
                                }
                                m_para->p_control[control].hfp = (HFloatProperty *)m_para->p_control[control].prop;
                            }
                            break;
                            case HOT_COLOR:
                            {
                                r_min = GetRValue(m_para->obj[i].prop[j].min_value_color);
                                g_min = GetGValue(m_para->obj[i].prop[j].min_value_color);
                                b_min = GetBValue(m_para->obj[i].prop[j].min_value_color);
                                r_max = GetRValue(m_para->obj[i].prop[j].max_value_color);
                                g_max = GetGValue(m_para->obj[i].prop[j].max_value_color);
                                b_max = GetBValue(m_para->obj[i].prop[j].max_value_color);
                                schritt_r = (r_max - r_min) / 127;
                                if (schritt_r < 0)
                                    schritt_r *= -1;
                                schritt_g = (g_max - g_min) / 127;
                                if (schritt_g < 0)
                                    schritt_g *= -1;
                                schritt_b = (b_max - b_min) / 127;
                                if (schritt_b < 0)
                                    schritt_b *= -1;
                                for (x = 0; x < 128; ++x) {
                                    r_store = (BYTE)ROUNDOFF(x * schritt_r + r_min);
                                    g_store = (BYTE)ROUNDOFF(x * schritt_g + g_min);
                                    b_store = (BYTE)ROUNDOFF(x * schritt_b + b_min);
                                    m_para->p_control[control].value_color[x] = ColorBuf(r_store, g_store, b_store);
                                }
                                m_para->p_control[control].hcp = (HColorProperty *)m_para->p_control[control].prop;
                            }
                            break;
                            default:
   break;
                        }
                        control ++;
                    }
                    break;
                }
            }
        }
    }

    CPluginDialog::OnOK();
}

void Assign::OnCheck1() {
    const CButton *id1 = (CButton *)GetDlgItem(IDC_CHECK1);
    if (id1->GetCheck()) {
        m_para->override = 1;
    } else {
        m_para->override = 0;
    }
}

void Assign::OnButton8() {
    viewassigned as_dlg(m_para);
    as_dlg.DoModal();
}
