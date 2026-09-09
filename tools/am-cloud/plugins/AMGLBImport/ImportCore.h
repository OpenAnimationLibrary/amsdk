#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace amglb {
constexpr size_t MaxFileBytes = 32 * 1024 * 1024;
constexpr size_t MaxInputTriangles = 50000;
constexpr size_t MaxOutputQuads = 100000;
constexpr size_t MaxVertices = 250000;
constexpr size_t MaxParts = 256;

struct Error : std::runtime_error { using std::runtime_error::runtime_error; };
struct Vec3 {
    double x = 0, y = 0, z = 0;
    Vec3 operator+(Vec3 b) const { return {x+b.x,y+b.y,z+b.z}; }
    Vec3 operator-(Vec3 b) const { return {x-b.x,y-b.y,z-b.z}; }
    Vec3 operator*(double s) const { return {x*s,y*s,z*s}; }
};
double Dot(Vec3 a, Vec3 b);
Vec3 Cross(Vec3 a, Vec3 b);
double Length(Vec3 a);
Vec3 Unit(Vec3 a);
bool Finite(Vec3 a);

struct Material {
    std::string name;
    std::array<double,4> color{.8,.8,.8,1};
    double metallic = 0, roughness = .5;
};
struct Face {
    std::array<uint32_t,4> vertex{};
    uint32_t count = 3, material = 0;
    bool hasUV = false, hasNormals = false;
    std::array<std::array<double,2>,4> uv{};
    std::array<Vec3,4> normals{};
};
struct Part {
    std::string name;
    std::vector<Vec3> vertices;
    std::vector<Face> faces;
    // Empty for welded parts. Otherwise maps intentional seam copies to the
    // original vertex in this part; unrelated coincident points stay invalid.
    std::vector<uint32_t> seamSource;
};
struct SplinePath {
    std::vector<uint32_t> vertex;
    bool closed = false;
};
struct SplinePlan {
    std::vector<SplinePath> paths;
    std::vector<size_t> occurrences;
    size_t edges = 0, highValenceVertices = 0;
};
struct MaterialGroup {
    uint32_t material = 0;
    std::vector<uint32_t> vertices;
    std::vector<size_t> faces;
};
struct Plan {
    std::vector<Part> parts;
    std::vector<Material> materials;
    std::vector<std::string> notes;
    size_t inputTriangles = 0, pairedQuads = 0, curvedPairs = 0, subdividedComponents = 0;
    size_t outputQuads = 0, vertices = 0;
    size_t seamedParts = 0, seamEdges = 0, seamCopies = 0;
    Vec3 minimum{}, maximum{};
};
// Parsing and conversion never call the A:M SDK or open external GLB resources.
Plan ReadGLB(const std::vector<uint8_t>& bytes);
void ConvertToQuads(Plan& plan);
void ValidatePlan(Plan& plan);
// Apply native float precision before touching the host. Only explicitly
// recorded seam copies may coincide after scaling/mirroring.
std::vector<std::array<float,3>> PreparePositions(const Part& part,double scale,bool mirror);
// Each mesh edge occurs exactly once. Three-way junctions have two CP records:
// one through-spline and one ending spline, never three overlapping splines.
SplinePlan RouteSplines(const Part& part);
// A:M colors groups of CPs. Every quad enclosed by a group's CPs must have
// that group's material, including quads incidentally enclosed by shared CPs.
std::vector<MaterialGroup> GroupMaterials(const Part& part);
std::string SafeName(const char* utf8, const std::string& fallback);
}
