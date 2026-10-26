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
void CALLBACK watchdog(HWND window, UINT, UINT_PTR id, DWORD) {
    KillTimer(window, id); timeout = true; EndDialog(window, IDCANCEL);
}
void CALLBACK nextAction(HWND window, UINT, UINT_PTR id, DWORD) {
    KillTimer(window, id);
    if (calls == 1) {
        SetDlgItemTextW(window, IDC_FW2_TEXT, L"Second stamp");
        SetDlgItemTextW(window, IDC_FW2_HEIGHT, L"12.5");
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
    for (int test = 0; test < 3; ++test) {
        mode = test; dialog = nullptr; calls = 0; timeout = false; closedLabel = false;
        fw2::Options options;
        std::vector<fw2::Options> generated;
        const HHOOK hook = SetWindowsHookExW(WH_CBT, activated, nullptr, GetCurrentThreadId());
        require(hook != nullptr);
        const auto result = fw2::ShowWizard(GetModuleHandleW(nullptr), nullptr, options, true,
            [&](const fw2::Options &values) -> fw2::StampResult {
                generated.push_back(values); ++calls;
                if (test == 2) SetTimer(dialog, 0xF201, 10, nextAction);
                return {nullptr, static_cast<std::uint32_t>(calls + 2)};
            });
        UnhookWindowsHookEx(hook);
        require(!timeout && dialog != nullptr);
        const int expected = test == 2 ? 2 : test;
        require(calls == expected && result.stamps == static_cast<std::uint32_t>(expected));
        if (test == 0) require(result.splines == 0);
        if (test == 1) require(result.splines == 3 && result.text == L"First stamp" && !options.keepOpen);
        if (test == 2) {
            require(result.splines == 7 && result.text == L"Second stamp" && closedLabel);
            require(generated[0].text == L"First stamp" && generated[1].text == L"Second stamp");
            require(generated[1].height == 12.5F && generated[1].newModel && options.keepOpen);
        }
    }
}
