#include "stdafx.h"
#include "F_Protos.h"
#include "Resource.h"
#include "sample.h"
#include "SDK\Entry.h"

enum { MODEL, OBJECTCONTAINER };
extern "C" __declspec(dllexport) const BOOL HxtLoadCommandEntry(UINT index, ObjectType &objtype)
{
   switch (index) {
   case MODEL:
      objtype = HOT_MODEL;  //Objecttype in Objtype.h
      return TRUE;
   case OBJECTCONTAINER:
      objtype = HOT_OBJECTCACHECONTAINER;
      return TRUE;
   }
   return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, UINT index, String &menuname, MenuCategory &mc, BOOL &disabled)
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   CString string;
   string.LoadString(IDS_STRING1); // Der Name des Plugin's, welcher im Menu dann angezeigt wird
   menuname = (LPCTSTR)string;

   disabled = FALSE;
   mc = MC_WIZARD;
  // Hier wird darueber entschieden, bei welchem Menu das Plugin auftauchen soll
  // nachzulesen in entry.h

   switch (index) {
   case MODEL:
      if (!((HAnimObject *)htreeobject)->IsCache())
         return FALSE; 
      return TRUE;
   case OBJECTCONTAINER:
      return TRUE; 
   }
   return FALSE;
}

extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, UINT index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
   switch (index) {
   case MODEL:
      return ((CSampleApp *)AfxGetApp())->OnSampleWizard((HModelCache *)htreeobject);
   case OBJECTCONTAINER:
      HModelCache *modelcache = HModelCache::New();
      return ((CSampleApp *)AfxGetApp())->OnSampleWizard(modelcache);
   }
   return FALSE;
}


