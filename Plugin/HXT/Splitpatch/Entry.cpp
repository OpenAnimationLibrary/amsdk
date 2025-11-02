#include "StdAfx.h"
#include "Splitpatch.h"

enum {
    MGROUP
};

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    if (index == MGROUP) {
        objtype = HOT_GROUP;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    CString string;
    string.LoadString(IDS_STRING1);
    menuname = string;

    disabled = false;
    mc = MC_WIZARD;

    if (index == MGROUP) {
        auto *hg = (HGroup *)htreeobject;
        if (((HModel *)hg->GetParentOfType(HOT_MODEL))->GetChor() != nullptr)
            return FALSE;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == MGROUP) {
        auto *hg = (HGroup *)htreeobject;
        auto *hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
        return ((CSplitpatchApp *)AfxGetApp())->OnGroup(hmc, hg);
    }
    return FALSE;
}
