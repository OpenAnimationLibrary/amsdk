//BC  6/13/2005  \Master120\Include\Label.h

//We reserve the first 1000 numbers for the Headers/HOT's
//No Headers in here any more:
//The Headers are the HOT_'s, and are in ObjType.h

//Note: In order to maintain future binary file loadability, the label ID
//numbers should not be changed.
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once

//Generic Terms
#define IDL_NOLABEL          (-2)
#define IDL_VERSION          4001
#define IDL_PLATFORM         4002
#define IDL_NAME             4007
#define IDL_EMBEDDED         4008
#define IDL_COUNT            4009
#define IDL_TYPE             4010
#define IDL_VALUE            4011
#define IDL_IMAGESEQUENCE    4012
#define IDL_OFFSET           4013
#define IDL_VIEW             4014
#define IDL_VISIBLE          4015
#define IDL_EDITABLE         4016
#define IDL_SHORTCUTTO       4017
#define IDL_DESCRIPTION      4018
#define IDL_OBJECT           4019
#define IDL_COLOR            4020
#define IDL_EXPANDED         4021
#define IDL_SELECTED         4022
#define IDL_RANGE            4023
#define IDL_MATRIX           4024
#define IDL_PICKABLE         4025
#define IDL_SCALE            4028
#define IDL_TRANSLATE        4029
#define IDL_BLUR             4030
#define IDL_SHORTCUTTOLINKED 4031
#define IDL_DLLNAME          4032
#define IDL_MODIFIED         4033
#define IDL_AIM              4034
#define IDL_ROLL             4035
#define IDL_CLASSNAME        4036
#define IDL_PLUGINNAME       4037
#define IDL_MARKER           4038
#define IDL_CREATEDBY        4039
#define IDL_LASTMODIFIEDBY   4040
#define IDL_NOTES            4041
#define IDL_PLAYRANGE        4042
#define IDL_PLATFORMID       4043
#define IDL_VIEW1            4044
#define IDL_ROTATE           4045
#define IDL_ACTIVE           4046
#define IDL_LOCKED           4049
#define IDL_ANGLE            4050
#define IDL_MATCHNAME        4051
#define IDL_X                4052
#define IDL_Y                4053
#define IDL_Z                4054
#define IDL_W                4055
#define IDL_OPTIONS          4056
#define IDL_TRANSFORM        4057
#define IDL_RED              4058
#define IDL_GREEN            4059
#define IDL_BLUE             4060
#define IDL_URL              4061
#define IDL_EMAIL            4062
#define IDL_ORGANIZATION     4063
#define IDL_PREVIEW          4064
#define IDL_FILEINFO         4065
#define IDL_TACKEDOBJECT     4066
#define IDL_LENGTH           4067
#define IDL_INSTANCE         4068
#define IDL_CHILD            4069
#define IDL_MORETHANDRIVERS  4072
#define IDL_SEARCHSTRING     4073
#define IDL_SEARCHSTRING1    4074
#define IDL_SEARCHSTRING2    4075
#define IDL_SELECTIONSTRING  4076
#define IDL_LINKSTRING1      4077
#define IDL_LINKSTRING2      4078

//Figures                      100+

#define IDL_DRAWMODEOVERRIDE      4110
#define IDL_DRAWMODE              4111
#define IDL_WIREFRAME             4112
#define IDL_SHADED                4113
#define IDL_NAMECHANGED           4115
#define IDL_ANIMATEMODE           4116
#define IDL_PERSPECTIVE           4117
#define IDL_TEMPPERSPECTIVE       4118
#define IDL_DRAWSYSTEMS           4119

#define IDL_FRONTPROJECTIONTARGET 4120
#define IDL_CASTREFLECTIONS       4122
#define IDL_RECEIVESHADOWS        4123
#define IDL_CASTOCCLUSION         4124

#define IDL_LIGHTALL              4126
#define IDL_JITTERINFLUENCE       4127
#define IDL_SHADOWONLY            4129
#define IDL_GROUP                 4134
#define IDL_LINKEDDISTORT         4137
#define IDL_XRES                  4142
#define IDL_YRES                  4143
#define IDL_ZRES                  4144
#define IDL_IGNOREFOG             4145

//Actions                      4150+
#define IDL_USESTRIDE             4154
#define IDL_OVERLAPPING           4155
#define IDL_HOLDLASTFRAME         4156
#define IDL_TRANSITIONNAME        4157
#define IDL_REPEATCOUNT           4158
#define IDL_TRANSITIONTONEXT      4159

#define IDL_ACTIONSEQUENCE        4160
#define IDL_CROPSTARTFRAME        4161
#define IDL_CROPENDFRAME          4162
#define IDL_CHORSTARTFRAME        4163
#define IDL_CHORFRAMES            4164
#define IDL_CROPRANGE             4168
#define IDL_CHORRANGE             4169
#define IDL_BLENDRATIO            4170
#define IDL_CYCLELENGTH           4171
#define IDL_BLENDMETHOD           4172
#define IDL_CROP                  4173

//FigureCaches                 200+

#define IDL_GREATESTCPID     4210
#define IDL_TOTALPATCHES     4211
#define IDL_PIVOT            4212
#define IDL_SPLINES          4213
#define IDL_CPS              4214
#define IDL_HASBOOLEANS      4215
#define IDL_POSETOCLEARWITH  4216
#define IDL_ALPHA            4217
#define IDL_INMAGNITUDE      4218
#define IDL_OUTMAGNITUDE     4219

#define IDL_PERCENT          4240
#define IDL_SOFTNESS         4241
#define IDL_USEOBJECTCOLOR   4242
#define IDL_SHADINGMODE      4243
#define IDL_GRADIENTKEY      4244
#define IDL_GRADIENT         4245
#define IDL_GRADIENTPROPERTY 4246

