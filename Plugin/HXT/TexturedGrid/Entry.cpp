#include "StdAfx.h"
#include "Textured_Grid.h"

enum { OBJECTCONTAINER };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    if (index == OBJECTCONTAINER) {
        objtype = HOT_OBJECTS; //V13 SDK
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    CString string;
    string.LoadString(IDS_STRING1);
    menuname = string;

    disabled = FALSE;
    mc = MC_WIZARD;

    if (index == OBJECTCONTAINER) {
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == OBJECTCONTAINER) {
        return ((CTextured_GridApp *)AfxGetApp())->OnPrimitiveWizard();
    }
    return FALSE;
}
