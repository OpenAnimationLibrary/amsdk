// NAP  12/28/2004  \Noel120\Plugin\Post\Add\Process.cpp

#include "StdAfx.h"
#include "RGBHalf.inl"
#include "SDK/HBitmap.h"
#include "Custom.h"
#include "PostApp.h"

extern CPostApp theApp;

HProperty *CustomPostPlugin::GetPropertyAt( int i )
{
   switch (i) {
   case 0:
      return m_percent1;
   case 1:
      return m_percent2;
   case 2:
      return m_percent3;
   default:
      return nullptr;
   }
}
/*
CustomPostPlugin::Info    CustomPostPlugin::GetInfo() 
{
return NORMAL;
} 
*/
CustomPostPlugin::Styles  CustomPostPlugin::GetAllowedInputBufferStyles()
{
   return STYLE_RGBA;
}

int CustomPostPlugin::GetNumInputs()
{
   return 3;
}

// Create a set of lengths to apply to the offset vectors
const float avScales[8] =
{
   0.5625f,
   0.6250f,
   0.6875f,
   0.7500f,
   0.8125f,
   0.8750f,
   0.9375f,
   1.0000f
};

// Define reflection vectors
const Vector rotation[16][16] = 
{
   {Vector(0.979213,-0.00394083,-0.202798),Vector(0.459437,-0.571893,-0.6796),Vector(-0.267886,-0.963319,-0.0159409),Vector(0.141673,-0.892674,-0.427858),Vector(-0.605668,-0.522737,0.599927),Vector(0.36067,-0.521283,-0.773422),Vector(-0.617904,-0.785726,0.0288041),Vector(0.0271558,-0.817716,0.574981),Vector(0.874356,-0.283914,0.393566),Vector(0.44629,-0.447495,0.774967),Vector(-0.98568,-0.0282295,-0.166246),Vector(0.0136833,-0.366321,0.930388),Vector(0.928053,-0.0280628,0.37139),Vector(-0.100809,-0.99463,0.0234069),Vector(-0.30039,-0.947823,0.106757),Vector(0.752661,-0.499962,-0.428415)},
   {Vector(0.134703,-0.988616,0.0670385),Vector(0.92656,-0.17868,-0.331),Vector(-0.449829,-0.624531,0.638447),Vector(-0.0541511,-0.997785,-0.038643),Vector(-0.698716,-0.373442,0.610194),Vector(-0.222204,-0.130609,0.966213),Vector(-0.0552836,-0.991832,-0.114946),Vector(0.0777883,-0.99334,0.0849931),Vector(-0.558428,-0.413204,-0.71932),Vector(-0.360388,-0.633497,0.684691),Vector(0.0069461,-0.00218526,0.999973),Vector(-0.328396,-0.937604,-0.114253),Vector(0.538485,-0.743599,0.39635),Vector(-0.0657227,-0.475524,-0.877244),Vector(0.108545,-0.926043,0.361473),Vector(-0.0938633,-0.846157,-0.524602)},
   {Vector(0.245239,-0.0276785,-0.969068),Vector(0.489094,-0.763624,0.421504),Vector(-0.227781,-0.960828,0.157877),Vector(-0.660053,-0.482526,0.575759),Vector(0.026194,-0.999055,0.0346879),Vector(-0.694114,-0.716796,-0.0664092),Vector(0.0194243,-0.991762,-0.126615),Vector(-0.233739,-0.715253,-0.65862),Vector(-0.291034,-0.950516,-0.108716),Vector(-0.636915,-0.735691,0.230432),Vector(-0.208723,-0.97321,-0.0964224),Vector(0.578281,-0.459402,0.674196),Vector(0.13214,-0.97326,-0.187893),Vector(-0.00136498,-0.998328,0.0577794),Vector(-0.633131,-0.699423,-0.331591),Vector(0.756454,-0.507435,-0.412658)},
   {Vector(0.00428661,-0.999767,0.0211337),Vector(-0.591534,-0.806201,0.0112951),Vector(0.13438,-0.44801,-0.883872),Vector(0.258792,-0.431263,-0.864314),Vector(-0.468439,-0.818806,-0.331844),Vector(0.0495516,-0.974266,0.219887),Vector(-0.832018,-0.0970927,0.546186),Vector(0.32747,-0.464091,-0.823032),Vector(-0.821471,-0.525847,0.220612),Vector(0.437797,-0.566836,0.697876),Vector(-0.840761,-0.537812,-0.0622878),Vector(0.882256,-0.47055,-0.0143863),Vector(-0.641713,-0.742038,-0.193865),Vector(0.621326,-0.771081,-0.13924),Vector(-0.376758,-0.837599,0.395577),Vector(-0.644653,-0.762986,-0.0476969)},

   {Vector(0.848258,-0.37783,0.371084),Vector(-0.0961239,-0.490588,-0.866074),Vector(-0.049984,-0.998345,0.0284381),Vector(0.0733058,-0.974027,0.214236),Vector(-0.23468,-0.151068,0.960262),Vector(-0.141234,-0.987227,-0.0737266),Vector(0.0786212,-0.996381,0.0322987),Vector(-0.747721,-0.456474,-0.482228),Vector(0.101159,-0.990994,0.0877404),Vector(-0.805487,-0.0457108,-0.590848),Vector(-0.671006,-0.726708,0.147126),Vector(0.552159,-0.578811,-0.600081),Vector(-0.834493,-0.477467,-0.275041),Vector(-0.0022514,-0.999977,0.0064049),Vector(0.0089757,-0.0863984,-0.99622),Vector(-0.0365092,-0.973077,-0.227569)},
   {Vector(-0.0587858,-0.994739,-0.0838924),Vector(-0.813127,-0.467471,0.346837),Vector(-0.279966,-0.877412,-0.389572),Vector(-0.334297,-0.469933,-0.816951),Vector(0.675523,-0.339342,-0.654611),Vector(0.0971135,-0.83556,-0.540749),Vector(0.541337,-0.783955,0.303923),Vector(0.668761,-0.42753,-0.608258),Vector(-0.688827,-0.490755,0.53355),Vector(-0.22283,-0.949345,0.221567),Vector(0.307464,-0.714531,0.62842),Vector(0.190957,-0.00509423,0.981585),Vector(-0.363043,-0.566577,0.739723),Vector(0.280616,-0.615653,0.73636),Vector(-0.00765945,-0.985324,-0.170524),Vector(0.927412,-0.350709,0.13004)},
   {Vector(-0.595018,-0.69791,0.398592),Vector(-0.0323572,-0.990107,-0.136531),Vector(0.115298,-0.98098,0.156153),Vector(-0.461571,-0.812747,-0.35552),Vector(0.129801,-0.980962,0.14445),Vector(-0.245229,-0.96911,0.0262309),Vector(-0.192345,-0.917425,-0.348331),Vector(-0.00183823,-0.999856,0.016877),Vector(-0.131949,-0.813586,0.566275),Vector(0.72007,-0.563188,0.405361),Vector(0.00616074,-0.532637,-0.846321),Vector(-0.000215262,-0.991551,-0.129716),Vector(0.878643,-0.302293,-0.369602),Vector(0.938532,-0.292933,0.182616),Vector(-0.14868,-0.20629,-0.967129),Vector(-0.750408,-0.31835,-0.579259)},
   {Vector(0.497183,-0.656287,-0.567535),Vector(0.162598,-0.961815,0.220169),Vector(-0.374517,-0.918189,0.129101),Vector(0.147128,-0.989003,0.0150618),Vector(-0.279292,-0.951703,0.127504),Vector(-0.456355,-0.434446,0.776529),Vector(-0.295755,-0.922251,0.248961),Vector(-0.193802,-0.977814,-0.0795076),Vector(0.610035,-0.548326,-0.572011),Vector(-0.0506886,-0.984272,0.169231),Vector(0.404417,-0.69247,0.597438),Vector(-0.264889,-0.94481,0.192791),Vector(-0.238864,-0.963653,-0.119651),Vector(0.00337932,-0.999909,0.0130613),Vector(-0.647,-0.723332,0.241209),Vector(-0.307253,-0.927514,0.212872)},

   {Vector(-0.371527,-0.571004,-0.732067),Vector(-0.0957842,-0.970517,0.221186),Vector(-0.900048,-0.267351,0.344148),Vector(-0.0895738,-0.751118,-0.654063),Vector(-0.0334791,-0.86161,0.506465),Vector(0.533498,-0.837193,-0.120366),Vector(0.297318,-0.821022,0.487366),Vector(0.370811,-0.33527,-0.866079),Vector(-0.640932,-0.444547,0.625767),Vector(0.757135,-0.468683,0.455064),Vector(0.231501,-0.247314,0.940874),Vector(-0.229709,-0.901328,0.367209),Vector(-0.143615,-0.989366,-0.0230314),Vector(0.22543,-0.960301,0.164329),Vector(0.104322,-0.994543,-0.000808547),Vector(0.754303,-0.462473,0.465989)},
   {Vector(-0.571488,-0.729278,-0.376238),Vector(-0.103646,-0.512374,0.852485),Vector(-0.699515,-0.381097,0.60452),Vector(0.0982092,-0.810516,-0.577424),Vector(0.189278,-0.390078,0.901118),Vector(-0.781636,-0.620469,0.0637477),Vector(-0.0444662,-0.939627,0.339299),Vector(0.364766,-0.225647,-0.903343),Vector(-0.39857,-0.883022,-0.247817),Vector(0.945833,-0.324109,-0.0187878),Vector(0.598013,-0.655779,0.460797),Vector(-0.957158,-0.241697,0.159474),Vector(-0.174365,-0.869456,-0.462215),Vector(0.0181754,-0.999809,0.00719049),Vector(0.00365152,-0.999981,-0.00487471),Vector(-0.0309194,-0.999451,-0.0118694)},
   {Vector(-0.558701,-0.827268,0.059001),Vector(-0.31473,-0.943192,-0.106456),Vector(0.790676,-0.0185497,-0.611954),Vector(0.878293,-0.311624,-0.362619),Vector(-0.911707,-0.410313,-0.0208045),Vector(-0.705356,-0.708841,-0.00409277),Vector(0.226121,-0.931003,-0.286537),Vector(-0.152878,-0.985536,-0.0731183),Vector(-0.906784,-0.131181,0.400667),Vector(0.784845,-0.527911,0.324543),Vector(0.656999,-0.402785,-0.637273),Vector(-0.92735,-0.143653,0.345524),Vector(0.858509,-0.0875474,0.50527),Vector(0.889754,-0.17518,-0.421486),Vector(0.417574,-0.402785,-0.814492),Vector(-0.870041,-0.407243,0.277816)},
   {Vector(-0.282054,-0.763545,0.5809),Vector(0.38745,-0.0462163,0.920732),Vector(-0.570065,-0.790753,0.223013),Vector(0.159672,-0.632848,0.757634),Vector(0.795487,-0.50727,-0.331478),Vector(0.40264,-0.879079,0.255149),Vector(0.350203,-0.91586,-0.19636),Vector(-0.461583,-0.576515,0.674219),Vector(-0.0820001,-0.996172,0.0302926),Vector(-0.243163,-0.587302,0.771977),Vector(0.82196,-0.440432,-0.361111),Vector(0.214109,-0.954331,0.20835),Vector(0.393867,-0.4169,-0.819184),Vector(0.954051,-0.206879,0.216767),Vector(-0.189654,-0.972521,-0.135037),Vector(-0.100866,-0.987967,-0.117253)},

   {Vector(0.19001,-0.830829,0.523086),Vector(-0.340521,-0.561895,-0.753869),Vector(0.383123,-0.780361,-0.494219),Vector(-0.577563,-0.316527,0.752483),Vector(-0.651017,-0.716662,0.250147),Vector(0.180241,-0.90753,-0.379345),Vector(0.307849,-0.659111,-0.68615),Vector(0.530682,-0.661349,0.530089),Vector(-0.00546291,-0.990561,0.136968),Vector(0.250008,-0.168646,0.953443),Vector(-0.0794892,-0.996667,-0.0183258),Vector(0.695671,-0.29376,0.655551),Vector(-0.632258,-0.327538,-0.702117),Vector(0.343705,-0.445344,0.826762),Vector(-0.244292,-0.205914,-0.947587),Vector(0.18186,-0.147767,0.972158)},
   {Vector(0.126141,-0.872115,-0.472761),Vector(0.303526,-0.950673,0.0639794),Vector(-0.477399,-0.160942,0.863822),Vector(-0.0524248,-0.993762,0.0984267),Vector(-0.546806,-0.817646,-0.180164),Vector(0.0093487,-0.728572,0.684906),Vector(-0.0113193,-0.996428,0.0836859),Vector(0.213361,-0.950762,0.224785),Vector(-0.194371,-0.962853,-0.187441),Vector(-0.0901857,-0.834541,0.543515),Vector(0.0655844,-0.980227,-0.186693),Vector(0.177002,-0.0225858,-0.983951),Vector(-0.196471,-0.948038,0.250248),Vector(-0.105383,-0.970028,-0.218952),Vector(0.714457,-0.644386,0.272613),Vector(0.967688,-0.0134561,0.251793)},
   {Vector(0.844729,-0.256151,-0.469915),Vector(-0.182777,-0.433579,-0.882384),Vector(-0.724785,-0.553999,0.409601),Vector(-0.328421,-0.821337,0.466418),Vector(-0.0820988,-0.995116,0.0548024),Vector(0.742894,-0.434642,-0.509112),Vector(-0.421623,-0.750674,0.508649),Vector(0.392764,-0.0976921,-0.914436),Vector(-0.351574,-0.896443,0.269789),Vector(0.95048,-0.265893,-0.160898),Vector(-0.181828,-0.155532,-0.970952),Vector(0.286009,-0.761759,0.581311),Vector(-0.926844,-0.0494552,0.372174),Vector(0.141708,-0.79586,-0.588665),Vector(0.327619,-0.915822,-0.232241),Vector(0.364117,-0.635449,0.680899)},
   {Vector(0.724631,-0.687182,-0.0518824),Vector(-0.314246,-0.295389,-0.902216),Vector(-0.940347,-0.294287,-0.17071),Vector(0.607661,-0.249641,-0.753942),Vector(0.0622918,-0.515035,-0.854903),Vector(-0.298565,-0.642674,0.70557),Vector(0.780974,-0.615805,0.104231),Vector(0.701432,-0.0118222,-0.712638),Vector(0.895419,-0.351519,0.273237),Vector(0.0085528,-0.830455,-0.55702),Vector(0.707861,-0.121195,0.695877),Vector(0.582032,-0.561439,0.588239),Vector(0.821271,-0.464858,-0.33079),Vector(-0.171624,-0.34582,0.922472),Vector(0.51698,-0.577949,-0.631432),Vector(-0.391977,-0.894989,0.21295)}
};

