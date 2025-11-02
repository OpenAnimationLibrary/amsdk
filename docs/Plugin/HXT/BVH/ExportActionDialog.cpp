// NAP  9/4/2003  \Noelsrv105\Plugin\HXT\BVH\ExportActionDialog.cpp

#include "StdAfx.h"
#include "resource.h"
#include "ExportActionDialog.h"
#include "F_Protos.h"
#include "SDK/HAction.h"
#include "SDK/Misc.h"

IMPLEMENT_DYNAMIC(CExportActionDialog, CPluginDialog)

CExportActionDialog::CExportActionDialog(HActionCache *hac) : CPluginDialog(IDD_EXPORTACTION, FromHandle(GetMainApplicationWnd())) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    String path = GetRegistryString("BVH Plugin", "File Path", ".");
    m_ispadmotion = GetRegistryString("BVH Plugin", "Pad Motion", "FALSE") == "TRUE";
    m_exportstate = GetRegistryValue("BVH Plugin", "Export Bones", 0);
    m_nomotion = GetRegistryString("BVH Plugin", "No Motion", "FALSE") == "TRUE";

    m_filename = hac->GetFileName();
    m_filename = m_filename.GetNameOnlyWithoutSuffix() + ".bvh";
    m_filename = CombineNameToPath(path, m_filename);
    m_errortolerance = 0.F;
}

void CExportActionDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_PADMOTION_CHECK, m_ispadmotion);
    DDX_Check(pDX, IDC_CHECK1, m_nomotion);
    DDX_Radio(pDX, IDC_RADIO1, m_exportstate);
}

BEGIN_MESSAGE_MAP(CExportActionDialog, CPluginDialog)
ON_BN_CLICKED(IDC_BROWSE, &CExportActionDialog::OnBrowse)
END_MESSAGE_MAP()

BOOL CExportActionDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CExportActionDialog::OnOK() {
    CPluginDialog::OnOK();

    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    const String path = m_filename.GetPathOnly();
    SetRegistryString("BVH Plugin", "File Path", path);
    SetRegistryString("BVH Plugin", "Pad Motion", m_ispadmotion ? "TRUE" : "FALSE");
    SetRegistryValue("BVH Plugin", "Export Bones", m_exportstate);
    SetRegistryString("BVH Plugin", "No Motion", m_nomotion ? "TRUE" : "FALSE");
}

void CExportActionDialog::OnBrowse() {
    CString filters, title;
    title.LoadString(IDS_EXPORTTITLE);
    filters.LoadString(IDS_FILEFILTERS);

    const String ext("bvh");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, m_filename, ext.Get(), ext.Get()))
            return;
    }
    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());
}