//ActionCaches                 4250+

#define IDL_FRAMES                  4260
#define IDL_HASSTRIDE               4154//261 to share usestride
#define IDL_STRIDESTARTFRAME        4262
#define IDL_STRIDEENDFRAME          4263
#define IDL_STRIDESTARTPOSITION     4264
#define IDL_STRIDEENDPOSITION       4265
#define IDL_DEFAULTMODEL            4266
#define IDL_SCALEACTION             4267
#define IDL_SCALEBASIS              4268
#define IDL_SCALEBONENAME           4269
#define IDL_SCALESTANDARD           4270
#define IDL_STRIDELENGTH            4271
#define IDL_STRIDETIMERANGE         4272
#define IDL_SCALEMETHOD             4273

//BoneCaches                   4300+
#define IDL_END                     4310
#define IDL_ROLLHANDLE              4311
#define IDL_BONECOLOR               4312
#define IDL_RENDEREDCOLOR           4313
#define IDL_BOUNDS                  4314
#define IDL_CHAINED                 4315
#define IDL_HIDDEN                  4316
#define IDL_USERMOVED               4317
#define IDL_ROLLMETHOD              4318
#define IDL_MANIPULATION            4319
#define IDL_LIMITMANIPULATORS       4320
#define IDL_ALLOWXTRANSLATE         4321
#define IDL_ALLOWYTRANSLATE         4322
#define IDL_ALLOWZTRANSLATE         4323
#define IDL_ALLOWXSCALE             4324
#define IDL_ALLOWYSCALE             4325
#define IDL_ALLOWZSCALE             4326
#define IDL_ALLOWXROTATE            4327
#define IDL_ALLOWYROTATE            4328
#define IDL_ALLOWZROTATE            4329
#define IDL_BONEPOS                 4330
#define IDL_EULERORDER              4331

//SegmentCaches                4400+
#define IDL_HASFALLOFF              4407
#define IDL_PREVENTCPASSIGNMENT     4408
#define IDL_BOOLEANCUTTER           4410
#define IDL_PIVOTINNER              4411
#define IDL_PIVOTOUTER              4412
#define IDL_ENDINNER                4413
#define IDL_ENDOUTER                4414
#define IDL_PIVOTSCALE              4415
#define IDL_ENDSCALE                4416
#define IDL_FALLOFFTYPE             4417
#define IDL_BONEFALLOFFCURVE        4418

#define IDL_DEFAULTVALUE            4464
#define IDL_MINVALUE                4465
#define IDL_MAXVALUE                4466
#define IDL_MAXCHANNELITEMS         4467
#define IDL_INTERPOLATION           4468
#define IDL_REPEAT                  4469
//SkeletalChannels
#define IDL_BONEDIRECTION           4470
#define IDL_ROLLDIRECTION           4471
#define IDL_PARENTBONEDIR           4472
#define IDL_PARENTROLLDIR           4473
#define IDL_STOPCHAIN               4474
#define IDL_EULERINTERP             4475
#define IDL_ANGLEINTERP             4476
#define IDL_BONETOPARENT            4477

#define IDL_ENDMETHOD               4478
#define IDL_PREMETHOD               4479

//DopeFrames
#define IDL_DOPEFRAME               4480

#define IDL_PARENTTOBONE            4481

//LensFlare Channels
#define IDL_GLOWS                   4493
#define IDL_BEAMS                   4494
#define IDL_REFLECTIONS             4495

//Surfaces                     4500+
#define IDL_SEETHRU                 4502
#define IDL_PATCHESHIT              4503
#define IDL_DECALTYPE               4508
#define IDL_SEAMLESS                4509
#define IDL_MAPREPEAT               4510
#define IDL_REFERENCEMAP            4523
#define IDL_IMAGESHOWN              4524
#define IDL_IMAGE                   4526
#define IDL_APPLICATIONMETHOD       4527
#define IDL_OPACITY                 4528
#define IDL_DISPLAYASROTO           4529
#define IDL_PROPERTIESDRIVEN        4530
#define IDL_PROPERTY                4531
#define IDL_CONTRIBUTETOSHADOWCOLOR 4532
#define IDL_RELATIONNAME            4533

//Rotoscopes                    4700+
#define IDL_POSITION                4702
#define IDL_FRONTPROJECTIONMAP      4703
#define IDL_FRONTROTOSCOPE          4706
#define IDL_TOPLEFT                 4709
#define IDL_BOTTOMRIGHT             4710
#define IDL_INCLUDEINALPHABUFFER    4711
#define IDL_ROTOUSEADDITIVECOLOR    4712

//BitmapNodes                  4800+
#define IDL_BACKGROUNDCOLOR         4800
#define IDL_CACHE                   4801
#define IDL_GAMMA                   4802
#define IDL_HASBACKGROUNDCOLOR      4803
#define IDL_COMPRESSED              4804
#define IDL_CACHESIZE               4805

//Chors                         4900+

#define IDL_GRAVITY               4922
#define IDL_RADIOSITY             4927
#define IDL_GLOWRADIUS            4928
#define IDL_GLOWSTRENGTH          4929
#define IDL_PHOTONMAP             4933
#define IDL_PHOTONSAMPLEAREA      4934
#define IDL_PHOTONSAMPLES         4935
#define IDL_PHOTONINTENISITY      4936
#define IDL_PHOTONBRIGHTNESS      4937
#define IDL_PHOTONTHRESHOLD       4938
#define IDL_PHOTONRAYSCAST        4939
#define IDL_MAXBOUNCES            4940
#define IDL_FINALGATHERING        4941
#define IDL_FINALGATHERINGSAMPLES 4942
#define IDL_JITTERING             4943
#define IDL_PRECOMPUTEIRRADIANCE  4944
#define IDL_CAUSTICS              4945
#define IDL_PRESETVERSION         4946
#define IDL_PRESETNAME            4947
#define IDL_AMBIANCETYPE          4948
#define IDL_IBLMAP                4949
#define IDL_MAPPINGTYPE           4950
#define IDL_EXPOSURE              4951
#define IDL_AZIMUTH               4952
#define IDL_ELEVATION             4953
#define IDL_AMBIANCEOCCLUSION     4954
#define IDL_USEFRONTREALTIMELIGHT 4955

