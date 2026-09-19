#pragma once

#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

namespace amjson {

struct Error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Value {
public:
    using Array = std::vector<Value>;
    using Object = std::map<std::string, Value, std::less<>>;

private:
    using Storage = std::variant<std::nullptr_t, bool, double, std::string, Array, Object>;
    Storage value_ = nullptr;

public:
    Value() = default;
    Value(std::nullptr_t) : value_(nullptr) {}
    Value(bool value) : value_(value) {}
    Value(double value) : value_(value) {}
    Value(int value) : value_(static_cast<double>(value)) {}
    Value(std::size_t value) : value_(static_cast<double>(value)) {}
    Value(std::string value) : value_(std::move(value)) {}
    Value(const char* value) : value_(std::string(value)) {}
    Value(Array value) : value_(std::move(value)) {}
    Value(Object value) : value_(std::move(value)) {}

    static Value array(std::initializer_list<Value> values) { return Array(values); }
    static Value object(std::initializer_list<std::pair<const std::string, Value>> values) {
        Object result;
        for (const auto& item : values) {
            if (!result.emplace(item.first, item.second).second) throw Error("Duplicate object key");
        }
        return result;
    }

    bool is_null() const { return std::holds_alternative<std::nullptr_t>(value_); }
    bool is_bool() const { return std::holds_alternative<bool>(value_); }
    bool is_number() const { return std::holds_alternative<double>(value_); }
    bool is_string() const { return std::holds_alternative<std::string>(value_); }
    bool is_array() const { return std::holds_alternative<Array>(value_); }
    bool is_object() const { return std::holds_alternative<Object>(value_); }

    bool as_bool() const {
        if (!is_bool()) throw Error("Expected a Boolean");
        return std::get<bool>(value_);
    }
    double as_number() const {
        if (!is_number()) throw Error("Expected a number");
        return std::get<double>(value_);
    }
    const std::string& as_string() const {
        if (!is_string()) throw Error("Expected a string");
        return std::get<std::string>(value_);
    }
    const Array& as_array() const {
        if (!is_array()) throw Error("Expected an array");
        return std::get<Array>(value_);
    }
    Array& as_array() {
        if (!is_array()) throw Error("Expected an array");
        return std::get<Array>(value_);
    }
    const Object& as_object() const {
        if (!is_object()) throw Error("Expected an object");
        return std::get<Object>(value_);
    }
    Object& as_object() {
        if (!is_object()) throw Error("Expected an object");
        return std::get<Object>(value_);
    }
    const Value& at(std::string_view key) const {
        const auto& object = as_object();
        const auto found = object.find(key);
        if (found == object.end()) throw Error("Missing object field: " + std::string(key));
        return found->second;
    }
    const Value* find(std::string_view key) const {
        if (!is_object()) return nullptr;
        const auto& object = std::get<Object>(value_);
        const auto found = object.find(key);
        return found == object.end() ? nullptr : &found->second;
    }
};

class Parser {
    std::string_view source_;
    std::size_t cursor_ = 0;
    std::size_t nodes_ = 0;
    std::size_t max_nodes_;
    std::size_t max_depth_;

