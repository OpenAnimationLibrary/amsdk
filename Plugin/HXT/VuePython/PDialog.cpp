// PDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "VuePython.h"
#include "PDialog.h"

PDialog::PDialog(W_PARA *m_para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    para = m_para;
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnBnClickedButton1)
        ON_EN_CHANGE(IDC_EDIT6, &PDialog::OnEnChangeEdit6)
        ON_BN_CLICKED(IDOK, &PDialog::OnBnClickedOk)
END_MESSAGE_MAP()

// PDialog-Meldungshandler

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    SetDlgItemText(IDC_STATIC_FILE, para->filename);
    return TRUE;
}

void PDialog::OnBnClickedButton1() {
    CString filters, title;
    const String ext("py");
    String filename = para->filename.GetBuffer();
    title.Format("Export Python Script");
    filters.Format("Python File (*.py)|*.py|ASCII||");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, filename, ext.Get(), ext.Get())) {
            filename = para->filename.GetBuffer();
        }
    }
    title.Format("%s", filename.Get());
    SetDlgItemText(IDC_STATIC_FILE, title);
    para->filename.Format("%s", filename.Get());
    para->path.Format("%s\\", filename.GetPathOnly().Get());
}

void PDialog::OnEnChangeEdit6() {
    UpdateData(true);
    para->filename = para->path + para->cameraname + ".py";
    SetDlgItemText(IDC_STATIC_FILE, para->filename);
}

void PDialog::OnBnClickedOk() {
    UpdateData(true);
    CPluginDialog::OnOK();
}