//Groups                       1100+

#define IDL_TEMPORARYGROUP           1110
#define IDL_HASATTRIBUTES            1111
#define IDL_FOCUSCP                  1112
#define IDL_RENDERASLINES            1113

//Cameras                      1199+
#define IDL_CAMERAFRAME              1199
#define IDL_FRONTDISTANCE            1206
#define IDL_BACKDISTANCE             1207

#define IDL_GLOWBACKGROUND           1208
#define IDL_CONEVISIBLE              1209
#define IDL_FOCALLENGTH              1210
#define IDL_FOCALDISTANCE            1211
#define IDL_FOGDISTANCE              1213
#define IDL_GLOBALAMBIANCE           1214

//renderfileinfo
#define IDL_HEIGHT                   1215
#define IDL_ASPECT                   1216
#define IDL_ALPHABUFFER              1217
#define IDL_FILEFORMAT               1218
#define IDL_STARTFRAME               1219
#define IDL_ENDFRAME                 1220
#define IDL_STEPFRAME                1221
#define IDL_FILENAME                 1222
#define IDL_FPS                      1223
#define IDL_RENDERQUALITY            1224
#define IDL_FILTERTEXTURES           1225
#define IDL_FLATSHADED               1227
#define IDL_SHOWSHADOWS              1228
#define IDL_MOTIONBLUR               1229
#define IDL_SHOWREFLECTIONS          1230
#define IDL_REFLECTIONLEVELS         1231
#define IDL_SHUTTER                  1232
#define IDL_DISPLAYBONES             1233
#define IDL_DISPLAYCPS               1234
#define IDL_SHOWDECALS               1235
#define IDL_POLYGONSPERPATCH         1236
#define IDL_SOFTEN                   1237

//camera still
#define IDL_TVSAFE                   1240
#define IDL_TITLESAFE                1241
#define IDL_CAMERAVISIBLE            1242
#define IDL_BACKGROUNDCOLORVISIBLE   1243

#define IDL_TOONRENDER               1244
#define IDL_DEPTHBUFFER              1245
#define IDL_NORMALBUFFER             1246
#define IDL_SHADOWBUFFER             1247
#define IDL_FIELDRENDER              1249
#define IDL_FIELDORDER               1250

#define IDL_TOONLINEMODE             1251
#define IDL_TOONLINETHICKNESS        1252
#define IDL_TOONLINECOLOR            1253
#define IDL_TOONSHADINGMODE          1254
#define IDL_TOONLINEPERCENT          1255
#define IDL_TOONBIAS                 1256
#define IDL_SHADEDCOLOR              1257
#define IDL_ANIMEEYEBROWS            1258
#define IDL_OBSCUREDBYLINES          1259
#define IDL_NUMPROGRESSIVE           1260
#define IDL_DISPLAYPIVOT             1261
#define IDL_ALIASEDGES               1262
#define IDL_TOONLINESONLY            1263
#define IDL_APPLYGAMMA               1264
#define IDL_SHORTCUTTOLINKEDFOGIMAGE 1265
#define IDL_FOGFRAME                 1266
#define IDL_PATCHSUBDIVISIONS        1267
#define IDL_SHOWBACKFACING           1268
#define IDL_DISPLAYGRID              1269
#define IDL_NUMPASSES                1270
#define IDL_MULTIPASS                1271
#define IDL_DOF                      1272
#define IDL_FOG                      1273
#define IDL_STEREO                   1275
#define IDL_STEREOEYESPACING         1276
#define IDL_STEREODEPTH              1277
#define IDL_ISSTEREODEPTH            1278
#define IDL_TINT                     1279
#define IDL_TINTLIGHTCOLOR           1280
#define IDL_TINTDARKCOLOR            1281
#define IDL_TINTPERCENT              1282
#define IDL_SOFTNESSCOLOR            1283
#define IDL_ISSTEREOPARALLEL         1285
#define IDL_ISSAVEANAGLYPH           1287
#define IDL_ANAGLYPHTYPE             1288
#define IDL_ANAGLYPHGLASSES          1289
#define IDL_AVERAGENORMALS           1290
#define IDL_GLOBALILLUMINATION       1291
#define IDL_GLOBALILLUMINATIONRAYS   1292
#define IDL_STEREOTYPE               1293
#define IDL_STEREOGLASSES            1294
#define IDL_OVERRIDELINES            1295
#define IDL_OVERRIDESHADING          1296
#define IDL_STEREOINTERLACEORDER     1297
#define IDL_FREEVIEWINGTYPE          1298
#define IDL_TOONBIASATTR             1299

//Lights                       1300+

#define IDL_CASTSHADOWS         1310
#define IDL_SHADOWMAP           1311 //vers < 9.0 now SHADOWTYPE
#define IDL_SHADOWMAPSOFTNESS   1312
#define IDL_INTENSITY           1313
#define IDL_VOLUMETRIC          1314
#define IDL_SPECULAR            1315
#define IDL_DIFFUSE             1316
#define IDL_QUALITY             1317
#define IDL_SHADOWMAPRESOLUTION 1318
#define IDL_SHADOWMAPBIAS       1319
#define IDL_SHADOWMAPDARKNESS   1320
#define IDL_RAYTRACESOFTSHADOWS 1321
//see Lights More
//FXs                          1322+
#define IDL_WIDTH               1322
#define IDL_FALLOFF             1323
#define IDL_CONEANGLE           1324
#define IDL_WIDTHSOFTNESS       1325
#define IDL_FALLOFFSOFTNESS     1326

