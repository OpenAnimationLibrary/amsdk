// Dan  12/27/00  \Dan90\Plugin\HXT\Duplicator\Entry.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "MirrorBonesDialog.h"
#include "SDK/Entry.h"

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    if (index == 0) {
        objtype = HOT_MODEL;
        return TRUE;
    }

    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    if (!((HAnimObject *)htreeobject)->IsCache()) // Only allow on Caches
        return FALSE;

    CString string;
    string.LoadString(IDS_MENUFILTER);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return ((CHxtApp *)AfxGetApp())->OnInstallRig(htreeobject);
}
