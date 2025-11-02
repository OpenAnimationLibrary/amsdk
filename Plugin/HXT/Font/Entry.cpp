//
#include "StdAfx.h"
#include "StrClass.h"
#include "F_Protos.h"
#include "Hxt.h"
#include "SDK/Entry.h"

enum { FONTMODEL, AIMODEL, FONTOBJECTCONTAINER, AIOBJECTCONTAINER };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case FONTMODEL:
        case AIMODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case FONTOBJECTCONTAINER:
        case AIOBJECTCONTAINER:
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
    mc = MC_WIZARD;

    switch (index) {
        case FONTMODEL:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Only allow on Caches
                return FALSE;
            menuname = "Font";
            return TRUE;
        case AIMODEL:
            if (!((HAnimObject *)htreeobject)->IsCache()) // Only allow on Caches
                return FALSE;
        //	  menuname = "AI";
            mc = MC_IMPORT;
            return TRUE;
        case FONTOBJECTCONTAINER:
            menuname = "Font";
            return TRUE;
        case AIOBJECTCONTAINER:
            //	  menuname = "AI";
            mc = MC_IMPORT;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case FONTMODEL:
            return ((CHxtApp *)AfxGetApp())->OnFontWizard((HModelCache *)htreeobject);
        case AIMODEL:
            return ((CHxtApp *)AfxGetApp())->OnAIWizard((HModelCache *)htreeobject);
        case FONTOBJECTCONTAINER:
            return ((CHxtApp *)AfxGetApp())->OnFontWizard(nullptr);
        case AIOBJECTCONTAINER:
            return ((CHxtApp *)AfxGetApp())->OnAIWizard(nullptr);
        default:
            return FALSE;
    }
}
