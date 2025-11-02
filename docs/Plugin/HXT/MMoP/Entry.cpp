#include "StdAfx.h"
#include "MMoP.h"

enum { P_Path, P_Group };

//extern "C" __declspec(dllexport) const BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case P_Path:
            objtype = HOT_PATHMODEL;
            return TRUE;
        case P_Group:
            objtype = HOT_GROUP;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    //   CString string;
    //   string.LoadString(IDS_STRING1);
    menuname = "Multiple Models on Path";

    disabled = FALSE;
    mc = MC_WIZARD;

    switch (index) {
        case P_Path:
            return TRUE;
        case P_Group:
            {
            auto *hg = (HGroup *)htreeobject;
            if (hg->IsTempGroup())
                return FALSE;
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
        case P_Path:
            return ((CMMoPApp *)AfxGetApp())->OnPath((HPathModel *)htreeobject);
        case P_Group:
            return ((CMMoPApp *)AfxGetApp())->OnGroup((HGroup *)htreeobject);
        default:
            return FALSE;
    }
}
