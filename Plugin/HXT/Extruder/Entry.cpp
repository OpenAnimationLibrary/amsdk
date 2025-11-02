//
#include "StdAfx.h"
#include "StrClass.h"
#include "F_Protos.h"
#include "Hxt.h"
#include "SDK/Entry.h"

enum { EXTRUDER_GROUP, EXTRUDER_MODEL };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case EXTRUDER_GROUP:
            objtype = HOT_GROUP;
            return TRUE;
        case EXTRUDER_MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        default:
            return FALSE;
    }
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

    switch (index) {
        case EXTRUDER_GROUP:
            return ((CHxtApp *)AfxGetApp())->OnExtruderWizard(nullptr, (HGroup *)htreeobject);
        case EXTRUDER_MODEL:
            return ((CHxtApp *)AfxGetApp())->OnExtruderWizard((HModelCache *)htreeobject, nullptr);
        default:
            return FALSE;
    }
}
