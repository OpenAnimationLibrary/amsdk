#include "StdAfx.h"
#include "MirrorBone.h"

enum { SEGMENT, NULLOBJECT, NGROUP };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case SEGMENT:
            objtype = HOT_SEGMENT;
            return TRUE;
        case NULLOBJECT:
            objtype = HOT_NULLOBJECT;
            return TRUE;
        case NGROUP:
            objtype = HOT_GROUP;
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

    switch (index) {
        case SEGMENT:
            return TRUE;
        case NULLOBJECT:
            return TRUE;
        case NGROUP:
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case SEGMENT:
        {
            auto *hbc = (HBoneCache *)htreeobject;
            auto *hmc = (HModelCache *)hbc->GetParentOfType(HOT_MODEL);
            return ((CMirrorBoneApp *)AfxGetApp())->OnBone(hmc, hbc);
        }
        case NULLOBJECT:
        {
            auto *hbc = (HBoneCache *)htreeobject;
            auto *hmc = (HModelCache *)hbc->GetParentOfType(HOT_MODEL);
            return ((CMirrorBoneApp *)AfxGetApp())->OnBone(hmc, hbc);
        }
        case NGROUP:
        {
            auto *hg = (HGroup *)htreeobject;
            auto *hmc = (HModelCache *)hg->GetParentOfType(HOT_MODEL);
            return ((CMirrorBoneApp *)AfxGetApp())->OnGroup(hmc, hg);
        }
        default:
            return FALSE;
    }
}
