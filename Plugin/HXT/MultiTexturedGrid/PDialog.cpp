// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "MultiTexGrid.h"
#include "PDialog.h"
#include "StringLi.h"
#include "mlistctl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

PDialog::PDialog(PParameter *parameters) : CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())) {
    //{{AFX_DATA_INIT(PDialog)
    m_para = parameters;
    pix_unit = GetRegistryValue("GridImages HXT", "pix_unit", 10.F);
    sd_x = GetRegistryValue("GridImages HXT", "sd_x", 1);
    sd_y = GetRegistryValue("GridImages HXT", "sd_y", 1);
    m_para->m_orientation = GetRegistryValue("GridImages HXT", "orientation", 0); //Front
    m_para->modelname = GetRegistryString("GridImages HXT", "modelname", "GridImage");
    m_para->add_to_chor = GetRegistryValue("GridImages HXT", "addtochor", 0);
    m_para->fpos.x = GetRegistryValue("GridImages HXT", "fpos_x", 0);
    m_para->fpos.y = GetRegistryValue("GridImages HXT", "fpos_y", 0);
    m_para->fpos.z = GetRegistryValue("GridImages HXT", "fpos_z", 0);
    m_para->pos_ofs.x = GetRegistryValue("GridImages HXT", "ofs_x", 0);
    m_para->pos_ofs.y = GetRegistryValue("GridImages HXT", "ofs_y", 0);
    m_para->pos_ofs.z = GetRegistryValue("GridImages HXT", "ofs_z", 0);
    m_para->use_model = GetRegistryValue("GridImages HXT", "modelorlayer", 0);
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Control(pDX, IDC_IMAGELIST, m_listctrl);
    DDX_Text(pDX, IDC_EDIT3, pix_unit);
    DDV_MinMaxFloat(pDX, pix_unit, 0, hash_constants::big_float);
    DDX_Text(pDX, IDC_EDIT1, sd_x);
    DDV_MinMaxInt(pDX, sd_x, 1, hash_constants::big_int);
    DDX_Text(pDX, IDC_EDIT2, sd_y);
    DDV_MinMaxInt(pDX, sd_y, 1, hash_constants::big_int);
    DDX_Text(pDX, IDC_EDIT4, m_para->fpos.x);
    DDX_Text(pDX, IDC_EDIT5, m_para->fpos.y);
    DDX_Text(pDX, IDC_EDIT8, m_para->fpos.z);
    DDX_Text(pDX, IDC_EDIT9, m_para->pos_ofs.x);
    DDX_Text(pDX, IDC_EDIT10, m_para->pos_ofs.y);
    DDX_Text(pDX, IDC_EDIT11, m_para->pos_ofs.z);
    DDX_Check(pDX, IDC_CHECK1, m_para->add_to_chor);
    DDX_Radio(pDX, IDC_FRONT, m_para->m_orientation);
    DDX_Text(pDX, IDC_EDIT7, m_para->modelname);
    DDX_Radio(pDX, IDC_RADIO1, m_para->use_model);
    DDX_Check(pDX, IDC_CHECK2, m_para->create_cookie);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        //{{AFX_MSG_MAP(PDialog)
        ON_BN_CLICKED(IDC_BUTTON1, &PDialog::OnButton1)
        ON_BN_CLICKED(IDC_BUTTON2, &PDialog::OnButton2)
        ON_BN_CLICKED(IDC_CHECK1, &PDialog::OnCheck1)
        ON_EN_KILLFOCUS(IDC_EDIT1, &PDialog::OnEnKillfocusEdit1)
        ON_EN_KILLFOCUS(IDC_EDIT2, &PDialog::OnEnKillfocusEdit2)
        ON_EN_KILLFOCUS(IDC_EDIT3, &PDialog::OnEnKillfocusEdit3)
        ON_EN_KILLFOCUS(IDC_EDIT4, &PDialog::OnEnKillfocusEdit4)
        ON_EN_KILLFOCUS(IDC_EDIT5, &PDialog::OnEnKillfocusEdit5)
        ON_EN_KILLFOCUS(IDC_EDIT5, &PDialog::OnEnKillfocusEdit8)
        ON_EN_KILLFOCUS(IDC_EDIT5, &PDialog::OnEnKillfocusEdit9)
        ON_EN_KILLFOCUS(IDC_EDIT5, &PDialog::OnEnKillfocusEdit10)
        ON_EN_KILLFOCUS(IDC_EDIT5, &PDialog::OnEnKillfocusEdit11)
        ON_EN_KILLFOCUS(IDC_EDIT6, &PDialog::OnEnKillfocusEdit6)
        ON_COMMAND(ID__ADDIMAGES, &PDialog::OnAddEntry)
        ON_COMMAND(ID__REMOVESELECTED, &PDialog::OnRemoveEntry)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CRect listsize;
    m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT); // | LVS_EX_GRIDLINES);
    m_listctrl.GetWindowRect(&listsize);
    ScreenToClient(&listsize);
    m_listctrl.DeleteColumn(0);
    m_listctrl.DeleteColumn(0);
    m_listctrl.InsertColumn(0, "Image", LVCFMT_LEFT, listsize.Width() - 165);
    m_listctrl.InsertColumn(1, "Imagesize", LVCFMT_CENTER, 60);
    m_listctrl.InsertColumn(2, "Gridsize", LVCFMT_CENTER, 60);
    m_listctrl.InsertColumn(3, "Seq", LVCFMT_CENTER, 40);
    GetDlgItem(IDC_EDIT4)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT5)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT8)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT9)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT10)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT11)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDOK)->EnableWindow(FALSE);
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnOK() {
    UpdateData();
    m_para->subdiv.Set(sd_x, sd_y);
    if (m_listctrl.m_bOrderChanged) {
        int azimg = m_para->images.size();
        std::vector<ImageParameters> tempimages;
        for (int i = 0; i < azimg; ++i) {
            String tfilename = m_listctrl.GetItemText(i, 0);
            for (int j = 0; j < azimg; ++j) {
                if (tfilename == m_para->images[j].filename) {
                    tempimages.push_back(m_para->images[j]);
                }
            }
        }
        m_para->images.clear();
        azimg = tempimages.size();
        for (int i = 0; i < azimg; ++i) {
            m_para->images.push_back(tempimages[i]);
        }
    }
    SetRegistryValue("GridImages HXT", "pix_unit", pix_unit);
    SetRegistryValue("GridImages HXT", "sd_x", sd_x);
    SetRegistryValue("GridImages HXT", "sd_y", sd_y);
    SetRegistryValue("GridImages HXT", "orientation", m_para->m_orientation); //Front
    SetRegistryString("GridImages HXT", "modelname", m_para->modelname);
    SetRegistryValue("GridImages HXT", "addtochor", m_para->add_to_chor);
    SetRegistryValue("GridImages HXT", "fpos_x", m_para->fpos.x);
    SetRegistryValue("GridImages HXT", "fpos_y", m_para->fpos.y);
    SetRegistryValue("GridImages HXT", "fpos_z", m_para->fpos.z);
    SetRegistryValue("GridImages HXT", "ofs_x", m_para->pos_ofs.x);
    SetRegistryValue("GridImages HXT", "ofs_y", m_para->pos_ofs.y);
    SetRegistryValue("GridImages HXT", "ofs_z", m_para->pos_ofs.z);
    SetRegistryValue("GridImages HXT", "modelorlayer", m_para->use_model);
    CPluginDialog::OnOK();
}

