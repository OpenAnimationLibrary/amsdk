#include "StdAfx.h"
#include "MotCam.h"

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    if (index == 0) {
        objtype = HOT_CAMERA;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    CString string;
    string.LoadString(IDS_STRING3000);
    menuname = string;
    disabled = FALSE;
    mc = MC_EXPORT;

    if (index == 0) {
        if (((HAnimObject *)htreeobject)->IsCache())
            return FALSE;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == 0) {
        return ((CMotCamApp *)AfxGetApp())->OnCamera((HCamera *)htreeobject);
    }
    return FALSE;
}
