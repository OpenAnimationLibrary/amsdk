// Dialog1.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "RenderPasses.h"
#include "Dialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
Dialog1::Dialog1(PARAMETER *para) : CDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(Dialog1)
    m_para = para;
    //}}AFX_DATA_INIT
}

void Dialog1::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Dialog1)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Dialog1, CDialog)
        //{{AFX_MSG_MAP(Dialog1)
        ON_BN_CLICKED(IDC_RADIO1, &Dialog1::OnRadio1)
        ON_BN_CLICKED(IDC_RADIO2, &Dialog1::OnRadio2)
        ON_BN_CLICKED(IDC_RADIO3, &Dialog1::OnRadio3)
        ON_BN_CLICKED(IDC_RADIO4, &Dialog1::OnRadio4)
        ON_BN_CLICKED(IDC_RADIO5, &Dialog1::OnRadio5)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Dialog1 

void Dialog1::OnOK() {
    m_para->pass = option;
    CDialog::OnOK();
}

void Dialog1::OnCancel() {
    m_para->pass = -1;
    CDialog::OnCancel();
}

void Dialog1::OnRadio1() {
    option = 0;
}

void Dialog1::OnRadio2() {
    option = 1;
}

void Dialog1::OnRadio3() {
    option = 2;
}

void Dialog1::OnRadio4() {
    option = 3;
}

void Dialog1::OnRadio5() {
    option = 4;
}

BOOL Dialog1::OnInitDialog() {
    CDialog::OnInitDialog();

    auto *id1 = (CButton *)GetDlgItem(IDC_RADIO1);
    id1->SetCheck(TRUE);
    option = 0;

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
