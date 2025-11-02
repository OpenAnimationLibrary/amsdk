// WEP  4/12/2005  \will120\Plugin\MotionCapture\Polhemus Network\Construc.cpp

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
    m_isbinary = HBoolProperty::New(theApp.m_isbinaryinfo);
    m_ipaddress = HStringProperty::New(theApp.m_ipaddressinfo);
    m_port = HIntProperty::New(theApp.m_portinfo);
    m_timeout = HIntProperty::New(theApp.m_timeoutinfo);
}

Driver::~Driver() {
    delete m_scalefactortype;
    delete m_isbinary;
    delete m_ipaddress;
    delete m_port;
    delete m_timeout;
}
