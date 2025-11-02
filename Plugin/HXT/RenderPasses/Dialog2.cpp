// Dialog2.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "RenderPasses.h"
#include "Dialog2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
Dialog2::Dialog2(PARAMETER *para) : CDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(Dialog2)
    m_edit1 = 0.F;
    m_edit2 = 0.F;
    m_edit3 = 0.F;
    m_edit4 = 0.F;
    m_diffuse_color = FALSE;
    m_ambience_color = FALSE;
    m_ambience_intensity = FALSE;
    m_specular_color = FALSE;
    m_specular_intensity = FALSE;
    m_reflection_intensity = FALSE;
    m_decal_intensity = FALSE;
    m_decal_all = FALSE;
    m_para = para;
    m_specular_size = FALSE;
    m_edit5 = 0.F;
    //}}AFX_DATA_INIT
}

void Dialog2::DoDataExchange(CDataExchange *pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Dialog2)
    DDX_Text(pDX, IDC_EDIT1, m_edit1);
    DDV_MinMaxFloat(pDX, m_edit1, 0.F, 1000.F);
    DDX_Text(pDX, IDC_EDIT2, m_edit2);
    DDV_MinMaxFloat(pDX, m_edit2, 0.F, 1000.F);
    DDX_Text(pDX, IDC_EDIT3, m_edit3);
    DDV_MinMaxFloat(pDX, m_edit3, 0.F, 1000.F);
    DDX_Text(pDX, IDC_EDIT4, m_edit4);
    DDV_MinMaxFloat(pDX, m_edit4, 0.F, 1000.F);
    DDX_Check(pDX, IDC_CHECK1, m_diffuse_color);
    DDX_Check(pDX, IDC_CHECK2, m_ambience_color);
    DDX_Check(pDX, IDC_CHECK3, m_ambience_intensity);
    DDX_Check(pDX, IDC_CHECK4, m_specular_color);
    DDX_Check(pDX, IDC_CHECK5, m_specular_intensity);
    DDX_Check(pDX, IDC_CHECK6, m_reflection_intensity);
    DDX_Check(pDX, IDC_CHECK7, m_decal_intensity);
    DDX_Check(pDX, IDC_CHECK8, m_decal_all);
    DDX_Check(pDX, IDC_CHECK9, m_specular_size);
    DDX_Text(pDX, IDC_EDIT5, m_edit5);
    DDV_MinMaxFloat(pDX, m_edit5, 0.F, 1000.F);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Dialog2, CDialog)
    //{{AFX_MSG_MAP(Dialog2)
    ON_BN_CLICKED(IDC_CHECK1, &Dialog2::OnCheck1)
    ON_BN_CLICKED(IDC_CHECK2, &Dialog2::OnCheck2)
    ON_BN_CLICKED(IDC_CHECK3, &Dialog2::OnCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &Dialog2::OnCheck4)
    ON_BN_CLICKED(IDC_CHECK5, &Dialog2::OnCheck5)
    ON_BN_CLICKED(IDC_CHECK6, &Dialog2::OnCheck6)
    ON_BN_CLICKED(IDC_CHECK7, &Dialog2::OnCheck7)
    ON_BN_CLICKED(IDC_RADIO1, &Dialog2::OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &Dialog2::OnRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &Dialog2::OnRadio3)
    ON_BN_CLICKED(IDC_RADIO4, &Dialog2::OnRadio4)
    ON_BN_CLICKED(IDC_RADIO5, &Dialog2::OnRadio5)
    ON_BN_CLICKED(IDC_BUTTON1, &Dialog2::OnButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &Dialog2::OnButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &Dialog2::OnButton3)
    ON_BN_CLICKED(IDC_CHECK9, &Dialog2::OnCheck9)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Dialog2 

BOOL Dialog2::OnInitDialog() {
    CDialog::OnInitDialog();
    CButton *id1;

#if _V10
      id1 = (CButton *)GetDlgItem(IDC_CHECK2);
	  id1->ShowWindow(FALSE);
      id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
	  id1->ShowWindow(FALSE);
#endif

    id1 = (CButton *)GetDlgItem(IDC_RADIO1);
    id1->SetCheck(TRUE);
    diffuse = ambience = specular = 0;
    radiostate = 0;

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void Dialog2::OnCheck1() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK1);
    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON1);
    if (id->GetCheck()) {
        id1->EnableWindow(TRUE);
    } else {
        id1->EnableWindow(FALSE);
    }
}

