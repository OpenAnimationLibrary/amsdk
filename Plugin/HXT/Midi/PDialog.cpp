// PDialog.cpp: Implementierungsdatei
//

// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
#include "StdAfx.h"
#include "Midi.h"
#include "PDialog.h"
#include "NDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

PDialog::PDialog(Parameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_parameters = parameters;
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Text(pDX, IDC_EDIT1, m_parameters->p_min);
    DDV_MinMaxFloat(pDX, m_parameters->p_min, -10000.F, 10000.F);
    DDX_Text(pDX, IDC_EDIT2, m_parameters->p_max);
    DDV_MinMaxFloat(pDX, m_parameters->p_max, -10000.F, 10000.F);
    DDX_Text(pDX, IDC_EDIT3, m_parameters->m_frame_vor);
    DDV_MinMaxInt(pDX, m_parameters->m_frame_vor, 1, 100);
    DDX_Text(pDX, IDC_EDIT4, m_parameters->m_frame_nach);
    DDV_MinMaxInt(pDX, m_parameters->m_frame_nach, 1, 100);
    DDX_Text(pDX, IDC_EDIT5, m_parameters->m_hold_az);
    DDV_MinMaxInt(pDX, m_parameters->m_hold_az, 1, 100);
    DDX_Check(pDX, IDC_CHECK1, m_parameters->add_old);
    DDX_Check(pDX, IDC_CHECK2, m_parameters->bool_prop);
    DDX_Check(pDX, IDC_CHECK3, m_parameters->m_hold);
    DDX_Check(pDX, IDC_CHECK4, m_parameters->m_hold_force);
    DDX_Check(pDX, IDC_CHECK5, m_parameters->cakewalk);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
    //{{AFX_MSG_MAP(PDialog)
    ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnButton1)
    ON_CBN_SELCHANGE(IDC_COMBO2, &PDialog::OnSelchangeCombo2)
    ON_CBN_SELCHANGE(IDC_COMBO3, &PDialog::OnSelchangeCombo3)
    ON_BN_CLICKED(IDC_RADIO1, &PDialog::OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &PDialog::OnRadio2)
    ON_WM_DRAWITEM()
    ON_BN_CLICKED(IDC_BUTTON2, &PDialog::OnButton2)
    ON_CBN_SELCHANGE(IDC_COMBO1, &PDialog::OnSelchangeCombo1)
    ON_BN_CLICKED(IDC_CHECK2, &PDialog::OnCheck2)
    ON_BN_CLICKED(IDC_RADIO4, &PDialog::OnRadio4)
    ON_BN_CLICKED(IDC_RADIO5, &PDialog::OnRadio5)
    ON_BN_CLICKED(IDC_RADIO3, &PDialog::OnRadio3)
    ON_BN_CLICKED(IDC_RADIO6, &PDialog::OnRadio6)
    ON_BN_CLICKED(IDC_BUTTON3, &PDialog::OnButton3)
    ON_BN_CLICKED(IDC_CHECK3, &PDialog::OnCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &PDialog::OnCheck4)
    ON_BN_CLICKED(IDC_CHECK5, &PDialog::OnCheck5)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

void PDialog::OnButton1() {
    CColorDialog cdlg(m_parameters->p_min_f, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        m_parameters->p_min_f = cdlg.GetColor();
        auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
        id1->Invalidate(TRUE);
    }
}