#define IDL_SHADOWRAYS          1327
#define IDL_PENUMBRA            1328
#define IDL_SHADOWDISTRIBUTE    1329

//Forces                       1330+

#define IDL_FORCE                   1335
#define IDL_FORCEKIND               1336
#define IDL_MAGNITUDE               1337

//VolFXs                       1340+
#define IDL_BRIGHTNESS              1344
#define IDL_CONTRAST                1345
#define IDL_SHADOWCOLOR             1346
#define IDL_VOLSTEPS                1347
#define IDL_VOLSAMPLES              1348
#define IDL_VOLREALTIME             1349

//Projects                     1350+
#define IDL_PRODUCTVERSION          1354
#define IDL_SPLINEVERSION           1355
#define IDL_FILEINFOPOS             1356

#define IDL_FRONTVIEW               1370
#define IDL_BACKVIEW                1371
#define IDL_LEFTVIEW                1372
#define IDL_RIGHTVIEW               1373
#define IDL_TOPVIEW                 1374
#define IDL_BOTTOMVIEW              1375
#define IDL_BIRDSEYEVIEW            1376

#define IDL_WINDOWPOSITION          1380
#define IDL_CURRENTVIEW             1381
#define IDL_WINDOWCAPTION           1382
#define IDL_MODELNAME               1383
#define IDL_MODE                    1384

#define IDL_LINKEDCHOR              1390

#define IDL_FRONTVIEWPERSPECTIVE    1391
#define IDL_BACKVIEWPERSPECTIVE     1392
#define IDL_LEFTVIEWPERSPECTIVE     1393
#define IDL_RIGHTVIEWPERSPECTIVE    1394
#define IDL_TOPVIEWPERSPECTIVE      1395
#define IDL_BOTTOMVIEWPERSPECTIVE   1396
#define IDL_BIRDSEYEVIEWPERSPECTIVE 1397

//ObjectCacheContainer         1400+

#define IDL_LINKEDMODEL 1410

//ActionCacheContainer         1450+

#define IDL_LINKEDACTION 1460

//Materials                    1470+

#define IDL_LINKEDMATERIAL        1510

#define IDL_GLOBALAXIS            1517
#define IDL_BUMPMAP               1518
#define IDL_BUMPPERCENT           1519
#define IDL_OLDBUMPMAP            1520

#define IDL_START                 1522
#define IDL_EDGETHRESHOLD         1523

#define IDL_RADIUS1               1532
#define IDL_RADIUS2               1533

#define IDL_AMPLITUDE             1537

#define IDL_DISPLACEPERCENT       1540

//MuscleChannelContainer        1550+
#define IDL_CPID                  1555

//DopeSheet                       1560+
#define IDL_DOPEOFFSET            1562
#define IDL_DOPESCALE             1563
#define IDL_FRAME                 1566
#define IDL_DOPETYPE              1567
#define IDL_LINKEDDOPESHEET       1572
#define IDL_LINKEDACTIONDOPESHEET 1577

//Poses                           1580+

#define IDL_DEFAULTPERCENT       1596
#define IDL_DISPLAYSLIDER        1597
#define IDL_POSEPREVIEWPATH      1598

//Constraints                     1600+
#define IDL_OBJECTTARGET         1614
#define IDL_BONETARGET           1615
#define IDL_OBJECTTARGET2        1616
#define IDL_BONETARGET2          1617
#define IDL_PATHTARGET           1620
#define IDL_GROUPTARGET          1621
#define IDL_MIN                  1627
#define IDL_MAX                  1628
#define IDL_TRANSLATEONLY        1629
#define IDL_STOREROLL            1632
#define IDL_ACTIONOBJECTTARGET   1633
#define IDL_ACTIONOBJECTTARGET2  1634
#define IDL_LOCKOFFSETS          1635
#define IDL_SCALETOREACH         1640
#define IDL_SCALEZONLY           1641
#define IDL_SUPPORTLIMITSDAMPING 1644
#define IDL_COMPUTEROLL          1645
#define IDL_IKDAMPING            1646
#define IDL_STOREHINTS           1649
//1650+ is taken for Null Objects (see MORE CONSTRAINTS)

//Null Objects                         1650+

//Motion Capture Devices               1660+

//Sensors                              1665+

//Paths                                1670+
#define IDL_SLICECPID            1673

//Attributes
#define IDL_AMBIANCECOLOR        1698
#define IDL_DIFFUSEFALLOFF       1699
#define IDL_DIFFUSECOLOR         1700
#define IDL_AMBIANCE             1701
#define IDL_ROUGHNESS            1702
#define IDL_REFLECTIVITY         1703
#define IDL_TRANSPARENCY         1704
#define IDL_REFRACTION           1705
#define IDL_SPECULARCOLOR        1706
#define IDL_SPECULARSIZE         1707
#define IDL_SPECULARINTENSITY    1708
#define IDL_ADDITIVE             1709
#define IDL_ROUGHNESSSCALE       1710
#define IDL_GLOW                 1711
#define IDL_DENSITY              1712
#define IDL_TRANSLUCENCY         1713
#define IDL_REFLECTIVITYFALLOFF  1714
#define IDL_RADIANCE             1715
#define IDL_SURFACE              1716
#define IDL_TOONLINES            1717
#define IDL_TOONSHADING          1718
#define IDL_COLORMETHOD          1719
#define IDL_SHADINGMETHOD        1720
#define IDL_NORMALWEIGHT         1721
#define IDL_DENSITYFACTOR        1722
#define IDL_REFLECTIVEBLEND      1723
#define IDL_REFLECTIONFILTER     1724
#define IDL_SUBSURFACESCATTERING 1725
#define IDL_AMBIANCEBLEND        1726
#define IDL_STARTATBIRTH         1727
#define IDL_REPEATSEQUENCE       1728
#define IDL_RANDOMSEQUENCE       1729

