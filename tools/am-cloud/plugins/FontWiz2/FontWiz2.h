#pragma once
#include "StdAfx.h"
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "FontWiz2Api.h"
#include "GlyphOutline.h"
#include "Options.h"
#include "Wizard.h"
#include <string>

class HModelCache;
class HTreeObject;
namespace fw2 {
HModelCache *ResolveModel(HTreeObject *object);
HModelCache *FindLiveModel(const void *identity);
HModelCache *Generate(HModelCache *model, const Options &options, std::uint32_t &splines);
}
