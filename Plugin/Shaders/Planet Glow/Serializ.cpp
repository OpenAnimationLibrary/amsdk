// KB  4/26/00  \Ken85\Plugin\Shaders\Phong\Serializ.cpp

#include "StdAfx.h"
#include "Custom.h"

BOOL CustomShader::Save(char *&label, char *&value, int count)
{
   static char text[255];
	switch (count) {
	case 0:
		label = "PlanetFallOff";
		sprintf( text, "%.2f", m_falloff );
      value = text;
		return TRUE;

	case 1:
		label = "PlanetGlow";
		sprintf( text, "%.2f", m_glow );
      value = text;
		return TRUE;

	case 2:
		label = "PlanetFade";
		sprintf( text, "%.2f", m_fade );
      value = text;
		return TRUE;

	case 3:
		label = "PlanetTransparency";
		sprintf( text, "%.2f", m_xparency );
      value = text;
		return TRUE;

	case 4:
		label = "PlanetHiColor";
		sprintf( text, "%.2f %.2f %.2f", m_hiColor.red, m_hiColor.green, m_hiColor.blue );
      value = text;
		return TRUE;

	case 5:
		label = "PlanetLowColor";
		sprintf( text, "%.2f %.2f %.2f", m_lowColor.red, m_lowColor.green, m_lowColor.blue );
      value = text;
		return TRUE;
	}
   return FALSE;
}

BOOL CustomShader::ParseArg( const char *label, const char *value )
{
	if (strcmp(label, "PlanetFallOff") == 0) {
	   sscanf( value, "%f", &m_falloff );
		NormalizeFallOff();
	   return TRUE;
	}
	if (strcmp(label, "PlanetGlow") == 0) {
	   sscanf( value, "%f", &m_glow );
	   return TRUE;
	}
	if (strcmp(label, "PlanetFade") == 0) {
	   sscanf( value, "%f", &m_fade );
	   return TRUE;
	}
	if (strcmp(label, "PlanetTransparency") == 0) {
	   sscanf( value, "%f", &m_xparency );
	   return TRUE;
	}
	if (strcmp(label, "PlanetHiColor") == 0) {
	   sscanf( value, "%f %f %f", &m_hiColor.red, &m_hiColor.green, &m_hiColor.blue );
	   return TRUE;
	}
	if (strcmp(label, "PlanetLowColor") == 0) {
	   sscanf( value, "%f %f %f", &m_lowColor.red, &m_lowColor.green, &m_lowColor.blue );
	   return TRUE;
	}
	return FALSE;
}

