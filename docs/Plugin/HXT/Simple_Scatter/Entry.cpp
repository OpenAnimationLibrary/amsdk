#include "StdAfx.h"
#include "Simple_Scatter.h"

enum { P_MODEL, P_GROUP };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case P_MODEL:
            objtype = HOT_MODEL;
            return TRUE;
        case P_GROUP:
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
        case P_MODEL:
            if (((HObject *)htreeobject)->GetChor() == nullptr)
                return FALSE;
            return TRUE;
        case P_GROUP:
        {
            auto *hg = (HGroup *)htreeobject;
            if (((HModel *)hg->GetParentOfType(HOT_MODEL))->GetChor() == nullptr)
                return FALSE;
            return TRUE;
        }
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case P_MODEL:
            return ((CSimple_ScatterApp *)AfxGetApp())->OnChorModel((HModel *)htreeobject);
        case P_GROUP:
            return ((CSimple_ScatterApp *)AfxGetApp())->OnChorGroup((HGroup *)htreeobject);
        default:
            return FALSE;
    }
}
