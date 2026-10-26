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
#include "HashMath.h"
