// Dan  11/26/2001  \Dan90\Plugin\MotionCapture\BioVision BVH\Construc.cpp

#include "StdAfx.h"
#include "Capture.h"

extern "C" __declspec(dllexport) MCDriver *CreateDriver(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new Driver(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return MCDLLVERSION;
}

Driver::Driver(HTreeObject *Treeobject) : MCDriver(Treeobject) {}
