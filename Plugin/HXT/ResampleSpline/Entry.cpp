#include "StdAfx.h"
#include "ResampleSpline.h"

enum { CP, CPINSTANCE, MGROUP };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case CP:
            objtype = HOT_CP;
            return TRUE;
        case CPINSTANCE:
            objtype = HOT_CPINSTANCE;
            return TRUE;
        case MGROUP:
            objtype = HOT_GROUP;
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
        case CP:
            return TRUE;
        case MGROUP:
            return TRUE;
        case CPINSTANCE:
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case CP:
            return ((CResampleSplineApp *)AfxGetApp())->OnCP((HCP *)htreeobject);
        case MGROUP:
            return ((CResampleSplineApp *)AfxGetApp())->OnGroup((HGroup *)htreeobject);
        case CPINSTANCE:
            return ((CResampleSplineApp *)AfxGetApp())->OnCPInstance((HCPInstance *)htreeobject);
        default:
            return FALSE;
    }
}
