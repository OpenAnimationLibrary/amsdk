#include "ModelCopy.h"
#include <commdlg.h>
#include <array>
#include <cwchar>
#include <filesystem>
#include <stdexcept>

namespace fw2 {
std::wstring ChooseModelCopy(HWND owner) {
    std::array<wchar_t, 32768> filename{};
    wcscpy_s(filename.data(), filename.size(), L"FontWiz2-model.mdl");
    OPENFILENAMEW dialog{}; dialog.lStructSize = sizeof(dialog); dialog.hwndOwner = owner;
    dialog.lpstrFile = filename.data(); dialog.nMaxFile = static_cast<DWORD>(filename.size());
    dialog.lpstrFilter = L"A:M model (*.mdl)\0*.mdl\0\0"; dialog.lpstrDefExt = L"mdl";
    dialog.lpstrTitle = L"Save current model copy";
    dialog.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
    if (GetSaveFileNameW(&dialog)) {
        const std::wstring path = filename.data();
        if (_wcsicmp(std::filesystem::path(path).extension().c_str(), L".mdl") != 0)
            throw std::runtime_error("Choose a .mdl filename for the model copy.");
        return path;
    }
    if (CommDlgExtendedError()) throw std::runtime_error("The model-copy file dialog could not be opened.");
    return {};
}
void WriteModelCopy(const std::wstring &path, const std::string &bytes) {
    if (bytes.empty() || bytes.size() > 256 * 1024 * 1024)
        throw std::runtime_error("The model copy is empty or exceeds 256 MiB.");
    static LONG sequence = 0;
    for (int attempt = 0; attempt < 16; ++attempt) {
        const std::wstring temporary = path + L".tmp-" + std::to_wstring(GetCurrentProcessId()) + L"-" +
            std::to_wstring(InterlockedIncrement(&sequence));
        HANDLE file = CreateFileW(temporary.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE) {
            if (GetLastError() == ERROR_FILE_EXISTS) continue;
            throw std::runtime_error("The model copy could not be created in this folder. Text remains in A:M.");
        }
        try {
            DWORD written = 0;
            if (!WriteFile(file, bytes.data(), static_cast<DWORD>(bytes.size()), &written, nullptr) ||
                written != bytes.size() || !FlushFileBuffers(file))
                throw std::runtime_error("The model copy could not be fully written. The previous file was preserved.");
            const BOOL closed = CloseHandle(file); file = INVALID_HANDLE_VALUE;
            if (!closed || !MoveFileExW(temporary.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
                throw std::runtime_error("The model copy could not be replaced. The previous file was preserved.");
        } catch (...) {
            if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
            DeleteFileW(temporary.c_str()); throw;
        }
        return;
    }
    throw std::runtime_error("A temporary model-copy file could not be created.");
}
}
