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

CustomImageIO::CustomImageIO(HTreeObject *treeobject) : ImageIO(treeobject),
                                                        m_filenumber{0},
                                                        m_data(nullptr),
                                                        m_buf(nullptr),
                                                        m_row{nullptr},
                                                        m_bytesperpixel{0},
                                                        m_palette{},
                                                        m_width{0},
                                                        m_height{0},
                                                        m_depth{0},
                                                        m_width2{0},
                                                        m_width3{0},
                                                        m_bytes3{0},
                                                        m_bytes{0},
                                                        m_filled{0},
                                                        m_flags{0},
                                                        m_palentries{0},
                                                        m_status{0},
                                                        m_header{} { }

CustomImageIO::~CustomImageIO() {
    FREE(m_data)
}
