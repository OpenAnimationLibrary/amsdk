// about.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "about1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

about::about(HWND pParent) : CPluginDialog(IDD, FromHandle(pParent)) {
    //{{AFX_DATA_INIT(about)
    // HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
    //}}AFX_DATA_INIT
}

void about::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(about)
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(about, CDialog)
        //{{AFX_MSG_MAP(about)
        ON_BN_CLICKED(IDC_BUTTON1, &about::OnButton1)
        ON_BN_CLICKED(IDC_BUTTON2, &about::OnButton2)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten about 

BOOL about::OnInitDialog() {
    CPluginDialog::OnInitDialog();


    SetDlgItemText(IDC_STATIC_NAME,pname);
    SetDlgItemText(IDC_STATIC_VERSION,vnummer);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void about::OnButton1() {
    const HWND hwnd = GetMainApplicationWnd();
    LaunchEMail(hwnd, "am@sgross.com");
}

void about::OnButton2() {
    const HWND hwnd = GetMainApplicationWnd();
    LaunchURL(hwnd, "http://www.sgross.com/plugins/");

}
