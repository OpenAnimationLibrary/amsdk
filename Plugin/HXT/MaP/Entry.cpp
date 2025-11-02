#include "StdAfx.h"
#include "MaP.h"

enum { MODEL };

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

    CString string;
    string.LoadString(IDS_STRING1);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == MODEL) {
        return ((CMaPApp *)AfxGetApp())->OnModel((HModelCache *)htreeobject);
    }
    return FALSE;
}
