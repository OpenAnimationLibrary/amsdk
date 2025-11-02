#include <SDK/Entry.h>

#include "StdAfx.h"
#include "Push.h"
#include "resource.h"

enum { MODEL, NGROUP };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case MODEL:
            objtype = HOT_MODEL;
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

    //   if (!((HAnimObject *)htreeobject)->IsCache())
    //      return FALSE;

    CString string;
    string.LoadString(IDS_STRING1);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;
    switch (index) {
        case MODEL:
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
        case MODEL:
        {
            if (!((HAnimObject *)htreeobject)->IsCache())
                return ((CPushApp *)AfxGetApp())->OnModelInstance((HModel *)htreeobject);
            return ((CPushApp *)AfxGetApp())->OnModel((HModelCache *)htreeobject);
        }
        case NGROUP:
        {
            if (!((HAnimObject *)htreeobject)->IsCache())
                return ((CPushApp *)AfxGetApp())->OnGroupInstance((HGroup *)htreeobject);
            return ((CPushApp *)AfxGetApp())->OnGroup((HGroup *)htreeobject);
        }
        default:
            return FALSE;
    }
}
