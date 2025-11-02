// about.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "about.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Diahash_math::logeld about 

about::about(HWND pParent)
        : CPluginDialog(about::IDD, CWnd::FromHandle(pParent))
{
	//{{AFX_DATA_INIT(about)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void about::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(about)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(about, CDialog)
	//{{AFX_MSG_MAP(about)
	ON_BN_CLICKED(IDC_A_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_A_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten about 


BOOL about::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	SetDlgItemText(IDC_STATIC_A_NAME,pname);
	SetDlgItemText(IDC_STATIC_A_VERSION,vnummer);

#if !defined(SGROSS)
   CWnd *htmlbutton = GetDlgItem(IDC_A_BUTTON2);
   htmlbutton->SetWindowText("Steffen Gross");
   GetDlgItem(IDC_A_BUTTON1)->ShowWindow(SW_HIDE);
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void about::OnButton1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    HWND hwnd;
	hwnd = GetMainApplicationWnd();
	LaunchEMail(hwnd, "am@sgross.com");
}

void about::OnButton2() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    HWND hwnd;
	hwnd = GetMainApplicationWnd();
	LaunchURL(hwnd, "http://www.sgross.com/plugins/");
	
}

