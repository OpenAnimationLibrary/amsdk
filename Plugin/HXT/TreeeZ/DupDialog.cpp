// KB  1/18/05  \Plugin\HXT\Duplicator\DupDialog.cpp

#include "StdAfx.h"
#include "StrClass.h"
#include "F_Protos.h"
#include "DupDialog.h"
#include "Hxt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDupDialog dialog

CDupDialog::CDupDialog(DupParameters *parameters)
: CPluginDialog(CDupDialog::IDD, CWnd::FromHandle(GetMainApplicationWnd()))
{
	//{{AFX_DATA_INIT(CDupDialog)
	m_parameters = parameters;
	//}}AFX_DATA_INIT
}


void CDupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CDupDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDupDialog, CDialog)
	//{{AFX_MSG_MAP(CDupDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDupDialog message handlers
BOOL CDupDialog::OnInitDialog()
{
   CDialog::OnInitDialog();

   return FALSE;
}

void CDupDialog::OnOK() 
{
	CDialog::OnOK();
}
