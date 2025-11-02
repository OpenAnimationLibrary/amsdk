// Yves Poissant  2004/03/21  \My Plugins\Shaders\WardAnisotropic\Shader.cpp
//

#include "StdAfx.h"
#include "StrClass.h"
#include "Shader.h"
#include "F_Protos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
[[maybe_unused]] static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShaderApp

BEGIN_MESSAGE_MAP(CShaderApp, CWinApp)
    //{{AFX_MSG_MAP(CShaderApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardApp construction

CShaderApp::CShaderApp(): m_MaterialInfo{nullptr}, m_RoughnessXInfo{nullptr}, m_RoughnessYInfo{nullptr}, m_AlignmentInfo{nullptr}, m_IsIsotropicInfo{nullptr}, m_IsBRDFInfo{nullptr},
                          m_AxisBoneInfo{nullptr} {}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShaderApp object

CShaderApp theApp;

BOOL CShaderApp::InitInstance() {
    SetRegistryKey("Hash, Inc.");
    free((void *)m_pszProfileName);
    m_pszProfileName = _tcsdup("AM Plugins");

    CString string;

    HTypeInfo *typeinfo;
    // Anisotropy presets
    m_MaterialInfoArray.SetArraySize(NPRESETS);
    for (int i = 0; i < NPRESETS; ++i) {
        typeinfo = m_MaterialInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("RolledBrass");
                string.LoadString(IDS_N_ROLLEDBRASS);
                break;
            case 1:
                typeinfo->SetMatchName("RolledAluminum");
                string.LoadString(IDS_N_ROLLEDALUMINUM);
                break;
            case 2:
                typeinfo->SetMatchName("LightlyBrushedAluminum");
                string.LoadString(IDS_N_LIGHTLYBRUSHEDALUMINUM);
                break;
            case 3:
                typeinfo->SetMatchName("VarnishedPlywood");
                string.LoadString(IDS_N_VARNISHEDPLYWOOD);
                break;
            case 4:
                typeinfo->SetMatchName("EnamelFinishedMetal");
                string.LoadString(IDS_N_ENAMELFINISHEDMETAL);
                break;
            case 5:
                typeinfo->SetMatchName("PaintedCardboardBox");
                string.LoadString(IDS_N_PAINTEDCARDBOARDBOX);
                break;
            case 6:
                typeinfo->SetMatchName("BrushedLatexSemiGlossMetal");
                string.LoadString(IDS_N_BRUSHEDLATEXSEMIGLOSSMETAL);
                break;
            case 7:
                typeinfo->SetMatchName("BrushedLatexSemiGlossSheetrock");
                string.LoadString(IDS_N_BRUSHEDLATEXSEMIGLOSSSHEETROCK);
                break;
            case 8:
                typeinfo->SetMatchName("BrushedLatexSemiGlossWood");
                string.LoadString(IDS_N_BRUSHEDLATEXSEMIGLOSSWOOD);
                break;
            case 9:
                typeinfo->SetMatchName("BrushedLatexGlossMetal");
                string.LoadString(IDS_N_BRUSHEDLATEXGLOSSMETAL);
                break;
            case 10:
                typeinfo->SetMatchName("BrushedLatexGlossSheetrock");
                string.LoadString(IDS_N_BRUSHEDLATEXGLOSSSHEETROCK);
                break;
            case 11:
                typeinfo->SetMatchName("BrushedLatexGlossWood");
                string.LoadString(IDS_N_BRUSHEDLATEXGLOSSWOOD);
                break;
            case 12:
                typeinfo->SetMatchName("RolledLatexSemiGlossMetal");
                string.LoadString(IDS_N_ROLLEDLATEXSEMIGLOSSMETAL);
                break;
            case 13:
                typeinfo->SetMatchName("RolledLatexSemiGlossSheetrock");
                string.LoadString(IDS_N_ROLLEDLATEXSEMIGLOSSSHEETROCK);
                break;
            case 14:
                typeinfo->SetMatchName("RolledLatexSemiGlossWood");
                string.LoadString(IDS_N_ROLLEDLATEXSEMIGLOSSWOOD);
                break;
            case 15:
                typeinfo->SetMatchName("RolledLatexGlossMetal");
                string.LoadString(IDS_N_ROLLEDLATEXGLOSSMETAL);
                break;
            case 16:
                typeinfo->SetMatchName("RolledLatexGlossSheetrock");
                string.LoadString(IDS_N_ROLLEDLATEXGLOSSSHEETROCK);
                break;
            case 17:
                typeinfo->SetMatchName("RolledLatexGlossWood");
                string.LoadString(IDS_N_ROLLEDLATEXGLOSSWOOD);
                break;
            case 18:
                typeinfo->SetMatchName("SprayedLatexSemiGlossMetal");
                string.LoadString(IDS_N_SPRAYEDLATEXSEMIGLOSSMETAL);
                break;
            case 19:
                typeinfo->SetMatchName("SprayedLatexSemiGlossSheetrock");
                string.LoadString(IDS_N_SPRAYEDLATEXSEMIGLOSSSHEETROCK);
                break;
            case 20:
                typeinfo->SetMatchName("SprayedLatexSemiGlossWood");
                string.LoadString(IDS_N_SPRAYEDLATEXSEMIGLOSSWOOD);
                break;
            case 21:
                typeinfo->SetMatchName("SprayedLatexGlossMetal");
                string.LoadString(IDS_N_SPRAYEDLATEXGLOSSMETAL);
                break;
            case 22:
                typeinfo->SetMatchName("SprayedLatexGlossSheetrock");
                string.LoadString(IDS_N_SPRAYEDLATEXGLOSSSHEETROCK);
                break;
            case 23:
                typeinfo->SetMatchName("SprayedLatexGlossWood");
                string.LoadString(IDS_N_SPRAYEDLATEXGLOSSWOOD);
                break;
            case 24:
                typeinfo->SetMatchName("CeramicTile");
                string.LoadString(IDS_N_CERAMICTILE);
                break;
            case 25:
                typeinfo->SetMatchName("GlossyPaper");
                string.LoadString(IDS_N_GLOSSYPAPER);
                break;
            case 26:
                typeinfo->SetMatchName("ComputerPlastic");
                string.LoadString(IDS_N_COMPUTERPLASTIC);
                break;
            case 27:
                typeinfo->SetMatchName("PlasticLaminate");
                string.LoadString(IDS_N_PLASTICLAMINATE);
                break;
            case 28:
                typeinfo->SetMatchName("Custom");
                string.LoadString(IDS_N_CUSTOM);
                break;
            case 29:
                typeinfo->SetMatchName("SpecularityBased");
                string.LoadString(IDS_N_SPECULARITYBASED);
                break;
            default: 
                break;
        }
        typeinfo->SetLocalizedName((String)string);
    }
    string.LoadString(IDS_MATERIAL);
    m_MaterialInfo = HTypePropertyInfo::New(string, "MaterialAnisotropy", &m_MaterialInfoArray);
    m_MaterialInfo->SetDefaultIndex(GetRegistryValue(TRUE, "Ward SHD", "Material", 20));

    string.LoadString(IDS_ROUGHNESSX);
    m_RoughnessXInfo = HPercentPropertyInfo::New(string, "Roughness X");
    m_RoughnessXInfo->SetDefaultValue(GetRegistryValue(TRUE, "Ward SHD", "RoughX", 0.099f));
    m_RoughnessXInfo->SetMinValue(0.01f);
    m_RoughnessXInfo->SetMaxValue(100.F);

    string.LoadString(IDS_ROUGHNESSY);
    m_RoughnessYInfo = HPercentPropertyInfo::New(string, "Roughness Y");
    m_RoughnessYInfo->SetDefaultValue(GetRegistryValue(TRUE, "Ward SHD", "RoughY", 0.26f));
    m_RoughnessYInfo->SetMinValue(0.01f);
    m_RoughnessYInfo->SetMaxValue(100.F);

    // Types of Tangent orientations
    m_AlignmentInfoArray.SetArraySize(3);
    for (int i = 0; i < 3; ++i) {
        typeinfo = m_AlignmentInfoArray[i];
        switch (i) {
            case 0:
                typeinfo->SetMatchName("Tangent Vector");
                string.LoadString(IDS_N_TANGENTVECT);
                break;
            case 1:
                typeinfo->SetMatchName("Up Vector");
                string.LoadString(IDS_N_UPVECT);
                break;
            case 2:
                typeinfo->SetMatchName("Axis Vector");
                string.LoadString(IDS_N_AXISVECT);
                break;
            default: 
                break;
        }
        typeinfo->SetLocalizedName((String)string);
    }
    string.LoadString(IDS_ALIGNMENT);
    m_AlignmentInfo = HTypePropertyInfo::New(string, "TangentAlignment", &m_AlignmentInfoArray);
    m_AlignmentInfo->SetDefaultIndex(GetRegistryValue(TRUE, "Ward SHD", "Alignment", 0));

    string.LoadString(IDS_ISISOTROPIC);
    m_IsIsotropicInfo = HBoolPropertyInfo::New(string, "IsIsotropic");
    m_IsIsotropicInfo->SetDefaultValue(GetRegistryValue(TRUE, "Ward SHD", "IsIsotropic", FALSE));

    string.LoadString(IDS_ISBRDF);
    m_IsBRDFInfo = HBoolPropertyInfo::New(string, "IsBRDF");
    m_IsBRDFInfo->SetDefaultValue(GetRegistryValue(TRUE, "Ward SHD", "IsBRDF", FALSE));

    string.LoadString(IDS_AXISBONE);
    m_AxisBoneInfo = HPointerPropertyInfo::New(string, "BoneAxis");

    return CPluginApp::InitInstance();
}

int CShaderApp::ExitInstance() {
    delete m_MaterialInfo;
    delete m_RoughnessXInfo;
    delete m_RoughnessYInfo;
    delete m_AlignmentInfo;
    delete m_IsIsotropicInfo;
    delete m_IsBRDFInfo;
    delete m_AxisBoneInfo;
    return CPluginApp::ExitInstance();
}

CShaderApp &GetApp() {
    return theApp;
}
