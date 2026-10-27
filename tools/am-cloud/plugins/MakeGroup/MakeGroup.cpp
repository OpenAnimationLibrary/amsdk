#include "StdAfx.h"
#include "Cube.h"
#include "ObjType.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HCP.h"
#include "SDK/HPatch.h"
#include "SDK/HProject.h"
#include "SDK/HPropert.h"
#include <commdlg.h>
#include <array>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <string>

CPluginApp theApp;
namespace {
bool busy = false;
HModelCache *modelFor(HTreeObject *object) {
    if (!object) return nullptr;
    HHashObject *model = nullptr;
    if (object->GetObjectType() == HOT_MODEL) model = static_cast<HHashObject *>(object);
    else if (object->GetObjectType() == HOT_GROUP)
        model = static_cast<HHashObject *>(object)->GetParentOfType(HOT_MODEL);
    return model && model->IsCache() ? static_cast<HModelCache *>(model) : nullptr;
}
HModelCache *liveModel(const void *identity) {
    auto *project = GetHProject();
    auto *container = project ? project->GetChildObjectCacheContainer() : nullptr;
    if (container)
        for (auto *model = container->GetChildModelCache(); model;
             model = static_cast<HModelCache *>(model->GetSiblingSame()))
            if (model == identity) return model;
    return nullptr;
}
std::string groupName(HModelCache *model) {
    for (unsigned i = 1; i < 1000000; ++i) {
        const std::string name = i == 1 ? "color" : "color " + std::to_string(i);
        bool exists = false;
        if (auto *container = model->GetChildGroupContainer())
            for (auto *group = container->GetChildGroup(); group;
                 group = static_cast<HGroup *>(group->GetSiblingSame()))
                if (name == group->GetName()) { exists = true; break; }
        if (!exists) return name;
    }
    throw std::runtime_error("A unique color group name could not be created.");
}
HGroup *cube(HModelCache *model, const std::string &name, float offsetX = 0) {
    model->SaveAllToUndo();
    auto *group = model->CreateGroup(name.c_str());
    if (!group) throw std::runtime_error("A:M could not create the color group.");
    group->SetTempGroup(FALSE);
    GetHProject()->DeselectAll();
    HGroupCP *selected = nullptr;
    for (const auto &face : make_group::faces) {
        std::array<HCP *, 4> first{}, last{};
        for (std::size_t i = 0; i < 4; ++i) {
            const auto &a = face[i], &b = face[(i + 1) % 4];
            Vector from(a.x + offsetX, a.y, a.z), to(b.x + offsetX, b.y, b.z);
            auto *spline = model->StartSpline(&from, &to);
            if (!spline || !(first[i] = spline->GetHeadCP()) || !(last[i] = first[i]->GetNext()))
                throw std::runtime_error("A:M could not create a cube edge. Partial model changes may remain.");
            first[i]->SetPeaked(); last[i]->SetPeaked();
        }
        // Four separate two-point splines, attached at the face corners.
        // Faces remain independent, matching the owner's working cube.mdl.
        for (std::size_t i = 0; i < 4; ++i)
            model->AttachCPs(first[(i + 1) % 4], last[i]);
        for (std::size_t i = 0; i < 4; ++i)
            for (auto *cp : {first[i], last[i]}) {
                if (!group->AddCP(cp) && !group->IsCPInGroup(cp))
                    throw std::runtime_error("A:M could not add a cube point to the color group.");
                cp->AddToGroup(&selected);
            }
    }
    if (selected) model->AddToTemporaryGroup(selected);
    model->FindPatches();
    model->SetChanged(TRUE);
    model->Update();
    model->MakeCurrent();
    model->OpenView();
    model->ZoomFit();
    group->HilightInProjectBar();
    GetHProject()->UpdateAllViews(TRUE);
    return group;
}
bool contains(HModelCache *model, HGroup *identity) {
    auto *container = model->GetChildGroupContainer();
    if (container)
        for (auto *group = container->GetChildGroup(); group;
             group = static_cast<HGroup *>(group->GetSiblingSame()))
            if (group == identity) return true;
    return false;
}
void setColor(HModelCache *model, HGroup *group, COLORREF chosen) {
    auto *surface = group->GetAttr();
    auto *diffuse = surface ? surface->GetDiffuseColor() : nullptr;
    if (!diffuse) throw std::runtime_error("A:M could not access the group's diffuse color.");
    // Enable the group surface and its diffuse child explicitly.
    surface->SetNull(FALSE, group);
    diffuse->SetNull(FALSE, group);
    diffuse->StoreValue(Time(), RGBFloat(GetRValue(chosen) / 255.0F,
        GetGValue(chosen) / 255.0F, GetBValue(chosen) / 255.0F), TRUE);
    surface->OnModified();
    group->OnModified();
    model->OnModified();
    model->SetChanged(TRUE);
    GetHProject()->UpdateAllViews(TRUE);
}
struct TestGroup { const char *name; COLORREF color; };
constexpr TestGroup tests[] = {
    {"MG Red", RGB(255,0,0)}, {"MG Green", RGB(0,255,0)}, {"MG Blue", RGB(0,0,255)}
};
constexpr const char *commands[] = {
    "Make Group...", "Make Group - Create Three Colors", "Make Group - Swap Test Groups"
};
HGroup *findGroup(HModelCache *model, const char *name) {
    auto *container = model ? model->GetChildGroupContainer() : nullptr;
    if (container)
        for (auto *group = container->GetChildGroup(); group;
             group = static_cast<HGroup *>(group->GetSiblingSame()))
            if (std::string(group->GetName()) == name) return group;
    return nullptr;
}
void createTest(HModelCache *model) {
    for (const auto &test : tests)
        if (findGroup(model, test.name))
            throw std::runtime_error("A color test group already exists. Use a new empty model for a fresh test.");
    for (std::size_t i = 0; i < 3; ++i) {
        auto *group = cube(model, tests[i].name, make_group::centers[i]);
        setColor(model, group, tests[i].color);
    }
}
std::vector<HGroup *> groupOrder(HGroupContainer *container) {
    std::vector<HGroup *> order;
    for (auto *group = container->GetChildGroup(); group;
         group = static_cast<HGroup *>(group->GetSiblingSame()))
        order.push_back(group);
    return order;
}
void swapTest(HModelCache *model) {
    auto *red = findGroup(model, tests[0].name);
    auto *green = findGroup(model, tests[1].name);
    auto *blue = findGroup(model, tests[2].name);
    auto *container = model->GetChildGroupContainer();
    if (!red || !green || !blue || !container)
        throw std::runtime_error("Create Three Colors first, in this model.");
    const auto before = groupOrder(container);
    const auto redAt = std::find(before.begin(), before.end(), red);
    const auto blueAt = std::find(before.begin(), before.end(), blue);
    if (redAt == before.end() || blueAt == before.end())
        throw std::runtime_error("The test group order could not be read.");
    const auto leftAt = (std::min)(redAt, blueAt);
    const auto rightAt = (std::max)(redAt, blueAt);
    HGroup *left = *leftAt, *right = *rightAt;
    HGroup *previousLeft = leftAt == before.begin() ? nullptr : *(leftAt - 1);
    HGroup *previousRight = *(rightAt - 1);
    model->SaveAllToUndo();
    // Only move the two persistent test groups. Preserve the positions of the
    // green group, selection group and all unrelated groups.
    right->Move(container, previousLeft, FALSE, TRUE);
    left->Move(container, previousRight == left ? right : previousRight, FALSE, TRUE);
    auto expected = before;
    std::iter_swap(expected.begin() + (redAt - before.begin()),
                   expected.begin() + (blueAt - before.begin()));
    if (groupOrder(container) != expected)
        throw std::runtime_error("A:M did not produce the requested group order. Partial order changes may remain.");
    model->SetChanged(TRUE);
    model->OnModified();
    GetHProject()->UpdateAllViews(TRUE);
    // No color write, topology rebuild, Save or reload occurs during this command.
}
}
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const uint32_t index, ObjectType &type) {
    if (index >= 6) return FALSE;
    type = index % 2 == 0 ? HOT_MODEL : HOT_GROUP; return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const uint32_t index, String &name, MenuCategory &category, BOOL &disabled) {
    if (index >= 6) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try {
        name = commands[index / 2]; category = MC_WIZARD;
        auto *model = modelFor(object);
        disabled = busy || !model;
        if (!disabled && index / 2 == 2)
            disabled = !findGroup(model, tests[0].name) || !findGroup(model, tests[1].name) || !findGroup(model, tests[2].name);
        return TRUE;
    } catch (CException *error) {
        if (error) error->Delete();
    } catch (...) {}
    return FALSE;
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *object, const uint32_t index) {
    if (index >= 6) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (busy) return FALSE;
    struct Busy { Busy() { busy = true; } ~Busy() { busy = false; } } active;
    try {
        const HWND owner = GetMainApplicationWnd();
        if (!owner || GetWindowThreadProcessId(owner, nullptr) != GetCurrentThreadId())
            throw std::runtime_error("Run Make Group on A:M's UI thread.");
        auto *model = modelFor(object);
        auto *project = GetHProject();
        if (!model || !project) throw std::runtime_error("Run Make Group from a Model window or Model selection.");
        if (index / 2 == 1) { createTest(model); return TRUE; }
        if (index / 2 == 2) { swapTest(model); return TRUE; }
        const void *identity = model;
        HGroup *group = cube(model, groupName(model));
        COLORREF custom[16]{};
        CHOOSECOLORW choice{}; choice.lStructSize = sizeof(choice); choice.hwndOwner = owner;
        choice.rgbResult = RGB(0, 0, 255); choice.lpCustColors = custom;
        choice.Flags = CC_FULLOPEN | CC_RGBINIT;
        if (!ChooseColorW(&choice)) {
            if (CommDlgExtendedError()) throw std::runtime_error("The color picker could not be opened. The cube remains uncolored.");
            return TRUE; // Cancel preserves the cube/group with no color override.
        }
        if (GetHProject() != project || !(model = liveModel(identity)) || !contains(model, group))
            throw std::runtime_error("The model or color group changed. No color was assigned.");
        setColor(model, group, choice.rgbResult);
        return TRUE;
    } catch (CException *error) {
        if (error) error->Delete();
        MessageBoxW(GetMainApplicationWnd(), L"A:M or MFC could not complete Make Group. Partial model changes may remain.", L"Make Group", MB_OK | MB_ICONERROR);
    } catch (const std::exception &error) {
        MessageBoxA(GetMainApplicationWnd(), error.what(), "Make Group", MB_OK | MB_ICONERROR);
    } catch (...) {
        MessageBoxW(GetMainApplicationWnd(), L"Make Group could not complete. Partial model changes may remain.", L"Make Group", MB_OK | MB_ICONERROR);
    }
    return FALSE;
}
