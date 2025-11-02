// KB  1/18/05  \Plugin\HXT\Duplicator\DupDialog.h

#ifndef __DUPDIALOG_H
#define __DUPDIALOG_H
// DupDialog.h : header file
//
#include "SDK/Misc.h"
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDupDialog dialog

class DupParameters;
class CDupDialog : public CPluginDialog
{
// Construction
public:
	DupParameters *m_parameters;

	CDupDialog(){};   // standard constructor
	CDupDialog(DupParameters *parameters);

// Dialog Data
	//{{AFX_DATA(CDupDialog)
	enum { IDD = IDD_DUP };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDupDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDupDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //DUPDIALOG_H
