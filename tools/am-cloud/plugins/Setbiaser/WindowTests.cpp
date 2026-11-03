// Win32-only regression checks using the ACTUAL Setbiaser dialog resource.
// Does not load A:M, fabricate SDK objects, or claim A:M runtime validation.
#include "WindowFrame.h"
#include <windowsx.h>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
int checks = 0;
void require(bool value, const char *message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}
INT_PTR CALLBACK procedure(HWND window, UINT message, WPARAM wparam, LPARAM) {
    if (message == WM_INITDIALOG) return TRUE;
    if (sb::window::isCloseRequest(message,wparam)) {
        DestroyWindow(window);
        return TRUE;
    }
    return FALSE;
}
HWND createPalette(HINSTANCE instance, HWND owner) {
    HWND window=CreateDialogParamW(instance,MAKEINTRESOURCEW(IDD_SETBIASER),owner,procedure,0);
    require(window!=nullptr,"The actual Setbiaser dialog resource did not create.");
    require(sb::window::hasPaletteFrame(window),"Missing caption/border/system menu, or DS_CONTROL set.");
    require(GetWindow(window,GW_OWNER)==owner,"Palette is not owned by the host window.");
    require(IsWindowEnabled(owner)!=FALSE,"A modeless palette disabled its host.");
    require(GetDlgItem(window,IDC_CLOSE)!=nullptr,"Explicit Close button is missing.");
    require(sb::window::positionPalette(window,owner),"Could not center the palette.");
    ShowWindow(window,SW_SHOWNOACTIVATE);
    return window;
}
void geometry() {
    const RECT work{0,0,1920,1040}, owner{100,100,1100,800};
    const SIZE size{336,300};
    const auto center=sb::window::centeredOrigin(owner,size,work);
    require(center.x==432 && center.y==300,"Initial center is not relative to the owner.");
    auto point=sb::window::clampOrigin({-10000,-10000},size,work);
    require(point.x==0 && point.y==0,"Negative offscreen position was not clamped.");
    point=sb::window::clampOrigin({10000,10000},size,work);
    require(point.x==1584 && point.y==740,"Far offscreen position was not clamped.");
    const RECT leftMonitor{-1920,-200,0,880};
    point=sb::window::clampOrigin({-1700,-100},size,leftMonitor);
    require(point.x==-1700 && point.y==-100,"Valid negative monitor coordinates changed.");
    point=sb::window::clampOrigin({10000,10000},{3000,2000},work);
    require(point.x==0 && point.y==0,"Oversized palette did not keep the caption reachable.");
    require(!sb::window::useSavedPlacement(0,true,true),"Old borderless placement was reused.");
    require(!sb::window::useSavedPlacement(1,true,false),"Incomplete saved placement was used.");
    require(sb::window::useSavedPlacement(1,true,true),"Current placement was not restored.");
    require(!sb::window::useSavedPlacement(2,true,true),"Unknown placement version was used.");
    require(sb::window::isCloseRequest(WM_CLOSE,0),"WM_CLOSE was not routed.");
    require(sb::window::isCloseRequest(WM_SYSCOMMAND,SC_CLOSE),"SC_CLOSE was not routed.");
    require(sb::window::isCloseRequest(WM_COMMAND,IDCANCEL),"Dialog-manager Close was not routed.");
    require(sb::window::isCloseRequest(WM_COMMAND,IDC_CLOSE),"Close button was not routed.");
    require(!sb::window::isCloseRequest(WM_SYSCOMMAND,SC_MOVE),"Move was mistaken for close.");
    require(!sb::window::isCloseRequest(WM_COMMAND,IDC_REFRESH),"Refresh was mistaken for close.");
    require(sb::window::isAltF4(WM_SYSKEYDOWN,VK_F4,LPARAM{1}<<29),"Alt+F4 was not routed.");
    require(!sb::window::isAltF4(WM_KEYDOWN,VK_F4,0),"Ordinary F4 was mistaken for close.");
    require(!sb::window::isAltF4(WM_SYSKEYDOWN,VK_F4,0),"F4 without Alt was mistaken for close.");
}
} // namespace

