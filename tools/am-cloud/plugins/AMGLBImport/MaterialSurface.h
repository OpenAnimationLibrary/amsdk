#pragma once
#include "ImportCore.h"

namespace amglb {
// A:M StoreValue uses fractions for these percentage properties; the UI and
// saved MDL multiply them by 100. SDK OldAttr.h likewise defaults intensity to
// 1.F (100%). Keep this conversion shared by the native adapter and core tests.
struct SurfaceFractions {
    double specularSize, specularIntensity, reflectivity, transparency;
};
inline SurfaceFractions SurfaceForMaterial(const Material& material){
    return {.05+.75*material.roughness, .2+.6*material.metallic,
            .35*material.metallic, 1-material.color[3]};
}
}
