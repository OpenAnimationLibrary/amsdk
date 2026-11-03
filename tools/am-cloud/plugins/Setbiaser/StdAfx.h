#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#undef __noinline
#define __noinline __declspec(noinline)
#define __restrict__
#define __thread __declspec(thread)
#define __aligned(...) __declspec(align(__VA_ARGS__))
#include <cmath>
#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <cstdint>
#include <algorithm>
#include "HashMath.h"
// SDK 19.5 RGBByte.h has six reviewed float *= byte conversions at
// lines 138-140, 299 and 473-474. These inline color operators are not used
// by Setbiaser. Scope C4244 suppression to this unmodified SDK header only;
// restore diagnostics before all plugin code and keep the build audit strict.
#pragma warning(push)
#pragma warning(disable: 4244)
#include "RGBByte.h"
#pragma warning(pop)
#include "SDK/Entry.h"
#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HProject.h"
#include "SDK/HCP.h"
#include "SDK/HPatch.h"
#include "SDK/HPropert.h"
