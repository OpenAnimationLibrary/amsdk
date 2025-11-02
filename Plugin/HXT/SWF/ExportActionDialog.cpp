// Dan  12/28/00  \Dan90\Plugin\HXT\KFM\ExportActionDialog.cpp
// ZPiDER 2001-11 http://www.kci-group.com/z
// ZPiDER 2002-08 http://www.kci-group.com/z

#include "StdAfx.h"
#include "Hxt.h"
#include "ExportActionDialog.h"
#include "F_Protos.h"

#include "SDK/HAction.h"
#include "SDK/Misc.h"
#include "SDK/HChor.h"
#include "SDK/HCamera.h"

/*IMPLEMENT_DYNAMIC(CExportActionDialog, CDialog)*/

UINT regKeyDD = 0;
CHxtApp *application;

/*
// rewrites for registry interaction, because A:M 9.0r GET - functions dont work

// http://www.microsoft.com/mobile/developer/technicalarticles/registry.asp
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wceobjst/htm/cerefregopenkeyex.asp (win ce)
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/sysinfo/regapi_7fuh.asp
// http://tikitak.narod.ru/using/07/part07.htm#Heading12

String GetRegistryString( const String &section, const String &entry, const String &defaultstring )
{
   HKEY key;
   String ret = defaultstring.buf;

   if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\kci:dnd\\am2swf"), 0, KEY_QUERY_VALUE, &key) == 0)
   {
      DWORD dsize = 200;
      TCHAR szBuf[200];

      DWORD err = RegQueryValueEx(key, TEXT(entry.buf), nullptr, nullptr, (LPBYTE)szBuf, &dsize);

      RegCloseKey(key);

      if (err == 0) ret = String(szBuf);
   }
   return ret;
}

float  GetRegistryValue( const String &section, const String &entry, float defaultvalue )
{
   String val = GetRegistryString(section, entry, String(defaultvalue).buf);
   return atof_replace(val.buf);
}

int  GetRegistryValue( const String &section, const String &entry, int defaultvalue )
{
   String val = GetRegistryString(section, entry, String(defaultvalue).buf);
   return atoi_replace(val.buf);
}

BOOL SetRegistryString( const String &section, const String &entry, const String &string )
{
   HKEY key;
   RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\kci:dnd\\am2swf"), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &key, nullptr);
   LRESULT lResult = RegSetValueEx(key, TEXT(entry.buf), 0, REG_SZ, (LPBYTE)string.buf, string.length());
   RegCloseKey(key);
   return TRUE;
}

BOOL SetRegistryValue( const String &section, const String &entry, int tvalue )
{
   return SetRegistryString(section, entry, String(tvalue));
}

BOOL SetRegistryValue( const String &section, const String &entry, float value )
{
   return SetRegistryString(section, entry, String(value));
}
*/
////////////////////////////

CExportActionDialog::CExportActionDialog(const String &filename, HChor *chor, CHxtApp *app): CPluginDialog(IDD, FromHandle(GetMainApplicationWnd())), m_RegOK(true) {
    application = app;

    m_chor = chor;

    const String path = GetRegistryString("SWF Plugin", "File Path", ".");
    m_filename = filename.GetNameOnlyWithoutSuffix() + ".SWF";
    m_filename = CombineNameToPath(path, m_filename);
    m_subtype = GetRegistryValue("SWF Plugin", "Sub Type", 0);

    m_style_outline_color = GetRegistryValue("SWF Plugin", "Style Outline Color", 0); // default = black
    m_style_outline_col.SetBkColor(m_style_outline_color);
    m_style_outline_thickness = GetRegistryValue("SWF Plugin", "Style Outline Thickness", 20);

    m_frame_range = GetRegistryValue("SWF Plugin", "Frame Range", 1);
    m_frame_from = GetRegistryValue("SWF Plugin", "Frame From", 0);
    m_frame_to = GetRegistryValue("SWF Plugin", "Frame To", 10);
    m_frame_stepping = GetRegistryValue("SWF Plugin", "Frame Stepping", 1);

    m_camera_name = GetRegistryString("SWF Plugin", "Camera Name", "Camera1");
    m_cameraindex = GetRegistryValue("SWF Plugin", "Camera Index", 1);
    m_camera_perspective = GetRegistryValue("SWF Plugin", "Camera Perspective", 1);
    m_camera_zero = GetRegistryValue("SWF Plugin", "Camera Zero", 1);

    m_lights_parallel = GetRegistryValue("SWF Plugin", "Lights Parallel", 0);

    m_culling_occlusion = GetRegistryValue("SWF Plugin", "Culling Occlusion", 0);
    m_culling_mapsize = GetRegistryValue("SWF Plugin", "Culling Map Size", 500);
    m_culling_minarea = GetRegistryValue("SWF Plugin", "Culling Minimum Area", 10);
    m_culling_backface = GetRegistryValue("SWF Plugin", "Culling Backface", 1);

    m_flat = GetRegistryValue("SWF Plugin", "Flat Enabled", 0);
    m_flat_spec = GetRegistryValue("SWF Plugin", "Flat Specularity Enabled", 0);
    m_flat_minedgelength = GetRegistryValue("SWF Plugin", "Flat Minimum Edge Length", 0);

    m_safe_frame1 = GetRegistryValue("SWF Plugin", "Safe Mode Frame 1", 0);
    m_safe_all = GetRegistryValue("SWF Plugin", "Safe Mode All Frames", 0);

    m_preview_frame = GetRegistryValue("SWF Plugin", "Preview Frame", 0);
    m_preview = FALSE;

    //{{AFX_DATA_INIT(CExportActionDialog)
    //}}AFX_DATA_INIT
}

