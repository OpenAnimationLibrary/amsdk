#include "StdAfx.h"
#include "Conform.h"
#include "SDK/Entry.h"

enum { MODEL };

//enum { MODEL, OBJECTCONTAINER, CHORACTION };
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    //only one objecttype per case statement , otherwise only the last is used
    if (index == MODEL) {
        objtype = HOT_MODEL; // ObjectType from Objtype.h
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    CString string;
    string.LoadString(IDS_MENUFILTER); // Retrieves the data from the String Table
    menuname = string;        // The name of the plugin

    disabled = FALSE;
    mc = MC_WIZARD; // MenuCategory from Entry.h

    if (index == MODEL) {
        if (!((HAnimObject *)htreeobject)->IsCache())
            return TRUE; //let the plugin start from a selected model in the chor 
        return FALSE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (index == MODEL) {
        //starting from chor , without the model have a action yet
        return ((CConformApp *)AfxGetApp())->OnConformPlugin((HModel *)htreeobject);
    }
    return FALSE;
}