void PDialog::OnCheck1() {
    UpdateData();
    GetDlgItem(IDC_EDIT4)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT5)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT8)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT9)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT10)->EnableWindow(m_para->add_to_chor);
    GetDlgItem(IDC_EDIT11)->EnableWindow(m_para->add_to_chor);
}

void PDialog::OnButton1() {
    bool issequence = false;
    StringList *filenames = BrowseImages(&issequence);
    if (filenames) {
        ImageParameters temp;
        for (POSITION namepos = filenames->GetHeadPosition(); namepos;) {
            String filename = filenames->GetNext(namepos);
            temp.filename = filename;
            temp.issequence = issequence;
            HClip *clip = m_para->hclipcache->CreateClip(filename.Get(), issequence);
            if (!clip) {
                clip = m_para->hclipcache->CreateClip(filename.Get(), !issequence);
                if (clip)
                    temp.issequence = !issequence;
            }
            if (clip) {
                height = clip->GetHeight();
                width = clip->GetWidth();
                delete clip;
                temp.size.Set(width, height);
                temp.gridsize.Set(fast_round((float)width / pix_unit), fast_round((float)height / pix_unit));
                m_para->images.push_back(temp);
            }
        }
        delete filenames;
        UpdateListbox();
        GetDlgItem(IDOK)->EnableWindow(TRUE);
    }
}

