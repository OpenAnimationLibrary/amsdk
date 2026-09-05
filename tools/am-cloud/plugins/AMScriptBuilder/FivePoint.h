#pragma once
// Plan-topology-only five-point candidate detection.
// This does not call A:M and does not claim a candidate is an HPatch5.
#include "Plan.h"
#include <array>
#include <functional>
#include <set>
#include <vector>

namespace amscript {
using FiveCycle = std::array<std::size_t, 5>;

inline FiveCycle CanonicalFiveCycle(const FiveCycle& cycle) {
    FiveCycle best = cycle;
    for (unsigned reverse = 0; reverse < 2; ++reverse) {
        for (std::size_t offset = 0; offset < 5; ++offset) {
            FiveCycle candidate{};
            for (std::size_t i = 0; i < 5; ++i) {
                const std::size_t source = reverse ? (offset + 5 - i) % 5 : (offset + i) % 5;
                candidate[i] = cycle[source];
            }
            if (candidate < best) best = candidate;
        }
    }
    return best;
}

inline std::vector<FiveCycle> FivePointCandidates(const Plan& plan) {
    std::vector<std::set<std::size_t>> adjacency(plan.points.size());
    for (const auto& spline : plan.splines) {
        for (std::size_t i = 1; i < spline.size(); ++i) {
            adjacency[spline[i - 1]].insert(spline[i]);
            adjacency[spline[i]].insert(spline[i - 1]);
        }
    }
    std::set<FiveCycle> found;
    FiveCycle path{};
    std::function<void(std::size_t, std::size_t, std::size_t)> visit;
    visit = [&](std::size_t start, std::size_t current, std::size_t depth) {
        if (depth == 5) {
            if (!adjacency[current].count(start)) return;
            const auto cycle = CanonicalFiveCycle(path);
            for (std::size_t i = 0; i < 5; ++i) {
                const auto a = cycle[i];
                const auto previous = cycle[(i + 4) % 5];
                const auto next = cycle[(i + 1) % 5];
                for (const auto b : cycle) {
                    if (b != a && b != previous && b != next && adjacency[a].count(b)) return;
                }
            }
            found.insert(cycle);
            return;
        }
        for (const auto next : adjacency[current]) {
            if (next < start || next == start) continue;
            bool used = false;
            for (std::size_t i = 0; i < depth; ++i) if (path[i] == next) used = true;
            if (used) continue;
            path[depth] = next;
            visit(start, next, depth + 1);
        }
    };
    for (std::size_t start = 0; start < adjacency.size(); ++start) {
        path[0] = start;
        visit(start, start, 1);
    }
    return {found.begin(), found.end()};
}
} // namespace amscript
