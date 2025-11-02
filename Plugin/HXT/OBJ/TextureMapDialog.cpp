// TextureMapDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "StrClass.h"
#include "Hxt.h"
#include "TextureMapDialog.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureMapDialog dialog

CTextureMapDialog::CTextureMapDialog(CHxtApp *app, IEPolyModel *model) : CPluginDialog(IDD, nullptr) {
    //{{AFX_DATA_INIT(CTextureMapDialog)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_copymaps = GetRegistryValue("OBJ Plugin", "Copy Maps", TRUE);
    m_app = app;
    m_model = model;
}

void CTextureMapDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CTextureMapDialog)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTextureMapDialog, CDialog)
    //{{AFX_MSG_MAP(CTextureMapDialog)
    ON_BN_CLICKED(IDC_COPYMAPSYES, &CTextureMapDialog::OnCopyMapsYes)
    ON_BN_CLICKED(IDC_COPYMAPSNO, &CTextureMapDialog::OnCopyMapsNo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureMapDialog message handlers

void CTextureMapDialog::MakeUnique(String &filename, const int count) const {
    const int digits = (int)log10((float)count) + 1;

    filename = filename.Left(7 - digits) + "_" + (String)count;
    for (int i = 0; i < m_app->m_maplist.GetSize(); ++i) {
        if (m_app->m_maplist[i] == (CString)filename.Get()) {
            MakeUnique(filename, count + 1);
            return;
        }
    }
}

BOOL CTextureMapDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    auto *radio1 = (CButton *)GetDlgItem(IDC_COPYMAPSYES);
    auto *radio2 = (CButton *)GetDlgItem(IDC_COPYMAPSNO);
    if (m_copymaps) {
        radio1->SetCheck(true);
        radio2->SetCheck(false);
    } else {
        radio1->SetCheck(false);
        radio2->SetCheck(true);
    }

    //   GetDlgItem(IDOK)->EnableWindow(FALSE);

    m_app->m_maplist.SetSize(m_model->m_maplist.GetSize());
    auto *list = (CListCtrl *)GetDlgItem(IDC_FILENAMES);
    CString origheader;
    origheader.LoadString(IDS_ORIGINALFILENAME);
    CString newheader;
    newheader.LoadString(IDS_NEWFILENAME);

    list->InsertColumn(0, origheader, LVCFMT_LEFT, 200);
    list->InsertColumn(1, newheader, LVCFMT_LEFT, 200);

    int index = -1;
    for (int i = 0; i < m_model->m_maplist.GetSize(); ++i) {
        const IEMap &map = m_model->m_maplist[i];
        String filename = map.m_filename;
        String suffix = filename.GetSuffixOnly();
        filename = filename.GetNameOnlyWithoutSuffix();
        String origfilename = filename;

        filename = filename.Left(8);
        if (filename != origfilename) {
            MakeUnique(filename);
            filename += "." + suffix;
            origfilename += "." + suffix;
            index = list->InsertItem(LVIF_TEXT | LVIF_PARAM, index + 1, origfilename.Get(), 0, 0, 0, 0);
            list->SetItem(index, 1, LVIF_TEXT, filename.Get(), 0, 0, 0, 0);
        } else
            filename += "." + suffix;

        m_app->m_maplist[i] = (CString)filename.Get();
    }
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CTextureMapDialog::OnCopyMapsYes() {
    m_copymaps = TRUE;
}

void CTextureMapDialog::OnCopyMapsNo() {
    m_copymaps = FALSE;
}

void CTextureMapDialog::OnOK() {
    CPluginDialog::OnOK();
    SetRegistryValue("OBJ Plugin", "Copy Maps", m_copymaps);
}
