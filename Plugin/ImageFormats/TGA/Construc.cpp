// Dan  11/26/2001  \Dan90\Plugin\tures\Environment\Construc.cpp

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
