// KB  1/19/2005  \Plugin\Image Formats\BMP\IOApp.h
#pragma once

#include "SDK/HPropert.h"
#include "SDK/Misc.h"

class CImageIOApp final : public CPluginApp {
public:
    BOOL InitInstance() override;
    int ExitInstance() override;
};
