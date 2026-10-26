#include "GlyphOutline.h"
#include <cstddef>
#include <cstring>
#include <cmath>
#include <stdexcept>

namespace fw2 {
namespace {
float fixed(FIXED v) { return static_cast<float>(v.value) + static_cast<float>(v.fract) / 65536.0F; }
Point point(POINTFX v, Point origin, float scale) {
    return {origin[0] + scale * fixed(v.x), origin[1] + scale * fixed(v.y)};
}
Point interpolate(Point a, Point b, float t) {
    return {a[0] + t * (b[0] - a[0]), a[1] + t * (b[1] - a[1])};
}
class FontDC {
public:
    HDC dc = CreateCompatibleDC(nullptr);
    HFONT font = nullptr;
    HGDIOBJ previous = nullptr;
    explicit FontDC(const LOGFONTW &description) {
        if (dc) font = CreateFontIndirectW(&description);
        if (font) previous = SelectObject(dc, font);
        if (!dc || !font || !previous || previous == HGDI_ERROR) {
            cleanup();
            throw std::runtime_error("The selected font could not be opened.");
        }
    }
    ~FontDC() { cleanup(); }
    FontDC(const FontDC &) = delete;
    FontDC &operator=(const FontDC &) = delete;
private:
    void cleanup() {
        if (dc && previous && previous != HGDI_ERROR) SelectObject(dc, previous);
        if (font) DeleteObject(font);
        if (dc) DeleteDC(dc);
        dc = nullptr; font = nullptr; previous = nullptr;
    }
};
template<class T> T read(const std::vector<unsigned char> &buffer, std::size_t offset,
                         std::size_t limit) {
    if (offset > limit || sizeof(T) > limit - offset || limit > buffer.size())
        throw std::runtime_error("The font returned an invalid outline.");
    T value{};
    std::memcpy(&value, buffer.data() + offset, sizeof(T));
    return value;
}
}

std::vector<Contour> ReadGlyphOutlines(const std::wstring &text, const LOGFONTW &font,
                                     float emHeight) {
    if (text.empty() || text.size() > 512 || !std::isfinite(emHeight) || emHeight <= 0)
        throw std::runtime_error("Invalid text or em height.");
    LOGFONTW description = font;
    description.lfHeight = -2048; description.lfWidth = 0;
    FontDC context(description);
    MAT2 matrix{}; matrix.eM11.value = 1; matrix.eM22.value = 1;
    const float scale = emHeight / 2048.0F;
    Point origin{0, 0};
    std::vector<Contour> result;
    std::size_t segmentCount = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        const wchar_t ch = text[i];
        if (ch == L'\r' || ch == L'\n') {
            if (ch == L'\r' && i + 1 < text.size() && text[i + 1] == L'\n') ++i;
            origin[0] = 0; origin[1] -= emHeight * 1.2F; continue;
        }
        if (ch == L'\t') { origin[0] += emHeight * 2; continue; }
        if (ch < 32 || (ch >= 0xD800 && ch <= 0xDFFF))
            throw std::runtime_error("Unsupported text character. Use BMP text without control characters.");
        WORD glyph = 0;
        if (GetGlyphIndicesW(context.dc, &ch, 1, &glyph, GGI_MARK_NONEXISTING_GLYPHS) == GDI_ERROR || glyph == 0xFFFF)
            throw std::runtime_error("The selected font does not contain every text character.");
        GLYPHMETRICS metrics{};
        const DWORD bytes = GetGlyphOutlineW(context.dc, static_cast<UINT>(ch), GGO_NATIVE,
                                             &metrics, 0, nullptr, &matrix);
        if (bytes == GDI_ERROR || bytes > 16 * 1024 * 1024)
            throw std::runtime_error("The selected font does not provide usable native outlines.");
        std::vector<unsigned char> buffer(bytes);
        if (bytes && GetGlyphOutlineW(context.dc, static_cast<UINT>(ch), GGO_NATIVE,
                                     &metrics, bytes, buffer.data(), &matrix) == GDI_ERROR)
            throw std::runtime_error("The font outline could not be read.");
        std::size_t offset = 0;
        while (offset < buffer.size()) {
            const auto header = read<TTPOLYGONHEADER>(buffer, offset, buffer.size());
            if (header.dwType != TT_POLYGON_TYPE || header.cb < sizeof(header) || header.cb > buffer.size() - offset)
                throw std::runtime_error("The font returned an invalid contour.");
            const std::size_t end = offset + header.cb;
            offset += sizeof(header);
            Contour contour; contour.start = point(header.pfxStart, origin, scale);
            Point current = contour.start;
            while (offset < end) {
                const WORD type = read<WORD>(buffer, offset, end);
                const WORD count = read<WORD>(buffer, offset + sizeof(WORD), end);
                const std::size_t dataStart = offset + offsetof(TTPOLYCURVE, apfx);
                if (count == 0 || dataStart > end || count > (end - dataStart) / sizeof(POINTFX))
                    throw std::runtime_error("The font returned an invalid curve.");
                std::vector<Point> points;
                for (WORD j = 0; j < count; ++j)
                    points.push_back(point(read<POINTFX>(buffer, dataStart + static_cast<std::size_t>(j) * sizeof(POINTFX), end), origin, scale));
                if (type == TT_PRIM_LINE) {
                    for (Point p : points) { contour.segments.push_back({p, {}, {}, false}); current = p; }
                } else if (type == TT_PRIM_QSPLINE && count >= 2) {
                    for (std::size_t j = 0; j + 1 < points.size(); ++j) {
                        const Point finish = j + 2 == points.size() ? points[j + 1] : interpolate(points[j], points[j + 1], 0.5F);
                        contour.segments.push_back({finish, interpolate(current, points[j], 2.0F / 3.0F),
                                                    interpolate(finish, points[j], 2.0F / 3.0F), true});
                        current = finish;
                    }
                } else if (type == TT_PRIM_CSPLINE && count % 3 == 0) {
                    for (std::size_t j = 0; j < points.size(); j += 3) {
                        contour.segments.push_back({points[j + 2], points[j], points[j + 1], true});
                        current = points[j + 2];
                    }
                } else throw std::runtime_error("The font contains an unsupported curve type.");
                offset = dataStart + static_cast<std::size_t>(count) * sizeof(POINTFX);
                segmentCount += points.size();
                if (segmentCount > 200000) throw std::runtime_error("Text geometry is too complex; use a shorter text.");
            }
            if (current != contour.start) contour.segments.push_back({contour.start, {}, {}, false});
            if (!contour.segments.empty()) result.push_back(std::move(contour));
        }
        origin[0] += scale * static_cast<float>(metrics.gmCellIncX);
    }
    if (result.empty()) throw std::runtime_error("The text contains no visible outline geometry.");
    return result;
}
}
