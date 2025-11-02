#include "StdAfx.h"
#include "primitive.h"

enum { MODEL, OBJECTCONTAINER };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case OBJECTCONTAINER:
            objtype = HOT_OBJECTS; //V13 SDK
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
        case MODEL:
            if (!((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            return TRUE;
        case OBJECTCONTAINER:
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case MODEL:
            return ((CPrimitiveApp *)AfxGetApp())->OnPrimitiveWizard((HModelCache *)htreeobject);
        case OBJECTCONTAINER:
            return ((CPrimitiveApp *)AfxGetApp())->OnPrimitiveWizard(nullptr);
        default:
            return FALSE;
    }
}
