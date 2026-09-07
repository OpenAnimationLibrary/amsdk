#include "Coordinates.h"
#include <cassert>
#include <limits>

int main() {
    using namespace makeabone;
    float value = 123.0f;
    assert(ParseCoordinate(" -2.5 ", value) && value == -2.5f);
    assert(ParseCoordinate("+1e2", value) && value == 100.0f);
    assert(ParseCoordinate(".25", value) && value == 0.25f);
    assert(ParseCoordinate("-1000000", value) && value == -1000000.0f);
    for (const char *invalid : {"", " ", "nan", "inf", "-inf", "1e100", "2cm",
                               "1,2", "1000001", "--2", "+-2", "++2", "+", "1 2"}) {
        value = 123.0f;
        assert(!ParseCoordinate(invalid, value) && value == 123.0f);
    }
    const float ordinary[6] = {-2.5f, 4.0f, -6.0f, 1.0f, 8.0f, -10.0f};
    assert(ValidEndpoints(ordinary));
    const float same[6] = {1, 2, 3, 1, 2, 3};
    assert(!ValidEndpoints(same));
    const float tooShort[6] = {0, 0, 0, 0, 1e-6f, 0};
    assert(!ValidEndpoints(tooShort));
    const float large[6] = {-1000000, -1000000, -1000000, 1000000, 1000000, 1000000};
    assert(ValidEndpoints(large));
    const float invalid[6] = {0, 0, 0, 0, std::numeric_limits<float>::infinity(), 0};
    assert(!ValidEndpoints(invalid));
    for (int axis = 0; axis < 3; ++axis) {
        for (float sign : {-1.0f, 1.0f}) {
            float points[6] = {};
            points[axis + 3] = sign * 10.0f;
            assert(ValidEndpoints(points));
        }
    }
    return 0;
}