void Dialog2::OnCheck2() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK2);
    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON2);
    if (id->GetCheck()) {
        id1->EnableWindow(TRUE);
    } else {
        id1->EnableWindow(FALSE);
    }
}

void Dialog2::OnCheck3() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK3);
    auto *id1 = (CEdit *)GetDlgItem(IDC_EDIT1);
    if (id->GetCheck()) {
        id1->EnableWindow(TRUE);
    } else {
        id1->EnableWindow(FALSE);
    }
}

void Dialog2::OnCheck4() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK4);
    auto *id1 = (CButton *)GetDlgItem(IDC_BUTTON3);
    if (id->GetCheck()) {
        id1->EnableWindow(TRUE);
    } else {
        id1->EnableWindow(FALSE);
    }
}

void Dialog2::OnCheck5() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK5);
    auto *id1 = (CEdit *)GetDlgItem(IDC_EDIT2);
    if (id->GetCheck()) {
        id1->EnableWindow(TRUE);
    } else {
        id1->EnableWindow(FALSE);
    }
}

void Dialog2::OnCheck6() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK6);
    auto *id1 = (CEdit *)GetDlgItem(IDC_EDIT3);
    if (id->GetCheck()) {
        id1->EnableWindow(TRUE);
    } else {
        id1->EnableWindow(FALSE);
    }
}

void Dialog2::OnCheck7() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK7);
    auto *id2 = (CButton *)GetDlgItem(IDC_CHECK8);
    auto *id1 = (CEdit *)GetDlgItem(IDC_EDIT4);
    if (id->GetCheck()) {
        id1->EnableWindow(TRUE);
        id2->EnableWindow(TRUE);
    } else {
        id1->EnableWindow(FALSE);
        id2->EnableWindow(FALSE);
    }
}

void Dialog2::OnCheck9() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK9);
    auto *id1 = (CEdit *)GetDlgItem(IDC_EDIT5);
    if (id->GetCheck()) {
        id1->EnableWindow(TRUE);
    } else {
        id1->EnableWindow(FALSE);
    }
}

void Dialog2::OnRadio1() {
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    id1->ResetContent();
    SetID();
    id1->SetHorizontalExtent(0);
    radiostate = 0;
}

void Dialog2::OnRadio2() {
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);

    id1->ResetContent();
    SetID();
    CClientDC dc(this);
    CFont *f = id1->GetFont();
    dc.SelectObject(f);
    int width = 0;

    for (int i = 0; i < m_para->azmodel; ++i) {
        CString temp = m_para->model[i].hmodel->GetName();
        m_para->model[i].id = id1->AddString(temp);
        CSize sz = dc.GetTextExtent(temp);
        sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
        if (sz.cx > width)
            width = sz.cx;
    }
    id1->SetHorizontalExtent(width);
    radiostate = 1;
}

void Dialog2::OnRadio3() {

    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    id1->ResetContent();
    SetID();

    CClientDC dc(this);
    CFont *f = id1->GetFont();
    dc.SelectObject(f);
    int width = 0;

    for (int i = 0; i < m_para->azmodel; ++i) {
        CString temp = m_para->model[i].hmodel->GetName();
        m_para->model[i].id = id1->AddString(temp);
        CSize sz = dc.GetTextExtent(temp);
        sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
        if (sz.cx > width)
            width = sz.cx;
        for (int j = 0; j < m_para->model[i].azgroup; ++j) {
            temp.Format("      Group    %s", m_para->model[i].gruppe[j].hgroup->GetName());
            m_para->model[i].gruppe[j].id = id1->AddString(temp);
            sz = dc.GetTextExtent(temp);
            sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
            if (sz.cx > width)
                width = sz.cx;
        }
    }
    id1->SetHorizontalExtent(width);
    radiostate = 2;
}

