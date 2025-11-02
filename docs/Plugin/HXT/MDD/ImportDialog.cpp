// ImportDialog.cpp : implementation file
//
#include "StdAfx.h"
#include "MDD.h"
#include "ImportDialog.h"

ImportDialog::ImportDialog(W_PARA *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_para = parameters;
}

ImportDialog::~ImportDialog() = default;

void ImportDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_para->fps);
    DDV_MinMaxFloat(pDX, m_para->fps, 0.1F, 1000);
    DDX_Text(pDX, IDC_EDIT2, m_para->scale);
    DDV_MinMaxFloat(pDX, m_para->scale, 1e-6F, 10000);
    //   DDX_Text(pDX, IDC_STATIC_FILENAME, m_para->filename);
    DDX_Check(pDX, IDC_CHECK1, m_para->startatcurrenttime);
}

BEGIN_MESSAGE_MAP(ImportDialog, CDialog)ON_BN_CLICKED(IDC_BUTTON1, &ImportDialog::OnClickedButton1)END_MESSAGE_MAP()

void ImportDialog::OnClickedButton1() {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("mdd");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr)) {
            m_para->filename = defdir;
            CWnd *dlgitem = GetDlgItem(IDC_STATIC_FILENAME);
            const String text = m_para->filename.GetAbbreviated(dlgitem);
            dlgitem->SetWindowText(text.Get());
            //         UpdateData(false);
        }
    }
}

void ImportDialog::OnOK() {
    UpdateData(true);
    CPluginDialog::OnOK();
}

BOOL ImportDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CWnd *dlgitem = GetDlgItem(IDC_STATIC_FILENAME);
    const String text = m_para->filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());

    return TRUE; // return TRUE unless you set the focus to a control
}
