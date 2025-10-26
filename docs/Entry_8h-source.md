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

<a href="dir_C_3A_2F.md" class="el">C:</a> » <a href="dir_C_3A_2FProgram_20Files_2F.md" class="el">Program Files</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2F.md" class="el">Hash Inc</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2F.md" class="el">AM120SDK</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2F.md" class="el">Include</a> » <a href="dir_C_3A_2FProgram_20Files_2FHash_20Inc_2FAM120SDK_2FInclude_2FSDK_2F.md" class="el">SDK</a>

</div>

# Entry.h

[Go to the documentation of this file.](Entry_8h.md)

<div class="fragment">

``` fragment
00001 // BC  11/12/2004  \BobL115\Include\SDK\Entry.h
00002 
00003 #define __ENTRY_H
00004 
00005 #ifndef __AM_SDK
00006 #define __AM_SDK
00007 #endif
00008 
00009 #ifdef __INTEL_COMPILER
00010 #pragma warning(disable: 1572)  // floating-point equality and inequality comparisons are unreliable
00011 #endif
00012 
00013 enum MenuCategory {
00014    MC_GENERAL,
00015    MC_EXPORT,
00016    MC_IMPORT,
00017    MC_WIZARD,
00018    MC_PLUGINOBJECT
00019 };
00020 
00021 /* Command Entry Point Functions
00022 extern "C" __declspec(dllexport) BOOL HxtLoadCommandEntry(UINT index, ObjectType &);
00023 extern "C" __declspec(dllexport) BOOL HxtOnAddCommandMenu(HTreeObject *htreeobject, UINT index, String &menuname, MenuCategory &mc, BOOL &disabled);
00024 extern "C" __declspec(dllexport) BOOL HxtOnCommand(HTreeObject *htreeobject, UINT index);
00025 */
00026 
00027 /* Property Entry Point Functions
00028 extern "C" __declspec(dllexport) BOOL HxtLoadPropertyEntry(UINT index, ObjectType &);
00029 extern "C" __declspec(dllexport) HProperty *HxtOnAddProperties(HTreeObject *htreeobject, HCategoryProperty *pluginproperty, UINT index );
00030 */
00031 
00032 
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
