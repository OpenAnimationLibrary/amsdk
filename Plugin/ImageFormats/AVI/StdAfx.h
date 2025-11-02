// StdAfx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#pragma once
#ifndef STDAFX_H
#define STDAFX_H 

#define NOMINMAX

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0601
#ifdef NTDDI_VERSION
#undef NTDDI_VERSION
#endif
#define NTDDI_VERSION 0x06010000
#ifdef _WIN32_IE
#undef _WIN32_IE
#endif
#define _WIN32_IE 0x0800

// Exclude rarely-used stuff from Windows headers
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef _SECURE_ATL
#define _SECURE_ATL
#endif


#undef __noinline
#define __noinline            __declspec(noinline)
#define __restrict__           //__restrict // causes issues with MSVC
#ifndef __forceinline
#define __forceinline inline
#endif
#include <cmath>

#define __thread              __declspec(thread)
#define __aligned(...)        __declspec(align(__VA_ARGS__))

#include <afxwin.h> //MFC core and standard components
#include <afxext.h> //MFC extensions

#include "HashMath.h"

#ifdef _WIN64
#ifndef _AFX_NO_DB_SUPPORT
#define _AFX_NO_DB_SUPPORT
#endif
#ifndef _AFX_NO_DAO_SUPPORT
#define _AFX_NO_DAO_SUPPORT
#endif
#ifndef _AFX_NO_OLE_SUPPORT
#define _AFX_NO_OLE_SUPPORT
#endif
#endif

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#include <afxcmn.h>			// MFC support for Windows Common Controls

#if !defined (_DEBUG) && !defined (DEBUG)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef NO_WARN_MBCS_MFC_DEPRECATION
#define  NO_WARN_MBCS_MFC_DEPRECATION
#endif
// Some CString constructors will be explicit.
#ifndef _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#endif
// Turns off MFC feature that hides of some common warning messages
// that are frequently and safely ignored .
#ifndef _AFX_ALL_WARNINGS
#define _AFX_ALL_WARNINGS
#endif
#ifndef _ATL_ALL_WARNINGS
#define _ATL_ALL_WARNINGS
#endif
#endif

#endif
