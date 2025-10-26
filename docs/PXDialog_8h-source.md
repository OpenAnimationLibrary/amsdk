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

# PXDialog.h

[Go to the documentation of this file.](PXDialog_8h.md)

<div class="fragment">

``` fragment
00001 /************************************************************************
00002 * @doc
00003 * $Workfile: PXDialog.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 2 $ $Author: Yury $ $Date: 6/22/97 10:30p $
00013 ************************************************************************/
00014 #ifndef __CPXDIALOG_H
00015 #define __CPXDIALOG_H
00016 
00017 
00018 #ifndef _OS9
00019 #define CPXDialog CDialog
00020 
00021 #else
00022 //@class Macintosh centered dialog
00023 //@devnote  This class is Mac only; on Windows it maps to CDialog. It produces a centered Dialog,Mac style.
00024 
00025 
00026 class XMAC_CLASS CPXDialog : public CDialog
00027 {
00028 public:
00029    CPXDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
00030    CPXDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
00031 
00032    virtual BOOL OnInitDialog();
00033 
00034 protected:
00035    DECLARE_MESSAGE_MAP()
00036 };
00037 
00038 
00039 #endif//_OS9
00040 #endif//__CPXDIALOG_H
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:45 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
