// PDialog.cpp: Implementierungsdatei
//

#include "StdAfx.h"
#include "Multiply.h"
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
    //}}AFX_DATA_INIT
}

void PDialog::DoDataExchange(CDataExchange *pDX) {
    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(PDialog)
    DDX_Text(pDX, IDC_EDIT1, m_para->number);
    DDV_MinMaxInt(pDX, m_para->number, 1, 10000);
    DDX_Text(pDX, IDC_EDIT2, m_para->translate_offset.x);
    DDV_MinMaxDouble(pDX, m_para->translate_offset.x, -hash_constants::max_float, hash_constants::max_float);
    DDX_Text(pDX, IDC_EDIT3, m_para->translate_offset.y);
    DDV_MinMaxFloat(pDX, m_para->translate_offset.y, -hash_constants::max_float, hash_constants::max_float);
    DDX_Text(pDX, IDC_EDIT4, m_para->translate_offset.z);
    DDV_MinMaxFloat(pDX, m_para->translate_offset.z, -hash_constants::max_float, hash_constants::max_float);
    DDX_Text(pDX, IDC_EDIT5, m_para->rotate_offset.x);
    DDV_MinMaxFloat(pDX, m_para->rotate_offset.x, -hash_constants::max_float, hash_constants::max_float);
    DDX_Text(pDX, IDC_EDIT6, m_para->rotate_offset.y);
    DDV_MinMaxFloat(pDX, m_para->rotate_offset.y, -hash_constants::max_float, hash_constants::max_float);
    DDX_Text(pDX, IDC_EDIT7, m_para->rotate_offset.z);
    DDV_MinMaxFloat(pDX, m_para->rotate_offset.z, -hash_constants::max_float, hash_constants::max_float);
    DDX_Text(pDX, IDC_EDIT8, m_para->scale_offset.x);
    DDV_MinMaxFloat(pDX, m_para->scale_offset.x, -hash_constants::max_float, hash_constants::max_float);
    DDX_Text(pDX, IDC_EDIT9, m_para->scale_offset.y);
    DDV_MinMaxFloat(pDX, m_para->scale_offset.y, -hash_constants::max_float, hash_constants::max_float);
    DDX_Text(pDX, IDC_EDIT10, m_para->scale_offset.z);
    DDV_MinMaxFloat(pDX, m_para->scale_offset.z, -hash_constants::max_float, hash_constants::max_float);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PDialog, CDialog)
        //{{AFX_MSG_MAP(PDialog)
        ON_LBN_SELCHANGE(IDC_LIST1, &PDialog::OnSelchangeList1)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten PDialog 

void PDialog::SetCalculatedExtents(HModelCache *hmc) {
    HBone *hb = hmc->GetCurrentBone();
    Vector min, max, extents;
    min.Set(hash_constants::max_float);
    max.Set(-hash_constants::max_float);
    extents.Set(0.F);
    if (hb) {
        const Vector *bounds = hb->GetBounds();
        for (int j = 0; j < 8; ++j) {
            bounds[j].PushMinMax(min, max);
        }
    } else {
        for (HSpline *hsp = hmc->GetHeadSpline(); hsp; hsp = hsp->GetNextSpline()) {
            for (HCP *cp = hsp->GetHeadCP(); cp; cp = cp->GetNext()) {
                const Vector pos = *cp->GetModelPosition();
                pos.PushMinMax(min, max);
                if (cp->IsLoop())
                    break;
            }
        }
    }
    extents.x = hash_math::abs(min.x) + hash_math::abs(max.x);
    extents.y = hash_math::abs(min.y) + hash_math::abs(max.y);
    extents.z = hash_math::abs(min.z) + hash_math::abs(max.z);
    CString temp;
    temp.Format("X: %f", extents.x);
    SetDlgItemText(IDC_STATIC_X, temp);
    temp.Format("Y: %f", extents.y);
    SetDlgItemText(IDC_STATIC_Y, temp);
    temp.Format("Z: %f", extents.z);
    SetDlgItemText(IDC_STATIC_Z, temp);
}

