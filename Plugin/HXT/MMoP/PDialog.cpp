// PDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "MMoP.h"
#include "PDialog.h"
#include "SPDialog.h"
#include "APDialog.h"

IMPLEMENT_DYNAMIC(PDialog, CPluginDialog)

PDialog::PDialog(PParameter *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    mp = para;
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, mp->distance);
    DDV_MinMaxFloat(pDX, mp->distance, 0.1F, 1000.F);
    DDX_Text(pDX, IDC_EDIT2, mp->offset.x);
    DDV_MinMaxFloat(pDX, mp->offset.x, -10000.F, 10000.F);
    DDX_Text(pDX, IDC_EDIT3, mp->offset.y);
    DDV_MinMaxFloat(pDX, mp->offset.y, -10000.F, 10000.F);
    DDX_Text(pDX, IDC_EDIT4, mp->offset.z);
    DDV_MinMaxFloat(pDX, mp->offset.z, -10000.F, 10000.F);
    DDX_Check(pDX, IDC_CHECK1, mp->store_rotate);
    DDX_Check(pDX, IDC_CHECK2, mp->allow_overlap);
    DDX_Check(pDX, IDC_CHECK3, mp->align);
    DDX_Check(pDX, IDC_CHECK4, mp->use_offset);
    DDX_Radio(pDX, IDC_RADIO1, mp->random);
    DDX_Text(pDX, IDC_EDIT5, mp->max_az);
    DDV_MinMaxInt(pDX, mp->max_az, 1, 10000);
}

BEGIN_MESSAGE_MAP(PDialog, CPluginDialog)
    ON_LBN_SELCHANGE(IDC_LIST1, &PDialog::OnSelchangeList1)
    ON_EN_UPDATE(IDC_EDIT1, &PDialog::OnUpdateEdit1)
    ON_BN_CLICKED(IDC_RADIO1, &PDialog::OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &PDialog::OnBnClickedRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &PDialog::OnBnClickedRadio3)
    ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &PDialog::OnBnClickedButton2)
END_MESSAGE_MAP()

// PDialog-Meldungshandler
BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;

    HObjectCacheContainer *hocc = mp->hproject->GetChildObjectCacheContainer();
    for (HHashObject *hmc = hocc->GetChildModelCache(); hmc; hmc = hmc->GetSibling()) {
        if (hmc->GetObjectType() == HOT_MODEL) {
            temp.Format("%s", hmc->GetName());
            const int index = id1->AddString(temp);
            id1->SetItemDataPtr(index, hmc);
        }
    }
    id1->SetCurSel(0);
    mp->hmc = (HModelCache *)id1->GetItemDataPtr(id1->GetCurSel());

    temp.Format("Splinelength = %.1f", mp->spline_length);
    SetDlgItemText(IDC_STATIC1, temp);
    UpdateSettings();

    const HUserCategoryProperty *hucp = mp->hmc->GetUserCategoryProperty();
    auto *id2 = (CButton *)GetDlgItem(IDC_BUTTON1);
    if (hucp)
        id2->EnableWindow(true);

    HActionCacheContainer *hacc = mp->hproject->GetChildActionCacheContainer();
    const HActionCache *hac = hacc->GetChildActionCache();
    id2 = (CButton *)GetDlgItem(IDC_BUTTON2);
    if (hac)
        id2->EnableWindow(true);

    //	hac->GetSiblingActionCache();
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnSelchangeList1() {
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    auto *id2 = (CButton *)GetDlgItem(IDC_BUTTON1);
    mp->hmc = (HModelCache *)id1->GetItemDataPtr(id1->GetCurSel());
    const HUserCategoryProperty *hucp = mp->hmc->GetUserCategoryProperty();
    if (hucp) {
        id2->EnableWindow(true);
    } else {
        id2->EnableWindow(false);
        if (mp->azprop != 0) {
            for (int i = 0; i < mp->azprop; ++i)
                mp->props[i] = nullptr;
            mp->azprop = 0;
        }
    }
}

void PDialog::OnUpdateEdit1() {
    CString temp;
    UpdateData(true);
    const int az = FLOOR_INT(mp->spline_length / mp->distance) + 1;
    temp.Format("%i copies to import", az);
    SetDlgItemText(IDC_STATIC2, temp);
}

void PDialog::OnOK() {
    CPluginDialog::OnOK();
}

void PDialog::UpdateSettings() {
    CString temp;
    UpdateData(true);
    auto *id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
    auto *id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
    auto *id3 = (CButton *)GetDlgItem(IDC_CHECK4);
    auto *id4 = (CButton *)GetDlgItem(IDC_CHECK2);
    if (mp->random == 2) {
        SetDlgItemText(IDC_STATIC_OFS, "Area around the path");
        id3->ShowWindow(false);
    } else {
        SetDlgItemText(IDC_STATIC_OFS, "Offset");
        id3->ShowWindow(true);
    }
    if (mp->random == 0) {
        const int az = FLOOR_INT(mp->spline_length / mp->distance) + 1;
        temp.Format("%i copies to import", az);
        SetDlgItemText(IDC_STATIC2, temp);
        SetDlgItemText(IDC_STATIC_DIST, "Distance");
        id2->ShowWindow(false);
        id1->ShowWindow(true);
        id4->EnableWindow(false);
    } else {
        SetDlgItemText(IDC_STATIC2, "");
        SetDlgItemText(IDC_STATIC_DIST, "Population");
        id1->ShowWindow(false);
        id2->ShowWindow(true);
        id4->EnableWindow(true);
    }
}

void PDialog::OnBnClickedRadio1() {
    UpdateSettings();
}

void PDialog::OnBnClickedRadio2() {
    UpdateSettings();
}

void PDialog::OnBnClickedRadio3() {
    UpdateSettings();
}

void PDialog::OnBnClickedButton1() {
    SPDialog spdlg(mp);
    spdlg.DoModal();
}

void PDialog::OnBnClickedButton2() {
    APDialog apdlg(mp);
    apdlg.DoModal();
}
