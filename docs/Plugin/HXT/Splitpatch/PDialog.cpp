// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Splitpatch.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
PDialog::PDialog(Parameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_parameters = parameters;
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPDialog)
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        //{{AFX_MSG_MAP(PDialog)
        ON_BN_CLICKED(IDC_RADIO1, &PDialog::OnRadio1)
        ON_BN_CLICKED(IDC_RADIO2, &PDialog::OnRadio2)
        ON_BN_CLICKED(IDC_RADIO3, &PDialog::OnRadio3)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPDialog 

void PDialog::OnRadio1()  {
    m_parameters->insert = FALSE;
    m_parameters->connect = FALSE;
}

void PDialog::OnRadio2()  {
    m_parameters->insert = TRUE;
    m_parameters->connect = FALSE;
}

void PDialog::OnRadio3()  {
    m_parameters->insert = TRUE;
    m_parameters->connect = TRUE;
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    auto *id1 = (CButton *)GetDlgItem(IDC_RADIO1);
    if (m_parameters->insert && m_parameters->connect) {
        id1 = (CButton *)GetDlgItem(IDC_RADIO3);
    } else {
        if (m_parameters->insert) {
            id1 = (CButton *)GetDlgItem(IDC_RADIO2);
        } else {
            id1 = (CButton *)GetDlgItem(IDC_RADIO1);
        }
    }
    id1->SetCheck(TRUE);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
