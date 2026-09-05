#include "StdAfx.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HCP.h"
#include "SDK/HPatch.h"
#include "SDK/HProject.h"
#include "Plan.h"
#include "FivePoint.h"
#include "Worker.h"
#include <commdlg.h>
#include <cwctype>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <utility>

CPluginApp theApp;
namespace {
namespace fs = std::filesystem;
LONG g_busy = 0;
// Session-only convenience; no registry edits or automatic interpreter discovery.
std::wstring g_python;
constexpr ObjectType kContexts[] = {HOT_OBJECTS, HOT_MODEL, HOT_GROUP};
std::wstring Wide(const std::string& text) {
    if (text.empty()) return {};
    const int length = MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), nullptr, 0);
    if (!length) return L"Text conversion failed.";
    std::wstring value(static_cast<std::size_t>(length), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()), value.data(), length);
    return value;
}
HWND Owner() { return AfxGetMainWnd() ? AfxGetMainWnd()->GetSafeHwnd() : nullptr; }
int Message(const std::wstring& text, UINT flags = MB_OK | MB_ICONINFORMATION) {
    return MessageBoxW(Owner(), text.c_str(), L"A:M Script Builder v1", flags);
}
HMODULE Module() {
    HMODULE value = nullptr;
    amscript::RequireWin(GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, reinterpret_cast<LPCWSTR>(&g_busy), &value),
        "Find plugin module");
    return value;
}
std::string Resource(unsigned id) {
    const auto module = Module();
    const auto resource = FindResourceW(module, MAKEINTRESOURCEW(id), MAKEINTRESOURCEW(10));
    if (!resource) throw std::runtime_error("Embedded Python support resource is missing");
    const DWORD size = SizeofResource(module, resource);
    const auto loaded = LoadResource(module, resource);
    const auto data = loaded ? LockResource(loaded) : nullptr;
    if (!data || !size || size > amscript::MaxBytes) throw std::runtime_error("Invalid embedded Python resource");
    return std::string(static_cast<const char*>(data), size);
}
std::wstring Choose(const wchar_t* title, const wchar_t* filter, const std::wstring& initial = {}) {
    std::vector<wchar_t> name(32768, L'\0');
    if (initial.size() >= name.size()) throw std::runtime_error("File path too long");
    std::copy(initial.begin(), initial.end(), name.begin());
    OPENFILENAMEW dialog{};
    dialog.lStructSize = sizeof(dialog); dialog.hwndOwner = Owner();
    dialog.lpstrFile = name.data(); dialog.nMaxFile = static_cast<DWORD>(name.size());
    dialog.lpstrFilter = filter; dialog.lpstrTitle = title;
    dialog.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_EXPLORER;
    if (GetOpenFileNameW(&dialog)) return name.data();
    if (CommDlgExtendedError()) throw std::runtime_error("File selection dialog failed");
    return {};
}
std::string ReadBounded(const fs::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("Cannot read selected script/plan");
    std::string bytes(amscript::MaxBytes + 1, '\0');
    file.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    bytes.resize(static_cast<std::size_t>(file.gcount()));
    if (file.bad() || bytes.empty() || bytes.size() > amscript::MaxBytes)
        throw std::runtime_error("Script/plan must be nonempty and at most 256 KiB");
    return bytes;
}
class Scratch {
    fs::path folder;
public:
    Scratch() {
        wchar_t temp[32768];
        const DWORD count = GetTempPathW(_countof(temp), temp);
        if (!count || count >= _countof(temp)) throw std::runtime_error("Windows TEMP path unavailable");
        GUID id{};
        if (FAILED(CoCreateGuid(&id))) throw std::runtime_error("Cannot allocate a private run ID");
        wchar_t guid[40];
        if (!StringFromGUID2(id, guid, _countof(guid))) throw std::runtime_error("Invalid run ID");
        folder = fs::path(temp) / (std::wstring(L"AMScriptBuilder-") + guid);
        if (!CreateDirectoryW(folder.c_str(), nullptr)) throw std::runtime_error("Cannot create private worker directory");
    }
    ~Scratch() {
        // Only remove our three known files, never recurse through user-script output.
        for (const auto* name : {L"runner.py", L"ambridge.py", L"script.py"})
            DeleteFileW((folder / name).c_str());
        RemoveDirectoryW(folder.c_str());
    }
    const fs::path& path() const { return folder; }
    void write(const wchar_t* name, const std::string& bytes) const {
        amscript::Handle file(CreateFileW((folder / name).c_str(), GENERIC_WRITE, 0, nullptr,
                                         CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr));
        if (file.get() == INVALID_HANDLE_VALUE) throw std::runtime_error("Cannot write private worker snapshot");
        DWORD written = 0;
        amscript::RequireWin(WriteFile(file.get(), bytes.data(), static_cast<DWORD>(bytes.size()), &written, nullptr), "Write snapshot");
        if (written != bytes.size()) throw std::runtime_error("Incomplete worker snapshot write");
    }
};
class Progress final : public CDialog {
    const Scratch& scratch;
    amscript::Worker worker;
    bool done = false;
public:
    std::string output, failure;
    explicit Progress(const Scratch& value) : CDialog(301, AfxGetMainWnd()), scratch(value) {}
    BOOL OnInitDialog() override {
        CDialog::OnInitDialog();
        try {
            worker.start(g_python, {L"-I", L"-S", L"-B", L"-X", L"utf8",
                         (scratch.path() / L"runner.py").wstring(), (scratch.path() / L"script.py").wstring()}, scratch.path().wstring());
            if (!SetTimer(1, 50, nullptr)) throw std::runtime_error("Cannot start worker timer");
        } catch (const std::exception& error) { failure = error.what(); worker.stop(); EndDialog(IDABORT); }
        return TRUE;
    }
    afx_msg void OnTimer(UINT_PTR id) {
        if (id != 1 || done) return;
        try {
            if (worker.poll()) { done = true; KillTimer(1); output = worker.output; EndDialog(IDOK); }
        } catch (const std::exception& error) {
            done = true; KillTimer(1); worker.stop();
            failure = std::string(error.what()) + "\n\n" + worker.errors.substr(0, 4096);
            EndDialog(IDABORT);
        }
    }
    void OnCancel() override { done = true; KillTimer(1); worker.stop(); EndDialog(IDCANCEL); }
    DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(Progress, CDialog)
    ON_WM_TIMER()
END_MESSAGE_MAP()

Vector Position(const std::array<float, 3>& point) { return Vector(point[0], point[1], point[2]); }
void CreateModel(const amscript::Plan& plan, const std::vector<amscript::FiveCycle>& fiveCandidates) {
    // Only this function mutates A:M. No source/context objects are edited.
    // The SDK does NOT establish a transactional rollback contract here.
    HModelCache* model = nullptr;
    bool finished = false;
    try {
        if (!GetHProject()) throw std::runtime_error("No current A:M project");
        // Allocate bookkeeping before creating any native geometry.
        std::vector<HCP*> heads(plan.points.size(), nullptr);
        std::vector<std::pair<std::size_t, HCP*>> occurrences;
        occurrences.reserve(plan.occurrences);
        model = HModelCache::New(plan.name.c_str());
        if (!model) throw std::runtime_error("SDK could not create a new model");
        for (const auto& indices : plan.splines) {
            Vector first = Position(plan.points[indices[0]]), second = Position(plan.points[indices[1]]);
            // StartSpline creates two points; no deliberately incomplete one-CP spline.
            HSpline* spline = model->StartSpline(&first, &second);
            if (!spline) throw std::runtime_error("SDK could not create a spline");
            HCP* one = spline->GetHeadCP();
            HCP* two = one ? one->GetNext() : nullptr;
            if (!one || !two) throw std::runtime_error("SDK returned an incomplete spline");
            one->SetPeaked(); two->SetPeaked();
            occurrences.emplace_back(indices[0], one); occurrences.emplace_back(indices[1], two);
            for (std::size_t i = 2; i < indices.size(); ++i) {
                HCP* cp = spline->CreateCPAtTail(Position(plan.points[indices[i]]));
                if (!cp) throw std::runtime_error("SDK could not add a control point");
                cp->SetPeaked(); occurrences.emplace_back(indices[i], cp);
            }
        }
        std::size_t deletedByAttachment = 0;
        for (const auto& occurrence : occurrences) {
            HCP*& head = heads[occurrence.first];
            if (!head) {
                head = occurrence.second;
            } else {
                // SDK semantics: TRUE means A:M deleted the second CP as part of
                // attachment/loopback handling. FALSE is also a normal attachment
                // outcome; it is NOT a failure return. The SDK Grid sample treats
                // this result as cp2deleted for exactly that reason.
                if (model->AttachCPs(head, occurrence.second)) ++deletedByAttachment;
            }
        }
        model->Update();
        model->FindPatches();
        std::size_t actualFivePatches = 0;
        for (HPatch5* patch = model->GetHeadPatch5(); patch; patch = patch->GetNextPatch5())
            ++actualFivePatches;
        model->SetChanged();
        model->RefreshInProjectBar(TRUE);
        finished = true;
        model->OpenView(); model->ZoomFit();
        GetHProject()->UpdateAllViews();
        const String version = GetAMVersion();
        std::ostringstream message;
        message << "Built a NEW, unsaved model.\n\nName: " << plan.name
                << "\nLogical points: " << plan.points.size() << "\nSpline CP records: " << plan.occurrences
                << "\nSplines: " << plan.splines.size() << "\nRequested attachments: " << plan.attachments
                << "\nAttachCPs deleted-second-CP results: " << deletedByAttachment
                << "\nPlan five-point candidates: " << fiveCandidates.size()
                << "\nA:M standard patch count: " << model->GetPatchCount()
                << "\nA:M HPatch5 count: " << actualFivePatches << "\nA:M: " << version.Get();
        if (actualFivePatches != fiveCandidates.size())
            message << "\n\nDiagnostic: plan candidate count differs from A:M HPatch5 count."
                    << " This is reported for study and is not treated as a build failure.";
        message << "\n\nExisting model geometry was not targeted. Save/test this new model manually."
                << "\nDo not rely on whole-build Undo: remove the generated model through A:M to discard it.";
        Message(Wide(message.str()));
    } catch (...) {
        if (model) Message(finished ?
            L"Model construction finished, but display/reporting failed. Inspect the new model in the Project Workspace." :
            L"Native construction failed after creating a NEW model. A partial model may remain. Delete that new model through A:M before retrying. No automatic rollback or whole-build Undo is claimed.", MB_OK | MB_ICONWARNING);
        throw;
    }
}
void Build() {
    if (!GetHProject()) throw std::runtime_error("Open or create an A:M project first");
    const auto chosen = Choose(L"Choose trusted Python script or existing model plan", L"Script or plan (*.py;*.json)\0*.py;*.json\0\0");
    if (chosen.empty()) return;
    const auto input = ReadBounded(fs::path(chosen)); // immutable snapshot for this invocation
    auto extension = fs::path(chosen).extension().wstring();
    std::transform(extension.begin(), extension.end(), extension.begin(), [](wchar_t c) { return static_cast<wchar_t>(towlower(c)); });
    std::string data;
    if (extension == L".json") data = input;
    else if (extension == L".py") {
        const auto executable = Choose(L"Choose 64-bit CPython 3.11 or 3.12 python.exe (not py.exe or pythonw.exe)", L"Python executable (python.exe)\0python.exe\0\0", g_python);
        if (executable.empty()) return;
        if (_wcsicmp(fs::path(executable).filename().c_str(), L"python.exe") != 0)
            throw std::runtime_error("Select 64-bit CPython 3.11 or 3.12 python.exe, not a launcher");
        g_python = executable;
        if (Message(L"Run this local Python script?\n\n" + chosen + L"\n\nInterpreter:\n" + executable +
            L"\n\nSupported: 64-bit CPython 3.11 or 3.12; the worker verifies this before executing the script."
            L"\nONLY run code you trust. Python runs with your account permissions; this is NOT a security sandbox."
            L"\nThe plugin has no network/API feature, but arbitrary scripts can access files/network."
            L"\n15-second, 512 MiB and output limits apply. No A:M geometry will change until a separate confirmation.",
            MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES) return;
        Scratch scratch;
        scratch.write(L"runner.py", Resource(201)); scratch.write(L"ambridge.py", Resource(202));
        scratch.write(L"script.py", input);
        Progress progress(scratch);
        const auto result = progress.DoModal();
        if (result == IDCANCEL) return;
        if (result != IDOK) throw std::runtime_error(progress.failure.empty() ? "Worker dialog failed" : progress.failure);
        data = std::move(progress.output);
    } else throw std::runtime_error("Select a .py script or .json plan");
    const auto plan = amscript::Parse(data); // independent C++ validation before ANY creation
    const auto fiveCandidates = amscript::FivePointCandidates(plan);
    std::ostringstream summary;
    summary << "Validated plan v1: " << plan.name << "\n\nLogical points: " << plan.points.size()
            << "\nOpen, peaked splines: " << plan.splines.size() << "\nSpline CP records: " << plan.occurrences
            << "\nExplicit attachments: " << plan.attachments
            << "\nFive-point topology candidates: " << fiveCandidates.size();
    if (!fiveCandidates.empty()) {
        summary << "\nCandidate boundaries:";
        const std::size_t shown = fiveCandidates.size() < 8 ? fiveCandidates.size() : 8;
        for (std::size_t i = 0; i < shown; ++i) {
            summary << "\n  [";
            for (std::size_t j = 0; j < 5; ++j) {
                if (j) summary << ',';
                summary << fiveCandidates[i][j];
            }
            summary << ']';
        }
        if (fiveCandidates.size() > shown) summary << "\n  ...";
    }
    summary << "\n\nCreate a NEW model now? Existing geometry will not be replaced."
            << "\nA:M will discover patches; plan candidates are topology hints, not HPatch5 proof."
            << "\nThe result dialog compares candidates with A:M's actual HPatch5 count."
            << "\nNo automatic save or whole-build Undo. To discard, delete the generated model."
            << "\nNative failure can leave a partial NEW model; test only in a disposable project.";
    if (Message(Wide(summary.str()), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
        CreateModel(plan, fiveCandidates);
}
} // namespace

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(uint32_t index, ObjectType& type) {
    if (index >= _countof(kContexts)) return FALSE;
    type = kContexts[index]; return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject*, uint32_t index,
    String& name, MenuCategory& category, BOOL& disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (index >= _countof(kContexts)) return FALSE;
    name = "A:M Script Builder v1 - New Model";
    category = MC_WIZARD; disabled = g_busy != 0 || !GetHProject(); return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject*, uint32_t index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (index >= _countof(kContexts)) return FALSE;
    if (InterlockedCompareExchange(&g_busy, 1, 0) != 0) return TRUE;
    struct Busy { ~Busy() { InterlockedExchange(&g_busy, 0); } } busy;
    try { Build(); }
    catch (CException* error) { error->Delete(); Message(L"MFC operation failed. No further operations will be attempted.", MB_OK | MB_ICONERROR); }
    catch (const std::exception& error) { Message(Wide(error.what()), MB_OK | MB_ICONERROR); }
    catch (...) { Message(L"Unexpected failure. Stop testing and inspect the disposable project.", MB_OK | MB_ICONERROR); }
    return TRUE;
}
