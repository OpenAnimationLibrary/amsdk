#include "MirrorConstraint.h"

enum { MODEL, ACTION };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case ACTION:
            objtype = HOT_ACTION;
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
            if (!((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            return TRUE;
        case ACTION:
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case MODEL:
            return ((CMirrorConstraintApp *)AfxGetApp())->OnModel((HModelCache *)htreeobject);
        case ACTION:
            return ((CMirrorConstraintApp *)AfxGetApp())->OnAction((HActionCache *)htreeobject);
        default:
            return FALSE;
    }
}
