#include "StdAfx.h"
#include "Midicontrol.h"

enum { P_MODEL, P_CHOR, P_LIGHT, P_CAMERA, P_NULL, P_FORCE };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case P_MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case P_CHOR:
            objtype = HOT_CHOR;
            return TRUE;
        case P_LIGHT:
            objtype = HOT_LIGHT;
            return TRUE;
        case P_CAMERA:
            objtype = HOT_CAMERA;
            return TRUE;
        case P_NULL:
            objtype = HOT_NULLOBJECT;
            return TRUE;
        case P_FORCE:
            objtype = HOT_FORCE;
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
        case P_MODEL:
        {
            if (!((HAnimObject *)htreeobject)->IsCache())
                return TRUE;
            return FALSE;
        }
        case P_CHOR:
            return TRUE;
        case P_LIGHT:
        {
            if (!((HAnimObject *)htreeobject)->IsCache())
                return TRUE;
            return FALSE;
        }
        case P_CAMERA:
        {
            if (!((HAnimObject *)htreeobject)->IsCache())
                return TRUE;
            return FALSE;
        }
        case P_NULL:
        {
            if (!((HAnimObject *)htreeobject)->IsCache())
                return TRUE;
            return FALSE;
        }
        case P_FORCE:
        {
            if (!((HAnimObject *)htreeobject)->IsCache())
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
        case P_MODEL:
            return ((CMidicontrolApp *)AfxGetApp())->Objectstart((HHashObject *)htreeobject);
        case P_CHOR:
            return ((CMidicontrolApp *)AfxGetApp())->Chorstart((HChor *)htreeobject);
        case P_LIGHT:
            return ((CMidicontrolApp *)AfxGetApp())->Objectstart((HHashObject *)htreeobject);
        case P_CAMERA:
            return ((CMidicontrolApp *)AfxGetApp())->Objectstart((HHashObject *)htreeobject);
        case P_NULL:
            return ((CMidicontrolApp *)AfxGetApp())->Objectstart((HHashObject *)htreeobject);
        case P_FORCE:
            return ((CMidicontrolApp *)AfxGetApp())->Objectstart((HHashObject *)htreeobject);
        default:
            return FALSE;
    }
}
