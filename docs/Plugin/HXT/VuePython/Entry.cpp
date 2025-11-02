#include "StdAfx.h"
#include "VuePython.h"

enum { KAMERA, LICHT, CHOR };

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const UINT index, ObjectType &objtype) {
    switch (index) {
        case KAMERA:
            objtype = HOT_CAMERA;
            return TRUE;
        case LICHT:
            objtype = HOT_LIGHT;
            return TRUE;
        case CHOR:
            objtype = HOT_CHOR;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, const UINT index, String &menuname, MenuCategory &mc, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    CString string;
    disabled = FALSE;
    mc = MC_EXPORT;

    switch (index) {
        case KAMERA:
            if (((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            string.LoadString(IDS_STRING3000);
            menuname = string;
            return TRUE;
        case LICHT:
            string.LoadString(IDS_STRING3001);
            menuname = string;
            if (((HAnimObject *)htreeobject)->IsCache())
                return FALSE;
            return TRUE;
        case CHOR:
            string.LoadString(IDS_STRING3002);
            menuname = string;
            return TRUE;
        default:
            return FALSE;
    }
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, const UINT index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    switch (index) {
        case KAMERA:
            return ((CVuePythonApp *)AfxGetApp())->OnCamera((HCamera *)htreeobject);
        case LICHT:
            return ((CVuePythonApp *)AfxGetApp())->OnLight((HLight *)htreeobject);
        case CHOR:
            return ((CVuePythonApp *)AfxGetApp())->OnChor((HChor *)htreeobject);
        default:
            return FALSE;
    }
}
