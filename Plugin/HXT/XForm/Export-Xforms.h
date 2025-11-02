#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <cinttypes>
#include <string>
#include "F_Protos.h"
#include "SDK/Misc.h"
#include "SDK/HProject.h"

#define G_STRPLUGNAME _T("Export Transforms (*.xform)")

class HTreeObject;
class HModelCache;

class ExportXformsApp final : public CPluginApp {
public:
    ExportXformsApp();
    ~ExportXformsApp() override;

    BOOL InitInstance() override;
    int ExitInstance() override;

};

/*
Dump file data structures
*/

struct main_header {
    char file_tag[6]; // "XFORM"
    char version[2]; // {0,1} (0.1) for this version
    int32_t num_bones;
    int32_t num_frames;
    int32_t start_frame;
};

/*
The base (rest pose) transformations of all bones are specified in the same shared coordinate space.
*/
struct bone_def {
    char name[128];
    int32_t parent;
    float base_translation[3];
    float base_quat[4];
};

struct frame_header {
    int32_t num_bones;
};

/*
The animated bone transformations are specified in the bone's local space, as would be reflected by baked animation curves.
*/
struct xforms {
    int32_t bone_index;
    float translation[3];
    float quat[4]; // wxyz
    float scale[3];
};
