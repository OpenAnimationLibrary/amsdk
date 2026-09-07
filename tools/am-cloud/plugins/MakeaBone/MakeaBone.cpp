// MakeaBone 0.1.0. Developed for Rodney Baker with OpenAI Codex assistance.
// Uses the Hash SDK command, AddSegment and bone-property patterns.
#include "StdAfx.h"
#include "Coordinates.h"
#include "resource.h"
#include "SDK/Entry.h"
#include "SDK/HModel.h"
#include "SDK/Misc.h"
#include "Quaterni.h"
#include <set>
#include <string>
#include <vector>

CPluginApp theApp;

namespace {
constexpr ObjectType kContexts[] = {HOT_MODEL, HOT_GROUP, HOT_CP, HOT_SEGMENT};

HModelCache *ModelFor(HTreeObject *object, uint32_t index) {
    if (!object || index >= _countof(kContexts) ||
        object->GetObjectType() != kContexts[index]) return nullptr;
    // Only a model cache may be edited: never redirect an Action/Chor instance
    // to its source model. Selection parents are resolved before the dialog.
    HTreeObject *parent = object;
    while (parent && parent->GetObjectType() != HOT_MODEL) parent = parent->GetParent();
    if (!parent) return nullptr;
    HAnimObject *model = parent->GetAnimObject();
    return model && model->IsCache() ? static_cast<HModelCache *>(model) : nullptr;
}

class CoordinatesDialog final : public CDialog {
public:
    float values[6] = {0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f};
    CoordinatesDialog() : CDialog(IDD_MAKEABONE, CWnd::FromHandle(GetMainApplicationWnd())) {}

protected:
    BOOL OnInitDialog() override {
        CDialog::OnInitDialog();
        for (int i = 0; i < 6; ++i) {
            SetDlgItemText(IDC_START_X + i, i == 4 ? "10" : "0");
            static_cast<CEdit *>(GetDlgItem(IDC_START_X + i))->SetLimitText(64);
        }
        return TRUE;
    }

    void OnOK() override {
        for (int i = 0; i < 6; ++i) {
            CString text;
            GetDlgItemText(IDC_START_X + i, text);
            if (!makeabone::ParseCoordinate(std::string_view(text.GetString(), text.GetLength()), values[i])) {
                MessageBox("Enter a number between -1000000 and 1000000.\n"
                           "Use a period for decimals (for example, -2.5).", "MakeaBone", MB_OK | MB_ICONWARNING);
                auto *edit = static_cast<CEdit *>(GetDlgItem(IDC_START_X + i));
                edit->SetFocus();
                edit->SetSel(0, -1);
                return;
            }
        }
        if (!makeabone::ValidEndpoints(values)) {
            MessageBox("Start and end must be at least 0.00001 cm apart.", "MakeaBone", MB_OK | MB_ICONWARNING);
            GetDlgItem(IDC_END_X)->SetFocus();
            return;
        }
        CDialog::OnOK();
    }
};

String NewBoneName(HModelCache *model) {
    std::set<std::string> names;
    std::vector<HBoneCache *> pending;
    if (auto *container = model->GetChildBoneCacheContainer())
        if (auto *bone = container->GetChildBoneCache()) pending.push_back(bone);
    while (!pending.empty()) {
        HBoneCache *bone = pending.back();
        pending.pop_back();
        if (const char *name = bone->GetName()) names.insert(name);
        if (auto *child = bone->GetChildBoneCache()) pending.push_back(child);
        if (auto *sibling = bone->GetSiblingBoneCache()) pending.push_back(sibling);
    }
    std::string name = "MakeaBone";
    for (size_t number = 2; names.count(name); ++number)
        name = "MakeaBone " + std::to_string(number);
    return String(name.c_str());
}

BOOL CreateBone(HModelCache *model, const float (&values)[6]) {
    const Vector origin(values[0], values[1], values[2]);
    const Vector end(values[3], values[4], values[5]);
    const Vector direction = end - origin;
    const float length = direction.Norm();
    // A:M's unrotated bone points along +Z (see SDK E_Rebuild example).
    const Quaternion rotation = Rotate2VQ(Vector(0.0f, 0.0f, 1.0f), direction.Normalized());
    String name = NewBoneName(model);
    const ColorBuf color = GetColor(model->CountBones());
    model->SaveAllToUndo();
    // nullptr parent creates one top-level bone; no CPs are assigned or moved.
    HSegmentCache *bone = model->AddSegment(nullptr, nullptr, name, color);
    if (!bone) {
        AfxMessageBox("MakeaBone could not create the bone.", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    // Store rest properties, following the SDK's MirrorBone pattern. The model
    // snapshot covers the operation; do not add per-property undo records.
    bone->GetPivot()->StoreValue(Time(), origin, FALSE);
    bone->GetRotate()->StoreValue(Time(), rotation, FALSE, FALSE);
    bone->GetLength()->StoreValue(Time(), length, FALSE);
    bone->GetEnd()->StoreValue(Time(), end, FALSE);
    model->SetChanged();
    model->Update();
    model->MarkViewsNeedDrawn();
    RefreshAllTrees();
    return TRUE;
}
} // namespace

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(uint32_t index, ObjectType &type) {
    if (index >= _countof(kContexts)) return FALSE;
    type = kContexts[index];
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, uint32_t index, String &name, MenuCategory &category, BOOL &disabled) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try {
        if (!ModelFor(object, index)) return FALSE;
        name = "MakeaBone...";
        category = MC_WIZARD;
        disabled = FALSE;
        return TRUE;
    } catch (CException *error) { error->Delete(); }
      catch (...) {}
    return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *object, uint32_t index) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    try {
        HModelCache *model = ModelFor(object, index);
        if (!model) return FALSE;
        CoordinatesDialog dialog;
        const INT_PTR result = dialog.DoModal();
        if (result == IDCANCEL) return TRUE; // no snapshot or model edit
        if (result != IDOK) {
            AfxMessageBox("MakeaBone could not open its coordinate dialog.", MB_OK | MB_ICONERROR);
            return FALSE;
        }
        // Modal ownership prevents a model switch/close while coordinates are
        // being entered. No SDK handles are retained after this command.
        return CreateBone(model, dialog.values);
    } catch (CException *error) { error->Delete(); }
      catch (...) {}
    AfxMessageBox("MakeaBone could not finish. If a bone was added, use Undo.", MB_OK | MB_ICONERROR);
    return FALSE;
}
