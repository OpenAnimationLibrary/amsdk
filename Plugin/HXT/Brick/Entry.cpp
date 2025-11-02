#include "StdAfx.h"
#include "Brick.h"

enum {
    P_CHOR
};

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    if (index == P_CHOR) {
        objtype = HOT_CHOR;
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

    if (index == P_CHOR) {
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == P_CHOR) {
        return ((CBrickApp *)AfxGetApp())->OnChor((HChor *)htreeobject);
    }
    return FALSE;
}
