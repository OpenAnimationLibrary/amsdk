#include "FontWiz2Api.h"
#include "GlyphOutline.h"
#include <iostream>
#include <stdexcept>
#include <limits>

namespace {
void require(bool value) { if (!value) throw std::runtime_error("FontWiz2 native test failed."); }
}
int main() {
    FW2Request request; FW2Reply reply;
    require(!FW2ValidRequest(&request, &reply));
    wcscpy_s(request.text, L"Hello\r\nWorld");
    require(FW2ValidRequest(&request, &reply));
    const auto invalid = [&]() { require(!FW2ValidRequest(&request, &reply)); };
    request.version = 99; invalid(); request.version = FW2_API_VERSION;
    request.size = 0; invalid(); request.size = sizeof(request);
    reply.version = 99; invalid(); reply.version = FW2_API_VERSION;
    reply.size = 0; invalid(); reply.size = sizeof(reply);
    std::wmemset(request.text, L'A', FW2_MAX_TEXT + 1); invalid();
    wcscpy_s(request.text, L" \t\r\n "); invalid();
    request.text[0] = 0xD800; request.text[1] = 0; invalid();
    wcscpy_s(request.text, L"Caf\x00e9"); require(FW2ValidRequest(&request, &reply));
    require(!FW2ValidRequest(nullptr, &reply)); require(!FW2ValidRequest(&request, nullptr));
    LOGFONTW font{}; font.lfWeight = FW_NORMAL; wcscpy_s(font.lfFaceName, L"Arial");
    const auto outlines = fw2::ReadGlyphOutlines(L"AB8", font, 10);
    require(outlines.size() >= 6);
    bool curved = false;
    for (const auto &contour : outlines) {
        require(!contour.segments.empty() && contour.segments.back().end == contour.start);
        for (const auto &segment : contour.segments) curved = curved || segment.curved;
    }
    require(curved);
    const auto newline = fw2::ReadGlyphOutlines(L"A\r\nA", font, 10);
    require(newline.size() == 4);
    require(newline[2].start[1] < newline[0].start[1]);
    const auto accented = fw2::ReadGlyphOutlines(L"Caf\x00e9", font, 10);
    require(!accented.empty());
    bool rejected = false;
    try { (void)fw2::ReadGlyphOutlines(L" ", font, 10); } catch (const std::exception &) { rejected = true; }
    require(rejected); rejected = false;
    try { (void)fw2::ReadGlyphOutlines(L"A", font, std::numeric_limits<float>::infinity()); }
    catch (const std::exception &) { rejected = true; }
    require(rejected);
    std::cout << "FontWiz2: API validation and real GDI outline, curve, hole, multiline and accented-text tests passed.\n";
}
