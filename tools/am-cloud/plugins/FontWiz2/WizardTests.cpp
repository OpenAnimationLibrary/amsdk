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
void require(bool condition) { if (!condition) throw std::runtime_error("FontWiz2 modeless input/stamping test failed."); }
void click(HWND window, int id) {
    const HWND button = GetDlgItem(window, id);
    PostMessageW(button, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(5, 5));
    PostMessageW(button, WM_LBUTTONUP, 0, MAKELPARAM(5, 5));
}
void type(HWND edit, const wchar_t *text) {
    for (; *text; ++text) PostMessageW(edit, WM_CHAR, static_cast<WPARAM>(*text), 0);
}
bool nestedInputPreserved = false;
LRESULT CALLBACK nestedInput(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    if (message == WM_LBUTTONDOWN) {
        MSG next{};
        nestedInputPreserved = PeekMessageW(&next, window, WM_LBUTTONUP, WM_LBUTTONUP, PM_REMOVE) &&
            next.hwnd == window && next.message == WM_LBUTTONUP;
        return 0;
    }
    return DefWindowProcW(window, message, wparam, lparam);
}
void TestFilteredInput() {
    bool finished = false;
    unsigned creations = 0, leaked = 0;
    fw2::WizardResult result;
    std::vector<fw2::Options> generated;
    fw2::Options options;
    options.keepOpen = false; // Exercise turning it on with a control click.
    timeout = false;
    SetWindowTextW(modelEdit, L"");
    const HWND window = fw2::OpenWizard(GetModuleHandleW(nullptr), modelWindow, options, true,
        [&](const fw2::Options &values) {
            ++creations; generated.push_back(values); return fw2::StampResult{nullptr, 3};
        }, [&](const fw2::Options &, const fw2::WizardResult &value) { result = value; finished = true; });
    SetTimer(window, 0xF2FF, 10000, watchdog);
    WNDCLASSW nestedClass{}; nestedClass.lpfnWndProc = nestedInput;
    nestedClass.hInstance = GetModuleHandleW(nullptr); nestedClass.lpszClassName = L"FontWiz2NestedInputTest";
    require(RegisterClassW(&nestedClass) != 0);
    const HWND nested = CreateWindowW(nestedClass.lpszClassName, L"", WS_CHILD,
        0, 0, 1, 1, window, nullptr, nestedClass.hInstance, nullptr);
    require(nested != nullptr);
    const HWND edit = GetDlgItem(window, IDC_FW2_TEXT);
    SetWindowTextW(edit, L"");
    SetFocus(edit);
    type(edit, L"Input works");
    PostMessageW(GetDlgItem(window, IDC_FW2_SUBDIVIDE), WM_KEYDOWN, VK_END, 0);
    click(window, IDC_FW2_KEEP_OPEN);
    click(window, IDC_FW2_APPLY_COLOR);
    click(window, IDOK);
    PostMessageW(modelEdit, WM_CHAR, L'm', 0);
    PostMessageW(nested, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));
    PostMessageW(nested, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
    constexpr UINT checkpoint = WM_APP + 42;
    PostThreadMessageW(GetCurrentThreadId(), checkpoint, 0, 0);
    while (!finished) {
        MSG message{};
        require(GetMessageW(&message, nullptr, 0, 0) > 0);
        if (!message.hwnd && message.message == checkpoint) {
            require(creations == 1 && IsWindow(window) && IsWindowEnabled(window) && nestedInputPreserved);
            require(IsWindowEnabled(modelWindow) && IsWindowEnabled(GetDlgItem(window, IDC_FW2_COLOR)));
            require(generated[0].text == L"Input works" && generated[0].keepOpen && generated[0].applyColor);
            require(SendDlgItemMessageW(window, IDC_FW2_SUBDIVIDE, CB_GETCURSEL, 0, 0) == 2);
            wchar_t received[8]{}; GetWindowTextW(modelEdit, received, 8);
            require(std::wstring(received) == L"m");
            SetWindowTextW(edit, L"");
            type(edit, L"Second input");
            click(window, IDC_FW2_KEEP_OPEN);
            click(window, IDOK);
            continue;
        }
        const bool input = (message.message >= WM_KEYFIRST && message.message <= WM_KEYLAST) ||
            (message.message >= WM_MOUSEFIRST && message.message <= WM_MOUSELAST);
        // Model A:M pretranslation which consumes input to an unknown palette.
        // No WM_COMMAND or BM_CLICK shortcuts: use the controls' input path.
        if (input && (message.hwnd == window || IsChild(window, message.hwnd))) {
            ++leaked; continue;
        }
        TranslateMessage(&message); DispatchMessageW(&message);
    }
    require(!timeout && leaked == 0 && creations == 2 && result.stamps == 2 && result.splines == 6);
    require(generated[1].text == L"Second input" && !generated[1].keepOpen);
    require(!IsWindow(window) && IsWindowEnabled(modelWindow));
    require(UnregisterClassW(nestedClass.lpszClassName, nestedClass.hInstance) != FALSE);
    // Keyboard navigation and Escape still work after mouse/typing dispatch.
    finished = false;
    const HWND cancel = fw2::OpenWizard(GetModuleHandleW(nullptr), modelWindow, options, true,
        [](const fw2::Options &) { return fw2::StampResult{}; },
        [&](const fw2::Options &, const fw2::WizardResult &value) { result = value; finished = true; });
    SetTimer(cancel, 0xF2FF, 10000, watchdog);
    SetFocus(GetDlgItem(cancel, IDC_FW2_TEXT));
    PostMessageW(GetDlgItem(cancel, IDC_FW2_TEXT), WM_KEYDOWN, VK_TAB, 0);
    PostThreadMessageW(GetCurrentThreadId(), checkpoint, 0, 0);
    while (!finished) {
        MSG message{}; require(GetMessageW(&message, nullptr, 0, 0) > 0);
        if (!message.hwnd && message.message == checkpoint) {
            require(GetFocus() == GetDlgItem(cancel, IDC_FW2_PICKFONT));
            PostMessageW(GetFocus(), WM_KEYDOWN, VK_ESCAPE, 0);
            continue;
        }
        TranslateMessage(&message); DispatchMessageW(&message);
    }
    require(!timeout && result.stamps == 0 && !IsWindow(cancel));
}
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
            require(generated[1].height == 12.5F && !generated[1].newModel && options.keepOpen);
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
    require(IsDlgButtonChecked(asynchronous, IDC_FW2_NEW) == BST_UNCHECKED);
    require(IsDlgButtonChecked(asynchronous, IDC_FW2_KEEP_OPEN) == BST_CHECKED);
    SendMessageW(asynchronous, WM_CLOSE, 0, 0);
    require(finished && !IsWindow(asynchronous));
    TestFilteredInput();
    // WM_QUIT must survive the synchronous V1 adapter and its window must close.
    PostQuitMessage(97);
    const auto quit = fw2::ShowWizard(GetModuleHandleW(nullptr), modelWindow, options, true,
        [](const fw2::Options &) { return fw2::StampResult{}; });
    MSG message{};
    require(quit.stamps == 0 && PeekMessageW(&message, nullptr, WM_QUIT, WM_QUIT, PM_REMOVE) && message.wParam == 97);
    DestroyWindow(modelWindow);
}