//Props                                1730+
#define IDL_PROPSCALE            1730
#define IDL_PROPTEXTURING        1731

//Containers

//MatFXs                               1770+

//More RenderInfo
#define IDL_SOFTREFLECTION               1790
#define IDL_SOFTREFLECTIONQUALITY        1791
#define IDL_AMBIANCEOCCLUSIONQUALITY     1792
#define IDL_AMBIANCEOCCLUSIONFALLOFF     1793
#define IDL_ISSUBSURFACESCATTERING       1794
#define IDL_ISTRANSPARENTAO              1795

//NetRender                             1800+
#define IDL_NETGPU                       1818
#define IDL_AUTOJOIN                     1819
#define IDL_PROJECTNAME                  1820
#define IDL_CHORNAME                     1821
#define IDL_CAMERATREENAME               1822
#define IDL_OUTPUTNAME                   1823
#define IDL_CUSTOMRANGE                  1824
#define IDL_NODENAME                    1825
#define IDL_STATUS                       1826
#define IDL_PERCENTCOMPLETE              1827
#define IDL_STARTTIME                    1828
#define IDL_ENDTIME                      1829
#define IDL_ISCUSTOMRANGE                1830
#define IDL_OS                           1831
#define IDL_RAM                          1832
#define IDL_NODEEXE                     1833
#define IDL_USERDATA                     1834
#define IDL_VALIDNODE                   1835
#define IDL_NETOMP                       1836
#define IDL_TIME                         1837
#define IDL_JOBNAME                      1838
#define IDL_ELAPSETIME                   1839
#define IDL_DISABLED                     1840
#define IDL_PCNODENAME                  1841
#define IDL_PCFOLDERNAME                 1842
#define IDL_PCSCHEMENAME                 1843
#define IDL_MACNODENAME                 1844
#define IDL_MACFOLDERNAME                1845
#define IDL_MACSCHEMENAME                1846
#define IDL_OUTPUTFORMAT                 1847
#define IDL_CAMERAMATCHNAME              1848
#define IDL_SORTORDER                    1849

//Particles                            1850+
#define IDL_LIFEVARIATION                1850
#define IDL_RATEVARIATION                1851
#define IDL_OPACITYVARIATION             1852
#define IDL_OPACITYOVERLIFE              1853
#define IDL_SIZEVARIATION                1854
#define IDL_SIZEOVERLIFE                 1855
#define IDL_SPINVARIATION                1856

#define IDL_MASSVARIATION                1858
#define IDL_MASSOVERLIFE                 1859
#define IDL_GRAVITATIONALAFFECTVARIATION 1860
#define IDL_GRAVITATIONALAFFECTOVERLIFE  1861
#define IDL_BOUNCEVARIATION              1862
#define IDL_BOUNCEOVERLIFE               1863
#define IDL_ANGLEMETHOD                  1864
#define IDL_ANGLEVARIATION               1865
#define IDL_SPINOVERLIFE                 1866
#define IDL_VELOCITYVARIATION            1867
#define IDL_SINGLEPARTICLE               1868
#define IDL_DRAGVARIATION                1869
#define IDL_DRAGOVERLIFE                 1870

#define IDL_PHYSICSCATEGORY              1871
#define IDL_PRESSURE                     1872
#define IDL_SURFACETENSION               1873
#define IDL_FLUIDMODELGENCATEGORY        1874
#define IDL_MCSAMPLESCALE                1875
#define IDL_SMOOTHINTENSITY              1876
#define IDL_SMOOTHITERATIONS             1877
#define IDL_NUMSUBDIVISIONS              1878
#define IDL_SLIDE                        1879
#define IDL_PARTICLEBAKED                1880
#define IDL_PARTICLEBAKEDFILENAME        1881
#define IDL_PARTICLEBAKEDIDXNAME         1882
#define IDL_PARTICLEBAKEDCHORTIME        1883
#define IDL_FLUIDCLIPPING                1884
#define IDL_FLUIDCULL                    1885
#define IDL_FLUIDHIGHRESCD               1886

#define IDL_MAXDISTANCEPEREMIT           1909

#define IDL_LIFE                         1910
#define IDL_RATE                         1911
#define IDL_VELOCITY                     1912
#define IDL_BOUNCE                       1913
#define IDL_VISCOSITY                    1914
#define IDL_SIZEATBIRTH                  1915
#define IDL_SIZETOLERENCE                1916
#define IDL_PARTICLECOLLISIONS           1917
#define IDL_OBJECTCOLLISIONS             1918
#define IDL_DIEONIMPACT                  1919
#define IDL_TAILDURATION                 1920
#define IDL_THICKNESS                    1921
#define IDL_SIZEATDEATH                  1922
#define IDL_BLOBBINESS                   1923
#define IDL_PREROLL                      1924
#define IDL_SIZE                         1925
#define IDL_SPIN                         1926
#define IDL_GRAVITATIONALAFFECT          1927
#define IDL_PARTICLESHADOWS              1928
//SHAG ONLY
#define IDL_DYNAMICS                     1929
#define IDL_PARTICLEACTIVE               1930

#define IDL_PARTICLEOVERTIME             1931

//Fur
#define IDL_ATTRVARIATION           1932
#define IDL_THICKNESSVARIATION      1933
#define IDL_KINKINESSVARIATION      1934
#define IDL_KINKSCALEVARIATION      1935
#define IDL_ACCURATTRANSPARENCY     1936
#define IDL_STIFFNESS               1937

