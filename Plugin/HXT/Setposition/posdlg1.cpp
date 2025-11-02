// posdlg1.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Setposition.h"
#include "posdlg1.h"
#include "about1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
posdlg1::posdlg1(PParameters *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(posdlg1)
    m_parameters = parameters;
    // HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
    //}}AFX_DATA_INIT
}

void posdlg1::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(posdlg1)
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT1, m_parameters->translate_bone.x);
    DDV_MinMaxUnit(pDX, m_parameters->translate_bone.x, -1000000., 1000000.);
    DDX_Text(pDX, IDC_EDIT2, m_parameters->translate_bone.y);
    DDV_MinMaxUnit(pDX, m_parameters->translate_bone.y, -1000000., 1000000.);
    DDX_Text(pDX, IDC_EDIT3, m_parameters->translate_bone.z);
    DDV_MinMaxUnit(pDX, m_parameters->translate_bone.z, -1000000., 1000000.);
    DDX_Text(pDX, IDC_EDIT4, m_parameters->rotate_bone.x);
    DDV_MinMaxFloat(pDX, m_parameters->rotate_bone.x, -359.999F, 359.999F);
    DDX_Text(pDX, IDC_EDIT5, m_parameters->rotate_bone.y);
    DDV_MinMaxFloat(pDX, m_parameters->rotate_bone.y, -359.999F, 359.999F);
    DDX_Text(pDX, IDC_EDIT6, m_parameters->rotate_bone.z);
    DDV_MinMaxFloat(pDX, m_parameters->rotate_bone.z, -359.999F, 359.999F);
    DDX_Check(pDX, IDC_CHECK1, m_parameters->translate);
    DDX_Check(pDX, IDC_CHECK2, m_parameters->rotate);
}

BEGIN_MESSAGE_MAP(posdlg1, CDialog)
        //{{AFX_MSG_MAP(posdlg1)
        ON_BN_CLICKED(IDC_BUTTON1, &posdlg1::OnButton1)
        ON_BN_CLICKED(IDC_CHECK1, &posdlg1::OnCheck1)
        ON_BN_CLICKED(IDC_CHECK2, &posdlg1::OnCheck2)
        ON_BN_CLICKED(IDC_RADIO1, &posdlg1::OnRadio1)
        ON_BN_CLICKED(IDC_RADIO2, &posdlg1::OnRadio2)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten posdlg1 

void posdlg1::OnButton1()  {
    about dlg(m_hWnd);
    dlg.DoModal();
}

void posdlg1::OnCheck1() {
    CWnd *id;
    CButton *id1;
    UpdateData(true);
    if (m_parameters->translate) {
        id = GetDlgItem(IDC_EDIT1);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT2);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT3);
        id->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->EnableWindow(true);
    } else {
        id = GetDlgItem(IDC_EDIT1);
        id->EnableWindow(false);
        id = GetDlgItem(IDC_EDIT2);
        id->EnableWindow(false);
        id = GetDlgItem(IDC_EDIT3);
        id->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->EnableWindow(false);
    }
}

void posdlg1::OnCheck2() {
    CWnd *id;
    UpdateData(true);
    if (m_parameters->rotate) {
        id = GetDlgItem(IDC_EDIT4);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT5);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT6);
        id->EnableWindow(true);
    } else {
        id = GetDlgItem(IDC_EDIT4);
        id->EnableWindow(false);
        id = GetDlgItem(IDC_EDIT5);
        id->EnableWindow(false);
        id = GetDlgItem(IDC_EDIT6);
        id->EnableWindow(false);
    }
}

BOOL posdlg1::OnInitDialog() {
    CWnd *id;
    CButton *id1;
    CPluginDialog::OnInitDialog();

    if (m_parameters->rotate) {
        id = GetDlgItem(IDC_EDIT4);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT5);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT6);
        id->EnableWindow(true);
    } else {
        id = GetDlgItem(IDC_EDIT4);
        id->EnableWindow(false);
        id = GetDlgItem(IDC_EDIT5);
        id->EnableWindow(false);
        id = GetDlgItem(IDC_EDIT6);
        id->EnableWindow(false);
    }
    if (m_parameters->translate) {
        id = GetDlgItem(IDC_EDIT1);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT2);
        id->EnableWindow(true);
        id = GetDlgItem(IDC_EDIT3);
        id->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->EnableWindow(true);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->EnableWindow(true);
    } else {
        id = GetDlgItem(IDC_EDIT1);
        id->EnableWindow(false);
        id = GetDlgItem(IDC_EDIT2);
        id->EnableWindow(false);
        id = GetDlgItem(IDC_EDIT3);
        id->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->EnableWindow(false);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->EnableWindow(false);
    }
    if (m_parameters->modus) {
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->SetCheck(true);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->SetCheck(false);
    } else {
        id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        id1->SetCheck(false);
        id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        id1->SetCheck(true);
    }
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void posdlg1::OnOK() {
    CPluginDialog::OnOK();
    UpdateData(true);
}

void posdlg1::OnRadio1()  {
    const CButton *id1 = (CButton *)GetDlgItem(IDC_RADIO1);
    if (id1->GetCheck())
        m_parameters->modus = true;
}

void posdlg1::OnRadio2()  {
    const CButton *id1 = (CButton *)GetDlgItem(IDC_RADIO2);
    if (id1->GetCheck())
        m_parameters->modus = false;
}
