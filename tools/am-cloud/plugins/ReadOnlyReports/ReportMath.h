#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>

namespace am_reports {
// Input positions come from SDK float coordinates. Accumulate in double.
struct PositionStats {
    std::size_t count = 0;
    std::size_t invalid = 0;
    std::array<double, 3> minimum{};
    std::array<double, 3> maximum{};
    std::array<double, 3> sum{};

    void add(double x, double y, double z) {
        const std::array<double, 3> p{x, y, z};
        if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z)) {
            ++invalid;
            return;
        }
        if (count == 0) minimum = maximum = p;
        for (std::size_t axis = 0; axis < 3; ++axis) {
            minimum[axis] = std::min(minimum[axis], p[axis]);
            maximum[axis] = std::max(maximum[axis], p[axis]);
            sum[axis] += p[axis];
        }
        ++count;
    }
    std::array<double, 3> mean() const {
        if (!count) return {};
        return {sum[0] / static_cast<double>(count),
                sum[1] / static_cast<double>(count),
                sum[2] / static_cast<double>(count)};
    }
};
}  // namespace am_reports
