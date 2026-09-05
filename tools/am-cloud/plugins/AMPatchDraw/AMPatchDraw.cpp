#include "StdAfx.h"
#include "ObjType.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "CanvasDialog.h"

class HTreeObject; // Opaque command context; this stage never dereferences it.
CPluginApp theApp;
namespace {
LONG busy = 0;
constexpr ObjectType contexts[] = {HOT_MODEL,HOT_OBJECTS,HOT_GROUP};
}
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(uint32_t index,ObjectType& type) {
    if(index>=_countof(contexts)) return FALSE;
    type=contexts[index];return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject*,uint32_t index,
    String& name,MenuCategory& category,BOOL& disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if(index>=_countof(contexts)) return FALSE;
    name="A:M Patch Draw v0.1 - Canvas";category=MC_WIZARD;disabled=busy!=0;return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject*,uint32_t index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if(index>=_countof(contexts)) return FALSE;
    if(InterlockedCompareExchange(&busy,1,0)!=0) return TRUE;
    struct Reset { ~Reset(){InterlockedExchange(&busy,0);} } reset;
    // No model pointer is retained or dereferenced. GetAMVersion is the only
    // host query besides obtaining an owner window; all drawing is local data.
    try {
        const String version=GetAMVersion();
        PatchDrawDialog dialog(CWnd::FromHandle(GetMainApplicationWnd()),version.Get());
        if(dialog.DoModal()==-1) throw std::runtime_error("Cannot open Patch Draw dialog.");
    } catch(CException* error) {
        error->Delete(); ::MessageBoxA(GetMainApplicationWnd(),"MFC operation failed. No A:M geometry was changed.","Patch Draw",MB_OK|MB_ICONERROR);
    } catch(const std::exception& error) {
        ::MessageBoxA(GetMainApplicationWnd(),error.what(),"Patch Draw",MB_OK|MB_ICONERROR);
    } catch(...) {
        ::MessageBoxA(GetMainApplicationWnd(),"Unexpected canvas failure. No model-editing operation was requested.","Patch Draw",MB_OK|MB_ICONERROR);
    }
    return TRUE;
}
