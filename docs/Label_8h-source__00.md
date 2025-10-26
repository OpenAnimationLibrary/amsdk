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

# Label.h

[Go to the documentation of this file.](Label_8h.md)

<div class="fragment">

``` fragment
00001 // BC  6/13/2005  \Master120\Include\Label.h
00002 // MH  4 Oct 2002  added IDL_VOLSTEPS (replacing "QUALITY")
00003 // MH  19 Aug 2002  added IDL_DISPLACEPERCENT
00004 // MH  19 Jul 2002  added IDL_PENUMBRA
00005 // MH  12 Apr 2002  added IDL_PHOTONSAMPLES, deleted IDL_OCTREELEVELS
00006 
00007 // Generic Terms
00008 #define IDL_NOLABEL            -2
00009 #define IDL_VERSION             1
00010 #define IDL_PLATFORM            2
00011 #define IDH_CHILD               3
00012 #define IDH_ENDCHILD            4
00013 #define IDH_SIBLING             5
00014 #define IDH_ENDSIBLING          6
00015 #define IDL_NAME                7
00016 #define IDL_EMBEDDED            8
00017 #define IDL_COUNT               9
00018 #define IDL_TYPE                10
00019 #define IDL_VALUE               11
00020 #define IDL_IMAGESEQUENCE       12
00021 #define IDL_OFFSET              13
00022 #define IDL_VIEW                14
00023 #define IDL_VISIBLE             15
00024 #define IDL_EDITABLE            16
00025 #define IDL_SHORTCUTTO          17
00026 #define IDL_DESCRIPTION         18
00027 #define IDL_OBJECT              19
00028 #define IDL_COLOR               20
00029 #define IDL_EXPANDED            21
00030 #define IDL_SELECTED            22
00031 #define IDL_RANGE               23
00032 #define IDL_MATRIX              24
00033 #define IDL_PICKABLE            25
00034 #define IDH_ICON                26
00035 #define IDH_ENDICON             27
00036 #define IDL_SCALE               28
00037 #define IDL_TRANSLATE           29
00038 #define IDL_BLUR                30
00039 #define IDL_SHORTCUTTOLINKED    31
00040 #define IDL_DLLNAME             32
00041 #define IDL_MODIFIED            33
00042 #define IDL_AIM                 34
00043 #define IDL_ROLL                35
00044 #define IDL_CLASSNAME           36
00045 #define IDL_PLUGINNAME          37
00046 #define IDL_MARKER              38
00047 #define IDL_CREATEDBY           39
00048 #define IDL_LASTMODIFIEDBY      40
00049 #define IDL_NOTES               41
00050 #define IDL_PLAYRANGE           42
00051 #define IDL_PLATFORMID          43
00052 #define IDL_VIEW1               44
00053 #define IDL_ROTATE              45
00054 #define IDL_ACTIVE              46
00055 #define IDH_TRANSFORM           47
00056 #define IDH_ENDTRANSFORM        48
00057 #define IDL_LOCKED              49
00058 #define IDL_ANGLE               50
00059 #define IDL_MATCHNAME           51
00060 #define IDL_X                   52
00061 #define IDL_Y                   53
00062 #define IDL_Z                   54
00063 #define IDL_W                   55
00064 #define IDL_OPTIONS             56
00065 #define IDL_TRANSFORM           57
00066 #define IDL_RED                 58
00067 #define IDL_GREEN               59
00068 #define IDL_BLUE                60
00069 #define IDL_URL                 61
00070 #define IDL_EMAIL               62
00071 #define IDL_ORGANIZATION        63
00072 #define IDL_PREVIEW             64
00073 #define IDL_FILEINFO            65
00074 #define IDL_TACKEDOBJECT        66
00075 #define IDL_LENGTH              67
00076 #define IDL_INSTANCE            68
00077 #define IDL_CHILD               69
00078 #define IDH_LINKED              70
00079 #define IDH_ENDLINKED           71
00080 #define IDL_MORETHANDRIVERS     72
00081 // Misc
00082 #define IDH_SCHEME              80
00083 #define IDH_FILTER              81
00084 #define IDH_ENDFILTER           82
00085 #define IDH_FILTERLIST          83
00086 #define IDL_SEARCHSTRING        84
00087 
00088 #define IDH_OBJECTSHORTCUT      90
00089 #define IDH_ENDOBJECTSHORTCUT   91
00090 #define IDH_CPSHORTCUT          92
00091 #define IDH_ENDCPSHORTCUT       93
00092 #define IDH_SPLINESHORTCUT      94
00093 #define IDH_ENDSPLINESHORTCUT   95
00094 #define IDH_SPLINECONTAINERSHORTCUT      96
00095 #define IDH_ENDSPLINECONTAINERSHORTCUT   97
00096 
00097 // Figures                      100+
00098 #define IDH_FIGURESHORTCUT      100
00099 #define IDH_ENDFIGURESHORTCUT   101
00100 #define IDH_PATHFIGURE          102
00101 #define IDH_ENDPATHFIGURE       103
00102 #define IDH_MODELSHORTCUT       104
00103 #define IDH_ENDMODELSHORTCUT    105
00104 #define IDH_PATHMODEL           106
00105 #define IDH_ENDPATHMODEL        107
00106 #define IDH_WEATHERMAP          108
00107 #define IDH_ENDWEATHERMAP       109
00108 
00109 #define IDL_DRAWMODEOVERRIDE    110
00110 #define IDL_DRAWMODE            111
00111 #define IDL_WIREFRAME           112
00112 #define IDL_SHADED              113
00113 #define IDL_MASCOTNAME          114
00114 #define IDL_NAMECHANGED         115
00115 #define IDL_ANIMATEMODE         116
00116 #define IDL_PERSPECTIVE         117
00117 #define IDL_TEMPPERSPECTIVE     118
00118 #define IDL_DRAWSYSTEMS         119
00119 
00120 #define IDL_FRONTPROJECTIONTARGET 120
00121 #define IDL_CASTREFLECTIONS     122
00122 #define IDL_RECEIVESHADOWS      123
00123 
00124 #define IDH_LIGHTLIST           124
00125 #define IDH_ENDLIGHTLIST        125
00126 #define IDL_LIGHTALL            126
00127 #define IDH_LIGHTLISTNODE       127
00128 #define IDH_ENDLIGHTLISTNODE    128
00129 #define IDL_SHADOWONLY          129
00130 #define IDH_LAYER               130
00131 #define IDH_ENDLAYER            131
00132 #define IDH_LAYERSHORTCUT       132
00133 #define IDH_ENDLAYERSHORTCUT    133
00134 #define IDL_GROUP               134
00135 #define IDH_DISTORTSHORTCUT     135
00136 #define IDH_ENDDISTORTSHORTCUT  136
00137 #define IDL_LINKEDDISTORT       137
00138 #define IDH_DISTORTFILE         138
00139 #define IDH_ENDDISTORTFILE      139
00140 #define IDH_DISTORT             140
00141 #define IDH_ENDDISTORT          141
00142 #define IDL_XRES                142
00143 #define IDL_YRES                143
00144 #define IDL_ZRES                144
00145 #define IDL_IGNOREFOG           145
00146 
00147 // Actions                      150+
00148 #define IDH_ACTION              150
00149 #define IDH_ENDACTION           151
00150 #define IDH_ACTIONSHORTCUT      152
00151 #define IDH_ENDACTIONSHORTCUT   153
00152 #define IDL_USESTRIDE           154
00153 #define IDL_OVERLAPPING         155
00154 #define IDL_HOLDLASTFRAME       156
00155 #define IDL_TRANSITIONNAME      157
00156 #define IDL_REPEATCOUNT         158
00157 #define IDL_TRANSITIONTONEXT    159
00158 
00159 #define IDL_ACTIONSEQUENCE      160
00160 #define IDL_CROPSTARTFRAME      161
00161 #define IDL_CROPENDFRAME        162
00162 #define IDL_CHORSTARTFRAME      163
00163 #define IDL_CHORFRAMES          164
00164 #define IDH_BONES               166
00165 #define IDH_ENDBONES            167
00166 #define IDL_CROPRANGE           168
00167 #define IDL_CHORRANGE           169
00168 #define IDL_BLENDRATIO          170
00169 #define IDL_CYCLELENGTH         171
00170 #define IDL_BLENDMETHOD         172
00171 #define IDL_CROP                173
00172 
00173 // FigureCaches                 200+
00174 #define IDH_FIGUREFILE          200
00175 #define IDH_ENDFIGUREFILE       201
00176 #define IDH_MESH                202
00177 #define IDH_ENDMESH             203
00178 #define IDH_FIGURE              204
00179 #define IDH_ENDFIGURE           205
00180 #define IDH_PATCHES             206
00181 #define IDH_ENDPATCHES          207
00182 #define IDH_AVA                 208
00183 #define IDH_ENDAVA              209
00184 
00185 #define IDL_GREATESTCPID        210
00186 #define IDL_TOTALPATCHES        211
00187 #define IDL_PIVOT               212
00188 #define IDL_SPLINES             213
00189 #define IDL_CPS                 214
00190 #define IDL_HASBOOLEANS         215
00191 #define IDL_POSETOCLEARWITH     216
00192 #define IDL_ALPHA               217
00193 
00194 #define IDH_ATTRS               220 // realtime stuff
00195 #define IDH_ENDATTRS            221
00196 #define IDH_NORMALS             222
00197 #define IDH_ENDNORMALS          223
00198 
00199 #define IDH_MODELFILE           230
00200 #define IDH_ENDMODELFILE        231
00201 #define IDH_MODEL               232
00202 #define IDH_ENDMODEL            233
00203 
00204 #define IDL_SILCOLOR            235
00205 #define IDL_SILPCT              236
00206 #define IDL_SILTHICKNESS        237
00207 #define IDL_SILUSEOBJECTCOLOR   238
00208 
00209 #define IDL_PERCENT             240
00210 #define IDL_SOFTNESS            241
00211 #define IDL_USEOBJECTCOLOR      242
00212 #define IDL_SHADINGMODE         243
00213 #define IDL_GRADIENTKEY         244
00214 #define IDL_GRADIENT            245
00215 #define IDL_GRADIENTPROPERTY    246
00216 
00217 
00218 // ActionCaches                 250+
00219 #define IDH_ACTIONFILE          250
00220 #define IDH_ENDACTIONFILE       251
00221 
00222 #define IDH_OLDACTIONFILE       255
00223 
00224 #define IDL_FRAMES              260
00225 #define IDL_HASSTRIDE           154//261 to share usestride
00226 #define IDL_STRIDESTARTFRAME    262
00227 #define IDL_STRIDEENDFRAME      263
00228 #define IDL_STRIDESTARTPOSITION 264
00229 #define IDL_STRIDEENDPOSITION   265
00230 #define IDL_DEFAULTMODEL        266
00231 #define IDL_SCALEACTION         267
00232 #define IDL_SCALEBASIS          268
00233 #define IDL_SCALEBONENAME       269
00234 #define IDL_SCALESTANDARD       270
00235 #define IDL_STRIDELENGTH        271
00236 #define IDL_STRIDETIMERANGE     272
00237 #define IDL_SCALEMETHOD         273
00238 
00239 // BoneCaches                   300+
00240 #define IDL_END                 310
00241 #define IDL_ROLLHANDLE          311
00242 #define IDL_BONECOLOR           312
00243 #define IDL_RENDEREDCOLOR       313
00244 #define IDL_BOUNDS              314
00245 #define IDL_CHAINED             315
00246 #define IDL_HIDDEN              316
00247 #define IDL_USERMOVED           317
00248 #define IDL_ROLLMETHOD          318
00249 #define IDL_MANIPULATION        319
00250 #define IDL_LIMITMANIPULATORS   320
00251 #define IDL_ALLOWXTRANSLATE     321
00252 #define IDL_ALLOWYTRANSLATE     322
00253 #define IDL_ALLOWZTRANSLATE     323
00254 #define IDL_ALLOWXSCALE         324
00255 #define IDL_ALLOWYSCALE         325
00256 #define IDL_ALLOWZSCALE         326
00257 #define IDL_ALLOWXROTATE        327
00258 #define IDL_ALLOWYROTATE        328
00259 #define IDL_ALLOWZROTATE        329
00260 #define IDL_BONEPOS             330
00261 #define IDL_EULERORDER          331
00262 
00263 // SegmentCaches                400+
00264 #define IDH_SEGMENT             400
00265 #define IDH_ENDSEGMENT          401
00266 #define IDH_SKINNEDCPS          402
00267 #define IDH_NONSKINNEDCPS       403
00268 #define IDH_ENDNONSKINNEDCPS    404
00269 #define IDH_WEIGHTEDCPS         405
00270 #define IDH_ENDWEIGHTEDCPS      406
00271 #define IDL_HASFALLOFF          407
00272 
00273 #define IDL_BOOLEANCUTTER       410
00274 #define IDL_PIVOTINNER          411
00275 #define IDL_PIVOTOUTER          412
00276 #define IDL_ENDINNER            413
00277 #define IDL_ENDOUTER            414
00278 #define IDL_PIVOTSCALE          415
00279 #define IDL_ENDSCALE            416
00280 #define IDL_FALLOFFTYPE         417
00281 #define IDL_BONEFALLOFFCURVE    418
00282 
00283 // Channels                     420+
00284 #define IDH_FXSKELETALCHANNEL    420
00285 #define IDH_ENDFXSKELETALCHANNEL 421
00286 #define IDH_VOLFXSKELETALCHANNEL    422
00287 #define IDH_ENDVOLFXSKELETALCHANNEL 423
00288 #define IDH_MATFXSKELETALCHANNEL    424
00289 #define IDH_ENDMATFXSKELETALCHANNEL 425
00290 #define IDH_FORCESKELETALCHANNEL    426
00291 #define IDH_ENDFORCESKELETALCHANNEL 427
00292 
00293 #define IDH_LAYERSKELETALCHANNEL    428
00294 #define IDH_ENDLAYERSKELETALCHANNEL 429
00295 #define IDH_LAYERCHORCHANNEL        430
00296 #define IDH_ENDLAYERCHORCHANNEL     431
00297 
00298 #define IDH_SKELETALCHANNEL     452
00299 #define IDH_ENDSKELETALCHANNEL  453
00300 #define IDH_CHANNELITEM         454
00301 #define IDH_ENDCHANNELITEM      455
00302 #define IDH_CAMERASKELETALCHANNEL    458
00303 #define IDH_ENDCAMERASKELETALCHANNEL 459
00304 #define IDH_LIGHTSKELETALCHANNEL     460
00305 #define IDH_ENDLIGHTSKELETALCHANNEL  461
00306 #define IDH_MODELSKELETALCHANNEL     462
00307 #define IDH_ENDMODELSKELETALCHANNEL  463
00308 
00309 #define IDL_DEFAULTVALUE        464
00310 #define IDL_MINVALUE            465
00311 #define IDL_MAXVALUE            466
00312 #define IDL_MAXCHANNELITEMS     467
00313 #define IDL_INTERPOLATION       468
00314 #define IDL_REPEAT              469
00315 // SkeletalChannels
00316 #define IDL_BONEDIRECTION       470
00317 #define IDL_ROLLDIRECTION       471
00318 #define IDL_PARENTBONEDIR       472
00319 #define IDL_PARENTROLLDIR       473
00320 #define IDL_STOPCHAIN           474
00321 #define IDL_EULERINTERP         475
00322 #define IDL_ANGLEINTERP         476
00323 #define IDL_BONETOPARENT        477
00324 
00325 #define IDL_ENDMETHOD           478
00326 #define IDL_PREMETHOD           479
00327 
00328 // DopeFrames
00329 #define IDL_DOPEFRAME           480
00330 
00331 #define IDL_PARENTTOBONE        481
00332 
00333 // LensFlare Channels           
00334 #define IDH_LENSFLAREGLOBALCHANNEL     485
00335 #define IDH_ENDLENSFLAREGLOBALCHANNEL  486
00336 #define IDH_GLOWCHANNEL                487
00337 #define IDH_ENDGLOWCHANNEL             488
00338 #define IDH_BEAMCHANNEL                489
00339 #define IDH_ENDBEAMCHANNEL             490
00340 #define IDH_REFLECTCHANNEL             491
00341 #define IDH_ENDREFLECTCHANNEL          492
00342 #define IDL_GLOWS                      493
00343 #define IDL_BEAMS                      494
00344 #define IDL_REFLECTIONS                495
00345 
00346 // Surfaces                     498+
00347 #define IDH_DECALS              498
00348 #define IDH_ENDDECALS           499
00349 #define IDH_DECAL               500
00350 #define IDH_ENDDECAL            501
00351 #define IDL_SEETHRU             502
00352 #define IDL_PATCHESHIT          503
00353 #define IDH_DATA                504
00354 #define IDH_ENDDATA             505
00355 #define IDH_STAMP               506
00356 #define IDH_ENDSTAMP            507
00357 #define IDL_DECALTYPE           508
00358 #define IDL_SEAMLESS            509
00359 #define IDL_MAPREPEAT           510
00360 #define IDH_STAMPS              511
00361 #define IDH_ENDSTAMPS    