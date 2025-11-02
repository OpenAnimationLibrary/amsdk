// Dan  12/28/00  \Dan90\Plugin\HXT\3DS\Construc.cpp

#include "StdAfx.h"
#include "Hxt.h"
#include "Custom.h"

extern CHxtApp theApp;

extern "C" __declspec(dllexport) IEModelBase *CreateExportModelBase()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   return new CustomExport;
}

extern "C" __declspec(dllexport) void DestroyExportModelBase(IEModelBase *modelbase)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   delete modelbase;
}

extern "C" __declspec(dllexport) int GetDLLVersion()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   return IEVERSION;
}

CustomExport::CustomExport()
{
}

CustomExport::~CustomExport()
{
}

