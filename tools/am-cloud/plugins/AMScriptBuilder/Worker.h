#pragma once
// Windows process supervision only. Does not include or call the A:M SDK.
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

namespace amscript {
class Handle {
    HANDLE value = nullptr;
public:
    Handle() = default;
    explicit Handle(HANDLE h) : value(h) {}
    ~Handle() { reset(); }
    Handle(const Handle&) = delete;
    Handle& operator=(const Handle&) = delete;
    HANDLE get() const { return value; }
    void reset(HANDLE next = nullptr) {
        if (value && value != INVALID_HANDLE_VALUE) CloseHandle(value);
        value = next;
    }
};
inline void RequireWin(BOOL result, const char* operation) {
    if (!result) throw std::runtime_error(std::string(operation) + " failed; Windows error " + std::to_string(GetLastError()));
}
inline std::wstring Quote(const std::wstring& value) {
    if (value.find(L'\0') != std::wstring::npos) throw std::runtime_error("NUL in process argument");
    std::wstring result = L"\"";
    std::size_t slashes = 0;
    for (wchar_t c : value) {
        if (c == L'\\') { ++slashes; continue; }
        result.append(slashes * (c == L'"' ? 2 : 1), L'\\'); slashes = 0;
        if (c == L'"') result += L'\\';
        result += c;
    }
    result.append(slashes * 2, L'\\');
    return result + L'"';
}

class Worker {
    Handle process, job, outRead, errRead;
    ULONGLONG started = 0;
    DWORD timeout = 15000;
    bool complete = false;
    DWORD exitCode = 0;
    static void Pipe(Handle& read, Handle& write) {
        SECURITY_ATTRIBUTES sa{sizeof(sa), nullptr, TRUE};
        HANDLE r = nullptr, w = nullptr;
        RequireWin(CreatePipe(&r, &w, &sa, 0), "CreatePipe");
        read.reset(r); write.reset(w);
        RequireWin(SetHandleInformation(r, HANDLE_FLAG_INHERIT, 0), "SetHandleInformation");
    }
    static void Drain(HANDLE pipe, std::string& into, std::size_t limit) {
        // Bounded work per timer tick; a flood cannot starve cancellation.
        std::size_t budget = 65536;
        while (budget) {
            DWORD available = 0;
            if (!PeekNamedPipe(pipe, nullptr, 0, nullptr, &available, nullptr)) {
                if (GetLastError() == ERROR_BROKEN_PIPE) return;
                RequireWin(FALSE, "PeekNamedPipe");
            }
            if (!available) return;
            char bytes[4096]; DWORD count = 0;
            const DWORD wanted = (std::min)(available, static_cast<DWORD>(sizeof(bytes)));
            RequireWin(ReadFile(pipe, bytes, wanted, &count, nullptr), "ReadFile(pipe)");
            if (!count) return;
            if (into.size() + count > limit) throw std::runtime_error("Python exceeded stdout/stderr limit");
            into.append(bytes, count);
            budget -= (std::min)(budget, static_cast<std::size_t>(count));
        }
    }
public:
    std::string output, errors;
    Worker() = default;
    ~Worker() { stop(); }
    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;
    void stop() noexcept {
        // An assigned process (including any children) is terminated on close.
        job.reset();
        if (process.get()) {
            // Also cover a failure before assignment while CREATE_SUSPENDED.
            if (WaitForSingleObject(process.get(), 0) != WAIT_OBJECT_0) {
                TerminateProcess(process.get(), 1);
                WaitForSingleObject(process.get(), 2000);
            }
            process.reset();
        }
    }
    void start(const std::wstring& executable, const std::vector<std::wstring>& arguments,
               const std::wstring& directory, DWORD milliseconds = 15000) {
        if (process.get() || started) throw std::runtime_error("Worker cannot be reused");
        if (!milliseconds || milliseconds > 15000) throw std::runtime_error("Invalid worker deadline");
        timeout = milliseconds;
        Handle outWrite, errWrite;
        Pipe(outRead, outWrite); Pipe(errRead, errWrite);
        SECURITY_ATTRIBUTES sa{sizeof(sa), nullptr, TRUE};
        Handle input(CreateFileW(L"NUL", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                 &sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));
        RequireWin(input.get() != INVALID_HANDLE_VALUE, "Open stdin NUL");
        job.reset(CreateJobObjectW(nullptr, nullptr));
        RequireWin(job.get() != nullptr, "CreateJobObject");
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits{};
        limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE |
            JOB_OBJECT_LIMIT_ACTIVE_PROCESS | JOB_OBJECT_LIMIT_PROCESS_MEMORY;
        limits.BasicLimitInformation.ActiveProcessLimit = 1;
        limits.ProcessMemoryLimit = 512ULL * 1024 * 1024;
        RequireWin(SetInformationJobObject(job.get(), JobObjectExtendedLimitInformation,
                                          &limits, sizeof(limits)), "SetInformationJobObject");
        SIZE_T bytes = 0;
        InitializeProcThreadAttributeList(nullptr, 1, 0, &bytes);
        if (!bytes) throw std::runtime_error("Missing attribute-list size");
        std::vector<unsigned char> storage(bytes);
        auto attributes = reinterpret_cast<LPPROC_THREAD_ATTRIBUTE_LIST>(storage.data());
        RequireWin(InitializeProcThreadAttributeList(attributes, 1, 0, &bytes), "Initialize attributes");
        struct DeleteAttributes {
            LPPROC_THREAD_ATTRIBUTE_LIST p;
            ~DeleteAttributes() { DeleteProcThreadAttributeList(p); }
        } cleanup{attributes};
        HANDLE inherit[] = {input.get(), outWrite.get(), errWrite.get()};
        RequireWin(UpdateProcThreadAttribute(attributes, 0, PROC_THREAD_ATTRIBUTE_HANDLE_LIST,
                                             inherit, sizeof(inherit), nullptr, nullptr), "Limit inherited handles");
        STARTUPINFOEXW startup{};
        startup.StartupInfo.cb = sizeof(startup);
        startup.StartupInfo.dwFlags = STARTF_USESTDHANDLES;
        startup.StartupInfo.hStdInput = input.get();
        startup.StartupInfo.hStdOutput = outWrite.get();
        startup.StartupInfo.hStdError = errWrite.get();
        startup.lpAttributeList = attributes;
        std::wstring command = Quote(executable);
        for (const auto& arg : arguments) command += L" " + Quote(arg);
        if (command.size() >= 32767) throw std::runtime_error("Python command line too long");
        PROCESS_INFORMATION info{};
        // Explicit executable, no cmd.exe, shell expansion, PATH search or network launcher.
        RequireWin(CreateProcessW(executable.c_str(), command.data(), nullptr, nullptr, TRUE,
            CREATE_SUSPENDED | CREATE_NO_WINDOW | EXTENDED_STARTUPINFO_PRESENT,
            nullptr, directory.c_str(), &startup.StartupInfo, &info), "CreateProcessW");
        process.reset(info.hProcess); Handle thread(info.hThread);
        RequireWin(AssignProcessToJobObject(job.get(), process.get()), "AssignProcessToJobObject");
        started = GetTickCount64();
        RequireWin(ResumeThread(thread.get()) != static_cast<DWORD>(-1), "ResumeThread");
    }
    bool poll() {
        if (complete) return true;
        if (!process.get()) throw std::runtime_error("Worker not running");
        Drain(outRead.get(), output, 262144);
        Drain(errRead.get(), errors, 16384);
        const DWORD state = WaitForSingleObject(process.get(), 0);
        if (state == WAIT_FAILED) RequireWin(FALSE, "WaitForSingleObject");
        if (GetTickCount64() - started >= timeout) throw std::runtime_error("Python exceeded its time limit");
        if (state != WAIT_OBJECT_0) return false;
        // A pipe can still hold data after process exit. Drain again next tick.
        DWORD outLeft = 0, errLeft = 0;
        if (!PeekNamedPipe(outRead.get(), nullptr, 0, nullptr, &outLeft, nullptr) && GetLastError() != ERROR_BROKEN_PIPE)
            RequireWin(FALSE, "Final stdout inspection");
        if (!PeekNamedPipe(errRead.get(), nullptr, 0, nullptr, &errLeft, nullptr) && GetLastError() != ERROR_BROKEN_PIPE)
            RequireWin(FALSE, "Final stderr inspection");
        if (outLeft || errLeft) return false;
        RequireWin(GetExitCodeProcess(process.get(), &exitCode), "GetExitCodeProcess");
        complete = true; stop();
        if (exitCode != 0) throw std::runtime_error("Python exited with code " + std::to_string(exitCode));
        return true;
    }
};
} // namespace amscript
