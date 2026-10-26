#include "Inspector.h"
#include "ModelCopy.h"
#include "resource.h"
#include <fstream>
#include <filesystem>
#include <stdexcept>

namespace {
bool activated = false, checked = false;
void require(bool value) { if (!value) throw std::runtime_error("FontWiz2 inspector test failed."); }
void CALLBACK check(HWND window, UINT, UINT_PTR timer, DWORD) {
    KillTimer(window, timer);
    wchar_t text[512]{}; GetDlgItemTextW(window, IDC_FW2_CURRENT_CODE, text, 512);
    checked = std::wstring(text).find(L"getter snapshot") != std::wstring::npos &&
        std::wstring(text).find(L"<MODEL>test</MODEL>") != std::wstring::npos &&
        !IsWindowEnabled(GetDlgItem(window, IDC_FW2_CAPTURE_CODE));
    PostMessageW(window, WM_CLOSE, 0, 0);
}
LRESULT CALLBACK hook(int code, WPARAM wparam, LPARAM lparam) {
    if (code == HCBT_ACTIVATE) {
        const HWND window = reinterpret_cast<HWND>(wparam);
        wchar_t title[64]{}; GetWindowTextW(window, title, 64);
        if (std::wstring(title) == L"FontWiz2 - Model Inspector") {
            wchar_t text[64]{}; GetDlgItemTextW(window, IDC_FW2_CURRENT_CODE, text, 64);
            activated = std::wstring(text) == L"getter snapshot" &&
                (GetWindowLongPtrW(GetDlgItem(window, IDC_FW2_CURRENT_CODE), GWL_STYLE) & ES_READONLY);
            PostMessageW(window, WM_COMMAND, IDC_FW2_CAPTURE_CODE, 0);
            SetTimer(window, 77, 100, check);
        }
    }
    return CallNextHookEx(nullptr, code, wparam, lparam);
}
}
void TestFontWiz2Inspector() {
    wchar_t temp[MAX_PATH]{}, path[MAX_PATH]{};
    require(GetTempPathW(MAX_PATH, temp) != 0 && GetTempFileNameW(temp, L"fw2", 0, path) != 0);
    const std::wstring text = L"<MODEL>\r\nCaf\x00e9 \x03a9\r\n</MODEL>\r\n";
    fw2::SaveDiagnosticFile(path, text);
    require(fw2::ReadDiagnosticFile(path) == text);
    require(fw2::DiagnosticText("\xEF\xBB\xBF<MODEL>") == L"<MODEL>");
    bool rejected = false;
    try { (void)fw2::DiagnosticText(std::string("bad\0model", 9)); }
    catch (const std::exception &) { rejected = true; }
    require(rejected);
    { std::ofstream stream(std::filesystem::path(path), std::ios::binary | std::ios::trunc);
      stream.seekp(16 * 1024 * 1024); stream.put('x'); }
    rejected = false;
    try { (void)fw2::ReadDiagnosticFile(path); } catch (const std::exception &) { rejected = true; }
    require(rejected && DeleteFileW(path));
    require(GetTempFileNameW(temp, L"fw2", 0, path) != 0);
    const std::string modelBytes = "<MODELFILE>\r\nName=Caf\xE9\r\n</MODELFILE>\r\n";
    fw2::WriteModelCopy(path, modelBytes);
    const auto readBytes = [&]() {
        std::ifstream stream(std::filesystem::path(path), std::ios::binary);
        return std::string(std::istreambuf_iterator<char>(stream), {});
    };
    require(readBytes() == modelBytes); // Preserve SDK bytes; no UTF-8 conversion.
    const HANDLE locked = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    require(locked != INVALID_HANDLE_VALUE);
    rejected = false;
    try { fw2::WriteModelCopy(path, "replacement"); } catch (const std::exception &) { rejected = true; }
    CloseHandle(locked);
    require(rejected && readBytes() == modelBytes);
    fw2::WriteModelCopy(path, "second save");
    require(readBytes() == "second save");
    rejected = false;
    try { fw2::WriteModelCopy(path, ""); } catch (const std::exception &) { rejected = true; }
    require(rejected && readBytes() == "second save" && DeleteFileW(path));
    unsigned getter = 0, serializer = 0;
    const HHOOK input = SetWindowsHookExW(WH_CBT, hook, nullptr, GetCurrentThreadId());
    require(input != nullptr);
    fw2::ShowModelInspector(GetModuleHandleW(nullptr), nullptr, nullptr, [&](void *, bool code) {
        if (code) { ++serializer; return std::wstring(L"<MODEL>test</MODEL>"); }
        ++getter; return std::wstring(L"getter snapshot");
    });
    UnhookWindowsHookEx(input);
    require(activated && checked && getter == 1 && serializer == 1);
}
