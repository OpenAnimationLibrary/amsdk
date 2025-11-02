#include "StdAfx.h"
#include "BakeNull.h"

enum { P_NULL };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    if (index == P_NULL) {
        objtype = HOT_NULLOBJECT;
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

    if (index == P_NULL) {
        if (((HNullObject *)htreeobject)->GetChor())
            return TRUE;
        return FALSE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == P_NULL) {
        return ((CBakeNullApp *)AfxGetApp())->CloneNull((HNullObject *)htreeobject);
    }
    return FALSE;
}
