#include "StdAfx.h"
#include "Setposition.h"

enum { MGROUP, SEGMENT };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case MGROUP:
            objtype = HOT_GROUP;
            return TRUE;
        case SEGMENT:
            objtype = HOT_SEGMENT;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    if (!((HAnimObject *)htreeobject)->IsCache())
        return FALSE;

    CString string;
    string.LoadString(IDS_STRING1);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case MGROUP:
        {
            auto *hg = (HGroup *)htreeobject;
            auto *hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
            return ((CSetpositionApp *)AfxGetApp())->OnSetGroup(hmc, hg);
        }
        case SEGMENT:
        {
            auto *hb = (HBone *)htreeobject;
            auto *hmc = (HModelCache *)hb->GetParentOfType(HOT_MODEL);
            return ((CSetpositionApp *)AfxGetApp())->OnSetBone(hmc, hb);
        }
        default:
            return FALSE;
    }
}
