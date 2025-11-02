#include "export-xforms-dialog.h"

CExportXformsDialog::CExportXformsDialog(const String &filename)
  : CPluginDialog(CExportXformsDialog::IDD, CWnd::FromHandle(GetMainApplicationWnd()))
{
  String path = GetRegistryString("Export Transforms Plugin", "File Path", ".");
  m_filename = filename.GetNameOnlyWithoutSuffix() + ".xforms";
  m_filename = CombineNameToPath(path, m_filename);

  //{{AFX_DATA_INIT(CExportModelDialog)
  //}}AFX_DATA_INIT
}

void CExportXformsDialog::OnOK()
{
  CDialog::OnOK();
  String path = m_filename.GetPathOnly();
  SetRegistryString("Export Transforms Plugin", "File Path", path);
}

void CExportXformsDialog::OnBrowse()
{
  CString filters, title;
  title.LoadString(IDS_EXPORTTITLE);
  filters.LoadString(IDS_FILEFILTERS);

  String ext("Transforms");
  {
    AFX_MANAGE_STATE(AfxGetAppModuleState());
    if (!SaveRequest((LPCTSTR)title, (LPCTSTR)filters, m_filename, ext.Get(), ext.Get()))
      return;
  }

  CWnd *dlgitem = GetDlgItem(IDC_FILENAME);
  String text;
  text = m_filename.GetAbbreviated(dlgitem);
  dlgitem->SetWindowText(text.Get());
}
