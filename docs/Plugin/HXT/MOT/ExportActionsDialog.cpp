// Dan  3/6/2003  \Dan105\Plugin\HXT\MOT\ExportActionsDialog.cpp
//

#include "StdAfx.h"
#include "resource.h"
#include "ExportActionsDialog.h"
#include "F_Protos.h"

#include "SDK/HAction.h"
#include "SDK/HProject.h"
#include "SDK/Misc.h"

CExportActionsDialog::CExportActionsDialog(HActionCacheContainer *hacc) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_hacc = hacc;
    m_dir = GetRegistryString("MOT Plugin", "Output Directory", ".");
}

CExportActionsDialog::~CExportActionsDialog() {
    m_checklistbox.Detach();
}

void CExportActionsDialog::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ACTIONLIST_COMBO, m_checklistbox);
}

BEGIN_MESSAGE_MAP(CExportActionsDialog, CDialog)ON_BN_CLICKED(IDC_BROWSE, &CExportActionsDialog::OnBrowse)END_MESSAGE_MAP()

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
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportActionsDialog::OnOK() {
    CDialog::OnOK();
    for (int iIndex = 0; iIndex < m_checklistbox.GetCount(); iIndex++) {
        if (m_checklistbox.GetCheck(iIndex)) {
            auto *hac = (HActionCache *)m_checklistbox.GetItemData(iIndex);
            m_selected.AddTail(hac);
        }
    }
    SetRegistryString("MOT Plugin", "Output Directory", m_dir);
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