void Dialog2::OnRadio4() {
    int j;

    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    id1->ResetContent();
    SetID();
    CClientDC dc(this);
    CFont *f = id1->GetFont();
    dc.SelectObject(f);
    int width = 0;

    for (int i = 0; i < m_para->azmodel; ++i) {
        CString temp = m_para->model[i].hmodel->GetName();
        m_para->model[i].id = id1->AddString(temp);
        CSize sz = dc.GetTextExtent(temp);
        sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
        if (sz.cx > width)
            width = sz.cx;
        for (j = 0; j < m_para->model[i].azgroup; ++j) {
            temp.Format("      Group    %s", m_para->model[i].gruppe[j].hgroup->GetName());
            m_para->model[i].gruppe[j].id = id1->AddString(temp);
            sz = dc.GetTextExtent(temp);
            sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
            if (sz.cx > width)
                width = sz.cx;
        }
        for (j = 0; j < m_para->model[i].azdecal; ++j) {
            temp.Format("      Decal    %s", m_para->model[i].decal[j].hdecalclip->GetName());
            m_para->model[i].decal[j].id = id1->AddString(temp);
            sz = dc.GetTextExtent(temp);
            sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
            if (sz.cx > width)
                width = sz.cx;
        }
    }
    id1->SetHorizontalExtent(width);
    radiostate = 3;
}

void Dialog2::OnRadio5() {
    int j;
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);

    id1->ResetContent();
    SetID();
    CClientDC dc(this);
    CFont *f = id1->GetFont();
    dc.SelectObject(f);
    int width = 0;

    for (int i = 0; i < m_para->azmodel; ++i) {
        CString temp = m_para->model[i].hmodel->GetName();
        m_para->model[i].id = id1->AddString(temp);
        CSize sz = dc.GetTextExtent(temp);
        sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
        if (sz.cx > width)
            width = sz.cx;
        for (j = 0; j < m_para->model[i].azmat; ++j) {
            if (m_para->model[i].material[j].isclip) {
                temp.Format("      Material        %s    Clip", m_para->model[i].material[j].hmaterial->GetName());
            } else {
                temp.Format("      Material        %s", m_para->model[i].material[j].hmaterial->GetName());
            }
            m_para->model[i].material[j].id = id1->AddString(temp);
            sz = dc.GetTextExtent(temp);
            sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
            if (sz.cx > width)
                width = sz.cx;
        }
        for (j = 0; j < m_para->model[i].azgroup; ++j) {
            temp.Format("      Group        %s", m_para->model[i].gruppe[j].hgroup->GetName());
            m_para->model[i].gruppe[j].id = id1->AddString(temp);
            sz = dc.GetTextExtent(temp, _tcslen(temp));
            sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
            if (sz.cx > width)
                width = sz.cx;
            for (int k = 0; k < m_para->model[i].gruppe[j].azmat; ++k) {
                if (m_para->model[i].gruppe[j].material[k].isclip) {
                    temp.Format("          Material    %s    Clip", m_para->model[i].gruppe[j].material[k].hmaterial->GetName());
                } else {
                    temp.Format("          Material    %s", m_para->model[i].gruppe[j].material[k].hmaterial->GetName());
                }
                m_para->model[i].gruppe[j].material[k].id = id1->AddString(temp);
                sz = dc.GetTextExtent(temp);
                sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
                if (sz.cx > width)
                    width = sz.cx;
            }
        }
        for (j = 0; j < m_para->model[i].azdecal; ++j) {
            temp.Format("      Decal        %s", m_para->model[i].decal[j].hdecalclip->GetName());
            m_para->model[i].decal[j].id = id1->AddString(temp);
            sz = dc.GetTextExtent(temp);
            sz.cx += 3 * GetSystemMetrics(SM_CXBORDER);
            if (sz.cx > width)
                width = sz.cx;
        }
    }
    id1->SetHorizontalExtent(width);
    radiostate = 4;
}

void Dialog2::OnButton1() {
    auto *id1 = (CButton *)GetDlgItem(IDOK);
    auto *id2 = (CButton *)GetDlgItem(IDCANCEL);
    id1->EnableWindow(FALSE);
    id2->EnableWindow(FALSE);
    CColorDialog cdlg(diffuse, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        diffuse = cdlg.GetColor();
    }
    id1->EnableWindow(TRUE);
    id2->EnableWindow(TRUE);
}

