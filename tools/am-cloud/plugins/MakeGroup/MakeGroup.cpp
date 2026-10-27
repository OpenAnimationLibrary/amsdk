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
HGroup *cube(HModelCache *model) {
    model->SaveAllToUndo();
    const std::string name = groupName(model);
    auto *group = model->CreateGroup(name.c_str());
    if (!group) throw std::runtime_error("A:M could not create the color group.");
    group->SetTempGroup(FALSE);
    GetHProject()->DeselectAll();
    HGroupCP *selected = nullptr;
    for (const auto &face : make_group::faces) {
        std::array<HCP *, 4> first{}, last{};
        for (std::size_t i = 0; i < 4; ++i) {
            const auto &a = face[i], &b = face[(i + 1) % 4];
            Vector from(a.x, a.y, a.z), to(b.x, b.y, b.z);
            auto *spline = model->StartSpline(&from, &to);
            if (!spline || !(first[i] = spline->GetHeadCP()) || !(last[i] = first[i]->GetNext()))
                throw std::runtime_error("A:M could not create a cube edge. Partial geometry may remain.");
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
}
extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(const uint32_t index, ObjectType &type) {
    if (index >= 2) return FALSE;
    type = index == 0 ? HOT_MODEL : HOT_GROUP; return TRUE;
}
extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const uint32_t index, String &name, MenuCategory &category, BOOL &disabled) {
    if (index >= 2) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try {
        name = "Make Group..."; category = MC_WIZARD; disabled = busy || !modelFor(object);
        return TRUE;
    } catch (CException *error) {
        if (error) error->Delete();
    } catch (...) {}
    return FALSE;
}
extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *object, const uint32_t index) {
    if (index >= 2) return FALSE;
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
        const void *identity = model;
        HGroup *group = cube(model);
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
        MessageBoxW(GetMainApplicationWnd(), L"A:M or MFC could not complete Make Group. Partial geometry may remain.", L"Make Group", MB_OK | MB_ICONERROR);
    } catch (const std::exception &error) {
        MessageBoxA(GetMainApplicationWnd(), error.what(), "Make Group", MB_OK | MB_ICONERROR);
    } catch (...) {
        MessageBoxW(GetMainApplicationWnd(), L"Make Group could not complete. Partial geometry may remain.", L"Make Group", MB_OK | MB_ICONERROR);
    }
    return FALSE;
}
