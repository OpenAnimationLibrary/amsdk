#pragma once
#include <charconv>
#include <cmath>
#include <string_view>
#include <system_error>

namespace makeabone {
// Bounds keep downstream SDK float geometry clear of overflow/degeneracy.
inline bool ParseCoordinate(std::string_view text, float &value) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string_view::npos) return false;
    text = text.substr(first, text.find_last_not_of(" \t\r\n") - first + 1);
    if (text.front() == '+') {
        text.remove_prefix(1);
        if (!text.empty() && text.front() == '-') return false;
    }
    if (text.empty() || text.front() == '+') return false;
    float parsed = 0.0f;
    const auto result = std::from_chars(text.data(), text.data() + text.size(), parsed);
    if (result.ec != std::errc{} || result.ptr != text.data() + text.size() ||
        !std::isfinite(parsed) || std::abs(parsed) > 1000000.0f) return false;
    value = parsed;
    return true;
}

inline bool ValidEndpoints(const float (&values)[6]) {
    for (const float value : values)
        if (!std::isfinite(value) || std::abs(value) > 1000000.0f) return false;
    double squared = 0.0;
    for (int i = 0; i < 3; ++i) {
        const double difference = static_cast<double>(values[i + 3]) - values[i];
        squared += difference * difference;
    }
    return squared >= 1.0e-10; // at least 0.00001 cm after float conversion
}
} // namespace makeabone
