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

# Misc.h

[Go to the documentation of this file.](Misc_8h.md)

<div class="fragment">

``` fragment
00001 // NAP  12/20/2004  \Noel120\Include\SDK\Misc.h
00002 
00003 #ifndef __MISC_H
00004 #define __MISC_H
00005 
00006 #ifndef _SMALLPDB
00007 
00008 #include "Exports.h"
00009 
00010 #ifndef __COLORBUF_H
00011 #include "ColorBuf.h"
00012 #endif
00013 #ifndef __ColorBuf_INL
00014 #include "ColorBuf.inl"
00015 #endif
00016 
00017 class Vector;
00018 class IEModel;
00019 class BitmapNode;
00020 //*********************************************************
00021 //** Misc Exported Functions
00022 //*********************************************************
00023 PLUGINEXPORT HWND GetMainApplicationWnd();
00024 PLUGINEXPORT int GetTimeMode();//enum { SMPTE, FRAMES, CELS };
00025 PLUGINEXPORT float GetTurbulence( const Vector &vec );
00026 PLUGINEXPORT void DeleteIEModel(IEModel *iemodel);
00027 PLUGINEXPORT CWnd *GetPanel( const String &name, BOOL ensurevisible=TRUE );
00028 PLUGINEXPORT BOOL IsInNetRender();
00029 PLUGINEXPORT ColorBuf GetColor( int index );
00030 PLUGINEXPORT void RefreshAllTrees();
00031 
00032 PLUGINEXPORT BitmapNode *BrowseImage(const String &title, String &filename);
00033 
00034 // derive apps in plugins off of this to get around funky Mac crash
00035 class CPluginApp : public CWinApp
00036 {
00037 public:
00038    virtual ~CPluginApp() {}
00039 
00040    virtual CWnd* GetMainWnd() { return CWinApp::GetMainWnd(); }
00041    virtual int Run() { return CWinApp::Run(); }
00042    virtual BOOL PreTranslateMessage(MSG* pMsg) { return CWinApp::PreTranslateMessage( pMsg ); }
00043    virtual BOOL PumpMessage() { return CWinApp::PumpMessage(); }
00044    virtual BOOL OnIdle(LONG lCount) { return CWinApp::OnIdle( lCount ); }
00045    virtual BOOL IsIdleMessage(MSG* pMsg) { return CWinApp::IsIdleMessage( pMsg ); }
00046    virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt) { return CWinApp::DoMessageBox( lpszPrompt, nType, nIDPrompt ); }
00047    virtual BOOL InitInstance() { return CWinApp::InitInstance(); }
00048    virtual int  ExitInstance() { return CWinApp::ExitInstance(); }
00049    virtual void DoWaitCursor(int nCode) { CWinApp::DoWaitCursor( nCode ); }
00050 };
00051 
00052 // derive dialogs in plugins off of this to get around funky Mac crash
00053 class CPluginDialog : public CDialog
00054 {
00055 public:
00056    CPluginDialog() {}
00057    CPluginDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL) : CDialog( nIDTemplate, pParentWnd ) {}
00058    virtual ~CPluginDialog() {}
00059 
00060    virtual void PreSubclassWindow() { CDialog::PreSubclassWindow(); }
00061    virtual WNDPROC* GetSuperWndProcAddr() { return CDialog::GetSuperWndProcAddr(); }
00062    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) { return CDialog::WindowProc( message, wParam, lParam ); }
00063    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) { return CDialog::OnWndMsg( message,  wParam,  lParam, pResult ); }
00064    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) { return CDialog::DefWindowProc( message, wParam, lParam ); }
00065    virtual void PreInitDialog() { CDialog::PreInitDialog(); }
00066    virtual CRuntimeClass* GetRuntimeClass() const { return CDialog::GetRuntimeClass(); }
00067    virtual BOOL OnInitDialog() { return CDialog::OnInitDialog(); }
00068    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) { return CDialog::OnCommand( wParam, lParam ); }
00069    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) { return CDialog::OnNotify( wParam, lParam, pResult ); }
00070    virtual BOOL CheckAutoCenter() { return CDialog::CheckAutoCenter(); }
00071    virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) { return CDialog::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo); }
00072    virtual BOOL PreTranslateMessage(MSG* pMsg) { return CDialog::PreTranslateMessage( pMsg ); }
00073    virtual BOOL ContinueModal() { return CDialog::ContinueModal(); }
00074    virtual void EndModalLoop(int nResult) { CDialog::EndModalLoop( nResult ); }
00075    virtual BOOL IsFrameWnd() const { return CDialog::IsFrameWnd(); }
00076    virtual BOOL DestroyWindow() { return CDialog::DestroyWindow(); }
00077    virtual void PostNcDestroy() { CDialog::PostNcDestroy(); }
00078    virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange( pDX ); }
00079    virtual void OnOK() { CDialog::OnOK(); }
00080    virtual void OnCancel() { CDialog::OnCancel(); }
00081 };
00082 
00083 #endif
00084 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