    [[noreturn]] void fail(const std::string& message) const {
        throw Error(message + " at byte " + std::to_string(cursor_));
    }
    void whitespace() {
        while (cursor_ < source_.size()) {
            const char c = source_[cursor_];
            if (c != ' ' && c != '\t' && c != '\r' && c != '\n') break;
            ++cursor_;
        }
    }
    bool take(char wanted) {
        whitespace();
        if (cursor_ < source_.size() && source_[cursor_] == wanted) {
            ++cursor_;
            return true;
        }
        return false;
    }
    void expect(char wanted) {
        if (!take(wanted)) fail(std::string("Expected '") + wanted + "'");
    }
    static void utf8(std::string& output, std::uint32_t codepoint) {
        if (codepoint <= 0x7f) {
            output.push_back(static_cast<char>(codepoint));
        } else if (codepoint <= 0x7ff) {
            output.push_back(static_cast<char>(0xc0 | (codepoint >> 6)));
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
        } else if (codepoint <= 0xffff) {
            output.push_back(static_cast<char>(0xe0 | (codepoint >> 12)));
            output.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
        } else if (codepoint <= 0x10ffff) {
            output.push_back(static_cast<char>(0xf0 | (codepoint >> 18)));
            output.push_back(static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
            output.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3f)));
        } else {
            throw Error("Unicode code point is out of range");
        }
    }
    std::uint32_t hex4() {
        if (source_.size() - cursor_ < 4) fail("Short Unicode escape");
        std::uint32_t value = 0;
        for (unsigned i = 0; i < 4; ++i) {
            const char c = source_[cursor_++];
            value <<= 4;
            if (c >= '0' && c <= '9') value |= static_cast<std::uint32_t>(c - '0');
            else if (c >= 'a' && c <= 'f') value |= static_cast<std::uint32_t>(c - 'a' + 10);
            else if (c >= 'A' && c <= 'F') value |= static_cast<std::uint32_t>(c - 'A' + 10);
            else fail("Invalid Unicode escape");
        }
        return value;
    }
    std::string string() {
        whitespace();
        if (cursor_ >= source_.size() || source_[cursor_++] != '"') fail("Expected a string");
        std::string result;
        while (cursor_ < source_.size()) {
            const unsigned char c = static_cast<unsigned char>(source_[cursor_++]);
            if (c == '"') return result;
            if (c < 0x20) fail("Unescaped control character in string");
            if (c != '\\') {
                result.push_back(static_cast<char>(c));
                continue;
            }
            if (cursor_ >= source_.size()) fail("Short escape sequence");
            const char escaped = source_[cursor_++];
            switch (escaped) {
            case '"': result.push_back('"'); break;
            case '\\': result.push_back('\\'); break;
            case '/': result.push_back('/'); break;
            case 'b': result.push_back('\b'); break;
            case 'f': result.push_back('\f'); break;
            case 'n': result.push_back('\n'); break;
            case 'r': result.push_back('\r'); break;
            case 't': result.push_back('\t'); break;
            case 'u': {
                std::uint32_t codepoint = hex4();
                if (codepoint >= 0xd800 && codepoint <= 0xdbff) {
                    if (source_.size() - cursor_ < 6 || source_[cursor_] != '\\' || source_[cursor_ + 1] != 'u')
                        fail("Missing low surrogate");
                    cursor_ += 2;
                    const std::uint32_t low = hex4();
                    if (low < 0xdc00 || low > 0xdfff) fail("Invalid low surrogate");
                    codepoint = 0x10000 + ((codepoint - 0xd800) << 10) + (low - 0xdc00);
                } else if (codepoint >= 0xdc00 && codepoint <= 0xdfff) {
                    fail("Unexpected low surrogate");
                }
                utf8(result, codepoint);
                break;
            }
            default: fail("Unknown escape sequence");
            }
        }
        fail("Unclosed string");
    }
    Value number() {
        whitespace();
        const std::size_t begin = cursor_;
        if (cursor_ < source_.size() && source_[cursor_] == '-') ++cursor_;
        if (cursor_ >= source_.size()) fail("Missing number");
        if (source_[cursor_] == '0') {
            ++cursor_;
            if (cursor_ < source_.size() && source_[cursor_] >= '0' && source_[cursor_] <= '9')
                fail("Leading zero in number");
        } else {
            if (source_[cursor_] < '1' || source_[cursor_] > '9') fail("Invalid number");
            while (cursor_ < source_.size() && source_[cursor_] >= '0' && source_[cursor_] <= '9') ++cursor_;
        }
        if (cursor_ < source_.size() && source_[cursor_] == '.') {
            ++cursor_;
            const std::size_t digits = cursor_;
            while (cursor_ < source_.size() && source_[cursor_] >= '0' && source_[cursor_] <= '9') ++cursor_;
            if (digits == cursor_) fail("Missing fractional digits");
        }
        if (cursor_ < source_.size() && (source_[cursor_] == 'e' || source_[cursor_] == 'E')) {
            ++cursor_;
            if (cursor_ < source_.size() && (source_[cursor_] == '+' || source_[cursor_] == '-')) ++cursor_;
            const std::size_t digits = cursor_;
            while (cursor_ < source_.size() && source_[cursor_] >= '0' && source_[cursor_] <= '9') ++cursor_;
            if (digits == cursor_) fail("Missing exponent digits");
        }
        const auto token = source_.substr(begin, cursor_ - begin);
        double result = 0;
        const auto parsed = std::from_chars(token.data(), token.data() + token.size(), result);
        if (parsed.ec != std::errc{} || parsed.ptr != token.data() + token.size() || !std::isfinite(result))
            fail("Number is outside the finite range");
        return result;
    }
    Value value(std::size_t depth) {
        if (depth > max_depth_) fail("JSON nesting limit exceeded");
        if (++nodes_ > max_nodes_) fail("JSON node limit exceeded");
        whitespace();
        if (cursor_ >= source_.size()) fail("Missing value");
        const char c = source_[cursor_];
        if (c == '"') return string();
        if (c == '{') return object(depth + 1);
        if (c == '[') return array(depth + 1);
        if (c == '-' || (c >= '0' && c <= '9')) return number();
        const auto literal = [&](std::string_view text) {
            if (source_.substr(cursor_, text.size()) != text) fail("Invalid literal");
            cursor_ += text.size();
        };
        if (c == 't') { literal("true"); return true; }
        if (c == 'f') { literal("false"); return false; }
        if (c == 'n') { literal("null"); return nullptr; }
        fail("Unexpected JSON token");
    }
    Value array(std::size_t depth) {
        expect('[');
        Value::Array result;
        if (take(']')) return result;
        do { result.push_back(value(depth)); } while (take(','));
        expect(']');
        return result;
    }
    Value object(std::size_t depth) {
        expect('{');
        Value::Object result;
        if (take('}')) return result;
        do {
            const std::string key = string();
            expect(':');
            if (!result.emplace(key, value(depth)).second) fail("Duplicate object key");
        } while (take(','));
        expect('}');
        return result;
    }