void PDialog::SetCalculatedExtents(HModel *hm_org) {
    Vector min, max, extents;
    min.Set(hash_constants::max_float);
    max.Set(-hash_constants::max_float);
    extents.Set(0.F);
    auto *hmc = (HModelCache *)hm_org->GetCache();
    HChor *hchor = HChor::New();
    HModel *hmodel = hmc->NewInstance(hchor);
    IEPolyModelParms m_iemp;
    m_iemp.m_isbuildmodelmap = false;
    m_iemp.m_isbuildattrarray = false;
    m_iemp.m_isbuildbonelist = false;
    m_iemp.m_isdisplaypercentbar = false;
    m_iemp.m_isbuildmaparray = false;
    m_iemp.m_subtype = ST_16;
    m_iemp.m_ignorevisibility = TRUE;
    IEPolyModel *iemodel = hmodel->BuildExportModel(&m_iemp, Time(), nullptr);
    const UINT count = iemodel->m_polyarray.GetSize();
    IEPoly **polyarray = iemodel->m_polyarray.GetArray();
    for (UINT i = 0; i < count; ++i) {
        Vector p0 = iemodel->m_vertexlist[polyarray[i]->m_vertexid[0]];
        p0.PushMinMax( min, max);
        p0 = iemodel->m_vertexlist[polyarray[i]->m_vertexid[1]];
        p0.PushMinMax( min, max);
        p0 = iemodel->m_vertexlist[polyarray[i]->m_vertexid[2]];
        p0.PushMinMax( min, max);
    }
    DeleteIEModel(iemodel);
    HProject::DeleteHandle(hchor);
    extents.x = hash_math::abs(min.x) + hash_math::abs(max.x);
    extents.y = hash_math::abs(min.y) + hash_math::abs(max.y);
    extents.z = hash_math::abs(min.z) + hash_math::abs(max.z);
    extents *= hm_org->GetTransform()->GetScale()->GetValue();
    CString temp;
    temp.Format("X: %f", extents.x);
    SetDlgItemText(IDC_STATIC_X, temp);
    temp.Format("Y: %f", extents.y);
    SetDlgItemText(IDC_STATIC_Y, temp);
    temp.Format("Z: %f", extents.z);
    SetDlgItemText(IDC_STATIC_Z, temp);
}

void PDialog::OnSelchangeList1() {
    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    CString temp;
    temp.Format("Import \'%s\'", ((HModelCache *)id1->GetItemDataPtr(id1->GetCurSel()))->GetName());
    SetDlgItemText(IDC_STATIC1, temp);
    SetCalculatedExtents((HModelCache *)id1->GetItemDataPtr(id1->GetCurSel()));
}

BOOL PDialog::OnInitDialog() {
    CPluginDialog::OnInitDialog();
    CString temp;
    auto *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    if (m_para->mode) {
        id1->ShowWindow(false);
        temp.Format("Import \'%s\'", m_para->hmc->GetName());
        SetDlgItemText(IDC_STATIC1, temp);
        SetCalculatedExtents(m_para->hm);
    } else {
        auto *id2 = (CEdit *)GetDlgItem(IDC_EDIT2);
        id2->ShowWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT3);
        id2->ShowWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT4);
        id2->ShowWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT5);
        id2->ShowWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT6);
        id2->ShowWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT7);
        id2->ShowWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT8);
        id2->ShowWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT9);
        id2->ShowWindow(false);
        id2 = (CEdit *)GetDlgItem(IDC_EDIT10);
        id2->ShowWindow(false);
        auto *id3 = (CStatic *)GetDlgItem(IDC_STATIC3);
        id3->ShowWindow(false);
        id3 = (CStatic *)GetDlgItem(IDC_STATIC4);
        id3->ShowWindow(false);
        id3 = (CStatic *)GetDlgItem(IDC_STATIC5);
        id3->ShowWindow(false);
        id3 = (CStatic *)GetDlgItem(IDC_STATIC6);
        id3->ShowWindow(false);
        id3 = (CStatic *)GetDlgItem(IDC_STATIC7);
        id3->ShowWindow(false);
        id3 = (CStatic *)GetDlgItem(IDC_STATIC8);
        id3->ShowWindow(false);

        HObjectCacheContainer *hocc = m_para->hproject->GetChildObjectCacheContainer();
        for (HHashObject *hmc = hocc->GetChildModelCache(); hmc; hmc = hmc->GetSibling()) {
            if (hmc->GetObjectType() == HOT_MODEL) {
                temp.Format("%s", hmc->GetName());
                const int index = id1->AddString(temp);
                id1->SetItemDataPtr(index, hmc);
            }
        }
        id1->SetCurSel(0);
        temp.Format("Import \'%s\'", ((HModelCache *)id1->GetItemDataPtr(id1->GetCurSel()))->GetName());
        SetDlgItemText(IDC_STATIC1, temp);
        SetCalculatedExtents((HModelCache *)id1->GetItemDataPtr(id1->GetCurSel()));
    }
    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void PDialog::OnOK() {

    const CListBox *id1 = (CListBox *)GetDlgItem(IDC_LIST1);
    UpdateData(true);
    if (!m_para->mode)
        m_para->hmc = (HModelCache *)id1->GetItemDataPtr(id1->GetCurSel());

    CPluginDialog::OnOK();
}