CDataExchange *lastpDX = nullptr;

void CExportActionDialog::DoDataExchange(CDataExchange *pDX) {
    lastpDX = pDX;

    CPluginDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CExportActionDialog)

    DDX_Radio(pDX, IDC_SUB1, m_subtype);

    // Frame Range

    DDX_Check(pDX, IDC_FRAME_RANGE, m_frame_range);

    DDX_Text(pDX, IDC_FRAME_FROM, m_frame_from);
    DDV_MinMaxInt(pDX, m_frame_from, 0, 10000);

    DDX_Text(pDX, IDC_FRAME_TO, m_frame_to);
    DDV_MinMaxInt(pDX, m_frame_to, 0, 10000);

    DDX_Text(pDX, IDC_FRAME_STEPPING, m_frame_stepping);
    DDV_MinMaxInt(pDX, m_frame_stepping, -10000, 10000);

    // Outline

    DDX_Control(pDX, IDST_STYLE_OUTLINE_COL, m_style_outline_col);

    DDX_Text(pDX, IDC_STYLE_OUTLINE_THICKNESS, m_style_outline_thickness);
    DDV_MinMaxFloat(pDX, m_style_outline_thickness, 0.F, 2000.0F);

    // Camera
    DDX_CBIndex(pDX, IDC_CAMERA_COMBO, m_cameraindex);
    DDX_Text(pDX, IDC_CAMERA_NAME, m_camera_name);
    DDX_Check(pDX, IDC_CAMERA_PERSPECTIVE, m_camera_perspective);
    DDX_Check(pDX, IDC_CAMERA_ZERO, m_camera_zero);

    // Lights

    DDX_Check(pDX, IDC_LIGHTS_PARALLEL, m_lights_parallel);

    // Culling

    DDX_Check(pDX, IDC_CULLING_OCCLUSION, m_culling_occlusion);

    DDX_Text(pDX, IDC_CULLING_MAPSIZE, m_culling_mapsize);
    DDV_MinMaxInt(pDX, m_culling_mapsize, 10, 10000);

    DDX_Text(pDX, IDC_CULLING_MINAREA, m_culling_minarea);
    DDV_MinMaxInt(pDX, m_culling_mapsize, 0, 10000);

    DDX_Check(pDX, IDC_CULLING_BACKFACE, m_culling_backface);

    // Flat

    DDX_Check(pDX, IDC_FLAT, m_flat);

    DDX_Check(pDX, IDC_FLAT_SPEC, m_flat_spec);

    DDX_Text(pDX, IDC_FLAT_MINEDGELENGTH, m_flat_minedgelength);
    DDV_MinMaxFloat(pDX, m_flat_minedgelength, 0.F, 2000.0F);

    // Safe Mode

    DDX_Check(pDX, IDC_SAFE_FRAME1, m_safe_frame1);
    DDX_Check(pDX, IDC_SAFE_ALL, m_safe_all);

    // Preview

    DDX_Text(pDX, IDC_PREVIEW_FRAME, m_preview_frame);
    DDV_MinMaxInt(pDX, m_preview_frame, 0, 10000);

    // RegKey

    DDX_Text(pDX, IDC_REGKEY, regKeyDD);

    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportActionDialog, CDialog)ON_BN_CLICKED(IDC_BROWSE, &CExportActionDialog::OnBrowse) ON_BN_CLICKED(IDC_PREVIEW, &CExportActionDialog::OnPreview) ON_BN_CLICKED(IDC_FRAME_RANGE, &CExportActionDialog::OnFrameRange) ON_BN_CLICKED(IDC_STYLE_OUTLINE_PICK, &CExportActionDialog::OnStyleOutlinePick)END_MESSAGE_MAP()

