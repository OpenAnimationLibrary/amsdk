// Detail.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "CalcSurface.h"
#include "Detail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

CDetail::CDetail(Parameter *parameters, HWND pParent) : CPluginDialog(IDD, FromHandle(pParent)) {
    //{{AFX_DATA_INIT(CDetail)
    m_para = parameters;
    //}}AFX_DATA_INIT
}

void CDetail::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDetail)
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDetail, CDialog)
        //{{AFX_MSG_MAP(CDetail)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDetail 

BOOL CDetail::OnInitDialog() {
    CPluginDialog::OnInitDialog();

    CString temp, temp1;
    LVITEM lvi;
    CRect rect;
    auto *id2 = (CListCtrl *)GetDlgItem(IDC_LIST2);
    id2->GetClientRect(&rect);
    const int nColInterval = rect.Width() / 6;

    id2->InsertColumn(0,_T("Model"),LVCFMT_LEFT, nColInterval * 4, 0);
    id2->InsertColumn(1,_T("Surface cm*cm"),LVCFMT_RIGHT, nColInterval * 2, 1);
    for (int i = 0; i < m_para->detail.GetSize(); ++i) {
        temp.Format("%s", m_para->detail[i].name.Get());
        temp1.Format("%.2f", m_para->detail[i].surface);
        lvi.mask = LVIF_TEXT;
        lvi.iItem = i;
        lvi.iSubItem = 0;
        lvi.pszText = (LPTSTR)(LPCTSTR)temp;
        id2->InsertItem(&lvi);
        lvi.iSubItem = 1;
        lvi.pszText = (LPTSTR)(LPCTSTR)temp1;
        id2->SetItem(&lvi);
    }

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
