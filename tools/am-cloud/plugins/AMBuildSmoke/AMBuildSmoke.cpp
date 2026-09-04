#include "StdAfx.h"
#include "ObjType.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"

class HTreeObject;
// A real MFC application object is required for a regular MFC plugin DLL.
CPluginApp theApp;

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(
    const uint32_t index, ObjectType &objectType) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (index != 0) return FALSE;
    objectType = HOT_CP;
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const uint32_t index, String &menuName,
    MenuCategory &category, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (index != 0 || !object) return FALSE;
    CString label;
    if (!label.LoadString(101)) return FALSE;
    menuName = label;
    category = MC_WIZARD;
    disabled = FALSE;
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(
    HTreeObject *object, const uint32_t index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (index != 0 || !object) return FALSE;
    // Exercise an actual SDK import as well as MFC and the compiled resource.
    const String version = GetAMVersion();
    (void)version;
    AfxMessageBox("A:M cloud-build test succeeded.\n\n"
                  "The plugin loaded, its menu resource was read, and an SDK "
                  "function returned. No model data was changed.", MB_OK | MB_ICONINFORMATION);
    return TRUE;
}
