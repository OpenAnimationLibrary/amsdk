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

# Localize.h

[Go to the documentation of this file.](Localize_8h.md)

<div class="fragment">

``` fragment
00001 // KB  12/16/2004  \Include\Localize.h
00002 
00003 inline BOOL SetAppLocalizationDLL(HINSTANCE hinstance)
00004 {
00005    HINSTANCE hlangdll;
00006    char exename[512];
00007    CString dllname;
00008 
00009    GetModuleFileName( hinstance, exename, 512 );
00010 
00011    char *ptr;
00012    if (ptr = strrchr( exename, '.' ))
00013       *ptr = '\0';
00014 
00015    dllname = exename;
00016    dllname += ".lng";
00017 
00018    if (hlangdll = LoadLibrary(dllname)) {
00019       AfxSetResourceHandle(hlangdll);      
00020       return TRUE;
00021    }
00022 
00023    return FALSE;
00024 }
00025 
00026 
00027 // Niels 10/5/2003: remove the AFX_EXTENSION_MODULE reference so Hxt plugins can be compiled without 
00028 // reference to MFC
00029 
00030 //inline BOOL SetExtensionLocalizationDLL(AFX_EXTENSION_MODULE &dll)
00031 
00032 inline BOOL SetExtensionLocalizationDLL(HMODULE hModule, HMODULE& hResource)
00033 {
00034    HINSTANCE hlangdll;
00035    char exename[512];
00036    CString dllname;
00037 
00038    GetModuleFileName( hModule, exename, 512 );
00039 
00040    char *ptr = strrchr( exename, '.' );
00041    if (ptr)
00042       *ptr = '\0';
00043 
00044    dllname = exename;
00045    dllname += ".lng";
00046 
00047    hlangdll = LoadLibrary(dllname);
00048    
00049    if (hlangdll) {
00050       hResource = hlangdll;
00051      return TRUE;
00052    }
00053 
00054    return FALSE;
00055 }
00056 
00057 void InitStaticsLocalization();
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
