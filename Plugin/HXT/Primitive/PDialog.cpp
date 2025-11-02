// PDialog.cpp: Implementierungsdatei
//
#include "StdAfx.h"
#include "primitive.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
PDialog::PDialog(PParameters *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_parameters = parameters;
    //}}AFX_DATA_INIT

    m_parameters->m_radius1 = GetRegistryValue("Primitive HXT", "Radius1", 1.F);
    m_parameters->m_segment1 = GetRegistryValue("Primitive HXT", "Segment1", 12);
    m_parameters->m_radius2 = GetRegistryValue("Primitive HXT", "Radius2", 0.1F);
    m_parameters->m_segment2 = GetRegistryValue("Primitive HXT", "Segment2", 12);
    m_parameters->m_segment3 = GetRegistryValue("Primitive HXT", "Segment3", 1);
    m_parameters->m_hoehe = GetRegistryValue("Primitive HXT", "Height", 1.F);
    m_parameters->m_breite = GetRegistryValue("Primitive HXT", "Width", 1.F);
    m_parameters->m_tiefe = GetRegistryValue("Primitive HXT", "Depth", 1.F);
    m_parameters->m_turn = GetRegistryValue("Primitive HXT", "Turn", 1);
    m_parameters->m_magnitude = GetRegistryValue("Primitive HXT", "Magnitude", 100.F);
    m_parameters->m_magnitude2 = GetRegistryValue("Primitive HXT", "Magnitude2", 100.F);
    m_parameters->m_type = GetRegistryValue("Primitive HXT", "Type", 0);
    m_parameters->m_richtung = GetRegistryValue("Primitive HXT", "Direction", FALSE);
    m_parameters->m_typcp = GetRegistryValue("Primitive HXT", "Typcp", FALSE);
    m_parameters->m_subdiv = GetRegistryValue("Primitive HXT", "Subdivision", 1);
    m_parameters->m_autobone = FALSE;
    aHbmBild[0] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP1));
    aHbmBild[1] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP2));
    aHbmBild[2] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP3));
    aHbmBild[3] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP4));
    aHbmBild[4] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP5));
    aHbmBild[5] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP6));
    aHbmBild[6] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP7));
    aHbmBild[7] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP8));
    aHbmBild[8] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP9));
    aHbmBild[9] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP10));
    aHbmBild[10] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP11));
    aHbmBild[11] = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP12));
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    //   DDX_Control(pDX, IDC_STATIC_BITMAP, c_bitmap);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT1, m_parameters->m_radius1);
    DDV_MinMaxFloat(pDX, m_parameters->m_radius1, 1e-6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT2, m_parameters->m_segment1);
    DDV_MinMaxInt(pDX, m_parameters->m_segment1, 3, 1000);
    DDX_Text(pDX, IDC_EDIT3, m_parameters->m_radius2);
    DDV_MinMaxFloat(pDX, m_parameters->m_radius2, 1e-6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT4, m_parameters->m_segment2);
    DDV_MinMaxInt(pDX, m_parameters->m_segment2, 3, 1000);
    DDX_Text(pDX, IDC_EDIT5, m_parameters->m_hoehe);
    DDV_MinMaxFloat(pDX, m_parameters->m_hoehe, 1e-6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT6, m_parameters->m_breite);
    DDV_MinMaxFloat(pDX, m_parameters->m_breite, 1e-6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT7, m_parameters->m_tiefe);
    DDV_MinMaxFloat(pDX, m_parameters->m_tiefe, 1e-6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT8, m_parameters->m_turn);
    DDV_MinMaxInt(pDX, m_parameters->m_turn, 1, 1000);
    DDX_Text(pDX, IDC_EDIT9, m_parameters->m_magnitude);
    DDV_MinMaxFloat(pDX, m_parameters->m_magnitude, 1e-6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT11, m_parameters->m_magnitude2);
    DDV_MinMaxFloat(pDX, m_parameters->m_magnitude2, 1e-6F, 1e6F);
    DDX_Text(pDX, IDC_EDIT10, m_parameters->m_segment3);
    DDV_MinMaxInt(pDX, m_parameters->m_segment3, 0, 1000);
    DDX_Text(pDX, IDC_EDIT12, m_parameters->m_subdiv);
    DDV_MinMaxInt(pDX, m_parameters->m_subdiv, 0, 100);
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
    //{{AFX_MSG_MAP(PDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, &PDialog::OnSelchangeCombo1)
    ON_BN_CLICKED(IDC_CHECK1, &PDialog::OnCheck1)
    ON_BN_CLICKED(IDC_CHECK2, &PDialog::OnCheck2)
    ON_EN_UPDATE(IDC_EDIT2, &PDialog::OnUpdateEdit2)
    ON_EN_UPDATE(IDC_EDIT4, &PDialog::OnUpdateEdit4)
    ON_EN_UPDATE(IDC_EDIT8, &PDialog::OnUpdateEdit8)
    ON_EN_UPDATE(IDC_EDIT10, &PDialog::OnUpdateEdit10)
    ON_EN_UPDATE(IDC_EDIT12, &PDialog::OnUpdateEdit12)
    ON_BN_CLICKED(IDC_CHECK3, &PDialog::OnCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &PDialog::OnCheck4)
    ON_BN_CLICKED(IDC_CHECK5, &PDialog::OnCheck5)
    ON_BN_CLICKED(IDC_BUTTON2, &PDialog::OnButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &PDialog::OnButton3)
    ON_EN_KILLFOCUS(IDC_EDIT2, &PDialog::OnKillfocusEdit2)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

