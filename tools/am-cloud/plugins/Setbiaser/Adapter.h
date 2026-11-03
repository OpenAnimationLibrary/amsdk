#pragma once
#include "StdAfx.h"
#include "BiasCore.h"
#include <set>
#include <string>
#include <vector>

namespace sb {
// These addresses are identities only. Reacquire from the live project before use.
struct Key {
    std::uintptr_t cp{}, spline{}, head{}, previous{}, next{};
    std::uint32_t id{};
    bool operator==(const Key &) const = default;
};
struct Sample {
    Key key;
    Values values{};
    std::array<float,3> position{};
    unsigned flags{};
    bool operator==(const Sample &) const = default;
};
struct Snapshot {
    std::vector<Sample> samples;
    std::size_t skipped{}, locations{};
};
class Binding {
    std::uintptr_t project_{}, model_{};
    std::string name_;
    std::vector<Key> topology_;
    std::set<std::uintptr_t> selection_;
    HWND modelView_{};
    bool hadView_{};
    bool invalid_ = false;
    HModelCache *liveModel();
public:
    Units units;
    static HModelCache *resolve(HTreeObject *object);
    explicit Binding(HTreeObject *object);
    const std::string &name() const noexcept { return name_; }
    Snapshot read(bool entire);
    // Returns changed occurrence count. All results validate before any write.
    std::size_t commit(bool entire, const Snapshot &baseline, const Edit &edit);
};
} // namespace sb
