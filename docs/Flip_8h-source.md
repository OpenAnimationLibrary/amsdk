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

# Flip.h

[Go to the documentation of this file.](Flip_8h.md)

<div class="fragment">

``` fragment
00001 // RC  4/24/2002  \HRandy95\Include\Flip.h
00002 
00003 #define __FLIP_H
00004 
00005 #ifndef __DATATYPE_H
00006 #include "DataType.h"
00007 #endif
00008 
00009 inline void FlipShort( SHORT *short_ptr ) /* Flip bytes in short from 68000 to 8088 */
00010 {
00011 #ifndef _MAC
00012    short tmp;
00013 
00014    tmp = (((*short_ptr << 8) & 0xFF00) | ((*short_ptr>>8) & 0xFF));
00015    *short_ptr = tmp;
00016 #endif
00017 }
00018  
00019 inline void FlipLong( LONG *long_ptr ) /* Flip bytes in long from 68000 to 8088 */
00020 {
00021 #ifndef _MAC
00022    LONG tmp;
00023   
00024    tmp = (((*long_ptr&0xFFL) << 24) | ((*long_ptr & 0xFF00L) << 8) |
00025     ((*long_ptr & 0xFF0000L) >> 8) | ((*long_ptr        >> 24) & 0xFFL));
00026    *long_ptr=tmp;
00027 #endif
00028 }
00029 
00030 inline void FlipShort68k( short *short_ptr )
00031 {
00032 #ifdef _MAC
00033    short tmp;
00034 
00035    tmp = (((*short_ptr << 8) & 0xFF00) | ((*short_ptr>>8) & 0xFF));
00036    *short_ptr = tmp;
00037 #endif
00038 }
00039 
00040 inline void FlipLong68k( long *long_ptr )
00041 {
00042 #ifdef _MAC
00043    LONG tmp;
00044     
00045    tmp = (((*long_ptr&0xFFL) << 24) | ((*long_ptr & 0xFF00L) << 8) |
00046     ((*long_ptr & 0xFF0000L) >> 8) | ((*long_ptr        >> 24) & 0xFFL));
00047    *long_ptr=tmp;
00048 #endif
00049 }
00050 
00051 inline void ReverseBytes(void *v, int size)
00052 {
00053 #ifdef _MAC
00054    UBYTE buffer[8];
00055    UBYTE *s = (UBYTE *) v;
00056    
00057    int i;
00058    for ( i = 0; i < size; i++)
00059       buffer[i] = s[size-i-1];
00060       
00061    for (i=0; i<size; i++)
00062       s[i] = buffer[i];
00063 #endif
00064 }
00065 
00066 inline void FlipDouble68k( double *double_ptr )
00067 {
00068 #ifdef _MAC
00069    ReverseBytes(double_ptr, 8);   
00070 #endif
00071 }
00072 
00073 inline void FlipLongBits( ULONG *ptr )
00074 {                  
00075 #ifdef _MAC
00076    ULONG newptr = 0;
00077    for (int i = 0; i < 32; i++)
00078       if (*ptr & (1 << i))
00079          newptr |= (1 << (31-i));
00080    *ptr = newptr;
00081 #endif
00082 }
00083    
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
