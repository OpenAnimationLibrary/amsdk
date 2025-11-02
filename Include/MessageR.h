//RC  12/23/97  \randy5\include\MessageR.h
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once

#include "StdAfx.h"
#include "Exports.h"

class String;

#define MR_OK               0
#define MR_OKCANCEL         1
#define MR_RETRYCANCEL      2
#define MR_YESNO            3
#define MR_YESNOCANCEL      4
#define MR_ABORTRETRYIGNORE 5
#define MR_SAVE             6
#define MR_WARNING          7
#define MR_INFORMATION      8
#define MR_STOP             9
#define MR_ERROR            10

/* RETURN VALUES */
#define MR_RETABORT         0
#define MR_RETNO            0
#define MR_RETCANCEL        (-1)
#define MR_RETIGNORE        2
#define MR_RETOK            1
#define MR_RETRETRY         1
#define MR_RETYES           1

FILEIOEXPORT INT MessageRequest(UINT messageid, UINT style = MR_OK, UINT titleid = 128);// 128 IDR_MAINFRAME
FILEIOEXPORT INT MessageRequest(const String &message, UINT style = MR_OK, UINT titleid = 128);
