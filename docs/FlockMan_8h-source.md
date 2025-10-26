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

# FlockMan.h

[Go to the documentation of this file.](FlockMan_8h.md)

<div class="fragment">

``` fragment
00001 // RC  4/24/2002  \HRandy95\Include\FlockMan.h
00002 
00003 #define __FLOCKMAN_H
00004 
00005 #ifndef __VECTOR_H
00006 #include "Vector.h"
00007 #endif
00008 
00009 class PeerBox;
00010 
00011 // particle flock object.  
00012 class Boid
00013 {
00014 public:
00015    int      id;
00016    PeerBox *peerbox;
00017    Vector   location, direction;
00018 };
00019 
00020 class BoidList
00021 {
00022 public:
00023    Boid     *boid;
00024    BoidList *next;
00025    
00026    BoidList() { boid = NULL; next = NULL; }
00027 };
00028 
00029 class PeerBox 
00030 {
00031 public:
00032    BoidList *boidlist;
00033    PeerBox  *top, *bottom, *left, *right, *front, *back;
00034    float     positionrating;
00035    Vector    center, upperleft, lowerright;
00036    
00037    PeerBox() { boidlist = NULL; }
00038    
00039    void ClearBoidList();
00040    
00041 };
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
