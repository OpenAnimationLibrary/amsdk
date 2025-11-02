//MH  16 May 1998
#pragma once

#include "Exports.h"

class Vector;

PLUGINEXPORT void Perturb(const Vector &p, Vector &delta);
PLUGINEXPORT float Noise3(const Vector &);
PLUGINEXPORT float Contrast(float, float) noexcept;
PLUGINEXPORT float Brighten(float, float) noexcept;
PLUGINEXPORT float FractalTurb(const Vector &p, int octaves);
PLUGINEXPORT float Noise3ForSampling(const Vector &);
