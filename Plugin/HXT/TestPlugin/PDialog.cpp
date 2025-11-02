// PDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "TestPlugin.h"
#include "PDialog.h"


// PDialog dialog

//IMPLEMENT_DYNAMIC(PDialog, CDialog)

PDialog::PDialog(PARAMETER *m_para)
	: CPluginDialog(PDialog::IDD, CWnd::FromHandle(GetMainApplicationWnd()))
{
	//{{AFX_DATA_INIT(PDialog)
	para = m_para;
	//}}AFX_DATA_INIT
}

PDialog::~PDialog()
{
}

void PDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
 //  DDX_Text(pDX, IDC_EDIT1, para->neededdistance);
//	DDV_MinMaxFloat(pDX, para->neededdistance, 1e-6f, 1e6f);
 //  DDX_Text(pDX, IDC_EDIT2, para->iteration);
//   DDV_MinMaxInt(pDX, para->iteration, 1, 10000);
 //  DDX_Text(pDX, IDC_EDIT3, para->zcount);
//   DDV_MinMaxInt(pDX, para->zcount, 1, 1000);
 //  DDX_Text(pDX, IDC_EDIT4, para->zvalue);
//	DDV_MinMaxFloat(pDX, para->zvalue, -1000.f, 1000.f);
 //  DDX_Check(pDX, IDC_CHECK1, para->extrude);
 //  DDX_Radio(pDX, IDC_RADIO1, para->direction);
}

BOOL PDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
    /*
   CString temp;
   temp.Format("Spline length %f CP count %i",para->splinelength,para->cpcount);
   SetDlgItemText(IDC_STATIC_LENGTH,temp.GetBuffer());
   if (para->zcount == -1) {
      GetDlgItem(IDC_EDIT3)->ShowWindow(FALSE);
      GetDlgItem(IDC_EDIT4)->ShowWindow(FALSE);
      GetDlgItem(IDC_STATIC_COUNT)->ShowWindow(FALSE);
      GetDlgItem(IDC_STATIC_VALUE)->ShowWindow(FALSE);
      GetDlgItem(IDC_CHECK1)->ShowWindow(FALSE);
      GetDlgItem(IDC_RADIO1)->ShowWindow(FALSE);
      GetDlgItem(IDC_RADIO2)->ShowWindow(FALSE);
      GetDlgItem(IDC_RADIO3)->ShowWindow(FALSE);
      para->zcount = 1;
      UpdateData(false);
   }
   */
   String test = " gjsgsjfgf\r\nhwehrkher\r\nende";
   CEdit *ed = (CEdit *)GetDlgItem(IDC_EDIT5);
   ed->SetWindowText(test.Get());
   return TRUE;
}


BEGIN_MESSAGE_MAP(PDialog, CDialog)
   ON_EN_KILLFOCUS(IDC_EDIT2, &PDialog::OnEnKillfocusEdit2)
   ON_EN_KILLFOCUS(IDC_EDIT1, &PDialog::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// PDialog message handlers


void PDialog::OnEnKillfocusEdit2()
{
//	UpdateData(true);
//   para->neededdistance = para->splinelength/para->iteration;
//	UpdateData(false);
}

void PDialog::OnEnKillfocusEdit1()
{
//	UpdateData(true);
//   para->iteration = RoundValue(para->splinelength/para->neededdistance);
//	UpdateData(false);
}

void PDialog::OnOK() 
{
//    UpdateData(true);
    CEdit *ed = (CEdit *)GetDlgItem(IDC_EDIT5);
    String test ="";
    CString test1;
    int num_lines = ed->GetLineCount();
    for (int i= 0;i<num_lines;++i){
        int len = ed->LineLength(ed->LineIndex(i));
        ed->GetLine(i, test1.GetBuffer(len), len);
        test1.ReleaseBuffer(len);
        test += (String)test1 + "<br>";
    }

    // TODO: Zusıtzliche Pr≥fung hier einf≥gen
//   SetRegistryValue("TestPlugin HXT","distance",para->neededdistance);
//   SetRegistryValue("TestPlugin HXT","extrude count",para->zcount);
//   SetRegistryValue("TestPlugin HXT","extrude distance",para->zvalue);
//   SetRegistryValue("TestPlugin HXT","extruding",para->extrude);
//   SetRegistryValue("TestPlugin HXT","extrude direction",para->direction);
	CDialog::OnOK();
}
