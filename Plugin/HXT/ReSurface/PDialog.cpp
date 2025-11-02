// PDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "ReSurface.h"
#include "PDialog.h"

PDialog::PDialog(PARAMETER *m_para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    para = m_para;
    //}}AFX_DATA_INIT
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, para->distance);
    DDV_MinMaxFloat(pDX, para->distance, -1e6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT2, para->maxdistance);
    DDV_MinMaxFloat(pDX, para->maxdistance, 1e-6F, 1e6F);
    DDX_Check(pDX, IDC_CHECK1, para->reversenormal);
    DDX_Check(pDX, IDC_CHECK2, para->instancing);
    DDX_Check(pDX, IDC_CHECK3, para->usegroupcenter);
    DDX_Check(pDX, IDC_CHECK4, para->ignore_x);
    DDX_Check(pDX, IDC_CHECK5, para->ignore_y);
    DDX_Check(pDX, IDC_CHECK6, para->ignore_z);
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
END_MESSAGE_MAP()

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CButton *id;
    if (para->isinchor) {
        id = (CButton *)GetDlgItem(IDC_CHECK2);
        id->ShowWindow(true);
        id = (CButton *)GetDlgItem(IDC_CHECK3);
        id->ShowWindow(false);
        id = (CButton *)GetDlgItem(IDC_CHECK4);
        id->EnableWindow(false);
        para->ignore_x = false;
        id->SetCheck(false);
        id = (CButton *)GetDlgItem(IDC_CHECK5);
        id->EnableWindow(false);
        para->ignore_y = false;
        id->SetCheck(false);
        id = (CButton *)GetDlgItem(IDC_CHECK6);
        id->EnableWindow(false);
        para->ignore_z = false;
        id->SetCheck(false);
    } else {
        id = (CButton *)GetDlgItem(IDC_CHECK2);
        id->ShowWindow(false);
        id = (CButton *)GetDlgItem(IDC_CHECK3);
        id->ShowWindow(true);
        id = (CButton *)GetDlgItem(IDC_CHECK4);
        id->EnableWindow(true);
        id = (CButton *)GetDlgItem(IDC_CHECK5);
        id->EnableWindow(true);
        id = (CButton *)GetDlgItem(IDC_CHECK6);
        id->EnableWindow(true);
    }
    return TRUE;
}

// PDialog-Meldungshandler