// Define the sampling kernel that will be used for this thread.  
const Vector avKernel[8] =
{
   ( Vector(  1, 1, 1 ).Normalized() ),
   ( Vector( -1,-1,-1 ).Normalized() ),
   ( Vector( -1,-1, 1 ).Normalized() ),
   ( Vector( -1, 1,-1 ).Normalized() ),
   ( Vector( -1, 1 ,1 ).Normalized() ),
   ( Vector(  1,-1,-1 ).Normalized() ),
   ( Vector(  1,-1, 1 ).Normalized() ),
   ( Vector(  1, 1,-1 ).Normalized() )
};

const float blurKernel[7] = { 0.004431f, 0.05402f, 0.2420f, 0.3990f, 0.2420f, 0.05402f, 0.004431f };

Vector CustomPostPlugin::ScreenPosToViewPos( Vector position, float depth )
{

   Vector2 vViewSpaceUV;
   vViewSpaceUV.x = position.x * vRecipDepthBufferSize.x;
   vViewSpaceUV.y = position.y * vRecipDepthBufferSize.y;

   vViewSpaceUV = vViewSpaceUV * Vector2( 2.0f, -2.0f );   // From 0..1 to to 0..2
   vViewSpaceUV = vViewSpaceUV + Vector2( -1.0f, 1.0f );   // From 0..2 to -1..1     
//   vViewSpaceUV = vViewSpaceUV * vCameraFrustrumSize;
   vViewSpaceUV = vViewSpaceUV * vCameraFrustrumSize * 0.5f;

      return Vector( vViewSpaceUV.x, vViewSpaceUV.y, 1.0f ) * depth;
};

