// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Textured_Grid.h"
#include "PDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
PDialog::PDialog(PParameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_para = parameters;
    nummodel = 1;
    maxmodel = 1;
    height = 640;
    width = 480;
    sd_x = GetRegistryValue("Textured Grid HXT", "sd_x", 1);
    sd_y = GetRegistryValue("Textured Grid HXT", "sd_y", 1);
    pix_unit = GetRegistryValue("Textured Grid HXT", "pix_unit", 10.F);
    offsetx = GetRegistryValue("Textured Grid HXT", "offset_x", 0);
    offsety = GetRegistryValue("Textured Grid HXT", "offset_y", 0);
    m_para->m_orientation = GetRegistryValue("Textured Grid HXT", "orientation", 0); //Front
    m_para->modelname = GetRegistryString("Textured Grid HXT", "modelname", "TexturedGrid");
    m_para->use_offset_first = GetRegistryValue("Textured Grid HXT", "use_offset_first", 0);
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Text(pDX, IDC_EDIT1, sd_x);
    DDV_MinMaxInt(pDX, sd_x, 1, hash_constants::big_int);
    DDX_Text(pDX, IDC_EDIT2, sd_y);
    DDV_MinMaxInt(pDX, sd_y, 1, hash_constants::big_int);
    DDX_Text(pDX, IDC_EDIT3, pix_unit);
    DDV_MinMaxFloat(pDX, pix_unit, 0, hash_constants::big_float);
    DDX_Text(pDX, IDC_EDIT4, offsetx);
    DDV_MinMaxInt(pDX, offsetx, 0, width);
    DDX_Text(pDX, IDC_EDIT5, offsety);
    DDV_MinMaxInt(pDX, offsety, 0, height);
    DDX_Text(pDX, IDC_EDIT6, nummodel);
    DDV_MinMaxInt(pDX, nummodel, 1, maxmodel);
    DDX_Radio(pDX, IDC_FRONT, m_para->m_orientation);
    DDX_Text(pDX, IDC_EDIT7, m_para->modelname);
    DDX_Check(pDX, IDC_CHECK1, m_para->use_offset_first);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        //{{AFX_MSG_MAP(PDialog)
        ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnButton1)
        ON_EN_KILLFOCUS(IDC_EDIT1, &PDialog::OnEnKillfocusEdit1)
        ON_EN_KILLFOCUS(IDC_EDIT2, &PDialog::OnEnKillfocusEdit2)
        ON_EN_KILLFOCUS(IDC_EDIT3, &PDialog::OnEnKillfocusEdit3)
        ON_EN_KILLFOCUS(IDC_EDIT4, &PDialog::OnEnKillfocusEdit4)
        ON_EN_KILLFOCUS(IDC_EDIT5, &PDialog::OnEnKillfocusEdit5)
        ON_EN_KILLFOCUS(IDC_EDIT6, &PDialog::OnEnKillfocusEdit6)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
    GetDlgItem(IDOK)->EnableWindow(FALSE);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnOK() {
    UpdateData();
    m_para->num_models = nummodel;
    m_para->offset.Set((float)offsetx / (float)width, (float)offsety / (float)height);
    SetRegistryValue("Textured Grid HXT", "sd_x", sd_x);
    SetRegistryValue("Textured Grid HXT", "sd_y", sd_y);
    SetRegistryValue("Textured Grid HXT", "pix_unit", pix_unit);
    SetRegistryValue("Textured Grid HXT", "offset_x", offsetx);
    SetRegistryValue("Textured Grid HXT", "offset_y", offsety);
    SetRegistryValue("Textured Grid HXT", "orientation", m_para->m_orientation);
    SetRegistryValue("Textured Grid HXT", "use_offset_first", m_para->use_offset_first);
    SetRegistryString("Textured Grid HXT", "modelname", m_para->modelname);
    CPluginDialog::OnOK();
}

void PDialog::OnButton1() {
    String filename;
    if (m_para->clip) {
        delete m_para->clip;
        m_para->clip = nullptr;
        SetDlgItemText(IDC_STATIC1, "");
    }
    bool issequence;
    if (m_para->hclipcache->BrowseClip(filename, &issequence)) {
        m_para->clip = m_para->hclipcache->CreateClip(filename.Get(), issequence);
        height = m_para->clip->GetHeight();
        width = m_para->clip->GetWidth();
        const String temp = filename.GetAbbreviated(FromHandle(GetSafeHwnd()));
        SetDlgItemText(IDC_STATIC1, temp.Get());
        CalculateSD();
        CalculateCopies();
        GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
        GetDlgItem(IDOK)->EnableWindow(TRUE);
    } else {
        GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
        GetDlgItem(IDOK)->EnableWindow(FALSE);
    }
}

void PDialog::CalculateSD() {
    UpdateData();
    m_para->size.x = fast_round((float)width / pix_unit);
    m_para->size.y = fast_round((float)height / pix_unit);
    m_para->subdiv.x = sd_x;
    m_para->subdiv.y = sd_y;
    const String temp = "Bitmap " + (String)width + " x " + (String)height + " GridSize " + (String)m_para->size.x + "x" + (String)m_para->size.y + " Patches " + (String)(sd_x * sd_y);
    SetDlgItemText(IDC_STATIC3, temp.Get());
}

void PDialog::CalculateCopies() {
    UpdateData();
    int modelx, modely;
    if (offsetx > 0)
        modelx = width / offsetx;
    else
        modelx = width;
    if (offsety > 0)
        modely = height / offsety;
    else
        modely = height;
    maxmodel = MIN(modelx, modely);
    if (nummodel > maxmodel)
        nummodel = maxmodel;
    const String temp = "Max Copies " + (String)maxmodel;
    SetDlgItemText(IDC_STATIC_MODELMAX, temp.Get());
}

void PDialog::OnEnKillfocusEdit1() {
    CalculateSD();
}

void PDialog::OnEnKillfocusEdit2() {
    CalculateSD();
}

void PDialog::OnEnKillfocusEdit3() {
    CalculateSD();
}

void PDialog::OnEnKillfocusEdit4() {
    CalculateCopies();
}

void PDialog::OnEnKillfocusEdit5() {
    CalculateCopies();
}

void PDialog::OnEnKillfocusEdit6() {
    UpdateData();
}