int main() {
    HWND owner{};
    try {
        geometry();
        HINSTANCE instance=GetModuleHandleW(nullptr);
        const wchar_t *className=L"SetbiaserWindowRegressionHost";
        WNDCLASSW wc{};
        wc.hInstance=instance; wc.lpfnWndProc=DefWindowProcW; wc.lpszClassName=className;
        require(RegisterClassW(&wc)!=0,"Could not register regression host.");
        owner=CreateWindowExW(0,className,L"Setbiaser window regression host",WS_OVERLAPPEDWINDOW,
            100,100,800,650,nullptr,nullptr,instance,nullptr);
        require(owner!=nullptr,"Could not create regression host.");
        ShowWindow(owner,SW_SHOWNOACTIVATE);
        HWND window=createPalette(instance,owner);
        const HMENU menu=GetSystemMenu(window,FALSE);
        require(menu!=nullptr,"System menu is absent.");
        for (UINT command : {SC_MOVE,SC_CLOSE}) {
            const UINT flags=GetMenuState(menu,command,MF_BYCOMMAND);
            require(flags!=static_cast<UINT>(-1) && !(flags&(MF_DISABLED|MF_GRAYED)),
                    "Native Move or Close is disabled.");
        }
        RECT r{},client{};
        GetWindowRect(window,&r); GetClientRect(window,&client);
        POINT clientTop{0,0}; ClientToScreen(window,&clientTop);
        require(clientTop.y>r.top,"Caption has no height.");
        const LPARAM captionPoint=MAKELPARAM(r.left+70,r.top+(clientTop.y-r.top)/2);
        require(SendMessageW(window,WM_NCHITTEST,0,captionPoint)==HTCAPTION,
                "The title bar does not expose a draggable caption.");
        RECT ownerRect{}; GetWindowRect(owner,&ownerRect);
        MONITORINFO monitor{}; monitor.cbSize=sizeof monitor;
        GetMonitorInfoW(MonitorFromWindow(owner,MONITOR_DEFAULTTONEAREST),&monitor);
        const SIZE size{r.right-r.left,r.bottom-r.top};
        const auto expected=sb::window::centeredOrigin(ownerRect,size,monitor.rcWork);
        require(r.left==expected.x && r.top==expected.y,"Native palette did not center on its owner.");
        const POINT saved=sb::window::clampOrigin({r.left+20,r.top+20},size,monitor.rcWork);
        require(sb::window::positionPalette(window,owner,saved),"Saved placement failed.");
        GetWindowRect(window,&r);
        require(r.left==saved.x && r.top==saved.y,"Saved position was not applied.");
        require(sb::window::positionPalette(window,owner,POINT{100000,100000}),"Offscreen restore failed.");
        GetWindowRect(window,&r);
        GetMonitorInfoW(MonitorFromWindow(window,MONITOR_DEFAULTTONEAREST),&monitor);
        require(r.left>=monitor.rcWork.left && r.top>=monitor.rcWork.top &&
                r.right<=monitor.rcWork.right && r.bottom<=monitor.rcWork.bottom,
                "Restored palette is outside the monitor work area.");
        SendMessageW(window,WM_SYSCOMMAND,SC_CLOSE,0);
        require(!IsWindow(window),"System-menu/caption close did not destroy the palette.");
        window=createPalette(instance,owner);
        SendMessageW(GetDlgItem(window,IDC_CLOSE),BM_CLICK,0,0);
        require(!IsWindow(window),"Explicit Close button did not destroy the palette.");
        window=createPalette(instance,owner);
        SendMessageW(window,WM_COMMAND,IDCANCEL,0);
        require(!IsWindow(window),"IDCANCEL did not close the palette.");
        window=createPalette(instance,owner);
        SendMessageW(window,WM_CLOSE,0,0);
        require(!IsWindow(window),"WM_CLOSE did not destroy the palette.");
        window=createPalette(instance,owner);
        MSG escape{}; escape.hwnd=GetDlgItem(window,IDC_VALUE0);
        escape.message=WM_KEYDOWN; escape.wParam=VK_ESCAPE;
        require(IsDialogMessageW(window,&escape)!=FALSE,"Dialog manager did not handle Escape.");
        require(!IsWindow(window),"Idle Escape did not close the palette.");

        // Reproduce the reported root cause independently of the corrected RC.
        struct alignas(DWORD) EmbeddedTemplate {
            DLGTEMPLATE dialog{};
            WORD menu{}, className{}, title{};
        } bad;
        bad.dialog.style=WS_POPUP|WS_CAPTION|WS_SYSMENU|DS_CONTROL;
        bad.dialog.cx=100; bad.dialog.cy=50;
        window=CreateDialogIndirectParamW(instance,&bad.dialog,owner,procedure,0);
        require(window!=nullptr,"Could not reproduce DS_CONTROL regression.");
        require(!sb::window::hasPaletteFrame(window),"The regression guard accepted DS_CONTROL.");
        const auto style=static_cast<DWORD>(GetWindowLongPtrW(window,GWL_STYLE));
        require(!(style&WS_CAPTION) && !(style&WS_SYSMENU),
                "DS_CONTROL did not reproduce the missing-caption symptom.");
        DestroyWindow(window);
        require(IsWindowEnabled(owner)!=FALSE,"Host remained disabled after palette closure.");
        DestroyWindow(owner); owner=nullptr;
        UnregisterClassW(className,instance);
        std::cout<<"PASS: "<<checks<<" native Setbiaser window checks. A:M integration is not tested.\n";
        return 0;
    } catch (const std::exception &e) {
        if(owner) DestroyWindow(owner);
        std::cerr<<"FAIL: "<<e.what()<<" (Win32 error "<<GetLastError()<<")\n";
        return 1;
    }
}
