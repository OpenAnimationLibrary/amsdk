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

# PatchID.h

[Go to the documentation of this file.](PatchID_8h.md)

<div class="fragment">

``` fragment
00001 // RC  8/3/2004  \Sony115\Include\PatchID.h
00002 
00003 #ifndef __PATCHID_H
00004 #define __PATCHID_H
00005 
00006 #ifndef __STRCLASS_H
00007 #include "StrClass.h"
00008 #endif
00009 
00010 class PatchID {
00011 public:
00012    ULONG m_id1, m_id2, m_id3, m_id4;
00013 
00014    PatchID() {}
00015    PatchID(UINT id1, UINT id2, UINT id3, UINT id4)
00016    {
00017       m_id1 = id1;
00018       m_id2 = id2;
00019       m_id3 = id3;
00020       m_id4 = id4;
00021    }
00022 
00023    BOOL operator==( const PatchID &other ) const
00024    {
00025       return m_id1 == other.m_id1 &&
00026              m_id2 == other.m_id2 &&
00027              m_id3 == other.m_id3 &&
00028              m_id4 == other.m_id4;
00029    }
00030    operator String() const;
00031 };
00032 
00033 class PatchID5 : public PatchID {
00034 public:
00035    ULONG m_id5;
00036 
00037    PatchID5(){}
00038    PatchID5(UINT id1, UINT id2, UINT id3, UINT id4, UINT id5)
00039    {
00040       m_id1 = id1;
00041       m_id2 = id2;
00042       m_id3 = id3;
00043       m_id4 = id4;
00044       m_id5 = id5;
00045    }
00046 
00047    BOOL operator==( const PatchID5 &other )
00048    {
00049       return m_id1 == other.m_id1 &&
00050              m_id2 == other.m_id2 &&
00051              m_id3 == other.m_id3 &&
00052              m_id4 == other.m_id4 &&
00053              m_id5 == other.m_id5;
00054    }
00055 
00056    PatchID5 &operator=( const PatchID &other )
00057    {
00058       m_id1 = other.m_id1;
00059       m_id2 = other.m_id2;
00060       m_id3 = other.m_id3;
00061       m_id4 = other.m_id4;
00062       return *this;
00063    }
00064 };
00065 
00066 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
