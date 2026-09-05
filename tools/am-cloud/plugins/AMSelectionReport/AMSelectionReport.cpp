#include "../ReadOnlyReports/ReportCommon.h"

CPluginApp theApp;

namespace {
constexpr ObjectType kTypes[] = {HOT_GROUP, HOT_CP, HOT_CPINSTANCE};
constexpr const char *kNames[] = {"Group", "CP", "CP instance"};
constexpr uint32_t kCount = static_cast<uint32_t>(_countof(kTypes));
BOOL matches(HTreeObject *object, uint32_t index) {
    return object && index < kCount && object->GetObjectType() == kTypes[index];
}
}  // namespace

extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(
    const uint32_t index, ObjectType &type) {
    if (index >= kCount) return FALSE;
    type = kTypes[index];
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(
    HTreeObject *object, const uint32_t index, String &name,
    MenuCategory &category, BOOL &disabled) {
    if (index >= kCount) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return am_reports::guarded("AMSelectionReport", [&]() -> BOOL {
        CString label;
        label.Format("A:M Selection Report v1 - %s (read-only)", kNames[index]);
        name = label;
        category = MC_WIZARD;
        disabled = !matches(object, index);
        return TRUE;
    });
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(
    HTreeObject *object, const uint32_t index) {
    if (index >= kCount) return FALSE;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return am_reports::guarded("AMSelectionReport", [&]() -> BOOL {
        if (!matches(object, index))
            throw std::runtime_error("The selected SDK object does not match this report context.");
        const BOOL modified = object->IsModified();
        am_reports::Budget budget;
        am_reports::Points points;
        CString text = am_reports::heading("A:M Selection Report", kNames[index]);
        if (index == 0) {
            auto *group = static_cast<HGroup *>(object);
            std::unordered_set<HGroupCP *> members;
            for (HGroupCP *member = group->GetGroupCP(); member; member = member->GetNext()) {
                budget.step();
                if (!members.insert(member).second)
                    throw std::runtime_error("Unexpected cycle in the SDK group membership list; report stopped.");
                points.add(member->GetCP());
            }
            text.AppendFormat("Temporary selection group: %s\nGroup membership records: %llu\n",
                              group->IsTempGroup() ? "yes" : "no",
                              static_cast<unsigned long long>(members.size()));
        } else {
            HCP *cp = index == 1 ? static_cast<HCP *>(object)
                               : static_cast<HCPInstance *>(object)->GetCP();
            points.add(cp);
            text += "Single CP source; CP-instance reports deliberately use its raw model CP.\n";
        }
        points.append(text);
        am_reports::finish(text, modified, object);
        return TRUE;
    });
}
