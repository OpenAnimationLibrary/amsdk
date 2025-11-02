// ==========================================================================
// CNewLabelTester.cpp
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 20/07/2000
// Last modification : 20/07/2000
// ==========================================================================

// ==========================================================================
// Les Includes
// ==========================================================================

#include "stdafx.h"
#include "CNewLabelTester.h"
#include "CNewLabelTesterDlg.h"
#include "DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ==========================================================================
// Les Fonctions Globales
// ==========================================================================

void SplitCommandLine(LPSTR lpszCmdLine, BOOL &bTestDlg)
 {
  bTestDlg = FALSE;

  char szTemp[512];

  memset(szTemp, 0, sizeof(szTemp));

  for (unsigned int I=0, J=0; I<=strlen(lpszCmdLine); I++)
   {
    if (lpszCmdLine[I] == ' ' || lpszCmdLine[I] == '\0')
     {
      if (strlen(szTemp) > 0)
       {
        char szTempSave[255];

        strcpy(szTempSave, szTemp);

        strupr(szTemp);

        // traitement du paramètre
        if (!strncmp(szTemp,"/TESTDLG",8)) bTestDlg = TRUE;

        J = 0;

        memset(szTemp, 0, sizeof(szTemp));
       }
      else I++;
     }
    else {
          szTemp[J] = lpszCmdLine[I];
          J++;
         }
   }
 }

/////////////////////////////////////////////////////////////////////////////
// CCNewLabelTesterApp

BEGIN_MESSAGE_MAP(CCNewLabelTesterApp, CWinApp)
	//{{AFX_MSG_MAP(CCNewLabelTesterApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCNewLabelTesterApp construction

CCNewLabelTesterApp::CCNewLabelTesterApp()
 {
 }

/////////////////////////////////////////////////////////////////////////////
// The one and only CCNewLabelTesterApp object

CCNewLabelTesterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCNewLabelTesterApp initialization

BOOL CCNewLabelTesterApp::InitInstance()
 {
  #ifdef _AFXDLL
  Enable3dControls();			// Call this when using MFC in a shared DLL
  #else
  Enable3dControlsStatic();	// Call this when linking to MFC statically
  #endif

  BOOL bTestDlg;

  SplitCommandLine(m_lpCmdLine, bTestDlg);

  if (bTestDlg)
   {
    CCNewLabelTesterDlg dlg;
  
    m_pMainWnd = &dlg;
  
    dlg.DoModal();
   }
  else {
        CDemoDlg dlg;
        
        m_pMainWnd = &dlg;

        dlg.DoModal();
       }

  return FALSE;
 }
