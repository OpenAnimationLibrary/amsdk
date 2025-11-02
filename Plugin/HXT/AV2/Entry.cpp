// Dan  1/26/00
#include "StdAfx.h"
#include "resource.h"
#include "Hxt.h"
#include "SDK/Entry.h"

enum { EXPORT_MODELCACHE, IMPORT_MODELCACHE, EXPORT_OBJECTCACHECONTAINER, IMPORT_OBJECTCACHECONTAINER, EXPORT_ACTIONCACHE, EXPORT_ACTIONCACHECONTAINER, EXPORT_CHOR };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case EXPORT_MODELCACHE:
            objtype = HOT_MODEL;
            return TRUE;
        case IMPORT_MODELCACHE:
            objtype = HOT_MODEL;
            return TRUE;
        case EXPORT_OBJECTCACHECONTAINER:
            objtype = HOT_OBJECTS;
            return TRUE;
        case IMPORT_OBJECTCACHECONTAINER:
            objtype = HOT_OBJECTS;
            return TRUE;
        case EXPORT_ACTIONCACHE:
            objtype = HOT_ACTION;
            return TRUE;
        case EXPORT_ACTIONCACHECONTAINER:
            objtype = HOT_ACTIONS;
            return TRUE;
        case EXPORT_CHOR:
            objtype = HOT_CHOR;
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

    switch (index) {
        case EXPORT_MODELCACHE:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Actually a Model, not a ModelCache
                return FALSE;
            mc = MC_EXPORT;
            return TRUE;
        case IMPORT_MODELCACHE:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Actually a Model, not a ModelCache
                return FALSE;
            mc = MC_IMPORT;
            return TRUE;
        case EXPORT_OBJECTCACHECONTAINER:
            mc = MC_EXPORT;
            return TRUE;
        case IMPORT_OBJECTCACHECONTAINER:
            mc = MC_IMPORT;
            return TRUE;
        case EXPORT_ACTIONCACHE:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Actually a Action, not a ActionCache
                return FALSE;
            mc = MC_EXPORT;
            return TRUE;
        case EXPORT_ACTIONCACHECONTAINER:
            mc = MC_EXPORT;
            return TRUE;
        case EXPORT_CHOR:
            mc = MC_EXPORT;
            return TRUE;
        default: 
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    switch (index) {
        case EXPORT_MODELCACHE:
            return ((CHxtApp *)AfxGetApp())->OnExportModelCache((HModelCache *)htreeobject);
        case IMPORT_MODELCACHE:
            return ((CHxtApp *)AfxGetApp())->OnImportModelCache((HModelCache *)htreeobject);
        case EXPORT_OBJECTCACHECONTAINER:
            return ((CHxtApp *)AfxGetApp())->OnExportObjectCacheContainer((HObjectCacheContainer *)htreeobject);
        case IMPORT_OBJECTCACHECONTAINER:
            return ((CHxtApp *)AfxGetApp())->OnImportObjectCacheContainer((HObjectCacheContainer *)htreeobject);
        case EXPORT_ACTIONCACHE:
            return ((CHxtApp *)AfxGetApp())->OnExportActionCache((HActionCache *)htreeobject);
        case EXPORT_ACTIONCACHECONTAINER:
            return ((CHxtApp *)AfxGetApp())->OnExportActionCacheContainer((HActionCacheContainer *)htreeobject);
        case EXPORT_CHOR:
            return ((CHxtApp *)AfxGetApp())->OnExportChor((HChor *)htreeobject);
        default: 
            return FALSE;
    }
}
