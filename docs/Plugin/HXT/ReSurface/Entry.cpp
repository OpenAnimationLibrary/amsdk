#include "StdAfx.h"
#include "ReSurface.h"

enum { MGROUP, MODEL };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case MGROUP:
            objtype = HOT_GROUP;
            return TRUE;
        case MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    CString string;
    string.LoadString(IDS_STRING1);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;

    switch (index) {
        case MGROUP:
            if (!((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            return TRUE;
        case MODEL:
            if (((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case MGROUP:
            return ((CReSurfaceApp *)AfxGetApp())->OnGroup((HGroup *)htreeobject);
        case MODEL:
            return ((CReSurfaceApp *)AfxGetApp())->OnModel((HModel *)htreeobject);
        default:
            return FALSE;
    }
}
