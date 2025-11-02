// YP  01/10/2005  \Plugin\Image Formats\JPG\Construc.cpp

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
                                                        m_status{0},
                                                        m_width{0},
                                                        m_height{0},
                                                        m_bytesperpixel{0},
                                                        m_colorspace{0},
                                                        m_gammacorrection{0.F},
                                                        m_gammapreset{GAMMA_NONE},
                                                        m_ungammacorrect{false},
                                                        m_dinfo{},
                                                        m_cinfo{},
                                                        m_jerr{},
                                                        m_jpegbuffer{nullptr} { }

CustomImageIO::~CustomImageIO() = default;
