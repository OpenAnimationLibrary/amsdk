#include "StdAfx.h"
#include "Select.h"

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

    CString string;
    string.LoadString(IDS_STRING1);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;

    if (index == MODEL) {
        if (!((HAnimObject *)htreeobject)->IsCache())
            return FALSE;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == MODEL) {
        return ((CSelectApp *)AfxGetApp())->OnWork((HModelCache *)htreeobject);
    }
    return FALSE;
}
