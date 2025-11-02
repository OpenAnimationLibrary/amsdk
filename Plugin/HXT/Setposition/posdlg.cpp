// pos.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Setposition.h"
#include "posdlg.h"
#include "about1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
posdlg::posdlg(PParameters *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(posdlg)
    m_parameters = parameters;
    //}}AFX_DATA_INIT
}

void posdlg::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(posdlg)
    DDX_Check(pDX, IDC_CHECK1, m_parameters->m_x);
    DDX_Check(pDX, IDC_CHECK2, m_parameters->m_y);
    DDX_Check(pDX, IDC_CHECK3, m_parameters->m_z);
    DDX_Check(pDX, IDC_CHECK4, m_parameters->mirror_x);
    DDX_Check(pDX, IDC_CHECK5, m_parameters->mirror_y);
    DDX_Check(pDX, IDC_CHECK6, m_parameters->mirror_z);
    DDX_Text(pDX, IDC_EDIT1, m_parameters->translate_bone.x);
    DDV_MinMaxFloat(pDX, m_parameters->translate_bone.x, -10000.F, 10000.F);
    DDX_Text(pDX, IDC_EDIT2, m_parameters->translate_bone.y);
    DDV_MinMaxFloat(pDX, m_parameters->translate_bone.y, -10000.F, 10000.F);
    DDX_Text(pDX, IDC_EDIT3, m_parameters->translate_bone.z);
    DDV_MinMaxFloat(pDX, m_parameters->translate_bone.z, -10000.F, 10000.F);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(posdlg, CDialog)
        //{{AFX_MSG_MAP(posdlg)
        ON_BN_CLICKED(IDC_BUTTON1, &posdlg::OnButton1)
        ON_BN_CLICKED(IDC_RADIO1, &posdlg::OnRadio1)
        ON_BN_CLICKED(IDC_RADIO2, &posdlg::OnRadio2)
        ON_BN_CLICKED(IDC_CHECK4, &posdlg::OnCheck4)
        ON_BN_CLICKED(IDC_CHECK5, &posdlg::OnCheck5)
        ON_BN_CLICKED(IDC_CHECK6, &posdlg::OnCheck6)
        ON_BN_CLICKED(IDC_CHECK1, &posdlg::OnCheck1)
        ON_BN_CLICKED(IDC_CHECK2, &posdlg::OnCheck2)
        ON_BN_CLICKED(IDC_CHECK3, &posdlg::OnCheck3)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten posdlg 

BOOL posdlg::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    SetDlgItemText(IDC_EDIT1, "0");
    SetDlgItemText(IDC_EDIT2, "0");
    SetDlgItemText(IDC_EDIT3, "0");
    update_dlg();
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void posdlg::OnButton1()  {
    about dlg(m_hWnd);
    dlg.DoModal();

}

void posdlg::OnRadio1()  {
    m_parameters->cp_group = false;
    update_dlg();
}

void posdlg::OnRadio2()  {
    m_parameters->cp_group = true;
    update_dlg();
}

void posdlg::OnCheck1() {
    UpdateData(true);
    update_dlg();
}

void posdlg::OnCheck2() {
    UpdateData(true);
    update_dlg();
}

void posdlg::OnCheck3() {
    UpdateData(true);
    update_dlg();
}

void posdlg::OnCheck4() {
    UpdateData(true);
    update_dlg();
}

void posdlg::OnCheck5() {
    UpdateData(true);
    update_dlg();
}

void posdlg::OnCheck6() {
    UpdateData(true);
    update_dlg();
}

void posdlg::update_dlg() const {

    CButton *id1;
    CWnd *id;

    if (m_parameters->cp_group) {
        // mirror aktiv
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->SetCheck(false);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->SetCheck(true);
        id1 = (CButton *)GetDlgItem(IDC_CHECK4);
        id1->EnableWindow(true);
        if (m_parameters->mirror_x) {
            id = GetDlgItem(IDC_EDIT1);
            id->EnableWindow(false);
        } else {
            id = GetDlgItem(IDC_EDIT1);
            id->EnableWindow(true);
        }
        id1 = (CButton *)GetDlgItem(IDC_CHECK5);
        id1->EnableWindow(true);
        if (m_parameters->mirror_y) {
            id = GetDlgItem(IDC_EDIT2);
            id->EnableWindow(false);
        } else {
            id = GetDlgItem(IDC_EDIT2);
            id->EnableWindow(true);
        }
        id1 = (CButton *)GetDlgItem(IDC_CHECK6);
        id1->EnableWindow(true);
        if (m_parameters->mirror_z) {
            id = GetDlgItem(IDC_EDIT3);
            id->EnableWindow(false);
        } else {
            id = GetDlgItem(IDC_EDIT3);
            id->EnableWindow(true);
        }
    } else {
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->SetCheck(true);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->SetCheck(false);
        id1 = (CButton *)GetDlgItem(IDC_CHECK4);
        id1->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_CHECK5);
        id1->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_CHECK6);
        id1->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_CHECK1);
        id1->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_CHECK2);
        id1->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_CHECK3);
        id1->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT1);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT2);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT3);
        id->EnableWindow(true);
    }
}
