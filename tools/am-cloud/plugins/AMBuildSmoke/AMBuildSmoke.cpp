#include "StdAfx.h"
#include "ObjType.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include <cstdio>

class HTreeObject;
CPluginApp theApp;

namespace {
struct TestContext {
    ObjectType type;
    const char *name;
};
// A diagnostic command does not dereference the supplied object. Register the
// contexts separately, as the SDK's Grid and ResampleSpline examples do.
constexpr TestContext kContexts[] = {
    {HOT_MODEL, "Model"}, {HOT_GROUP, "Group"}, {HOT_CP, "CP"},
    {HOT_CPINSTANCE, "CP instance"}, {HOT_ACTION, "Action"},
    {HOT_CHOR, "Choreography"}
};
constexpr uint32_t kContextCount = static_cast<uint32_t>(_countof(kContexts));
INIT_ONCE g_logInit = INIT_ONCE_STATIC_INIT;
wchar_t g_logPath[4096] = {};
LONG g_seen[40] = {};

HMODULE PluginModule() noexcept {
    HMODULE module = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                          GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                      reinterpret_cast<LPCWSTR>(&g_logInit), &module);
    return module;
}

void AppendLog(const wchar_t *text) noexcept {
    // No SDK calls here. Logging is only reached through exported callbacks,
    // never from a custom DllMain or CWinApp::InitInstance under loader lock.
    OutputDebugStringW(text);
    if (!g_logPath[0]) return;
    char utf8[32768] = {};
    const int bytes = WideCharToMultiByte(CP_UTF8, 0, text, -1, utf8,
                                        sizeof(utf8), nullptr, nullptr);
    if (bytes <= 1) return;
    const HANDLE file = CreateFileW(g_logPath, FILE_APPEND_DATA,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                   OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) return;
    DWORD written = 0;
    WriteFile(file, utf8, static_cast<DWORD>(bytes - 1), &written, nullptr);
    CloseHandle(file);
}

BOOL CALLBACK InitializeLog(PINIT_ONCE, PVOID, PVOID *) noexcept {
    wchar_t temp[4096] = {};
    const DWORD length = GetTempPathW(_countof(temp), temp);
    if (length > 0 && length < _countof(temp)) {
        if (_snwprintf_s(g_logPath, _countof(g_logPath), _TRUNCATE,
                         L"%lsAMBuildSmoke-v2-%lu.log", temp,
                         GetCurrentProcessId()) < 0) {
            g_logPath[0] = L'\0';
        }
    }
    wchar_t host[4096] = L"<unavailable>";
    wchar_t plugin[4096] = L"<unavailable>";
    GetModuleFileNameW(nullptr, host, _countof(host));
    const HMODULE module = PluginModule();
    if (module) GetModuleFileNameW(module, plugin, _countof(plugin));
    host[_countof(host) - 1] = L'\0';
    plugin[_countof(plugin) - 1] = L'\0';
    wchar_t header[10000] = {};
    _snwprintf_s(header, _countof(header), _TRUNCATE,
                 L"\r\nAMBuildSmoke diagnostic v2; PID=%lu\r\n"
                 L"Host: %ls\r\nPlugin: %ls\r\n"
                 L"sizeof(MenuCategory)=%u; sizeof(ObjectType)=%u\r\n",
                 GetCurrentProcessId(), host, plugin,
                 static_cast<unsigned>(sizeof(MenuCategory)),
                 static_cast<unsigned>(sizeof(ObjectType)));
    AppendLog(header);
    return TRUE;
}

void LogOnce(unsigned event, const char *stage, uint32_t index,
             const HTreeObject *object = nullptr) noexcept {
    // Bound log traffic: once per stage/context/process, not every menu open.
    if (event >= _countof(g_seen) ||
        InterlockedCompareExchange(&g_seen[event], 1, 0) != 0) return;
    InitOnceExecuteOnce(&g_logInit, InitializeLog, nullptr, nullptr);
    SYSTEMTIME time = {};
    GetLocalTime(&time);
    wchar_t line[512] = {};
    _snwprintf_s(line, _countof(line), _TRUNCATE,
                 L"%02u:%02u:%02u.%03u %hs index=%u context=%hs object=%hs\r\n",
                 time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
                 stage, index,
                 index < kContextCount ? kContexts[index].name : "end",
                 object ? "present" : "null");
    AppendLog(line);
}
}  // namespace

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(
    const uint32_t index, ObjectType &objectType) {
    // This callback only exchanges enum values; no MFC state is needed.
    if (index <= kContextCount) LogOnce(index, "registration", index);
    if (index >= kContextCount) return FALSE;
    objectType = kContexts[index].type;
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const uint32_t index, String &menuName,
    MenuCategory &category, BOOL &disabled) {
    if (index >= kContextCount) return FALSE;
    LogOnce(8 + index, "menu-enter", index, object);
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    // A missing resource or null selection must not hide a diagnostic command.
    // The resource is still checked explicitly when the command is invoked.
    CString label;
    label.Format("A:M Cloud Build Test v2 - %s", kContexts[index].name);
    menuName = label;
    category = MC_WIZARD;
    disabled = FALSE;
    LogOnce(16 + index, "menu-return-true", index, object);
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(
    HTreeObject *object, const uint32_t index) {
    if (index >= kContextCount) return FALSE;
    LogOnce(24 + index, "command-enter", index, object);
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    const String version = GetAMVersion();
    char resource[256] = {};
    const HMODULE module = PluginModule();
    const bool resourceOK = module &&
        LoadStringA(module, 101, resource, _countof(resource)) > 0;
    CString message;
    message.Format("A:M Cloud Build Test v2\n\n"
                   "Context: %s\nA:M version: %s\n"
                   "Object supplied: %s\nMenu resource: %s\n\n"
                   "The SDK call returned. No model data was changed.\n"
                   "A local diagnostic log is attempted in the Windows TEMP "
                   "folder as AMBuildSmoke-v2-%lu.log.",
                   kContexts[index].name, version.Get(),
                   object ? "yes" : "no",
                   resourceOK ? "present" : "missing (menu uses a built-in label)",
                   GetCurrentProcessId());
    LogOnce(32 + index, "sdk-returned; showing-message", index, object);
    AfxMessageBox(message, MB_OK | MB_ICONINFORMATION);
    return TRUE;
}
