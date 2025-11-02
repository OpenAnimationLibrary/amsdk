#include "StdAfx.h"
#include "CutPlane.h"

extern "C" __declspec(dllexport) BOOL HxtLoadSelectObjectEntry(UINT index, ObjectType &objtype) {
    //   if (IsInNetRender()) return false;
    if (index < NUM_HOTS) {
        //SDK addition of GetNumHots() would be more robust
        objtype = (ObjectType)index;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) void HxtOnSelectObject(HTreeObject *htreeobject, UINT index, BOOL isselected) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    //   if (IsInNetRender()) return;
    if (theApp.hmc && theApp.plane.hg) {
        if (theApp.hmc == ((HModelCache *)htreeobject)->GetParentOfType(HOT_MODEL)) {
            theApp.OnSelectionChanged(true);
        } else {
            theApp.OnSelectionChanged(false);
        }
    }
}

enum {
    MODEL
};

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    if (index == MODEL) {
        objtype = HOT_MODEL;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (!((HAnimObject *)htreeobject)->IsCache())
        return FALSE;
    if (theApp.mdlg)
        return FALSE;

    CString string;
    string.LoadString(IDS_STRING1);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;

    if (index == MODEL) {
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == MODEL) {
        return theApp.OnStart((HModelCache *)htreeobject);
    }
    return FALSE;
}
