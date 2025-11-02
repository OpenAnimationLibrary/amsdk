#include "StdAfx.h"
#include "Hxt.h"
#include "StrClass.h"
#include "SDK/Entry.h"

enum { IMPORT_MODELCACHE, IMPORT_OBJECTCACHECONTAINER };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case IMPORT_MODELCACHE:
            objtype = HOT_MODEL;
            return TRUE;
        case IMPORT_OBJECTCACHECONTAINER:
            objtype = HOT_OBJECTS;
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
        case IMPORT_MODELCACHE:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Actually a Model, not a ModelCache
                return FALSE;
            mc = MC_IMPORT;
            return TRUE;
        case IMPORT_OBJECTCACHECONTAINER:
            mc = MC_IMPORT;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    switch (index) {
        case IMPORT_MODELCACHE:
            return ((CHxtApp *)AfxGetApp())->OnImportModelCache((HModelCache *)htreeobject);
        case IMPORT_OBJECTCACHECONTAINER:
            return ((CHxtApp *)AfxGetApp())->OnImportObjectCacheContainer((HObjectCacheContainer *)htreeobject);
        default:
            return FALSE;
    }
}
