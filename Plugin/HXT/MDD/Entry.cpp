#include "StdAfx.h"
#include "MDD.h"

enum { EXPORT_MODEL, IMPORT_MODEL };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case EXPORT_MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case IMPORT_MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    CString string;
    disabled = FALSE;
    mc = MC_WIZARD;

    switch (index) {
        case EXPORT_MODEL:
            if (((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            string.LoadString(IDS_STRING4);
            menuname = string;
            mc = MC_EXPORT;
            return TRUE;
        case IMPORT_MODEL:
            if (((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            string.LoadString(IDS_STRING1);
            menuname = string;
            mc = MC_IMPORT;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case EXPORT_MODEL:
            return ((CMDDApp *)AfxGetApp())->OnExportModel((HModel *)htreeobject);
        case IMPORT_MODEL:
            return ((CMDDApp *)AfxGetApp())->OnImportModel((HModel *)htreeobject);
        default:
            return FALSE;
    }
}
