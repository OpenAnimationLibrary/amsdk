#include "StdAfx.h"
#include "resource.h"
#include "Amplitude.h"

enum {
    PROP_PERCENT,
    PROP_FLOAT,
    PROP_INT,
    PROP_COLOR,
    PROP_EULER,
    PROP_CATEGORY,
    PROP_VIRTUAL
};

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case PROP_PERCENT:
            objtype = HOT_PERCENT;
            return TRUE;
        case PROP_FLOAT:
            objtype = HOT_FLOAT;
            return TRUE;
        case PROP_INT:
            objtype = HOT_INTEGER;
            return TRUE;
        case PROP_COLOR:
            objtype = HOT_COLOR;
            return TRUE;
        case PROP_EULER:
            objtype = HOT_EULERFLOAT;
            return TRUE;
        case PROP_CATEGORY:
            objtype = HOT_CATEGORYPROPERTY;
            return TRUE;
        case PROP_VIRTUAL:
            objtype = HOT_VIRTUALPROPERTY;
            return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    BOOL isinchor = FALSE;
    if (((HHashObject *)htreeobject)->GetParentOfType(HOT_CHOR) || ((HHashObject *)htreeobject)->GetParentOfType(HOT_ACTION)) {
        isinchor = TRUE;
    }
    if (!isinchor)
        return FALSE;

    CString string;
    string.LoadString(IDS_STRING1);
    disabled = FALSE;
    mc = MC_WIZARD;

#ifdef _DEBUG
    switch (index) {
        case PROP_PERCENT:
            string += " Percent";
            menuname = string;       
            return TRUE;
        case PROP_FLOAT:
            string += " Float";
            menuname = string;       
            return TRUE;
        case PROP_INT:
            string += " Int";
            menuname = string;       
            return TRUE;
        case PROP_COLOR:
            string += " Color";
            menuname = string;       
            return TRUE;
        case PROP_EULER:
            string += " Euler";
            menuname = string;       
            return TRUE;
        case PROP_CATEGORY:
        {
            if ((htreeobject->GetFullName().Find("Surface.Reflectivity")) > 0) {
                string += " CATEGORY";
                menuname = string;       
                return TRUE;
            }
            return FALSE;
        }
        case PROP_VIRTUAL:
            string += " Virtual";
            menuname = string;       
            return TRUE;
    }
#else
    menuname = string;       
    switch (index) {
        case PROP_PERCENT:
            return TRUE;
        case PROP_FLOAT:
            return TRUE;
        case PROP_INT:
            return TRUE;
        case PROP_COLOR:
            return TRUE;
        case PROP_EULER:
            return TRUE;
        case PROP_CATEGORY:
        {
            if (htreeobject->GetFullName().Find("Surface.Reflectivity") > 0)
                return TRUE;
            return FALSE;
        }
        case PROP_VIRTUAL:
            return TRUE;
    }
#endif
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case PROP_CATEGORY:
            return ((CAmplitudeApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case PROP_VIRTUAL:
            return ((CAmplitudeApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case PROP_PERCENT:
            return ((CAmplitudeApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case PROP_FLOAT:
            return ((CAmplitudeApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case PROP_INT:
            return ((CAmplitudeApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case PROP_COLOR:
            return ((CAmplitudeApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
        case PROP_EULER:
            return ((CAmplitudeApp *)AfxGetApp())->OnProperty((HProperty *)htreeobject);
    }

    return FALSE;
}
