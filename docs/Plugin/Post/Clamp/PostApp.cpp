// NAP  1/26/2005  \Noel120\Plugin\Post\Clamp\PostApp.cpp
//

#include "StdAfx.h"
#include "PostApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostApp

BEGIN_MESSAGE_MAP(CPostApp, CWinApp)
        //{{AFX_MSG_MAP(CPostApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostApp construction

CPostApp::CPostApp() = default;

/*
   static TypeInfo f_softenpresets[] = {
      TypeInfo( "OFF",    IDS_OFF, 
      DOC("No soften affect will be applied.") ),
      TypeInfo( "8MM",    IDS_8MM, 
      DOC("Mimics the softness of a 8MM lens.") ),
      TypeInfo( "16MM",   IDS_16MM, 
      DOC("Mimics the softness of a 16MM lens.") ),
      TypeInfo( "35MM",   IDS_35MM, 
      DOC("Mimics the softness of a 35MM lens.") ),
      TypeInfo( "Custom", IDS_CUSTOM, 
      DOC("Allows a custom softness setting.") ) };
   static TypePropertyInfo    f_issofteninfo(
      4, DOC("Camera lens can be made nearly perfect, but the light rays are still \
      distorted by the glass. As a result, filmed images are slightly blurry \
      (called &quot;soft&quot;). Larger lenses (35mm) produce sharper images \
      because the ratio of imperfection to size is less. Surprisingly, computer \
      generated images need to be blurred to degrade them to film quality! Blur \
      values range from &quot;0&quot; to &quot;15&quot;."),
      IDS_SOFTEN,    f_softenpresets, NUMELEMENTS(f_softenpresets), IDL_SOFTEN, 0, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLEALWAYS, PropertyInfo::CONSTANT|PropertyInfo::NOTIFYANIMOBJECTVALUECHANGED );
      static FloatPropertyInfo   f_softnessinfo(
         0, DOC("Size of the softness filter."),
         IDS_SOFTNESS,           IDL_SOFTNESS,        0, 1, .1f, 15,   1, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLESOMETIMES );
*/
BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
