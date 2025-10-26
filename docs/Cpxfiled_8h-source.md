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

# Cpxfiled.h

[Go to the documentation of this file.](Cpxfiled_8h.md)

<div class="fragment">

``` fragment
00001 /* KB  10/30/00  \Ken90\Include\3rdParty\CPXFILED.H
00002 * @doc
00003 * $Workfile: cpxFileDlg.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 11 $ $Author: Yury $ $Date: 6/22/97 10:30p $
00013 ************************************************************************/
00014 #ifndef __CPX_FILEDLG
00015 #define __CPX_FILEDLG
00016 
00017 #ifndef appendDITLBottom
00018 #define overlayDITL        0
00019 #define appendDITLRight    1
00020 #define appendDITLBottom   2
00021 #endif
00022 
00023 #define OFN_ADDEXTENSION              0x00100000     
00024 
00026 // CPXNewDir dialog
00027 
00028 //@class New directory dialog.
00029 //@base     public | CDialog 
00030 //@devnote  Lets you choose a new directory
00031 
00032 class XMAC_CLASS CPXNewDir : public CDialog
00033 {
00034 // Construction
00035 public:
00036    CPXNewDir(CWnd* pParent = NULL);   // standard constructor
00037 // Dialog Data
00038    //{{AFX_DATA(CPXNewDir)
00039    enum { IDD = IDD_CPX_NEWDIR };
00040    CString  m_NewDir;
00041    //}}AFX_DATA
00042 // Overrides
00043    // ClassWizard generated virtual function overrides
00044    //{{AFX_VIRTUAL(CPXNewDir)
00045    protected:
00046    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
00047    virtual void OnOK();
00048    //}}AFX_VIRTUAL
00049 // Implementation
00050 protected:
00051    // Generated message map functions
00052    //{{AFX_MSG(CPXNewDir)
00053    virtual BOOL OnInitDialog();
00054    //}}AFX_MSG
00055    DECLARE_MESSAGE_MAP()
00056 };
00057 
00058 #ifndef _MAC
00059 
00060 //@class Open or Save file dialog.
00061 //@base     public | CFileDialog for Win32 only
00062 //@devnote  When compiled for Windows platforms the <c CPXFileDialog> is mapped to the
00063 //       standard Win32 CFileDilaog.
00064 // To use the dialog box on the Macintosh, you must include "CpxDlgs.r" in your 
00065 //  "APP".r file.  If you'd like to have 3D gray buttons, the "CDEF3d.r" should also be
00066 //  included.  There are some limitations on what one can do in the dialog callbacks
00067 //  (inside the methods like OnUserItem(), OnFolderChanged()). Never call _chdir() or 
00068 //  any other APIs that will modify the current directory.  Some operations on DCs are 
00069 //  also proscribed: changing the clipping region in any way is not recommended.
00070 //
00071 class XMAC_CLASS CPXFileDialog : public CFileDialog
00072 {
00073 public:
00074 // CPXFileDialog (BOOL bOpen,LPCTSTR lpszDefExt = NULL,LPCTSTR lpszFileName = NULL,DWORD dwFlags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL );
00075 #if _MEMDEBUG
00076    void             *operator new( size_t size, char *file, const int line ) { return ALLOCEXT( size, file, line ); }
00077 #else
00078    void             *operator new( size_t size ) { return AllocExt( size ); }
00079 #endif   
00080    void              operator delete( void *ptr ) { FreeExt( ptr ); }
00081    BOOL  GetItemPos     (int nID, CRect *rect);
00082    int               m_DITLoperand;
00083 };
00084 
00085 
00086 #define OFN_CHOOSEDIR_FLAGS      OFN_SHOWHELP|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ENABLETEMPLATE
00087 
00088 //@class Choose directory dialog.
00089 //@base     public | CFileDialog for Win32 only.
00090 //@devnote Portable.
00091 class XMAC_CLASS CPXChooseDirectory : public CFileDialog
00092 {
00093 public:
00094     CPXChooseDirectory(LPCTSTR lpcszCaption, LPCTSTR lpcszInitialDir = NULL, CWnd* pWndParent = NULL);
00095    CString GetPathName(void);
00096 protected:
00097     virtual BOOL OnInitDialog();
00098    afx_msg void OnNewDir();
00099     DECLARE_MESSAGE_MAP()
00100 };
00101 
00102 #else // _MAC
00103 #ifndef _CPX_REZ_H
00104    #include <cpxRez.h>
00105 #endif
00106 
00107 #ifndef __MACFILES_H
00108    #include <MacFiles.h>
00109 #endif
00110 
00111 
00112 typedef struct S_FileTypes {
00113    S_FileTypes() {
00114       types = 0;
00115       ntypes = 0;
00116    }
00117    ~S_FileTypes() {
00118       DELETE_ARRAY(types);
00119    }
00120    Str32    name;
00121    FOURCC      *types;
00122    short    ntypes;
00123    CExtension  ext;
00124 } FTYPES;
00125 
00126 #define MAX_FILTERS  128
00127 
00128 class XMAC_CLASS CPXFileDialog 
00129 {
00130 public:
00131    CPXFileDialog (BOOL bOpen,LPCTSTR lpszDefExt = NULL,LPCTSTR lpszFileName = NULL,DWORD dwFlags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL );
00132    ~CPXFileDialog();
00133 
00134    BOOL  GetItemPos     (int nID, CRect *rect);
00135    virtual void   InvalidateRect (CRect *rect, BOOL erase);
00136    virtual int    DoModal        (void);
00137       CString     GetPathName    (void);
00138       CString     GetFileName    (void);
00139       CString     GetFileExt     (void);
00140       CString     GetFileTitle   (void);
00141       BOOL     GetReadOnlyPref   (void) const;
00142 
00143 // Standard MFC ones we would like to have here
00144    virtual void   DoDataExchange (CDataExchange* pDX) { return; }
00145    BOOL  OnCommand      (WPARAM wParam, LPARAM lParam)   { return FALSE; }
00146    BOOL  OnEraseBkgnd   (CDC* pDC)                 { return FALSE; }
00147    CDC      *GetDC         (void);
00148    void  ReleaseDC      (CDC *pDC);
00149 //Overridables
00150    virtual void   OnMouseMove    (UINT nFlags, CPoint point);     
00151    virtual BOOL   OnSetCursor    (CWnd* pWnd, UINT nHitTest, UINT message);
00152    virtual void   OnFileNameChange();
00153    virtual void   OnFolderChange();
00154    virtual BOOL   OnFileNameOK   (void);
00155    virtual void   OnLBSelChangedNotify(UINT, UINT, UINT);
00156    virtual void   OnInitDone     (void);
00157    virtual void   OnTypeChange   (void);
00158    virtual  void  OnHelp         (void);
00159    virtual  void  OnUserItem     (short item);
00160    virtual void   OnLButtonDown   ( UINT nFlags, CPoint point ) {}
00161    virtual void   OnLButtonUp     ( UINT nFlags, CPoint point ) {}
00162 
00163 
00164    BOOL IsFileEdit(Rect *rect);
00165 
00166    OPENFILENAME      m_ofn;
00167    int               m_DITLoperand;
00168 protected:
00169    BOOL           m_bOpenFileDialog;
00170    DialogPtr         m_MacDlg;
00171 private:
00172    void     SetFilter      (LPCSTR filter);
00173    CString     getFileName    (void);
00174    CString           m_iniFilter;
00175    CString           m_FileTitle;
00176    CString           m_FilePath;
00177    FTYPES            m_Types[MAX_FILTERS];
00178    int               m_fcnt;
00179    short          m_SelType;
00180    StandardFileReply m_SFReply;
00181    BOOL           m_edFilter;
00182    BOOL           m_RdOnly;
00183    BOOL           m_inModal;
00184    HDC               m_WrappedDC;
00185    Rect           m_FileEditRect;
00186    int               m_Return;
00187 friend unsigned char __pascal FileOpenFilter(CInfoPBPtr pb,void *data);
00188 friend short __pascal OpenFileHook(short item,DialogPtr dlg,void *data);
00189 friend pascal Boolean EventFilter(DialogPtr dlg, EventRecord *event, short *item, void *data);
00190 friend void MacSetFileDialogStartPosition (LPCSTR start, StandardFileReply *sfr);
00191 
00192 };
00193 
00194 class XMAC_CLASS CPXChooseDirectory 
00195 {
00196 public:
00197     CPXChooseDirectory(LPCTSTR lpcszCaption, LPCTSTR lpcszInitialDir = NULL, CWnd* pWndParent = NULL);
00198    CString GetPathName(void);
00199 
00200    virtual int    DoModal        (void);
00201 
00202 private:
00203    StandardFileReply m_SFReply;
00204    int               m_OK;
00205    CString           m_FilePath;
00206    CString           m_Title;
00207 friend unsigned char __pascal ChooseDirFilter(CInfoPBPtr pb,void *data);
00208 friend short __pascal ChooseDirHook(short item,DialogPtr dlg,void *data);
00209 
00210 };
00211 
00212 #endif // _MAC
00213 
00214 #endif //__CPX_FILEDLG
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:43 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