Vector CustomPostPlugin::ViewPosToScreenPos( Vector ViewPos )
{

   Vector2 SamplePoint;
   SamplePoint.x = ViewPos.x / ViewPos.z;
   SamplePoint.y = ViewPos.y / ViewPos.z;

//   SamplePoint /= (vCameraFrustrumSize * 0.5f);
   SamplePoint.x = SamplePoint.x / (vCameraFrustrumSize.x * 0.5f);
   SamplePoint.y = SamplePoint.y / (vCameraFrustrumSize.y * 0.5f);
   SamplePoint = SamplePoint + Vector2( 1.0f, -1.0f );
   SamplePoint = SamplePoint * Vector2( 0.5f, -0.5f );
   SamplePoint = SamplePoint * Vector2( xres, yres );

   return( Vector(fast_round(SamplePoint.x), fast_round(SamplePoint.y), 0 ) );
};

Vector reflect( Vector vSample, Vector vNormal )
{
   return( vSample - 2.0f * Dot( vSample, vNormal ) * vNormal );
};

float CustomPostPlugin::LoadDepth( Vector offset )
{
   if (offset.x < 0 || offset.y < 0)
      return 0.f;
   if (offset.x >= xres || offset.y >= yres)
      return 0.f;
   size_t array_point;
   array_point = fast_round(offset.y) * xres + fast_round(offset.x);
   return( LoadedDepths[array_point] );
};

