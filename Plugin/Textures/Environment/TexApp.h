// KB  4/5/01  \Ken90\Plugin\Textures\Environment\TexApp.h
#pragma once

#include "SDK/HPropert.h"
#include "SDK/Misc.h"

class CTextureApp final : public CPluginApp {
public:
    HClipPropertyInfo *m_clipinfo{};
    HTimePropertyInfo *m_timeinfo{};
    HFloatPropertyInfo *m_opacityinfo{};
    HBoolPropertyInfo *m_isadditiveinfo{};

    BOOL InitInstance() override;
    int ExitInstance() override;
};
