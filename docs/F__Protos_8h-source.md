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

# F_Protos.h

[Go to the documentation of this file.](F__Protos_8h.md)

<div class="fragment">

``` fragment
00001 // BC  5/18/2005  \BobL120\Include\F_Protos.h
00002 
00003 #define __F_PROTOS_H
00004 
00005 #ifndef __EXPORTS_H
00006 #include "Exports.h"
00007 #endif
00008 
00009 class String;
00010 
00011 FILEIOEXPORT BOOL IsShift();
00012 FILEIOEXPORT BOOL IsCtrl();
00013 FILEIOEXPORT BOOL IsAlt();
00014 FILEIOEXPORT BOOL IsCommand();
00015 FILEIOEXPORT BOOL IsOption();
00016 FILEIOEXPORT BOOL IsLeft();
00017 FILEIOEXPORT BOOL IsMiddle();
00018 FILEIOEXPORT BOOL IsRight();
00019 FILEIOEXPORT BOOL IsXLock();
00020 FILEIOEXPORT BOOL IsYLock();
00021 FILEIOEXPORT BOOL IsZLock();
00022 FILEIOEXPORT BOOL IsFourKey();
00023 FILEIOEXPORT BOOL IsFiveKey();
00024 FILEIOEXPORT BOOL IsSixKey();
00025 FILEIOEXPORT BOOL IsMenuKey();
00026 FILEIOEXPORT BOOL IsSelectRangeKey();
00027 FILEIOEXPORT BOOL IsMultiSelectKey();
00028 FILEIOEXPORT BOOL IsRemoveKey();
00029 FILEIOEXPORT BOOL IsCopyKey();
00030 
00031 FILEIOEXPORT BOOL EscapeKeyDown();
00032 
00033 FILEIOEXPORT void  SetBasePath( const String & );
00034 FILEIOEXPORT const String &GetBasePath();
00035 FILEIOEXPORT void  FreeBasePaths ();
00036 
00037 
00038 FILEIOEXPORT void WatchMouse( BOOL );
00039 FILEIOEXPORT BOOL IsWatchMouse();
00040 FILEIOEXPORT BOOL MessageReceived(BOOL includemouseup = FALSE);
00041 
00042 FILEIOEXPORT String GetResourceString( UINT id );
00043 
00044 FILEIOEXPORT void DoEvents(CWnd* pWnd = NULL);
00045 FILEIOEXPORT void DoOneEvent(CWnd* pWnd = NULL);
00046 
00047 FILEIOEXPORT float GetClockTicks();  // in seconds
00048 
00049 void PrintMemory(const String &title);
00050 FILEIOEXPORT void PrintMemoryMessage(const String &title);
00051 
00052 FILEIOEXPORT void SetSwapping(BOOL pswapping);
00053 FILEIOEXPORT BOOL IsSwapping();
00054 
00055 FILEIOEXPORT void RemoveCachedMessages();
00056 
00057 FILEIOEXPORT BOOL InitSmartHeapPools();
00058 FILEIOEXPORT void FreeSmartHeapPools();
00059 
00060 FILEIOEXPORT int    GetRegistryValue( const String &section, const String &entry, int defaultvalue );
00061 FILEIOEXPORT float  GetRegistryValue( const String &section, const String &entry, float defaultvalue );
00062 FILEIOEXPORT double GetRegistryValue( const String &section, const String &entry, double defaultvalue );
00063 FILEIOEXPORT String GetRegistryString( const String &section, const String &entry, const String &defaultstring );
00064 FILEIOEXPORT BOOL   SetRegistryValue( const String &section, const String &entry, int tvalue );
00065 FILEIOEXPORT BOOL   SetRegistryValue( const String &section, const String &entry, float value );
00066 FILEIOEXPORT BOOL   SetRegistryValue( const String &section, const String &entry, double value );
00067 FILEIOEXPORT BOOL   SetRegistryString( const String &section, const String &entry, const String &string );
00068 FILEIOEXPORT BOOL   DeleteRegistryItem( const String &section, const String &entry );
00069 FILEIOEXPORT void   ResetRegistry(const String &regname);
00070 FILEIOEXPORT void   ResetRegistry(const String &key, const String &regname);
00071 FILEIOEXPORT BOOL   GetRegistryBOOL( const String &section, const String &entry, BOOL defaultvalue );
00072 FILEIOEXPORT BOOL   SetRegistryBOOL( const String &section, const String &entry, BOOL value );
00073 
00074 FILEIOEXPORT int    GetRegistryValue( BOOL ischar, const char *section, const char *entry, int defaultvalue );
00075 FILEIOEXPORT float  GetRegistryValue( BOOL ischar, const char *section, const char *entry, float defaultvalue );
00076 FILEIOEXPORT char  *GetRegistryString( BOOL ischar, const char *section, const char *entry, const char *defaultstring );
00077 FILEIOEXPORT BOOL   SetRegistryValue( BOOL ischar, const char *section, const char *entry, int tvalue );
00078 FILEIOEXPORT BOOL   SetRegistryValue( BOOL ischar, const char *section, const char *entry, float value );
00079 FILEIOEXPORT BOOL   SetRegistryString( BOOL ischar, const char *section, const char *entry, const char *string );
00080 FILEIOEXPORT BOOL WriteProfileBinarySplit(BOOL ischar, const char *section, const char *entry, LPBYTE pData, UINT nBytes);
00081 FILEIOEXPORT BOOL GetProfileBinarySplit(BOOL ischar, const char *section, const char *entry, LPBYTE* ppData, UINT* pBytes);
00082 
00083 FILEIOEXPORT int    GetLocalRegistryValue( const String &section, const String &entry, int defaultvalue );
00084 FILEIOEXPORT float  GetLocalRegistryValue( const String &section, const String &entry, float defaultvalue );
00085 FILEIOEXPORT String GetLocalRegistryString(const String &section, const String &entry, const String &defaultstring);
00086 FILEIOEXPORT BOOL   SetLocalRegistryValue( const String &section, const String &entry, int tvalue );
00087 FILEIOEXPORT BOOL   SetLocalRegistryValue( const String &section, const String &entry, float value );
00088 FILEIOEXPORT BOOL   SetLocalRegistryString(const String &section, const String &entry, const String &string );
00089 FILEIOEXPORT void   SetLocalRegistryProfile(const String &profile);
00090 FILEIOEXPORT String GetLocalRegistryProfile();
00091 FILEIOEXPORT void   FreeLocalRegistryProfile();
00092 
00093 FILEIOEXPORT BOOL WriteProfileBinarySplit(const String &section, const String &entry, LPBYTE pData, UINT nBytes);
00094 FILEIOEXPORT BOOL GetProfileBinarySplit(const String &section, const String &entry, LPBYTE* ppData, UINT* pBytes);
00095 
00096 FILEIOEXPORT String InitMacProfile( char *name );
00097 FILEIOEXPORT void   FreeMacProfile();
00098 FILEIOEXPORT void   SaveMacProfile();
00099 
00100 FILEIOEXPORT ULONG GetLastSubdivision();
00101 
00102 class CHashFileDialog;
00103 
00104 FILEIOEXPORT BOOL SaveRequest( UINT titleid, UINT filterid, String &filename, char *extension, const char *inilookup, UINT actionid = 3, CWnd *parent = NULL );
00105 FILEIOEXPORT BOOL SaveRequest( UINT titleid, const String &filters, String &filename, char *extension, const char *inilookup, UINT actionid = 3, CWnd *parent = NULL, int *pindex=NULL );
00106 FILEIOEXPORT BOOL SaveRequest( const String &title, const String &filters, String &filename, char *extension, const char *inilookup, UINT actionid = 3, CWnd *parent = NULL, int *pindex=NULL );
00107 FILEIOEXPORT String GetDescriptionGivenIndex(const String &filters, int index);
00108 
00109 class StringList;
00110 
00111 FILEIOEXPORT void DeleteStringList(StringList *);
00112 
00113 FILEIOEXPORT BOOL OpenRequest( UINT titleid,        UINT filterid,        String &filename, char *extension, char *inilookup, int *index=NULL, CWnd *parent=NULL, StringList **multiselect=NULL, CHashFileDialog *pdlg=NULL );
00114 FILEIOEXPORT BOOL OpenRequest( const String &title, const String &filter, String &filename, char *extension, char *inilookup, int *index=NULL, CWnd *parent=NULL, StringList **multiselect=NULL, CHashFileDialog *pdlg=NULL );
00115 FILEIOEXPORT BOOL OpenRequest( const String &title, const String &filter, String &filename, char *extension, char *inilookup, int *index, CWnd *parent, StringList **multiselect, CHashFileDialog *pdlg, BOOL *pbCancelall );
00116 
00117 FILEIOEXPORT BOOL StringRequest( UINT messageid, String &string, CWnd *parent = NULL, UINT titleid = 0 );
00118 FILEIOEXPORT BOOL StringRequest( CString &message, String &string, CWnd *parent = NULL, UINT titleid = 0 );
00119 FILEIOEXPORT BOOL StringRequest( const CString &message, String &string, CWnd *parent = NULL, UINT titleid = 0 );
00120 FILEIOEXPORT BOOL DirRequest(String &dir, LPCTSTR lpcszCaption = NULL, LPCTSTR lpcszInitialDir = NULL, CWnd *pWndParent = NULL);
00121 
00122 FILEIOEXPORT BOOL LaunchAssociatedApp( const String &filename );
00123 FILEIOEXPORT void LaunchEMail(HWND hwnd, const String &address);
00124 FILEIOEXPORT void LaunchURL(HWND hwnd, const String &url);
00125 
00126 FILEIOEXPORT void LogPoolMemory();
00127 
00128 FILEIOEXPORT BOOL QueryRegistration();
00129 
00130 class Time;
00131 FILEIOEXPORT void AFXAPI DDX_Time(CDataExchange *pDX, int nIDC, Time &time, int fps, int timeunits, BOOL treatasdelta = FALSE);
00132 FILEIOEXPORT void AFXAPI DDV_MinMaxTime(CDataExchange *pDX, Time time, Time minval, Time maxvalue, int fps, int timeunits );
00133 
00134 FILEIOEXPORT void AFXAPI DDV_NotEmpty(CDataExchange *pDX, const String &string );
00135 
00136 String AddMacFieldToFilters( const String &filters );
00137 
00138 //Internet
00139 FILEIOEXPORT BOOL IsConnectedToInternet();
00140 FILEIOEXPORT BOOL IsUseDialUp();
00141 FILEIOEXPORT DWORD ConnectToInternetUsingDialUp(DWORD &connection);
00142 FILEIOEXPORT BOOL HangUpDialUp(DWORD connection);
00143 #ifdef _OS9
00144 FILEIOEXPORT String LookupInternetName(char *hostname);
00145 FILEIOEXPORT LONG InitOpenTransport();
00146 FILEIOEXPORT void CloseOpenTransport();
00147 FILEIOEXPORT void OpenMacStubLib();
00148 FILEIOEXPORT void CloseMacStubLib();
00149 FILEIOEXPORT BOOL LaunchMacURL( char *url );
00150 #endif
00151 
00152 FILEIOEXPORT CFont *GetGUIFont();
00153 
00154 // Resource
00155 FILEIOEXPORT BOOL GetProductVersion(const String &filename, int &vermajor, int &verminor, int &revmajor, int &revminor);
00156 FILEIOEXPORT String GetProductVersion(const String &filename);
00157 
00158 //*********
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
