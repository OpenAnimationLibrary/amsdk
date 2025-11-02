// MaPD.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "MaPD.h"
#include "SDK/HPropert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaPDApp

BEGIN_MESSAGE_MAP(CMaPDApp, CWinApp)
    //{{AFX_MSG_MaPD(CMaPDApp)
    // HINWEIS - Hier werden MaPDping-Makros vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG_MaPD
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaPDApp Konstruktion

CMaPDApp::CMaPDApp() = default;

CMaPDApp::~CMaPDApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMaPDApp-Objekt

CMaPDApp theApp;

BOOL CMaPDApp::GetDecalList(HModelCache *hmc, CArrayEx<MyDecal, MyDecal> &decallist) {
    HDecalContainer *hdc = hmc->GetChildDecalContainer();
    if (!hdc)
        return FALSE;

    Vector uvs[15];
    for (auto &uv: uvs) {
        uv.SetZero();
    }
    for (HDecal *hd = hdc->GetChildDecal(); hd; hd = (HDecal *)hd->GetSiblingSame()) {
        MyDecal _decal;
        _decal.hd = hd;
        _decal.isdeletet = false;
        _decal.stamp.RemoveAll();
        HDecalStampContainer *hdsc = hd->GetChildDecalStampContainer();
        for (HDecalStamp *hds = hdsc->GetChildDecalStamp(); hds; hds = (HDecalStamp *)hds->GetSiblingSame()) {
            MyStamp _stamp;
            _stamp.hds = hds;
            _stamp.stampdata.RemoveAll();
            for (HBasePatchUV *hbpuv = hds->GetFirstPatchUV(); hbpuv; hbpuv = hds->GetNextPatchUV(hbpuv)) {
                MyStampData _stampdata;
                _stampdata.hp = hbpuv->GetPatch();
                hbpuv->GetUVs(uvs);
                for (int i = 0; i < 15; ++i) {
                    _stampdata.uvs[i] = uvs[i];
                }
                _stamp.stampdata.Add(_stampdata);
            }
            _decal.stamp.Add(_stamp);
        }
        decallist.Add(_decal);
    }
    return TRUE;
}

bool CMaPDApp::IsMatchDecal(const MyDecal &org, const MyDecal &check) {
    HDecalClip *hdc_o, *hdc_c;
    for (hdc_o = org.hd->GetChildDecalClipContainer()->GetChildDecalClip(), hdc_c = check.hd->GetChildDecalClipContainer()->GetChildDecalClip(); hdc_o && hdc_c; hdc_o = (HDecalClip *)hdc_o->GetSiblingSame(), hdc_c = (HDecalClip *)hdc_c->GetSiblingSame()) {
        HClipProperty *hcp_o = hdc_o->GetClip();
        HClipProperty *hcp_c = hdc_c->GetClip();
        const HTypeProperty *ht_o = hdc_o->GetKind();
        const UINT sa = ht_o->GetValue();
        const HTypeProperty *ht_c = hdc_c->GetKind();
        const UINT sa1 = ht_c->GetValue();
        if (sa != sa1)
            return false;
        const float percent_o = hdc_o->GetPercent()->GetValue();
        const float percent_c = hdc_c->GetPercent()->GetValue();
        if (percent_o != percent_c)
            return false;
        const int t_oo = hdc_o->GetType();
        const int t_cc = hdc_c->GetType();
        if (t_oo != t_cc)
            return false;
        const int t_o = hcp_o->GetType();
        const int t_c = hcp_c->GetType();
        if (t_o != t_c)
            return false;
        const int h_o = hcp_o->GetHeight();
        const int h_c = hcp_c->GetHeight();
        if (h_o != h_c)
            return false;
        const int w_o = hcp_o->GetWidth();
        const int w_c = hcp_c->GetWidth();
        if (w_o != w_c)
            return false;
        String n_o = hcp_o->GetClip()->GetFileName();
        String n_c = hcp_c->GetClip()->GetFileName();
        if (n_o != n_c)
            return false;
        if (hdc_o->GetClip()->GetIsSeamless()->GetValue() != hdc_c->GetClip()->GetIsSeamless()->GetValue())
            return false;
        const Vector2 repeat_o = hdc_o->GetClip()->GetRepeat()->GetValue();
        const Vector2 repeat_c = hdc_c->GetClip()->GetRepeat()->GetValue();
        if (repeat_o.x != repeat_c.x || repeat_o.y != repeat_c.y)
            return false;
        if (hdc_o->GetExportType()->GetValue() != hdc_c->GetExportType()->GetValue())
            return false;
    }
    if (!hdc_o && !hdc_c)
        return true; //containers equal   // NOLINT(readability-simplify-boolean-expr)

    return false;
}

void CMaPDApp::CopyDecalData(const MyDecal &org, MyDecal tocopy) {
    for (int i = 0; i < tocopy.stamp.GetSize(); ++i) {
        HDecalStamp *addstamp = org.hd->AddDecalStamp();
        for (int j = 0; j < tocopy.stamp[i].stampdata.GetSize(); ++j) {
            addstamp->AddPatchUV(tocopy.stamp[i].stampdata[j].hp, tocopy.stamp[i].stampdata[j].uvs);
        }
    }
}

BOOL CMaPDApp::OnModel(HModelCache *hmc) {
    CArrayEx<MyDecal, MyDecal> decallist;

    CWaitCursor wait;
    if (!GetDecalList(hmc, decallist))
        return true;

#ifdef _DEBUG
    fs.Open("e:\\TestDecal.txt", FileMode::HS_ASCII);
    fs << "Decals for " << hmc->GetName() << nl;
    for (int i = 0; i < decallist.GetSize(); ++i)
        fs << decallist[i].hd->GetName() << nl;
    fs << nl;
#endif

    bool ischanged = false;
    for (int i = 0; i < decallist.GetSize() - 1; ++i) {
        if (decallist[i].isdeletet)
            continue;
        for (int j = i + 1; j < decallist.GetSize(); ++j) {
            if (decallist[j].isdeletet)
                continue;
            bool needcopy = IsMatchDecal(decallist[i], decallist[j]);
#ifdef _DEBUG
            fs << decallist[i].hd->GetName() << " ";
            fs << decallist[j].hd->GetName() << " isequal " << needcopy << nl;
#endif
            if (needcopy) {
                CopyDecalData(decallist[i], decallist[j]);
                decallist[j].isdeletet = true;
                ischanged = true;
            }
        }
    }

#ifdef _DEBUG
    fs.Close();
#endif

    if (ischanged) {
        for (int i = 0; i < decallist.GetSize(); ++i) {
            if (decallist[i].isdeletet)
                HModelCache::DeleteHandle(decallist[i].hd);
        }
    }
    decallist.RemoveAll();
    if (ischanged) {
        hmc->SetChanged(true);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        return true;
    }
    return true;
}

BOOL CMaPDApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMaPDApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
