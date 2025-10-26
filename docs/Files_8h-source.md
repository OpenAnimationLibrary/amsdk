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

# Files.h

[Go to the documentation of this file.](Files_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  8/18/2004  \DanLP110\Include\Files.h
00002 
00003 #ifndef __FILES_H
00004 #define __FILES_H
00005 
00006 #ifndef __EXPORTS_H
00007 #include "Exports.h"
00008 #endif
00009 
00010 class String;
00011 
00012 FILEIOEXPORT BOOL   Remove( const String &filename );
00013 FILEIOEXPORT BOOL   RemoveDir(const String &dir);
00014 FILEIOEXPORT BOOL   Rename( const String &src, const String &dst );
00015 FILEIOEXPORT BOOL   DirExists( const String &pathname );
00016 FILEIOEXPORT BOOL   FileExists( const String &filename );
00017 FILEIOEXPORT BOOL   MakeDirPath( const String &unexplodedname );
00018 FILEIOEXPORT BOOL   CanWriteDirPath( const String &name );
00019 FILEIOEXPORT BOOL   CanWriteToFile( const String &name );
00020 FILEIOEXPORT BOOL   IsReadOnly( const String &filename );
00021 FILEIOEXPORT FILETIME GetFileModifiedTime( int filenumber );
00022 FILEIOEXPORT FILETIME GetFileModifiedTime( const String &filename );
00023 FILEIOEXPORT BOOL   IsFileModified( const String &filename, FILETIME reftime );
00024 FILEIOEXPORT void   SetFileType( const String &filename, BOOL setapp, ULONG type);
00025 FILEIOEXPORT BOOL   CopyFile( String src, String dst );
00026 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
