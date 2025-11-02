// PDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "MirrorBone.h"
#include "PDialog.h"

PDialog::PDialog(Parameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_para = parameters;
    //}}AFX_DATA_INIT
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK1, m_para->excludestartbone);
    DDX_Text(pDX, IDC_EDIT1, m_para->removestring);
    DDX_Text(pDX, IDC_EDIT2, m_para->addstring);
    DDX_Check(pDX, IDC_CHECK2, m_para->use_tolerance_cps);
    DDX_Text(pDX, IDC_EDIT3, m_para->tolerance_cps);
    DDV_MinMaxFloat(pDX, m_para->tolerance_cps, 0.F, 100.F);
    DDX_Check(pDX, IDC_CHECK3, m_para->use_tolerance_bones);
    DDX_Text(pDX, IDC_EDIT4, m_para->tolerance_bones);
    DDV_MinMaxFloat(pDX, m_para->tolerance_bones, 0.F, 100.F);
    DDX_Text(pDX, IDC_EDIT5, m_para->tolerance_midbone);
    DDV_MinMaxFloat(pDX, m_para->tolerance_midbone, 0.F, 100.F);
    DDX_Check(pDX, IDC_CHECK4, m_para->groupunassigned);
    DDX_Check(pDX, IDC_CHECK5, m_para->correct_pos_mirrorbone);
    DDX_Check(pDX, IDC_CHECK6, m_para->name_only);
    DDX_Check(pDX, IDC_CHECK7, m_para->groupnotmirrors);
    DDX_Check(pDX, IDC_CHECK8, m_para->write_log);
    DDX_Check(pDX, IDC_CHECK9, m_para->weight_unweighted);
    DDX_Check(pDX, IDC_CHECK10, m_para->clear_target);
    DDX_Check(pDX, IDC_CHECK11, m_para->extended_log);
    DDX_Check(pDX, IDC_CHECK12, m_para->casesensitive);
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        ON_BN_CLICKED(IDC_CHECK2, &PDialog::OnBnClickedCheck2)
        ON_BN_CLICKED(IDC_CHECK3, &PDialog::OnBnClickedCheck3)
        ON_BN_CLICKED(IDC_CHECK6, &PDialog::OnBnClickedCheck6)
        ON_BN_CLICKED(IDC_RADIO1, &PDialog::OnRadio1)
        ON_BN_CLICKED(IDC_RADIO2, &PDialog::OnRadio2)
        ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnBnClickedButton1)
END_MESSAGE_MAP()

void PDialog::SetViewing() const {
    CEdit *id1;
    CButton *id2;
    if (m_para->start_from_group) {
        id2 = (CButton *)GetDlgItem(IDC_CHECK10);
        id2->EnableWindow(false);
    }
    if (m_para->name_only) {
        id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
        id1->EnableWindow(FALSE);
        m_para->use_tolerance_bones = false;
        id2 = (CButton *)GetDlgItem(IDC_CHECK3);
        id2->SetCheck(FALSE);
        id2->EnableWindow(FALSE);
    } else {
        id2 = (CButton *)GetDlgItem(IDC_CHECK3);
        id2->EnableWindow(TRUE);
    }
    if (m_para->use_tolerance_cps) {
        id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
        id1->EnableWindow(TRUE);
    } else {
        id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
        id1->EnableWindow(FALSE);
    }
    if (m_para->use_tolerance_bones) {
        id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
        id1->EnableWindow(TRUE);
    } else {
        id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
        id1->EnableWindow(FALSE);
    }
    if (m_para->sourceside) {
        id2 = (CButton *)GetDlgItem(IDC_RADIO1);
        id2->SetCheck(BST_CHECKED);
    } else {
        id2 = (CButton *)GetDlgItem(IDC_RADIO2);
        id2->SetCheck(BST_CHECKED);
    }
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    SetViewing();
    GetDlgItem(IDC_STATIC_DIR)->SetWindowText(m_para->path.Get());
    return TRUE;
}

void PDialog::OnBnClickedCheck2() {
    UpdateData(true);
    SetViewing();
}

void PDialog::OnBnClickedCheck3() {
    UpdateData(true);
    SetViewing();
}

void PDialog::OnBnClickedCheck6() {
    UpdateData(true);
    SetViewing();
}

void PDialog::OnRadio1() {
    UpdateData(true);
    const CButton *id2 = (CButton *)GetDlgItem(IDC_RADIO1);
    if (id2->GetCheck()) {
        m_para->sourceside = true;
    } else {
        m_para->sourceside = false;
    }
}

void PDialog::OnRadio2() {
    UpdateData(true);
    const CButton *id2 = (CButton *)GetDlgItem(IDC_RADIO2);
    if (id2->GetCheck()) {
        m_para->sourceside = false;
    } else {
        m_para->sourceside = true;
    }
}

void PDialog::OnBnClickedButton1() {
    const CString caption = "Change hash_math::logile directory";
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!DirRequest(m_para->path, caption/*nullptr*/, m_para->path.Get(), this))
            return;
    }
    GetDlgItem(IDC_STATIC_DIR)->SetWindowText(m_para->path.Get());
}
