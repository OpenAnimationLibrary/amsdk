// ImportModelDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "StrClass.h"
#include "Hxt.h"
#include "ImportModelDialog.h"
#include "F_Protos.h"

#include "SDK/Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportModelDialog dialog

CImportModelDialog::CImportModelDialog(): CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_peaktolerance = GetRegistryValue("LWO Plugin", "Peak Tolerance", 45.0F);
    //{{AFX_DATA_INIT(CImportModelDialog)
    //}}AFX_DATA_INIT
}

void CImportModelDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CImportModelDialog)
    DDX_Text(pDX, IDC_PEAKTOLERANCE, m_peaktolerance);
    DDV_MinMaxFloat(pDX, m_peaktolerance, 0.F, 360.F);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImportModelDialog, CDialog)
    //{{AFX_MSG_MAP(CImportModelDialog)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportModelDialog message handlers

void CImportModelDialog::OnOK() {
    CPluginDialog::OnOK();
    SetRegistryValue("LWO Plugin", "Peak Tolerance", m_peaktolerance);
}
