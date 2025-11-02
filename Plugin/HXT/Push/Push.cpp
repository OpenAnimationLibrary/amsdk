// Push.cpp : Legt die Initialisierungsroutinen für die DLL fest.
//

#include "StdAfx.h"
#include "Push.h"

#include <SDK/HAction.h>
#include <SDK/HChor.h>
#include <SDK/HPatch.h>

#include "PDialog.h"
#include "ADialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPushApp

BEGIN_MESSAGE_MAP(CPushApp, CWinApp)
    //{{AFX_MSG_Push(CPushApp)
    // HINWEIS - Hier werden Pushping-Makros vom Klassen-Assistenten eingefügt und entfernt.
    //    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
    //}}AFX_MSG_Push
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPushApp Konstruktion

CPushApp::CPushApp() = default;
CPushApp::~CPushApp() = default;

/////////////////////////////////////////////////////////////////////////////
// Das einzige CPushApp-Objekt

CPushApp theApp;

BOOL CPushApp::OnModelInstance(HModel *hm) {
    auto *hchor = (HChor *)hm->GetParentOfType(HOT_CHOR);
    if (!hchor)
        return TRUE;
    para = new PARAMETER;
    para->hmc = (HModelCache *)hm->GetCache();
    para->makekeys = 0;
    para->pose0 = FALSE;
    for (int i = 0; i < 10; ++i) {
        para->distance[i] = 0;
        para->frame[i] = 0;
        para->keyframe[i] = false;
    }

    ADialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        delete para;
        return true;
    }

    // ReSharper disable once CppLocalVariableWithNonTrivialDtorIsNeverUsed
    CWaitCursor waitcursor;

    AFX_MANAGE_STATE(AfxGetAppModuleState())

    HActionCache *hactioncache = nullptr;
    BOOL isaction = false;
    HActionCacheContainer *hacc = GetHProject()->GetChildActionCacheContainer();
    const String temp = hchor->GetFullName();
    for (HActionCache *hac = hacc->GetChildActionCache(); hac; hac = hac->GetSiblingActionCache()) {
        String temp1 = hac->GetName();
        if (temp.Find(temp1) != -1) {
            hactioncache = hac;
            isaction = true;
            para->hmc = hactioncache->GetDefaultModelCache();
        }
    }

    HCP *cp;
    for (UINT i = 0; i < para->hmc->GetPatchCount(); ++i) {
        HPatch *hp = para->hmc->GetPatch(i);
        cp = hp->GetCP1();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp->GetCP2();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp->GetCP3();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        if (hp->GetNumPoints() == 4) {
            cp = hp->GetCP4();
            if (cp == cp->GetHead())
                groupcps.Add(cp);
        }
    }

    for (HPatch5 *hp5 = para->hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        cp = hp5->GetCP1();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp5->GetCP2();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp5->GetCP3();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp5->GetCP4();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp5->GetCP5();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
    }
    GetHProject()->DeselectAll();

    para->hmc->FindPatches();
    WorkInstance(hactioncache, hchor, isaction);

    groupcps.RemoveAll();
    delete para;
    return TRUE;
}

BOOL CPushApp::OnGroupInstance(HGroup *hg) {
    auto *hchor = (HChor *)hg->GetParentOfType(HOT_CHOR);
    if (!hchor)
        return TRUE;
    para = new PARAMETER;
    para->hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
    para->makekeys = 0;
    para->pose0 = FALSE;
    for (int i = 0; i < 10; ++i) {
        para->distance[i] = 0;
        para->frame[i] = 0;
        para->keyframe[i] = false;
    }
    ADialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        delete para;
        return true;
    }
    // ReSharper disable once CppLocalVariableWithNonTrivialDtorIsNeverUsed
    CWaitCursor waitcursor;

    AFX_MANAGE_STATE(AfxGetAppModuleState())

    HActionCache *hactioncache = nullptr;
    BOOL isaction = false;
    HActionCacheContainer *hacc = GetHProject()->GetChildActionCacheContainer();
    const String temp = hchor->GetFullName();
    for (HActionCache *hac = hacc->GetChildActionCache(); hac; hac = hac->GetSiblingActionCache()) {
        String temp1 = hac->GetName();
        if (temp.Find(temp1) != -1) {
            hactioncache = hac;
            isaction = true;
        }
    }

    if (isaction) {
        para->hmc = hactioncache->GetDefaultModelCache();
    } else {
        para->hmc = (HModelCache *)para->hmc->GetCache();
    }

    for (HGroupCP *currentgroupcp = hg->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
        HCP *cp = currentgroupcp->GetCP();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
    }
    GetHProject()->DeselectAll();
    para->hmc->FindPatches();

    WorkInstance(hactioncache, hchor, isaction);

    groupcps.RemoveAll();
    delete para;
    return TRUE;
}