float CustomPostPlugin::LoadDepth( Vector2 offset )
{
   if (offset.x < 0 || offset.y < 0)
      return 0.f;
   if (offset.x >= xres || offset.y >= yres)
      return 0.f;
   size_t array_point;
   array_point = fast_round(offset.y) * xres + fast_round(offset.x);
   return( LoadedDepths[array_point] );
};

Vector CustomPostPlugin::LoadNormal( Vector2 offset )
{
   if (offset.x < 0 || offset.y < 0)
      return Vector(0.f);
   if (offset.x >= xres || offset.y >= yres)
      return Vector(0.f);
   size_t array_point;
   array_point = fast_round(offset.y) * xres + fast_round(offset.x);
   Vector normal = LoadedNormals[array_point];
   return normal;
};

float CustomPostPlugin::LoadOCC( Vector2 offset )
{
   if (offset.x < 0 || offset.y < 0)
      return 1.f;
   if (offset.x >= xres || offset.y >= yres)
      return 1.f;
   size_t array_point;
   array_point = fast_round(offset.y) * xres + fast_round(offset.x);
   return( CalculatedOCCs[array_point] );
};

float CustomPostPlugin::LoadOCCBlur( Vector2 offset )
{
   if (offset.x < 0 || offset.y < 0)
      return 1.f;
   if (offset.x >= xres || offset.y >= yres)
      return 1.f;
   size_t array_point;
   array_point = fast_round(offset.y) * xres + fast_round(offset.x);
   return( CalculatedOCCsBlur[array_point] );
};

