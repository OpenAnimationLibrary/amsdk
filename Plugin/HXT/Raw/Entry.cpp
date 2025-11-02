// Dan  1/26/00
#include "StdAfx.h"
#include "resource.h"
#include "Hxt.h"
#include "ObjType.h"
#include "StrClass.h"
#include "SDK/HHashobj.h"
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

enum { EXPORT_CAMERA, IMPORT_RAW };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case EXPORT_CAMERA:
        case IMPORT_RAW:
            objtype = HOT_CAMERA;
            return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    CString string;
    string.LoadString(IDS_MENUFILTER);
    menuname = string;       

    disabled = FALSE;

    switch (index) {
        case EXPORT_CAMERA:
            if (((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            mc = MC_EXPORT;
            return TRUE;
        case IMPORT_RAW:
            if (((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            mc = MC_IMPORT;
            return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    switch (index) {
        case EXPORT_CAMERA:
            return ((CHxtApp *)AfxGetApp())->OnExportRaw((HCamera *)htreeobject);
        case IMPORT_RAW:
            return ((CHxtApp *)AfxGetApp())->OnImportRaw((HCamera *)htreeobject);
    }
    return FALSE;
}