void Dialog2::OnButton2() {
    auto *id1 = (CButton *)GetDlgItem(IDOK);
    auto *id2 = (CButton *)GetDlgItem(IDCANCEL);
    id1->EnableWindow(FALSE);
    id2->EnableWindow(FALSE);
    CColorDialog cdlg(ambience, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        ambience = cdlg.GetColor();
    }
    id1->EnableWindow(TRUE);
    id2->EnableWindow(TRUE);
}

void Dialog2::OnButton3() {
    auto *id1 = (CButton *)GetDlgItem(IDOK);
    auto *id2 = (CButton *)GetDlgItem(IDCANCEL);
    id1->EnableWindow(FALSE);
    id2->EnableWindow(FALSE);
    CColorDialog cdlg(specular, CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_ENABLEHOOK, FromHandle(GetMainApplicationWnd()));
    if (cdlg.DoModal() == IDOK) {
        specular = cdlg.GetColor();
    }
    id1->EnableWindow(TRUE);
    id2->EnableWindow(TRUE);
}

void Dialog2::OnOK() {

    UpdateData(TRUE);
    Change();
    switch (radiostate) {
        case 0:
            // gesamte Chor 
            Change1();
            break;
        case 1:
            // Model
            Change2();
            break;
        case 2:
            // Model / Gruppen
            Change2();
            break;
        case 3:
            // Model / Gruppen / Decals
            Change2();
            break;
        case 4:
            // Model / Gruppen / Decals / Material
            Change2();
            break;
    }
    CDialog::OnOK();
}

void Dialog2::SetID() const {
    int j;

    for (int i = 0; i < m_para->azmodel; ++i) {
        // model
        m_para->model[i].id = -1;
        // Material
        for (j = 0; j < m_para->model[i].azmat; ++j) {
            m_para->model[i].material[j].id = -1;
        }
        //Decal
        for (j = 0; j < m_para->model[i].azdecal; ++j) {
            m_para->model[i].decal[j].id = -1;
        }
        //Gruppe
        for (j = 0; j < m_para->model[i].azgroup; ++j) {
            m_para->model[i].gruppe[j].id = -1;
            for (int k = 0; k < m_para->model[i].gruppe[j].azmat; ++k) {
                m_para->model[i].gruppe[j].material[k].id = -1;
            }
        }
    }
}

