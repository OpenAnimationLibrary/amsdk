#include "ModelPlan.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <tuple>

namespace amastra {
namespace {

constexpr double Pi = 3.1415926535897932384626433832795;

using Object = amjson::Value::Object;
using Array = amjson::Value::Array;

void Fields(const amjson::Value& value, std::initializer_list<std::string_view> allowed,
            std::string_view context) {
    const auto& object = value.as_object();
    std::set<std::string_view> names(allowed.begin(), allowed.end());
    for (const auto& item : object) {
        if (!names.erase(item.first)) throw Error(std::string(context) + " has an unknown or duplicate field: " + item.first);
    }
    if (!names.empty()) throw Error(std::string(context) + " is missing field: " + std::string(*names.begin()));
}

double Number(const amjson::Value& value, double minimum, double maximum, std::string_view field) {
    const double result = value.as_number();
    if (!std::isfinite(result) || result < minimum || result > maximum)
        throw Error(std::string(field) + " is outside the supported range");
    return result;
}

std::size_t Integer(const amjson::Value& value, std::size_t minimum, std::size_t maximum,
                    std::string_view field) {
    const double number = value.as_number();
    if (!std::isfinite(number) || number < static_cast<double>(minimum) ||
        number > static_cast<double>(maximum) || std::floor(number) != number)
        throw Error(std::string(field) + " must be a supported integer");
    return static_cast<std::size_t>(number);
}

std::string Text(const amjson::Value& value, std::size_t maximum, std::string_view field) {
    const auto& result = value.as_string();
    if (result.empty() || result.size() > maximum) throw Error(std::string(field) + " is empty or too long");
    return result;
}

Vec3 Vector3(const amjson::Value& value, double minimum, double maximum, std::string_view field) {
    const auto& array = value.as_array();
    if (array.size() != 3) throw Error(std::string(field) + " must contain exactly three numbers");
    return {Number(array[0], minimum, maximum, field), Number(array[1], minimum, maximum, field),
            Number(array[2], minimum, maximum, field)};
}

std::size_t SizeValue(const amjson::Value& value, std::string_view field) {
    return Integer(value, 0, std::numeric_limits<std::uint32_t>::max(), field);
}

Material::Finish ParseFinish(std::string_view value) {
    if (value == "matte") return Material::Finish::Matte;
    if (value == "satin") return Material::Finish::Satin;
    if (value == "glossy") return Material::Finish::Glossy;
    if (value == "metallic") return Material::Finish::Metallic;
    if (value == "glass") return Material::Finish::Glass;
    throw Error("Unknown material finish");
}

Vec3 Rotate(Vec3 point, Vec3 degrees) {
    const double x = degrees.x * Pi / 180.0;
    const double y = degrees.y * Pi / 180.0;
    const double z = degrees.z * Pi / 180.0;
    const double cx = std::cos(x), sx = std::sin(x);
    const double cy = std::cos(y), sy = std::sin(y);
    const double cz = std::cos(z), sz = std::sin(z);
    point = {point.x, point.y * cx - point.z * sx, point.y * sx + point.z * cx};
    point = {point.x * cy + point.z * sy, point.y, -point.x * sy + point.z * cy};
    return {point.x * cz - point.y * sz, point.x * sz + point.y * cz, point.z};
}

void Transform(MeshPart& part, Vec3 center, Vec3 rotation) {
    for (auto& point : part.vertices) point = Rotate(point, rotation) + center;
}

void Reverse(Quad& face) { std::swap(face.vertex[1], face.vertex[3]); }

Vec3 FaceNormal(const MeshPart& part, const Quad& face) {
    const Vec3 a = part.vertices[face.vertex[0]];
    const Vec3 b = part.vertices[face.vertex[1]];
    const Vec3 c = part.vertices[face.vertex[2]];
    const Vec3 d = part.vertices[face.vertex[3]];
    return Cross(b - a, c - a) + Cross(c - a, d - a);
}

Vec3 FaceCenter(const MeshPart& part, const Quad& face) {
    Vec3 result{};
    for (auto index : face.vertex) result = result + part.vertices[index];
    return result * .25;
}

void OrientFromOrigin(MeshPart& part) {
    for (auto& face : part.faces) if (Dot(FaceNormal(part, face), FaceCenter(part, face)) < 0) Reverse(face);
}

MeshPart Box(const Component& component) {
    MeshPart part;
    part.name = component.name;
    part.material = component.material;
    part.smooth = false;
    const Vec3 half = component.size * .5;
    part.vertices = {{-half.x,-half.y,-half.z},{half.x,-half.y,-half.z},{half.x,half.y,-half.z},{-half.x,half.y,-half.z},
                     {-half.x,-half.y,half.z},{half.x,-half.y,half.z},{half.x,half.y,half.z},{-half.x,half.y,half.z}};
    part.faces = {{{{0,1,2,3}}},{{{4,5,6,7}}},{{{0,4,5,1}}},{{{1,5,6,2}}},{{{2,6,7,3}}},{{{3,7,4,0}}}};
    OrientFromOrigin(part);
    Transform(part, component.center, component.rotation);
    return part;
}

MeshPart Ellipsoid(const Component& component) {
    MeshPart part;
    part.name = component.name;
    part.material = component.material;
    part.smooth = true;
    const int resolution = static_cast<int>(component.detail * 2);
    std::map<std::array<int,3>, std::uint32_t> indices;
    const auto index = [&](std::array<int,3> key) -> std::uint32_t {
        const auto found = indices.find(key);
        if (found != indices.end()) return found->second;
        Vec3 value{static_cast<double>(key[0]), static_cast<double>(key[1]), static_cast<double>(key[2])};
        value = Unit(value);
        value = {value.x * component.radii.x, value.y * component.radii.y, value.z * component.radii.z};
        const auto result = static_cast<std::uint32_t>(part.vertices.size());
        part.vertices.push_back(value);
        indices.emplace(key, result);
        return result;
    };
    for (int axis = 0; axis < 3; ++axis) for (int sign : {-1, 1}) {
        for (int row = 0; row < resolution; ++row) for (int column = 0; column < resolution; ++column) {
            const int a0 = -resolution + row * 2;
            const int a1 = a0 + 2;
            const int b0 = -resolution + column * 2;
            const int b1 = b0 + 2;
            const auto key = [&](int a, int b) {
                std::array<int,3> result{};
                result[axis] = sign * resolution;
                result[(axis + 1) % 3] = a;
                result[(axis + 2) % 3] = b;
                return result;
            };
            part.faces.push_back({{index(key(a0,b0)), index(key(a1,b0)), index(key(a1,b1)), index(key(a0,b1))}});
        }
    }
    OrientFromOrigin(part);
    Transform(part, component.center, component.rotation);
    return part;
}

MeshPart Torus(const Component& component) {
    MeshPart part;
    part.name = component.name;
    part.material = component.material;
    part.smooth = true;
    const auto major = component.majorSegments;
    const auto minor = component.minorSegments;
    part.vertices.reserve(major * minor);
    for (std::size_t i = 0; i < major; ++i) {
        const double u = 2 * Pi * static_cast<double>(i) / static_cast<double>(major);
        for (std::size_t j = 0; j < minor; ++j) {
            const double v = 2 * Pi * static_cast<double>(j) / static_cast<double>(minor);
            const double radial = component.majorRadius + component.minorRadius * std::cos(v);
            part.vertices.push_back({radial * std::cos(u), component.minorRadius * std::sin(v), radial * std::sin(u)});
        }
    }
    const auto at = [minor](std::size_t i, std::size_t j) {
        return static_cast<std::uint32_t>(i * minor + j);
    };
    for (std::size_t i = 0; i < major; ++i) for (std::size_t j = 0; j < minor; ++j) {
        const auto nextI = (i + 1) % major, nextJ = (j + 1) % minor;
        Quad face{{at(i,j), at(nextI,j), at(nextI,nextJ), at(i,nextJ)}};
        const Vec3 center = FaceCenter(part, face);
        const double angle = std::atan2(center.z, center.x);
        const Vec3 ring{component.majorRadius * std::cos(angle), 0, component.majorRadius * std::sin(angle)};
        if (Dot(FaceNormal(part, face), center - ring) < 0) Reverse(face);
        part.faces.push_back(face);
    }
    Transform(part, component.center, component.rotation);
    return part;
}

MeshPart Tube(const Component& component) {
    MeshPart part;
    part.name = component.name;
    part.material = component.material;
    part.smooth = true;
    const Vec3 direction = component.end - component.start;
    const Vec3 axis = Unit(direction);
    const Vec3 helper = std::abs(axis.y) < .9 ? Vec3{0,1,0} : Vec3{1,0,0};
    const Vec3 one = Unit(Cross(axis, helper));
    const Vec3 two = Unit(Cross(axis, one));
    part.vertices.reserve(component.sides * 2);
    for (std::size_t ring = 0; ring < 2; ++ring) {
        const Vec3 center = ring ? component.end : component.start;
        const double radius = ring ? component.radiusEnd : component.radiusStart;
        for (std::size_t i = 0; i < component.sides; ++i) {
            const double angle = 2 * Pi * static_cast<double>(i) / static_cast<double>(component.sides);
            part.vertices.push_back(center + one * (radius * std::cos(angle)) + two * (radius * std::sin(angle)));
        }
    }
    for (std::size_t i = 0; i < component.sides; ++i) {
        const auto next = (i + 1) % component.sides;
        Quad face{{static_cast<std::uint32_t>(i), static_cast<std::uint32_t>(next),
                   static_cast<std::uint32_t>(component.sides + next),
                   static_cast<std::uint32_t>(component.sides + i)}};
        const Vec3 center = FaceCenter(part, face);
        const double along = Dot(center - component.start, axis);
        const Vec3 onAxis = component.start + axis * along;
        if (Dot(FaceNormal(part, face), center - onAxis) < 0) Reverse(face);
        part.faces.push_back(face);
    }
    return part;
}

MeshPart Lathe(const Component& component) {
    MeshPart part;
    part.name = component.name;
    part.material = component.material;
    part.smooth = true;
    part.vertices.reserve(component.profile.size() * component.segments);
    for (const auto& point : component.profile) {
        for (std::size_t i = 0; i < component.segments; ++i) {
            const double angle = 2 * Pi * static_cast<double>(i) / static_cast<double>(component.segments);
            part.vertices.push_back({point[0] * std::cos(angle), point[1], point[0] * std::sin(angle)});
        }
    }
    const auto at = [&](std::size_t row, std::size_t column) {
        return static_cast<std::uint32_t>(row * component.segments + column);
    };
    for (std::size_t row = 0; row + 1 < component.profile.size(); ++row) {
        for (std::size_t column = 0; column < component.segments; ++column) {
            const auto next = (column + 1) % component.segments;
            Quad face{{at(row,column), at(row + 1,column), at(row + 1,next), at(row,next)}};
            const Vec3 center = FaceCenter(part, face);
            if (Dot(FaceNormal(part, face), Vec3{center.x,0,center.z}) < 0) Reverse(face);
            part.faces.push_back(face);
        }
    }
    Transform(part, component.center, component.rotation);
    return part;
}

MeshPart PatchGrid(const Component& component) {
    MeshPart part;
    part.name = component.name;
    part.material = component.material;
    part.smooth = component.smooth;
    part.vertices = component.points;
    const auto at = [&](std::size_t row, std::size_t column) {
        return static_cast<std::uint32_t>(row * component.columns + column);
    };
    for (std::size_t row = 0; row + 1 < component.rows; ++row)
        for (std::size_t column = 0; column + 1 < component.columns; ++column)
            part.faces.push_back({{at(row,column), at(row + 1,column), at(row + 1,column + 1), at(row,column + 1)}});
    return part;
}

void ValidateMesh(const MeshPart& part) {
    if (part.vertices.empty() || part.faces.empty()) throw Error("Component '" + part.name + "' produced no surface");
    std::vector<bool> used(part.vertices.size());
    std::set<std::array<std::uint32_t,4>> faces;
    std::map<std::pair<std::uint32_t,std::uint32_t>, unsigned> edges;
    for (const auto& face : part.faces) {
        auto key = face.vertex;
        std::sort(key.begin(), key.end());
        if (std::adjacent_find(key.begin(), key.end()) != key.end()) throw Error("Component '" + part.name + "' has a repeated quad corner");
        if (!faces.insert(key).second) throw Error("Component '" + part.name + "' has a duplicate quad");
        for (std::size_t i = 0; i < 4; ++i) {
            const auto a = face.vertex[i], b = face.vertex[(i + 1) % 4];
            if (a >= part.vertices.size() || b >= part.vertices.size()) throw Error("Component '" + part.name + "' has an invalid point index");
            used[a] = true;
            if (++edges[std::minmax(a,b)] > 2) throw Error("Component '" + part.name + "' has a non-manifold edge");
        }
        if (Length(FaceNormal(part, face)) < 1e-8) throw Error("Component '" + part.name + "' has a zero-area patch");
    }
    for (std::size_t i = 0; i < part.vertices.size(); ++i) {
        const auto point = part.vertices[i];
        if (!Finite(point) || std::abs(point.x) > 100000 || std::abs(point.y) > 100000 || std::abs(point.z) > 100000)
            throw Error("Component '" + part.name + "' exceeds the finite +/-100000 cm coordinate limit");
        if (!used[i]) throw Error("Component '" + part.name + "' has an unused point");
        for (std::size_t j = 0; j < i; ++j)
            if (Length(point - part.vertices[j]) < 1e-7)
                throw Error("Component '" + part.name + "' collapses two points to the same position");
    }
}

MeshPart BuildMesh(const Component& component) {
    switch (component.kind) {
    case Component::Kind::Box: return Box(component);
    case Component::Kind::Ellipsoid: return Ellipsoid(component);
    case Component::Kind::Torus: return Torus(component);
    case Component::Kind::Tube: return Tube(component);
    case Component::Kind::Lathe: return Lathe(component);
    case Component::Kind::PatchGrid: return PatchGrid(component);
    }
    throw Error("Unknown component kind");
}

amjson::Value Type(std::string name) { return amjson::Value::object({{"type", std::move(name)}}); }

amjson::Value NumberSchema(double minimum, double maximum) {
    return amjson::Value::object({{"type","number"},{"minimum",minimum},{"maximum",maximum}});
}

amjson::Value IntegerSchema(std::size_t minimum, std::size_t maximum) {
    return amjson::Value::object({{"type","integer"},{"minimum",minimum},{"maximum",maximum}});
}

amjson::Value StringSchema(std::string description) {
    return amjson::Value::object({{"type","string"},{"description",std::move(description)}});
}

amjson::Value EnumSchema(std::initializer_list<const char*> values) {
    Array list;
    for (const char* value : values) list.emplace_back(value);
    return amjson::Value::object({{"type","string"},{"enum",std::move(list)}});
}

amjson::Value VectorSchema(double minimum, double maximum, std::string description) {
    return amjson::Value::object({{"type","array"},{"description",std::move(description)},
        {"items",NumberSchema(minimum,maximum)},{"minItems",3},{"maxItems",3}});
}

amjson::Value ObjectSchema(Object properties, std::vector<std::string> required) {
    Array names;
    for (auto& name : required) names.emplace_back(std::move(name));
    return amjson::Value::object({{"type","object"},{"properties",std::move(properties)},
                                 {"required",std::move(names)},{"additionalProperties",false}});
}

Object CommonProperties(const char* kind) {
    return {{"kind",amjson::Value::object({{"type","string"},{"enum",amjson::Value::array({kind})}})},
            {"name",StringSchema("Short ASCII component/group name")},
            {"material",IntegerSchema(0,MaxMaterials-1)}};
}

std::vector<std::string> CommonRequired() { return {"kind","name","material"}; }

amjson::Value ComponentSchema() {
    Array alternatives;
    {
        auto p = CommonProperties("box");
        p.emplace("center",VectorSchema(-100000,100000,"Center in centimeters"));
        p.emplace("rotation",VectorSchema(-3600,3600,"XYZ Euler degrees, applied X then Y then Z"));
        p.emplace("size",VectorSchema(.01,100000,"Positive X/Y/Z size in centimeters"));
        auto r=CommonRequired();r.insert(r.end(),{"center","rotation","size"});
        alternatives.push_back(ObjectSchema(std::move(p),std::move(r)));
    }
    {
        auto p = CommonProperties("ellipsoid");
        p.emplace("center",VectorSchema(-100000,100000,"Center in centimeters"));
        p.emplace("rotation",VectorSchema(-3600,3600,"XYZ Euler degrees"));
        p.emplace("radii",VectorSchema(.01,50000,"Positive X/Y/Z radii in centimeters"));
        p.emplace("detail",IntegerSchema(1,4));
        auto r=CommonRequired();r.insert(r.end(),{"center","rotation","radii","detail"});
        alternatives.push_back(ObjectSchema(std::move(p),std::move(r)));
    }
    {
        auto p = CommonProperties("torus");
        p.emplace("center",VectorSchema(-100000,100000,"Center in centimeters"));
        p.emplace("rotation",VectorSchema(-3600,3600,"XYZ Euler degrees"));
        p.emplace("major_radius",NumberSchema(.02,50000));
        p.emplace("minor_radius",NumberSchema(.01,25000));
        p.emplace("major_segments",IntegerSchema(4,32));
        p.emplace("minor_segments",IntegerSchema(4,16));
        auto r=CommonRequired();r.insert(r.end(),{"center","rotation","major_radius","minor_radius","major_segments","minor_segments"});
        alternatives.push_back(ObjectSchema(std::move(p),std::move(r)));
    }
    {
        auto p = CommonProperties("tube");
        p.emplace("start",VectorSchema(-100000,100000,"Start point in centimeters"));
        p.emplace("end",VectorSchema(-100000,100000,"End point in centimeters"));
        p.emplace("radius_start",NumberSchema(.01,25000));
        p.emplace("radius_end",NumberSchema(.01,25000));
        p.emplace("sides",IntegerSchema(4,24));
        auto r=CommonRequired();r.insert(r.end(),{"start","end","radius_start","radius_end","sides"});
        alternatives.push_back(ObjectSchema(std::move(p),std::move(r)));
    }
    {
        auto p = CommonProperties("lathe");
        p.emplace("center",VectorSchema(-100000,100000,"Center in centimeters"));
        p.emplace("rotation",VectorSchema(-3600,3600,"XYZ Euler degrees"));
        p.emplace("segments",IntegerSchema(4,32));
        p.emplace("profile",amjson::Value::object({{"type","array"},{"description","Bottom-to-top [radius,height] pairs; radii stay positive"},
            {"items",amjson::Value::object({{"type","array"},{"items",NumberSchema(-100000,100000)},{"minItems",2},{"maxItems",2}})},
            {"minItems",2},{"maxItems",16}}));
        auto r=CommonRequired();r.insert(r.end(),{"center","rotation","segments","profile"});
        alternatives.push_back(ObjectSchema(std::move(p),std::move(r)));
    }
    {
        auto p = CommonProperties("patch_grid");
        p.emplace("rows",IntegerSchema(2,12));
        p.emplace("columns",IntegerSchema(2,12));
        p.emplace("smooth",Type("boolean"));
        p.emplace("points",amjson::Value::object({{"type","array"},{"description","Row-major points; count must equal rows times columns"},
            {"items",VectorSchema(-100000,100000,"Point in centimeters")},{"minItems",4},{"maxItems",144}}));
        auto r=CommonRequired();r.insert(r.end(),{"rows","columns","smooth","points"});
        alternatives.push_back(ObjectSchema(std::move(p),std::move(r)));
    }
    return amjson::Value::object({{"anyOf",std::move(alternatives)}});
}

} // namespace

double Dot(Vec3 a, Vec3 b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
Vec3 Cross(Vec3 a, Vec3 b) { return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x}; }
double Length(Vec3 value) { return std::sqrt(Dot(value,value)); }
Vec3 Unit(Vec3 value) {
    const double length=Length(value);
    if (!std::isfinite(length) || length < 1e-12) throw Error("Cannot normalize a zero-length vector");
    return value*(1.0/length);
}
bool Finite(Vec3 value) { return std::isfinite(value.x)&&std::isfinite(value.y)&&std::isfinite(value.z); }

std::string SafeName(std::string_view utf8, std::string_view fallback, std::size_t maximum) {
    std::string result;
    result.reserve(std::min(utf8.size(), maximum));
    bool space = false;
    for (unsigned char c : utf8) {
        const bool allowed = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                             (c >= '0' && c <= '9') || c == '_' || c == '-' || c == '.';
        if (allowed) {
            if (space && !result.empty() && result.size() < maximum) result.push_back(' ');
            space = false;
            if (result.size() < maximum) result.push_back(static_cast<char>(c));
        } else if (c == ' ' || c == '\t' || c >= 0x80) {
            space = true;
        }
        if (result.size() >= maximum) break;
    }
    while (!result.empty() && (result.back() == ' ' || result.back() == '.')) result.pop_back();
    if (result.empty()) result.assign(fallback.substr(0, maximum));
    return result;
}

std::string KindName(Component::Kind kind) {
    switch (kind) {
    case Component::Kind::Box: return "box";
    case Component::Kind::Ellipsoid: return "ellipsoid";
    case Component::Kind::Torus: return "torus";
    case Component::Kind::Tube: return "tube";
    case Component::Kind::Lathe: return "lathe";
    case Component::Kind::PatchGrid: return "patch grid";
    }
    return "unknown";
}

std::string FinishName(Material::Finish finish) {
    switch (finish) {
    case Material::Finish::Matte: return "matte";
    case Material::Finish::Satin: return "satin";
    case Material::Finish::Glossy: return "glossy";
    case Material::Finish::Metallic: return "metallic";
    case Material::Finish::Glass: return "glass";
    }
    return "unknown";
}

SurfaceFractions SurfaceForMaterial(const Material& material) {
    SurfaceFractions surface;
    surface.transparency = 1 - material.opacity;
    switch (material.finish) {
    case Material::Finish::Matte:
        surface.specularSize = .12; surface.specularIntensity = .12; break;
    case Material::Finish::Satin:
        surface.specularSize = .32; surface.specularIntensity = .3; surface.reflectivity = .03; break;
    case Material::Finish::Glossy:
        surface.specularSize = .72; surface.specularIntensity = .68; surface.reflectivity = .09; break;
    case Material::Finish::Metallic:
        surface.specularSize = .58; surface.specularIntensity = .82; surface.reflectivity = .55; break;
    case Material::Finish::Glass:
        surface.specularSize = .9; surface.specularIntensity = .9; surface.reflectivity = .18;
        surface.refraction = 1.5; break;
    }
    return surface;
}

ModelPlan ParseModelPlan(const amjson::Value& root) {
    Fields(root,{"name","description","materials","components"},"model plan");
    ModelPlan plan;
    plan.name = SafeName(Text(root.at("name"),128,"name"),"Astra Model");
    plan.description = root.at("description").as_string();
    if (plan.description.size() > 2000) throw Error("description is too long");
    const auto& materials = root.at("materials").as_array();
    if (materials.empty() || materials.size() > MaxMaterials) throw Error("materials must contain 1-16 entries");
    std::set<std::string> materialNames;
    for (const auto& value : materials) {
        Fields(value,{"name","color","finish","opacity"},"material");
        Material material;
        material.name = SafeName(Text(value.at("name"),128,"material name"),"Material");
        material.color = Vector3(value.at("color"),0,1,"material color");
        material.finish = ParseFinish(value.at("finish").as_string());
        material.opacity = Number(value.at("opacity"),0,1,"material opacity");
        if (!materialNames.insert(material.name).second) throw Error("Material names must be unique");
        plan.materials.push_back(std::move(material));
    }
    const auto& components = root.at("components").as_array();
    if (components.empty() || components.size() > MaxComponents) throw Error("components must contain 1-32 entries");
    std::set<std::string> componentNames;
    for (const auto& value : components) {
        const auto kind = value.at("kind").as_string();
        Component component;
        component.name = SafeName(Text(value.at("name"),128,"component name"),"Part");
        component.material = Integer(value.at("material"),0,plan.materials.size()-1,"material index");
        if (!componentNames.insert(component.name).second) throw Error("Component names must be unique after A:M name cleanup");
        if (kind == "box") {
            Fields(value,{"kind","name","material","center","rotation","size"},"box");
            component.kind=Component::Kind::Box;component.center=Vector3(value.at("center"),-100000,100000,"center");
            component.rotation=Vector3(value.at("rotation"),-3600,3600,"rotation");
            component.size=Vector3(value.at("size"),.01,100000,"size");
        } else if (kind == "ellipsoid") {
            Fields(value,{"kind","name","material","center","rotation","radii","detail"},"ellipsoid");
            component.kind=Component::Kind::Ellipsoid;component.center=Vector3(value.at("center"),-100000,100000,"center");
            component.rotation=Vector3(value.at("rotation"),-3600,3600,"rotation");
            component.radii=Vector3(value.at("radii"),.01,50000,"radii");
            component.detail=Integer(value.at("detail"),1,4,"detail");component.smooth=true;
        } else if (kind == "torus") {
            Fields(value,{"kind","name","material","center","rotation","major_radius","minor_radius","major_segments","minor_segments"},"torus");
            component.kind=Component::Kind::Torus;component.center=Vector3(value.at("center"),-100000,100000,"center");
            component.rotation=Vector3(value.at("rotation"),-3600,3600,"rotation");
            component.majorRadius=Number(value.at("major_radius"),.02,50000,"major radius");
            component.minorRadius=Number(value.at("minor_radius"),.01,25000,"minor radius");
            if (component.majorRadius <= component.minorRadius*1.01) throw Error("Torus major radius must exceed its minor radius");
            component.majorSegments=Integer(value.at("major_segments"),4,32,"major segments");
            component.minorSegments=Integer(value.at("minor_segments"),4,16,"minor segments");component.smooth=true;
        } else if (kind == "tube") {
            Fields(value,{"kind","name","material","start","end","radius_start","radius_end","sides"},"tube");
            component.kind=Component::Kind::Tube;component.start=Vector3(value.at("start"),-100000,100000,"start");
            component.end=Vector3(value.at("end"),-100000,100000,"end");
            if (Length(component.end-component.start)<.01) throw Error("Tube start and end are too close");
            component.radiusStart=Number(value.at("radius_start"),.01,25000,"start radius");
            component.radiusEnd=Number(value.at("radius_end"),.01,25000,"end radius");
            component.sides=Integer(value.at("sides"),4,24,"tube sides");component.smooth=true;
        } else if (kind == "lathe") {
            Fields(value,{"kind","name","material","center","rotation","segments","profile"},"lathe");
            component.kind=Component::Kind::Lathe;component.center=Vector3(value.at("center"),-100000,100000,"center");
            component.rotation=Vector3(value.at("rotation"),-3600,3600,"rotation");
            component.segments=Integer(value.at("segments"),4,32,"lathe segments");
            const auto& profile=value.at("profile").as_array();
            if(profile.size()<2||profile.size()>16)throw Error("Lathe profile must contain 2-16 points");
            double previous=-std::numeric_limits<double>::infinity();
            for(const auto& point:profile){
                const auto& pair=point.as_array();
                if(pair.size()!=2)throw Error("Lathe profile points require [radius,height]");
                const double radius=Number(pair[0],.01,50000,"lathe radius");
                const double height=Number(pair[1],-100000,100000,"lathe height");
                if(height<=previous)throw Error("Lathe profile heights must increase from bottom to top");
                previous=height;
                component.profile.push_back({radius,height});
            }
            component.smooth=true;
        } else if (kind == "patch_grid") {
            Fields(value,{"kind","name","material","rows","columns","smooth","points"},"patch grid");
            component.kind=Component::Kind::PatchGrid;component.rows=Integer(value.at("rows"),2,12,"rows");
            component.columns=Integer(value.at("columns"),2,12,"columns");component.smooth=value.at("smooth").as_bool();
            const auto& points=value.at("points").as_array();if(points.size()!=component.rows*component.columns)throw Error("Patch-grid point count must equal rows times columns");
            for(const auto& point:points)component.points.push_back(Vector3(point,-100000,100000,"patch-grid point"));
        } else throw Error("Unknown component kind: "+kind);
        plan.components.push_back(std::move(component));
    }
    return plan;
}

SplinePlan RouteSplines(const MeshPart& part) {
    using Edge=std::pair<std::uint32_t,std::uint32_t>;
    const auto edge=[](std::uint32_t a,std::uint32_t b)->Edge{return std::minmax(a,b);};
    constexpr std::uint32_t end=UINT32_MAX;
    std::set<Edge> edges;
    std::vector<std::set<std::uint32_t>> neighbors(part.vertices.size());
    std::vector<std::set<Edge>> adjacent(part.vertices.size());
    for(const auto& face:part.faces)for(std::uint32_t k=0;k<4;++k){const auto a=face.vertex[k],b=face.vertex[(k+1)%4],c=face.vertex[(k+3)%4];
        edges.insert(edge(a,b));neighbors[a].insert(b);neighbors[b].insert(a);adjacent[a].insert(edge(b,c));}
    std::vector<std::map<std::uint32_t,std::uint32_t>> through(neighbors.size());
    for(std::uint32_t v=0;v<neighbors.size();++v){const auto& ns=neighbors[v];if(ns.empty())throw Error("Unused routing point");
        if(ns.size()>4)throw Error("Component '"+part.name+"' exceeds A:M's two-spline junction limit");
        for(auto n:ns)through[v][n]=end;
        if(ns.size()<3)continue;
        struct Pair{bool adjacent;double bend;std::uint32_t a,b;};std::vector<Pair> pairs;
        for(auto a:ns)for(auto b:ns)if(a<b)pairs.push_back({adjacent[v].count(edge(a,b))!=0,Dot(Unit(part.vertices[a]-part.vertices[v]),Unit(part.vertices[b]-part.vertices[v])),a,b});
        std::sort(pairs.begin(),pairs.end(),[](const Pair& a,const Pair& b){return std::tie(a.adjacent,a.bend,a.a,a.b)<std::tie(b.adjacent,b.bend,b.a,b.b);});
        std::set<std::uint32_t> paired;for(const auto& pair:pairs)if(!paired.count(pair.a)&&!paired.count(pair.b)){through[v][pair.a]=pair.b;through[v][pair.b]=pair.a;paired.insert(pair.a);paired.insert(pair.b);}}
    const auto emit=[&](){SplinePlan result;result.edges=edges.size();result.occurrences.resize(neighbors.size());std::set<Edge> remaining=edges;
        const auto walk=[&](std::uint32_t start,std::uint32_t next){SplinePath path;path.vertex.push_back(start);auto previous=start,current=next;
            while(true){if(!remaining.erase(edge(previous,current)))throw Error("Spline routing reused an edge");const auto following=through[current].at(previous);
                if(current==start&&following==next){path.closed=true;break;}path.vertex.push_back(current);if(following==end)break;previous=current;current=following;}
            if(!path.closed&&path.vertex.front()==path.vertex.back()){path.closed=true;path.vertex.pop_back();}
            if(path.vertex.size()<2||(path.closed&&path.vertex.size()<3))throw Error("Invalid spline path");
            for(auto v:path.vertex)++result.occurrences[v];
            result.paths.push_back(std::move(path));
        };
        for(std::uint32_t v=0;v<through.size();++v)for(const auto& pair:through[v])if(pair.second==end&&remaining.count(edge(v,pair.first)))walk(v,pair.first);
        while(!remaining.empty()){const auto first=*remaining.begin();walk(first.first,first.second);}return result;};
    const auto single=[&](const SplinePlan& routing){std::map<Edge,std::size_t> owner;
        for(std::size_t i=0;i<routing.paths.size();++i){const auto& path=routing.paths[i];for(std::size_t k=1;k<path.vertex.size();++k)owner.emplace(edge(path.vertex[k-1],path.vertex[k]),i);if(path.closed)owner.emplace(edge(path.vertex.back(),path.vertex.front()),i);}
        std::vector<std::size_t> bad;for(std::size_t i=0;i<part.faces.size();++i){const auto& face=part.faces[i];const auto first=owner.at(edge(face.vertex[0],face.vertex[1]));bool same=true;
            for(std::size_t k=1;k<4;++k)
                if(owner.at(edge(face.vertex[k],face.vertex[(k+1)%4]))!=first)same=false;
            if(same)bad.push_back(i);
        }
        return bad;
    };
    auto result=emit();auto bad=single(result);std::size_t work=0;
    while(!bad.empty()){bool repaired=false;const auto& face=part.faces[bad.front()];
        for(std::size_t a=0;a<4&&!repaired;++a)for(std::size_t b=a+1;b<4&&!repaired;++b){const auto u=face.vertex[a],v=face.vertex[b];if(neighbors[u].size()!=3||neighbors[v].size()!=3)continue;
            const auto beforeU=through[u],beforeV=through[v];for(auto endU:neighbors[u])for(auto endV:neighbors[v]){if(repaired||beforeU.at(endU)==end||beforeV.at(endV)==end)continue;
                if(work+edges.size()>20000000)throw Error("Spline routing repair limit exceeded");
                work+=edges.size();
                const auto pairOthers=[&](std::uint32_t at,std::uint32_t endpoint){
                    std::vector<std::uint32_t> pair;
                    for(auto n:neighbors[at]){
                        through[at][n]=end;
                        if(n!=endpoint)pair.push_back(n);
                    }
                    through[at][pair[0]]=pair[1];
                    through[at][pair[1]]=pair[0];
                };
                pairOthers(u,endU);pairOthers(v,endV);auto candidate=emit();auto next=single(candidate);if(next.size()<bad.size()){result=std::move(candidate);bad=std::move(next);repaired=true;}else{through[u]=beforeU;through[v]=beforeV;}}}
        if(!repaired)throw Error("Cannot route every quad across at least two splines in component '"+part.name+"'");}
    for(std::size_t v=0;v<neighbors.size();++v){const auto degree=neighbors[v].size();const auto expected=degree<3?degree:(degree+1)/2;
        if(result.occurrences[v]>2||(result.occurrences[v]!=expected&&!(degree==2&&result.occurrences[v]==1)))throw Error("Spline occurrence count does not match topology");}
    return result;
}

PreparedPlan PreparePlan(ModelPlan plan, std::size_t requestedPatchLimit) {
    if(requestedPatchLimit<1||requestedPatchLimit>HardMaxPatches)throw Error("Patch limit must be 1-20000");
    PreparedPlan prepared;prepared.source=std::move(plan);prepared.parts.reserve(prepared.source.components.size());
    for(const auto& component:prepared.source.components){MeshPart part=BuildMesh(component);ValidateMesh(part);
        if(prepared.patches+part.faces.size()>requestedPatchLimit)throw Error("Astra plan exceeds the requested patch limit before A:M is modified");
        part.splines=RouteSplines(part);std::size_t records=0;for(auto count:part.splines.occurrences)records+=count;
        if(prepared.controlPointRecords+records>HardMaxControlPointRecords)throw Error("Astra plan exceeds the control-point record limit");
        prepared.patches+=part.faces.size();prepared.vertices+=part.vertices.size();prepared.splinePaths+=part.splines.paths.size();prepared.controlPointRecords+=records;prepared.parts.push_back(std::move(part));}
    if(!prepared.patches)throw Error("Astra plan contains no patches");
    return prepared;
}

amjson::Value BuildToolSchema(std::size_t componentLimit) {
    componentLimit=std::clamp(componentLimit,std::size_t(1),MaxComponents);
    Object materialProperties{{"name",StringSchema("Short ASCII material name")},
        {"color",VectorSchema(0,1,"Linear-looking RGB values from 0 to 1")},
        {"finish",EnumSchema({"matte","satin","glossy","metallic","glass"})},
        {"opacity",NumberSchema(0,1)}};
    const auto material=ObjectSchema(std::move(materialProperties),{"name","color","finish","opacity"});
    Object planProperties{{"name",StringSchema("Short ASCII model name")},{"description",StringSchema("Concise construction summary")},
        {"materials",amjson::Value::object({{"type","array"},{"items",material},{"minItems",1},{"maxItems",MaxMaterials}})},
        {"components",amjson::Value::object({{"type","array"},{"items",ComponentSchema()},{"minItems",1},{"maxItems",componentLimit}})}};
    auto parameters=ObjectSchema(std::move(planProperties),{"name","description","materials","components"});
    return amjson::Value::object({{"type","function"},{"name","build_animation_master_model"},
        {"description","Create one bounded Animation:Master patch-model plan from procedural components."},
        {"parameters",std::move(parameters)},{"strict",true}});
}

std::string BuildRequestJson(std::string_view prompt,std::size_t componentLimit,std::size_t patchLimit) {
    if(prompt.empty()||prompt.size()>MaxPromptBytes)throw Error("Prompt must contain 1-16000 UTF-8 bytes");
    componentLimit=std::clamp(componentLimit,std::size_t(1),MaxComponents);patchLimit=std::clamp(patchLimit,std::size_t(1),HardMaxPatches);
    std::ostringstream instructions;
    instructions<<"Create a modest, editable, stylized patch model for Animation:Master. Call build_animation_master_model exactly once. "
        <<"All coordinates and dimensions are centimeters. Y is up. Use at most "<<componentLimit<<" components and keep the estimated total below "<<patchLimit<<" quad patches. "
        <<"Use boxes for hard forms, ellipsoids for rounded closed forms, tori for rings, open tapered tubes for limbs/rails, bottom-to-top positive-radius lathes for revolved forms, and patch grids for custom sheets. "
        <<"Tube and lathe ends are open: bury or cover them with another component when a closed silhouette matters. Components are separate A:M groups and are not welded to one another. "
        <<"Prefer low detail, meaningful unique ASCII names, a compact material palette, and deliberate overlap. Avoid zero thickness, coincident duplicate surfaces, and coplanar overlaps. "
        <<"For patch_grid, provide exactly rows*columns row-major points with consistent winding. Material indexes are zero-based. Follow the user's requested subject and proportions.";
    amjson::Value request=amjson::Value::object({{"model","gpt-6-astra"},{"instructions",instructions.str()},{"input",std::string(prompt)},
        {"reasoning",amjson::Value::object({{"effort","high"}})},{"max_output_tokens",20000},{"store",false},{"parallel_tool_calls",false},
        {"tools",amjson::Value::array({BuildToolSchema(componentLimit)})},
        {"tool_choice",amjson::Value::object({{"type","function"},{"name","build_animation_master_model"}})}});
    return amjson::dump(request);
}

ApiResult ExtractApiResult(std::string_view responseJson,std::string requestId) {
    if(responseJson.empty()||responseJson.size()>MaxResponseBytes)throw Error("OpenAI response is empty or exceeds 8 MiB");
    const auto root=amjson::parse(responseJson);
    if(const auto* error=root.find("error");error&&error->is_object()){
        if(const auto* message=error->find("message");message&&message->is_string())throw Error("OpenAI API: "+message->as_string());
        throw Error("OpenAI API returned an error");}
    ApiResult result;result.requestId=std::move(requestId);
    if(const auto* id=root.find("id");id&&id->is_string())result.responseId=id->as_string();
    if(const auto* status=root.find("status");status&&status->is_string()&&status->as_string()!="completed")throw Error("OpenAI response did not complete: "+status->as_string());
    const auto& output=root.at("output").as_array();std::size_t calls=0;
    for(const auto& item:output){if(!item.is_object())continue;const auto* type=item.find("type");if(!type||!type->is_string()||type->as_string()!="function_call")continue;
        const auto& name=item.at("name").as_string();if(name!="build_animation_master_model")continue;++calls;result.arguments=item.at("arguments").as_string();}
    if(calls!=1||result.arguments.empty())throw Error("Astra did not return exactly one required model-plan tool call");
    if(result.arguments.size()>1024*1024)throw Error("Astra model plan exceeds 1 MiB");
    if(const auto* usage=root.find("usage");usage&&usage->is_object()){
        if(const auto* input=usage->find("input_tokens");input&&input->is_number())result.inputTokens=SizeValue(*input,"input token count");
        if(const auto* outputTokens=usage->find("output_tokens");outputTokens&&outputTokens->is_number())result.outputTokens=SizeValue(*outputTokens,"output token count");}
    return result;
}

} // namespace amastra
