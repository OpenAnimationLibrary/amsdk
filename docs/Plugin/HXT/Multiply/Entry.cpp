#include "StdAfx.h"
#include "Multiply.h"

enum { P_CHOR, P_MODEL };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case P_CHOR:
            objtype = HOT_CHOR;
            return TRUE;
        case P_MODEL:
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
        case P_CHOR:
            return TRUE;
        case P_MODEL:
            if (((HAnimObject *)htreeobject)->IsCache()) // Only allow on Instances
                return FALSE;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case P_CHOR:
            return ((CMultiplyApp *)AfxGetApp())->OnChor((HChor *)htreeobject);
        case P_MODEL:
            return ((CMultiplyApp *)AfxGetApp())->OnInstance((HModel *)htreeobject);
        default:
            return FALSE;
    }
}
