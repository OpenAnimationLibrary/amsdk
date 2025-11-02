// MDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "CutPlane.h"
#include "MDialog.h"
#include "OFS_Dialog.h"

MDialog::MDialog(CWnd *pParent /*=nullptr*/) : CPluginDialog(IDD, pParent) {}

MDialog::~MDialog() = default;

void MDialog::Cleanup() {
    theApp.Cleanup();
}

void MDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK1, theApp.plane.infinite);
    DDX_Check(pDX, IDC_CHECK2, theApp.plane.addring);
    DDX_Check(pDX, IDC_CHECK3, theApp.plane.break_splines);
    DDX_Check(pDX, IDC_CHECK4, theApp.plane.cut_splines);
}

BEGIN_MESSAGE_MAP(MDialog, CDialog)
        ON_BN_CLICKED(IDC_BUTTON1, &MDialog::OnBnClickedButton1)
        ON_BN_CLICKED(IDC_BUTTON2, &MDialog::OnBnClickedButton2)
        ON_BN_CLICKED(IDC_CHECK2, &MDialog::OnBnClickedCheck2)
        ON_BN_CLICKED(IDC_CHECK3, &MDialog::OnBnClickedCheck3)
        ON_BN_CLICKED(IDC_CHECK4, &MDialog::OnBnClickedCheck4)
        ON_BN_CLICKED(IDC_BUTTON3, &MDialog::OnBnClickedButton3)
END_MESSAGE_MAP()

// MDialog-Meldungshandler
void MDialog::OnOK() {
    CPluginDialog::OnOK();
    Cleanup();
}

void MDialog::OnCancel() {
    CPluginDialog::OnCancel();
    Cleanup();
}

void MDialog::OnBnClickedButton1() {
    UpdateData(true);
    CPluginDialog::OnOK();
    theApp.UpdateCutCPs();
    theApp.ApplyCutCPs();
    //	Cleanup();
}

void MDialog::EnableControls(const bool check) const {
    auto *id = (CButton *)GetDlgItem(IDC_BUTTON1);
    id->EnableWindow(check);
    id = (CButton *)GetDlgItem(IDC_BUTTON2);
    id->EnableWindow(check);
}

BOOL MDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id = (CButton *)GetDlgItem(IDC_BUTTON1);
    id->EnableWindow(false);
    id = (CButton *)GetDlgItem(IDC_BUTTON2);
    id->EnableWindow(false);
    id = (CButton *)GetDlgItem(IDC_BUTTON3);
    id->EnableWindow(false);
    if (theApp.plane.addring) {
        id = (CButton *)GetDlgItem(IDC_CHECK3);
        id->EnableWindow(true);
        id = (CButton *)GetDlgItem(IDC_CHECK4);
        id->EnableWindow(true);
    } else {
        theApp.plane.break_splines = false;
        theApp.plane.cut_splines = false;
        id = (CButton *)GetDlgItem(IDC_CHECK3);
        id->SetCheck(false);
        id->EnableWindow(false);
        id = (CButton *)GetDlgItem(IDC_CHECK4);
        id->SetCheck(false);
        id->EnableWindow(false);
    }
    CString temp;
    temp.Format("Offset %g", theApp.plane.offset);
    SetDlgItemText(IDC_BUTTON3, temp);
    id = (CButton *)GetDlgItem(IDC_BUTTON3);
    if (theApp.plane.cut_splines) {
        id->EnableWindow(true);
    } else {
        id->EnableWindow(false);
    }
    return TRUE;
}

void MDialog::OnBnClickedButton2() {
    UpdateData(true);
    theApp.UpdateCutCPs();
}

void MDialog::OnBnClickedCheck2() {
    CButton *id;
    UpdateData(true);
    if (theApp.plane.addring) {
        id = (CButton *)GetDlgItem(IDC_CHECK3);
        id->EnableWindow(true);
        id = (CButton *)GetDlgItem(IDC_CHECK4);
        id->EnableWindow(true);
    } else {
        theApp.plane.break_splines = false;
        theApp.plane.cut_splines = false;
        id = (CButton *)GetDlgItem(IDC_CHECK3);
        id->SetCheck(false);
        id->EnableWindow(false);
        id = (CButton *)GetDlgItem(IDC_CHECK4);
        id->SetCheck(false);
        id->EnableWindow(false);
        id = (CButton *)GetDlgItem(IDC_BUTTON3);
        id->EnableWindow(false);
    }
}

void MDialog::OnBnClickedCheck3() {
    UpdateData(true);
    auto *id = (CButton *)GetDlgItem(IDC_CHECK4);
    if (theApp.plane.break_splines) {
        theApp.plane.cut_splines = false;
        id->SetCheck(false);
        id = (CButton *)GetDlgItem(IDC_BUTTON3);
        id->EnableWindow(false);
    }
}

void MDialog::OnBnClickedCheck4() {
    UpdateData(true);
    auto *id = (CButton *)GetDlgItem(IDC_CHECK3);
    if (theApp.plane.cut_splines) {
        theApp.plane.break_splines = false;
        id->SetCheck(false);
        id = (CButton *)GetDlgItem(IDC_BUTTON3);
        id->EnableWindow(true);
    } else {
        id = (CButton *)GetDlgItem(IDC_BUTTON3);
        id->EnableWindow(false);
    }
}

void MDialog::OnBnClickedButton3() {
    auto *dlg = new OFS_Dialog();
    dlg->DoModal();
    delete dlg;
    CString temp;
    temp.Format("Offset %g", theApp.plane.offset);
    SetDlgItemText(IDC_BUTTON3, temp);
}
