#pragma once
namespace make_group {
inline constexpr float centers[3] = {-150, 0, 150};
struct Point { float x, y, z; };
// Same six independent four-point faces as the owner's working cube(3).mdl.
// Coordinates are centimeters; the cube is centered and 100 cm across.
inline constexpr Point faces[6][4] = {
    {{-50,50,50}, {-50,-50,50}, {50,-50,50}, {50,50,50}},
    {{50,50,-50}, {50,-50,-50}, {-50,-50,-50}, {-50,50,-50}},
    {{50,50,50}, {50,-50,50}, {50,-50,-50}, {50,50,-50}},
    {{-50,50,-50}, {-50,-50,-50}, {-50,-50,50}, {-50,50,50}},
    {{-50,50,-50}, {-50,50,50}, {50,50,50}, {50,50,-50}},
    {{-50,-50,50}, {-50,-50,-50}, {50,-50,-50}, {50,-50,50}}
};
}
