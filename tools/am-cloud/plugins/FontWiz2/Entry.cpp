#include "FontWiz2.h"
#include "SDK/HModel.h"
#include <exception>
#include <stdexcept>
#include <cwchar>

CPluginApp theApp;
namespace {
bool busy = false;
fw2::Options remembered;
constexpr ObjectType contexts[] = {HOT_MODEL, HOT_GROUP};
struct BusyScope { BusyScope() { busy = true; } ~BusyScope() { busy = false; } };
void detail(FW2Reply *reply, const wchar_t *message) { wcsncpy_s(reply->detail, message, _TRUNCATE); }
}

extern "C" __declspec(dllexport) FW2Status __cdecl FontWiz2RunV1(
    const FW2Request *request, FW2Reply *reply) noexcept {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (!FW2ValidRequest(request, reply)) return FW2_INVALID_INPUT;
    reply->model = nullptr; reply->splines = 0; reply->text[0] = L'\0'; reply->detail[0] = L'\0';
    const HWND mainWindow = GetMainApplicationWnd();
    if (!mainWindow || GetWindowThreadProcessId(mainWindow, nullptr) != GetCurrentThreadId()) {
        detail(reply, L"Call FontWiz2 on A:M's UI thread."); return FW2_WRONG_THREAD;
    }
    if (busy) { detail(reply, L"FontWiz2 is already open."); return FW2_BUSY; }
    BusyScope active;
    try {
        HModelCache *model = request->model ? fw2::ResolveModel(static_cast<HTreeObject *>(request->model)) : nullptr;
        if (request->model && !model) { detail(reply, L"A Model cache is required."); return FW2_INVALID_INPUT; }
        HWND owner = request->owner ? static_cast<HWND>(request->owner) : mainWindow;
        if (!IsWindow(owner) || GetWindowThreadProcessId(owner, nullptr) != GetCurrentThreadId()) {
            detail(reply, L"The dialog owner must belong to A:M's UI thread."); return FW2_INVALID_INPUT;
        }
        fw2::Options options = remembered; options.text = request->text;
        const auto result = fw2::ShowWizard(AfxGetInstanceHandle(), owner, options, model != nullptr,
            [&](const fw2::Options &values) -> fw2::StampResult {
                try {
                    std::uint32_t splines = 0;
                    void *generated = fw2::Generate(model, values, splines);
                    return {generated, splines};
                } catch (CException *error) {
                    if (error) error->Delete();
                    throw std::runtime_error("A:M or MFC could not finish text generation.");
                }
            });
        if (!result.stamps) {
            detail(reply, L"FontWiz2 cancelled. No geometry was added."); return FW2_CANCELLED;
        }
        remembered = options;
        reply->model = result.model; reply->splines = result.splines;
        wcscpy_s(reply->text, result.text.c_str());
        swprintf_s(reply->detail, L"FontWiz2 completed: %u splines across %u stamp(s).", reply->splines, result.stamps);
        return FW2_COMPLETED;
    } catch (CException *error) {
        if (error) error->Delete();
        detail(reply, L"A:M or MFC could not finish text generation.");
    } catch (const std::exception &error) {
        MultiByteToWideChar(CP_UTF8, 0, error.what(), -1, reply->detail, 256);
        reply->detail[255] = L'\0';
    } catch (...) { detail(reply, L"FontWiz2 could not finish text generation."); }
    return FW2_FAILED;
}

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const std::uint32_t index, ObjectType &type) {
    if (index >= 2) return FALSE;
    type = contexts[index]; return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const std::uint32_t index, String &name, MenuCategory &category, BOOL &disabled) {
    if (index >= 2) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try {
        CString label("FontWiz2..."); name = label; category = MC_WIZARD;
        disabled = busy || fw2::ResolveModel(object) == nullptr; return TRUE;
    } catch (...) { return FALSE; }
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *object, const std::uint32_t index) {
    if (index >= 2) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try {
        FW2Request request; FW2Reply reply;
        request.model = fw2::ResolveModel(object); request.owner = GetMainApplicationWnd();
        if (!request.model) return FALSE;
        wcscpy_s(request.text, remembered.text.c_str());
        const FW2Status status = FontWiz2RunV1(&request, &reply);
        if (status != FW2_COMPLETED && status != FW2_CANCELLED)
            MessageBoxW(static_cast<HWND>(request.owner), reply.detail[0] ? reply.detail : L"Invalid text input.",
                        L"FontWiz2", MB_OK | MB_ICONERROR);
        return status == FW2_COMPLETED || status == FW2_CANCELLED;
    } catch (...) { return FALSE; }
}
