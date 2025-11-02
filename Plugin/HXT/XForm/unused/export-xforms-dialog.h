#pragma once
#include "StdAfx.h"
#include "F_Protos.h"
#include "MapLimit.h"
#include "SDK/HModel.h"
#include "SDK/Misc.h"
#include "IEModel.h"

class CExportXformsDialog : public CPluginDialog
{
  // Construction
public:
  CExportXformsDialog() {}   // standard constructor
  CExportXformsDialog(const String &filename);

  // Dialog Data
  String m_filename;

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CExportModelDialog)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
                                                      //}}AFX_VIRTUAL

                                                      // Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CExportModelDialog)
  virtual void OnOK();
  virtual BOOL OnInitDialog();
  afx_msg void OnBrowse();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
