#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <algorithm>
#include <optional>
#include "resource.h"

namespace sb::window {
// DS_CONTROL is for embedded sub-dialogs: Windows strips WS_CAPTION and
// WS_SYSMENU when it is set. Never use it for this owned top-level palette.
inline bool hasPaletteFrame(HWND window) noexcept {
    const auto style = static_cast<DWORD>(GetWindowLongPtrW(window, GWL_STYLE));
    constexpr DWORD required = WS_POPUP | WS_CAPTION | WS_SYSMENU;
    return (style & required) == required && !(style & (WS_CHILD | DS_CONTROL));
}
inline bool isCloseRequest(UINT message, WPARAM wparam) noexcept {
    if (message == WM_CLOSE) return true;
    if (message == WM_SYSCOMMAND) return (wparam & 0xfff0U) == SC_CLOSE;
    return message == WM_COMMAND &&
        (LOWORD(wparam) == IDC_CLOSE || LOWORD(wparam) == IDCANCEL);
}
inline bool isAltF4(UINT message, WPARAM wparam, LPARAM lparam) noexcept {
    return message == WM_SYSKEYDOWN && wparam == VK_F4 &&
        (static_cast<ULONG_PTR>(lparam) & (ULONG_PTR{1} << 29)) != 0;
}
inline bool useSavedPlacement(DWORD version, bool hasX, bool hasY) noexcept {
    // Ignore coordinates saved by the old unmovable, borderless 0.1.0 palette.
    return version == 1 && hasX && hasY;
}
inline POINT clampOrigin(POINT point, SIZE size, const RECT &work) noexcept {
    point.x = (std::max)(work.left, (std::min)(point.x, work.right - size.cx));
    point.y = (std::max)(work.top, (std::min)(point.y, work.bottom - size.cy));
    return point;
}
inline POINT centeredOrigin(const RECT &owner, SIZE size, const RECT &work) noexcept {
    return clampOrigin({owner.left + ((owner.right - owner.left) - size.cx) / 2,
                        owner.top + ((owner.bottom - owner.top) - size.cy) / 2},
                       size, work);
}
inline bool positionPalette(HWND window, HWND owner, std::optional<POINT> saved = {}) noexcept {
    RECT current{};
    if (!GetWindowRect(window, &current)) return false;
    const SIZE size{current.right - current.left, current.bottom - current.top};
    const HMONITOR monitor = saved
        ? MonitorFromPoint(*saved, MONITOR_DEFAULTTONEAREST)
        : MonitorFromWindow(owner, MONITOR_DEFAULTTONEAREST);
    MONITORINFO info{};
    info.cbSize = sizeof info;
    if (!GetMonitorInfoW(monitor, &info)) return false;
    RECT anchor = info.rcWork;
    if (owner && !IsIconic(owner)) {
        RECT ownerRect{};
        if (GetWindowRect(owner, &ownerRect)) anchor = ownerRect;
    }
    const POINT point = saved ? clampOrigin(*saved, size, info.rcWork)
                             : centeredOrigin(anchor, size, info.rcWork);
    return SetWindowPos(window, nullptr, point.x, point.y, 0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE) != FALSE;
}
} // namespace sb::window
