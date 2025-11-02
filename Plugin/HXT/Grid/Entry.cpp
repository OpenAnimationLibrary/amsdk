// KB  10/3/00  \Ken90\Plugin\Wizards\Grid\Entry.cpp

#include "StdAfx.h"
#include "StrClass.h"
#include "F_Protos.h"
#include "Hxt.h"
#include "SDK/Entry.h"

enum { MODEL, OBJECTCONTAINER };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case OBJECTCONTAINER:
            objtype = HOT_OBJECTS;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    CString string;
    string.LoadString(IDS_MENUFILTER);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;

    switch (index) {
        case MODEL:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Only allow on Caches
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
            return ((CHxtApp *)AfxGetApp())->OnGridWizard((HModelCache *)htreeobject);
        case OBJECTCONTAINER:
            return ((CHxtApp *)AfxGetApp())->OnGridWizard(nullptr);
        default:
            return FALSE;
    }
}