//Shag
#define IDL_KINKINESS               1938
#define IDL_KINKSCALE               1939
#define IDL_SHAGLENGTH              1942
#define IDL_SHAGSTIFFNESS           1943
#define IDL_SHAGDENSITY             1944
#define IDL_SHAGTHICKNESS           1945

#define IDL_FURLENGTH               IDL_SHAGLENGTH        //1932
#define IDL_FURSTIFFNESS            IDL_SHAGSTIFFNESS     //1933
#define IDL_FURDENSITY              IDL_SHAGDENSITY       //1934
#define IDL_FURTHICKNESS            IDL_SHAGTHICKNESS     //1935

#define IDL_HASGEOMETRY             1948
#define IDL_CLUMPINESS              1949

#define IDL_RANDOMSEED              1952

//Lens Flares
#define IDL_LENSFLARE               1953
#define IDL_POLYNUM                 1955
#define IDL_ISPOLYGON               1956
#define IDL_GLOWPRESET              1957
#define IDL_BEAMPRESET              1958
#define IDL_REFLECTPRESET           1959
#define IDL_ISCREATELENSFLARE       1960
#define IDL_ISFADEWITHDISTANCE      1961
#define IDL_ISFADELEAVINGVIEW       1962
#define IDL_ISFADEBEHINDOBJECTS     1963
#define IDL_ISFADEWITHAIM           1964
#define IDL_FLAREGLOBALANGLE        1965
#define IDL_FLAREGLOBALINTENSITY    1966
#define IDL_FLAREGLOBALSCALE        1967

#define IDL_FLAREFADEDISTANCE       1969
#define IDL_FLARESCALE              1970

#define IDL_FLARESPECTRUM           1972
#define IDL_FLAREZONES              1973
#define IDL_FLAREOCTAVES            1974
#define IDL_FLAREANGLE              1975
#define IDL_FLARERANDOMDISTRIBUTION 1976
#define IDL_FLARERANDOMLENGTH       1977
#define IDL_FLARESHAPE              1978
#define IDL_FLAREFILLTYPE           1979
#define IDL_FLARETHICKNESS          1980
#define IDL_FLAREGRADIN             1981
#define IDL_FLAREGRADOUT            1982
#define IDL_FLARENAME               1983
#define IDL_FLARECOLOR              1984
#define IDL_FLARESPECTRUMCOUNT      1985
#define IDL_FLAREZONECOVERAGE       1986
#define IDL_FLAREOCTAVELEN          1987
#define IDL_FLAREMINLEN             1988
#define IDL_FLAREMAXLEN             1989
#define IDL_FLARELENGTH             1990
#define IDL_FLAREINTENSITY          1995
#define IDL_FLARESOFTNESS           1996
#define IDL_FLARECOUNT              1997
#define IDL_FLAREPOSITION           1998
#define IDL_FLARERADIUS             1999

//Sounds

#define IDL_VOLUME           2004
#define IDL_MUTE             2005
#define IDL_LINKEDSOUND      2010
#define IDL_HIDDENINTIMELINE 2011
#define IDL_SOUND            2012

//Text
#define IDL_DISPLAYNAME      2035
#define IDL_HASTRANSLATED    2036

//Clips

#define IDL_LINKEDCLIP             2060
#define IDL_RAYSCAST               2061
#define IDL_MAPSCALE               2062
#define IDL_MINMAPSIZE             2063
#define IDL_MAXMAPSIZE             2064
#define IDL_TIMING                 2065
#define IDL_SPEED                  2066
#define IDL_CLIPRANGE              2067

#define IDL_LINKEDLIGHT            2072
#define IDL_LINKEDCAMERA           2073

#define IDL_FOGSTART               2092
#define IDL_FOGEND                 2093

#define IDL_BUFFERID               2096
#define IDL_BUFFERNAME             2097

#define IDL_INSTANCECROPSTYLE      2098

//SMARTSKIN
#define IDL_AXISNUMBER             2106

//RELATIONSHIPS
#define IDL_RADIUSFACTOR           2156
#define IDL_KEY                    2161
#define IDL_KEYDIM                 2162
#define IDL_VALUEDIM               2163

//SPRINGSYSTEM
#define IDL_MASS                   2210
#define IDL_MASS1                  2211
#define IDL_MASS2                  2212
#define IDL_CONSTANT               2213
#define IDL_DAMPING                2214
#define IDL_RESTLENGTH             2215
#define IDL_SPRINGSYSTEM           2218
#define IDL_MASSNUMBER             2219
#define IDL_CLOTHDRAG              2222
#define IDL_MASSDRAG               2223
#define IDL_COLLISIONRADIUS        2224
#define IDL_DISPLAYWHILESIMULATING 2225
#define IDL_COLLISIONRADIUSPERCENT 2226
#define IDL_AIMONLY                2227
#define IDL_REVERSEDIRECTION       2228
#define IDL_ISFIXED                2229
#define IDL_SPRINGTYPE             2230
#define IDL_USESSYSTEM             2231
#define IDL_ISCLOTH                2232
#define IDL_STRUCTSTIFFNESS        2233
#define IDL_STRUCTDAMPING          2234
#define IDL_SHEARSTIFFNESS         2235
#define IDL_SHEARDAMPING           2236
#define IDL_FOLDSTIFFNESS          2237
#define IDL_FOLDDAMPING            2238
#define IDL_OVERRIDESYSTEM         2239
#define IDL_SUBDIV                 2240
#define IDL_MASSSETTINGS           2243
#define IDL_SPRINGSETTINGS         2244
#define IDL_CLOTHSETTINGS          2245
#define IDL_STRUCTSETTINGS         2246
#define IDL_SHEARSETTINGS          2247
#define IDL_FOLDSETTINGS           2248
#define IDL_SPRING                 2249
#define IDL_REDUCTIONERROR         2250

//More Constraints                     2300+