void PDialog::OnButton2() {
    CColorDialog cdlg(m_parameters->p_max_f, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        m_parameters->p_max_f = cdlg.GetColor();
        auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
        id1->Invalidate(TRUE);
    }
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CString temp;
    CButton *id1;
    CWnd *id2;

    Init();
    temp.Format("%s", m_parameters->p_property->GetFullName().Get());
    int i = temp.GetLength() - temp.ReverseFind('|');
    const CString temp1 = temp.Right(i - 1);
    if (m_parameters->p_iscolor) {
        temp = temp1 + " !! minimum value 0 maximum value 255 !!";
    } else {
        temp = temp1;
    }
    switch (m_parameters->reduce) {
        case 0:
            id1 = (CButton *)GetDlgItem(IDC_RADIO3);
            id1->SetCheck(TRUE);
            break;
        case 1:
            id1 = (CButton *)GetDlgItem(IDC_RADIO4);
            id1->SetCheck(TRUE);
            break;
        case 2:
            id1 = (CButton *)GetDlgItem(IDC_RADIO5);
            id1->SetCheck(TRUE);
            break;
    }
    switch (m_parameters->m_control) {
        case 0:
            id1 = (CButton *)GetDlgItem(IDC_RADIO1);
            id1->SetCheck(TRUE);
            id2 = GetDlgItem(IDC_STATIC_in);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_STATIC_out);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT3);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT4);
            id2->ShowWindow(SW_HIDE);
            break;
        case 1:
            id1 = (CButton *)GetDlgItem(IDC_RADIO6);
            id1->SetCheck(TRUE);
            if (m_parameters->p_type != HOT_BOOL) {
                id2 = GetDlgItem(IDC_STATIC_in);
                id2->ShowWindow(SW_SHOW);
                id2 = GetDlgItem(IDC_STATIC_out);
                id2->ShowWindow(SW_SHOW);
                id2 = GetDlgItem(IDC_EDIT3);
                id2->ShowWindow(SW_SHOW);
                id2 = GetDlgItem(IDC_EDIT4);
                id2->ShowWindow(SW_SHOW);
            } else {
                id2 = GetDlgItem(IDC_STATIC_in);
                id2->ShowWindow(SW_HIDE);
                id2 = GetDlgItem(IDC_STATIC_out);
                id2->ShowWindow(SW_HIDE);
                id2 = GetDlgItem(IDC_EDIT3);
                id2->ShowWindow(SW_HIDE);
                id2 = GetDlgItem(IDC_EDIT4);
                id2->ShowWindow(SW_HIDE);
            }
            break;
        case 2:
            id1 = (CButton *)GetDlgItem(IDC_RADIO2);
            id1->SetCheck(TRUE);
            id2 = GetDlgItem(IDC_STATIC_in);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_STATIC_out);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT3);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT4);
            id2->ShowWindow(SW_HIDE);
            break;
    }
    id2 = GetDlgItem(IDC_EDIT5);
    id1 = (CButton *)GetDlgItem(IDC_CHECK4);
    if (m_parameters->m_hold) {
        id2->ShowWindow(SW_SHOW);
        id1->ShowWindow(SW_SHOW);
    } else {
        id2->ShowWindow(SW_HIDE);
        id1->ShowWindow(SW_HIDE);
    }
    id1 = (CButton *)GetDlgItem(IDC_CHECK5);
    if (m_parameters->cakewalk) {
        id1->SetCheck(TRUE);
    } else {
        id1->SetCheck(FALSE);
    }
    SetDlgItemText(IDC_STATIC_Property, temp);
    //	temp.Format("%s %d Frames long",m_parameters->m_name,m_parameters->az_frames);
    temp.Format(" %d Frames long", m_parameters->az_frames);
    temp = m_parameters->m_name + temp;
    SetDlgItemText(IDC_STATIC_midifile, temp);
    switch (m_parameters->p_type) {
        case HOT_BOOL:
            id2 = GetDlgItem(IDC_STATIC_prop_min);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_STATIC_prop_max);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_STATIC_reduce);
            id2->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
            id1->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id1->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT1);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT2);
            id2->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_CHECK1);
            id1->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_RADIO3);
            id1->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_RADIO4);
            id1->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_RADIO5);
            id1->ShowWindow(SW_HIDE);
            m_parameters->p_min = 0;
            m_parameters->p_min = 1;
            break;
        case HOT_PERCENT:SetDlgItemText(IDC_STATIC_prop_min, "%");
            SetDlgItemText(IDC_STATIC_prop_max, "%");
            id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
            id1->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id1->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT1);
            id2->ShowWindow(SW_SHOW);
            id2 = GetDlgItem(IDC_EDIT2);
            id2->ShowWindow(SW_SHOW);
            id1 = (CButton *)GetDlgItem(IDC_CHECK2);
            id1->ShowWindow(SW_HIDE);
            break;
        case HOT_FLOAT:
        case HOT_INTEGER:
        case HOT_EULERFLOAT:SetDlgItemText(IDC_STATIC_prop_min, "");
            SetDlgItemText(IDC_STATIC_prop_max, "");
            id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
            id1->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id1->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT1);
            id2->ShowWindow(SW_SHOW);
            id2 = GetDlgItem(IDC_EDIT2);
            id2->ShowWindow(SW_SHOW);
            id1 = (CButton *)GetDlgItem(IDC_CHECK2);
            id1->ShowWindow(SW_HIDE);
            break;
        case HOT_COLOR:SetDlgItemText(IDC_STATIC_prop_min, "");
            SetDlgItemText(IDC_STATIC_prop_max, "");
            id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
            id1->ShowWindow(SW_SHOW);
            id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id1->ShowWindow(SW_SHOW);
            id2 = GetDlgItem(IDC_EDIT1);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT2);
            id2->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_CHECK1);
            id1->ShowWindow(SW_HIDE);
            id1 = (CButton *)GetDlgItem(IDC_CHECK2);
            id1->ShowWindow(SW_HIDE);
            break;
        default:
   break;
    }
    auto *id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    if (m_parameters->m_aztrack == 0) {
        id3->EnableWindow(false);
        id3->AddString("Complete file");
        id3->SetCurSel(0);
    } else {
        id3->EnableWindow(true);
        id3->AddString("All tracks");
        for (i = 1; i < m_parameters->m_aztrack; ++i) {
            id3->AddString(m_parameters->m_trackname[i]);
        }
        id3->SetCurSel(m_parameters->m_track);
    }
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnSelchangeCombo2() {
    const CComboBox *id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    const int index = id1->GetCurSel();
    m_parameters->m_min = index;
}

