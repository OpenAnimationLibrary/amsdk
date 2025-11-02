//NAP  2/26/2001  \Noel90\Include\Exports.h
#pragma once

#ifdef PATCHLIB
#define PATCHEXPORT __declspec(dllexport)
#else
#define PATCHEXPORT
#endif

#ifdef BITMAPLIB
#define BITMAPEXPORT __declspec(dllexport)
#else
#define BITMAPEXPORT
#endif

#ifdef FILEIOLIB
#define FILEIOEXPORT __declspec(dllexport)
#else
#define FILEIOEXPORT
#endif

#ifdef GASSISTLIB
#define GASSISTEXPORT __declspec(dllexport)
#else
#define GASSISTEXPORT
#endif

#ifdef MATRIXLIB
#define MATRIXEXPORT __declspec(dllexport)
#else
#define MATRIXEXPORT
#endif

#ifdef PLUGINLIB
#define PLUGINEXPORT __declspec(dllexport)
#else
#define PLUGINEXPORT
#endif

#ifdef SUPPORTLIB
#define SUPPORTEXPORT __declspec(dllexport)
#else
#define SUPPORTEXPORT
#endif