//FlockFXs                             2400+
#define IDL_POPULATION       2441
#define IDL_ANTIGRAVITY      2442
#define IDL_DRAWASDOTS       2443
#define IDL_MAXACTIONOFFSET  2444

//RIGID BODY
#define IDL_INVERSEMASS      2502
#define IDL_IBODY            2503
#define IDL_MINVEL           2504
#define IDL_COLLIDEWITH      2505
#define IDL_DRAG             2506
#define IDL_SUBSAMPLES       2507

//DYNAMIC CONSTRAINT
#define IDL_FREQUENCY        2525
#define IDL_USEGRAVITY       2526
#define IDL_USEFORCES        2527
#define IDL_ANGLELIMIT       2528
#define IDL_TARGETING        2529
#define IDL_DYNAMICOPTIONS   2530
#define IDL_SIMULATEONTHEFLY 2531

//SHADER PLUGIN TOGGLES
#define IDL_SHADERS          2550
#define IDL_ISDIFFUSESHADER  2551
#define IDL_ISSPECULARSHADER 2552
#define IDL_DIFFUSENAME      2553
#define IDL_SPECULARNAME     2554

#define IDL_ISAMBIANCESHADER 2567
#define IDL_AMBIANCENAME     2568

//DRIVERS

//CPS

//USER PROPERTIES
#define IDL_PLUGINPROPERTIES           2693
#define IDL_FACTORVALUE                2694
#define IDL_UNIT                       2695
#define IDL_ILLEGALCHARS               2696
#define IDL_TITLE                      2701
#define IDL_FILTER                     2702
#define IDL_EXTENSION                  2703
#define IDL_REGLOOKUP                  2704
#define IDL_ISOPENDIALOG               2715

//MUSCLE
#define IDL_INBIAS                     2720
#define IDL_OUTBIAS                    2721
#define IDL_BIAS                       2722

//RENDERSETTINGS
#define IDL_RENDEROPTIONS              2738
#define IDL_MULTIPASSDOF               2740
#define IDL_MULTIPASSMOTIONBLUR        2741
#define IDL_MULTIPASSMOTIONBLURPERCENT 2742
#define IDL_SAVEBUFFER                 2743
#define IDL_SAVELIGHTBUFFER            2744
#define IDL_UNPREMULTIPLIEDALPHA       2745
#define IDL_POST                       2750
#define IDL_GAMMAAMOUNT                2752
#define IDL_DEANTIALIAS                2753

//OUTPUTSETTINGS
#define IDL_OUTPUTOPTIONS              2798
#define IDL_FORMAT                     2799
#define IDL_RESOLUTION                 2800
#define IDL_GAMMAPRESET                2801
#define IDL_BUFFERS                    2802
#define IDL_SCALEOUTPUT                2803
#define IDL_OUTPUTRESOLUTION           2804
#define IDL_OUTPUTWIDTH                2805
#define IDL_OUTPUTHEIGHT               2806
#define IDL_SAVEOPTIONS                2807
#define IDL_LIGHTBUFFERS               2808
#define IDL_LIGHTBUFFERTYPE            2809

#define IDL_BACKGROUND                 2866

//MORE USER PROPERTIES
#define IDL_COMPRESSION                2874

//EVEN MORE CONSTRAINTS                2900-2949
#define IDL_ENFORCEMENT                2902
#define IDL_EASE                       2903
#define IDL_LAG                        2904
#define IDL_TRANSLATE2                 2905
#define IDL_ROLLOFFSET                 2906
#define IDL_ROLLSCALE                  2907
#define IDL_LATITUDE                   2908
#define IDL_LONGITUDE                  2909
#define IDL_BEFOREACTION               2912
#define IDL_SCALEOFFSET                2913
#define IDL_SCALESCALE                 2914
#define IDL_KIND                       2915
#define IDL_FRICTION                   2918
#define IDL_ISROD                      2919
#define IDL_ADJUSTDOF                  2920

//Lights MORE
#define IDL_SHADOWTYPE                 3000  //was equal to #define IDL_FREEVIEWINGTYPE     1298
#define IDL_RAYBIAS                    3001
#define IDL_ATTENUATION                3002

//GUIDE HAIRS
#define IDL_HAIRCP                     3022
#define IDL_SPLINE                     3023

//HAIR
#define IDL_DIRECTIONVARIATION         3052
#define IDL_INDEX                      3059
#define IDL_GEOMETRY                   3062
#define IDL_FACECAMERA                 3065
#define IDL_FACECAMERAVARIATION        3066
#define IDL_BOW                        3067
#define IDL_BOWVARIATION               3068
#define IDL_POSITIONVARIATION          3069
#define IDL_CAPENDS                    3070
#define IDL_BRIGHTENFACINGHAIRS        3071
#define IDL_OPAQUEINREFLECTIONS        3072
#define IDL_JITTER                     3072
#define IDL_CULLHAIRS                  3073

//PostEffects
#define IDL_LINKEDPOST                 3104
#define IDL_APPLYPOSTEFFECTSTORENDER   3111
//give me room

//Composites
#define IDL_ISSEQUENCE      3534
#define IDL_LINKEDCOMPOSITE 3537
//give me room

//Subsurface Scattering                3600+
#define IDL_SSS                        3601
#define IDL_SSSEXTINCTION              3602
#define IDL_SSSABSORPTION              3603
#define IDL_SSSIOR                     3604
#define IDL_SSSSAMPLES                 3605
#define IDL_SSSEXTEND                  3606

#define IDL_CAMERACONE                 3700

//Net Render More                       3800+
#define IDL_SORTKEY                    3800
#define IDL_AVGFRAMETIME               3801
#define IDL_FRAMESRENDERED             3802
#define IDL_TOTALFRAMETIME             3803

//Light Lists                           4000+
#define IDL_LIGHTPARENT                4000

