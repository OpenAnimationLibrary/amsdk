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

# RObject.h

[Go to the documentation of this file.](RObject_8h.md)

<div class="fragment">

``` fragment
00001 // KB  8/28/2003  \Ken110\Include\RObject.h
00002 
00003 #define __ROBJECT_H
00004 
00005 #ifndef __ALLOCATE_H
00006 #include "Allocate.h"
00007 #endif
00008 #ifndef __HIT_H
00009 #include "Hit.h"
00010 #endif
00011 
00012 #ifndef __RTYPE_H
00013 #include "RType.h"
00014 #endif
00015 
00016 //#define CYLINDERWIDTHFACTOR   10
00017 //#define BOXWIDTHFACTOR      100
00018 
00019 class Hit;
00020 class ThreadInfo;
00021 
00022 class RObject {
00023 public:
00024 #if _MEMDEBUG
00025    void *operator new( size_t size, char *file, const int line ) { return ALLOCATT( size, file, line ); }
00026 #else
00027    void *operator new( size_t size ) { return AllocAtt( size ); }
00028 #endif   
00029    void operator delete( void *ptr ) { FreeAtt( ptr ); }   
00030 
00031    virtual void Intersect( const Vector &, const Vector &, ThreadInfo * ) {}
00032    virtual BOOL Intersect( const Vector &, const Vector &, Vector &, Vector & ) { return FALSE; }
00033    virtual void Normal( Hit &, Vector &, Vector & ) {}
00034    virtual BOOL IsPatch() { return FALSE;}
00035    virtual void Collision( ThreadInfo *, Vector &min, Vector &max ) {}
00036    virtual int  GetType() = 0;
00037 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