float CustomPostPlugin::CalculateOCC(Vector2 position) 
{
   float depth = MAX(LoadDepth( position ),1e-10f);
   Vector normal = LoadNormal(position);
   float fPixelDepth = depth * zf;
   Vector fPixelNormal = normal * 2.0f - 1.0f;
   float fNumSamples = 0.0f;
   float fResults = 0.0f;
   int t_x = position.x;
   int t_y = position.y;
   int rotx = t_x & 0xF;
   int roty = t_y & 0xF;

   // Find the view space 3D position of the pixel
   Vector PixelPosVS = ScreenPosToViewPos( position, fPixelDepth );
   //   float fKernelScale = .00751751f;
   float fKernelScale = 0.001f;
   //   float fKernelScale = .001f;

   for ( int x = 0; x < 2; x++ )  {
      for ( int y = 0; y < 8; y++ )  {
         // Calculate an offset into the reflection vector array
         rotx = (rotx + x) & 0xF;
         roty = (roty + y) & 0xF;

         //         // Find the new texture coordinates to load
         Vector vRotatedOffset = (reflect( avKernel[y], rotation[rotx][roty] )) * avScales[y];
         Vector vFlippedOffset = vRotatedOffset;
         float fSign = Dot( fPixelNormal, vRotatedOffset );
         if ( fSign < 0.0f )
            vFlippedOffset = -vFlippedOffset;

         Vector Sample3D = PixelPosVS + (vFlippedOffset * fKernelScale);
         Vector iNewOffset = ViewPosToScreenPos( Sample3D );
         //         Vector iNewNorm = LoadNormal(Vector2(iNewOffset.x,iNewOffset.y));
         //         Vector norm_diff = iNewNorm - normal;
         //         float l_diff = norm_diff.NormalizeLength();
         float fSample = 0;
         //         if (l_diff > 1) {
         fSample = LoadDepth( iNewOffset ) * zf;
         float fDelta = Sample3D.z - fSample;
         float fOcclusion = 0.0f;  // Initialize to zero occlusion

         const float fMinDeltaEpsilon = 0.051f;
         const float fFullOcclusionThreshold = 0.051f;
         const float fNoOcclusionThreshold = 0.5354f;
         const float fOcclusionPower = 2.0f;

         if ( fDelta > fMinDeltaEpsilon ) {
            float fNoOcclusionRange = fNoOcclusionThreshold - fFullOcclusionThreshold;      
            if ( fDelta < fFullOcclusionThreshold )
               fOcclusion = 1.0f;
            else
               fOcclusion = MAX( 1.0f - pow( ( fDelta - fFullOcclusionThreshold ) / fNoOcclusionRange, fOcclusionPower ), 0.0f );
         } 

         // Accumulate the resulting occlusion scaled by the distance from
         // this pixel's depth sample.
         fResults += fOcclusion * (avScales[y]* avScales[y]);
         //         }
         fNumSamples += 1.0f;
      }
   }
   return 1.0f - MIN( ( fResults / fNumSamples ), 1.0f );
}

float CustomPostPlugin::CalculateOCC1(Vector2 position) 
{
   float depth = MAX(LoadDepth( position ),1e-10f);
   Vector normal = LoadNormal(position);
   float fPixelDepth = depth * zf;
   Vector fPixelNormal = normal * 2.0f - 1.0f;
   float fNumSamples = 0.0f;
   float fResults = 0.0f;
   int t_x = 0;//position.x;
   int t_y = 0;//position.y;
   int rotx = t_x & 0xF;
   int roty = t_y & 0xF;

   // Find the view space 3D position of the pixel
   Vector PixelPosVS = ScreenPosToViewPos( position, fPixelDepth );
//   float fKernelScale = .00751751f;
	float fKernelScale = depth / (zf*zf);//0.001f;
   fKernelScale = MAX(fKernelScale,0.001f);
   if (fKernelScale > 0.001f) {
      int a;
      a =0;
   }
//   float fKernelScale = .001f;

   for ( int x = 0; x < 2; x++ )  {
      for ( int y = 0; y < 8; y++ )  {
         // Calculate an offset into the reflection vector array
         rotx = (rotx + x) & 0xF;
         roty = (roty + y) & 0xF;

         //         // Find the new texture coordinates to load
         Vector vRotatedOffset = (reflect( avKernel[y], rotation[rotx][roty] )) * avScales[y];
         Vector vFlippedOffset = vRotatedOffset;
         float fSign = Dot( fPixelNormal, vRotatedOffset );
         if ( fSign < 0.0f )
            vFlippedOffset = -vFlippedOffset;

            Vector Sample3D = PixelPosVS + (vFlippedOffset * fKernelScale);
            Vector iNewOffset = ViewPosToScreenPos( Sample3D );

            float fSample = LoadDepth( iNewOffset ) * zf;
            float fDelta = Sample3D.z - fSample;
            float fOcclusion = 0.0f;  // Initialize to zero occlusion

            const float fMinDeltaEpsilon = 0.051f;
            const float fFullOcclusionThreshold = 0.051f;
            const float fNoOcclusionThreshold = 0.5354f;
            const float fOcclusionPower = 2.0f;

            if ( fDelta > fMinDeltaEpsilon ) {
               float fNoOcclusionRange = fNoOcclusionThreshold - fFullOcclusionThreshold;      
               if ( fDelta < fFullOcclusionThreshold )
                  fOcclusion = 1.0f;
               else
                  fOcclusion = MAX( 1.0f - pow( ( fDelta - fFullOcclusionThreshold ) / fNoOcclusionRange, fOcclusionPower ), 0.0f );
            } 

            // Accumulate the resulting occlusion scaled by the distance from
            // this pixel's depth sample.
            fResults += fOcclusion * (avScales[y]* avScales[y]);
//         }
         fNumSamples += 1.0f;
      }
   }
   return 1.0f - MIN( ( fResults / fNumSamples ), 1.0f );
}

