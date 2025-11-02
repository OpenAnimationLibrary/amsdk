// RC  12/21/2004  \Ken120\Plugin\Image Formats\AVI\Construc.cpp

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

CustomImageIO::CustomImageIO(HTreeObject *treeobject) : ImageIO(treeobject),
                                                        AVIopts{},
                                                        AVIaopts{},
                                                        AVIsvi{},
                                                        AVIsai{},
                                                        bmHeader{},
                                                        pmdStuff{nullptr},
                                                        pAVIFile{nullptr},
                                                        pAVIStream{nullptr},
                                                        pAVIStreamB{nullptr},
                                                        pAVIStreamA{nullptr},
                                                        pAVIStreamAB{nullptr},
                                                        waveformat{} {}

CustomImageIO::~CustomImageIO() = default;
