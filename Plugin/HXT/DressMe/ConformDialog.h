#if !defined(AFX_CONFORMDIALOG_H__D2438804_D8E6_46DB_9FEA_D656065E3BC1__INCLUDED_)
#define AFX_CONFORMDIALOG_H__D2438804_D8E6_46DB_9FEA_D656065E3BC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CConformDialog.h : header file
//

//AM SDK
#include "Conform.h"
#include "SDK/Misc.h"
#include "resource.h"

//#include "SDK/HAction.h"
//#include "SDK/HChor.h"

/////////////////////////////////////////////////////////////////////////////
// CConformDialog dialog

class CConformDialog final : public CPluginDialog {
    // Construction
public:
    HModel *m_ModelBody; //This is figure. - this will be chosen from the ListBox.
    HModel *m_ModelClothing; //This is clothing. - Where the right click happened.

    HChor *m_Chor;

    CConformDialog(HChor *chor, HModel *model, CWnd *pParent = nullptr); // standard constructor

    struct MODELS {
        HModel *m_Model; //This is for the array of models in the Listbox
        MODELS *next;
    };

    MODELS *m_FirstModel; //Holds address of first in Struct

    int m_iModelCount; //This counts the number of models.

    // Dialog Data
    //{{AFX_DATA(CConformDialog)
    enum { IDD = IDD_CONFORM };

    CListBox m_lstFigure;
    //}}AFX_DATA

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CConformDialog)
protected:
    void DoDataExchange(CDataExchange *pDX) override; // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CConformDialog)
    afx_msg void OnEditchangeFigureToConformTo();
    BOOL OnInitDialog() override;
    void OnOK() override;
    //}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFORM_H__3A6EE968_7482_4FD4_A969_7E44093A154C__INCLUDED_)
