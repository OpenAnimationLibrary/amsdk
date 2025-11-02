// ConformDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "Conform.h"
#include "ConformDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ConformDialog dialog

CConformDialog::CConformDialog(HChor *chor, HModel *model, CWnd *pParent /*=nullptr*/) : CPluginDialog(IDD, pParent), m_ModelBody{nullptr}, m_FirstModel{nullptr}, m_iModelCount{0} {
    m_Chor = chor;
    m_ModelClothing = model;
    //{{AFX_DATA_INIT(CConformDialog)
    //}}AFX_DATA_INIT
}

void CConformDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CConformDialog)
    DDX_Control(pDX, IDC_FIGURETOCONFORMTO, m_lstFigure);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConformDialog, CDialog)
    //{{AFX_MSG_MAP(CConformDialog)
    ON_CBN_EDITCHANGE(IDC_FIGURETOCONFORMTO, &CConformDialog::OnEditchangeFigureToConformTo)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConformDialog message handlers

void CConformDialog::OnEditchangeFigureToConformTo() {
    // TODO: Add your control notification handler code here

}

BOOL CConformDialog::OnInitDialog() {

//    HBone *rbone = nullptr;

//    CString message = " ";
CPluginDialog::OnInitDialog();
    auto *pListBox = (CListBox *)GetDlgItem(IDC_FIGURETOCONFORMTO);

    //Display all models in Choreography except the one chosen.

    MODELS *ptr_model = nullptr;
    m_FirstModel = nullptr;
    for (HModel *model = m_Chor->GetChildModel(); model; model = model->GetNextModelInChor()) {
        if (model != m_ModelClothing) {
            CString message = model->GetName();
            pListBox->AddString(message);
            MODELS *ptr_prevModel = ptr_model;
            ptr_model = new MODELS;
            ptr_model->m_Model = model;
            ptr_model->next = nullptr;
            if (ptr_prevModel == nullptr) {
                //Save address of first Model in structure
                m_FirstModel = ptr_model;
            } else {
                ptr_prevModel->next = ptr_model;
            }
        }
    }
    pListBox->SetCurSel(0);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CConformDialog::OnOK() {
//    CString message = " ";
CPluginDialog::OnOK();
    const MODELS *ptr_model = m_FirstModel;
    m_ModelBody = nullptr;
    //Get from the list box the correct figure to conform to, 
    for (int i = 0; i <= m_lstFigure.GetCurSel(); ++i) {
        m_ModelBody = ptr_model->m_Model;
        ptr_model = ptr_model->next;
        if (ptr_model == nullptr) {
            i = m_lstFigure.GetCurSel() + 1; //break out of loop
        }
    }
}
