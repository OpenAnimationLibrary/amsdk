// PDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "Push.h"
#include "PDialog.h"

#include "resource.h"

PDialog::PDialog(PARAMETER *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    mp = para;
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Text(pDX, IDC_EDIT1, mp->distance[0]);
    DDV_MinMaxFloat(pDX, mp->distance[0], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT2, mp->frame[0]);
    DDV_MinMaxInt(pDX, mp->frame[0], 0, 10000);
    DDX_Check(pDX, IDC_CHECK1, mp->keyframe[0]);

    DDX_Text(pDX, IDC_EDIT3, mp->distance[1]);
    DDV_MinMaxFloat(pDX, mp->distance[1], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT4, mp->frame[1]);
    DDV_MinMaxInt(pDX, mp->frame[1], 0, 10000);
    DDX_Check(pDX, IDC_CHECK2, mp->keyframe[1]);

    DDX_Text(pDX, IDC_EDIT5, mp->distance[2]);
    DDV_MinMaxFloat(pDX, mp->distance[2], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT6, mp->frame[2]);
    DDV_MinMaxInt(pDX, mp->frame[2], 0, 10000);
    DDX_Check(pDX, IDC_CHECK3, mp->keyframe[2]);

    DDX_Text(pDX, IDC_EDIT7, mp->distance[3]);
    DDV_MinMaxFloat(pDX, mp->distance[3], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT8, mp->frame[3]);
    DDV_MinMaxInt(pDX, mp->frame[3], 0, 10000);
    DDX_Check(pDX, IDC_CHECK4, mp->keyframe[3]);

    DDX_Text(pDX, IDC_EDIT9, mp->distance[4]);
    DDV_MinMaxFloat(pDX, mp->distance[4], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT10, mp->frame[4]);
    DDV_MinMaxInt(pDX, mp->frame[4], 0, 10000);
    DDX_Check(pDX, IDC_CHECK5, mp->keyframe[4]);

    DDX_Text(pDX, IDC_EDIT11, mp->distance[5]);
    DDV_MinMaxFloat(pDX, mp->distance[5], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT12, mp->frame[5]);
    DDV_MinMaxInt(pDX, mp->frame[5], 0, 10000);
    DDX_Check(pDX, IDC_CHECK6, mp->keyframe[5]);

    DDX_Text(pDX, IDC_EDIT13, mp->distance[6]);
    DDV_MinMaxFloat(pDX, mp->distance[6], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT14, mp->frame[6]);
    DDV_MinMaxInt(pDX, mp->frame[6], 0, 10000);
    DDX_Check(pDX, IDC_CHECK7, mp->keyframe[6]);

    DDX_Text(pDX, IDC_EDIT15, mp->distance[7]);
    DDV_MinMaxFloat(pDX, mp->distance[7], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT16, mp->frame[7]);
    DDV_MinMaxInt(pDX, mp->frame[7], 0, 10000);
    DDX_Check(pDX, IDC_CHECK8, mp->keyframe[7]);

    DDX_Text(pDX, IDC_EDIT17, mp->distance[8]);
    DDV_MinMaxFloat(pDX, mp->distance[8], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT18, mp->frame[8]);
    DDV_MinMaxInt(pDX, mp->frame[8], 0, 10000);
    DDX_Check(pDX, IDC_CHECK9, mp->keyframe[8]);

    DDX_Text(pDX, IDC_EDIT19, mp->distance[9]);
    DDV_MinMaxFloat(pDX, mp->distance[9], -10000, 10000);
    DDX_Text(pDX, IDC_EDIT20, mp->frame[9]);
    DDV_MinMaxInt(pDX, mp->frame[9], 0, 10000);
    DDX_Check(pDX, IDC_CHECK10, mp->keyframe[9]);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)ON_BN_CLICKED(IDC_RADIO1, &PDialog::OnBnClickedRadio1) ON_BN_CLICKED(IDC_RADIO2, &PDialog::OnBnClickedRadio2) ON_BN_CLICKED(IDC_RADIO3, &PDialog::OnBnClickedRadio3) ON_BN_CLICKED(IDC_RADIO4, &PDialog::OnBnClickedRadio4)END_MESSAGE_MAP()

