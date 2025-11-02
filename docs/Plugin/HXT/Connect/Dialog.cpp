// Dialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

Dialog::Dialog(PARA *para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(Dialog)
    m_para = para;
    //}}AFX_DATA_INIT
}

void Dialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Dialog)
    DDX_Text(pDX, IDC_EDIT1, m_para->tol);
    DDV_MinMaxFloat(pDX, m_para->tol, 0., 10.);
    DDX_Check(pDX, IDC_CHECK1, m_para->modus);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Dialog, CDialog)
        //{{AFX_MSG_MAP(Dialog)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Dialog 

BOOL Dialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();



    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Dialog::OnOK() {

    UpdateData(TRUE);
    CPluginDialog::OnOK();
}
