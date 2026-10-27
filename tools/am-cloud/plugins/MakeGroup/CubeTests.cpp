#include "Cube.h"
#include <cmath>
#include <map>
#include <set>
#include <stdexcept>
#include <tuple>
#include <iostream>
int main() try {
    std::map<std::tuple<int,int,int>, unsigned> corners;
    std::set<std::tuple<int,int,int>> normals;
    for (const auto &face : make_group::faces) {
        std::set<std::tuple<int,int,int>> unique;
        for (const auto &p : face) {
            if (std::abs(p.x) != 50 || std::abs(p.y) != 50 || std::abs(p.z) != 50)
                throw std::runtime_error("Cube bounds changed.");
            const auto key = std::make_tuple(static_cast<int>(p.x), static_cast<int>(p.y), static_cast<int>(p.z));
            ++corners[key]; unique.insert(key);
        }
        if (unique.size() != 4) throw std::runtime_error("A cube face has repeated corners.");
        const auto &a = face[0], &b = face[1], &c = face[2], &d = face[3];
        const float ux=b.x-a.x, uy=b.y-a.y, uz=b.z-a.z;
        const float vx=c.x-a.x, vy=c.y-a.y, vz=c.z-a.z;
        const float nx=uy*vz-uz*vy, ny=uz*vx-ux*vz, nz=ux*vy-uy*vx;
        const float area = std::abs(nx)+std::abs(ny)+std::abs(nz);
        if (area != 10000 || nx*a.x+ny*a.y+nz*a.z <= 0 ||
            nx*(d.x-a.x)+ny*(d.y-a.y)+nz*(d.z-a.z) != 0)
            throw std::runtime_error("Cube face is degenerate, nonplanar or points inward.");
        normals.emplace(static_cast<int>(nx/10000), static_cast<int>(ny/10000), static_cast<int>(nz/10000));
    }
    if (corners.size() != 8 || normals.size() != 6) throw std::runtime_error("Cube faces are missing.");
    for (const auto &[point, count] : corners) {
        (void)point;
        if (count != 3) throw std::runtime_error("Cube corner must meet three faces.");
    }
    std::cout << "Make Group: six outward planar faces, eight corners, 100 cm bounds passed.\n";
    return 0;
} catch (const std::exception &error) {
    std::cerr << error.what() << '\n'; return 1;
}
