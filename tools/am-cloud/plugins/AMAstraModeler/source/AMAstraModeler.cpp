// AMAstraModeler 0.1.0. Developed for Rodney Baker with OpenAI Codex assistance.
#include "StdAfx.h"

#include "ModelPlan.h"
#include "OpenAIClient.h"
#include "PromptLog.h"
#include "resource.h"

#include "SDK/Entry.h"
#include "SDK/HCP.h"
#include "SDK/HModel.h"
#include "SDK/HPatch.h"
#include "SDK/HPropert.h"
#include "SDK/Misc.h"
#include "HashTime.h"
#include "RGBFloat.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cwctype>
#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

CPluginApp theApp;

namespace {

constexpr ObjectType Contexts[] = {HOT_OBJECTS, HOT_MODEL, HOT_GROUP};
constexpr UINT GenerationCompleteMessage = WM_APP + 71;

bool ContextOK(HTreeObject* object, std::uint32_t index) {
    if (!object || index >= _countof(Contexts) || object->GetObjectType() != Contexts[index]) return false;
    if (index == 0) return true;
    auto* parent = object;
    for (std::size_t depth = 0; parent && depth < 64; ++depth, parent = parent->GetParent()) {
        if (parent->GetObjectType() == HOT_MODEL) {
            auto* model = parent->GetAnimObject();
            return model && model->IsCache();
        }
    }
    return false;
}

std::wstring ControlText(HWND dialog, int control) {
    const HWND item = GetDlgItem(dialog, control);
    if (!item) throw amastra::Error("A required dialog control is missing");
    const int length = GetWindowTextLengthW(item);
    if (length < 0) throw amastra::Error("Cannot read a dialog control");
    std::wstring result(static_cast<std::size_t>(length) + 1, L'\0');
    const int copied = GetWindowTextW(item, result.data(), length + 1);
    if (copied < 0) throw amastra::Error("Cannot read a dialog control");
    result.resize(static_cast<std::size_t>(copied));
    return result;
}

void SetControlText(HWND dialog, int control, const std::wstring& text) {
    const HWND item = GetDlgItem(dialog, control);
    if (!item || !SetWindowTextW(item, text.c_str())) throw amastra::Error("Cannot update a dialog control");
}

void ErrorBox(std::string_view message, const wchar_t* title = L"Astra Modeler 0.1.0") {
    std::wstring wide;
    try { wide = amastra::WideFromUtf8(message); }
    catch (...) { wide = L"An error occurred, and its UTF-8 message could not be displayed."; }
    MessageBoxW(GetMainApplicationWnd(), wide.c_str(), title, MB_OK | MB_ICONERROR);
}

std::size_t PositiveInteger(std::wstring_view text, std::size_t minimum, std::size_t maximum,
                            const char* label) {
    if (text.empty()) throw amastra::Error(std::string(label) + " is required");
    std::size_t value = 0;
    for (wchar_t c : text) {
        if (c < L'0' || c > L'9') throw amastra::Error(std::string(label) + " must be a whole number");
        const auto digit = static_cast<std::size_t>(c - L'0');
        if (value > (maximum - digit) / 10) throw amastra::Error(std::string(label) + " is too large");
        value = value * 10 + digit;
    }
    if (value < minimum || value > maximum)
        throw amastra::Error(std::string(label) + " must be " + std::to_string(minimum) + "-" +
                             std::to_string(maximum));
    return value;
}

class PromptDialog final : public CDialog {
public:
    std::string prompt;
    std::size_t componentLimit = 24;
    std::size_t patchLimit = 2000;

    PromptDialog() : CDialog(IDD_PROMPT, CWnd::FromHandle(GetMainApplicationWnd())) {}

protected:
    BOOL OnInitDialog() override {
        CDialog::OnInitDialog();
        try {
            SetControlText(m_hWnd, IDC_COMPONENT_LIMIT, L"24");
            SetControlText(m_hWnd, IDC_PATCH_LIMIT, L"2000");
            const auto directory = amastra::ProgramDirectory();
            SetControlText(m_hWnd, IDC_PATH_NOTE,
                L"API key: " + directory + L"\\api_key.txt\r\n"
                L"Prompt log: " + directory +
                L"\\astra_modeler.log (LOCALAPPDATA fallback if this folder is read-only)");
            SendDlgItemMessage(IDC_PROMPT, EM_SETLIMITTEXT, 16000, 0);
        } catch (const std::exception& error) {
            ErrorBox(error.what());
        }
        return TRUE;
    }

