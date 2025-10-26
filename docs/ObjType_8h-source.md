<div class="tabs">

- [Main Page](index.md)
- [Classes](annotated.md)
- <span id="current">[Files](files.md)</span>
- [Directories](dirs.md)
- [Related Pages](pages.md)

</div>

<div class="tabs">

- [File List](files.md)
- [File Members](globals.md)

</div>

<div class="nav">

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a>

</div>

# ObjType.h

[Go to the documentation of this file.](ObjType_8h.md)

<div class="fragment">

``` fragment
00001 // BC  6/14/2005  \Master120\Include\ObjType.h
00002 
00003 #define __OBJTYPE_H
00004 
00005 // Hash Object Types
00006 enum ObjectType {
00007  HOT_CHOR                        = 0,
00008  HOT_MODEL                       = 1,
00009  HOT_SEGMENT                     = 2,
00010  HOT_ACTION                      = 3,
00011  HOT_GROUP                       = 4,
00012  HOT_DECAL                       = 5,
00013  HOT_ROTOSCOPE                   = 6,
00014  HOT_HASHOBJECT                  = 7,
00015  HOT_CAMERA                      = 9,
00016  HOT_LIGHT                       = 10,
00017  HOT_NULLOBJECT                  = 11,
00018  HOT_PROJECT                     = 12,
00019  HOT_MUSCLECHANNELCONTAINER      = 13,
00020  HOT_OBJECTCACHECONTAINER        = 14,
00021  HOT_ACTIONCACHECONTAINER        = 15,
00022  HOT_MATERIALCACHECONTAINER      = 16,
00023  HOT_AIMATCONSTRAINT             = 17,
00024  HOT_AIMROLLATCONSTRAINT         = 18,
00025  HOT_TRANSLATETOCONSTRAINT       = 19,
00026  HOT_ORIENTLIKECONSTRAINT        = 20,
00027  HOT_KINEMATICCONSTRAINT         = 21,
00028  HOT_AIMLIKETWOCONSTRAINT        = 22,
00029  HOT_AIMROLLLIKETWOCONSTRAINT    = 23,
00030  HOT_MATERIAL                    = 24,
00031  HOT_ATTRIBUTE                   = 25,
00032  HOT_GRADIENT                    = 26,
00033  HOT_SPHERICAL                   = 27,
00034  HOT_CHECKER                     = 28,
00035  HOT_DISTORT                     = 29,
00036  HOT_TURBULENCE                  = 30,
00037  HOT_BLOBBY                      = 31,
00038  HOT_STREAK                      = 32,
00039  HOT_PATH                        = 33,
00040  HOT_PATHCONSTRAINT              = 34,
00041  HOT_SPHERICALLIMITS             = 35,
00042  HOT_UNUSED3                     = 36,
00043  HOT_EULERLIMITS                 = 37,
00044  HOT_POSE                        = 38,
00045  HOT_POSECACHECONTAINER          = 39,
00046  HOT_DOPESHEET                   = 40,
00047  HOT_DOPEFRAME                   = 41,
00048  HOT_WEATHERMAP                  = 42,
00049  HOT_STAMP                       = 43,
00050  HOT_PATHFIGURE                  = 44,
00051  HOT_BONE                        = 45,
00052  HOT_CHORCONTAINER               = 46,
00053  HOT_MOTIONCAPTUREDEVICE         = 47,
00054  HOT_SENSOR                      = 48,
00055  HOT_CONTAINER                   = 49,
00056  HOT_ACTIONOBJECTSCONTAINER      = 50,
00057  HOT_ROLLLIKECONSTRAINT          = 51,
00058  HOT_ACTIONOBJECTACTION          = 52,
00059  HOT_FORCE                       = 53,
00060  HOT_PARTICLE                    = 54,
00061  HOT_RADIOSITYMAP                = 55, //unused
00062  HOT_MATFX                       = 56,
00063  HOT_VOLFX                       = 57,
00064  HOT_HAIR                        = 58,
00065  HOT_SOUNDCONTAINER              = 59,
00066  HOT_SOUND                       = 60,
00067  HOT_IMAGECONTAINER              = 61,
00068  HOT_CLIP                        = 62,
00069  HOT_STILL                       = 63,
00070  HOT_ANIMATION                   = 64,
00071  HOT_DECALCLIP                   = 65,
00072  HOT_DECALCONTAINER              = 66,
00073  HOT_DECALCLIPCONTAINER          = 67,
00074  HOT_STAMPCONTAINER              = 68,
00075  HOT_WEATHERCLIP                 = 69,
00076  HOT_SPRITESYSTEM                = 70,
00077  HOT_SPRITEEMITTER               = 71,
00078  HOT_SKELETALCHANNELMODIFIER     = 72,
00079  HOT_SKELETALPOSEMODIFIER        = 73,
00080  HOT_RELATIONCONTAINER           = 74,
00081  HOT_RELATION                    = 75,
00082  HOT_RELATIONKEY                 = 76,
00083  HOT_RELATIONMDSHORTCUT          = 77,
00084  HOT_SURFACECONSTRAINT           = 78,
00085  HOT_SCALELIKECONSTRAINT         = 79,
00086  HOT_GROUPCONTAINER              = 80,
00087  HOT_TRANSLATELIMITS             = 81,
00088  HOT_UNUSED6                     = 82,
00089  HOT_FLOCKFX                     = 83,
00090  HOT_LIGHTLISTNODE               = 84,
00091  HOT_LIGHTCONTAINER              = 85,
00092  HOT_CHORACTION                  = 86,
00093  HOT_USERCONTAINER               = 87,
00094  HOT_BONECONTAINER               = 88,
00095  HOT_ONETARGETSHORTCUT           = 89,
00096  HOT_SPRING                      = 90,
00097  HOT_SPRINGSCONTAINER            = 91,
00098  HOT_SPRINGSYSTEM                = 92,
00099  HOT_MASS                        = 93,
00100  HOT_MASSCONTAINER               = 94,
00101  HOT_PROP                        = 95,
00102  HOT_PHONEME                     = 96,
00103  HOT_TEXT                        = 97,
00104  HOT_UNUSED7                     = 98,
00105  HOT_UNUSED2                     = 99,
00106  HOT_CPTOMASSCONSTRAINT          = 100,
00107  HOT_ACTIONDOPESHEET             = 101,
00108  HOT_TWOTARGETSHORTCUT           = 102,
00109  HOT_SPLINECONTAINER             = 103,
00110  HOT_CHANNEL                     = 104,
00111  HOT_CPINSTANCE                  = 105,
00112  HOT_CP                          = 106,
00113  HOT_RELATIONSTORAGEDRIVER       = 107,
00114  HOT_ACTIONSHORTCUTCONTAINER     = 108,
00115  HOT_USERCATEGORYPROPERTY        = 109,
00116  HOT_ANIMOBJECTSHORTCUT          = 110,  
00117  HOT_CHANNELDRIVER               = 111,
00118  HOT_UNUSED8                     = 112,
00119  HOT_UNUSED9                     = 113,
00120  HOT_UNUSED10                    = 114,
00121  HOT_EULERROTATEDRIVER           = 115,
00122  HOT_VECTORROTATEDRIVER          = 116,
00123  HOT_QUATERNIONROTATEDRIVER      = 117,
00124  HOT_CATEGORYPROPERTY            = 118,
00125  HOT_RELATION1DSHORTCUT          = 119,
00126  HOT_RELATIONCONSTRAINTSHORTCUT  = 120,
00127  HOT_PATHCONSHORTCUT             = 121,
00128  HOT_SLICE                       = 122,
00129  HOT_SLICEINST                   = 123, 
00130  HOT_SMARTSKINCONTAINER          = 124,
00131  HOT_SMARTSKINBONE               = 125,
00132  HOT_SMARTSKINAXIS               = 126,
00133  HOT_ROTATEDRIVERSHORTCUT        = 127,
00134  HOT_DYNAMICCATEGORYPROPERTY     = 128,
00135  HOT_POSECHANNELCONTAINER        = 129,
00136  HOT_CHILDCONSTRAINT             = 130,
00137  HOT_EMPTYRELATION               = 131,
00138  HOT_RELATIONHASHOBJECTSHORTCUT  = 132,
00139  HOT_MASSTOCPCONSTRAINT          = 133,
00140  HOT_MASSTOBONECONSTRAINT        = 134,
00141  HOT_LAYER                       = 135,
00142  HOT_CPSHORTCUT                  = 136,
00143  HOT_SPLINESHORTCUT              = 137,
00144  HOT_ACTIONOBJECTINSTANCECONTAINER = 138,
00145  HOT_TRANSLATEFLOATDRIVERSHORTCUT  = 139,
00146  HOT_FLOCKSURFACECONSTRAINT      = 140,
00147  HOT_TRANSLATEDRIVERNOSUBS       = 141,
00148  HOT_RELATION1DSHORTCUTSIMPLE    = 142,
00149  HOT_SHAG                        = 143,
00150  HOT_TIMEBASEDDRIVER             = 144,
00151  HOT_TIMEBASEDKEY                = 145,
00152  HOT_CONSTDRIVER                 = 146,
00153  HOT_MASSSHORTCUT                = 147,
00154  HOT_ATTRPROPERTY                = 148,
00155  HOT_BIASPROPERTY                = 149,
00156  HOT_BOOLPROPERTY                = 150,
00157  HOT_BUTTONPROPERTY              = 151,
00158  HOT_CLIPPROPERTY                = 152,
00159  HOT_COLORPROPERTY               = 153,
00160  HOT_CONTAINERPROPERTY           = 154,
00161  HOT_DYNAMICCONTAINERPROPERTY    = 155,
00162  HOT_EMAILPROPERTY               = 156,
00163  HOT_FILEINFOPROPERTY            = 157,
00164  HOT_FILENAMEPROPERTY            = 158,
00165  HOT_FLOATPROPERTY               = 159,
00166  HOT_GRADIENTPROPERTY            = 160,
00167  HOT_INTPROPERTY                 = 161,
00168  HOT_PERCENTPROPERTY             = 162,
00169  HOT_POINTERPROPERTY             = 163,
00170  HOT_PREVIEWPROPERTY             = 164,
00171  HOT_ROTATEPROPERTY              = 165,
00172  HOT_SCALEPROPERTY               = 166,
00173  HOT_SHADERPROPERTY              = 167,
00174  HOT_STRINGPROPERTY              = 168,
00175  HOT_TIMEPROPERTY                = 169,
00176  HOT_TIMERANGEPROPERTY           = 170,
00177  HOT_TYPEPROPERTY                = 171,
00178  HOT_TRANSFORMPROPERTY           = 172,
00179  HOT_TRANSLATEPROPERTY           = 173,
00180  HOT_URLPROPERTY                 = 174,
00181  HOT_VECTOR2PROPERTY             = 175,
00182  HOT_VECTORPROPERTY              = 176,
00183  HOT_VECTORNOSUBSPROPERTY        = 177,
00184  HOT_TRANSLATENOSUBSPROPERTY     = 178,
00185  HOT_ACTIONOBJECTPLACEHOLDER     = 179,
00186  HOT_RIGIDBODYCONSTRAINT         = 180,
00187  HOT_DRIVER                      = 181,
00188  HOT_EMPTYDRIVER                 = 182,
00189  HOT_MODELBONEFOLDER             = 183,
00190  HOT_CUSTOMRANGEPROPERTY         = 184,
00191  HOT_PROPERTYLISTPROPERTY        = 185,
00192  HOT_EXPRESSION                  = 186,
00193  HOT_BONETOSPRINGCONSTRAINT      = 187,
00194  HOT_DECALSURFACEDRIVER          = 188,
00195  HOT_EULERFLOATPROPERTY          = 189,
00196  HOT_VIRTUALPROPERTY             = 190,
00197  HOT_POSTCONTAINER               = 191,
00198  HOT_POSTEFFECT                  = 192,
00199  HOT_POSTCACHECONTAINER          = 193,
00200  HOT_DYNAMICCONSTRAINT           = 194,
00201  HOT_MULTIMULTIDSTORAGEDRIVER    = 195,
00202  HOT_SPLINECONTAINERSHORTCUT     = 196,
00203  HOT_RELATION1DSHORTCUTDIRECT    = 197,
00204  HOT_DIRNAMEPROPERTY             = 198,
00205  HOT_HAIRGUIDE                   = 199,
00206  HOT_HAIRGUIDESHORTCUT           = 200,
00207  HOT_GUIDECPSHORTCUT             = 201,
00208  HOT_PLATTCORNER                 = 202,
00209  HOT_GROUPNODEDESCRIPTION        = 203,
00210  HOT_GUIDECPOBJECT               = 204,
00211  HOT_DYNAMICOPTIONSCONSTRAINT    = 205,
00212  HOT_DATAPROPERTY                = 206,
00213  HOT_DYNAMICRESULTSDRIVER        = 207,
00214  HOT_HAIRCLUSTERCONTAINER        = 208,
00215  HOT_HAIRCLUSTER                 = 209,
00216  HOT_POLYMODIFIERNODE            = 209,
00217  HOT_POLYMODIFIERCONTAINER       = 210,
00218  HOT_POLYMODIFIERSHORTCUT        = 211,
00219  HOT_BUFFERSHORTCUT              = 212,  
00220  HOT_BITMAPBUFFER                = 213,  
00221  HOT_COMPOSITE                   = 214,
00222  HOT_LIGHTBUFFERLIGHTS           = 215,
00223  HOT_TEXTURENODE                 = 216,
00224  NUM_HOTS
00225 };
00226 
00227 //if you change the length of this you need to
00228 //run sourcedir\master\numhots.bat
00229 //or make
00230 //master\master.cpp
00231 //master\hxtplugin.cpp
00232 //hashapp\hot.cpp
00233 //hashapp\filter.cpp
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
