#include "StdAfx.h"
#include "ObjType.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "ExchangeProtocol.h"
#include <array>
#include <exception>
#include <stdexcept>
#include <string>

class HTreeObject;
CPluginApp theApp;

namespace {
#if AM_MESSAGE_SIDE == 1
constexpr char kSelf[] = "Plugin A";
constexpr char kPeer[] = "Plugin B";
constexpr char kLabel[] = "Message Test A -> B";
#ifdef _DEBUG
constexpr wchar_t kPeerFile[] = L"AMMessageB_64d.hxtd";
#else
constexpr wchar_t kPeerFile[] = L"AMMessageB_64.hxt";
#endif
#elif AM_MESSAGE_SIDE == 2
constexpr char kSelf[] = "Plugin B";
constexpr char kPeer[] = "Plugin A";
constexpr char kLabel[] = "Message Test B -> A";
#ifdef _DEBUG
constexpr wchar_t kPeerFile[] = L"AMMessageA_64d.hxtd";
#else
constexpr wchar_t kPeerFile[] = L"AMMessageA_64.hxt";
#endif
#else
#error Define AM_MESSAGE_SIDE as 1 or 2.
#endif

// Model node plus the selection context used in the Model window.
constexpr ObjectType kContexts[] = {HOT_MODEL, HOT_GROUP};
constexpr std::uint32_t kContextCount = 2;
bool busy = false;  // A:M's UI thread only; no background work is started.

class BusyScope {
public:
    BusyScope() { busy = true; }
    ~BusyScope() { busy = false; }
    BusyScope(const BusyScope &) = delete;
    BusyScope &operator=(const BusyScope &) = delete;
};

class Module {
public:
    explicit Module(HMODULE value) : value_(value) {}
    ~Module() { if (value_) FreeLibrary(value_); }
    HMODULE get() const { return value_; }
    Module(const Module &) = delete;
    Module &operator=(const Module &) = delete;
private:
    HMODULE value_;
};

bool validContext(HTreeObject *object, std::uint32_t index) {
    // A:M supplies the registered context. This message-only test never needs
    // to dereference its object or pull in the model-editing headers.
    return object != nullptr && index < kContextCount;
}

HWND ownerWindow() {
    CWnd *window = AfxGetMainWnd();
    return window ? window->GetSafeHwnd() : nullptr;
}

void showError(HWND owner, const char *message) {
    MessageBoxA(owner, message, kSelf, MB_OK | MB_ICONERROR);
}

template<class Function>
BOOL guarded(Function function) {
    try { return function(); }
    catch (CException *error) {
        if (error) error->Delete();
        showError(ownerWindow(), "MFC could not complete the message test.");
    }
    catch (const std::exception &error) { showError(ownerWindow(), error.what()); }
    catch (...) { showError(ownerWindow(), "The message test could not complete."); }
    return FALSE;
}

BOOL sendMessage(HTreeObject *object) {
    const HWND owner = ownerWindow();
    if (busy) {
        showError(owner, "This plugin is already handling a message. Close its dialog first.");
        return TRUE;
    }
    BusyScope active;
    std::array<wchar_t, 32768> path{};
    const DWORD length = GetModuleFileNameW(AfxGetInstanceHandle(), path.data(),
                                          static_cast<DWORD>(path.size()));
    if (length == 0 || length >= static_cast<DWORD>(path.size())) {
        showError(owner, "Could not locate this plugin's folder.");
        return TRUE;
    }
    std::wstring peerPath(path.data(), length);
    const auto separator = peerPath.find_last_of(L"\\/");
    if (separator == std::wstring::npos) {
        showError(owner, "Could not locate this plugin's folder.");
        return TRUE;
    }
    peerPath.resize(separator + 1);
    peerPath += kPeerFile;
    // Own one reference; do not unload the reference A:M holds for its plugin.
    Module peer(LoadLibraryExW(peerPath.c_str(), nullptr,
                 LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR | LOAD_LIBRARY_SEARCH_DEFAULT_DIRS));
    if (!peer.get()) {
        const DWORD code = GetLastError();
        CString message;
        message.Format("Could not load %s (Windows error %lu).\n\n"
                       "Place both matching plugins in the same HXT folder and restart A:M.",
                       kPeer, static_cast<unsigned long>(code));
        showError(owner, message.GetString());
        return TRUE;
    }
    const FARPROC address = GetProcAddress(peer.get(), "AMMessageExchangeV1");
    if (!address) {
        showError(owner, "The other plugin does not export the matching message interface.");
        return TRUE;
    }
    using Exchange = AMMessageStatus (__cdecl *)(const AMMessageRequest *, AMMessageReply *);
    static_assert(sizeof(Exchange) == sizeof(address));
    Exchange exchange = nullptr;
    // Windows guarantees GetProcAddress supplies the exported function address.
    std::memcpy(&exchange, &address, sizeof(exchange));
    AMMessageRequest request;
    request.context = object;
    request.owner_window = owner;
    std::snprintf(request.message, sizeof(request.message), "Hello from %s.", kSelf);
    AMMessageReply reply;
    const AMMessageStatus status = exchange(&request, &reply);  // Synchronous DLL call.
    if (reply.size != sizeof(reply) || reply.version != AM_MESSAGE_VERSION ||
        !std::memchr(reply.message, '\0', sizeof(reply.message))) {
        showError(owner, "The other plugin returned an invalid reply.");
        return TRUE;
    }
    CString message;
    if (status == AM_MESSAGE_OK || status == AM_MESSAGE_CANCELLED) {
        message.Format("%s resumed after %s returned.\n\nSent: %s\n\nReply: %s\n\n"
                       "Result: %s", kSelf, kPeer, request.message, reply.message,
                       status == AM_MESSAGE_OK ? "Completed" : "Cancelled");
        MessageBoxA(owner, message.GetString(), kSelf, MB_OK | MB_ICONINFORMATION);
    } else {
        message.Format("%s resumed after %s returned error %d.", kSelf, kPeer,
                       static_cast<int>(status));
        showError(owner, message.GetString());
    }
    return TRUE;
}
}  // namespace