void PDialog::OnSelchangeCombo3() {
    const CComboBox *id1 = (CComboBox *)GetDlgItem(IDC_COMBO3);
    const int index = id1->GetCurSel();
    m_parameters->m_max = index;
}

BOOL PDialog::Init() {
    int k;
    const CString Keys[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    const CString Keys1[12] = {"C", "Db", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};
    constexpr float gnote[12] = {8.1757989156F, 8.6619572180F, 9.1770239974F, 9.7227182413F, 10.3008611535F, 10.9133822323F, 11.5623257097F, 12.2498573744F, 12.9782717994F, 13.7500000000F, 14.5676175474F, 15.4338531643F};
    //	midinote = new MidiNote[128];
    int j = 0;
    if (m_parameters->cakewalk) {
        k = 0;
    } else {
        k = -2;
    }
    int k1 = 1;
    for (auto &i: midinote) {
        i.freq = gnote[j] * k1;
        i.note.Format(" %d", k);
        if (m_parameters->cakewalk) {
            i.note = Keys1[j] + i.note;
            //			midinote[i].note.Format("%s %d",Keys1[j],k);
        } else {
            i.note = Keys[j] + i.note;
            //			midinote[i].note.Format("%s %d",Keys[j],k);
        }
        j++;
        if (j == 12) {
            j = 0;
            k++;
            k1 *= 2;
        }
    }
    UpdatePage();
    return TRUE;
}

void PDialog::UpdatePage() const {
    CComboBox *id1;
    CWnd *id2;
    CButton *id3;
    int i;
    CString temp;

    switch (m_parameters->m_control) {
        case 0:
            // Noten
            id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
            id1->ResetContent();
            for (i = 0; i < 128; ++i) {
                id1->AddString(midinote[i].note);
            }
            id1->SetCurSel(m_parameters->m_min);
            id1->ShowWindow(SW_SHOW);
            id1 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id1->ResetContent();
            for (i = 0; i < 128; ++i) {
                id1->AddString(midinote[i].note);
            }
            id1->SetCurSel(m_parameters->m_max);
            id2 = GetDlgItem(IDC_STATIC_in);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_STATIC_out);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT3);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT4);
            id2->ShowWindow(SW_HIDE);
            id3 = (CButton *)GetDlgItem(IDC_RADIO3);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_RADIO4);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_RADIO5);
            id3->EnableWindow(TRUE);
            break;
        case 1:
            //Noten high
            id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
            id1->ResetContent();
            for (i = 0; i < 128; ++i) {
                id1->AddString(midinote[i].note);
            }
            id1->SetCurSel(m_parameters->m_min);
            id1->ShowWindow(SW_HIDE);
            id1 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id1->ResetContent();
            for (i = 0; i < 128; ++i) {
                id1->AddString(midinote[i].note);
            }
            id1->SetCurSel(m_parameters->m_max);
            if (m_parameters->p_type != HOT_BOOL) {
                id2 = GetDlgItem(IDC_STATIC_in);
                id2->ShowWindow(SW_SHOW);
                id2 = GetDlgItem(IDC_STATIC_out);
                id2->ShowWindow(SW_SHOW);
                id2 = GetDlgItem(IDC_EDIT3);
                id2->ShowWindow(SW_SHOW);
                id2 = GetDlgItem(IDC_EDIT4);
                id2->ShowWindow(SW_SHOW);
            } else {
                id2 = GetDlgItem(IDC_STATIC_in);
                id2->ShowWindow(SW_HIDE);
                id2 = GetDlgItem(IDC_STATIC_out);
                id2->ShowWindow(SW_HIDE);
                id2 = GetDlgItem(IDC_EDIT3);
                id2->ShowWindow(SW_HIDE);
                id2 = GetDlgItem(IDC_EDIT4);
                id2->ShowWindow(SW_HIDE);
            }
            id3 = (CButton *)GetDlgItem(IDC_RADIO3);
            id3->SetCheck(TRUE);
            m_parameters->reduce = 0;
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_RADIO4);
            id3->SetCheck(FALSE);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_RADIO5);
            id3->SetCheck(FALSE);
            id3->EnableWindow(FALSE);
            break;
        case 2:
            id1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
            id1->ResetContent();
            for (i = 0; i < 128; ++i) {
                temp.Format("%d", i);
                id1->AddString(temp);
            }
            id1->SetCurSel(m_parameters->m_min);
            id1->ShowWindow(SW_SHOW);
            id1 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id1->ResetContent();
            for (i = 0; i < 128; ++i) {
                temp.Format("%d", i);
                id1->AddString(temp);
            }
            id1->SetCurSel(m_parameters->m_max);
            id2 = GetDlgItem(IDC_STATIC_in);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_STATIC_out);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT3);
            id2->ShowWindow(SW_HIDE);
            id2 = GetDlgItem(IDC_EDIT4);
            id2->ShowWindow(SW_HIDE);
            id3 = (CButton *)GetDlgItem(IDC_RADIO3);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_RADIO4);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_RADIO5);
            id3->EnableWindow(TRUE);
            break;
    }

