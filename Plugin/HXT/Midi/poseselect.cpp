// poseselect.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Midi.h"
#include "poseselect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

poseselect::poseselect(Parameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(poseselect)
    m_parameters = parameters;
    // HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
    //}}AFX_DATA_INIT
}

void poseselect::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(poseselect)
    // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(poseselect, CDialog)
        //{{AFX_MSG_MAP(poseselect)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten poseselect 

BOOL poseselect::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    int index;
    HProperty *property1, *property2;
    CString temp;
    String name, name1;
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST2);
    HProperty *property = m_parameters->hm_org->GetUserCategoryProperty();
    for (int i = 0; (property1 = property->GetPropertyAt(i)); ++i) {
        if (property1->GetObjectType() == HOT_USERPROPERTY) {
            for (int j = 0; (property2 = property1->GetPropertyAt(j)); ++j) {
                name = property2->GetName();
                name1 = ((HProperty *)property2->GetParent())->GetName();
                temp.Format("%s -- %s", name1.Get(), name.Get());
                index = id1->AddString(temp);
                id1->SetItemDataPtr(index, property2);
            }
        } else {
            name = property1->GetName();
            name1 = ((HProperty *)property1->GetParent())->GetName();
            temp.Format("%s -- %s", name1.Get(), name.Get());
            index = id1->AddString(temp);
            id1->SetItemDataPtr(index, property1);
        }
    }
    id1->SetCurSel(0);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void poseselect::OnOK() {

    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST2);
    m_parameters->p_property = (HProperty *)id1->GetItemDataPtr(id1->GetCurSel());
    m_parameters->p_name = m_parameters->p_property->GetName();
    m_parameters->p_type = m_parameters->p_property->GetObjectType();
    CPluginDialog::OnOK();
}
