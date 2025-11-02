// Dan  12/28/00  \Dan90\Plugin\HXT\Ply\Entry.cpp
// ZPiDER 2001-11 http://www.kci-group.com/z
// ZPiDER 2002-10 http://www.kci-group.com/z

#include "StdAfx.h"
#include "Hxt.h"
#include "ObjType.h"
#include "StrClass.h"
#include "SDK/HHashobj.h"
#include "SDK/Entry.h"

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

enum { EXPORT_ACTIONCACHE, EXPORT_CHOR };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case EXPORT_ACTIONCACHE:
            objtype = HOT_ACTION;
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
        case EXPORT_ACTIONCACHE:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Actually an Action, not an ActionCache
                return FALSE;
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
        case EXPORT_ACTIONCACHE:
            return ((CHxtApp *)AfxGetApp())->OnExportActionCache((HActionCache *)htreeobject);

        case EXPORT_CHOR:
            return ((CHxtApp *)AfxGetApp())->OnExportChor((HChor *)htreeobject);
        default:
            return FALSE;
    }
}
