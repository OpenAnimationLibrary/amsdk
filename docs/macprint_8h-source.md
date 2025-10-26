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

# macprint.h

[Go to the documentation of this file.](macprint_8h.md)

<div class="fragment">

``` fragment
00001 /************************************************************************
00002 * @doc
00003 * $Workfile: MacSound.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 2 $ $Author: Yury $ $Date: 4/28/97 4:37p $
00013 ************************************************************************/
00014 #ifndef _OS9PRINT_H
00015 #define _OS9PRINT_H
00016 
00017 #ifdef _OS9
00018 int XMAC_API SetMacPrintRez (THPrint thPrint);
00019 
00020 #define GD_CART_DONTCARE   0
00021 #define GD_CART_BLACK      1
00022 #define GD_CART_PHOTO      2
00023 
00024 #define ORIENT_DONTCARE    -1
00025 #define ORIENT_PORTRAIT    0
00026 #define ORIENT_LANDSCAPE   1
00027 
00028 // This is Global data used by the Macintosh Page Setup's callback function.
00029 typedef struct {
00030    int      Orient;           // the program's last requested orientation
00031    Rect  dRect;            // the original dialog's size
00032    WORD  wDev;          // the device whose dialog we mangled
00033    TPPrDlg  prDlg;            // the dialog 
00034 } GMacPrintData;
00035 
00036 class CMacPageSetupDialog;
00037 
00038 //@class Macintosh TPrint database and runtime handling.
00039 //@base     public | CObject
00040 //@devnote  This class is Mac only, use this in conjunction with the CMacPageSetupDialog
00041 //       and a CMProfile to maintain the user's current Page Setup, as well as a database of 
00042 //       TPrint record's in your application's .ini file.  Our experience is that the printer
00043 //       DC's that you get from WPL are constructed from the current printer's default
00044 //       TPrint, and have nothing to do with whatever the user has done in the Page Setup
00045 //       Dialog.  This class should be put in your App class (along with a CMProfile object).
00046 //       A list of each different TPrint record the user creates with CMacPageSetupDialog is
00047 //       kept in the ini file, and we can load one in if we need to switch from portrait to
00048 //       landscape, without bothering the user more than once per printer.  By using the 
00049 //       TPrint record maintained in your CTPrint object, you can always print with the user's
00050 //       latest settings.  The database currently distinguishes records by device ID (warning -
00051 //       some printers reuse other printer's ID's!!), page size, and orientation.
00052 class XMAC_CLASS CTPrint : public CObject
00053 {
00054    friend CMacPageSetupDialog;
00055 public:
00056    CTPrint (CMProfile * mp, CString inifilename);
00057    ~CTPrint ();
00058    
00059    BOOL     GetTprint      (TPrint * tpp);
00060    BOOL     GetTprint      (TPrint * tpp, int orientation);
00061    BOOL     PutTprint      (void);  
00062    BOOL     PutTprint      (TPrint * tpp);
00063    BOOL     StartPreparePrinting (CPrintInfo* pInfo, int orientation);
00064    BOOL     EndPreparePrinting      (CPrintInfo* pInfo, int maxpages);
00065    BOOL     GetPaperRects  (CRect & paper, CRect & printable, int dpi);
00066    BOOL     GetPaperRects  (TPrint * tpp, CRect & paper, CRect & printable, int dpi);
00067 
00068    enum {
00069       TPTRACTOR = 0x1000,
00070       TPORIENT  = 0x2000,
00071       TPHOTO     = 0x3000
00072    };
00073    enum {                  // various HP690 Kludge constants
00074       PHOTOWORD   = 0x11,     // the word we look at in the printX array
00075       HP690    = 0x1F,     // the HP690's (or Apple SW 4500's) WDEV
00076       PHOTOBIT = 0x8000 // if this bit is set, the PHOTO cartridge is installed
00077    };
00078 
00079    int         m_maxDPI;      // Maximun DPI for a current TPrint.
00080 protected:
00081    
00082    BOOL     GetUserTprint  (TPrint * tpp, int orientation);
00083    BOOL     GetRscTprint   (TPrint * tpp, int rid);
00084    CString     MakeRName      (TPrint * tpp, int orientation);
00085    void     SetCartridge   (TPrint * tpp);
00086 
00087    TPrint      m_tp;       // the currently setup tprint record
00088    BOOL     m_tpValid;     // if TRUE, the above is useful
00089    CMProfile   * m_mp;        // access to our ini file, which contains our TPrint database
00090    BOOL     m_saved;    // is m_tp on the disk?
00091    int         m_Cartridge;   // a horrible hack to track one specific printer's color cartridge status  
00092    CString     m_inifilename; // name of the app's inifile
00093 };
00094 
00095 
00096 //@class Macintosh Page Setup Dailog.
00097 //@devnote  This class is Mac only, use this in conjunction with the CTPrint object
00098 //       and a CMProfile to maintain the user's current Page Setup, as well as a database of 
00099 //       TPrint record's in your application's .ini file.  The dialog has an additional
00100 //       prompt line added to the printer's default dialog that asks the user to select the
00101 //       proper orientation for a given document.  CTPrint's GetTprint (x,y) function uses
00102 //       one of these in a loop to demand the appropriate setup if it's not available in it's
00103 //       database.  
00104 //
00105 class XMAC_CLASS CMacPageSetupDialog
00106 {
00107 public:
00108    CMacPageSetupDialog (CTPrint * ctp, int orient);
00109    int DoModal (void);
00110 protected:
00111    CTPrint * m_ctp;
00112 };
00113 
00114 #endif//_OS9
00115 #endif//_OS9PRINT
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
