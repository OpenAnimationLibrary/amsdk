#pragma once
// include geom.h before this

// extrude spec flags
enum : unsigned {
    EX_FRONT = 0x0U,
    // always want front cross section, so use "no effect" flag for documentation
    EX_MID = 0x1U,
    // want cross section between front and back
    EX_BACK = 0x2U,
    // want cross section at back
    EX_CLOSE_FRONT =0x4U,
    // want front quadrified
    EX_CLOSE_BACK = 0x8U,
    // want back quadrified
    EX_BEV_FRONT = 0x10U,
    // want front beveled
    EX_BEV_BACK = 0x20U,
    // want back beveled
    EX_BEV_SIDE = 0x40U,
    // want sides beveled
    EX_ROUND = 0x80U,
    // want round bevels
    EX_INWARD = 0x100U,
    // want inward insets
    EX_SUB = 0x200U,
    // let edges be subdivided
    EX_SUB_ALL = 0x400U // want all edges subdivided
};

void Extrude(Subdiv *subdiv, PolygonalAreaArray *pa, unsigned flags, float depth, float inset);
