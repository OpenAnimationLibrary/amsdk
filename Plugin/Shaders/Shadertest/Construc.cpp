// KB  11/15/2002  \Ken100\Plugin\Shaders\Gradient\Construc.cpp

#include "stdafx.h"
#include "Custom.h"
#include "Shader.h"

extern CShaderApp theApp;

extern "C" __declspec(dllexport) Shader *CreateShader(HTreeObject *treeobject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   return new CustomShader(treeobject);
}

extern "C" __declspec(dllexport) int GetDLLVersion()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState())
   return SHADERDLLVERSION;
}

CustomShader::CustomShader(HTreeObject *treeobject) : Shader2(treeobject)
{
   m_RayDistance = HFloatProperty::New(theApp.m_RayDistanceInfo);
   m_Samples = HIntProperty::New(theApp.m_SamplesInfo);
   m_ObjType = HOT_MODEL;  // Or on a group is the same
   m_Chor = nullptr;
   HModel *mdl = GetModel();
   HTreeObject *obj;
   if ( !mdl ) {
      if ( (obj = GetOwner()) == nullptr )
         return;                       // This is a registration instance. Don't bother
      while ( obj = obj->GetParent() )
         if ( obj->GetObjectType() == HOT_MATERIAL ) {
            m_ObjType = HOT_MATERIAL;
            return;
         }
      m_ObjType = -1;                  // This is the render instance
      return;
   }
   obj = (HTreeObject*) mdl;
   while ( obj = obj->GetParent() )
      if ( obj->GetObjectType() == HOT_CHOR ) {
         m_ObjType = HOT_CHOR;
         m_Chor = (HChor*) obj;
         return;
      }
   
   
}

CustomShader::~CustomShader()
{
	delete m_Samples;
	delete m_RayDistance;
}


