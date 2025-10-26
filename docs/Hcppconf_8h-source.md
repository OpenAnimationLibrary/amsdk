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

# Hcppconf.h

[Go to the documentation of this file.](Hcppconf_8h.md)

<div class="fragment">

``` fragment
00001 /*
00002  *  HCPPCONF.H - A General Configuration header for the HASP C++ Classes.
00003  *
00004  *  Determines system configuration in order to declare the hasp routine
00005  *  properly, and to define some constants needed for memory operations.
00006  *
00007  *  Copyright (c) 1996, 1998 Aladdin Knowledge Systems Ltd.
00008  */
00009 
00010 #if !defined (HCPPCONF_H_)
00011 #define HCPPCONF_H_
00012 
00013 /*
00014  *  C++ Section.
00015  */
00016 #if !defined (__cplusplus)
00017 #error HCPPCONF.H is for use with C++ only
00018 #endif
00019 
00020 
00021 /*
00022  * Definition of HASP_EXPORT
00023  */
00024 #if defined(_WIN32) || defined (__NT__) || defined (__WIN32__)
00025 #  ifndef HASP_WIN32
00026 #    define HASP_WIN32
00027 #  endif
00028 #  if defined (BUILD_HASP_CLASSES_DLL)
00029 #     define HASP_EXPORT __declspec(dllexport)
00030 #  elif defined (HASP_CLASSES_DLL)
00031 #     if defined (__BORLANDC__)
00032 #        define HASP_EXPORT __declspec(dllimport)
00033 #     endif
00034 #  endif
00035 #endif
00036 
00037 #if !defined(HASP_EXPORT)
00038 #define HASP_EXPORT
00039 #endif
00040 
00041 
00042 /*
00043  *  Borland C++
00044  */
00045 #if defined (__BORLANDC__)
00046 #  if __BORLANDC__ >= 0x500
00047 #    define COMPILER_HAS_BOOL
00048 #    define COMPILER_HAS_EXPLICIT
00049 #    define COMPILER_HAS_TYPENAME
00050 #    define HASP_NAMESPACE_SUPPORTED
00051 #  endif
00052 #  if defined (HASP_WIN32) && (defined (__MT__) || defined (_MT))
00053 #    define HASP_MULTITHREAD
00054 #  endif
00055 
00056 #endif /* Borland C++ */
00057 
00058 
00059 /*
00060  *  Watcom C++
00061  */
00062 #if defined (__WATCOMC__)
00063 #  if __WATCOMC__ >= 1100
00064 #    define COMPILER_HAS_BOOL
00065 #    define COMPILER_HAS_EXPLICIT
00066 #    define HASP_NAMESPACE_SUPPORTED
00067 #  endif
00068 #  if defined (HASP_WIN32) && defined (__SW_BM)
00069 #    define HASP_MULTITHREAD
00070 #  endif
00071 #endif
00072 
00073 
00074 /*
00075  * GNU g++ (DJGPP, CygWin, Mingw32)
00076  */
00077 #if defined (__GNUG__)
00078 #  if (__GNUG__ >= 2)
00079 #    if (__GNUC_MINOR__ >= 7)
00080 #      define COMPILER_HAS_BOOL
00081 #      define COMPILER_HAS_EXPLICIT
00082 #      define COMPILER_HAS_TYPENAME
00083 #    endif
00084 
00085      /* EGCS 1.1 */ 
00086 #    if (__GNUC_MINOR__ >= 91)
00087 #      define HASP_NAMESPACE_SUPPORTED
00088 #    endif
00089 
00090 #  endif
00091 #endif  /* __GNUG__ */
00092 
00093 
00094 /*
00095  *  MSVC 4.x, 5.x
00096  */
00097 #if defined (_MSC_VER)
00098 #  if (_MSC_VER >= 1100)
00099 #    define COMPILER_HAS_BOOL
00100 #    define COMPILER_HAS_EXPLICIT
00101 #    define COMPILER_HAS_TYPENAME
00102 #    define HASP_NAMESPACE_SUPPORTED
00103 #  endif
00104 #  if defined(HASP_WIN32) && defined(_MT)
00105 #    define HASP_MULTITHREAD
00106 #  endif
00107 
00108   /*
00109    * The inheritance via dominance is perfectly legal, but MSVC
00110    * warns about it even at low warning levels. The following pragma
00111    * moves this warning to level 4
00112    */
00113 #  pragma warning(4: 4250)
00114 #endif /* _MSC_VER */
00115 
00116 
00117 /*
00118  *  in other compilers we emulate the new keywords 'bool', 'false', 'true'
00119  *  as  int, 0, 1  respectively
00120  */
00121 #if !defined (COMPILER_HAS_BOOL)
00122 #  if !defined(bool)
00123 #    define bool int
00124 #  endif
00125 #  if !defined(false)
00126 #    define false 0
00127 #  endif
00128 #  if !defined(true)
00129 #    define true  1
00130 #  endif
00131 #endif
00132 
00133 /*
00134  *  The library uses the keyword explicit in some places.
00135  */
00136 #if !defined (COMPILER_HAS_EXPLICIT)
00137 #  define explicit
00138 #endif
00139 
00140 /*
00141  *  HASP namespace support
00142  */
00143 #if defined(HASP_NAMESPACE_SUPPORTED) && !defined (NO_HASP_NAMESPACE)
00144 
00145 #ifndef HASP_CLASSES_NAMESPACE
00146 #define HASP_CLASSES_NAMESPACE  HASPCLAS_V2
00147 #endif
00148 
00149 namespace HASP_CLASSES_NAMESPACE {}
00150 namespace HASP = HASP_CLASSES_NAMESPACE;
00151 
00152 #  define BEGIN_HASP_NAMESPACE namespace HASP_CLASSES_NAMESPACE {
00153 #  define END_HASP_NAMESPACE }
00154 #  define USING_NAMESPACE_HASP using namespace HASP_CLASSES_NAMESPACE
00155 #  define _HASP HASP_CLASSES_NAMESPACE ::
00156 
00157 #else
00158 
00159 #  define BEGIN_HASP_NAMESPACE
00160 #  define END_HASP_NAMESPACE
00161 #  define USING_NAMESPACE_HASP
00162 #  define _HASP
00163 
00164 #endif
00165 
00166 /*
00167  *  We do not need these anymore.
00168  */
00169 #undef COMPILER_HAS_BOOL
00170 #undef COMPILER_HAS_EXPLICIT
00171 #undef COMPILER_HAS_TYPENAME
00172 
00173 
00174 #endif /* include guard */
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
