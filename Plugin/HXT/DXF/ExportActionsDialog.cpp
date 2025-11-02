// ExportActionsDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Hxt.h"
#include "ExportActionsDialog.h"
#include "F_Protos.h"
#include "MapLimit.h"

#include "SDK/Misc.h"
#include "SDK/HAction.h"
#include "SDK/HProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportActionsDialog dialog

CExportActionsDialog::CExportActionsDialog(HActionCacheContainer *hacc) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_hacc = hacc;
    m_dir = GetRegistryString("DXF Plugin", "Output Directory", ".");
    m_subtype = GetRegistryValue("DXF Plugin", "Sub Type", ST_VARIABLE);
    m_applybump = GetRegistryString("DXF Plugin", "Apply Displace", "FALSE") == "TRUE";
    //{{AFX_DATA_INIT(CExportActionsDialog)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}

BOOL CExportActionsDialog::OnInitDialog() {
    CDialog::OnInitDialog();

    m_selected.RemoveAll();
    for (HActionCache *hac = m_hacc->GetChildActionCache(); hac; hac = hac->GetSiblingActionCache()) {
        String name = hac->GetName();
        const int iIndex = m_checklistbox.AddString(name.GetNameOnlyWithoutSuffix().Get());
        m_checklistbox.SetItemData(iIndex, (DWORD_PTR)hac);
        m_checklistbox.SetCheck(iIndex, TRUE);
    }
    GetDlgItem(IDC_OUTPUTDIR)->SetWindowText(m_dir.Get());
    CString text;
    text.LoadString(IDS_ACTIONSTOEXPORT);
    GetDlgItem(IDC_LISTLABEL)->SetWindowText(text);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportActionsDialog::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExportActionsDialog)
    DDX_Control(pDX, IDC_MODELLIST_COMBO, m_checklistbox);
    DDX_Radio(pDX, IDC_SUB1, m_subtype);
    DDX_Check(pDX, IDC_CHECK1, m_applybump);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportActionsDialog, CDialog)
    //{{AFX_MSG_MAP(CExportActionsDialog)
    ON_BN_CLICKED(IDC_BROWSE, &CExportActionsDialog::OnBrowse)
    // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportActionsDialog message handlers

void CExportActionsDialog::OnOK() {
    CDialog::OnOK();
    for (int iIndex = 0; iIndex < m_checklistbox.GetCount(); iIndex++) {
        if (m_checklistbox.GetCheck(iIndex)) {
            auto *hac = (HActionCache *)m_checklistbox.GetItemData(iIndex);
            m_selected.AddTail(hac);
        }
    }
    SetRegistryString("DXF Plugin", "Output Directory", m_dir);
    SetRegistryValue("DXF Plugin", "Sub Type", m_subtype);
    SetRegistryString("DXF Plugin", "Apply Displace", m_applybump ? "TRUE" : "FALSE");
}

void CExportActionsDialog::OnBrowse() {
    CString caption;
    caption.LoadString(IDS_CHOOSEDIRECTORY);
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!DirRequest(m_dir, caption/*nullptr*/, m_dir.Get(), this))
            return;
    }
    GetDlgItem(IDC_OUTPUTDIR)->SetWindowText(m_dir.Get());
}