// This is our added plugin-to-plugin ABI, not a built-in A:M SDK command.
extern "C" __declspec(dllexport) AMMessageStatus __cdecl AMMessageExchangeV1(
    const AMMessageRequest *request, AMMessageReply *reply) noexcept {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (busy) return AM_MESSAGE_BUSY;
    BusyScope active;
    try {
        return ReceiveAMMessage(request, reply, kSelf, [](const AMMessageRequest &incoming) {
            CString text;
            text.Format("%s received:\n\n%s\n\n"
                        "Click OK to complete this task and return a reply.\n"
                        "Cancel returns control with a cancelled result.", kSelf, incoming.message);
            const int choice = MessageBoxA(static_cast<HWND>(incoming.owner_window),
                                          text.GetString(), kSelf,
                                          MB_OKCANCEL | MB_ICONINFORMATION);
            if (choice == 0) throw std::runtime_error("Could not display the receiving dialog.");
            return choice == IDOK;
        });
    }
    catch (CException *error) { if (error) error->Delete(); }
    catch (...) {}  // Never propagate a C++ exception across the DLL boundary.
    return AM_MESSAGE_FAILED;
}

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(
    const std::uint32_t index, ObjectType &type) {
    if (index >= kContextCount) return FALSE;
    type = kContexts[index];
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const std::uint32_t index, String &name,
    MenuCategory &category, BOOL &disabled) {
    if (index >= kContextCount) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return guarded([&]() -> BOOL {
        CString label(kLabel);
        name = label;
        category = MC_WIZARD;
        disabled = !validContext(object, index) || busy;
        return TRUE;
    });
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(
    HTreeObject *object, const std::uint32_t index) {
    if (index >= kContextCount) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return guarded([&]() -> BOOL {
        if (!validContext(object, index)) {
            showError(ownerWindow(), "Run the message test from an open Model or its selection.");
            return FALSE;
        }
        return sendMessage(object);
    });
}
