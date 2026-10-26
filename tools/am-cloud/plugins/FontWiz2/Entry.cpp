#include "FontWiz2.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
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
fw2::GenerateText generator(HModelCache *original) {
    const void *projectIdentity = GetHProject();
    const void *modelIdentity = original;
    return [projectIdentity, modelIdentity](const fw2::Options &values) -> fw2::StampResult {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
        try {
            if (!projectIdentity || GetHProject() != projectIdentity)
                throw std::runtime_error("The project changed. Close FontWiz2 and reopen it from the intended model.");
            HModelCache *model = fw2::FindLiveModel(modelIdentity);
            if (!values.newModel && !model)
                throw std::runtime_error("The original model is no longer available. Choose Create a new model or reopen FontWiz2.");
            std::uint32_t splines = 0;
            void *generated = fw2::Generate(model, values, splines);
            return {generated, splines};
        } catch (CException *error) {
            if (error) error->Delete();
            throw std::runtime_error("A:M or MFC could not finish text generation.");
        }
    };
}
fw2::InspectModel inspector(HModelCache *original) {
    const void *projectIdentity = GetHProject();
    const void *modelIdentity = original;
    return [projectIdentity, modelIdentity](void *lastModel, bool serialize) {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
        try {
            if (!projectIdentity || GetHProject() != projectIdentity)
                throw std::runtime_error("The project changed. Reopen FontWiz2 from the intended model.");
            auto *model = fw2::FindLiveModel(lastModel ? lastModel : modelIdentity);
            if (!model) throw std::runtime_error("The inspected model is no longer available. Reopen FontWiz2.");
            return fw2::ModelSnapshot(model, serialize);
        } catch (CException *error) {
            if (error) error->Delete();
            throw std::runtime_error("A:M or MFC could not inspect the model.");
        }
    };
}
fw2::SaveModelCopy modelSaver(HModelCache *original) {
    const void *projectIdentity = GetHProject();
    const void *modelIdentity = original;
    return [projectIdentity, modelIdentity](void *lastModel, HWND owner) {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
        try {
            const auto path = fw2::ChooseModelCopy(owner);
            if (path.empty()) return false;
            if (!projectIdentity || GetHProject() != projectIdentity)
                throw std::runtime_error("The project changed. Reopen FontWiz2 from the intended model.");
            auto *model = fw2::FindLiveModel(lastModel ? lastModel : modelIdentity);
            if (!model) throw std::runtime_error("The model is no longer available. Reopen FontWiz2.");
            const auto bytes = fw2::ModelCode(model, path);
            if (bytes.find("<MODELFILE>") == std::string::npos || bytes.find("</MODELFILE>") == std::string::npos)
                throw std::runtime_error("The SDK did not produce a complete model file. Use A:M Save for this model; text remains in place.");
            fw2::WriteModelCopy(path, bytes);
            return true;
        } catch (CException *error) {
            if (error) error->Delete();
            throw std::runtime_error("A:M could not save the model copy. Generated text remains in A:M.");
        }
    };
}
struct EnabledHost {
    HWND window; bool restore;
    explicit EnabledHost(HWND host) : window(host), restore(!IsWindowEnabled(host)) {
        if (restore) EnableWindow(window, TRUE);
    }
    ~EnabledHost() { if (restore && IsWindow(window)) EnableWindow(window, FALSE); }
};
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
        EnabledHost enabled(mainWindow);
        const auto result = fw2::ShowWizard(AfxGetInstanceHandle(), mainWindow, options, model != nullptr,
            generator(model), [](MSG &message) {
                CWinApp *host = GetMainApplication();
                return host && host->PreTranslateMessage(&message) != FALSE;
            }, inspector(model), modelSaver(model));
        if (!result.stamps) {
            detail(reply, L"FontWiz2 cancelled. No geometry was added."); return FW2_CANCELLED;
        }
        remembered = options;
        reply->model = fw2::FindLiveModel(result.model); reply->splines = result.splines;
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
        if (busy) return FALSE;
        auto *model = fw2::ResolveModel(object);
        if (!model) return FALSE;
        // The command returns while its window/hook still execute plugin code.
        // Keep that code mapped until process exit, even if A:M releases its HXT.
        HMODULE module = nullptr;
        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
            reinterpret_cast<LPCWSTR>(&HxtOnCommand), &module))
            throw std::runtime_error("FontWiz2 could not retain its modeless window module.");
        busy = true;
        fw2::OpenWizard(AfxGetInstanceHandle(), GetMainApplicationWnd(), remembered, true, generator(model),
            [](const fw2::Options &values, const fw2::WizardResult &result) {
                AFX_MANAGE_STATE(AfxGetStaticModuleState());
                if (result.stamps) remembered = values;
                busy = false;
            }, inspector(model), modelSaver(model));
        return TRUE;
    } catch (const std::exception &error) {
        busy = false; MessageBoxA(GetMainApplicationWnd(), error.what(), "FontWiz2", MB_OK | MB_ICONERROR);
    } catch (...) { busy = false; }
    return FALSE;
}
