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

# DLLPlugi.h

[Go to the documentation of this file.](DLLPlugi_8h.md)

<div class="fragment">

``` fragment
00001 // BC  12/2/2004  \BobL120\Include\DLLPlugi.h
00002 
00003 #ifndef __DLLPLUGI_H
00004 #define __DLLPLUGI_H
00005 
00006 #ifndef __HASHTIME_H
00007 #include "HashTime.h"
00008 #endif
00009 
00010 #ifndef __HHASHOBJ_H
00011 #include "sdk/HHashObj.h"
00012 #endif
00013 
00014 #ifndef __PTRMESSA_H
00015 #include "PtrMessa.h"
00016 #endif
00017 
00018 class HProperty;
00019 class HTreeObject;
00020 
00021 class DLLPlugin {
00022 public:
00023    HINSTANCE                 m_hresource;
00024    HTreeObject              *m_treeobject; //for ReassignPtr and so plugin knows owner
00025                                            //passed to CreatePLUGINTYPE
00026                                            //so CreatePLUGINTYPE knows plugins owner
00027                                            //currently CreatePLUGINTYPE must pass this through constructor to set this
00028                                            //grep for GetProcAddress and set this after creation to take burden off plugin writer
00029                                            //also expose GetOwner() that returns this
00030 // CONSTRUCTION/DESTRUCTION
00031                              DLLPlugin() { Init(); }
00032                              DLLPlugin( HTreeObject *treeobject) { Init(); m_treeobject = treeobject; }
00033    virtual                  ~DLLPlugin() {}
00034 
00035    void Init();
00036    
00037    virtual void              Init( Time time ) {}
00038    virtual void              Copy( const DLLPlugin &other ) {}
00039    HTreeObject              *GetOwner() { return m_treeobject; }
00040 
00041 // INTERFACE
00042    virtual UINT              GetIconID() { return 0; }
00043 
00044    virtual UINT              GetNameID() { return 0; }
00045    virtual char             *GetClassName() { return NULL; }
00046 
00047    virtual HProperty        *GetPropertyAt( int i ) { return NULL; }
00048    virtual int               GetNumProperties() 
00049    {
00050       int c;
00051       for(c=0; GetPropertyAt(c); c++);
00052       return c;
00053    }
00054 
00055 // SERIALIZATION
00056    virtual BOOL              Save( char *&label, char *&value, int count ) { return FALSE; }
00057    virtual BOOL              ParseArg( const char *label, const char *value ) { return FALSE; }
00058    virtual BOOL              OnNotifyEndProjectLoad( float productversion ) { return TRUE; }
00059 
00060 // POINTER MESSAGES
00061    virtual HTreeObject     **GetPtrAt( int index ) { return NULL; }
00062    void                      ReassignPtr( void *ptruplink, HTreeObject *newvalue ) {if (m_treeobject) m_treeobject->ReassignPtr(ptruplink, newvalue);}
00063    virtual BOOL              OnPtrMessage( PtrMessage ptrmessage, HTreeObject **ptruplink, LONG lparam, Time time=0 ) { return FALSE; }
00064 };
00065 
00066 inline void DLLPlugin::Init()
00067 {
00068    HINSTANCE hlangdll;
00069    char exename[512];
00070 
00071    GetModuleFileName( AfxGetInstanceHandle(), exename, 512 );
00072    
00073 #ifdef _OS9    
00074    char macname[512];
00075    GetFileTitle(exename, macname, 512);
00076    strcpy(exename, macname);
00077 #endif   
00078 
00079    char *ptr;
00080    if (ptr = strrchr( exename, '.' ))
00081       *ptr = '\0';
00082 
00083    strcat(exename, ".lng");
00084 
00085    if (hlangdll = LoadLibrary(exename)) {
00086       AfxSetResourceHandle(hlangdll);      
00087       m_hresource = hlangdll;
00088    }
00089    else
00090       m_hresource = AfxGetInstanceHandle();
00091 }
00092 
00093 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
