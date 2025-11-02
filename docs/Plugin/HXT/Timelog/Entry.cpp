#include "StdAfx.h"
#include "TimeLog.h"

extern "C" __declspec(dllexport) BOOL HxtLoadSelectObjectEntry(UINT index, ObjectType &objtype) {
    //accept messages from all objects
    if (IsInNetRender())
        return false;
    if (index < NUM_HOTS) {
        //SDK addition of GetNumHots() would be more robust
        objtype = (ObjectType)index;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) void HxtOnSelectObject(HTreeObject *htreeobject, UINT index, const BOOL isselected) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (IsInNetRender())
        return;
    const CTimeLogApp *app = (CTimeLogApp *)AfxGetApp();
    if (isselected)
        app->OnSelectionChanged();
}

enum {
    PROJECT
};

extern "C" __declspec(dllexport) BOOL HxtLoadPropertyEntry(const UINT index, ObjectType &objtype) {
    if (IsInNetRender())
        return false;
    if (index == PROJECT) {
        objtype = HOT_PROJECT;
        return TRUE;
    }
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddProperties(HTreeObject *htreeobject, HCategoryProperty *pluginproperty, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (IsInNetRender())
        return FALSE;
    if (index == PROJECT) {
        return ((CTimeLogApp *)AfxGetApp())->AddProjectProperties((HProject *)htreeobject, pluginproperty);
    }
    return FALSE;
}

extern "C" __declspec(dllexport) LRESULT HxtOnPropertyMessage(HTreeObject *htreeobject, const UINT index, const PtrMessage ptrmessage, HTreeObject * *ptruplink, const LONG_PTR lparam, const Time time) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    if (IsInNetRender())
        return FALSE;
    if (index == PROJECT) {
        return ((CTimeLogApp *)AfxGetApp())->OnProjectPropertiesMessage((HProject *)htreeobject, ptrmessage, lparam, time);
    }
    return FALSE;
}