void PDialog::OnOK() {
    CPluginDialog::OnOK();
    SetRegistryValue("Primitive HXT", "Radius1", m_parameters->m_radius1);
    SetRegistryValue("Primitive HXT", "Segment1", m_parameters->m_segment1);
    SetRegistryValue("Primitive HXT", "Radius2", m_parameters->m_radius2);
    SetRegistryValue("Primitive HXT", "Segment2", m_parameters->m_segment2);
    SetRegistryValue("Primitive HXT", "Segment3", m_parameters->m_segment3);
    SetRegistryValue("Primitive HXT", "Height", m_parameters->m_hoehe);
    SetRegistryValue("Primitive HXT", "Width", m_parameters->m_breite);
    SetRegistryValue("Primitive HXT", "Depth", m_parameters->m_tiefe);
    SetRegistryValue("Primitive HXT", "Turn", m_parameters->m_turn);
    SetRegistryValue("Primitive HXT", "Magnitude", m_parameters->m_magnitude);
    SetRegistryValue("Primitive HXT", "Magnitude2", m_parameters->m_magnitude2);
    SetRegistryValue("Primitive HXT", "Type", m_parameters->m_type);
    SetRegistryValue("Primitive HXT", "Direction", m_parameters->m_richtung);
    SetRegistryValue("Primitive HXT", "Typcp", m_parameters->m_typcp);
    SetRegistryValue("Primitive HXT", "Subdivision", m_parameters->m_subdiv);
    for (const auto &i: aHbmBild)
        DeleteObject(i);

}

void PDialog::OnCancel() {
    for (const auto &i: aHbmBild)
        DeleteObject(i);
    CPluginDialog::OnCancel();
}

void PDialog::OnSelchangeCombo1() {
    const CComboBox *id = (CComboBox *)GetDlgItem(IDC_COMBO1);
    SetItems(id->GetCurSel());
}

void PDialog::OnCheck1() {
    m_parameters->m_richtung = FALSE;
    auto *id = (CButton *)GetDlgItem(IDC_CHECK1);
    id->SetCheck(TRUE);
    id = (CButton *)GetDlgItem(IDC_CHECK2);
    id->SetCheck(FALSE);
}

void PDialog::OnCheck2() {
    m_parameters->m_richtung = TRUE;
    auto *id = (CButton *)GetDlgItem(IDC_CHECK1);
    id->SetCheck(FALSE);
    id = (CButton *)GetDlgItem(IDC_CHECK2);
    id->SetCheck(TRUE);
}

void PDialog::OnCheck3() {
    m_parameters->m_typcp = FALSE;
    auto *id = (CButton *)GetDlgItem(IDC_CHECK3);
    id->SetCheck(TRUE);
    id = (CButton *)GetDlgItem(IDC_CHECK4);
    id->SetCheck(FALSE);
}

void PDialog::OnCheck4() {
    m_parameters->m_typcp = TRUE;
    auto *id = (CButton *)GetDlgItem(IDC_CHECK3);
    id->SetCheck(FALSE);
    id = (CButton *)GetDlgItem(IDC_CHECK4);
    id->SetCheck(TRUE);
}

void PDialog::OnCheck5() {
    const CButton *id = (CButton *)GetDlgItem(IDC_CHECK5);
    m_parameters->m_autobone = id->GetCheck();
}

