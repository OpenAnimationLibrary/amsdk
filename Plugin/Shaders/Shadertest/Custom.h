// Dan  11/26/2001  \Dan90\Plugin\Shaders\Gradient\Custom.h

#include <afxwin.h>
#include <afxcmn.h>

#include "ShadeDLL.h"
#include "Resource.h"
#include "SDK/HPropert.h"
#include "SDK/HThreadInfo.h"
#include "SDK/HChor.h"

class CustomShader : public Shader2
{
public:
   int                       m_ObjType;
   HChor                     *m_Chor;
   HFloatProperty 	         *m_RayDistance;
   HIntProperty 	         *m_Samples;

// CONSTRUCTION/DESTRUCTION
                             CustomShader(HTreeObject *treeobject);
   virtual                  ~CustomShader();

// INTERFACE
   virtual UINT              GetIconID() { return nullptr; }

   virtual UINT              GetNameID() { return IDS_SHADERNAME; }
   virtual char             *GetClassName() { return "Hash\\ShaderTest"; }

// EVALUATION
   virtual const char       *GetShaderDiffuseFilters();
   virtual const char       *GetShaderSpecularFilters();
   virtual const char       *GetShaderAmbianceFilters();
// RENDERING
   virtual HProperty        *GetPropertyAt( int i );
   virtual BOOL              GetSpecular( HShading *shading, const RGBFloat &lightcolor );
   virtual void              GetDiffuse( HShading *shading );
   virtual void              GetAmbiance( HShading *shading );
};