void Dialog2::Change() const {
    int j;

    for (int i = 0; i < m_para->azmodel; ++i) {
        // model
        if (m_diffuse_color)
            m_para->model[i].cset.diffuse.Set(GetRValue(diffuse),GetGValue(diffuse),GetBValue(diffuse), 0);
        if (m_ambience_color)
            m_para->model[i].cset.ambience.Set(GetRValue(ambience),GetGValue(ambience),GetBValue(ambience), 0);
        if (m_ambience_intensity)
            m_para->model[i].cset.ambienceintensity = m_edit1 / 100;
        if (m_specular_color)
            m_para->model[i].cset.specular.Set(GetRValue(specular),GetGValue(specular),GetBValue(specular), 0);
        if (m_specular_intensity)
            m_para->model[i].cset.specularintensity = m_edit2 / 100;
        if (m_specular_size)
            m_para->model[i].cset.specularsize = m_edit5 / 100;
        if (m_reflection_intensity)
            m_para->model[i].cset.reflectionintensity = m_edit3 / 100;
        // Material
        for (j = 0; j < m_para->model[i].azmat; ++j) {
            if (m_para->model[i].material[j].isclip) {
                // Decal
                if (m_decal_intensity)
                    m_para->model[i].material[j].percentage = m_edit4 / 100;
            } else {
                if (m_diffuse_color)
                    m_para->model[i].material[j].cset.diffuse.Set(GetRValue(diffuse),GetGValue(diffuse),GetBValue(diffuse), 0);
                if (m_ambience_color)
                    m_para->model[i].material[j].cset.ambience.Set(GetRValue(ambience),GetGValue(ambience),GetBValue(ambience), 0);
                if (m_ambience_intensity)
                    m_para->model[i].material[j].cset.ambienceintensity = m_edit1 / 100;
                if (m_specular_color)
                    m_para->model[i].material[j].cset.specular.Set(GetRValue(specular),GetGValue(specular),GetBValue(specular), 0);
                if (m_specular_intensity)
                    m_para->model[i].material[j].cset.specularintensity = m_edit2 / 100;
                if (m_specular_size)
                    m_para->model[i].material[j].cset.specularsize = m_edit5 / 100;
                if (m_reflection_intensity)
                    m_para->model[i].material[j].cset.reflectionintensity = m_edit3 / 100;
            }
        }
        //Decal
        for (j = 0; j < m_para->model[i].azdecal; ++j) {
            if (m_decal_intensity) {
                if (m_decal_all) {
                    m_para->model[i].decal[j].percentage = m_edit4 / 100;
                } else {
                    if (m_para->model[i].decal[j].decaltype == 0) {
                        m_para->model[i].decal[j].percentage = m_edit4 / 100;
                    }
                }
            }
        }
        //Gruppe
        for (j = 0; j < m_para->model[i].azgroup; ++j) {
            if (m_diffuse_color)
                m_para->model[i].gruppe[j].cset.diffuse.Set(GetRValue(diffuse),GetGValue(diffuse),GetBValue(diffuse), 0);
            if (m_ambience_color)
                m_para->model[i].gruppe[j].cset.ambience.Set(GetRValue(ambience),GetGValue(ambience),GetBValue(ambience), 0);
            if (m_ambience_intensity)
                m_para->model[i].gruppe[j].cset.ambienceintensity = m_edit1 / 100;
            if (m_specular_color)
                m_para->model[i].gruppe[j].cset.specular.Set(GetRValue(specular),GetGValue(specular),GetBValue(specular), 0);
            if (m_specular_intensity)
                m_para->model[i].gruppe[j].cset.specularintensity = m_edit2 / 100;
            if (m_specular_size)
                m_para->model[i].gruppe[j].cset.specularsize = m_edit5 / 100;
            if (m_reflection_intensity)
                m_para->model[i].gruppe[j].cset.reflectionintensity = m_edit3 / 100;
            for (int k = 0; k < m_para->model[i].gruppe[j].azmat; ++k) {
                if (m_para->model[i].gruppe[j].material[k].isclip) {
                    // Decal
                    if (m_decal_intensity)
                        m_para->model[i].gruppe[j].material[k].percentage = m_edit4 / 100;
                } else {
                    // Material
                    if (m_diffuse_color)
                        m_para->model[i].gruppe[j].material[k].cset.diffuse.Set(GetRValue(diffuse),GetGValue(diffuse),GetBValue(diffuse), 0);
                    if (m_ambience_color)
                        m_para->model[i].gruppe[j].material[k].cset.ambience.Set(GetRValue(ambience),GetGValue(ambience),GetBValue(ambience), 0);
                    if (m_ambience_intensity)
                        m_para->model[i].gruppe[j].material[k].cset.ambienceintensity = m_edit1 / 100;
                    if (m_specular_color)
                        m_para->model[i].gruppe[j].material[k].cset.specular.Set(GetRValue(specular),GetGValue(specular),GetBValue(specular), 0);
                    if (m_specular_intensity)
                        m_para->model[i].gruppe[j].material[k].cset.specularintensity = m_edit2 / 100;
                    if (m_specular_size)
                        m_para->model[i].gruppe[j].material[k].cset.specularsize = m_edit5 / 100;
                    if (m_reflection_intensity)
                        m_para->model[i].gruppe[j].material[k].cset.reflectionintensity = m_edit3 / 100;
                }
            }
        }
    }
}

