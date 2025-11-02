// NAP  3/3/2003  \Noel105\Plugin\Post\FilmGrain\PostApp.cpp
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

CPostApp::CPostApp(): m_styleinfo{nullptr}, m_sizeinfo{nullptr}, m_amountinfo{nullptr} {}

/*
   static TypeInfo f_filmgrainpresets[] = {
      TypeInfo( "OFF",    IDS_OFF,
      DOC("No film grain applied.") ),
      TypeInfo( "100ASA", IDS_100ASA, 
      DOC("Average 100ASA film grain.") ),
      TypeInfo( "200ASA", IDS_200ASA, 
      DOC("Average 200ASA film grain.") ),
      TypeInfo( "400ASA", IDS_400ASA, 
      DOC("Average 400ASA film grain.") ),
      TypeInfo( "Custom", IDS_CUSTOM, 
      DOC("Allows custom grain sizes and amounts.") ) };
   static TypePropertyInfo    f_isfilmgraininfo(
      1, DOC("Film negatives consist of a clear mylar strip covered with light-sensitive \
      particles that change chemically when they are struck by a ray of light. \
      When the negatives are processed, the chemically changed particles interact \
      with color dyes to reproduce an image. Everything about this process is \
      delicate: the particles have to be small, react quickly but not too fast, \
      must be able to indicated the full range of color, and must be able to \
      represent both night and day and everything in between.\
      <p>Normally light is so abundant that, statistically speaking, distribution \
      is uniform, but the conditions inside of a camera are so exact that the \
      number of light rays that strike each particle exhibit their true randomness. \
      Places on the negative where a lot of light strikes are the brightest \
      and every particle has a chemical reaction, but in darker regions fewer \
      light rays leave many particles with partial reactions of varying degrees, \
      causing a visibly distinct &quot;grain&quot;.\
      <p>Different negative stocks that use particles with different sensitivities \
      show different grain patterns, and stocks that use particles that are \
      fast reacting for speed get even less light rays, exacerbating the problem. \
      Film grain is therefore a combination of film speed and chemical sensitivity. \
      Slow films, such as ASA100, have a lot of time to get light so there is \
      better distribution, so there is less grain. Fast films, such as ASA400, \
      have a lot of grain due to less light. Different negative stocks, such \
      as that used in old 8mm film, have poor resolution so the grains are large, \
      but most modern negative stocks have very fine random grain patterns. \
      Low light levels at night or in darkness exhibit more grain for the same \
      reasons."),
      IDS_FILMGRAIN, f_filmgrainpresets, NUMELEMENTS(f_filmgrainpresets), IDL_FILMGRAIN, 0, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLEALWAYS, PropertyInfo::CONSTANT|PropertyInfo::NOTIFYANIMOBJECTVALUECHANGED );
      static FloatPropertyInfo   f_filmgrainsizeinfo(
         0, DOC("The size of the grain as a percentage of the width of the negative."), IDS_SIZE,               IDL_FILMGRAINSIZE,   0, 0, 0,   1, 100, PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLESOMETIMES, PropertyInfo::CONSTANT );
      static PercentPropertyInfo f_filmgrainamountinfo(
         1, DOC("Sets the intensity of the grain, making more or less apparent."), IDS_AMOUNT,             IDL_FILMGRAINAMOUNT, .01f, .01f, 1,     PropertyInfo::DRAWNEVER, PropertyInfo::VISIBLESOMETIMES, PropertyInfo::CONSTANT );
*/

BOOL CPostApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");


    CString string;
    // New Infos here
    m_styletypes.SetArraySize(NUM_STYLES);
    m_styletypes[STYLE_100ASA]->SetMatchName("100ASA");
    string.LoadString(IDS_100ASA);
    m_styletypes[STYLE_100ASA]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_200ASA]->SetMatchName("200ASA");
    string.LoadString(IDS_200ASA);
    m_styletypes[STYLE_200ASA]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_400ASA]->SetMatchName("400ASA");
    string.LoadString(IDS_400ASA);
    m_styletypes[STYLE_400ASA]->SetLocalizedName(string.GetBuffer());
    m_styletypes[STYLE_CUSTOM]->SetMatchName("Custom");
    string.LoadString(IDS_CUSTOM);
    m_styletypes[STYLE_CUSTOM]->SetLocalizedName(string.GetBuffer());

    string.LoadString(IDS_STYLE);
    m_styleinfo = HTypePropertyInfo::New(string, "Style", &m_styletypes);
    m_styleinfo->SetDefaultIndex(STYLE_100ASA);

    string.LoadString(IDS_SIZE);
    m_sizeinfo = HPercentPropertyInfo::New(string, "Size");
    m_sizeinfo->SetDefaultValue(FILMGRAINSIZE100ASA);
    m_sizeinfo->SetMinValue(0.F);
    m_sizeinfo->SetMaxValue(1.F);
    m_sizeinfo->SetConstant(TRUE);

    string.LoadString(IDS_AMOUNT);
    m_amountinfo = HPercentPropertyInfo::New(string, "Amount");
    m_amountinfo->SetDefaultValue(FILMGRAINAMOUNT100ASA);
    m_amountinfo->SetMinValue(0.F);
    m_amountinfo->SetMaxValue(1.F);
    m_amountinfo->SetConstant(TRUE);

    return CPluginApp::InitInstance();
}

int CPostApp::ExitInstance() {
    // Delete Infos Here
    delete m_sizeinfo;
    delete m_amountinfo;
    delete m_styleinfo;

    return CPluginApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostApp object

CPostApp theApp;

CPostApp &GetApp() {
    return theApp;
}
