// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Smooth.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
PDialog::PDialog(PARAMETER *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_para = parameters;
    m_cp = 4;
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Text(pDX, IDC_EDIT1, m_cp);
    DDV_MinMaxInt(pDX, m_cp, 4, 10000);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
    //{{AFX_MSG_MAP(PDialog)
    ON_BN_CLICKED(IDC_CHECK1, &PDialog::OnCheck1)
    ON_BN_CLICKED(IDC_CHECK2, &PDialog::OnCheck2)
    ON_BN_CLICKED(IDC_CHECK3, &PDialog::OnCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &PDialog::OnCheck4)
    ON_BN_CLICKED(IDC_RADIO1, &PDialog::OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &PDialog::OnRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &PDialog::OnRadio3)
    ON_BN_CLICKED(IDC_CHECK5, &PDialog::OnCheck5)
    ON_BN_CLICKED(IDC_CHECK6, &PDialog::OnCheck6)
    ON_BN_CLICKED(IDC_CHECK7, &PDialog::OnCheck7)
    ON_BN_CLICKED(IDC_RADIO4, &PDialog::OnRadio4)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

void PDialog::OnCheck1() {
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK1);
    if (id1->GetCheck() == 1) {
        if (m_para->lock_y && m_para->lock_z) {
            AfxMessageBox("Only 2 axis can be locked !", MB_OK | MB_ICONSTOP);
            id1->SetCheck(FALSE);
        } else {
            m_para->lock_x = TRUE;
        }
    } else {
        m_para->lock_x = FALSE;
    }
}

void PDialog::OnCheck2() {
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK2);
    if (id1->GetCheck() == 1) {
        if (m_para->lock_x && m_para->lock_z) {
            AfxMessageBox("Only 2 axis can be locked !", MB_OK | MB_ICONSTOP);
            id1->SetCheck(FALSE);
        } else {
            m_para->lock_y = TRUE;
        }
    } else {
        m_para->lock_y = FALSE;
    }

}

void PDialog::OnCheck3() {
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK3);
    if (id1->GetCheck() == 1) {
        if (m_para->lock_x && m_para->lock_y) {
            AfxMessageBox("Only 2 axis can be locked !", MB_OK | MB_ICONSTOP);
            id1->SetCheck(FALSE);
        } else {
            m_para->lock_z = TRUE;
        }
    } else {
        m_para->lock_z = FALSE;
    }

}

void PDialog::OnCheck4() {
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK4);
    if (id1->GetCheck() == 1) {
        m_para->complet = true;
        if (m_para->azspline > 1) {
            id1 = (CButton *)GetDlgItem(IDC_CHECK7);
            id1->EnableWindow(FALSE);
            id1->SetCheck(FALSE);
            auto *id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(FALSE);
        }
    } else {
        m_para->complet = false;
        id1 = (CButton *)GetDlgItem(IDC_CHECK7);
        id1->EnableWindow(TRUE);
    }
}

void PDialog::OnRadio1() {
    m_para->recurse = 1;
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK5);
    id1->EnableWindow(true);
}

void PDialog::OnRadio2() {
    m_para->recurse = 2;
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK5);
    id1->SetCheck(false);
    id1->EnableWindow(false);
    m_para->half = false;
}

void PDialog::OnRadio3() {
    m_para->recurse = 4;
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK5);
    id1->SetCheck(false);
    id1->EnableWindow(false);
    m_para->half = false;
}

void PDialog::OnRadio4() {
    m_para->recurse = 8;
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK5);
    id1->SetCheck(false);
    id1->EnableWindow(false);
    m_para->half = false;
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    CEdit *id2;
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK4);
    if (m_para->complet) {
        id1->SetCheck(TRUE);
        id1->EnableWindow(FALSE);
    }
    id1 = (CButton *)GetDlgItem(IDC_RADIO1);
    id1->SetCheck(TRUE);
    id1 = (CButton *)GetDlgItem(IDC_CHECK1);
    id1->SetCheck(m_para->lock_x);
    id1 = (CButton *)GetDlgItem(IDC_CHECK2);
    id1->SetCheck(m_para->lock_y);
    id1 = (CButton *)GetDlgItem(IDC_CHECK3);
    id1->SetCheck(m_para->lock_z);
    m_cp = m_para->min_cp;
    if (m_para->azspline > 1) {
        id1 = (CButton *)GetDlgItem(IDC_CHECK6);
        id1->EnableWindow(TRUE);
        id1 = (CButton *)GetDlgItem(IDC_CHECK7);
        id1->EnableWindow(TRUE);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id2->EnableWindow(FALSE);
    } else {
        id1 = (CButton *)GetDlgItem(IDC_CHECK6);
        id1->EnableWindow(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_CHECK7);
        id1->EnableWindow(FALSE);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id2->EnableWindow(FALSE);
    }
    UpdateData(false);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnCheck5() {
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK5);
    if (id1->GetCheck() == 1) {
        m_para->half = true;
        m_para->recurse = 1;
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->SetCheck(TRUE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->EnableWindow(FALSE);
        id1->SetCheck(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO3);
        id1->EnableWindow(FALSE);
        id1->SetCheck(FALSE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO4);
        id1->EnableWindow(FALSE);
        id1->SetCheck(FALSE);
    } else {
        m_para->half = false;
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->EnableWindow(TRUE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO3);
        id1->EnableWindow(TRUE);
        id1 = (CButton *)GetDlgItem(IDC_RADIO4);
        id1->EnableWindow(TRUE);
    }
}

void PDialog::OnCheck6() {
    CEdit *id2;
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK6);
    if (id1->GetCheck() == 1) {
        id1 = (CButton *)GetDlgItem(IDC_CHECK7);
        id1->EnableWindow(FALSE);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id2->EnableWindow(FALSE);
        m_para->allsplines = 1;
    } else {
        if (!m_para->complet) {
            id1 = (CButton *)GetDlgItem(IDC_CHECK7);
            id1->EnableWindow(TRUE);
        }
        id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id2->EnableWindow(FALSE);
        m_para->allsplines = 0;
    }
}

void PDialog::OnCheck7() {
    CEdit *id2;
    auto *id1 = (CButton *)GetDlgItem(IDC_CHECK7);
    if (id1->GetCheck() == 1) {
        id1 = (CButton *)GetDlgItem(IDC_CHECK6);
        id1->EnableWindow(FALSE);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id2->EnableWindow(TRUE);
        m_para->allsplines = 2;
    } else {
        id1 = (CButton *)GetDlgItem(IDC_CHECK6);
        id1->EnableWindow(TRUE);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
        id2->EnableWindow(FALSE);
        m_para->allsplines = 0;
    }
}

void PDialog::OnOK() {
    UpdateData(true);
    m_para->min_cp = m_cp;
    CPluginDialog::OnOK();
}
