// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "PIMotion.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

PDialog::PDialog(PParameters *m_para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    para = m_para;
    m_height = para->height;
    m_width = para->width;
    m_start = para->startframe;
    m_end = para->endframe;
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT1, para->height);
    DDV_MinMaxInt(pDX, para->height, 0, 5000);
    DDX_Text(pDX, IDC_EDIT2, para->width);
    DDV_MinMaxInt(pDX, para->width, 0, 5000);
    DDX_Text(pDX, IDC_EDIT3, para->startframe);
    DDV_MinMaxInt(pDX, para->startframe, 0, 100000);
    DDX_Text(pDX, IDC_EDIT4, para->endframe);
    DDV_MinMaxInt(pDX, para->endframe, 0, 10000);
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
    //{{AFX_MSG_MAP(PDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, &PDialog::OnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDC_COMBO2, &PDialog::OnSelchangeCombo2)
    ON_BN_CLICKED(IDC_RADIO1, &PDialog::OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &PDialog::OnRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &PDialog::OnRadio3)
    ON_BN_CLICKED(IDC_RADIO4, &PDialog::OnRadio4)
    ON_CBN_SELCHANGE(IDC_COMBO3, &PDialog::OnSelchangeCombo3)
    ON_CBN_SELCHANGE(IDC_COMBO4, &PDialog::OnSelchangeCombo4)
    ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnButton1)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

BOOL PDialog::GetBoneSibling(HBone *hb, CComboBox *id, int &recurse) {

    CString temp;

    recurse++;
    for (HBone *hb1 = hb->GetChildBone(); hb1; hb1 = hb1->GetSiblingBone()) {
        CString temp1 = "";
        for (int i = 0; i < recurse; ++i) {
            temp1 += "   ";
        }
        String temp2 = hb1->GetName();
        temp.Format("%s%s", temp1.GetBuffer(temp1.GetLength() + 1), temp2.Get());
        const int index = id->AddString(temp);
        id->SetItemDataPtr(index, hb1);
        GetBoneSibling(hb1, id, recurse);
    }
    recurse--;
    return false;
}

BOOL PDialog::GetBoneRecurse(HBone *hb, CComboBox *id) {

    int recurse = 0;
    const CString temp = hb->GetName();
    const int index = id->AddString(temp);
    id->SetItemDataPtr(index, hb);
    GetBoneSibling(hb, id, recurse);

    return false;
}

BOOL PDialog::GetPropRecurseCamera(HProperty *akt_prop) const {
    HProperty *prop;
    Time time;

    for (int i = 0; (prop = akt_prop->GetPropertyAt(i)); ++i) {
        if (!prop)
            return TRUE;
        if (!GetPropRecurseCamera(prop)) {
            String temp = prop->GetFullName();
            if (temp.Find(".Resolution.Width") != -1) {
                para->width = ((HIntProperty *)prop)->GetValue();
            }
            if (temp.Find(".Resolution.Height") != -1) {
                para->height = ((HIntProperty *)prop)->GetValue();
            }
            if (temp.Find(".Range.StartFrame") != -1) {
                time = ((HTimeProperty *)prop)->GetValue();
                para->startframe = time.GetFrame(para->fps);
            }
            if (temp.Find(".Range.EndFrame") != -1) {
                time = ((HTimeProperty *)prop)->GetValue();
                para->endframe = time.GetFrame(para->fps);
            }
        }
    }
    return FALSE;
}

void PDialog::GetPropCamera(HHashObject *obj) const {
    HProperty *prop;

    //properties
    for (int i = 0; (prop = obj->GetPropertyAt(i)); ++i) {
        if (prop) {
            String temp = prop->GetFullName();
            if (temp.Find(".OutputOptions") != -1) {
                GetPropRecurseCamera(prop);
            }
        }
    }

}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    CString temp;
    CButton *id1;
    int index;

    //ListBox Kamera
    auto *id0 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    for (HCamera *camera = para->hchor->GetChildCamera(); camera; camera = camera->GetNextCameraInChor()) {
        temp = camera->GetName();
        index = id0->AddString(temp);
        id0->SetItemDataPtr(index, camera);
    }
    id0->SetCurSel(0);

    //ListBox Tracking Object
    id0 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    for (HHashObject *obj = para->hchor->GetChild(); obj; obj = obj->GetSibling()) {
        if (obj->GetObjectType() != HOT_CAMERA) {
            temp = obj->GetName();
            index = id0->AddString(temp);
            id0->SetItemDataPtr(index, obj);
        }
    }
    id0->SetCurSel(0);

    switch (para->trackpoint) {
        case 0:
            id1 = (CButton *)GetDlgItem(IDC_RADIO1);
            id1->SetCheck(true);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id0->EnableWindow(false);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
            id0->EnableWindow(false);
            break;
        case 1:
            id1 = (CButton *)GetDlgItem(IDC_RADIO2);
            id1->SetCheck(false);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id0->EnableWindow(false);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
            id0->EnableWindow(false);
            break;
        case 2:
            id1 = (CButton *)GetDlgItem(IDC_RADIO3);
            id1->SetCheck(false);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id0->EnableWindow(true);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
            id0->EnableWindow(false);
            break;
        case 3:
            id1 = (CButton *)GetDlgItem(IDC_RADIO4);
            id1->SetCheck(false);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id0->EnableWindow(false);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
            id0->EnableWindow(true);
            break;
    }

    UpdateKamera();
    UpdateObject();
    temp.Format("%s", para->filename.Get());
    SetDlgItemText(IDC_STATIC_SAVE, temp);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnSelchangeCombo1() {
    //Update Kamera
    UpdateKamera();
}