    void OnOK() override {
        try {
            const auto widePrompt = ControlText(m_hWnd, IDC_PROMPT);
            bool content = false;
            for (wchar_t c : widePrompt) if (!iswspace(c)) { content = true; break; }
            if (!content) throw amastra::Error("Enter a model prompt");
            prompt = amastra::Utf8FromWide(widePrompt);
            if (prompt.size() > amastra::MaxPromptBytes)
                throw amastra::Error("The UTF-8 prompt exceeds the 16,000-byte limit");
            componentLimit = PositiveInteger(ControlText(m_hWnd, IDC_COMPONENT_LIMIT), 1,
                                             amastra::MaxComponents, "Component limit");
            patchLimit = PositiveInteger(ControlText(m_hWnd, IDC_PATCH_LIMIT), 1,
                                         amastra::HardMaxPatches, "Patch limit");
            CDialog::OnOK();
        } catch (const std::exception& error) {
            ErrorBox(error.what(), L"Check Astra Modeler prompt");
        }
    }
};

class GenerateDialog final : public CDialog {
public:
    GenerateDialog(std::string apiKey, std::string requestBody, std::size_t componentLimit,
                   std::size_t patchLimit)
        : CDialog(IDD_GENERATING, CWnd::FromHandle(GetMainApplicationWnd())),
          apiKey_(std::move(apiKey)), requestBody_(std::move(requestBody)),
          componentLimit_(componentLimit), patchLimit_(patchLimit) {}

    ~GenerateDialog() override {
        cancelRequested_.store(true, std::memory_order_relaxed);
        if (worker_.joinable()) worker_.join();
        amastra::SecureErase(apiKey_);
    }

    amastra::ApiResult api;
    amastra::PreparedPlan plan;
    std::string error;

protected:
    BOOL OnInitDialog() override {
        CDialog::OnInitDialog();
        try {
            worker_ = std::thread([this] { Run(); });
        } catch (const std::exception& failure) {
            error = std::string("Cannot start the generation worker: ") + failure.what();
            PostMessage(GenerationCompleteMessage);
        }
        return TRUE;
    }

    BOOL OnCommand(WPARAM wParam, LPARAM lParam) override {
        if (LOWORD(wParam) == IDCANCEL) {
            cancelRequested_.store(true, std::memory_order_relaxed);
            if (auto* cancel = GetDlgItem(IDCANCEL)) cancel->EnableWindow(FALSE);
            try { SetControlText(m_hWnd, IDC_GENERATION_STATUS,
                                 L"Cancelling... The active HTTPS operation may take a moment to return."); }
            catch (...) {}
            return TRUE;
        }
        return CDialog::OnCommand(wParam, lParam);
    }

    afx_msg LRESULT OnGenerationComplete(WPARAM, LPARAM) {
        if (worker_.joinable()) worker_.join();
        if (cancelRequested_.load(std::memory_order_relaxed)) EndDialog(IDCANCEL);
        else if (!error.empty()) EndDialog(IDABORT);
        else EndDialog(IDOK);
        return 0;
    }

    DECLARE_MESSAGE_MAP()

private:
    void Run() noexcept {
        try {
            const auto response = amastra::PostResponses(apiKey_, requestBody_, cancelRequested_);
            api.requestId = response.requestId;
            try {
                const auto envelope = amjson::parse(response.body);
                if (const auto* id = envelope.find("id"); id && id->is_string()) api.responseId = id->as_string();
            } catch (...) {}
            if (response.status < 200 || response.status >= 300) {
                try {
                    api = amastra::ExtractApiResult(response.body, response.requestId);
                } catch (const std::exception& failure) {
                    std::ostringstream message;
                    message << failure.what() << " (HTTP " << response.status;
                    if (!response.requestId.empty()) message << ", request " << response.requestId;
                    message << ')';
                    throw amastra::Error(message.str());
                }
                throw amastra::Error("OpenAI API returned HTTP " + std::to_string(response.status));
            }
            api = amastra::ExtractApiResult(response.body, response.requestId);
            const auto root = amjson::parse(api.arguments);
            plan = amastra::PreparePlan(amastra::ParseModelPlan(root), patchLimit_, componentLimit_);
            if (cancelRequested_.load(std::memory_order_relaxed)) throw amastra::Error("Generation cancelled");
        } catch (const std::exception& failure) {
            error = failure.what();
        } catch (...) {
            error = "Unexpected generation error";
        }
        amastra::SecureErase(apiKey_);
        if (GetSafeHwnd()) PostMessage(GenerationCompleteMessage);
    }

