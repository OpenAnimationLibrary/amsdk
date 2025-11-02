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

CExportModelDialog::CExportModelDialog(const String &filename): CDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    const String path = GetRegistryString("STL Plugin", "File Path", ".");
    m_filename = filename.GetNameOnlyWithoutSuffix() + ".STL";
    m_filename = CombineNameToPath(path, m_filename);
    m_subtype = GetRegistryValue("STL Plugin", "Sub Type", ST_VARIABLE);
    m_applybump = GetRegistryString("STL Plugin", "Apply Displace", "FALSE") == "TRUE";
    m_binary = GetRegistryString("STL Plugin", "Binary Format", "TRUE") == "TRUE";

    //{{AFX_DATA_INIT(CExportModelDialog)
    //}}AFX_DATA_INIT
}

BOOL CExportModelDialog::OnInitDialog() {
    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());

    CDialog::OnInitDialog();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportModelDialog::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExportModelDialog)
    DDX_Radio(pDX, IDC_SUB1, m_subtype);
    DDX_Check(pDX, IDC_CHECK1, m_applybump);
    DDX_Check(pDX, IDC_CHECK2, m_binary);
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
    CDialog::OnOK();
    const String path = m_filename.GetPathOnly();
    SetRegistryString("STL Plugin", "File Path", path);
    SetRegistryValue("STL Plugin", "Sub Type", m_subtype);
    SetRegistryString("STL Plugin", "Apply Displace", m_applybump ? "TRUE" : "FALSE");
    SetRegistryString("STL Plugin", "Binary Format", m_binary ? "TRUE" : "FALSE");
}

void CExportModelDialog::OnBrowse() {
    CString filters, title;
    title.LoadString(IDS_EXPORTTITLE);
    filters.LoadString(IDS_FILEFILTERS);
    const String ext("STL");

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, m_filename, ext.Get(), ext.Get()))
            return;
    }

    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());
}
