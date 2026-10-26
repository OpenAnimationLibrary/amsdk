#include "Inspector.h"
#include "resource.h"
#include <commdlg.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

namespace fw2 {
namespace {
constexpr std::size_t limit = 16 * 1024 * 1024;
struct View {
    void *model;
    const InspectModel &inspect;
    std::wstring captured;
};
std::wstring file(HWND owner, bool save) {
    std::array<wchar_t, 32768> name{};
    if (save) wcscpy_s(name.data(), name.size(), L"FontWiz2-before-save.txt");
    OPENFILENAMEW choice{}; choice.lStructSize = sizeof(choice); choice.hwndOwner = owner;
    choice.lpstrFile = name.data(); choice.nMaxFile = static_cast<DWORD>(name.size());
    choice.lpstrFilter = save ? L"Text snapshot (*.txt)\0*.txt\0\0" : L"A:M model or text (*.mdl;*.txt)\0*.mdl;*.txt\0All files\0*.*\0\0";
    choice.lpstrDefExt = save ? L"txt" : L"mdl";
    choice.lpstrTitle = save ? L"Save captured text (does not save the A:M model)" : L"Read saved model for comparison";
    choice.Flags = OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY |
        (save ? OFN_OVERWRITEPROMPT : OFN_FILEMUSTEXIST);
    if (save ? GetSaveFileNameW(&choice) : GetOpenFileNameW(&choice)) return name.data();
    if (CommDlgExtendedError()) throw std::runtime_error("The comparison file dialog could not be opened.");
    return {};
}
INT_PTR CALLBACK procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    if (message == WM_INITDIALOG) {
        auto *view = reinterpret_cast<View *>(lparam);
        SetWindowLongPtrW(window, DWLP_USER, lparam);
        for (int id : {IDC_FW2_CURRENT_CODE, IDC_FW2_SAVED_CODE})
            SendDlgItemMessageW(window, id, EM_SETLIMITTEXT, limit, 0);
        SetDlgItemTextW(window, IDC_FW2_CURRENT_CODE, view->captured.c_str());
        return TRUE;
    }
    auto *view = reinterpret_cast<View *>(GetWindowLongPtrW(window, DWLP_USER));
    if (!view) return FALSE;
    try {
        if (message == WM_CLOSE || (message == WM_COMMAND && LOWORD(wparam) == IDCANCEL)) {
            EndDialog(window, 0); return TRUE;
        }
        if (message == WM_COMMAND) {
            switch (LOWORD(wparam)) {
            case IDC_FW2_CAPTURE_CODE: {
                // Preserve the original getter-only snapshot before asking the SDK to serialize.
                const auto code = view->inspect(view->model, true);
                if (view->captured.size() + code.size() > limit)
                    throw std::runtime_error("The snapshot exceeds the 16 MiB viewer limit.");
                view->captured += L"\r\n===== SDK MODEL SERIALIZATION =====\r\n" + code;
                SetDlgItemTextW(window, IDC_FW2_CURRENT_CODE, view->captured.c_str());
                EnableWindow(GetDlgItem(window, IDC_FW2_CAPTURE_CODE), FALSE);
                return TRUE;
            }
            case IDC_FW2_SAVE_SNAPSHOT: {
                const auto path = file(window, true);
                if (!path.empty()) SaveDiagnosticFile(path, view->captured);
                return TRUE;
            }
            case IDC_FW2_LOAD_MODEL: {
                const auto path = file(window, false);
                if (!path.empty()) {
                    const auto text = ReadDiagnosticFile(path);
                    SetDlgItemTextW(window, IDC_FW2_SAVED_CODE, text.c_str());
                }
                return TRUE;
            }
            }
        }
    } catch (const std::exception &error) {
        MessageBoxA(window, error.what(), "FontWiz2 Model Inspector", MB_OK | MB_ICONERROR);
    } catch (...) {
        MessageBoxW(window, L"The model snapshot could not be captured.", L"FontWiz2 Model Inspector", MB_OK | MB_ICONERROR);
    }
    return FALSE;
}
}
std::wstring DiagnosticText(const std::string &bytes) {
    if (bytes.size() > limit || bytes.find('\0') != std::string::npos)
        throw std::runtime_error("Expected an uncompressed text model of at most 16 MiB.");
    if (bytes.empty()) return {};
    UINT page = CP_UTF8; DWORD flags = MB_ERR_INVALID_CHARS;
    int count = MultiByteToWideChar(page, flags, bytes.data(), static_cast<int>(bytes.size()), nullptr, 0);
    if (!count) {
        page = CP_ACP; flags = 0;
        count = MultiByteToWideChar(page, flags, bytes.data(), static_cast<int>(bytes.size()), nullptr, 0);
    }
    if (!count) throw std::runtime_error("The model text could not be decoded.");
    std::wstring result(static_cast<std::size_t>(count), L'\0');
    if (!MultiByteToWideChar(page, flags, bytes.data(), static_cast<int>(bytes.size()), result.data(), count))
        throw std::runtime_error("The model text could not be decoded.");
    if (!result.empty() && result.front() == 0xFEFF) result.erase(0, 1);
    return result;
}
std::wstring ReadDiagnosticFile(const std::wstring &path) {
    std::ifstream stream(std::filesystem::path(path), std::ios::binary | std::ios::ate);
    if (!stream) throw std::runtime_error("The comparison file could not be opened.");
    const auto length = stream.tellg();
    if (length < 0 || length > static_cast<std::streamoff>(limit))
        throw std::runtime_error("The comparison file exceeds 16 MiB.");
    std::string bytes(static_cast<std::size_t>(length), '\0');
    stream.seekg(0);
    if (!stream.read(bytes.data(), static_cast<std::streamsize>(bytes.size())))
        throw std::runtime_error("The comparison file could not be read completely.");
    return DiagnosticText(bytes);
}
void SaveDiagnosticFile(const std::wstring &path, const std::wstring &text) {
    if (text.size() > limit) throw std::runtime_error("The snapshot exceeds 16 MiB.");
    const int length = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()), nullptr, 0, nullptr, nullptr);
    if (!length && !text.empty()) throw std::runtime_error("The snapshot could not be encoded.");
    std::string bytes(static_cast<std::size_t>(length), '\0');
    if (length && !WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text.data(), static_cast<int>(text.size()), bytes.data(), length, nullptr, nullptr))
        throw std::runtime_error("The snapshot could not be encoded.");
    std::ofstream stream(std::filesystem::path(path), std::ios::binary | std::ios::trunc);
    stream.write(bytes.data(), static_cast<std::streamsize>(bytes.size())); stream.flush();
    if (!stream) throw std::runtime_error("The snapshot could not be saved completely.");
}
void ShowModelInspector(HINSTANCE module, HWND owner, void *model, const InspectModel &inspect) {
    View view{model, inspect, inspect(model, false)};
    if (view.captured.size() > limit) throw std::runtime_error("The live report exceeds 16 MiB.");
    if (DialogBoxParamW(module, MAKEINTRESOURCEW(IDD_FW2_INSPECTOR), owner, procedure, reinterpret_cast<LPARAM>(&view)) == -1)
        throw std::runtime_error("The model inspector could not be opened.");
}
}
