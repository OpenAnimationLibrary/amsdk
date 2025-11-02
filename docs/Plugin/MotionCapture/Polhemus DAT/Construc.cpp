// Dan  11/26/2001  \Dan90\Plugin\MotionCapture\Polhemus DAT\Construc.cpp

#include "StdAfx.h"
#include "Capture.h"
#include "MotionCaptureApp.h"

extern CMCApp theApp;

extern "C" __declspec(dllexport) MCDriver *CreateDriver(HTreeObject *treeobject) {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return new Driver(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion() {
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    return MCDLLVERSION;
}

Driver::Driver(HTreeObject *Treeobject) : MCDriver(Treeobject) {
    m_scalefactortype = HTypeProperty::New(theApp.m_scalefactortypeinfo);
    //   m_isbinary = HBoolProperty::New( theApp.m_isbinaryinfo );
    m_filename = HFilenameProperty::New(theApp.m_filenameinfo);
}

Driver::~Driver() {
    delete m_scalefactortype;
    //delete m_isbinary;
    delete m_filename;
}
