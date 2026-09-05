#include "ReportMath.h"
#include <iostream>
#include <limits>

int main() {
    using am_reports::PositionStats;
    PositionStats stats;
    if (stats.count || stats.invalid || stats.mean() != std::array<double, 3>{}) return 1;
    stats.add(-2, 4, 0);
    if (stats.count != 1 || stats.minimum != stats.maximum || stats.mean()[0] != -2) return 2;
    stats.add(6, -4, 10);
    if (stats.count != 2 || stats.minimum != std::array<double, 3>{-2, -4, 0} ||
        stats.maximum != std::array<double, 3>{6, 4, 10} ||
        stats.mean() != std::array<double, 3>{2, 0, 5}) return 3;
    stats.add(std::numeric_limits<double>::quiet_NaN(), 0, 0);
    stats.add(0, std::numeric_limits<double>::infinity(), 0);
    if (stats.count != 2 || stats.invalid != 2 || stats.mean()[2] != 5) return 4;
    PositionStats large;
    const double v = std::numeric_limits<float>::max();
    large.add(v, -v, v); large.add(-v, v, -v);
    if (large.count != 2 || large.mean() != std::array<double, 3>{}) return 5;
    std::cout << "PASS: empty, single, bounds, mean, invalid coordinates and float-range positions.\n";
    return 0;
}
