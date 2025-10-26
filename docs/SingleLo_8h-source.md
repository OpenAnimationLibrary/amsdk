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

# SingleLo.h

[Go to the documentation of this file.](SingleLo_8h.md)

<div class="fragment">

``` fragment
00001 // Dan  4/15/2003  \Dan105\Include\SingleLo.h
00002 
00003 #define __SINGLELO_H
00004 
00005 #ifndef _OS9
00006 #include <afxmt.h>
00007 #else
00008 class CSyncObject : public CObject
00009 {
00010 public:
00011    operator HANDLE() const;
00012    HANDLE  m_hObject;
00013    CSyncObject(LPCTSTR pstrName) {}
00014    CSyncObject() {}
00015 
00016 // Operations
00017    virtual BOOL Lock(DWORD dwTimeout = INFINITE) { return TRUE; }
00018    virtual BOOL Unlock() = 0;
00019    virtual BOOL Unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */)
00020       { return TRUE; }
00021    virtual ~CSyncObject() {}
00022 };
00023 
00024 class CSingleLock
00025 {
00026 public:
00027    CSingleLock(CSyncObject* pObject, BOOL bInitialLock = FALSE) {}
00028    BOOL Lock(DWORD dwTimeOut = INFINITE) { return TRUE; }
00029    BOOL Unlock() { return TRUE; }
00030    BOOL Unlock(LONG lCount, LPLONG lPrevCount = NULL) { return TRUE; }
00031    BOOL IsLocked() { return FALSE; }
00032    ~CSingleLock() { }
00033 
00034 protected:
00035    CSyncObject* m_pObject;
00036    HANDLE  m_hObject;
00037    BOOL    m_bAcquired;
00038 };
00039 #endif
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:46 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
