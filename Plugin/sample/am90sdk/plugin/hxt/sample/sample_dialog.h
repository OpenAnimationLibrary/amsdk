#if !defined(AFX_SAMPLE_DIALOG_H__C75991CF_E9D7_4525_8C5E_B4031DB6051D__INCLUDED_)
#define AFX_SAMPLE_DIALOG_H__C75991CF_E9D7_4525_8C5E_B4031DB6051D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sample_dialog.h : Header-Datei

// zu includierende Headerdateien
#include "sample.h"
#include "SDK\Misc.h"
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld sample_dialog 

class sample_dialog : public CDialog
{
// Konstruktion
public:
	sample_dialog(CWnd* pParent = NULL);   // Standardkonstruktor
// Dialogfelddaten
	//{{AFX_DATA(sample_dialog)
	enum { IDD = IDD_DIALOG1 };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(sample_dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(sample_dialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SAMPLE_DIALOG_H__C75991CF_E9D7_4525_8C5E_B4031DB6051D__INCLUDED_
