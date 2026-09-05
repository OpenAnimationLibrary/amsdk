#include "../ReadOnlyReports/ReportCommon.h"

CPluginApp theApp;

namespace {
HModelCache *modelCache(HTreeObject *object) {
    if (!object || object->GetObjectType() != HOT_MODEL) return nullptr;
    auto *anim = static_cast<HAnimObject *>(object);
    if (!anim->IsCache()) return nullptr;  // Never silently switch an instance.
    return static_cast<HModelCache *>(object);
}
}  // namespace

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(
    const uint32_t index, ObjectType &type) {
    if (index != 0) return FALSE;
    type = HOT_MODEL;
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const uint32_t index, String &name,
    MenuCategory &category, BOOL &disabled) {
    if (index != 0) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return am_reports::guarded("AMModelReport", [&]() -> BOOL {
        CString label("A:M Model Report v1 (read-only)");
        name = label;
        category = MC_WIZARD;
        disabled = modelCache(object) == nullptr;
        return TRUE;
    });
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(
    HTreeObject *object, const uint32_t index) {
    if (index != 0) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return am_reports::guarded("AMModelReport", [&]() -> BOOL {
        HModelCache *model = modelCache(object);
        if (!model) throw std::runtime_error("Open a model directly and invoke the report from its Project Workspace entry, not an Action/Choreography instance.");
        const BOOL modified = model->IsModified();
        am_reports::Budget budget;
        am_reports::Points points;
        std::unordered_set<HSpline *> splines;
        for (HSpline *spline = model->GetHeadSpline(); spline; spline = spline->GetNextSpline()) {
            budget.step();
            if (!splines.insert(spline).second)
                throw std::runtime_error("Unexpected cycle in the SDK spline list; report stopped.");
            HCP *first = spline->GetHeadCP();
            std::unordered_set<HCP *> onSpline;
            for (HCP *cp = first; cp; cp = cp->GetNext()) {
                budget.step();
                if (!onSpline.insert(cp).second) {
                    if (cp == first && first->IsLoop()) break;
                    throw std::runtime_error("Unexpected cycle in a control-point list; report stopped.");
                }
                points.add(cp);
            }
        }
        std::unordered_set<HHashObject *> groups;
        HGroupContainer *container = model->GetChildGroupContainer();
        for (HHashObject *group = container ? container->GetChildGroup() : nullptr;
             group; group = group->GetSiblingSame()) {
            budget.step();
            if (group->GetObjectType() != HOT_GROUP || !groups.insert(group).second)
                throw std::runtime_error("Unexpected type/cycle in the SDK group list; report stopped.");
        }
        CString text = am_reports::heading("A:M Model Report", "Model cache");
        text.AppendFormat("Spline records: %llu\nGroup entries in model container: %llu\n"
                          "SDK GetPatchCount(): %d\nSDK CountBones(): %d\n",
                          static_cast<unsigned long long>(splines.size()),
                          static_cast<unsigned long long>(groups.size()),
                          model->GetPatchCount(), model->CountBones());
        points.append(text);
        text += "Patch value is read as supplied by the SDK; patches are not recomputed.\n";
        am_reports::finish(text, modified, model);
        return TRUE;
    });
}
