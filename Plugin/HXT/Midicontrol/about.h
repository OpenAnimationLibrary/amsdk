#if !defined(AFX_ABOUT_H__4B509261_981D_4551_B19E_7D383F6E81DD__INCLUDED_)
#define AFX_ABOUT_H__4B509261_981D_4551_B19E_7D383F6E81DD__INCLUDED_

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// about.h : Header-Datei
//

#include "resource.h"
#include "midicontrol.h"
//#include "HashFile.h"
//#include "SDK/misc.h"

#define pname "midicontrol.hxt"
#define vnummer "0.4b"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld about 

class about : public CPluginDialog
{
// Konstruktion
public:

	about(HWND pParent = nullptr);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(about)
	enum { IDD = IDD_DIALOG21 };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(about)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(about)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#undef AFX_DATA
#define AFX_DATA

#endif // AFX_ABOUT_H__4B509261_981D_4551_B19E_7D383F6E81DD__INCLUDED_
