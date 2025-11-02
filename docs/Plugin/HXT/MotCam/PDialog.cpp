// PDialog.cpp : Implementierungsdatei
//

#include "StdAfx.h"
#include "MotCam.h"
#include "PDialog.h"

PDialog::PDialog(W_PARA *m_para) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    para = m_para;
}

PDialog::~PDialog() = default;

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, para->height);
    DDV_MinMaxInt(pDX, para->height, 0, 5000);
    DDX_Text(pDX, IDC_EDIT2, para->width);
    DDV_MinMaxInt(pDX, para->width, 0, 5000);
    DDX_Text(pDX, IDC_EDIT3, para->start);
    DDV_MinMaxInt(pDX, para->start, 0, 5000);
    DDX_Text(pDX, IDC_EDIT4, para->end);
    DDV_MinMaxInt(pDX, para->end, 0, 5000);
    DDX_Text(pDX, IDC_EDIT5, para->fps);
    DDV_MinMaxInt(pDX, para->fps, 0, 5000);
    DDX_Text(pDX, IDC_EDIT6, para->cameraname);
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
    const String ext("mot");
    String filename = para->filename.GetBuffer();
    title.Format("Export Motion");
    filters.Format("Motion File (*.mot)|*.mot|ASCII||");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, filename, ext.Get(), ext.Get())) {
            filename = para->filename;
        }
    }
    title.Format("%s", filename.Get());
    SetDlgItemText(IDC_STATIC_FILE, title);
    para->filename.Format("%s", filename.Get());
    para->path.Format("%s\\", filename.GetPathOnly().Get());
}

void PDialog::OnEnChangeEdit6() {
    UpdateData(true);
    para->filename = para->path + para->cameraname + ".mot";
    SetDlgItemText(IDC_STATIC_FILE, para->filename);
}

void PDialog::OnBnClickedOk() {
    UpdateData(true);
    CPluginDialog::OnOK();
}