BOOL CExportActionDialog::OnInitDialog() {
    GetDlgItem(IDC_EDIT1)->SetWindowText("");

    //	if (m_RegOK)
    //	{
    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());

    //		GetDlgItem(IDC_FILENAME)->SetWindowText(m_filename.GetAbbreviated(dlgitem).Get());

    GetDlgItem(IDC_REGKEY)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_REGKEYG)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_PREVIEWG)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_PREVIEW)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_PREVIEW_FRAME)->ShowWindow(SW_HIDE);

    int m_frame_range_custom = 1;
    if (m_frame_range == 1) {
        m_frame_range_custom = 0;
    }

    GetDlgItem(IDC_FRAME_FROM)->EnableWindow(m_frame_range_custom);
    GetDlgItem(IDC_FRAME_TO)->EnableWindow(m_frame_range_custom);
    GetDlgItem(IDC_FRAME_STEPPING)->EnableWindow(m_frame_range_custom);

    auto *startmethodcombo = (CComboBox *)GetDlgItem(IDC_CAMERA_COMBO);
    //AFX_MANAGE_STATE(AfxGetStaticModuleState())
    startmethodcombo->AddString("None"); //GRS GetResourceString(IDS_NONE).Get() ); //not finding it for some dumb reason.
    HCamera *camera = m_chor->GetChildCamera();
    int numcameras = 0;
    while (camera) {
        String name = camera->GetName();
        name.Replace("Shortcut to ", "ScTo ");
        startmethodcombo->AddString(name.Get());
        camera = camera->GetNextCameraInChor();
        numcameras++;
    }
    startmethodcombo->SetCurSel(MIN(numcameras, m_cameraindex));
    /*	}
       else
       {
          GetDlgItem(IDC_FILENAME)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_BROWSE)->ShowWindow(SW_HIDE);
    
          CWnd *wnd = GetDlgItem(IDC_SUB1);
          ASSERT(wnd);
          if (wnd)      
             wnd->ShowWindow(SW_HIDE);
          wnd = GetDlgItem(IDC_SUB4);
          ASSERT(wnd);
          if (wnd)      
             wnd->ShowWindow(SW_HIDE);
          wnd = GetDlgItem(IDC_SUB16);
          ASSERT(wnd);
          if (wnd)      
             wnd->ShowWindow(SW_HIDE);
          wnd = GetDlgItem(IDC_SUBVARIABLE);
          ASSERT(wnd);
          if (wnd)      
             wnd->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDC_FRAME_RANGE)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_FRAME_FROM)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_FRAME_TO)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_FRAME_STEPPING)->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDC_CAMERA_NAME)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_CAMERA_PERSPECTIVE)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_CAMERA_ZERO)->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDC_LIGHTS_PARALLEL)->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDST_STYLE_OUTLINE_COL)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_STYLE_OUTLINE_PICK)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_STYLE_OUTLINE_THICKNESS)->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDC_CULLING_OCCLUSION)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_CULLING_MAPSIZE)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_CULLING_MINAREA)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_CULLING_BACKFACE)->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDC_FLAT)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_FLAT_SPEC)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_FLAT_MINEDGELENGTH)->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDC_SAFE_FRAME1)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_SAFE_ALL)->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDC_G10)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_G11)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_G12)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_G13)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_G14)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_G15)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_G16)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_G17)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_G18)->ShowWindow(SW_HIDE);
    
          GetDlgItem(IDC_PREVIEWG)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_PREVIEW)->ShowWindow(SW_HIDE);
          GetDlgItem(IDC_PREVIEW_FRAME)->ShowWindow(SW_HIDE);
       }*/

    CPluginDialog::OnInitDialog();

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CExportActionDialog message handlers

