// Dan  1/26/00
#include "StdAfx.h"
#include "Hxt.h"
#include "SDK/Entry.h"


//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState())
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

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

//****************************************************
//** Polygon Prop Import (IEPolyModel)
//****************************************************
extern "C" __declspec(dllexport) const char *GetImportPropModelFilters() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    static CString filter;
    filter.LoadString(IDS_FILEFILTERS);
    return filter;
}

extern "C" __declspec(dllexport) IEPolyModel *OnImportPropModel(const char *filename, [[maybe_unused]] const BOOL isnewimport, [[maybe_unused]] const float scale) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return ((CHxtApp *)AfxGetApp())->Import3DS(filename);
}

extern "C" __declspec(dllexport) void DeletePropModel(const IEPolyModel *iemodel) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    delete iemodel;
}