void Dialog2::Change1() const {
    int j;

    for (int i = 0; i < m_para->azmodel; ++i) {
        // model
        if (m_diffuse_color)
            m_para->model[i].cset.changediffusecolor = TRUE;
        if (m_ambience_color)
            m_para->model[i].cset.changeambiencecolor = TRUE;
        if (m_ambience_intensity)
            m_para->model[i].cset.changeambienceintensity = TRUE;
        if (m_specular_color)
            m_para->model[i].cset.changespecularcolor = TRUE;
        if (m_specular_intensity)
            m_para->model[i].cset.changespecularintensity = TRUE;
        if (m_specular_size)
            m_para->model[i].cset.changespecularsize = TRUE;
        if (m_reflection_intensity)
            m_para->model[i].cset.changereflectionintensity = TRUE;
        // Material
        for (j = 0; j < m_para->model[i].azmat; ++j) {
            if (m_para->model[i].material[j].isclip) {
                // Decal
                if (m_decal_intensity)
                    m_para->model[i].material[j].changepercentage = TRUE;
            } else {
                if (m_diffuse_color)
                    m_para->model[i].material[j].cset.changediffusecolor = TRUE;
                if (m_ambience_color)
                    m_para->model[i].material[j].cset.changeambiencecolor = TRUE;
                if (m_ambience_intensity)
                    m_para->model[i].material[j].cset.changeambienceintensity = TRUE;
                if (m_specular_color)
                    m_para->model[i].material[j].cset.changespecularcolor = TRUE;
                if (m_specular_intensity)
                    m_para->model[i].material[j].cset.changespecularintensity = TRUE;
                if (m_specular_size)
                    m_para->model[i].material[j].cset.changespecularsize = TRUE;
                if (m_reflection_intensity)
                    m_para->model[i].material[j].cset.changereflectionintensity = TRUE;
            }
        }
        //Decal
        for (j = 0; j < m_para->model[i].azdecal; ++j) {
            if (m_decal_intensity) {
                if (m_decal_all) {
                    m_para->model[i].decal[j].tochange = TRUE;
                } else {
                    if (m_para->model[i].decal[j].decaltype == 0) {
                        m_para->model[i].decal[j].tochange = TRUE;
                    }
                }
            }
        }
        //Gruppe
        for (j = 0; j < m_para->model[i].azgroup; ++j) {
            if (m_diffuse_color)
                m_para->model[i].gruppe[j].cset.changediffusecolor = TRUE;
            if (m_ambience_color)
                m_para->model[i].gruppe[j].cset.changeambiencecolor = TRUE;
            if (m_ambience_intensity)
                m_para->model[i].gruppe[j].cset.changeambienceintensity = TRUE;
            if (m_specular_color)
                m_para->model[i].gruppe[j].cset.changespecularcolor = TRUE;
            if (m_specular_intensity)
                m_para->model[i].gruppe[j].cset.changespecularintensity = TRUE;
            if (m_specular_size)
                m_para->model[i].gruppe[j].cset.changespecularsize = TRUE;
            if (m_reflection_intensity)
                m_para->model[i].gruppe[j].cset.changereflectionintensity = TRUE;
            for (int k = 0; k < m_para->model[i].gruppe[j].azmat; ++k) {
                if (m_para->model[i].gruppe[j].material[k].isclip) {
                    // Decal
                    if (m_decal_intensity)
                        m_para->model[i].gruppe[j].material[k].changepercentage = TRUE;
                } else {
                    // Material
                    if (m_diffuse_color)
                        m_para->model[i].gruppe[j].material[k].cset.changediffusecolor = TRUE;
                    if (m_ambience_color)
                        m_para->model[i].gruppe[j].material[k].cset.changeambiencecolor = TRUE;
                    if (m_ambience_intensity)
                        m_para->model[i].gruppe[j].material[k].cset.changeambienceintensity = TRUE;
                    if (m_specular_color)
                        m_para->model[i].gruppe[j].material[k].cset.changespecularcolor = TRUE;
                    if (m_specular_intensity)
                        m_para->model[i].gruppe[j].material[k].cset.changespecularintensity = TRUE;
                    if (m_specular_size)
                        m_para->model[i].gruppe[j].material[k].cset.changespecularsize = TRUE;
                    if (m_reflection_intensity)
                        m_para->model[i].gruppe[j].material[k].cset.changereflectionintensity = TRUE;
                }
            }
        }
    }
}

