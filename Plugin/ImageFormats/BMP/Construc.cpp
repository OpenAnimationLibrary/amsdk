// Yves  10/04/2004  \Yves115\Plugin\Image Formats\BMP\Construc.cpp

#include "StdAfx.h"
#include "Custom.h"
#include "IOApp.h"

extern CImageIOApp theApp;

extern "C" __declspec(dllexport) ImageIO *CreateImageIO(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new CustomImageIO(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())

    return IMAGEIODLLVERSION;
}

CustomImageIO::CustomImageIO(HTreeObject *treeobject) : ImageIO(treeobject) {}

CustomImageIO::~CustomImageIO() = default;