void PDialog::UpdateControls() {
    CWnd *id0;
    CButton *id1;
    switch (mp->makekeys) {
        case 0:
            id0 = GetDlgItem(IDC_EDIT1);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT2);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT3);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT4);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT5);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT6);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT7);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT8);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT9);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT10);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT11);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT12);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT13);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT14);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT15);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT16);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT17);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT18);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT19);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT20);
            id0->ShowWindow(false);
            SetDlgItemText(IDC_STATIC5, "frame");
            id0 = GetDlgItem(IDC_STATIC5);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_STATIC6);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_STATIC7);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_STATIC8);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_STATIC9);
            id0->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK1);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK2);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK3);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK4);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK5);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK6);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK7);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK8);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK9);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK10);
            id1->ShowWindow(false);
            break;
        case 1:
            id0 = GetDlgItem(IDC_EDIT1);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT2);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT3);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT4);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT5);
            if (mp->pose0)
                id0->ShowWindow(true);
            else
                id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT6);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT7);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT8);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT9);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT10);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT11);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT12);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT13);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT14);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT15);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT16);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT17);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT18);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT19);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_EDIT20);
            id0->ShowWindow(false);
            SetDlgItemText(IDC_STATIC5, "at");
            id0 = GetDlgItem(IDC_STATIC5);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_STATIC6);
            id0->ShowWindow(false);
            if (mp->pose0) {
                SetDlgItemText(IDC_STATIC7, "-100%");
                id0 = GetDlgItem(IDC_STATIC7);
                id0->ShowWindow(true);
                SetDlgItemText(IDC_STATIC8, "0%");
                id0 = GetDlgItem(IDC_STATIC8);
                id0->ShowWindow(true);
                SetDlgItemText(IDC_STATIC9, "100%");
                id0 = GetDlgItem(IDC_STATIC9);
                id0->ShowWindow(true);
            } else {
                SetDlgItemText(IDC_STATIC7, "0%");
                id0 = GetDlgItem(IDC_STATIC7);
                id0->ShowWindow(true);
                SetDlgItemText(IDC_STATIC8, "100%");
                id0 = GetDlgItem(IDC_STATIC8);
                id0->ShowWindow(true);
                id0 = GetDlgItem(IDC_STATIC9);
                id0->ShowWindow(false);
            }
            id1 = (CButton *)GetDlgItem(IDC_CHECK1);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK2);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK3);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK4);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK5);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK6);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK7);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK8);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK9);
            id1->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK10);
            id1->ShowWindow(false);
            break;
        case 2:
            id0 = GetDlgItem(IDC_EDIT1);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT2);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT3);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT4);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT5);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT6);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT7);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT8);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT9);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT10);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT11);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT12);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT13);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT14);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT15);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT16);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT17);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT18);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT19);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_EDIT20);
            id0->ShowWindow(true);
            SetDlgItemText(IDC_STATIC5, "frame");
            id0 = GetDlgItem(IDC_STATIC5);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_STATIC6);
            id0->ShowWindow(true);
            id0 = GetDlgItem(IDC_STATIC7);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_STATIC8);
            id0->ShowWindow(false);
            id0 = GetDlgItem(IDC_STATIC9);
            id0->ShowWindow(false);
            id1 = (CButton *)GetDlgItem(IDC_CHECK1);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK2);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK3);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK4);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK5);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK6);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK7);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK8);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK9);
            id1->ShowWindow(true);
            id1 = (CButton *)GetDlgItem(IDC_CHECK10);
            id1->ShowWindow(true);
            break;
    }
}

// PDialog-Meldungshandler

void PDialog::OnBnClickedRadio1() {
    mp->makekeys = 0;
    UpdateControls();
}

void PDialog::OnBnClickedRadio2() {
    mp->makekeys = 1;
    mp->pose0 = FALSE;
    UpdateControls();
}

void PDialog::OnBnClickedRadio3() {
    mp->makekeys = 2;
    UpdateControls();
}

void PDialog::OnBnClickedRadio4() {
    mp->makekeys = 1;
    mp->pose0 = TRUE;
    UpdateControls();
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CButton *id1 = nullptr;
    switch (mp->makekeys) {
        case 0:
            id1 = (CButton *)GetDlgItem(IDC_RADIO1);
            break;
        case 1:
            if (mp->pose0)
                id1 = (CButton *)GetDlgItem(IDC_RADIO2);
            else
                id1 = (CButton *)GetDlgItem(IDC_RADIO4);
            break;
        case 2:
            id1 = (CButton *)GetDlgItem(IDC_RADIO3);
            break;
    }
    id1->SetCheck(TRUE);
    UpdateControls();
    return TRUE;
}

void PDialog::OnOK() {

    UpdateData(true);
    BOOL isallok = TRUE;
    switch (mp->makekeys) {
        case 0:
            break;
        case 1:
            if (mp->pose0) {
                if (mp->distance[0] == mp->distance[1] && mp->distance[0] == mp->distance[2]) {
                    isallok = FALSE;
                }
            } else {
                if (mp->distance[0] == mp->distance[1]) {
                    isallok = FALSE;
                }
            }
            break;
        case 2:
        {
            int azkeys = 0;
            for (const int i: mp->keyframe) {
                if (i)
                    azkeys ++;
            }
            if (azkeys == 0)
                isallok = FALSE;
        }
        break;
    }

    if (!isallok) {
        AfxMessageBox("There is a logical error in Your input data !", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    CPluginDialog::OnOK();
}