/*
String thisRegDD = String("SOFTWARE\\kci:dnd\\am2swf");

void RegStoreDD(String keyname, String value)
{
   HKEY key;
   RegCreateKeyEx(HKEY_LOCAL_MACHINE, TEXT(thisRegDD.buf), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &key, nullptr);
   LRESULT lResult = RegSetValueEx(key, TEXT(keyname.buf), 0, REG_SZ, (LPBYTE)value.buf, value.length());
   RegCloseKey(key);
}
*/

void CExportActionDialog::OnOK() {
    CPluginDialog::OnOK();

    const String path = m_filename.GetPathOnly();
    SetRegistryString("SWF Plugin", "File Path", path);
    SetRegistryValue("SWF Plugin", "Sub Type", m_subtype);

    SetRegistryValue("SWF Plugin", "Style Outline Color", (int)m_style_outline_color);
    SetRegistryValue("SWF Plugin", "Style Outline Thickness", (float)m_style_outline_thickness);

    SetRegistryValue("SWF Plugin", "Frame Range", m_frame_range);
    SetRegistryValue("SWF Plugin", "Frame From", m_frame_from);
    SetRegistryValue("SWF Plugin", "Frame To", m_frame_to);
    SetRegistryValue("SWF Plugin", "Frame Stepping", m_frame_stepping);

    SetRegistryString("SWF Plugin", "Camera Name", m_camera_name);
    SetRegistryValue("SWF Plugin", "Camera Index", m_cameraindex);
    SetRegistryValue("SWF Plugin", "Camera Perspective", m_camera_perspective);
    SetRegistryValue("SWF Plugin", "Camera Zero", m_camera_zero);

    SetRegistryValue("SWF Plugin", "Lights Parallel", m_lights_parallel);

    SetRegistryValue("SWF Plugin", "Culling Occlusion", m_culling_occlusion);
    SetRegistryValue("SWF Plugin", "Culling Map Size", m_culling_mapsize);
    SetRegistryValue("SWF Plugin", "Culling Minimum Area", m_culling_minarea);
    SetRegistryValue("SWF Plugin", "Culling Backface", m_culling_backface);

    SetRegistryValue("SWF Plugin", "Flat Enabled", m_flat);
    SetRegistryValue("SWF Plugin", "Flat Specularity Enabled", m_flat_spec);
    SetRegistryValue("SWF Plugin", "Flat Minimum Edge Length", m_flat_minedgelength);

    SetRegistryValue("SWF Plugin", "Safe Mode Frame 1", m_safe_frame1);
    SetRegistryValue("SWF Plugin", "Safe Mode All", m_safe_all);

    SetRegistryValue("SWF Plugin", "Preview Frame", m_preview_frame);

    /*
       if (!m_RegOK)
       {
          RegStoreDD(String("RegKey"), regKeyDD);
       }
    */
}

void CExportActionDialog::OnBrowse() {
    // get title and filters string from resources
    CString filters, title;
    title.LoadString(IDS_EXPORTTITLE);
    filters.LoadString(IDS_FILEFILTERS);

    const String ext("SWF");
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!SaveRequest(title, filters, m_filename, ext.Get(), ext.Get()))
            return;
    }
    CWnd *dlgitem = GetDlgItem(IDC_FILENAME);

    const String text = m_filename.GetAbbreviated(dlgitem);
    dlgitem->SetWindowText(text.Get());
}

void CExportActionDialog::OnPreview() {
    //AfxMessageBox(TEXT("preview"), MB_OK|MB_ICONSTOP, 0);

    m_preview = TRUE;
    OnOK();
}

void CExportActionDialog::OnStyleOutlinePick() {
    CColorDialog dlg(m_style_outline_color, CC_FULLOPEN | CC_ANYCOLOR, this);

    if (dlg.DoModal() == IDOK)
        m_style_outline_color = dlg.GetColor();

    m_style_outline_col.SetBkColor(m_style_outline_color);
}

void CExportActionDialog::OnFrameRange() {
    m_frame_range = IsDlgButtonChecked(IDC_FRAME_RANGE);
    int m_frame_range_custom = 1;
    if (m_frame_range == 1) {
        m_frame_range_custom = 0;
    }
    GetDlgItem(IDC_FRAME_FROM)->EnableWindow(m_frame_range_custom);
    GetDlgItem(IDC_FRAME_TO)->EnableWindow(m_frame_range_custom);
    GetDlgItem(IDC_FRAME_STEPPING)->EnableWindow(m_frame_range_custom);
}
