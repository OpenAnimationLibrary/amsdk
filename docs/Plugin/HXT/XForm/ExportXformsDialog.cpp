#include "StdAfx.h"
#include "Export-Xforms.h"
#include "ExportXformsDialog.h"

//#include "afxdialogex.h"
//#include "resource.h"

// IMPLEMENT_DYNAMIC(CExportXformsDialog, CDialog)

CExportXformsDialog::CExportXformsDialog(CWnd *pParent /*=NULL*/) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())), start_frame{0}, end_frame{0} {}

CExportXformsDialog::CExportXformsDialog(const String &filename) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    start_frame = GetRegistryValue("Export Transforms Plugin", "Start Frame", 0);
    end_frame = GetRegistryValue("Export Transforms Plugin", "End Frame", 30);
    m_filename = GetRegistryString("Export Transforms Plugin", "File Path", ".\\animation-master-export.xform");
}

CExportXformsDialog::~CExportXformsDialog() = default;

void CExportXformsDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExportXformsDialog, CDialog)
    ON_BN_CLICKED(IDC_BrowseButton, &CExportXformsDialog::OnBrowse)
    ON_BN_CLICKED(IDOK, &CExportXformsDialog::OnBnClickedOk)
    ON_EN_CHANGE(IDC_StartFrame, &CExportXformsDialog::UpdateStartTimecode)
    ON_EN_CHANGE(IDC_EndFrame, &CExportXformsDialog::UpdateEndTimecode)
END_MESSAGE_MAP()

// CExportXformsDialog message handlers

BOOL CExportXformsDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    auto *start_spin = (CSpinButtonCtrl *)GetDlgItem(IDC_StartSpin);
    auto *end_spin = (CSpinButtonCtrl *)GetDlgItem(IDC_EndSpin);
    start_spin->SetRange32(0, INT32_MAX);
    end_spin->SetRange32(0, INT32_MAX);
    start_spin->SetPos32(start_frame);
    end_spin->SetPos32(end_frame);

    /*
    //    char fr[32];
    CWnd *start_ebox = GetDlgItem(IDC_StartFrame);
    std::string temp1 = std::to_string(start_frame);
    start_ebox->SetWindowText(temp1.c_str());
//    start_ebox->SetWindowText(itoa(start_frame, fr, 10));
    CWnd *end_ebox = GetDlgItem(IDC_EndFrame);
    std::string temp2 = std::to_string(end_frame);
    end_ebox->SetWindowText(temp2.c_str());
    */

    CWnd *dlgitem = GetDlgItem(IDC_BrowseFile);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());
    return TRUE;
}

void CExportXformsDialog::OnBrowse() {
    /*
        CString filters, title;
        title.LoadString(XXF_EXPORTTITLE);
        filters.LoadString(XXF_MENUFILTER);
        CFileDialog saveas_dlg(
            FALSE,
            "xforms",
            "animation_master_export",
            0,
            "Bone Transforms (*.xform)|*.xform|All Files (*)|*||"
            );
    
        if (saveas_dlg.DoModal() == IDOK)
        {
            CString path = saveas_dlg.GetPathName();
            CWnd *dlgitem = GetDlgItem(IDC_BrowseFile);
            dlgitem->SetWindowText(path);
        }
    
        "Bone Transforms (*.xform)|*.xform|HASH||"
      
        */
    CString filters, title;
    title.LoadString(XXF_EXPORTTITLE);
    filters.LoadString(XXF_MENUFILTER);

    const String ext("xform");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, m_filename, ext.Get(), ext.Get()))
            return;
    }

    CWnd *dlgitem = GetDlgItem(IDC_BrowseFile);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());

}

void CExportXformsDialog::OnBnClickedOk() {
    char ts[1024]{};
    const CEdit *sfeb = (CEdit *)GetDlgItem(IDC_StartFrame);
    sfeb->GetLine(0, ts, 15);
    const int sf = atoi_replace(ts);
    const CEdit *efeb = (CEdit *)GetDlgItem(IDC_EndFrame);
    efeb->GetLine(0, ts, 15);
    const int ef = atoi_replace(ts);
    if (ef < sf) {
        MessageBox("You have specified an end frame that comes before the start frame.\nPlease set a valid frame range.", "Invalid Frame Range", MB_ICONEXCLAMATION | MB_OK);
        return;
    }
    SetRegistryString("Export Transforms Plugin", "File Path", m_filename);

    /*
    CEdit *ed = (CEdit *)GetDlgItem(IDC_BrowseFile);
    String test = "";
    CString test1;
    int len = ed->LineLength(0);
    ed->GetLine(0, test1.GetBuffer(len), len);
    test1.ReleaseBuffer(len);
    test = (String)test1;
    //  CEdit *feb = (CEdit *)GetDlgItem(IDC_BrowseFile);
    //  feb->GetLine(0, ts, 1023);
    //  if(!strcmp(ts, ""))
    if (test.IsEmpty())
    {
    MessageBox(
    "Specify the file to export to.",
    "No File Specified",
    MB_ICONEXCLAMATION | MB_OK);
    return;
    }
    //    String path(ts);
    String path(test);
    SetRegistryString(
    "Export Transforms Plugin",
    "File Path",
    path);
    */
    SetRegistryValue("Export Transforms Plugin", "Start Frame", sf);
    SetRegistryValue("Export Transforms Plugin", "End Frame", ef);
    CPluginDialog::OnOK();
}

void CExportXformsDialog::UpdateTimecode(const int src, const int trg) const {
    char s[64]{0};
    CString cs;
    const CWnd *ebox = GetDlgItem(src);
    CWnd *stat = GetDlgItem(trg);
    if (!ebox || !stat) {
        return;
    }
    ebox->GetWindowText(cs);
    const int sf = atoi_replace(cs);
    int fps = (int)GetHProject()->GetFPS();
    if (fps == 0) {
        fps = 30;
    }
    snprintf(s, 63, "Timecode: %02i:%02i:%02i", sf / 1800, sf / fps % 60, sf % fps);
    stat->SetWindowText(s);
}

void CExportXformsDialog::UpdateStartTimecode() {
    UpdateTimecode(IDC_StartFrame, IDC_StartTimecode);
}

void CExportXformsDialog::UpdateEndTimecode() {
    UpdateTimecode(IDC_EndFrame, IDC_EndTimecode);
}
