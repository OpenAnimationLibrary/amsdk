//MH  3/25/2007 added Rnd4
//MH  4/26/2003  \Mart105\Include\Rnd.h
#pragma once

#include "Exports.h"

PLUGINEXPORT float Rnd(); //interval 0 <-> 1
PLUGINEXPORT int Rnd_RandMax(); //interval 0 <-> RAND_MAX mimics rand()
PLUGINEXPORT float Rnd(float min, float max);// interval min <-> max
PLUGINEXPORT int Rnd(int min, int max);// interval min <-> max
PLUGINEXPORT void SetSeed(UINT seed);

PLUGINEXPORT float Rnd2() noexcept;
PLUGINEXPORT void SetSeed2(UINT seed) noexcept;
PLUGINEXPORT UINT GetSeed2() noexcept;
PLUGINEXPORT void SetSeed_Seed2(UINT seed = 0);//setting seed for Rnd and Rnd2
PLUGINEXPORT float Rnd4(UINT seed) noexcept;
