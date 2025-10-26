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

# InternetConfig.h

[Go to the documentation of this file.](InternetConfig_8h.md)

<div class="fragment">

``` fragment
00001 /*
00002      File:       InternetConfig.h
00003  
00004      Contains:   Internet Config interfaces
00005  
00006      Version:    Technology: based on IC 2.5 alpha
00007                  Release:    Universal Interfaces 3.4
00008  
00009      Copyright:  © 1999-2001 by Apple Computer, Inc., all rights reserved.
00010  
00011      Bugs?:      For bug reports, consult the following page on
00012                  the World Wide Web:
00013  
00014                      http://developer.apple.com/bugreporter/
00015  
00016 */
00017 /*
00018     IMPORTANT NOTES ABOUT THE C HEADERS
00019     -----------------------------------
00020 
00021     o   When you see the parameter 'y *x', you should be aware that
00022         you *cannot pass in nil*.  In future this restriction may be eased,
00023         especially for the attr parameter to ICGetPref.  Parameters where nil
00024         is legal are declared using the explicit pointer type, ie 'yPtr x'.
00025 
00026     o   Strings are *Pascal* strings.  This means that they must be word aligned.
00027         MPW and Think C do this automatically.  The last time I checked, Metrowerks
00028         C does not.  If it still doesn't, then IMHO it's a bug in their compiler
00029         and you should report it to them.  [IC 1.4 and later no longer require
00030         word aligned strings.  You can ignore this warning if you require IC 1.4
00031         or greater.]
00032 */
00033 /***********************************************************************************************/
00034 
00035 #ifndef __INTERNETCONFIG__
00036 #define __INTERNETCONFIG__
00037 
00038 #ifndef __ALIASES__
00039 #include <Aliases.h>
00040 #endif
00041 
00042 #ifndef __COMPONENTS__
00043 #include <Components.h>
00044 #endif
00045 
00046 #ifndef __AEDATAMODEL__
00047 #include <AEDataModel.h>
00048 #endif
00049 
00050 
00051 
00052 
00053 #if PRAGMA_ONCE
00054 #pragma once
00055 #endif
00056 
00057 #ifdef __cplusplus
00058 extern "C" {
00059 #endif
00060 
00061 #if PRAGMA_IMPORT
00062 #pragma import on
00063 #endif
00064 
00065 #if PRAGMA_STRUCT_ALIGN
00066     #pragma options align=mac68k
00067 #elif PRAGMA_STRUCT_PACKPUSH
00068     #pragma pack(push, 2)
00069 #elif PRAGMA_STRUCT_PACK
00070     #pragma pack(2)
00071 #endif
00072 
00073 /************************************************************************************************
00074   IC error codes
00075  ************************************************************************************************/
00076 
00077 enum {
00078   icPrefNotFoundErr             = -666, /* preference not found (duh!)  */
00079   icPermErr                     = -667, /* cannot set preference  */
00080   icPrefDataErr                 = -668, /* problem with preference data  */
00081   icInternalErr                 = -669, /* hmm, this is not good  */
00082   icTruncatedErr                = -670, /* more data was present than was returned  */
00083   icNoMoreWritersErr            = -671, /* you cannot begin a write session because someone else is already doing it  */
00084   icNothingToOverrideErr        = -672, /* no component for the override component to capture  */
00085   icNoURLErr                    = -673, /* no URL found  */
00086   icConfigNotFoundErr           = -674, /* no configuration was found  */
00087   icConfigInappropriateErr      = -675, /* incorrect manufacturer code  */
00088   icProfileNotFoundErr          = -676, /* profile not found  */
00089   icTooManyProfilesErr          = -677  /* too many profiles in database  */
00090 };
00091 
00092 /************************************************************************************************
00093   IC versions (not necessarily, but historically, from a component)
00094  ************************************************************************************************/
00095 
00096 enum {
00097   kICComponentInterfaceVersion0 = 0x00000000, /* IC >= 1.0  */
00098   kICComponentInterfaceVersion1 = 0x00010000, /* IC >= 1.1  */
00099   kICComponentInterfaceVersion2 = 0x00020000, /* IC >= 1.2  */
00100   kICComponentInterfaceVersion3 = 0x00030000, /* IC >= 2.0  */
00101   kICComponentInterfaceVersion4 = 0x00040000, /* IC >= 2.5  */
00102   kICComponentInterfaceVersion  = kICComponentInterfaceVersion4 /* current version number is 4  */
00103 };
00104 
00105 /************************************************************************************************
00106   opaque type for preference reference
00107  ************************************************************************************************/
00108 
00109 typedef struct OpaqueICInstance*        ICInstance;
00110 
00111 /************************************************************************************************
00112   a record that specifies a folder, an array of such records, and a pointer to such an array
00113  ************************************************************************************************/
00114 struct ICDirSpec {
00115   short               vRefNum;
00116   long                dirID;
00117 };
00118 typedef struct ICDirSpec                ICDirSpec;
00119 typedef ICDirSpec                       ICDirSpecArray[4];
00120 typedef ICDirSpecArray *                ICDirSpecArrayPtr;
00121 
00122 /************************************************************************************************
00123   preference attributes type, bit number constants, and mask constants
00124  ************************************************************************************************/
00125 typedef UInt32                          ICAttr;
00126 
00127 enum {
00128   kICAttrLockedBit              = 0,
00129   kICAttrVolatileBit            = 1
00130 };
00131 
00132 enum {
00133   kICAttrNoChange               = (unsigned long)0xFFFFFFFF, /* pass this to ICSetPref to tell it not to change the attributes  */
00134   kICAttrLockedMask             = 0x00000001,
00135   kICAttrVolatileMask           = 0x00000002
00136 };
00137 
00138 /************************************************************************************************
00139   permissions for use with ICBegin
00140  ************************************************************************************************/
00141 
00142 typedef UInt8                           ICPerm;
00143 
00144 enum {
00145   icNoPerm                      = 0,
00146   icReadOnlyPerm                = 1,
00147   icReadWritePerm               = 2
00148 };
00149 
00150 /************************************************************************************************
00151   a reference to an instance's current configuration
00152  ************************************************************************************************/
00153 
00154 #if CALL_NOT_IN_CARBON
00155 struct ICConfigRef {
00156   OSType              manufacturer;
00157                                               /* other private data follows  */
00158 };
00159 typedef struct ICConfigRef              ICConfigRef;
00160 typedef ICConfigRef *                   ICConfigRefPtr;
00161 typedef ICConfigRefPtr *                ICConfigRefHandle;
00162 
00163 #endif  /* CALL_NOT_IN_CARBON */
00164 
00165 /************************************************************************************************
00166   profile IDs
00167  ************************************************************************************************/
00168 typedef long                            ICProfileID;
00169 typedef ICProfileID *                   ICProfileIDPtr;
00170 
00171 enum {
00172   kICNilProfileID               = 0
00173 };
00174 
00175 /************************************************************************************************
00176   other constants
00177  ************************************************************************************************/
00178 
00179 enum {
00180   kICNoUserInteractionBit       = 0
00181 };
00182 
00183 enum {
00184   kICNoUserInteractionMask      = 0x00000001
00185 };
00186 
00187 enum {
00188   kICFileType                   = FOUR_CHAR_CODE('ICAp'),
00189   kICCreator                    = FOUR_CHAR_CODE('ICAp')
00190 };
00191 
00192 /************************************************************************************************
00193   Apple event constants
00194  ************************************************************************************************/
00195 
00196 enum {
00197   kInternetEventClass           = FOUR_CHAR_CODE('GURL'),
00198   kAEGetURL                     = FOUR_CHAR_CODE('GURL'),
00199   kAEFetchURL                   = FOUR_CHAR_CODE('FURL'),
00200   keyAEAttaching                = FOUR_CHAR_CODE('Atch')
00201 };
00202 
00203 /* AERegistry.i defines a compatible keyAEDestination */
00204 
00205 enum {
00206   kICEditPreferenceEventClass   = FOUR_CHAR_CODE('ICAp'),
00207   kICEditPreferenceEvent        = FOUR_CHAR_CODE('ICAp'),
00208   keyICEditPreferenceDestination = FOUR_CHAR_CODE('dest')
00209 };
00210 
00211 /************************************************************************************************
00212   constants for use with ICGetVersion
00213  ************************************************************************************************/
00214 
00215 enum {
00216   kICComponentVersion           = 0,    /* Return a component version, comparable to kICComponentInterfaceVersion  */
00217   kICNumVersion                 = 1     /* Return a NumVersion structure  */
00218 };
00219 
00220 /************************************************************************************************
00221   types and constants for use with kICDocumentFont, et. al.
00222  ************************************************************************************************/
00223 struct ICFontRecord {
00224   short               size;
00225   Style               face;
00226   char                pad;
00227   Str255              font;
00228 };
00229 typedef struct ICFontRecord             ICFontRecord;
00230 typedef ICFontRecord *                  ICFontRecordPtr;
00231 typedef ICFontRecordPtr *               ICFontRecordHandle;
00232 
00233 /************************************************************************************************
00234   types and constants for use with kICCharacterSet, et. al.
00235  ************************************************************************************************/
00236 struct ICCharTable {
00237   unsigned char       netToMac[256];
00238   unsigned char       macToNet[256];
00239 };
00240 typedef struct ICCharTable              ICCharTable;
00241 typedef ICCharTable *                   ICCharTablePtr;
00242 typedef ICCharTablePtr *                ICCharTableHandle;
00243 
00244 /************************************************************************************************
00245   types and constants for use with kICHelper, et. al.
00246  ************************************************************************************************/
00247 struct ICAppSpec {
00248   OSType              fCreator;
00249   Str63               name;
00250 };
00251 typedef struct ICAppSpec                ICAppSpec;
00252 typedef ICAppSpec *                     ICAppSpecPtr;
00253 typedef ICAppSpecPtr *                  ICAppSpecHandle;
00254 struct ICAppSpecList {
00255   short               numberOfItems;
00256   ICAppSpec           appSpecs[1];
00257 };
00258 typedef struct ICAppSpecList            ICAppSpecList;
00259 typedef ICAppSpecList *                 ICAppSpecListPtr;
00260 typedef ICAppSpecListPtr *              ICAppSpecListHandle;
00261 
00262 /************************************************************************************************
00263   types and constants for use with kICDownloadFolder, et. al.
00264  ************************************************************************************************/
00265 
00266 #if !OLDROUTINENAMES
00267 struct ICFileSpec {
00268   Str31               volName;
00269   long                volCreationDate;
00270   FSSpec              fss;
00271   AliasRecord         alias;
00272                                               /* plus extra data, aliasSize 0 means no alias manager present when*/
00273                                               /* ICFileSpecification was created*/
00274 };
00275 typedef struct ICFileSpec               ICFileSpec;
00276 typedef ICFileSpec *                    ICFileSpecPtr;
00277 typedef ICFileSpecPtr *                 ICFileSpecHandle;
00278 #else
00279 struct ICFileSpec {
00280   Str31               vol_name;
00281   long                vol_creation_date;
00282   FSSpec              fss;
00283   AliasRecord         alias;
00284 };
00285 typedef struct ICFileSpec               ICFileSpec;
00286 typedef ICFileSpec *                    ICFileSpecPtr;
00287 typedef ICFileSpecPtr *                 ICFileSpecHandle;
00288 #endif  /* !OLDROUTINENAMES */
00289 
00290 enum {
00291   kICFileSpecHeaderSize         = sizeof(ICFileSpec) - sizeof(AliasRecord)
00292 };
00293 
00294 /************************************************************************************************
00295   types and constants for use with ICMapFilename, et. al.
00296  ************************************************************************************************/
00297 typedef long                            ICMapEntryFlags;
00298 typedef short                           ICFixedLength;
00299 
00300 #if !OLDROUTINENAMES
00301 struct ICMapEntry {
00302   short               totalLength;
00303   ICFixedLength       fixedLength;
00304   short               version;
00305   OSType              fileType;
00306   OSType              fileCreator;
00307   OSType              postCreator;
00308   ICMapEntryFlags     flags;
00309                                               /* variable part starts here*/
00310   Str255              extension;
00311   Str255              creatorAppName;
00312   Str255              postAppName;
00313   Str255              MIMEType;
00314   Str255              entryName;
00315 };
00316 typedef struct ICMapEntry               ICMapEntry;
00317 typedef ICMapEntry *                    ICMapEntryPtr;
00318 typedef ICMapEntryPtr *         