BOOL PDialog::OnInitDialog() {
    CButton *id3;

    CPluginDialog::OnInitDialog();

    auto *id = (CComboBox *)GetDlgItem(IDC_COMBO1);
    id->AddString("Circle");
    id->AddString("Spiral");
    id->AddString("Cube");
    id->AddString("Cylinder");
    id->AddString("Cylinder closed");
    id->AddString("Ring");
    id->AddString("Spring");
    id->AddString("Pyramid stump");
    id->AddString("Pyramid");
    id->AddString("Tetrahedron");
    id->AddString("Sphere");
    id->AddString("Subdivided Cube");
    if (m_parameters->m_richtung) {
        id3 = (CButton *)GetDlgItem(IDC_CHECK1);
        id3->SetCheck(FALSE);
        id3 = (CButton *)GetDlgItem(IDC_CHECK2);
        id3->SetCheck(TRUE);
    } else {
        id3 = (CButton *)GetDlgItem(IDC_CHECK1);
        id3->SetCheck(TRUE);
        id3 = (CButton *)GetDlgItem(IDC_CHECK2);
        id3->SetCheck(FALSE);
    }
    if (m_parameters->m_typcp) {
        id3 = (CButton *)GetDlgItem(IDC_CHECK3);
        id3->SetCheck(FALSE);
        id3 = (CButton *)GetDlgItem(IDC_CHECK4);
        id3->SetCheck(TRUE);
    } else {
        id3 = (CButton *)GetDlgItem(IDC_CHECK4);
        id3->SetCheck(FALSE);
        id3 = (CButton *)GetDlgItem(IDC_CHECK3);
        id3->SetCheck(TRUE);
    }
    id3 = (CButton *)GetDlgItem(IDC_CHECK5);
    id3->SetCheck(FALSE);
    id->SetCurSel(m_parameters->m_type);
    SetItems(m_parameters->m_type);

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

/*
void PDialog::SetBild() {
   CComboBox *id;
   HBITMAP hbm1=nullptr;
   HBITMAP hbm_old=nullptr;

   id = (CComboBox *)GetDlgItem(IDC_COMBO1);
   switch (id->GetCurSel()) {
   case 0:
      //		 Kreis
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP1));	   //works on the mac
      break;
   case 1:
      //	     Spirale
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP2));
      break;
   case 2:
      //	     Rechteck
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP3));
      break;
   case 3:
      //	     Zylinder
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP4));
      break;
   case 4:
      //	     Zylinder closed
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP11));
      break;
   case 5:
      //	     Ring
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP5));
      break;
   case 6:
      //	     Feder
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP6));
      break;
   case 7:
      //	     Pyramidenstumpf
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP7));
      break;
   case 8:
      //	     Pyramide
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP8));
      break;
   case 9:
      //	     Sechseck
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP9));
      break;
   case 10:
      //	     Kugel
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP10));
      break;
   case 11:
      //	     subdivided cube
      hbm1 = LoadBitmap(m_parameters->hinstance,MAKEINTRESOURCE(IDB_BITMAP12));
      break;
   }
   if (hbm1) {
      hbm_old = c_bitmap.SetBitmap(hbm1);
   }
}
*/

void PDialog::SetItems(int index) {
    CEdit *id2;
    CButton *id3;
    auto *bild = (CStatic *)GetDlgItem(IDC_STATIC_BITMAP);

    switch (index) {
        case 0: //Kreis
            bild->SetBitmap(aHbmBild[0]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = FALSE;
            m_parameters->m_type = 0;
            break;
        case 1: //Spirale
            bild->SetBitmap(aHbmBild[1]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = FALSE;
            m_parameters->m_type = 1;
            break;
        case 2: //Cube
            bild->SetBitmap(aHbmBild[2]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = TRUE;
            m_parameters->m_type = 2;
            m_parameters->m_magnitude = 100.F;
            break;
        case 3: //Zylinder
            bild->SetBitmap(aHbmBild[3]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = FALSE;
            m_parameters->m_type = 3;
            break;
        case 4: //Zylinder closed
            bild->SetBitmap(aHbmBild[10]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = FALSE;
            m_parameters->m_type = 4;
            break;
        case 5: //Ring
            bild->SetBitmap(aHbmBild[4]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(TRUE);
            if (m_parameters->m_segment1 < 3) {
                m_parameters->m_segment1 = 3;
                SetDlgItemText(IDC_EDIT2, "3");
            }
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = FALSE;
            m_parameters->m_type = 5;
            break;
        case 6: //Feder
            bild->SetBitmap(aHbmBild[5]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(TRUE);
            if (m_parameters->m_segment1 < 3) {
                m_parameters->m_segment1 = 3;
                SetDlgItemText(IDC_EDIT2, "3");
            }
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = FALSE;
            m_parameters->m_type = 6;
            break;
        case 7: //Pyramidenstumpf
            bild->SetBitmap(aHbmBild[6]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = TRUE;
            m_parameters->m_type = 7;
            m_parameters->m_magnitude = 100.F;
            break;
        case 8: //Pyramide
            bild->SetBitmap(aHbmBild[7]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = TRUE;
            m_parameters->m_type = 8;
            m_parameters->m_magnitude = 100.F;
            break;
        case 9: //Sechseck
            bild->SetBitmap(aHbmBild[8]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(FALSE);
            if (m_parameters->m_segment1 != 4) {
                m_parameters->m_segment1 = 4;
                SetDlgItemText(IDC_EDIT2, "4");
            }
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = TRUE;
            m_parameters->m_type = 9;
            m_parameters->m_magnitude = 100.F;
            break;
        case 10: //Kugel
            bild->SetBitmap(aHbmBild[9]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(FALSE);
            m_parameters->m_typcp = FALSE;
            m_parameters->m_type = 10;
            break;
        case 11: //Cube subdivided
            bild->SetBitmap(aHbmBild[11]);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT1);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
            id2->EnableWindow(TRUE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
            id2->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK1);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK3);
            id3->SetCheck(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK4);
            id3->SetCheck(TRUE);
            id3 = (CButton *)GetDlgItem(IDC_CHECK5);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON2);
            id3->EnableWindow(FALSE);
            id3 = (CButton *)GetDlgItem(IDC_BUTTON3);
            id3->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT11);
            id2->EnableWindow(FALSE);
            id2 = (CEdit *)GetDlgItem(IDC_EDIT12);
            id2->EnableWindow(TRUE);
            m_parameters->m_typcp = TRUE;
            m_parameters->m_type = 11;
            m_parameters->m_magnitude = 100.F;
            break;
    }
    UpdateData(false);
    CalculatePatch();
}

void PDialog::CalculatePatch() {
    long az_patches;
    int para1;
    CString buffer;
    div_t div_result;

    UpdateData(true);
    switch (m_parameters->m_type) {
        case 2:SetDlgItemText(IDC_STATIC10, "6");
            break;
        case 3:
            az_patches = m_parameters->m_segment1 * m_parameters->m_segment3;
            buffer.Format("%u", az_patches);
            SetDlgItemText(IDC_STATIC10, buffer);
            break;
        case 4:
            az_patches = m_parameters->m_segment1 * m_parameters->m_segment3 + 2 * m_parameters->m_segment1;
            buffer.Format("%u", az_patches);
            SetDlgItemText(IDC_STATIC10, buffer);
            break;
        case 5:
            az_patches = m_parameters->m_segment1 * m_parameters->m_segment2;
            buffer.Format("%u", az_patches);
            SetDlgItemText(IDC_STATIC10, buffer);
            break;
        case 6:
            az_patches = m_parameters->m_segment1 * m_parameters->m_segment2 * m_parameters->m_turn;
            buffer.Format("%u", az_patches);
            SetDlgItemText(IDC_STATIC10, buffer);
            break;
        case 7:SetDlgItemText(IDC_STATIC10, "6");
            break;
        case 8:SetDlgItemText(IDC_STATIC10, "4");
            break;
        case 9:SetDlgItemText(IDC_STATIC10, "8");
            break;
        case 10:
            para1 = m_parameters->m_segment1;
            div_result = div(para1, 4);
            if (div_result.rem != 0) {
                if (div_result.rem != 1) {
                    para1 = (div_result.quot + 1) * 4;
                } else {
                    para1 = div_result.quot * 4;
                }
            }
            m_parameters->m_segment1 = para1;
            az_patches = para1 * para1 * 0.5F;
            buffer.Format("%u", az_patches);
            SetDlgItemText(IDC_STATIC10, buffer);
            UpdateData(false);
            break;
        case 11:
            az_patches = m_parameters->m_subdiv + 1;
            az_patches *= az_patches;
            az_patches *= 6;
            buffer.Format("%u", az_patches);
            SetDlgItemText(IDC_STATIC10, buffer);
            break;
        default:
            break;
    }
}

void PDialog::OnUpdateEdit2() {
    if (m_parameters->m_type != 10)
        CalculatePatch();
}

void PDialog::OnUpdateEdit4() {
    CalculatePatch();
}

void PDialog::OnUpdateEdit8() {
    CalculatePatch();
}

void PDialog::OnUpdateEdit10() {
    CalculatePatch();
}

void PDialog::OnUpdateEdit12() {
    CalculatePatch();
}

static float GetMagnitude(const int num) {
    if (num > 16)
        return 1.00;
    constexpr float a = 1.0496677F, b = -2.6000651F, c = 0.48547743F;

    return a / (1.F + b * hash_math::exp(-c * num));
}

void PDialog::OnButton2() {
    // TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    UpdateData(true);
    m_parameters->m_magnitude = GetMagnitude(m_parameters->m_segment1) * 100;
    UpdateData(false);
}

void PDialog::OnButton3() {
    // TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
    UpdateData(true);
    m_parameters->m_magnitude2 = GetMagnitude(m_parameters->m_segment2) * 100;
    UpdateData(false);
}

void PDialog::OnKillfocusEdit2() {
    if (m_parameters->m_type == 10)
        CalculatePatch();
}
