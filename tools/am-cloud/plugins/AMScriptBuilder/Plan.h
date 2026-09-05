#pragma once
// A deliberately small JSON dialect for an offline, new-model-only plan.
// No SDK headers, execution, file paths or host pointers in this layer.
#include <array>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace amscript {
constexpr std::size_t MaxBytes = 262144;
constexpr std::size_t MaxPoints = 1024;
constexpr std::size_t MaxSplines = 128;
constexpr std::size_t MaxPerSpline = 256;
constexpr std::size_t MaxOccurrences = 2048;
struct Plan {
    std::string name;
    std::vector<std::array<float, 3>> points;
    std::vector<std::vector<std::size_t>> splines;
    std::size_t occurrences = 0;
    std::size_t attachments = 0;
};

class Parser {
    std::string_view source;
    std::size_t cursor = 0;
    [[noreturn]] void fail(const char* reason) const {
        throw std::runtime_error(std::string(reason) + " at byte " + std::to_string(cursor));
    }
    void whitespace() {
        while (cursor < source.size() && (source[cursor] == ' ' || source[cursor] == '\t' ||
               source[cursor] == '\r' || source[cursor] == '\n')) ++cursor;
    }
    bool take(char c) {
        whitespace();
        if (cursor < source.size() && source[cursor] == c) { ++cursor; return true; }
        return false;
    }
    void expect(char c) { if (!take(c)) fail("Unexpected JSON token"); }
    std::string text() {
        expect('"');
        const auto begin = cursor;
        while (cursor < source.size() && source[cursor] != '"') {
            const auto c = static_cast<unsigned char>(source[cursor++]);
            if (c < 32 || c > 126 || c == '\\') fail("Only unescaped printable ASCII strings are supported in v1");
            if (cursor - begin > 64) fail("String exceeds 64 bytes");
        }
        if (cursor == source.size()) fail("Unclosed string");
        const std::string value(source.substr(begin, cursor - begin));
        ++cursor;
        return value;
    }
    std::string_view number() {
        whitespace();
        const auto begin = cursor;
        if (cursor < source.size() && source[cursor] == '-') ++cursor;
        if (cursor == source.size()) fail("Missing number");
        if (source[cursor] == '0') ++cursor;
        else {
            if (source[cursor] < '1' || source[cursor] > '9') fail("Invalid number");
            while (cursor < source.size() && source[cursor] >= '0' && source[cursor] <= '9') ++cursor;
        }
        if (cursor < source.size() && source[cursor] == '.') {
            ++cursor; const auto digits = cursor;
            while (cursor < source.size() && source[cursor] >= '0' && source[cursor] <= '9') ++cursor;
            if (digits == cursor) fail("Missing fractional digits");
        }
        if (cursor < source.size() && (source[cursor] == 'e' || source[cursor] == 'E')) {
            ++cursor;
            if (cursor < source.size() && (source[cursor] == '+' || source[cursor] == '-')) ++cursor;
            const auto digits = cursor;
            while (cursor < source.size() && source[cursor] >= '0' && source[cursor] <= '9') ++cursor;
            if (digits == cursor) fail("Missing exponent digits");
        }
        if (cursor - begin > 64) fail("Number token too long");
        return source.substr(begin, cursor - begin);
    }
    std::size_t integer() {
        const auto token = number();
        if (token.empty() || token.front() == '-' || token.find_first_of(".eE") != token.npos)
            fail("Expected unsigned integer");
        std::size_t value = 0;
        auto result = std::from_chars(token.data(), token.data() + token.size(), value);
        if (result.ec != std::errc{} || result.ptr != token.data() + token.size()) fail("Integer out of range");
        return value;
    }
    float coordinate() {
        const auto token = number();
        double value = 0;
        auto result = std::from_chars(token.data(), token.data() + token.size(), value);
        if (result.ec != std::errc{} || result.ptr != token.data() + token.size() ||
            !std::isfinite(value) || std::abs(value) > 100000.0)
            fail("Coordinate must be finite and within +/-100000 model units");
        const auto converted = static_cast<float>(value);
        if (value != 0 && converted == 0) fail("Coordinate underflows SDK float range");
        return converted;
    }
    void points(Plan& plan) {
        expect('[');
        if (take(']')) return;
        do {
            if (plan.points.size() >= MaxPoints) fail("Too many logical points");
            expect('[');
            std::array<float, 3> point{};
            for (unsigned i = 0; i < 3; ++i) { if (i) expect(','); point[i] = coordinate(); }
            expect(']'); plan.points.push_back(point);
        } while (take(','));
        expect(']');
    }
    void splines(Plan& plan) {
        expect('[');
        if (take(']')) return;
        do {
            if (plan.splines.size() >= MaxSplines) fail("Too many splines");
            expect('[');
            std::vector<std::size_t> spline;
            if (!take(']')) {
                do {
                    if (spline.size() >= MaxPerSpline || plan.occurrences >= MaxOccurrences)
                        fail("Too many spline control points");
                    spline.push_back(integer()); ++plan.occurrences;
                } while (take(','));
                expect(']');
            }
            plan.splines.push_back(std::move(spline));
        } while (take(','));
        expect(']');
    }
public:
    explicit Parser(std::string_view value) : source(value) {
        if (source.empty() || source.size() > MaxBytes) fail("Empty or oversized plan");
    }
    Plan parse() {
        Plan plan;
        unsigned seen = 0;
        expect('{');
        do {
            const auto key = text(); expect(':');
            unsigned flag = 0;
            if (key == "am_plan") flag = 1;
            else if (key == "name") flag = 2;
            else if (key == "points") flag = 4;
            else if (key == "splines") flag = 8;
            else fail("Unknown plan field");
            if (seen & flag) fail("Duplicate plan field");
            seen |= flag;
            if (flag == 1) { if (integer() != 1) fail("Unsupported plan version"); }
            else if (flag == 2) plan.name = text();
            else if (flag == 4) points(plan);
            else splines(plan);
        } while (take(','));
        expect('}'); whitespace();
        if (cursor != source.size()) fail("Trailing data");
        if (seen != 15) fail("Missing plan field");
        if (plan.name.empty() || plan.name.size() > 64 ||
            plan.name.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 _.-") != std::string::npos ||
            plan.name.front() == ' ' || plan.name.back() == ' ')
            fail("Model name must be 1-64 ASCII letters/digits/spaces/underscore/dot/hyphen, without edge spaces");
        if (plan.points.size() < 2 || plan.splines.empty()) fail("At least two points and one spline required");
        std::vector<unsigned> uses(plan.points.size(), 0);
        std::set<std::array<std::size_t, 2>> edges;
        for (const auto& spline : plan.splines) {
            if (spline.size() < 2) fail("Each open spline requires two or more points");
            std::set<std::size_t> unique;
            for (std::size_t i = 0; i < spline.size(); ++i) {
                const auto id = spline[i];
                if (id >= plan.points.size()) fail("Point index outside points array");
                if (!unique.insert(id).second) fail("Repeated index in spline; loops are not supported in v1");
                if (++uses[id] > 2) fail("At most two spline occurrences may share a logical point in v1");
                if (i) {
                    const auto previous = spline[i - 1];
                    if (plan.points[id] == plan.points[previous]) fail("Zero-length edge after SDK float conversion");
                    const std::array<std::size_t, 2> edge = id < previous ?
                        std::array<std::size_t, 2>{id, previous} : std::array<std::size_t, 2>{previous, id};
                    if (!edges.insert(edge).second) fail("Duplicate logical edge");
                }
            }
        }
        for (auto count : uses) {
            if (!count) fail("Unused logical point");
            if (count == 2) ++plan.attachments;
        }
        return plan;
    }
};
inline Plan Parse(std::string_view source) { return Parser(source).parse(); }
} // namespace amscript
