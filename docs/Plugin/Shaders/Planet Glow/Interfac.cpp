// KB  6/8/00  \Ken85\Plugin\Shaders\Phong\Interfac.cpp

#include "StdAfx.h"
#include "Custom.h"

BOOL CustomShader::OnCommand( HWND hwnddlg, UINT id )
{
   CDialog *dialog = (CDialog *)CWnd::FromHandle( hwnddlg );
   char text[255];

   switch (id) {
   case IDC_FALLOFF:
      dialog->GetDlgItemText( id, text, 255 );
      m_falloff = (float) MIN(100.0f,MAX(0.0f,atof_replace(text)));
      sprintf( text, "%.2f", m_falloff);
      dialog->SetDlgItemText( id, text );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(id+1))->SetPos((int)m_falloff);
		m_falloff /= 100.0f;
		NormalizeFallOff();
      return TRUE;

   case IDC_GLOW:
      dialog->GetDlgItemText( id, text, 255 );
      m_glow = atof_replace(text);
      sprintf( text, "%.2f", m_glow);
      dialog->SetDlgItemText( id, text );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(id+1))->SetPos((int) m_glow);
		m_glow /= 100.0f;
      return TRUE;

   case IDC_FADE:
      dialog->GetDlgItemText( id, text, 255 );
      m_fade = atof_replace(text);
      sprintf( text, "%.2f", m_fade);
      dialog->SetDlgItemText( id, text );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(id+1))->SetPos((int) (m_fade));
		m_fade /= 100.0f;
      return TRUE;

   case IDC_XPARENCY:
      dialog->GetDlgItemText( id, text, 255 );
      m_xparency = atof_replace(text);
      sprintf( text, "%.2f", m_xparency);
      dialog->SetDlgItemText( id, text );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(id+1))->SetPos((int) (m_xparency));
		m_xparency /= 100.0f;
      return TRUE;

	case IDC_HI_COLOR:
		m_hiColor = m_hiColorBtn->GetColor();
		return TRUE;

	case IDC_LOW_COLOR:
		m_lowColor = m_lowColorBtn->GetColor();
		return TRUE;
	}
   return FALSE;
}

void CustomShader::InitPropertyPage( HWND hwnddlg, UINT dialogid, BOOL instance )
{
   CDialog *dialog = (CDialog *)CWnd::FromHandle(hwnddlg);

   if (dialogid == IDD_ATTRIBUTES_PAGE) {
      ((CSpinButtonCtrl *)dialog->GetDlgItem(IDC_FALLOFF_SPIN))->SetRange( 0, 100 );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(IDC_GLOW_SPIN))->SetRange( 0, 1000 );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(IDC_FADE_SPIN))->SetRange( 0, 1000 );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(IDC_XPARENCY_SPIN))->SetRange( 0, 100 );
		m_lowColorBtn = (HashColorBtn*) new HashColorBtn(IDC_LOW_COLOR);
		m_hiColorBtn = (HashColorBtn*) new HashColorBtn(IDC_HI_COLOR);
	}
}

void CustomShader::RefreshPropertyPage( HWND hwnddlg, UINT dialogidtoupdate, BOOL instance )
{
   CDialog *dialog = (CDialog *)CWnd::FromHandle(hwnddlg);

   if (dialogidtoupdate == IDD_ATTRIBUTES_PAGE) {
		char text[255];
		sprintf( text, "%.2f", m_falloff*100.0f );
		dialog->SetDlgItemText( IDC_FALLOFF, text );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(IDC_FALLOFF_SPIN))->SetPos( (int)(m_falloff*100.0f) );
      sprintf( text, "%.2f", m_glow*100.0f);
      dialog->SetDlgItemText( IDC_GLOW, text );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(IDC_GLOW_SPIN))->SetPos((int) (m_glow*100.0f));
      sprintf( text, "%.2f", m_fade*100.0f);
      dialog->SetDlgItemText( IDC_FADE, text );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(IDC_FADE_SPIN))->SetPos((int) (m_fade*100.0f));
      sprintf( text, "%.2f", m_xparency*100.0f);
      dialog->SetDlgItemText( IDC_XPARENCY, text );
      ((CSpinButtonCtrl *)dialog->GetDlgItem(IDC_XPARENCY_SPIN))->SetPos((int) (m_xparency*100.0f));
		m_hiColorBtn->SetColor(m_hiColor);
		m_lowColorBtn->SetColor(m_lowColor);
	}
}

void CustomShader::DoDataExchange(CDialog *dialog, CDataExchange* pDX)
{

}


void CustomShader::EnableControls()
{

}

BOOL CustomShader::OnInitDialog(CDialog *dialog)
{
   return FALSE;
}

