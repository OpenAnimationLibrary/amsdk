// NAP  3/3/2003  \Noel105\Plugin\Post\Bloom\PostApp.cpp
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

CPostApp::CPostApp(): m_styleinfo{nullptr}, m_strengthinfo{nullptr}, m_thresholdinfo{nullptr}, m_radiusinfo{nullptr} {}

/*
   static TypeInfo f_bloompresets[] = {
      TypeInfo( "OFF",    IDS_OFF,
      DOC("No Bloom affect will be applied.") ),
      TypeInfo( "Day",    IDS_DAY, 
      DOC("A daylight style bloom.") ),
      TypeInfo( "Night",  IDS_NIGHT, 
      DOC("A nighttime style bloom.") ),
      TypeInfo( "Custom", IDS_CUSTOM, 
      DOC("Allows custom control over the bloom.") ) };
   static TypePropertyInfo    f_isbloominfo(
      1, DOC("The time it takes for the chemical reaction to occur as a film negative \
      is exposed to light is called the &quot;response curve&quot;. Of course, \
      the exposure time is less than the frame rate of 24 frames per second, \
      and is the length of time the shutter is open - approximately one-hundredth \
      of a second. Longer exposure times can easily cause chemical reactions \
      to saturate, called &quot;over-exposure&quot;. The areas on the film negative \
      getting the most light get over-exposed first, which bloom into the darker \
      regions. This reaction is so sensitive to the amount of light that even \
      short exposure times can exhibit blooming in very bright areas such as \
      specular highlights. Blooming is most common when filming at night because \
      a large amount of light is allowed to enter the camera. Daylight filming \
      causes blooming where the amount of light varies greatly.\
      <br>Though Blooming is a camera artifact that most camera operators try \
      to avoid, it is a visual clue that all viewers are familiar with, therefore \
      it tends to make the image more realistic."),
      IDS_BLOOM,     f_bloompresets, NUMELEMENTS(f_bloompresets), IDL_BLOOM, 0, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLEALWAYS, PropertyInfo::CONSTANT|PropertyInfo::NOTIFYANIMOBJECTVALUECHANGED );
      static FloatPropertyInfo   f_bloomstrengthinfo(
         0, DOC("Controls how apparent the over-exposure is. These values range from “1” to “100”."),
         IDS_STRENGTH,           IDL_BLOOMSTRENGTH,   0, 0, 0, 100,   1, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLESOMETIMES );
      static FloatPropertyInfo   f_bloomthresholdinfo(
         1, DOC("Sets the light level at which blooming begins. These values range from “1” to “95”."),
         IDS_THRESHOLD,          IDL_BLOOMTHRESHOLD,  0, 0, 0, 100,   1, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLESOMETIMES );
      static FloatPropertyInfo   f_bloomradiusinfo(
         2, DOC("Controls how much the over-exposed regions on the negative seep outwards. These values range from “0” to “16”."),
         IDS_RADIUS,             IDL_BLOOMRADIUS,     0, 1, 1,  16,   1, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLESOMETIMES );
*/

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_styletypes.SetArraySize(NUM_STYLES);
    m_styletypes[STYLE_DAY]->SetMatchName("Day");
    string.LoadString(IDS_DAY);
    m_styletypes[STYLE_DAY]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_NIGHT]->SetMatchName("Night");
    string.LoadString(IDS_NIGHT);
    m_styletypes[STYLE_NIGHT]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_CUSTOM]->SetMatchName("Custom");
    string.LoadString(IDS_CUSTOM);
    m_styletypes[STYLE_CUSTOM]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_STYLE);
    m_styleinfo = HTypePropertyInfo::New(string, "Style", &m_styletypes);
    m_styleinfo->SetDefaultIndex(STYLE_DAY);

    string.LoadString(IDS_STRENGTH);
    m_strengthinfo = HPercentPropertyInfo::New(string, "Strength");
    m_strengthinfo->SetDefaultValue(DAY_STRENGTH);
    m_strengthinfo->SetConstant(TRUE);

    string.LoadString(IDS_THRESHOLD);
    m_thresholdinfo = HPercentPropertyInfo::New(string, "Threshold");
    m_thresholdinfo->SetDefaultValue(DAY_THRESHOLD);
    m_thresholdinfo->SetConstant(TRUE);

    string.LoadString(IDS_RADIUS);
    m_radiusinfo = HIntPropertyInfo::New(string, "Percent");
    m_radiusinfo->SetDefaultValue(DAY_RADIUS);
    m_radiusinfo->SetMinValue(1);
    m_radiusinfo->SetMaxValue(16);
    m_radiusinfo->SetConstant(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_strengthinfo;
    delete m_thresholdinfo;
    delete m_radiusinfo;
    delete m_styleinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