BOOL CPushApp::OnModel(HModelCache *hmc) {
    para = new PARAMETER;
    para->hmc = hmc;
    para->makekeys = 0;
    para->pose0 = FALSE;
    for (int i = 0; i < 10; ++i) {
        para->distance[i] = 0;
        para->frame[i] = 0;
        para->keyframe[i] = false;
    }

    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        delete para;
        return true;
    }
    // ReSharper disable once CppLocalVariableWithNonTrivialDtorIsNeverUsed
    CWaitCursor waitcursor;

    AFX_MANAGE_STATE(AfxGetAppModuleState())

    HCP *cp;
    for (UINT i = 0; i < para->hmc->GetPatchCount(); ++i) {
        HPatch *hp = para->hmc->GetPatch(i);
        cp = hp->GetCP1();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp->GetCP2();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp->GetCP3();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        if (hp->GetNumPoints() == 4) {
            cp = hp->GetCP4();
            if (cp == cp->GetHead())
                groupcps.Add(cp);
        }
    }

    for (HPatch5 *hp5 = para->hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        cp = hp5->GetCP1();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp5->GetCP2();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp5->GetCP3();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp5->GetCP4();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
        cp = hp5->GetCP5();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
    }

    GetHProject()->DeselectAll();
    CMap<HHashObject *, HHashObject *, BOOL, BOOL> AllInstances;
    AllInstances.InitHashTable(257);
    for (HHashObject *hho = para->hmc->GetHeadInstance(); hho; hho = para->hmc->GetNextInstance(hho)) {
        if (hho != para->hmc->GetHeadInstance()) {
            const BOOL old_active = ((HObject *)hho)->GetActive()->GetValue();
            AllInstances.SetAt(hho, old_active);
            ((HObject *)hho)->GetActive()->SetValue(FALSE);
        }
    }

    para->hmc->FindPatches();
    Work();

    POSITION pos = AllInstances.GetStartPosition();
    while (pos != nullptr) {
        HHashObject *hho;
        BOOL old_active;
        AllInstances.GetNextAssoc(pos, hho, old_active);
        ((HObject *)hho)->GetActive()->SetValue(old_active);
    }
    groupcps.RemoveAll();

    para->hmc->Update();
    RefreshAllTrees();
    GetHProject()->UpdateAllViews(TRUE);

    delete para;
    return TRUE;
}

BOOL CPushApp::OnGroup(HGroup *hg) {
    para = new PARAMETER;
    para->hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
    para->makekeys = 0;
    para->pose0 = FALSE;
    for (int i = 0; i < 10; ++i) {
        para->distance[i] = 0;
        para->frame[i] = 0;
        para->keyframe[i] = false;
    }
//#ifdef _DEBUG
//              para->distance[1] = -10;
//              para->makekeys = 1;
//    PDialog pdlg(para);
//    if (pdlg.DoModal() != IDOK) {
//        delete para;
//        return true;
//    }
//#else
    PDialog pdlg(para);
    if (pdlg.DoModal() != IDOK) {
        delete para;
        return true;
    }
//#endif
    // ReSharper disable once CppLocalVariableWithNonTrivialDtorIsNeverUsed
    CWaitCursor waitcursor;
    AFX_MANAGE_STATE(AfxGetAppModuleState())

    CMap<HHashObject *, HHashObject *, BOOL, BOOL> AllInstances;
    AllInstances.InitHashTable(257);
    for (HHashObject *hho = para->hmc->GetHeadInstance(); hho; hho = para->hmc->GetNextInstance(hho)) {
        if (hho != para->hmc->GetHeadInstance()) {
            const BOOL old_active = ((HObject *)hho)->GetActive()->GetValue();
            AllInstances.SetAt(hho, old_active);
            ((HObject *)hho)->GetActive()->SetValue(FALSE);
        }
    }

    for (HGroupCP *currentgroupcp = hg->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
        HCP *cp = currentgroupcp->GetCP();
        if (cp == cp->GetHead())
            groupcps.Add(cp);
    }
    GetHProject()->DeselectAll();

    para->hmc->FindPatches();

    Work();

    POSITION pos = AllInstances.GetStartPosition();
    while (pos != nullptr) {
        HHashObject *hho;
        BOOL old_active;
        AllInstances.GetNextAssoc(pos, hho, old_active);
        ((HObject *)hho)->GetActive()->SetValue(old_active);
    }

    groupcps.RemoveAll();

    para->hmc->Update();
    RefreshAllTrees();
    GetHProject()->UpdateAllViews(TRUE);

    delete para;
    return TRUE;
}

BOOL CPushApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");
    return CPluginApp::InitInstance();
}

int CPushApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}
