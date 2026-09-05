#pragma once
#include <windows.h>
#include <filesystem>
#include <string>
#include <system_error>
namespace patchdraw {
// Create-only: never overwrite a model, an existing JSON file, or a symlink.
inline void SaveNewPlan(const std::filesystem::path& path, const std::string& bytes) {
    if (_wcsicmp(path.extension().c_str(), L".json") != 0 || bytes.empty() || bytes.size()>262144)
        throw std::invalid_argument("Export needs a new .json filename and a bounded plan.");
    HANDLE file=CreateFileW(path.c_str(),GENERIC_WRITE|DELETE,0,nullptr,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(file==INVALID_HANDLE_VALUE) throw std::system_error(static_cast<int>(GetLastError()),std::system_category(),"Create new JSON (existing files are never overwritten)");
    DWORD written=0, error=ERROR_SUCCESS;
    if(!WriteFile(file,bytes.data(),static_cast<DWORD>(bytes.size()),&written,nullptr)) error=GetLastError();
    else if(written!=bytes.size()) error=ERROR_WRITE_FAULT;
    else if(!FlushFileBuffers(file)) error=GetLastError();
    if(error!=ERROR_SUCCESS) {
        FILE_DISPOSITION_INFO remove{TRUE};
        SetFileInformationByHandle(file,FileDispositionInfo,&remove,sizeof(remove));
    }
    CloseHandle(file);
    if(error!=ERROR_SUCCESS) throw std::system_error(static_cast<int>(error),std::system_category(),"Write JSON (incomplete new-file cleanup attempted)");
}
} // namespace patchdraw
