#pragma once
// Setbiaser: new implementation inspired by Emilio Le Roux's Setbias.
// Pure, SDK-independent arithmetic. All snapshots retain native float precision.
#include <array>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace sb {
enum class Operation { Set, Offset, Scale };
using Values = std::array<float, 6>; // Mag In/Out, Alpha In/Out, Gamma In/Out.
struct Units {
    std::array<double, 3> factor{100.0, 57.29577951308232, 57.29577951308232};
    std::array<double, 3> minimum{0.0, -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max()};
    std::array<double, 3> maximum{std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
    void validate() const {
        for (std::size_t i = 0; i != 3; ++i)
            if (!std::isfinite(factor[i]) || factor[i] <= 0 ||
                !std::isfinite(minimum[i]) || !std::isfinite(maximum[i]) || minimum[i] > maximum[i])
                throw std::runtime_error("A:M returned invalid native bias units or limits.");
    }
    double display(float raw, std::size_t field) const {
        if (field >= 6) throw std::out_of_range("Bias field");
        return static_cast<double>(raw) * factor[field / 2];
    }
};
struct Edit { std::size_t field = 0; Operation operation = Operation::Set; double value = 0; bool linked = false; bool reset = false; };
inline float checked(double value, const Units &units, std::size_t field) {
    const auto row = field / 2;
    if (!std::isfinite(value) || value < units.minimum[row] || value > units.maximum[row] ||
        std::abs(value) > static_cast<double>(std::numeric_limits<float>::max()) || (row == 0 && value < 0))
        throw std::runtime_error("The result is outside A:M's native bias range. No values were changed.");
    return static_cast<float>(value);
}
inline Values calculate(const Values &baseline, const Units &units, const Edit &edit) {
    units.validate();
    if (edit.field >= 6) throw std::out_of_range("Bias field");
    if (!std::isfinite(edit.value)) throw std::runtime_error("Enter a finite number.");
    Values result = baseline;
    if (edit.reset) {
        for (std::size_t f = 0; f != 6; ++f)
            result[f] = checked((f < 2 ? 100.0 : 0.0) / units.factor[f / 2], units, f);
        return result;
    }
    if (edit.operation == Operation::Scale && (edit.field >= 2 || edit.value < 0))
        throw std::runtime_error("Scale applies to magnitudes only and requires a nonnegative factor.");
    for (std::size_t f = 0; f != 6; ++f) {
        if (f != edit.field && !(edit.linked && f == (edit.field ^ std::size_t{1}))) continue;
        if (!std::isfinite(baseline[f])) throw std::runtime_error("The selected bias is not finite.");
        // Compute from the gesture-start baseline, never from an earlier preview.
        double raw = 0;
        switch (edit.operation) {
            case Operation::Set: raw = edit.value / units.factor[f / 2]; break;
            case Operation::Offset: raw = static_cast<double>(baseline[f]) + edit.value / units.factor[f / 2]; break;
            case Operation::Scale: raw = static_cast<double>(baseline[f]) * edit.value; break;
            default: throw std::runtime_error("Unknown bias operation.");
        }
        result[f] = checked(raw, units, f);
    }
    return result;
}
inline std::optional<float> common(const std::vector<Values> &values, std::size_t field) {
    if (field >= 6) throw std::out_of_range("Bias field");
    if (values.empty()) return std::nullopt;
    const float first = values.front()[field];
    for (const auto &value : values) if (value[field] != first) return std::nullopt;
    return first;
}
inline double parse(std::string_view text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string_view::npos) throw std::runtime_error("Enter a number, not Mixed or an empty field.");
    text.remove_prefix(first);
    text = text.substr(0, text.find_last_not_of(" \t\r\n") + 1);
    if (!text.empty() && text.front() == '+') text.remove_prefix(1);
    double value = 0;
    const auto parsed = std::from_chars(text.data(), text.data() + text.size(), value);
    if (text.empty() || parsed.ec != std::errc{} || parsed.ptr != text.data() + text.size() || !std::isfinite(value))
        throw std::runtime_error("Enter a finite decimal number using a dot as the decimal separator.");
    return value;
}
inline std::string format(double value) {
    char buffer[64]{};
    const auto r = std::to_chars(buffer, buffer + sizeof buffer, value, std::chars_format::general, 9);
    if (r.ec != std::errc{}) throw std::runtime_error("Cannot display this value.");
    return {buffer, r.ptr};
}
} // namespace sb
