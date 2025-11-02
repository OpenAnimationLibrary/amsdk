#include "StdAfx.h"
#include "Resource.h"
#include "TestPlugin.h"

enum { CP, MGROUP, MODEL, EXPORT_ACTIONCACHE, CHOR, ACTION, ACTIONCACHE };
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case CP:
            objtype = HOT_CP;
            return TRUE;
        case MGROUP:
            objtype = HOT_GROUP;
            return TRUE;
        case MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case EXPORT_ACTIONCACHE:
            objtype = HOT_ACTION;
            return TRUE;
        case CHOR:
            objtype = HOT_CHOR;
            return TRUE;
        case ACTIONCACHE:
            objtype = HOT_ACTION;
            return TRUE;
        case ACTION:
            objtype = HOT_ACTION;
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

    switch (index) {
        case CHOR:
            return TRUE;
        case CP:
            return TRUE;
        case MGROUP:
            return TRUE;
        case MODEL:
            return TRUE;
        case ACTIONCACHE:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Actually a Model, not a ModelCache
                return FALSE;
            return TRUE;
        case ACTION:
            if (((HAnimObject *)htreeobject)->IsCache()) // Actually a Model, not a ModelCache
                return FALSE;
            return TRUE;
        case EXPORT_ACTIONCACHE:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Actually a Model, not a ModelCache
                return FALSE;
            mc = MC_EXPORT;
            return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case CHOR:
            return ((CTestPluginApp *)AfxGetApp())->OnChor((HChor *)htreeobject);
        case CP:
            return ((CTestPluginApp *)AfxGetApp())->OnCP((HCP *)htreeobject);
        case MGROUP:
            return ((CTestPluginApp *)AfxGetApp())->OnGroup((HGroup *)htreeobject);
        case MODEL:
            return ((CTestPluginApp *)AfxGetApp())->OnModel((HModelCache *)htreeobject);
        case EXPORT_ACTIONCACHE:
            return ((CTestPluginApp *)AfxGetApp())->OnExportActionCache((HActionCache *)htreeobject);
            break;
        case ACTIONCACHE:
            return ((CTestPluginApp *)AfxGetApp())->OnActionCache((HActionCache *)htreeobject);
            break;
        case ACTION:
            return ((CTestPluginApp *)AfxGetApp())->OnAction((HAction *)htreeobject);
            break;
    }
    return FALSE;
}

