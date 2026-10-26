#include "../FontWiz2/FontWiz2.h"
#include "SDK/HModel.h"
#include "resource.h"
#include <array>
#include <cstring>
#include <stdexcept>

CPluginApp theApp;
namespace {
std::wstring remembered = L"Hello from FontWiz2!";
bool open = false;
constexpr ObjectType contexts[] = {HOT_MODEL, HOT_GROUP};
HModelCache *resolve(HTreeObject *object) {
    if (!object) return nullptr;
    HHashObject *candidate = nullptr;
    if (object->GetObjectType() == HOT_MODEL) candidate = static_cast<HHashObject *>(object);
    else if (object->GetObjectType() == HOT_GROUP)
        candidate = static_cast<HHashObject *>(object)->GetParentOfType(HOT_MODEL);
    return candidate && static_cast<HAnimObject *>(candidate)->IsCache() ? static_cast<HModelCache *>(candidate) : nullptr;
}
struct State { HModelCache *model; bool calling = false; };
class Module {
public:
    HMODULE handle;
    explicit Module(HMODULE value) : handle(value) {}
    ~Module() { if (handle) FreeLibrary(handle); }
    Module(const Module &) = delete;
    Module &operator=(const Module &) = delete;
};
void launch(HWND dialog, State &state) {
    FW2Request request; FW2Reply reply;
    request.model = state.model; request.owner = dialog;
    GetDlgItemTextW(dialog, IDC_FW2_INPUT, request.text, static_cast<int>(FW2_MAX_TEXT + 1));
    if (!FW2ValidRequest(&request, &reply))
        throw std::runtime_error("Enter visible text (up to 512 BMP characters). Emoji/surrogate pairs are not supported yet.");
    remembered = request.text;
    std::array<wchar_t, 32768> path{};
    const DWORD length = GetModuleFileNameW(AfxGetInstanceHandle(), path.data(), static_cast<DWORD>(path.size()));
    if (!length || length >= static_cast<DWORD>(path.size())) throw std::runtime_error("Could not locate this plugin's folder.");
    std::wstring filename(path.data(), length);
    const auto slash = filename.find_last_of(L"\\/");
    if (slash == std::wstring::npos) throw std::runtime_error("Could not locate this plugin's folder.");
    filename.resize(slash + 1);
#ifdef _DEBUG
    filename += L"FontWiz2_64d.hxtd";
#else
    filename += L"FontWiz2_64.hxt";
#endif
    Module module(LoadLibraryExW(filename.c_str(), nullptr, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR | LOAD_LIBRARY_SEARCH_DEFAULT_DIRS));
    if (!module.handle) throw std::runtime_error("FontWiz2 could not be loaded. Put both matching new plugins in the same HXT folder, then restart A:M.");
    const FARPROC address = GetProcAddress(module.handle, "FontWiz2RunV1");
    if (!address) throw std::runtime_error("The installed FontWiz2 does not provide the required V1 text interface.");
    using Run = FW2Status (__cdecl *)(const FW2Request *, FW2Reply *);
    Run run = nullptr; static_assert(sizeof(run) == sizeof(address));
    std::memcpy(&run, &address, sizeof(run));
    const FW2Status status = run(&request, &reply);
    if (reply.size != sizeof(reply) || reply.version != FW2_API_VERSION ||
        !std::wmemchr(reply.detail, L'\0', 256) ||
        !std::wmemchr(reply.text, L'\0', FW2_MAX_TEXT + 1))
        throw std::runtime_error("FontWiz2 returned an invalid reply.");
    std::wstring result = L"Returned to Pass text to FontWiz2.\r\n";
    if (status == FW2_COMPLETED) {
        remembered = reply.text; SetDlgItemTextW(dialog, IDC_FW2_INPUT, reply.text);
        result += reply.detail;
    } else if (status == FW2_CANCELLED) result += L"Cancelled; no text geometry added.";
    else result += reply.detail[0] ? reply.detail : L"FontWiz2 could not complete this request.";
    SetDlgItemTextW(dialog, IDC_FW2_RESULT, result.c_str());
    SetFocus(GetDlgItem(dialog, IDC_FW2_INPUT));
}
INT_PTR CALLBACK procedure(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam) {
    State *state = reinterpret_cast<State *>(GetWindowLongPtrW(dialog, DWLP_USER));
    if (message == WM_INITDIALOG) {
        state = reinterpret_cast<State *>(lparam); SetWindowLongPtrW(dialog, DWLP_USER, lparam);
        SendDlgItemMessageW(dialog, IDC_FW2_INPUT, EM_SETLIMITTEXT, FW2_MAX_TEXT, 0);
        SetDlgItemTextW(dialog, IDC_FW2_INPUT, remembered.c_str()); return TRUE;
    }
    if (!state) return FALSE;
    if (message == WM_CLOSE || (message == WM_COMMAND && LOWORD(wparam) == IDCANCEL)) {
        if (!state->calling) EndDialog(dialog, IDCANCEL); return TRUE;
    }
    if (message == WM_COMMAND && LOWORD(wparam) == IDC_FW2_OPEN && !state->calling) {
        state->calling = true; EnableWindow(GetDlgItem(dialog, IDC_FW2_OPEN), FALSE);
        try { launch(dialog, *state); }
        catch (CException *error) {
            if (error) error->Delete();
            MessageBoxW(dialog, L"A:M or MFC could not complete the call.", L"Pass text to FontWiz2", MB_OK | MB_ICONERROR);
        }
        catch (const std::exception &error) { MessageBoxA(dialog, error.what(), "Pass text to FontWiz2", MB_OK | MB_ICONERROR); }
        catch (...) { MessageBoxW(dialog, L"The FontWiz2 call failed.", L"Pass text to FontWiz2", MB_OK | MB_ICONERROR); }
        state->calling = false; EnableWindow(GetDlgItem(dialog, IDC_FW2_OPEN), TRUE); return TRUE;
    }
    return FALSE;
}
}
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const std::uint32_t index, ObjectType &type) {
    if (index >= 2) return FALSE; type = contexts[index]; return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const std::uint32_t index, String &name, MenuCategory &category, BOOL &disabled) {
    if (index >= 2) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try {
        CString label("Pass text to FontWiz2..."); name = label; category = MC_WIZARD;
        disabled = open || resolve(object) == nullptr; return TRUE;
    } catch (...) { return FALSE; }
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *object, const std::uint32_t index) {
    if (index >= 2) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (open) return FALSE;
    open = true;
    BOOL success = FALSE;
    try {
        State state{resolve(object)};
        if (state.model) {
            const INT_PTR result = DialogBoxParamW(AfxGetInstanceHandle(), MAKEINTRESOURCEW(IDD_FW2_LAUNCHER),
                                                   GetMainApplicationWnd(), procedure, reinterpret_cast<LPARAM>(&state));
            success = result != -1;
        }
    } catch (...) {}
    open = false; return success;
}
