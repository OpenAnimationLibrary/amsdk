#include "Adapter.h"
#include <memory>
#include <unordered_set>
#include <utility>

namespace sb {
namespace {
constexpr std::size_t limit = 2000000;
std::uintptr_t identity(const void *p) { return reinterpret_cast<std::uintptr_t>(p); }
HWND activeView() {
    HWND mdi = FindWindowExW(GetMainApplicationWnd(), nullptr, L"MDIClient", nullptr);
    return mdi ? reinterpret_cast<HWND>(SendMessageW(mdi, WM_MDIGETACTIVE, 0, 0)) : nullptr;
}
struct Record { HCP *cp; Key key; };
std::vector<Record> enumerate(HModelCache *model) {
    std::vector<Record> result;
    std::unordered_set<HSpline*> splines;
    std::unordered_set<HCP*> points;
    for (auto *s = model->GetHeadSpline(); s; s = s->GetNextSpline()) {
        if (!splines.insert(s).second || splines.size() > limit)
            throw std::runtime_error("Unexpected spline traversal. No values were changed.");
        auto *first = s->GetHeadCP();
        for (auto *cp = first; cp;) {
            if (!points.insert(cp).second || points.size() > limit)
                throw std::runtime_error("Unexpected control-point traversal. No values were changed.");
            auto *head = cp->GetHead();
            if (!head) throw std::runtime_error("A control point has no attached-stack head.");
            auto *next = cp->GetNext();
            result.push_back({cp,{identity(cp),identity(s),identity(head),identity(cp->GetPrev()),identity(next),cp->GetID()}});
            if (next == first) break;
            cp = next;
        }
    }
    return result;
}
std::vector<Key> keys(const std::vector<Record> &records) {
    std::vector<Key> result; result.reserve(records.size());
    for (const auto &r : records) result.push_back(r.key);
    return result;
}
Units nativeUnits() {
    // The SDK's GetFactoredValue uses these exact property metadata factors.
    // Own only the temporary parent; the three sub-property infos are host-owned.
    auto deleter = [](HBiasPropertyInfo *p) { if (p) HPropertyInfo::DeleteHandle(p); };
    std::unique_ptr<HBiasPropertyInfo,decltype(deleter)> info(
        HBiasPropertyInfo::New("Setbiaser units", "SetbiaserUnits"), deleter);
    if (!info) throw std::runtime_error("Cannot obtain A:M's native bias metadata.");
    const std::array<HFloatPropertyInfo*,3> rows{
        info->GetMagnitudePropertyInfo(),info->GetAlphaPropertyInfo(),info->GetGammaPropertyInfo()};
    Units u;
    for (std::size_t row = 0; row != rows.size(); ++row) {
        if (!rows[row]) throw std::runtime_error("A:M's bias metadata is incomplete.");
        u.factor[row] = rows[row]->GetFactorValue();
        u.minimum[row] = rows[row]->GetMinValue();
        u.maximum[row] = rows[row]->GetMaxValue();
    }
    u.validate(); return u;
}
Values values(HCP *cp) {
    return {cp->GetInMagnitude(),cp->GetOutMagnitude(),cp->GetInAlpha(),
            cp->GetOutAlpha(),cp->GetInGamma(),cp->GetOutGamma()};
}
void write(HCP *cp, const Values &before, const Values &after) {
    if (before[0] != after[0]) cp->SetInMagnitude(after[0]);
    if (before[1] != after[1]) cp->SetOutMagnitude(after[1]);
    if (before[2] != after[2]) cp->SetInAlpha(after[2]);
    if (before[3] != after[3]) cp->SetOutAlpha(after[3]);
    if (before[4] != after[4]) cp->SetInGamma(after[4]);
    if (before[5] != after[5]) cp->SetOutGamma(after[5]);
}
bool eligible(HCP *cp, bool entire) {
    auto *head = cp->GetHead();
    if (!head || cp->IsLocked() || head->IsLocked()) return false;
    if (!entire && (cp->IsHide() || head->IsHide())) return false;
    // Endpoint direction and host-constrained hook behavior need host tests.
    if (!cp->GetNext() || !cp->GetPrev()) return false;
    return !cp->IsHook() && !cp->IsEndHook() && !cp->IsHookBase();
}
Sample sample(const Record &record) {
    const Vector *p = record.cp->GetModelPosition();
    if (!p) throw std::runtime_error("The control point has no base-model position.");
    return {record.key,values(record.cp),{p->x,p->y,p->z},
        (record.cp->IsPeaked() ? 1U : 0U) | (record.cp->IsSmooth() ? 2U : 0U) |
        (record.cp->IsFlip() ? 4U : 0U)};
}
} // namespace

HModelCache *Binding::resolve(HTreeObject *object) {
    if (!object || object->IsActionObjectChild()) return nullptr;
    HTreeObject *candidate = object;
    if (object->GetObjectType() == HOT_CP)
        candidate = static_cast<HCP*>(object)->GetSegmentCache();
    std::unordered_set<HTreeObject*> seen;
    while (candidate && seen.insert(candidate).second && seen.size() < 128) {
        if (candidate->GetObjectType() == HOT_MODEL) {
            auto *anim = candidate->GetAnimObject();
            return anim && anim->IsCache() ? static_cast<HModelCache*>(candidate) : nullptr;
        }
        candidate = candidate->GetParent();
    }
    return nullptr;
}
Binding::Binding(HTreeObject *object) {
    auto *project = GetHProject();
    auto *model = resolve(object);
    if (!project || project->IsLoadingProject() || !model)
        throw std::runtime_error("Run Setbiaser on a base-model CP, group, or model in the Model window.");
    project_ = identity(project); model_ = identity(model);
    name_ = model->GetName() ? model->GetName() : "Model";
    modelView_ = activeView(); hadView_ = modelView_ != nullptr;
    units = nativeUnits();
    const auto records = enumerate(model);
    topology_ = keys(records);
    std::unordered_set<HCP*> valid;
    for (const auto &r : records) valid.insert(r.cp);
    const auto include = [&](HCP *cp) {
        if (cp && valid.contains(cp) && !cp->IsHide()) selection_.insert(identity(cp->GetHead()));
    };
    if (object->GetObjectType() == HOT_CP) include(static_cast<HCP*>(object));
    else if (object->GetObjectType() == HOT_GROUP) {
        std::unordered_set<HGroupCP*> seen;
        for (auto *g = static_cast<HGroup*>(object)->GetGroupCP(); g; g = g->GetNext()) {
            if (!seen.insert(g).second || seen.size() > limit)
                throw std::runtime_error("The selected group could not be traversed safely.");
            include(g->GetCP());
        }
    }
    // No implicit selection->whole-model fallback. Model context starts empty.
}
HModelCache *Binding::liveModel() {
    if (invalid_) throw std::runtime_error("Binding expired. Run Setbiaser again on the intended selection.");
    auto *p = GetHProject();
    if (!p || identity(p) != project_ || p->IsLoadingProject()) {
        invalid_ = true;
        throw std::runtime_error("The project changed. Run Setbiaser again on the intended selection.");
    }
    if (hadView_ && (!IsWindow(modelView_) || activeView() != modelView_)) {
        invalid_ = true;
        throw std::runtime_error("The model window changed. Run Setbiaser again to rebind.");
    }
    auto *container = p->GetChildObjectCacheContainer();
    if (container) {
        std::unordered_set<HHashObject*> seen;
        for (HHashObject *item = container->GetChildModelCache(); item; item = item->GetSiblingSame()) {
            if (!seen.insert(item).second || seen.size() > limit) break;
            if (identity(item) == model_ && item->GetObjectType() == HOT_MODEL) {
                auto *model = static_cast<HModelCache*>(item);
                const char *name = model->GetName();
                if (model->IsCache() && name_ == (name ? name : "Model")) return model;
                break;
            }
        }
    }
    invalid_ = true;
    throw std::runtime_error("The bound model is no longer available. Run Setbiaser again.");
}
Snapshot Binding::read(bool entire) {
    auto *model = liveModel();
    const auto records = enumerate(model);
    if (keys(records) != topology_) {
        invalid_ = true;
        throw std::runtime_error("Model topology changed. Run Setbiaser again to bind fresh control points.");
    }
    Snapshot result;
    std::set<std::uintptr_t> locations;
    for (const auto &record : records) {
        if (!entire && !selection_.contains(record.key.head)) continue;
        if (!eligible(record.cp,entire)) { ++result.skipped; continue; }
        auto s = sample(record);
        if (!std::all_of(s.values.begin(),s.values.end(),[](float v){return std::isfinite(v);})) {
            ++result.skipped; continue;
        }
        locations.insert(record.key.head); result.samples.push_back(s);
    }
    result.locations = locations.size(); return result;
}
std::size_t Binding::commit(bool entire, const Snapshot &baseline, const Edit &edit) {
    const auto current = read(entire);
    if (baseline.samples != current.samples || baseline.skipped != current.skipped)
        throw std::runtime_error("The model or target eligibility changed during this edit. Refresh and try again.");
    if (baseline.samples.empty()) throw std::runtime_error("No eligible control points are bound.");
    std::vector<Values> results; results.reserve(baseline.samples.size());
    std::size_t changed = 0;
    for (const auto &s : baseline.samples) {
        const auto result = calculate(s.values,units,edit);
        if (result != s.values) ++changed;
        results.push_back(result);
    }
    if (!changed) return 0;
    // All SDK access is synchronous on A:M's UI thread. No host messages are
    // pumped between validation, native snapshot, setters, and final refresh.
    auto *model = liveModel();
    const auto records = enumerate(model);
    std::vector<HCP*> targets;
    std::size_t index = 0;
    for (const auto &r : records) {
        if (index < baseline.samples.size() && r.key == baseline.samples[index].key) {
            targets.push_back(r.cp); ++index;
        }
    }
    if (targets.size() != baseline.samples.size())
        throw std::runtime_error("Targets changed before commit. No values were changed.");
    model->SaveAllToUndo(); // Exactly once per non-no-op synchronous commit.
    for (std::size_t i = 0; i < targets.size(); ++i) write(targets[i],baseline.samples[i].values,results[i]);
    model->SetChanged();
    model->Update();
    model->MarkViewsNeedDrawn();
    GetHProject()->UpdateAllViews(FALSE);
    return changed;
}
} // namespace sb
