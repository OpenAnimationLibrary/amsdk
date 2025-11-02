// Multiply.cpp : Legt die Initialisierungsroutinen für die DLL fest.
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
// CMultiplyApp

BEGIN_MESSAGE_MAP(CMultiplyApp, CWinApp)
        //{{AFX_MSG_MAP(CMultiplyApp)
        // HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
        //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiplyApp Konstruktion

CMultiplyApp::CMultiplyApp() = default;

CMultiplyApp::~CMultiplyApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMultiplyApp-Objekt

CMultiplyApp theApp;

BOOL CMultiplyApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    return CPluginApp::InitInstance();
}

int CMultiplyApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

BOOL CMultiplyApp::OnChor(HChor *hchor) {

    para = new PParameter;

    LoadSettings();
    para->mode = false;
    PDialog pdlg(para);

    if (pdlg.DoModal() == IDOK) {
        CWaitCursor wait;
        for (int i = 0; i < para->number; ++i) {
            HModel *hm = para->hmc->NewInstance(hchor);
            if (hm)
                hm->OnModified();
        }
        hchor->ExpandInProjectBar(true);
        para->hproject->UpdateAllViews(true);
        RefreshAllTrees();
        SaveSettings();
        delete para;
        return true;
    }

    para->hproject->UpdateAllViews(true);
    RefreshAllTrees();
    delete para;
    return true;
}

BOOL CMultiplyApp::OnInstance(HModel *model) {

    HChor *hchor = model->GetChor();
    if (!hchor)
        return true;

    para = new PParameter;

    LoadSettings();
    para->hmc = (HModelCache *)model->GetCache();
    para->mode = true;
    para->hm = model;
    PDialog pdlg(para);

    if (pdlg.DoModal() == IDOK) {
        CWaitCursor wait;
        const Vector scale_ofs = para->scale_offset / 100.F;
        Vector pos = model->GetTransform()->GetTranslate()->GetValue(Time());
        const Quaternion rot = model->GetTransform()->GetRotate()->GetValue(Time());
        RotateEuler rot1(rot);
        Vector scale = model->GetTransform()->GetScale()->GetValue(Time());
        for (int i = 0; i < para->number; ++i) {
            HModel *hm = para->hmc->NewInstance(hchor);
            if (hm) {
                pos += para->translate_offset;
                scale += scale_ofs;
                rot1.x += para->rotate_offset.x;
                rot1.y += para->rotate_offset.y;
                rot1.z += para->rotate_offset.z;
                hm->GetTransform()->GetTranslate()->StoreValue(Time(), pos, false);
                hm->GetTransform()->GetRotate()->StoreValue(Time(), Quaternion(rot1), true, false);
                hm->GetTransform()->GetScale()->StoreValue(Time(), scale, false);
                hm->OnModified();
            }
        }
        hchor->ExpandInProjectBar(true);
        para->hproject->UpdateAllViews(true);
        RefreshAllTrees();
        SaveSettings();
        delete para;
        return true;
    }

    para->hproject->UpdateAllViews(true);
    RefreshAllTrees();
    delete para;
    return true;
}

void CMultiplyApp::LoadSettings() const {
    para->hm = nullptr;
    para->hmc = nullptr;
    para->hproject = GetHProject();
    para->number = GetRegistryValue("Multiply HXT", "copies", 1);
    para->rotate_offset.x = GetRegistryValue("Multiply HXT", "rotatex", 0.F);
    para->rotate_offset.y = GetRegistryValue("Multiply HXT", "rotatey", 0.F);
    para->rotate_offset.z = GetRegistryValue("Multiply HXT", "rotatez", 0.F);
    para->translate_offset.x = GetRegistryValue("Multiply HXT", "translatex", 0.F);
    para->translate_offset.y = GetRegistryValue("Multiply HXT", "translatey", 0.F);
    para->translate_offset.z = GetRegistryValue("Multiply HXT", "translatez", 0.F);
    para->scale_offset.x = GetRegistryValue("Multiply HXT", "scalex", 0.F);
    para->scale_offset.y = GetRegistryValue("Multiply HXT", "scaley", 0.F);
    para->scale_offset.z = GetRegistryValue("Multiply HXT", "scalez", 0.F);
}

void CMultiplyApp::SaveSettings() const {
    SetRegistryValue("Multiply HXT", "copies", para->number);
    SetRegistryValue("Multiply HXT", "rotatex", para->rotate_offset.x);
    SetRegistryValue("Multiply HXT", "rotatey", para->rotate_offset.y);
    SetRegistryValue("Multiply HXT", "rotatez", para->rotate_offset.z);
    SetRegistryValue("Multiply HXT", "translatex", para->translate_offset.x);
    SetRegistryValue("Multiply HXT", "translatey", para->translate_offset.y);
    SetRegistryValue("Multiply HXT", "translatez", para->translate_offset.z);
    SetRegistryValue("Multiply HXT", "scalex", para->scale_offset.x);
    SetRegistryValue("Multiply HXT", "scaley", para->scale_offset.y);
    SetRegistryValue("Multiply HXT", "scalez", para->scale_offset.z);
}
