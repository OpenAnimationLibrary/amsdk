#pragma once

// include geom.h before this

// extrude spec flags
enum : unsigned {
    EX_FRONT = 0x0,	// always want front cross section, so use "no effect" flag for documentation
    EX_MID = 0x1,	// want cross section between front and back
    EX_BACK = 0x2,	// want cross section at back
    EX_CLOSE_FRONT =0x4,	// want front quadrified
    EX_CLOSE_BACK = 0x8,	// want back quadrified
    EX_BEV_FRONT = 0x10,	// want front beveled
    EX_BEV_BACK = 0x20,	// want back beveled
    EX_BEV_SIDE = 0x40,	// want sides beveled
    EX_ROUND = 0x80,	// want round bevels
    EX_INWARD = 0x100,	// want inward insets
    EX_SUB = 0x200,	// let edges be subdivided
    EX_SUB_ALL = 0x400	// want all edges subdivided
};

void Extrude(Subdiv *subdiv, PolygonalAreaArray *pa, unsigned flags, float depth, float inset);
