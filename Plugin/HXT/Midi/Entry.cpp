#include "StdAfx.h"
#include "Midi.h"

enum { P_PERCENT, P_FLOAT, P_INT, P_BOOL, P_COLOR, P_EULER, P_MODEL, P_VIRTUAL };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case P_PERCENT:
            objtype = HOT_PERCENT;
            return TRUE;
        case P_FLOAT:
            objtype = HOT_FLOAT;
            return TRUE;
        case P_INT:
            objtype = HOT_INTEGER;
            return TRUE;
        case P_BOOL:
            objtype = HOT_BOOL;
            return TRUE;
        case P_COLOR:
            objtype = HOT_COLOR;
            return TRUE;
        case P_EULER:
            objtype = HOT_EULERFLOAT;
            return TRUE;
        case P_MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case P_VIRTUAL:
            objtype = HOT_VIRTUALPROPERTY;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    CString string;
//    HUserCategoryProperty *huproperty;
    BOOL isinchor = FALSE;

    HTreeObject *parent = htreeobject->GetParent();
    if (parent) {
        if (parent->GetObjectType() == HOT_CHOR) {
            isinchor = TRUE;
        } else {
            while ((parent = parent->GetParent())) {
                if (parent->GetObjectType() == HOT_CHOR) {
                    isinchor = TRUE;
                    break;
                }
            }
        }
    } else {
        return FALSE;
    }
    if (!isinchor)
        return FALSE;

    string.LoadString(IDS_STRING1);
    menuname = string;
    disabled = FALSE;
    mc = MC_WIZARD;

    switch (index) {
        case P_VIRTUAL:
            return FALSE;
        case P_PERCENT:
            return TRUE;
        case P_FLOAT:
            return TRUE;
        case P_INT:
            return TRUE;
        case P_BOOL:
            return TRUE;
        case P_COLOR:
            return TRUE;
        case P_EULER:
            return TRUE;
        case P_MODEL:
        {
            if (((HModel *)htreeobject)->GetUserCategoryProperty() != nullptr)
                return TRUE;
            return FALSE;
        }
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case P_PERCENT:
            return ((CMidiApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case P_FLOAT:
            return ((CMidiApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case P_INT:
            return ((CMidiApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case P_BOOL:
            return ((CMidiApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case P_COLOR:
            return ((CMidiApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case P_EULER:
            return ((CMidiApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case P_MODEL:
            return ((CMidiApp *)AfxGetApp())->OnModel((HModel *)htreeobject);
        default:
            return FALSE;
    }
}
