// NAP  3/3/2003  \Noel105\Plugin\Post\Dither\PostApp.cpp
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

CPostApp::CPostApp(): m_bittypeinfo{nullptr}, m_levelsinfo{nullptr} {}

/*
   static BoolPropertyInfo    f_isditherinfo(
      6, DOC("Animation:Master calculates all color values \
      in the full visible range. Unfortunately, the most common image file formats \
      truncate the color to 24 bits (even the best file formats only save 30 \
      bits). This is a significant reduction in the number of colors distinguishable \
      by the human eye, and results in an undesirable artifact called &quot;Mach \
      banding&quot;. Mach banding is the visible change of a color gradient, \
      usually the falloff of light on a flat, uniform surface. Because Animation:Master \
      knows the true color before it gets truncated, the program can accumulate \
      the color error and disperse it to the surrounding pixels, called &quot;dithering&quot;. \
      Dithering substantially masks Mach banding but destroys the image's uniformity \
      when viewed closely. However, the trade-off is almost always appropriate for animation."),
      IDS_DITHER,             IDL_DITHER,          FALSE, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLEALWAYS, PropertyInfo::CONSTANT );
*/
BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_bittypes.SetArraySize(NUM_BIT_STYLES);
    m_bittypes[BITS_24]->SetMatchName("24");
    string.LoadString(IDS_24);
    m_bittypes[BITS_24]->SetLocalizedName(string.GetBuffer());
    m_bittypes[BITS_16]->SetMatchName("16");
    string.LoadString(IDS_16);
    m_bittypes[BITS_16]->SetLocalizedName(string.GetBuffer());
    m_bittypes[BITS_8]->SetMatchName("8");
    string.LoadString(IDS_8);
    m_bittypes[BITS_8]->SetLocalizedName(string.GetBuffer());
    m_bittypes[BITS_CUSTOM]->SetMatchName("Custom");
    string.LoadString(IDS_CUSTOM);
    m_bittypes[BITS_CUSTOM]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_BITSPERCHANNEL);
    m_bittypeinfo = HTypePropertyInfo::New(string, "BitsPerChannel", &m_bittypes);
    m_bittypeinfo->SetDefaultIndex(BITS_16);

    string.LoadString(IDS_LEVELS);
    m_levelsinfo = HIntPropertyInfo::New(string, "Levels");
    m_levelsinfo->SetDefaultValue(BITS_16_LEVELS);
    m_levelsinfo->SetMinValue(2);
    m_levelsinfo->SetConstant(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_levelsinfo;
    delete m_bittypeinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
