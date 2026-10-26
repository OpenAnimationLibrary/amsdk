#include "Wizard.h"
#include "resource.h"
#include <stdexcept>
#include <vector>

namespace {
HWND dialog = nullptr;
int mode = 0;
int calls = 0;
bool timeout = false;
bool closedLabel = false;
HWND modelWindow = nullptr;
HWND modelEdit = nullptr;
bool modelInteracted = false;
void CALLBACK watchdog(HWND window, UINT, UINT_PTR id, DWORD) {
    KillTimer(window, id); timeout = true; DestroyWindow(window);
}
void CALLBACK nextAction(HWND window, UINT, UINT_PTR id, DWORD) {
    KillTimer(window, id);
    if (calls == 1) {
        wchar_t moved[16]{}; GetWindowTextW(modelEdit, moved, 16);
        modelInteracted = IsWindowEnabled(modelWindow) && std::wstring(moved) == L"x";
        SetDlgItemTextW(window, IDC_FW2_TEXT, L"Second stamp");
        SetDlgItemTextW(window, IDC_FW2_HEIGHT, L"12.5");
        CheckDlgButton(window, IDC_FW2_APPLY_COLOR, BST_CHECKED);
        PostMessageW(window, WM_COMMAND, IDOK, 0);
    } else {
        wchar_t text[32]{}; GetDlgItemTextW(window, IDCANCEL, text, 32);
        closedLabel = std::wstring(text) == L"Close";
        PostMessageW(window, WM_CLOSE, 0, 0);
    }
}
LRESULT CALLBACK activated(int code, WPARAM wparam, LPARAM lparam) {
    if (code == HCBT_ACTIVATE && !dialog) {
        const HWND window = reinterpret_cast<HWND>(wparam);
        wchar_t title[64]{}; GetWindowTextW(window, title, 64);
        if (std::wstring(title) == L"FontWiz2 - Text Geometry") {
            dialog = window;
            SetTimer(window, 0xF2FF, 10000, watchdog);
            SetDlgItemTextW(window, IDC_FW2_TEXT, L"First stamp");
            CheckDlgButton(window, IDC_FW2_KEEP_OPEN, mode == 2 ? BST_CHECKED : BST_UNCHECKED);
            PostMessageW(window, WM_COMMAND, mode == 0 ? IDCANCEL : IDOK, 0);
        }
    }
    return CallNextHookEx(nullptr, code, wparam, lparam);
}
void require(bool condition) { if (!condition) throw std::runtime_error("FontWiz2 modal stamping test failed."); }
}

void TestFontWiz2Wizard() {
    modelWindow = CreateWindowExW(0, L"STATIC", L"Model interaction test", WS_OVERLAPPEDWINDOW,
        0, 0, 200, 100, nullptr, nullptr, GetModuleHandleW(nullptr), nullptr);
    require(modelWindow != nullptr);
    modelEdit = CreateWindowExW(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
        0, 0, 100, 30, modelWindow, nullptr, GetModuleHandleW(nullptr), nullptr);
    require(modelEdit != nullptr);
    ShowWindow(modelWindow, SW_SHOW);
    for (int test = 0; test < 3; ++test) {
        mode = test; dialog = nullptr; calls = 0; timeout = false; closedLabel = false;
        modelInteracted = false; SetWindowTextW(modelEdit, L"");
        fw2::Options options;
        std::vector<fw2::Options> generated;
        const HHOOK hook = SetWindowsHookExW(WH_CBT, activated, nullptr, GetCurrentThreadId());
        require(hook != nullptr);
        const auto result = fw2::ShowWizard(GetModuleHandleW(nullptr), modelWindow, options, true,
            [&](const fw2::Options &values) -> fw2::StampResult {
                generated.push_back(values); ++calls;
                if (test == 2) {
                    if (calls == 1) PostMessageW(modelEdit, WM_CHAR, L'x', 0);
                    SetTimer(dialog, 0xF201, 10, nextAction);
                }
                return {nullptr, static_cast<std::uint32_t>(calls + 2)};
            });
        UnhookWindowsHookEx(hook);
        require(!timeout && dialog != nullptr);
        const int expected = test == 2 ? 2 : test;
        require(calls == expected && result.stamps == static_cast<std::uint32_t>(expected));
        if (test == 0) require(result.splines == 0);
        if (test == 1) require(result.splines == 3 && result.text == L"First stamp" && !options.keepOpen);
        if (test == 2) {
            require(result.splines == 7 && result.text == L"Second stamp" && closedLabel && modelInteracted);
            require(generated[0].text == L"First stamp" && generated[1].text == L"Second stamp");
            require(generated[1].height == 12.5F && generated[1].newModel && options.keepOpen);
            require(!generated[0].applyColor && generated[1].applyColor);
        }
    }
    // The standalone command must return to A:M's own message loop immediately.
    bool finished = false;
    fw2::Options options;
    const HWND asynchronous = fw2::OpenWizard(GetModuleHandleW(nullptr), modelWindow, options, true,
        [](const fw2::Options &) { return fw2::StampResult{}; },
        [&](const fw2::Options &, const fw2::WizardResult &result) { finished = true; require(result.stamps == 0); });
    require(IsWindow(asynchronous) && !finished && IsWindowEnabled(modelWindow));
    SendMessageW(asynchronous, WM_CLOSE, 0, 0);
    require(finished && !IsWindow(asynchronous));
    // WM_QUIT must survive the synchronous V1 adapter and its window must close.
    PostQuitMessage(97);
    const auto quit = fw2::ShowWizard(GetModuleHandleW(nullptr), modelWindow, options, true,
        [](const fw2::Options &) { return fw2::StampResult{}; });
    MSG message{};
    require(quit.stamps == 0 && PeekMessageW(&message, nullptr, WM_QUIT, WM_QUIT, PM_REMOVE) && message.wParam == 97);
    DestroyWindow(modelWindow);
}