float CustomPostPlugin::CalculateOCC2(Vector2 position) 
{
   float depth = MAX(LoadDepth( position ),1e-10f);
   Vector normal = LoadNormal(position);
   float fPixelDepth = depth * zf;
   Vector fPixelNormal = normal * 2.0f - 1.0f;

   float fNumSamples = 0.0f;
   float fResults = 0.0f;

   // Find the view space 3D position of the pixel
   Vector PixelPosVS = ScreenPosToViewPos( position, fPixelDepth );

   // Kernel scale defines the size of the volume around each texel to sample
   //	float fKernelScale =0.01251751f;//= 0.01251751f;
   //	float fKernelScale = .00751751f;
   float fKernelScale = .002f;// Range 0,002 0,02 

   for ( int x = 0; x < 16; x++ )  {
      for ( int ya = 0; ya < 16; ya++ )  {
         for ( int y = 0; y < 8; y++ )  {
            // Calculate an offset into the reflection vector array
            Vector vRotatedOffset = (reflect( avKernel[y], rotation[x][ya] )) * avScales[y];

            Vector vFlippedOffset = vRotatedOffset;

            float fSign = Dot( fPixelNormal, vRotatedOffset );
            if ( fSign < 0.0f )
               vFlippedOffset = -vFlippedOffset;

            Vector Sample3D = PixelPosVS + vFlippedOffset * fKernelScale;

            Vector iNewOffset = ViewPosToScreenPos( Sample3D );

            Vector iNewNorm = LoadNormal(Vector2(iNewOffset.x,iNewOffset.y));
            Vector t1 = iNewNorm.Normalized();
            Vector t2 = normal.Normalized();
            Vector norm_diff = iNewNorm - normal;
            float l_diff = norm_diff.NormalizeLength();
            float fSample = 0;
            if (l_diff > 0.5f) {
               //         if (l_diff != 0 && l_diff != 1) {
               fSample = LoadDepth( iNewOffset ) * zf;

               float fDelta = Sample3D.z - fSample;
               float fOcclusion = 0.0f;  // Initialize to zero occlusion

               const float fMinDeltaEpsilon = 0.051f;
               const float fFullOcclusionThreshold = 0.051f;
               const float fNoOcclusionThreshold = 0.5354f;
               const float fOcclusionPower = 2.0f;

               if ( fDelta > fMinDeltaEpsilon ) {
                  float fNoOcclusionRange = fNoOcclusionThreshold - fFullOcclusionThreshold;      
                  if ( fDelta < fFullOcclusionThreshold )
                     fOcclusion = 1.0f;
                  else
                     fOcclusion = MAX( 1.0f - pow( ( fDelta - fFullOcclusionThreshold ) / fNoOcclusionRange, fOcclusionPower ), 0.0f );
               } 

               // Accumulate the resulting occlusion scaled by the distance from
               // this pixel's depth sample.
               fResults += fOcclusion * (avScales[y]* avScales[y]);
            }
            fNumSamples += 1.0f;
         }
      }
   }
   return 1.0f - MIN( ( fResults / fNumSamples ), 1.0f );
}

float CustomPostPlugin::CS_Horizontal(Vector2 position)
{
   float fCenterDepth = LoadDepth(position);
   float fCenterOcclusion = LoadOCC(position);

   const float rsigma = 0.0051f;

   float fBilateral = 0.0f;
   float fWeight = 0.0f;
   Vector2 pos = position;

   for ( int x = -3; x <= 3; x++ )
   {
      pos.x = position.x+x;
      float fSampleDepth = LoadDepth(pos);
      if (fSampleDepth > 0) {
         float fSampleOcclusion = LoadOCC(pos);

         float fDelta = fCenterDepth - fSampleDepth;
         float fRange = exp( ( -1.0f * fDelta * fDelta ) / ( 2.0f * rsigma * rsigma ) );

         fBilateral += fSampleOcclusion * fRange * blurKernel[x+3];
         fWeight += fRange * blurKernel[x+3];
      }
   }
   return fBilateral / fWeight;
}