void PDialog::OnButton2() {
    m_listctrl.DeleteAllItems();
    m_para->images.clear();
    GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void AutoSetColumnWidth(CListCtrl &list, const int iColumn) {

    list.SetColumnWidth(iColumn, LVSCW_AUTOSIZE);
    const int nAutoWidth = list.GetColumnWidth(iColumn);
    list.SetColumnWidth(iColumn, LVSCW_AUTOSIZE_USEHEADER);
    const int nAutoHeaderWidth = list.GetColumnWidth(iColumn);
    list.SetColumnWidth(iColumn, MAX(nAutoWidth, nAutoHeaderWidth));
}

void PDialog::UpdateListbox() {
    int azimg = m_para->images.size();
    if (m_listctrl.m_bOrderChanged) {
        std::vector<ImageParameters> tempimages;
        for (int i = 0; i < azimg; ++i) {
            String tfilename = m_listctrl.GetItemText(i, 0);
            for (int j = 0; j < azimg; ++j) {
                if (tfilename == m_para->images[j].filename) {
                    tempimages.push_back(m_para->images[j]);
                }
            }
        }
        m_para->images.clear();
        azimg = tempimages.size();
        for (int i = 0; i < azimg; ++i) {
            m_para->images.push_back(tempimages[i]);
        }
    }
    m_listctrl.DeleteAllItems();
//    String filename;
    m_listctrl.SetItemCount(azimg);
    for (int i = 0; i < azimg; ++i) {
        ImageParameters temp = m_para->images[i];
        m_listctrl.InsertItem(i, temp.filename.Get());
        String tempstring = (String)temp.size.x + " x " + (String)temp.size.y;
        m_listctrl.SetItemText(i, 1, tempstring.Get());
        tempstring = (String)temp.gridsize.x + " x " + (String)temp.gridsize.y;
        m_listctrl.SetItemText(i, 2, tempstring.Get());
        if (temp.issequence)
            tempstring = "x";
        else
            tempstring = "";
        m_listctrl.SetItemText(i, 3, tempstring.Get());
    }
    AutoSetColumnWidth(m_listctrl, 0);
    AutoSetColumnWidth(m_listctrl, 1);
    AutoSetColumnWidth(m_listctrl, 2);
    AutoSetColumnWidth(m_listctrl, 3);
    m_listctrl.m_bOrderChanged = FALSE;
}

void PDialog::CalculateGrid() {
    UpdateData();
    const int azimg = m_para->images.size();
    for (int i = 0; i < azimg; ++i) {
        const int l_width = m_para->images[i].size.x;
        const int l_height = m_para->images[i].size.y;
        m_para->images[i].gridsize.Set(fast_round((float)l_width / pix_unit), fast_round((float)l_height / pix_unit));
    }
}

void PDialog::OnEnKillfocusEdit1() {
    UpdateData();
}

void PDialog::OnEnKillfocusEdit2() {
    UpdateData();
}

void PDialog::OnEnKillfocusEdit3() {
    CalculateGrid();
    UpdateListbox();
}

void PDialog::OnEnKillfocusEdit4() {
    UpdateData();
}

void PDialog::OnEnKillfocusEdit5() {
    UpdateData();
}

void PDialog::OnEnKillfocusEdit6() {
    UpdateData();
}

void PDialog::OnEnKillfocusEdit8() {
    UpdateData();
}

void PDialog::OnEnKillfocusEdit9() {
    UpdateData();
}

void PDialog::OnEnKillfocusEdit10() {
    UpdateData();
}

void PDialog::OnEnKillfocusEdit11() {
    UpdateData();
}

void PDialog::OnRemoveEntry() {
    const int selected = m_listctrl.GetSelectionMark();
    if (selected > -1) {
        m_listctrl.DeleteItem(selected);
        m_listctrl.m_bOrderChanged = TRUE;
    }
}

void PDialog::OnAddEntry() {
    OnButton1();
}
