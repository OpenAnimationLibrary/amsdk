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

# Registra.h

[Go to the documentation of this file.](Registra_8h.md)

<div class="fragment">

``` fragment
00001 // RC  4/25/2002  \HRandy95\Include\Registra.h
00002 
00003 #define __REGISTRA_H
00004 
00005 #ifndef __STRCLASS_H
00006 #include "StrClass.h"
00007 #endif
00008 
00009 class Registration {
00010 public:
00011    Registration *m_next;
00012    String        m_localizedname;
00013    String        m_classname;
00014    String        m_filename;
00015    HINSTANCE     m_hinst, m_hresource;
00016    HICON         m_hicon;
00017    UINT          m_nameid;
00018    
00019    Registration() {}
00020    
00021    Registration(HINSTANCE hinst, HINSTANCE hresource, char *classname, UINT nameid)
00022    {
00023       m_hinst = hinst;
00024       m_hresource = hresource;
00025       m_classname = (String)classname;
00026       m_hicon = 0;
00027       m_nameid = 0;
00028 
00029       if (hresource) {
00030          char buf[STRINGSIZE];
00031          LoadString( hresource, nameid, buf, STRINGSIZE );
00032          m_localizedname = buf;
00033       }
00034       else {   // YP: This happens for statics registrations 
00035          m_nameid = nameid;   // so, localize later.
00036          // CString name;     // for statics registrations, the 3 following lines does not work in VS 7
00037          // name.LoadString( nameid );
00038          // m_localizedname = (LPCTSTR)name;
00039       }
00040    }
00041 
00042    void Localize()
00043    {
00044       CString name;
00045       name.LoadString( m_nameid );
00046       m_localizedname = (LPCTSTR)name;
00047    }
00048    
00049    virtual ~Registration() {
00050       if (m_hinst != m_hresource)
00051          ::FreeLibrary( m_hresource );
00052       if (m_hinst)
00053          ::FreeLibrary( m_hinst );
00054    }
00055 #if _MEMDEBUG
00056    void *operator new( size_t size, char *file, const int line ) { return ALLOCEXT( size, file, line ); }
00057 #else
00058    void *operator new( size_t size ) { return AllocExt( size ); }
00059 #endif   
00060    void  operator delete( void *ptr ) { FreeExt( ptr ); }
00061 };
00062 /*
00063 class ChannelRegistration : public Registration {
00064 public:
00065    int          m_numchaninfos;
00066    ChannelInfo *m_chaninfos;
00067    
00068    ChannelRegistration()
00069    {
00070       m_numchaninfos = NULL;
00071       m_chaninfos = NULL;
00072    }
00073    
00074    ChannelRegistration( HINSTANCE hinst, HINSTANCE hresource, char *classname, UINT nameid, int numchaninfos, 
00075     ChannelInfo *chaninfos ) : Registration(hinst, hresource, classname, nameid) 
00076    {
00077       m_numchaninfos = numchaninfos;
00078       m_chaninfos = NULL;
00079       if (m_numchaninfos) {
00080          if (m_hinst) {
00081             m_chaninfos = new ChannelInfo[m_numchaninfos];
00082             for (int i=0; i<m_numchaninfos; i++)
00083                m_chaninfos[i] = chaninfos[i];// = operator
00084          }
00085          else
00086             m_chaninfos = chaninfos;
00087       }
00088    }
00089 
00090    virtual ~ChannelRegistration() {
00091       if (m_hinst)
00092          delete [] m_chaninfos;
00093    }
00094 };
00095 */
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
