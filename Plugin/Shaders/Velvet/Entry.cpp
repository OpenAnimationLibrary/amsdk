// Dan  3/2/01  \Dan90\Plugin\Shaders\BlinnPhong\Entry.cpp

#include "stdafx.h"
#include "SDK/HPropert.h"
#include "F_Protos.h"
#include "Resource.h"

extern "C" __declspec(dllexport) const char *GetShaderDiffuseFilters()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   static CString filter;
   filter.LoadString(IDS_MENUFILTER);
   return (LPCTSTR)filter;
}

extern "C" __declspec(dllexport) const char *GetShaderSpecularFilters()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   static CString filter;
   filter.LoadString(IDS_MENUFILTER);
   return (LPCTSTR)filter;
}

extern "C" __declspec(dllexport) void GetDiffuse( Shading &shading )
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState())
   ((CShaderApp *)AfxGetApp())->GetDiffuse( shading );
}

extern "C" __declspec(dllexport) BOOL GetSpecular( Shading &shading, Vector &lightcolor )
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState())
   return ((CShaderApp *)AfxGetApp())->GetSpecular( shading, lightcolor );
}

