#pragma once

#include "Select.h"

struct Parameter {
    UINT number; //Indexnummer cp
    UINT pid1; //Indexnummer patch 
    UINT pid2;
    UINT pid3;
    UINT pid4;
    UINT pid5;
    int type; //0 select cp,1 select patch,2 select 5pointer,3 select hooked Patches, 4 5p und hook, 5 flipped normals, 6 viewabhängig, 7 3Pointer, 8 unweighted
    int view; //0 front,1 back,2 left,3 right,4 top,5 bottom
    float tolerance; //für viewselect
    int cp_mode; //0 only cp, 1 entire spline, 2 patches along the spline
};
