// KB  01/19/2005  \Plugin\Image Formats\JPG\IOApp.h
#pragma once

#include "SDK/Misc.h"

class CImageIOApp final : public CPluginApp {
public:
    int m_compression{}; // JPEG compression quality from 1 to 100
    int m_optimal{}; // 

    BOOL InitInstance() override;
    int ExitInstance() override;
};