float CustomPostPlugin::CS_Vertical( Vector2 position )
{
   float fCenterDepth = LoadDepth(position);
   float fCenterOcclusion = LoadOCC(position);

   const float rsigma = 0.0051f;

   float fBilateral = 0.0f;
   float fWeight = 0.0f;
   Vector2 pos = position;
   for ( int y = -3; y <= 3; y++ )
   {
      pos.y = position.y+y;
      float fSampleDepth = LoadDepth(pos);
      if (fSampleDepth > 0) {
         float fSampleOcclusion = LoadOCC(pos);

         float fDelta = fCenterDepth - fSampleDepth;
         float fRange = exp( ( -1.0f * fDelta * fDelta ) / ( 2.0f * rsigma * rsigma ) );

         fBilateral += fSampleOcclusion * fRange * blurKernel[y+3];
         fWeight += fRange * blurKernel[y+3];
      }
   }
   return fBilateral / fWeight;
}

BOOL CustomPostPlugin::PixelOfInterest( Vector2 position, int radius )
{
   Vector norm = LoadNormal(position);
   Vector2 pos;
   for ( int x = -radius; x <= radius; x++ )   {
      for ( int y = -radius; y <= radius; y++ )  {
         Vector2 addpos(x,y);
         pos = position + addpos;
         if  (pos.x > -1 && pos.y > -1 && pos.x < xres && pos.y < yres) {
            Vector norm2 = LoadNormal(pos);
            Vector norm_diff = norm - norm2;
            float l_diff = norm_diff.NormalizeLength();
            if (l_diff > 1.f ) {
               return TRUE;
            }
         }
      }
   }
   return FALSE;
}

float CustomPostPlugin::Blur( Vector2 position, int radius )
{
   Vector2 pos;
   float result = 0.f;
   float divider = 0.f;
   for ( int x = -radius; x <= radius; x++ )   {
      for ( int y = -radius; y <= radius; y++ )  {
         Vector2 addpos(x,y);
         pos = position + addpos;
         result += LoadOCCBlur(pos);
         divider += 1.f;
      }
   }
   return result / divider;
}

