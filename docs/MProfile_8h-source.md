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

# MProfile.h

[Go to the documentation of this file.](MProfile_8h.md)

<div class="fragment">

``` fragment
00001 /************************************************************************
00002 * @doc
00003 * $Workfile: MProfile.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 2 $ $Author: Jdk $ $Date: 2/25/97 1:07a $
00013 ************************************************************************/
00014 #ifndef __MPROFILE_H
00015 #define __MPROFILE_H
00016 
00017 
00018 //@class .Ini file handler functions.
00019 //@base     public | CObject
00020 //@devnote  This is a portable class, usable on any platform
00021 class XMAC_CLASS CMProfile : public CObject
00022 {
00023 public:
00024    // our constructor has some options.  The ini file's name can be specified,
00025    // or if it's null or a pointer to null, the app's base name will be used 
00026    // (AfxGetAppName()).  By setting flushOnWrite to TRUE, all
00027    // WriteProfileXXX calls will force the ini file to be re-written to disk 
00028    // immediatly.  If FALSE, the memory image will be flushed only on request
00029    // (ProfileFlush()),  or in the destructor (if the memory image is "dirty")
00030    CMProfile (char * iniFileName = NULL, BOOL flushOnWrite = FALSE, BOOL macwriteDOS = FALSE);
00031    ~CMProfile ();
00032 
00033    DWORD GetProfileString  (LPCTSTR psec, LPCTSTR pkey, LPCTSTR pdef, LPTSTR buf, DWORD bufsize);
00034    UINT  GetProfileInt     (LPCTSTR psec, LPCTSTR pkey, UINT nDefault);
00035    BOOL  WriteProfileString   (LPCTSTR psec, LPCTSTR pkey, LPCTSTR buf);
00036    BOOL  WriteProfileInt      (LPCTSTR psec, LPCTSTR pkey, UINT val);
00037    BOOL  ProfileFlush      (void);           
00038    char  * GetIniPath         (const char * fname);   // build's a path to the ini file (mac preferences folder or window's system directory)
00039 
00040 protected:
00041    void  ProfileRead       (void);           // read the ini file into memory
00042    BOOL  ProfileWrite      (void);           // flush the ini file to disk
00043    void  SetFileAttrib     (char * fname);      // for Mac, set the file attributes to text
00044    void  trim           (CString & cs);      // trim leading and trailing spaces from a string
00045    void  qTrim          (CString & cs);      // trim matching leading and trailing single and double quotes
00046    void  quote          (CString & cs);      // quote strings with leading and trailing white space
00047 
00048    BOOL                 m_Dirty;       // have we modified the memory profile?
00049    BOOL                 m_flushOnWrite;      // if TRUE, flush data to disk on every WriteProfileXXX call
00050    BOOL                 m_macwriteDOS;    // write DOS like files on MAC
00051    CMapStringToPtr            * m_profList;     // the memory image of the profile data
00052    CString                 m_iniFileName;    // the profile file's root filename (no extension)
00053 };
00054 
00055 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
