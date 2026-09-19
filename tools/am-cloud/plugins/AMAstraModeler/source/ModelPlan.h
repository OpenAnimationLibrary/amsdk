#pragma once

#include "Json.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace amastra {

constexpr std::size_t MaxResponseBytes = 8 * 1024 * 1024;
constexpr std::size_t MaxRequestBytes = 8 * 1024 * 1024;
constexpr std::size_t MaxPromptBytes = 16000;
constexpr std::size_t MaxReferenceImageBytes = 4 * 1024 * 1024;
constexpr std::size_t MaxReferenceImageDimension = 65535;
constexpr std::size_t MaxReferenceImagePixels = 64 * 1024 * 1024;
constexpr std::size_t MaxMaterials = 16;
constexpr std::size_t MaxComponents = 100;
constexpr std::size_t HardMaxPatches = 20000;
constexpr std::size_t HardMaxControlPointRecords = 100000;

struct Error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct ReferenceImageMetadata {
    std::string fileName;
    std::string mimeType;
    std::size_t byteSize = 0;
    std::size_t width = 0;
    std::size_t height = 0;
};

struct ReferenceImage {
    ReferenceImageMetadata metadata;
    std::string base64;
};

struct Vec3 {
    double x = 0;
    double y = 0;
    double z = 0;
    Vec3 operator+(Vec3 other) const { return {x + other.x, y + other.y, z + other.z}; }
    Vec3 operator-(Vec3 other) const { return {x - other.x, y - other.y, z - other.z}; }
    Vec3 operator*(double value) const { return {x * value, y * value, z * value}; }
    bool operator==(const Vec3&) const = default;
};

double Dot(Vec3 a, Vec3 b);
Vec3 Cross(Vec3 a, Vec3 b);
double Length(Vec3 value);
Vec3 Unit(Vec3 value);
bool Finite(Vec3 value);

struct Material {
    enum class Finish { Matte, Satin, Glossy, Metallic, Glass };
    std::string name;
    Vec3 color;
    Finish finish = Finish::Matte;
    double opacity = 1;
};

struct SurfaceFractions {
    double specularSize = 0;
    double specularIntensity = 0;
    double reflectivity = 0;
    double transparency = 0;
    double refraction = 1;
};

struct Component {
    enum class Kind { Box, Ellipsoid, Torus, Tube, Lathe, PatchGrid };
    std::string name;
    Kind kind = Kind::Box;
    std::size_t material = 0;
    bool smooth = false;
    Vec3 center{};
    Vec3 rotation{};
    Vec3 size{};
    Vec3 radii{};
    Vec3 start{};
    Vec3 end{};
    double majorRadius = 0;
    double minorRadius = 0;
    double radiusStart = 0;
    double radiusEnd = 0;
    std::size_t detail = 0;
    std::size_t majorSegments = 0;
    std::size_t minorSegments = 0;
    std::size_t sides = 0;
    std::size_t segments = 0;
    std::size_t rows = 0;
    std::size_t columns = 0;
    std::vector<std::array<double, 2>> profile;
    std::vector<Vec3> points;
};

struct ModelPlan {
    std::string name;
    std::string description;
    std::vector<Material> materials;
    std::vector<Component> components;
};

struct Quad {
    std::array<std::uint32_t, 4> vertex{};
};

struct SplinePath {
    std::vector<std::uint32_t> vertex;
    bool closed = false;
};

struct SplinePlan {
    std::vector<SplinePath> paths;
    std::vector<std::size_t> occurrences;
    std::size_t edges = 0;
};

struct MeshPart {
    std::string name;
    std::size_t material = 0;
    bool smooth = false;
    std::vector<Vec3> vertices;
    std::vector<Quad> faces;
    SplinePlan splines;
};

struct PreparedPlan {
    ModelPlan source;
    std::vector<MeshPart> parts;
    std::size_t patches = 0;
    std::size_t vertices = 0;
    std::size_t splinePaths = 0;
    std::size_t controlPointRecords = 0;
};

struct ApiResult {
    std::string responseId;
    std::string requestId;
    std::string arguments;
    std::size_t inputTokens = 0;
    std::size_t outputTokens = 0;
};

std::string SafeName(std::string_view utf8, std::string_view fallback, std::size_t maximum = 64);
ModelPlan ParseModelPlan(const amjson::Value& root);
PreparedPlan PreparePlan(ModelPlan plan, std::size_t requestedPatchLimit,
                         std::size_t requestedComponentLimit = MaxComponents);
SplinePlan RouteSplines(const MeshPart& part);

amjson::Value BuildToolSchema(std::size_t componentLimit);
std::string Base64Encode(const std::vector<unsigned char>& bytes);
ReferenceImage PrepareReferenceImage(std::string fileName,
                                     const std::vector<unsigned char>& bytes);
std::string BuildRequestJson(std::string_view prompt, std::size_t componentLimit,
                             std::size_t patchLimit, const ReferenceImage* image = nullptr);
ApiResult ExtractApiResult(std::string_view responseJson, std::string requestId = {});
std::string SanitizeDiagnostic(std::string_view detail);

std::string KindName(Component::Kind kind);
std::string FinishName(Material::Finish finish);
SurfaceFractions SurfaceForMaterial(const Material& material);

} // namespace amastra
