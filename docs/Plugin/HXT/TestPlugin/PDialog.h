#pragma once
#include  "TestPlugin.h"


// PDialog-Dialogfeld
class PDialog : public CPluginDialog
{
// Konstruktion
public:
	PARAMETER *para;
	PDialog(PARAMETER *para);
	PDialog(CWnd* pParent = nullptr);   // Standardkonstruktor
	virtual ~PDialog();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst³tzung
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnEnKillfocusEdit2();
   afx_msg void OnEnKillfocusEdit1();
};
