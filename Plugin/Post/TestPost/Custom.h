// NAP  6/24/2003  \Noelsrv105\Plugin\Post\Add\Custom.h

#include "PostPlug.h"
#include "Resource.h"
#include "ColorBtn.h"
#include "SDK/HPropert.h"

class CustomPostPlugin : public PostPlugin
{
public:
   HPercentProperty         *m_percent1;
   HPercentProperty         *m_percent2;
   HPercentProperty         *m_percent3;

//needed constants
// x,y resolution of buffer
int xres;
int yres;

// Vertical field of view and aspect ration
float fov;
float aspect;
	
// Near, far depth plane distance
float zn;
float zf; //changable
float zn_normalized;
float zf_normalized;

// World space units in x,y direction of near plane
float yn;
float xn;

Vector2 vRecipDepthBufferSize;
Vector2 vCameraFrustrumSize;

BOOL *LoadedPOI;
float *LoadedDepths;
float *CalculatedOCCs;
float *CalculatedOCCsBlur;
Vector *LoadedNormals;

float CalculateOCC(Vector2 position);
float CalculateOCC1(Vector2 position);
float CalculateOCC2(Vector2 position);
Vector ScreenPosToViewPos( Vector position, float fdepth);
Vector ViewPosToScreenPos( Vector ViewPos );
float LoadDepth( Vector2 offset );
float LoadDepth( Vector offset );
Vector LoadNormal( Vector2 offset );
float LoadOCC( Vector2 offset );
float LoadOCCBlur( Vector2 offset );
float CS_Horizontal(Vector2 position);
float CS_Vertical( Vector2 position );
float Blur( Vector2 position, int radius);
BOOL PixelOfInterest( Vector2 position, int radius );

// CONSTRUCTION/DESTRUCTION
                             CustomPostPlugin(HTreeObject *treeobject);
   virtual                  ~CustomPostPlugin();

// INTERFACE
   virtual UINT              GetIconID() { return IDI_POST; }

   virtual UINT              GetNameID() { return IDS_POSTNAME; }
   virtual char             *GetClassName() { return "Hash\\TestPost"; }

// PROCESSING
   virtual HProperty        *GetPropertyAt( int i );
   virtual BOOL              Process(Time time, HBufferShortcut *inputs, HBufferShortcut *output );
   virtual int               GetNumInputs();
   virtual Styles            GetAllowedInputBufferStyles();
//   virtual Info              GetInfo();

// CUSTOM POST FUNCTIONS
};
