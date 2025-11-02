// ExportDialog.cpp : implementation file
//
#include "StdAfx.h"
#include "MDD.h"
#include "ExportDialog.h"
#pragma warning( disable : 4244 )

ExportDialog::ExportDialog(W_PARA *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    m_para = parameters;
}

ExportDialog::~ExportDialog() = default;

void ExportDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    DDX_Time(pDX, IDC_EDIT1, m_para->start, m_para->fps, GetTimeMode(), FALSE);
    DDX_Text(pDX, IDC_EDIT2, m_para->scale);
    DDV_MinMaxFloat(pDX, m_para->scale, 1e-6F, 10000);
    DDX_Time(pDX, IDC_EDIT3, m_para->end, m_para->fps, GetTimeMode(), FALSE);
    //   DDX_Text(pDX, IDC_STATIC_FILENAME, m_para->filename);
    DDX_Radio(pDX, IDC_RADIO1, m_para->subtype);
}

BEGIN_MESSAGE_MAP(ExportDialog, CDialog)ON_BN_CLICKED(IDC_BUTTON1, &ExportDialog::OnClickedButton1)END_MESSAGE_MAP()

BOOL ExportDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CWnd *dlgitem = GetDlgItem(IDC_STATIC_FILENAME);
    const String text = m_para->filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void ExportDialog::OnClickedButton1() {
    CString caption, filter;
    caption.LoadString(IDS_EXPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir = m_para->filename; //not used for multiselect dlg
    const String ext("mdd");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (SaveRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr)) {
            m_para->filename = defdir;
            CWnd *dlgitem = GetDlgItem(IDC_STATIC_FILENAME);
            const String text = m_para->filename.GetAbbreviated(dlgitem);
            dlgitem->SetWindowText(text.Get());
            //         UpdateData(false);
        }
    }
}

void ExportDialog::OnOK() {
    UpdateData(true);
    CPluginDialog::OnOK();
}