    std::string apiKey_;
    std::string requestBody_;
    std::size_t componentLimit_ = 0;
    std::size_t patchLimit_ = 0;
    std::atomic_bool cancelRequested_{false};
    std::thread worker_;
};

BEGIN_MESSAGE_MAP(GenerateDialog, CDialog)
    ON_MESSAGE(GenerationCompleteMessage, &GenerateDialog::OnGenerationComplete)
END_MESSAGE_MAP()

class PreviewDialog final : public CDialog {
public:
    PreviewDialog(const amastra::PreparedPlan& plan, const amastra::ApiResult& api,
                  const std::wstring& logPath)
        : CDialog(IDD_PREVIEW, CWnd::FromHandle(GetMainApplicationWnd())),
          plan_(plan), api_(api), logPath_(logPath) {}

protected:
    BOOL OnInitDialog() override {
        CDialog::OnInitDialog();
        try {
            std::wostringstream summary;
            summary << L"Model: " << amastra::WideFromUtf8(plan_.source.name) << L"\r\n"
                    << L"Description: " << amastra::WideFromUtf8(plan_.source.description) << L"\r\n\r\n"
                    << plan_.parts.size() << L" components, " << plan_.source.materials.size()
                    << L" materials\r\n" << plan_.patches << L" four-point patches, "
                    << plan_.vertices << L" vertices\r\n" << plan_.splinePaths << L" splines, "
                    << plan_.controlPointRecords << L" A:M control-point records\r\n\r\n";
            for (std::size_t i = 0; i < plan_.parts.size(); ++i) {
                const auto& part = plan_.parts[i];
                const auto& material = plan_.source.materials[part.material];
                summary << (i + 1) << L". " << amastra::WideFromUtf8(part.name) << L" — "
                        << amastra::WideFromUtf8(amastra::KindName(plan_.source.components[i].kind))
                        << L", " << part.faces.size() << L" patches, material "
                        << amastra::WideFromUtf8(material.name) << L" ("
                        << amastra::WideFromUtf8(amastra::FinishName(material.finish)) << L")\r\n";
            }
            summary << L"\r\nAstra response: " << amastra::WideFromUtf8(api_.responseId) << L"\r\n"
                    << L"OpenAI request: " << amastra::WideFromUtf8(api_.requestId) << L"\r\n"
                    << L"Prompt log: " << logPath_ << L"\r\n\r\n"
                    << L"Create Model makes a new embedded model. Existing model geometry is not edited. "
                    << L"Components are disconnected named groups; tube and lathe ends are intentionally open.";
            SetControlText(m_hWnd, IDC_PREVIEW_SUMMARY, summary.str());
        } catch (const std::exception& error) {
            ErrorBox(error.what());
            EndDialog(IDABORT);
        }
        return TRUE;
    }

private:
    const amastra::PreparedPlan& plan_;
    const amastra::ApiResult& api_;
    const std::wstring& logPath_;
};

using NativePoint = std::array<float, 3>;
using PatchKey = std::array<std::uint32_t, 4>;

NativePoint Position(const Vector& value) { return {value.x, value.y, value.z}; }

struct ExpectedPatch {
    amastra::Vec3 normal;
    std::string partName;
};

struct NativePart {
    HGroup* group = nullptr;
    std::size_t material = 0;
    bool smooth = false;
    std::vector<HCP*> points;
    std::vector<PatchKey> faces;
};

struct NativePlan {
    std::map<PatchKey, ExpectedPatch> patches;
    std::map<std::uint32_t, std::pair<NativePoint, std::size_t>> vertices;
    std::map<std::uint32_t, bool> smooth;
    std::set<std::pair<std::uint32_t, std::uint32_t>> edges;
    std::set<HSpline*> closed;
    std::vector<NativePart> parts;
};

void SetFloat(HFloatProperty* property, double value) {
    if (!property || !std::isfinite(value)) throw amastra::Error("A:M returned an invalid surface property");
    property->SetNull(FALSE);
    property->StoreValue(Time(0), static_cast<float>(value), FALSE);
}

void SetPercentage(HFloatProperty* property, double fraction) {
    if (!std::isfinite(fraction) || fraction < 0 || fraction > 1)
        throw amastra::Error("A material percentage is outside the supported range");
    SetFloat(property, fraction);
    const auto stored = property->GetValue(Time(0));
    if (!std::isfinite(stored) || std::abs(stored - fraction) > 1e-5)
        throw amastra::Error("A:M did not retain a material percentage");
}

void SetColor(HColorProperty* property, const RGBFloat& value) {
    if (!property) throw amastra::Error("A:M returned a missing surface color");
    property->SetNull(FALSE);
    property->StoreValue(Time(0), value, FALSE);
}

void ApplyMaterial(HGroup* group, const amastra::Material& material) {
    auto* attr = group ? group->GetAttr() : nullptr;
    if (!attr) throw amastra::Error("A:M returned a missing component-group surface");
    attr->SetNull(FALSE);
    SetColor(attr->GetDiffuseColor(), RGBFloat(static_cast<float>(material.color.x),
                                               static_cast<float>(material.color.y),
                                               static_cast<float>(material.color.z)));
    SetColor(attr->GetSpecularColor(), RGBFloat(1.F));
    SetFloat(attr->GetDiffuseFallOff(), 1);
    SetFloat(attr->GetAmbiance(), .05);
    SetFloat(attr->GetRoughness(), 0);
    SetFloat(attr->GetRoughnessScale(), 0);
    const auto surface = amastra::SurfaceForMaterial(material);
    SetPercentage(attr->GetSpecularSize(), surface.specularSize);
    SetPercentage(attr->GetSpecularIntensity(), surface.specularIntensity);
    SetPercentage(attr->GetReflectivity(), surface.reflectivity);
    SetPercentage(attr->GetTransparency(), surface.transparency);
    SetFloat(attr->GetRefraction(), surface.refraction);
    group->OnModified();
}

void AddGroupPoints(HGroup* group, const std::vector<HCP*>& points) {
    if (!group) throw amastra::Error("A:M returned a missing component group");
    for (auto* point : points) {
        if (!point || !group->AddCP(point) || !group->IsCPInGroup(point))
            throw amastra::Error("A:M could not populate a component group");
    }
}

void CreatePart(HModelCache* model, const amastra::MeshPart& part, NativePlan& expected) {
    std::vector<Vector> positions;
    positions.reserve(part.vertices.size());
    for (const auto& point : part.vertices)
        positions.emplace_back(static_cast<float>(point.x), static_cast<float>(point.y),
                               static_cast<float>(point.z));

    std::vector<HCP*> heads(part.vertices.size(), nullptr);
    std::vector<std::pair<std::uint32_t, HCP*>> occurrences;
    for (const auto& path : part.splines.paths) {
        auto* spline = model->StartSpline(&positions[path.vertex[0]], &positions[path.vertex[1]]);
        if (!spline) throw amastra::Error("A:M could not create a planned spline");
        auto* first = spline->GetHeadCP();
        auto* second = first ? first->GetNext() : nullptr;
        if (!first || !second) throw amastra::Error("A:M returned an incomplete spline");
        if (part.smooth) { first->SetSmooth(); second->SetSmooth(); }
        else { first->SetPeaked(); second->SetPeaked(); }
        occurrences.emplace_back(path.vertex[0], first);
        occurrences.emplace_back(path.vertex[1], second);
        for (std::size_t index = 2; index < path.vertex.size(); ++index) {
            auto* point = spline->CreateCPAtTail(positions[path.vertex[index]]);
            if (!point) throw amastra::Error("A:M could not create a spline control point");
            if (part.smooth) point->SetSmooth(); else point->SetPeaked();
            occurrences.emplace_back(path.vertex[index], point);
        }
        if (path.closed) {
            spline->MakeLooped(TRUE);
            expected.closed.insert(spline);
        }
    }

    for (const auto& occurrence : occurrences) {
        auto*& head = heads[occurrence.first];
        if (!head) head = occurrence.second;
        else if (model->AttachCPs(head, occurrence.second))
            throw amastra::Error("A:M unexpectedly merged planned spline control points");
    }
    for (std::size_t vertex = 0; vertex < heads.size(); ++vertex) {
        if (!heads[vertex]) throw amastra::Error("A:M omitted a planned vertex");
        heads[vertex] = heads[vertex]->GetHead();
        const auto id = heads[vertex]->GetID();
        if (!expected.vertices.emplace(id, std::make_pair(Position(positions[vertex]),
                                                          part.splines.occurrences[vertex])).second)
            throw amastra::Error("A:M unexpectedly welded separate component vertices");
        expected.smooth.emplace(id, part.smooth);
    }

    NativePart nativePart;
    nativePart.material = part.material;
    nativePart.smooth = part.smooth;
    nativePart.points.reserve(occurrences.size());
    for (const auto& occurrence : occurrences) nativePart.points.push_back(occurrence.second);
    nativePart.group = model->CreateGroup(part.name.c_str());
    AddGroupPoints(nativePart.group, nativePart.points);

    for (const auto& face : part.faces) {
        PatchKey key;
        std::array<amastra::Vec3, 4> points;
        for (std::size_t corner = 0; corner < 4; ++corner) {
            key[corner] = heads[face.vertex[corner]]->GetID();
            points[corner] = part.vertices[face.vertex[corner]];
        }
        for (std::size_t corner = 0; corner < 4; ++corner)
            expected.edges.insert(std::minmax(key[corner], key[(corner + 1) % 4]));
        auto normal = amastra::Unit(amastra::Cross(points[1] - points[0], points[2] - points[0]) +
                                    amastra::Cross(points[2] - points[0], points[3] - points[0]));
        std::sort(key.begin(), key.end());
        if (!expected.patches.emplace(key, ExpectedPatch{normal, part.name}).second)
            throw amastra::Error("Duplicate native patch identity");
        nativePart.faces.push_back(key);
    }
    expected.parts.push_back(std::move(nativePart));
}

PatchKey NativePatchKey(HPatch* patch) {
    if (!patch) throw amastra::Error("A:M returned a missing patch");
    HCP* corners[] = {patch->GetCP1(), patch->GetCP2(), patch->GetCP3(), patch->GetCP4()};
    PatchKey key;
    for (std::size_t corner = 0; corner < 4; ++corner) {
        if (!corners[corner] || !corners[corner]->GetHead())
            throw amastra::Error("A native patch has a missing corner");
        key[corner] = corners[corner]->GetHead()->GetID();
    }
    std::sort(key.begin(), key.end());
    return key;
}

void VerifyAndMaterial(HModelCache* model, const NativePlan& expected,
                       const amastra::PreparedPlan& plan) {
    std::set<HSpline*> splines;
    std::map<std::uint32_t, std::size_t> actualVertices;
    std::multiset<std::pair<std::uint32_t, std::uint32_t>> actualEdges;
    std::size_t controlPoints = 0;
    for (auto* spline = model->GetHeadSpline(); spline; spline = spline->GetNextSpline()) {
        if (!splines.insert(spline).second || splines.size() > plan.splinePaths + 1)
            throw amastra::Error("A:M returned an unexpected native spline structure");
        auto* first = spline->GetHeadCP();
        std::set<HCP*> visited;
        for (auto* point = first; point; point = point->GetNext()) {
            if (!visited.insert(point).second) {
                if (point == first) break;
                throw amastra::Error("A:M returned an unexpected control-point loop");
            }
            if (++controlPoints > amastra::HardMaxControlPointRecords)
                throw amastra::Error("A:M returned too many control points");
            auto* head = point->GetHead();
            if (!head || !point->GetModelPosition()) throw amastra::Error("A:M returned a missing native point");
            const auto id = head->GetID();
            const auto found = expected.vertices.find(id);
            if (found == expected.vertices.end() || found->second.first != Position(*point->GetModelPosition()))
                throw amastra::Error("A native point differs from the validated plan");
            if (expected.smooth.at(id)) {
                if (!point->IsSmooth()) throw amastra::Error("A:M did not retain a planned smooth point");
            } else if (!point->IsPeaked()) {
                throw amastra::Error("A:M did not retain a planned peaked point");
            }
            if (++actualVertices[id] > 2)
                throw amastra::Error("A:M attached more than two splines at one control point");
            if (auto* next = point->GetNext()) actualEdges.insert(std::minmax(id, next->GetHead()->GetID()));
            else if (expected.closed.count(spline)) {
                if (!point->IsLoop() && !first->IsLoop() && first->GetPrev() != point)
                    throw amastra::Error("A:M did not close a planned spline");
                actualEdges.insert(std::minmax(id, first->GetHead()->GetID()));
            }
        }
    }
    if (splines.size() != plan.splinePaths || controlPoints != plan.controlPointRecords)
        throw amastra::Error("A:M spline totals differ from the validated plan");
    for (const auto& vertex : expected.vertices) {
        if (actualVertices[vertex.first] != vertex.second.second)
            throw amastra::Error("An A:M junction has an unexpected control-point count");
    }
    if (actualEdges != std::multiset<std::pair<std::uint32_t, std::uint32_t>>(
                           expected.edges.begin(), expected.edges.end()))
        throw amastra::Error("A:M spline edges differ from the validated plan");

    model->Update();
    model->FindPatches();
    const int count = model->GetPatchCount();
    if (count < 0 || static_cast<std::size_t>(count) > amastra::HardMaxPatches * 2)
        throw amastra::Error("A:M returned an invalid patch count");
    auto remaining = expected.patches;
    std::size_t unexpected = 0;
    for (int index = 0; index < count; ++index) {
        const auto found = remaining.find(NativePatchKey(model->GetPatch(static_cast<UINT>(index))));
        if (found == remaining.end()) ++unexpected;
        else remaining.erase(found);
    }
    if (!remaining.empty() || unexpected || model->GetHeadPatch5()) {
        std::ostringstream message;
        message << "A:M found " << count << " patches; expected " << expected.patches.size()
                << ". Missing: " << remaining.size() << "; unexpected or duplicate: " << unexpected << '.';
        if (!remaining.empty()) message << " First missing patch belongs to '"
                                        << remaining.begin()->second.partName << "'.";
        if (model->GetHeadPatch5()) message << " A:M also created an unexpected five-point patch.";
        message << " Materials were not assigned because topology verification failed.";
        throw amastra::Error(message.str());
    }
    for (int index = 0; index < count; ++index) {
        auto* patch = model->GetPatch(static_cast<UINT>(index));
        const auto& wanted = expected.patches.at(NativePatchKey(patch));
        Vector normal;
        patch->GetPointNormalOnPatch(.5F, .5F, normal);
        if (amastra::Dot(wanted.normal, {normal.x, normal.y, normal.z}) < 0) patch->ReverseNormal();
    }

    for (const auto& part : expected.parts) ApplyMaterial(part.group, plan.source.materials[part.material]);
    model->OnModified();
    model->Update();

    if (model->GetPatchCount() != count || model->GetHeadPatch5())
        throw amastra::Error("A:M changed patch topology while assigning materials");
    std::map<PatchKey, HPatch*> patches;
    for (int index = 0; index < count; ++index) {
        auto* patch = model->GetPatch(static_cast<UINT>(index));
        const auto key = NativePatchKey(patch);
        if (!expected.patches.count(key) || !patches.emplace(key, patch).second)
            throw amastra::Error("A:M changed patch identity while assigning materials");
    }
    for (const auto& part : expected.parts) {
        const int groupPatches = part.group->GetPatchCount();
        if (groupPatches < 0 || static_cast<std::size_t>(groupPatches) != part.faces.size())
            throw amastra::Error("A component group's patch coverage differs from the validated plan");
        for (const auto& key : part.faces) {
            if (!part.group->IsPatchInGroup(patches.at(key)))
                throw amastra::Error("A:M omitted a patch from its component group");
        }
        auto* attr = part.group->GetAttr();
        auto* diffuse = attr ? attr->GetDiffuseColor() : nullptr;
        if (!diffuse || attr->IsNull() || diffuse->IsNull())
            throw amastra::Error("A:M did not retain a component material");
        const auto actual = diffuse->GetNormalizedRGBFloat();
        const auto& wanted = plan.source.materials[part.material].color;
        if (std::abs(actual.m_red - wanted.x) > 1e-5 ||
            std::abs(actual.m_green - wanted.y) > 1e-5 ||
            std::abs(actual.m_blue - wanted.z) > 1e-5)
            throw amastra::Error("A:M retained the wrong component color");
    }
}

} // namespace

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(std::uint32_t index, ObjectType& type) {
    if (index >= _countof(Contexts)) return FALSE;
    type = Contexts[index];
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject* object, std::uint32_t index,
                                                           String& name, MenuCategory& category,
                                                           BOOL& disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try {
        if (!ContextOK(object, index)) return FALSE;
        name = "Create Model with Astra...";
        category = MC_WIZARD;
        disabled = FALSE;
        return TRUE;
    } catch (CException* error) {
        error->Delete();
    } catch (...) {}
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject* object, std::uint32_t index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    std::unique_ptr<amastra::PromptLog> log;
    amastra::ApiResult api;
    amastra::PreparedPlan plan;
    HModelCache* created = nullptr;
    bool modelComplete = false;
    std::string failure;
    try {
        if (!ContextOK(object, index)) return FALSE;
        PromptDialog promptDialog;
        const auto promptResult = promptDialog.DoModal();
        if (promptResult == IDCANCEL) return TRUE;
        if (promptResult != IDOK) throw amastra::Error("Cannot open the Astra prompt dialog");

        log = std::make_unique<amastra::PromptLog>();
        log->Begin(promptDialog.prompt, promptDialog.componentLimit, promptDialog.patchLimit);
        std::string apiKey = amastra::LoadApiKey();
        const std::string request = amastra::BuildRequestJson(promptDialog.prompt,
                                                              promptDialog.componentLimit,
                                                              promptDialog.patchLimit);
        GenerateDialog generation(std::move(apiKey), request, promptDialog.componentLimit,
                                  promptDialog.patchLimit);
        amastra::SecureErase(apiKey);
        const auto generationResult = generation.DoModal();
        api = generation.api;
        if (generationResult == IDCANCEL) {
            log->Finish("cancelled_during_generation", &api, nullptr, "User cancelled generation");
            return TRUE;
        }
        if (generationResult != IDOK) {
            if (!generation.error.empty()) throw amastra::Error(generation.error);
            throw amastra::Error("Cannot complete the Astra generation dialog");
        }
        plan = std::move(generation.plan);

        PreviewDialog preview(plan, api, log->path());
        const auto previewResult = preview.DoModal();
        if (previewResult == IDCANCEL) {
            log->Finish("cancelled_at_preview", &api, &plan, "Validated plan was not created");
            return TRUE;
        }
        if (previewResult != IDOK) throw amastra::Error("Cannot open the Astra plan preview");

        CWaitCursor busy;
        NativePlan expected;
        const auto incompleteName = "ASTRA INCOMPLETE - " + plan.source.name;
        created = HModelCache::New(incompleteName.c_str());
        if (!created) throw amastra::Error("A:M could not create a new model");
        for (const auto& part : plan.parts) CreatePart(created, part, expected);
        VerifyAndMaterial(created, expected, plan);
        created->SetName(plan.source.name.c_str());
        created->SetChanged();
        created->Update();
        created->OpenView();
        created->ZoomFit();
        RefreshAllTrees();
        modelComplete = true;
        log->Finish("success", &api, &plan, "Native A:M topology and group coverage verified");

        std::wostringstream message;
        message << L"Created '" << amastra::WideFromUtf8(plan.source.name) << L"' as "
                << plan.parts.size() << L" named components and " << plan.patches
                << L" four-point patches.\r\n\r\n"
                << L"Inspect the result in shaded and wireframe views, then save it as an A:M model.\r\n\r\n"
                << L"Prompt log: " << log->path();
        MessageBoxW(GetMainApplicationWnd(), message.str().c_str(), L"Astra Modeler 0.1.0",
                    MB_OK | MB_ICONINFORMATION);
        return TRUE;
    } catch (CException* error) {
        char message[1024]{};
        error->GetErrorMessage(message, _countof(message));
        failure = message;
        error->Delete();
    } catch (const std::exception& error) {
        failure = error.what();
    } catch (...) {
        failure = "Unexpected Astra Modeler error";
    }

    if (log) {
        try { log->Finish("failure", api.responseId.empty() && api.requestId.empty() ? nullptr : &api,
                          plan.parts.empty() ? nullptr : &plan, failure); }
        catch (const std::exception& loggingError) {
            failure += std::string("\n\nThe final prompt-log record also failed: ") + loggingError.what();
        }
    }
    if (created && !modelComplete) {
        failure += "\n\nA model named ASTRA INCOMPLETE may remain. Inspect or remove that new model. "
                   "Existing models were not edited.";
        try {
            created->SetChanged();
            created->Update();
            created->OpenView();
            RefreshAllTrees();
        } catch (CException* error) {
            error->Delete();
        } catch (...) {}
    } else if (created && modelComplete) {
        failure += "\n\nThe model was created and verified, but a later completion step failed.";
    }
    ErrorBox("Astra Modeler 0.1.0\n\n" + failure);
    return FALSE;
}