public:
    Parser(std::string_view source, std::size_t max_nodes, std::size_t max_depth)
        : source_(source), max_nodes_(max_nodes), max_depth_(max_depth) {}
    Value parse() {
        Value result = value(0);
        whitespace();
        if (cursor_ != source_.size()) fail("Trailing data");
        return result;
    }
};

inline Value parse(std::string_view source, std::size_t max_nodes = 200000, std::size_t max_depth = 64) {
    if (source.empty()) throw Error("Empty JSON document");
    return Parser(source, max_nodes, max_depth).parse();
}

inline void append_escaped(std::string& output, std::string_view value) {
    static constexpr char hex[] = "0123456789abcdef";
    output.push_back('"');
    for (const unsigned char c : value) {
        switch (c) {
        case '"': output += "\\\""; break;
        case '\\': output += "\\\\"; break;
        case '\b': output += "\\b"; break;
        case '\f': output += "\\f"; break;
        case '\n': output += "\\n"; break;
        case '\r': output += "\\r"; break;
        case '\t': output += "\\t"; break;
        default:
            if (c < 0x20) {
                output += "\\u00";
                output.push_back(hex[c >> 4]);
                output.push_back(hex[c & 0xf]);
            } else {
                output.push_back(static_cast<char>(c));
            }
        }
    }
    output.push_back('"');
}

inline void append(std::string& output, const Value& value) {
    if (value.is_null()) output += "null";
    else if (value.is_bool()) output += value.as_bool() ? "true" : "false";
    else if (value.is_number()) {
        char buffer[64];
        const auto result = std::to_chars(buffer, buffer + sizeof(buffer), value.as_number(), std::chars_format::general, 17);
        if (result.ec != std::errc{}) throw Error("Cannot serialize number");
        output.append(buffer, result.ptr);
    } else if (value.is_string()) {
        append_escaped(output, value.as_string());
    } else if (value.is_array()) {
        output.push_back('[');
        bool first = true;
        for (const auto& item : value.as_array()) {
            if (!first) output.push_back(',');
            first = false;
            append(output, item);
        }
        output.push_back(']');
    } else {
        output.push_back('{');
        bool first = true;
        for (const auto& item : value.as_object()) {
            if (!first) output.push_back(',');
            first = false;
            append_escaped(output, item.first);
            output.push_back(':');
            append(output, item.second);
        }
        output.push_back('}');
    }
}

inline std::string dump(const Value& value) {
    std::string output;
    append(output, value);
    return output;
}

} // namespace amjson
