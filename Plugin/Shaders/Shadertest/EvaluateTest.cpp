// KB  11/15/2002  \Ken100\Plugin\Shaders\Gradient\EvaluateGradient.cpp

#include "stdafx.h"
#include "resource.h"
#include "Custom.h"
#include "Matrix34.h"
#include "F_Protos.h"

HProperty *CustomShader::GetPropertyAt( int i )
{
   switch (i) {
       case 0:
	      return m_RayDistance;
      case 1:
      	return m_Samples;
     default:
         return nullptr;
   }
}

const char *CustomShader::GetShaderDiffuseFilters()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   static CString filter;
   filter.LoadString(IDS_MENUFILTER);
   return (LPCTSTR)filter;
}

const char *CustomShader::GetShaderSpecularFilters()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   static CString filter;
   filter.LoadString(IDS_MENUFILTER);
   return (LPCTSTR)filter;
}

const char *CustomShader::GetShaderAmbianceFilters()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
   static CString filter;
   filter.LoadString(IDS_MENUFILTER);
   return (LPCTSTR)filter;
}

void CustomShader::GetAmbiance( HShading *shading )
{
}

unsigned my_rand(void) {
  static unsigned next1=1151752134u, next2=2070363486u;
  next1 = next1 * 1701532575u + 571550083u;
  next2 = next2 * 3145804233u + 4178903934u;
  return (next1<<16)^next2;
}

float U_m1_p1(){
  return float(my_rand())*(1.0f/2147483648.0f) - 1.0f;
}

Vector pick_random_point_in_sphere(){
  float x1,x2,x3,d2;
  do{
    x1=U_m1_p1();
    x2=U_m1_p1();
    x3=U_m1_p1();
    d2=x1*x1+x2*x2+x3*x3;
  }while(d2>1.0f);
  float scale = InverseSqrt(d2);
  return Vector(x1*scale,x2*scale,x3*scale);
}

Vector pick_random_point_in_semisphere(Vector const &v){
  Vector result=pick_random_point_in_sphere();
  if(result.Dot(v)<0.f){
    result.x=-result.x;
    result.y=-result.y;
    result.z=-result.z;
  }
  return result;
}


void CustomShader::GetDiffuse( HShading *shading )
{
    if (m_Chor) {
	    Vector hitp,hitn;
	    RGBFloat color;
	    float maxdist,flatness;
	    flatness = 0.0016f;
	    PVOID oldrinfo=nullptr;
	    PVOID newrinfo=nullptr;
	    PVOID thread=nullptr;
	    Vector ray_dir;

	    int samples;//Anzahl der Samples nicht zeitkritisch 
	    int hitcounter = 0;
	    float average;
    
	    samples = m_Samples->GetValue();
	    maxdist = m_RayDistance->GetValue();
    
	    HTexInfo *htexinfo = shading->GetTexInfo();
#ifdef _DEBUG	    
	    Vector test,test1,test3;
        Matrix34 texmatrix;
	    texmatrix = *htexinfo->GetInverseMatrix();
#endif

	    Vector point_viewspace = shading->GetHitP();
	    Vector normal_viewspace = *htexinfo->GetN();

#ifdef _DEBUG	    
	    Vector point_worldspace = point_viewspace; //_worldspace nur fürs testen ...
	    TransformVectorNoTranslate( texmatrix, point_worldspace);
	    Vector normal_worldspace = normal_viewspace;
	    TransformVectorNoTranslate( texmatrix, normal_worldspace);
	    normal_worldspace.Normalize();
#endif
	   color.Set(0,1,0);
#ifdef _DEBUG	    
    if (normal_worldspace.y > 0) { // nur fuers testen
#endif    
       m_Chor->MultIntersect_Init(flatness,oldrinfo,newrinfo,thread ); 
        for (int i=0;i<=samples;++i) {
		   ray_dir = pick_random_point_in_semisphere(normal_viewspace);
           ray_dir.Normalize();
           if (m_Chor->MultIntersect(point_viewspace,ray_dir,hitp,hitn,maxdist,thread)) { //funktioniert erst ab V14
//           if (m_Chor->Intersect(point_viewspace,ray_dir,hitp,hitn,maxdist,flatness)) { //funktioniert auch mit V13, aber Memoryleaks und wesentlich langsamer
				hitcounter++;
           }
        }
        m_Chor->MultIntersect_Exit(oldrinfo,newrinfo,thread ); 
        if (hitcounter > 0) {
            average = hitcounter*1.f/samples;
		    color.Set(average,0,0);
        } 
#ifdef _DEBUG	           
	  }
#endif	  
	   shading->SetDCol( color );
   }
}

BOOL CustomShader::GetSpecular( HShading *shading, const RGBFloat &lightcolor )
{
   return FALSE;
}