//    return TRUE;
}

void PDialog::OnDrawItem(const int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) {
    // TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
    if (nIDCtl == IDC_BUTTON1) {
        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        CRect rect = lpDrawItemStruct->rcItem;
        const UINT state = lpDrawItemStruct->itemState;
        if (state & ODS_SELECTED)
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
        else
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

        rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
        pDC->FillSolidRect(rect, m_parameters->p_min_f);
    }
    if (nIDCtl == IDC_BUTTON2) {
        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        CRect rect = lpDrawItemStruct->rcItem;
        const UINT state = lpDrawItemStruct->itemState;
        if (state & ODS_SELECTED)
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
        else
            pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);

        rect.DeflateRect(CSize(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)));
        pDC->FillSolidRect(rect, m_parameters->p_max_f);
    }

    CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void PDialog::OnSelchangeCombo1() {
    const CComboBox *id1 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    const int index = id1->GetCurSel();
    m_parameters->m_track = index;

}

void PDialog::OnOK() {

    UpdateData(true);

    if (m_parameters->m_min == m_parameters->m_max || m_parameters->p_min == m_parameters->p_max || m_parameters->p_min_f == m_parameters->p_max_f) {
        if (m_parameters->m_min == m_parameters->m_max) {
            AfxMessageBox("Notes/Volume are the same",MB_OK | MB_ICONSTOP);
        } else {
            if (m_parameters->p_min == m_parameters->p_max) {
                AfxMessageBox("Values are the same",MB_OK | MB_ICONSTOP);
            } else {
                AfxMessageBox("Color are the same",MB_OK | MB_ICONSTOP);
            }
        }
    } else {
        CPluginDialog::OnOK();
    }
}

void PDialog::OnCheck2() {
    UpdateData(true);
    if (m_parameters->bool_prop) {
        SetDlgItemText(IDC_CHECK2, "on");
    } else {
        SetDlgItemText(IDC_CHECK2, "off");
    }
}

void PDialog::OnRadio3() {
    m_parameters->reduce = 0;
}

void PDialog::OnRadio4() {
    m_parameters->reduce = 1;
}

void PDialog::OnRadio5() {
    m_parameters->reduce = 2;
}

void PDialog::OnRadio1() {
    m_parameters->m_control = 0;
    UpdatePage();
}

void PDialog::OnRadio2() {
    m_parameters->m_control = 2;
    UpdatePage();
}

void PDialog::OnRadio6() {
    m_parameters->m_control = 1;
    UpdatePage();
}

void PDialog::OnButton3() {
    NDialog ndlg(m_parameters);
    ndlg.DoModal();

    // TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

}

void PDialog::OnCheck3() {
    CWnd *id2 = GetDlgItem(IDC_EDIT5);
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK4);
    UpdateData(true);
    if (m_parameters->m_hold) {
        id2->ShowWindow(SW_SHOW);
        id1->ShowWindow(SW_SHOW);
    } else {
        id2->ShowWindow(SW_HIDE);
        id1->ShowWindow(SW_HIDE);
        m_parameters->m_hold_force = 0;
        UpdateData(false);
    }

}

void PDialog::OnCheck4() {
    UpdateData(true);
}

void PDialog::OnCheck5() {
    UpdateData(true);
    Init();
}