//GPU Shaders                           5100+
#define IDL_USEGPU                     5100
#define IDL_GPUEACHPASS                5101
#define IDL_GPUBLUR                    5102
#define IDL_GPUBLURMERGE               5103
#define IDL_GPUBLURSAMPLES             5104
#define IDL_GPUBLURRADIUS              5105
#define IDL_GPUMISC                    5106
#define IDL_GPUMISCMERGE               5107
#define IDL_GPUMISCSAMPLES             5108
#define IDL_GPUMISCTYPE                5109
#define IDL_SSAO                       5110
#define IDL_SSAOMERGE                  5111
#define IDL_SSAOSAMPLES                5112
#define IDL_SSAORADIUS                 5113
#define IDL_SSAOLUM                    5114
#define IDL_SSAOAOONLY                 5115
#define IDL_SSAOBLUR                   5116
#define IDL_SSAOBLURRADIUS             5117
#define IDL_SSAODISTANCE               5118
#define IDL_SSAOGAMMA                  5119
#define IDL_SSAODIFFUSION              5120
#define IDL_SSAOSOFTNESS               5121
#define IDL_SSAOFALLBACK               5122

//Bullet                                5300+
#define IDL_BULLETSHAPE                5300
#define IDL_BULLETWEIGHT               5301
#define IDL_BULLETBOUNCE               5302
#define IDL_BULLETFRICTION             5303
#define IDL_BULLETLDAMP                5304
#define IDL_BULLETADAMP                5305
#define IDL_BULLETMARGIN               5306
#define IDL_BULLETHULL                 5307
#define IDL_BULLETROLLINGFRICTION      5308
#define IDL_BULLETSTATIC               5309
#define IDL_BULLETUSESTATIC            5310
#define IDL_BULLETSTATICWITHACTION     5311
#define IDL_BULLETJOINT                5312
#define IDL_BULLETUSEJOINT             5313
#define IDL_BULLETJOINTBREAK           5314
#define IDL_BULLETJOINTCENTER          5315
#define IDL_BULLETDEACTIVATION         5316
#define IDL_BULLETJOINTAXIS            5317
#define IDL_BULLETUSELINEARLIMIT       5318
#define IDL_BULLETLOWLINLIMIT          5319
#define IDL_BULLETUPLINLIMIT           5320
#define IDL_BULLETUSEANGULARLIMIT      5321
#define IDL_BULLETLOWANGLIMIT          5322
#define IDL_BULLETUPANGLIMIT           5323
#define IDL_BULLETUSEANGULARMOTOR      5324
#define IDL_BULLETUSELINEARMOTOR       5325
#define IDL_BULLETANGULARMOTORACTIVE   5326
#define IDL_BULLETANGULARMOTORVELOCITY 5327
#define IDL_BULLETLINEARMOTORACTIVE    5328
#define IDL_BULLETLINEARMOTORVELOCITY  5329
#define IDL_BULLETSWING1LIMIT          5330
#define IDL_BULLETSWING2LIMIT          5331
#define IDL_BULLETTWISTLIMIT           5332
#define IDL_BULLETXANGLOW              5333
#define IDL_BULLETXANGUP               5334
#define IDL_BULLETXLINLOW              5335
#define IDL_BULLETXLINUP               5336
#define IDL_BULLETYANGLOW              5337
#define IDL_BULLETYANGUP               5338
#define IDL_BULLETYLINLOW              5339
#define IDL_BULLETYLINUP               5340
#define IDL_BULLETZANGLOW              5341
#define IDL_BULLETZANGUP               5342
#define IDL_BULLETZLINLOW              5343
#define IDL_BULLETZLINUP               5344
#define IDL_BULLETXLIN                 5345
#define IDL_BULLETYLIN                 5346
#define IDL_BULLETZLIN                 5347
#define IDL_BULLETXANG                 5348
#define IDL_BULLETYANG                 5349
#define IDL_BULLETZANG                 5350
#define IDL_BULLETXSPRING              5351
#define IDL_BULLETXSPRINGSTIFF         5352
#define IDL_BULLETXSPRINGSDAMP         5353
#define IDL_BULLETYSPRING              5354
#define IDL_BULLETYSPRINGSTIFF         5355
#define IDL_BULLETYSPRINGSDAMP         5356
#define IDL_BULLETZSPRING              5357
#define IDL_BULLETZSPRINGSTIFF         5358
#define IDL_BULLETZSPRINGSDAMP         5359
#define IDL_BULLETXASPRING             5360
#define IDL_BULLETXASPRINGSTIFF        5361
#define IDL_BULLETXASPRINGSDAMP        5362
#define IDL_BULLETYASPRING             5363
#define IDL_BULLETYASPRINGSTIFF        5364
#define IDL_BULLETYASPRINGSDAMP        5365
#define IDL_BULLETZASPRING             5366
#define IDL_BULLETZASPRINGSTIFF        5367
#define IDL_BULLETZASPRINGSDAMP        5368
#define IDL_BULLETHULLEND              5369
#define IDL_BULLETANISOTROPICFRICTION  5370
#define IDL_BULLETFRACTURE             5371
#define IDL_BULLETLSTIFFNESS           5372
#define IDL_BULLETASTIFFNESS           5373
#define IDL_BULLETVSTIFFNESS           5374
#define IDL_BULLETVOLUMEPRESERVATION   5375
#define IDL_BULLETPOSEMATCHING         5376
#define IDL_BULLETVOLMATCHING          5377
#define IDL_BULLETCLUSTER              5378
#define IDL_BULLETDAMPING              5379
#define IDL_BULLETANCHORSTIFF          5380
#define IDL_BULLETSUBDIVIDE            5381
#define IDL_BULLETBENDING              5382
#define IDL_BULLETPRESSURE             5383
#define IDL_BULLETSPININNGFRICTION     5384
//something new                         5500+
