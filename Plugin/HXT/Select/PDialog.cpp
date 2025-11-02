// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Select.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

CPDialog::CPDialog(Parameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(CPDialog)
    m_para = parameters;
    //}}AFX_DATA_INIT
}

void CPDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPDialog)
    DDX_Text(pDX, IDC_EDIT1, m_para->number);
    DDX_Text(pDX, IDC_EDIT2, m_para->pid1);
    DDX_Text(pDX, IDC_EDIT3, m_para->pid2);
    DDX_Text(pDX, IDC_EDIT4, m_para->pid3);
    DDX_Text(pDX, IDC_EDIT5, m_para->pid4);
    DDX_Text(pDX, IDC_EDIT6, m_para->pid5);
    DDX_Text(pDX, IDC_EDIT7, m_para->tolerance);
    DDV_MinMaxFloat(pDX, m_para->tolerance, 0.0001F, 1.F);
    DDX_Radio(pDX, IDC_RADIO10, m_para->cp_mode);
    DDX_Radio(pDX, IDC_RADIO1, m_para->type);
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPDialog, CDialog)
    //{{AFX_MSG_MAP(CPDialog)
    ON_BN_CLICKED(IDC_RADIO1, &CPDialog::OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &CPDialog::OnRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &CPDialog::OnRadio3)
    ON_BN_CLICKED(IDC_RADIO4, &CPDialog::OnRadio4)
    ON_BN_CLICKED(IDC_RADIO5, &CPDialog::OnRadio5)
    ON_BN_CLICKED(IDC_RADIO6, &CPDialog::OnRadio6)
    ON_BN_CLICKED(IDC_RADIO7, &CPDialog::OnRadio7)
    ON_BN_CLICKED(IDC_RADIO8, &CPDialog::OnRadio8)
    ON_BN_CLICKED(IDC_RADIO9, &CPDialog::OnRadio9)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CPDialog::OnCbnSelchangeCombo1)
    //}}AFX_MSG_MAP
    ON_EN_KILLFOCUS(IDC_EDIT7, &CPDialog::OnEnKillfocusEdit7)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPDialog 
void CPDialog::Init() const {
    CEdit *id1;
    CButton *id2;
    CComboBox *id3;

    switch (m_para->type) {
        case 0:
            //CP
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(TRUE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(FALSE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(TRUE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(TRUE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(TRUE);
            break;
        case 1:
            //Patch
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(TRUE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(TRUE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(TRUE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(TRUE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(TRUE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(FALSE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(FALSE);
            break;
        case 2:
            //3Pointers
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(FALSE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(FALSE);
            break;
        case 3:
            //5PointPatch
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(FALSE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(FALSE);
            break;
        case 4:
            //HookPatches
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(FALSE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(FALSE);
            break;
        case 5:
            //5Point und HookPatches
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(FALSE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(FALSE);
            break;
        case 6:
            //unweighted cps
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(FALSE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(FALSE);
            break;
        case 7:
            //flipped normals
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(FALSE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(FALSE);
            break;
        case 8:
            //viewdepend
            id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id1->EnableWindow(FALSE);
            id1 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id1->EnableWindow(TRUE);
            id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
            id3->EnableWindow(TRUE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO10);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO11);
            id2->EnableWindow(FALSE);
            id2 = (CButton *)GetDlgItem(IDC_RADIO12);
            id2->EnableWindow(FALSE);
            break;
    }
}

BOOL CPDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    id3->AddString("Front");
    id3->AddString("Back");
    id3->AddString("Left");
    id3->AddString("Right");
    id3->AddString("Top");
    id3->AddString("Bottom");
    id3->SetCurSel(m_para->view);

    Init();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CPDialog::OnRadio1() {
    UpdateData(true);
    Init();
}

void CPDialog::OnRadio2() {
    UpdateData(true);
    Init();
}

void CPDialog::OnRadio3() {
    UpdateData(true);
    Init();
}

void CPDialog::OnRadio4() {
    UpdateData(true);
    Init();
}

void CPDialog::OnRadio5() {
    UpdateData(true);
    Init();
}

void CPDialog::OnRadio6() {
    UpdateData(true);
    Init();
}

void CPDialog::OnRadio7() {
    UpdateData(true);
    Init();
}

void CPDialog::OnRadio8() {
    UpdateData(true);
    Init();
}

void CPDialog::OnRadio9() {
    UpdateData(true);
    Init();
}

void CPDialog::OnCbnSelchangeCombo1() {
    const CComboBox *id3 = (CComboBox *)GetDlgItem(IDC_COMBO1);
    m_para->view = id3->GetCurSel();
}

void CPDialog::OnEnKillfocusEdit7() {
    UpdateData(true);
}
