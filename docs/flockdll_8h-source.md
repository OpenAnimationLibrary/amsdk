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

# flockdll.h

[Go to the documentation of this file.](flockdll_8h.md)

<div class="fragment">

``` fragment
00001 // KB  6/12/2003  \Ken105\Include\flockdll.h
00002 
00003 #define __FLOCKDLL_H
00004 
00005 #ifndef __FLOCKBUF_H
00006 #include "FlockBuf.h"
00007 #endif
00008 #ifndef __FLOCKMAN_H
00009 #include "FlockMan.h"
00010 #endif
00011 #ifndef __ROTATE_H
00012 #include "Rotate.h"
00013 #endif
00014 #ifndef __HASHTIME_H
00015 #include "HashTime.h"
00016 #endif
00017 
00018 #include "DLLPlugi.h"
00019 
00020 #define FLOCKDLLVERSION 1
00021 
00022 class Flock : public DLLPlugin
00023 {
00024 public:
00025    FlockBuf          m_flockbuf;
00026    Flock            *m_nextflock;
00027    
00028    Flock(HTreeObject *htreeobject) : DLLPlugin(htreeobject) {}
00029    virtual void InitParticlePos( int id, TSQ &tsq, Time &actionoffset ) =0;
00030    virtual void UpdateParticlePos( int id, TSQ &tsq, Vector &d, float frametime )=0;
00031    
00032 };
00033 
00034 
00035 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