void Dialog2::Change2() const {
    int j;

    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);

    const int azitem = id1->GetCount();
    auto *item = new int[azitem];
    const int selitem = id1->GetSelItems(azitem, item);

    for (int z = 0; z < selitem; ++z) {
        for (int i = 0; i < m_para->azmodel; ++i) {
            if (item[z] == m_para->model[i].id) {
                // model
                if (m_diffuse_color)
                    m_para->model[i].cset.changediffusecolor = TRUE;
                if (m_ambience_color)
                    m_para->model[i].cset.changeambiencecolor = TRUE;
                if (m_ambience_intensity)
                    m_para->model[i].cset.changeambienceintensity = TRUE;
                if (m_specular_color)
                    m_para->model[i].cset.changespecularcolor = TRUE;
                if (m_specular_intensity)
                    m_para->model[i].cset.changespecularintensity = TRUE;
                if (m_specular_size)
                    m_para->model[i].cset.changespecularsize = TRUE;
                if (m_reflection_intensity)
                    m_para->model[i].cset.changereflectionintensity = TRUE;
            }
            // Material
            for (j = 0; j < m_para->model[i].azmat; ++j) {
                if (item[z] == m_para->model[i].material[j].id) {
                    if (m_para->model[i].material[j].isclip) {
                        // Decal
                        if (m_decal_intensity)
                            m_para->model[i].material[j].changepercentage = TRUE;
                    } else {
                        if (m_diffuse_color)
                            m_para->model[i].material[j].cset.changediffusecolor = TRUE;
                        if (m_ambience_color)
                            m_para->model[i].material[j].cset.changeambiencecolor = TRUE;
                        if (m_ambience_intensity)
                            m_para->model[i].material[j].cset.changeambienceintensity = TRUE;
                        if (m_specular_color)
                            m_para->model[i].material[j].cset.changespecularcolor = TRUE;
                        if (m_specular_intensity)
                            m_para->model[i].material[j].cset.changespecularintensity = TRUE;
                        if (m_specular_size)
                            m_para->model[i].material[j].cset.changespecularsize = TRUE;
                        if (m_reflection_intensity)
                            m_para->model[i].material[j].cset.changereflectionintensity = TRUE;
                    }
                }
            }
            //Decal
            for (j = 0; j < m_para->model[i].azdecal; ++j) {
                if (item[z] == m_para->model[i].decal[j].id) {
                    if (m_decal_intensity) {
                        if (m_decal_all) {
                            m_para->model[i].decal[j].tochange = TRUE;
                        } else {
                            if (m_para->model[i].decal[j].decaltype == 0)
                                m_para->model[i].decal[j].tochange = TRUE;
                        }
                    }
                }
            }

            //Gruppe
            for (j = 0; j < m_para->model[i].azgroup; ++j) {
                if (item[z] == m_para->model[i].gruppe[j].id) {
                    if (m_diffuse_color)
                        m_para->model[i].gruppe[j].cset.changediffusecolor = TRUE;
                    if (m_ambience_color)
                        m_para->model[i].gruppe[j].cset.changeambiencecolor = TRUE;
                    if (m_ambience_intensity)
                        m_para->model[i].gruppe[j].cset.changeambienceintensity = TRUE;
                    if (m_specular_color)
                        m_para->model[i].gruppe[j].cset.changespecularcolor = TRUE;
                    if (m_specular_intensity)
                        m_para->model[i].gruppe[j].cset.changespecularintensity = TRUE;
                    if (m_specular_size)
                        m_para->model[i].gruppe[j].cset.changespecularsize = TRUE;
                    if (m_reflection_intensity)
                        m_para->model[i].gruppe[j].cset.changereflectionintensity = TRUE;
                }
                for (int k = 0; k < m_para->model[i].gruppe[j].azmat; ++k) {
                    if (item[z] == m_para->model[i].gruppe[j].material[k].id) {
                        if (m_para->model[i].gruppe[j].material[k].isclip) {
                            // Decal
                            if (m_decal_intensity)
                                m_para->model[i].gruppe[j].material[k].changepercentage = TRUE;
                        } else {
                            // Material
                            if (m_diffuse_color)
                                m_para->model[i].gruppe[j].material[k].cset.changediffusecolor = TRUE;
                            if (m_ambience_color)
                                m_para->model[i].gruppe[j].material[k].cset.changeambiencecolor = TRUE;
                            if (m_ambience_intensity)
                                m_para->model[i].gruppe[j].material[k].cset.changeambienceintensity = TRUE;
                            if (m_specular_color)
                                m_para->model[i].gruppe[j].material[k].cset.changespecularcolor = TRUE;
                            if (m_specular_intensity)
                                m_para->model[i].gruppe[j].material[k].cset.changespecularintensity = TRUE;
                            if (m_specular_size)
                                m_para->model[i].gruppe[j].material[k].cset.changespecularsize = TRUE;
                            if (m_reflection_intensity)
                                m_para->model[i].gruppe[j].material[k].cset.changereflectionintensity = TRUE;
                        }
                    }
                }
            }
        }
    }
    delete [] item;
}