void PDialog::OnSelchangeCombo2() {
    //Update Object	
    UpdateObject();
}

void PDialog::UpdateKamera() {

    const CComboBox *id0 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    const int index = id0->GetCurSel();
    auto *camera = (HCamera *)id0->GetItemDataPtr(index);
    if (camera) {
        GetPropCamera(camera);
        m_height = para->height;
        m_width = para->width;
        m_start = para->startframe;
        m_end = para->endframe;
        para->hcam = camera;
        UpdateData(false);
    }
}

void PDialog::UpdateObject() {
    CButton *id1;
    HGroupContainer *hgc;
    HBoneContainer *hbc;
    HBone *hb;

    auto *id0 = (CComboBox *)GetDlgItem(IDC_COMBO2);
    int index = id0->GetCurSel();
    auto *obj = (HObject *)id0->GetItemDataPtr(index);
    para->htracking = obj;

    id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
    id0->ResetContent();
    id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
    id0->ResetContent();
    if (obj->GetObjectType() == HOT_MODEL) {
        auto *hm = (HModel *)obj;
        para->trackpoint = 0;
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->SetCheck(true);
        id1->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->EnableWindow(true);
        if ((hgc = hm->GetChildGroupContainer())) {
            //Model hat Gruppen
            id1 = (CButton *)GetDlgItem(IDC_RADIO3);
            id1->EnableWindow(true);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id0->EnableWindow(true);
            for (HGroup *hg = hgc->GetChildGroup(); hg; hg = (HGroup *)hg->GetSibling()) {
                CString temp = hg->GetName();
                index = id0->AddString(temp);
                id0->SetItemDataPtr(index, hg);
            }
            id0->SetCurSel(0);
        } else {
            id1 = (CButton *)GetDlgItem(IDC_RADIO3);
            id1->SetCheck(false);
            id1->EnableWindow(false);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
            id0->EnableWindow(false);
        }
        if ((hbc = hm->GetChildBoneContainer())) {
            //Model hat Bones
            id1 = (CButton *)GetDlgItem(IDC_RADIO4);
            id1->EnableWindow(true);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
            id0->EnableWindow(true);
            if ((hb = hbc->GetChildBone()))
                GetBoneRecurse(hb, id0);
            id0->SetCurSel(0);
        } else {
            id1 = (CButton *)GetDlgItem(IDC_RADIO4);
            id1->SetCheck(false);
            id1->EnableWindow(false);
            id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
            id0->EnableWindow(false);
        }
    } else {
        para->trackpoint = 0;
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->SetCheck(true);
        id1->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->SetCheck(false);
        id1->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_RADIO3);
        id1->SetCheck(false);
        id1->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_RADIO4);
        id1->SetCheck(false);
        id1->EnableWindow(false);
        id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
        id0->EnableWindow(false);
        id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
        id0->EnableWindow(false);
    }

}

void PDialog::OnRadio1() {
    para->trackpoint = 0;
}

void PDialog::OnRadio2() {
    para->trackpoint = 1;
}

void PDialog::OnRadio3() {
    para->trackpoint = 2;
}

void PDialog::OnRadio4() {
    para->trackpoint = 3;
}

void PDialog::OnSelchangeCombo3() {
    const CComboBox *id0 = (CComboBox *)GetDlgItem(IDC_COMBO3);
    const int index = id0->GetCurSel();
    para->hgroup = (HGroup *)id0->GetItemDataPtr(index);

}

void PDialog::OnSelchangeCombo4() {
    const CComboBox *id0 = (CComboBox *)GetDlgItem(IDC_COMBO4);
    const int index = id0->GetCurSel();
    para->hbone = (HBone *)id0->GetItemDataPtr(index);
}

void PDialog::OnButton1() {
    CString filters, title;
    const String ext("txt");

    String filename = para->filename;
    title.Format("Export PI motiondata");
    filters.Format("Text File (*.txt)|*.txt|ASCII||");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, filename, ext.Get(), ext.Get())) {
            filename = "PImotion.txt";
        }
    }
    title.Format("%s", filename.Get());
    SetDlgItemText(IDC_STATIC_SAVE, title);
    para->filename = filename;
}

void PDialog::OnOK() {
    CPluginDialog::OnOK();
}