BOOL CustomPostPlugin::Process(Time time, HBufferShortcut *inputs, HBufferShortcut *output )
{

   HBufferShortcut *input = inputs;
   HRGBAFloatBuffer *inbuffer1 = input->GetRGBAFloatBuffer(time);//Color
   if (!inbuffer1)
      return FALSE;

   input = input->GetNextBufferShortcut();
   HRGBAFloatBuffer *inbuffer2 = input->GetRGBAFloatBuffer(time,FALSE);//Normal

   input = input->GetNextBufferShortcut();
   HRGBAFloatBuffer *inbuffer3 = input->GetRGBAFloatBuffer(time);//Depth normalized

   int width = inbuffer1->GetWidth(), height = inbuffer1->GetHeight();

   // x,y resolution of buffer
   xres= width;
   yres= height;

   // Vertical field of view and aspect ration
   fov = (3.1495f / 2.0f);
   aspect = (float)width/(float)height;

   // Near, far depth plane distance
   zn = 1.f;
   zf = 20.f;//Focal / 10 changable
   zn_normalized = (zn / zf);
   zf_normalized = (zf / zf);

   // World space units in x,y direction of near plane
   yn = (2.0f * zn_normalized * tan( fov / 2.0f ));
   xn = (aspect * yn);

   vRecipDepthBufferSize.Set( 1.0f/xres, 1.0f/yres );
   vCameraFrustrumSize.Set( xn, yn);

   int radiusPOI = 1;
   int radiusBlur = 10;

   size_t array_size = height * width;
   LoadedPOI = new BOOL[array_size];
   LoadedDepths = new float[array_size];
   CalculatedOCCs = new float[array_size];
   CalculatedOCCsBlur = new float[array_size];
   LoadedNormals = new Vector[array_size];

   BOOL SSAO_buffer = TRUE;
   BOOL SSAO_blur = FALSE;
#ifdef _DEBUG
   String bufname1;
   bufname1 = inbuffer1->GetName();
   String bufname2;
   bufname2 = inbuffer2->GetName();
   String bufname3;
   bufname3 = inbuffer3->GetName();
#endif

   HRGBAFloatBuffer *outbuffer = HBitmapNode::CreateRGBAFloatBuffer("RGBA", width, height);
   outbuffer->SetBackground(inbuffer1->GetBackground());
   outbuffer->AllocateData();

   HRGBAFloatBuffer *outbuffer1 = HBitmapNode::CreateRGBAFloatBuffer("RGBA", width, height);
   outbuffer1->SetBackground(inbuffer1->GetBackground());
   outbuffer1->AllocateData();


   RGBAFloat *inptr1,*inptr2,*inptr3;
   RGBAFloat *outptr = outbuffer->GetRGBAFloatData();
   RGBAFloat *outptr1 = outbuffer1->GetRGBAFloatData();

   int height_ptr;
   inptr2 = inbuffer2->GetRGBAFloatData();
   inptr3 = inbuffer3->GetRGBAFloatData();
   for (int y=0; y < height; ++y) {
      height_ptr = width * y;
      for (int x = 0; x < width; ++x) {
         float depth = inptr3->m_color.m_red;
         LoadedDepths[height_ptr+x] = depth;
         Vector normal(inptr2->m_color.m_red,inptr2->m_color.m_green,inptr2->m_color.m_blue);
         LoadedNormals[height_ptr+x] = normal.Normalize();
         ++inptr2; 
         ++inptr3; 
      }
   }

   RGBAFloat white(1,1,1,0);
   RGBAFloat black(0,0,0,0);
   outptr = outbuffer->GetRGBAFloatData();
   for (int y=0; y < height; ++y) {
      height_ptr = width * y;
      for (int x = 0; x < width; ++x) {
         Vector2 position(x,y);
         if (PixelOfInterest(position, radiusPOI )) {
            LoadedPOI[height_ptr+x] = TRUE;
         } else {
            LoadedPOI[height_ptr+x] = FALSE;
         }
      }
   }


   float multiplicator,multiplicator1;
   for (int y=0; y < height; ++y) {
      height_ptr = width * y;
      for (int x = 0; x < width; ++x) {
         Vector2 position(x,y);
//         if (LoadedPOI[height_ptr+x] == TRUE) {
//            multiplicator1 = CalculateOCC(position); 
            multiplicator = CalculateOCC2(position); 
//            multiplicator = CalculateOCC2(position); 
//            multiplicator = MIN(multiplicator,multiplicator1);
//         } else {
//            multiplicator = CalculateOCC(position); 
//         }
         CalculatedOCCs[height_ptr+x] = multiplicator;
      }
   }
/*
   for (int y=0; y < height; ++y) {
      height_ptr = width * y;
      for (int x = 0; x < width; ++x) {
         Vector2 position(x,y);
         multiplicator = (CS_Vertical(position)+CS_Horizontal(position))/2.f;
         CalculatedOCCsBlur[height_ptr+x] = CalculatedOCCs[height_ptr+x];//multiplicator;
      }
   }
*/

   outptr = outbuffer->GetRGBAFloatData();
/*
   if (SSAO_blur) {
      for (int y=0; y < height; ++y) {
         height_ptr = width * y;
         for (int x = 0; x < width; ++x) {
            Vector2 position(x,y);
            multiplicator = CalculatedOCCsBlur[height_ptr+x];
            multiplicator1 = Blur( position, radiusBlur);
            multiplicator = (multiplicator+multiplicator1)/2.f;
//            multiplicator = MIN(multiplicator,multiplicator1);
            CalculatedOCCs[height_ptr+x] = multiplicator;
         }
      }
      for (int y=0; y < height; ++y) {
         height_ptr = width * y;
         for (int x = 0; x < width; ++x) {
            Vector2 position(x,y);
            multiplicator = (CS_Vertical(position)+CS_Horizontal(position))/2.f;
            CalculatedOCCsBlur[height_ptr+x] = multiplicator;
         }
      }
   } 

   if (SSAO_buffer ) {
      for (int y=0; y < height; ++y) {
         height_ptr = width * y;
         for (int x = 0; x < width; ++x) {
            Vector2 position(x,y);
            multiplicator = CalculatedOCCsBlur[height_ptr+x];
            *outptr = white * multiplicator;
            outptr->m_alpha = 1;
            ++outptr;
         }
      }
      output->SetBuffer(outbuffer);
   } else {
      inptr1 = inbuffer1->GetRGBAFloatData();
      inptr2 = outbuffer->GetRGBAFloatData();
      outptr1 = outbuffer1->GetRGBAFloatData();
      for (int y=0; y < height; ++y) {
         height_ptr = width * y;
         for (int x = 0; x < width; ++x) {
//            multiplicator = CalculatedOCCsBlur[height_ptr+x];
            multiplicator = CalculatedOCCs[height_ptr+x];
            outptr1->m_color = inptr1->m_color * multiplicator;
//            outptr1->m_color = inptr1->m_color * inptr2->m_color.GetLuminance();
            outptr1->m_alpha = inptr1->m_alpha;
            ++outptr1;
            ++inptr1;
            ++inptr2;
         }
      }
      output->SetBuffer(outbuffer1);
   }
*/

      inptr1 = inbuffer1->GetRGBAFloatData();
      outptr1 = outbuffer1->GetRGBAFloatData();
      for (int y=0; y < height; ++y) {
         height_ptr = width * y;
         for (int x = 0; x < width; ++x) {
            *outptr1 = white * CalculatedOCCs[height_ptr+x];
//            outptr1->m_color = inptr1->m_color * multiplicator;
//            outptr1->m_alpha = inptr1->m_alpha;
            ++outptr1;
//            ++inptr1;
         }
      }
      output->SetBuffer(outbuffer1);

   delete LoadedPOI;
   delete LoadedDepths;
   delete CalculatedOCCs;
   delete CalculatedOCCsBlur;
   delete LoadedNormals;

   return TRUE;
}

