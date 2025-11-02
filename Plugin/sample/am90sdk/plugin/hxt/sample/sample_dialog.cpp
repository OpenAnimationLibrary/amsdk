// sample_dialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "sample.h"
#include "sample_dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld sample_dialog 


sample_dialog::sample_dialog(CWnd* pParent /*=NULL*/)
	: CDialog(sample_dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(sample_dialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void sample_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(sample_dialog)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(sample_dialog, CDialog)
	//{{AFX_MSG_MAP(sample_dialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten sample_dialog 
