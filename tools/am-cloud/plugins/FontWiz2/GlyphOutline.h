#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <array>
#include <string>
#include <vector>

namespace fw2 {
using Point = std::array<float, 2>;
struct Segment { Point end{}, control1{}, control2{}; bool curved = false; };
struct Contour { Point start{}; std::vector<Segment> segments; };
std::vector<Contour> ReadGlyphOutlines(const std::wstring &text,
                                     const LOGFONTW &font, float emHeight);
}
