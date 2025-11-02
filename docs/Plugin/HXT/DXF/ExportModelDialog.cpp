// ExportModelDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Hxt.h"
#include "ExportModelDialog.h"
#include "F_Protos.h"
#include "MapLimit.h"

#include "SDK/HModel.h"
#include "SDK/Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportModelDialog dialog

CExportModelDialog::CExportModelDialog(const String &filename): CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    const String path = GetRegistryString("DXF Plugin", "File Path", ".");
    m_filename = filename.GetNameOnlyWithoutSuffix() + ".DXF";
    m_filename = CombineNameToPath(path, m_filename);
    m_subtype = GetRegistryValue("DXF Plugin", "Sub Type", ST_VARIABLE);
    m_applybump = GetRegistryString("DXF Plugin", "Apply Displace", "FALSE") == "TRUE";

    //{{AFX_DATA_INIT(CExportModelDialog)
    //}}AFX_DATA_INIT
}

BOOL CExportModelDialog::OnInitDialog() {
    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());

    CPluginDialog::OnInitDialog();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportModelDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExportModelDialog)
    DDX_Radio(pDX, IDC_SUB1, m_subtype);
    DDX_Check(pDX, IDC_CHECK1, m_applybump);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportModelDialog, CDialog)
    //{{AFX_MSG_MAP(CExportModelDialog)
    ON_BN_CLICKED(IDC_BROWSE, &CExportModelDialog::OnBrowse)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportModelDialog message handlers

void CExportModelDialog::OnOK() {
    CPluginDialog::OnOK();
    const String path = m_filename.GetPathOnly();
    SetRegistryString("DXF Plugin", "File Path", path);
    SetRegistryValue("DXF Plugin", "Sub Type", m_subtype);
    SetRegistryString("DXF Plugin", "Apply Displace", m_applybump ? "TRUE" : "FALSE");
}

void CExportModelDialog::OnBrowse() {
    CString filters, title;
    title.LoadString(IDS_EXPORTTITLE);
    filters.LoadString(IDS_FILEFILTERS);

    const String ext("DXF");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, m_filename, ext.Get(), ext.Get()))
            return;
    }
    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());
}
