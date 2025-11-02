//BC  5/18/2005  \BobL120\Include\F_Protos.h
#pragma once

#include "StdAfx.h"
#include "Exports.h"

class String;

FILEIOEXPORT BOOL IsShift() noexcept;
FILEIOEXPORT BOOL IsCtrl() noexcept;
FILEIOEXPORT BOOL IsAlt() noexcept;
FILEIOEXPORT BOOL IsLeft() noexcept;
FILEIOEXPORT BOOL IsMiddle() noexcept;
FILEIOEXPORT BOOL IsRight() noexcept;
FILEIOEXPORT BOOL IsXLock() noexcept;
FILEIOEXPORT BOOL IsYLock() noexcept;
FILEIOEXPORT BOOL IsZLock() noexcept;
FILEIOEXPORT BOOL IsFourKey() noexcept;
FILEIOEXPORT BOOL IsFiveKey() noexcept;
FILEIOEXPORT BOOL IsSixKey() noexcept;
FILEIOEXPORT BOOL IsSelectRangeKey() noexcept;
FILEIOEXPORT BOOL IsMultiSelectKey() noexcept;
FILEIOEXPORT BOOL IsRemoveKey() noexcept;
FILEIOEXPORT BOOL IsCopyKey() noexcept;
FILEIOEXPORT BOOL IsSpace() noexcept;
FILEIOEXPORT void IgnoreEscapeKey(BOOL ignore) noexcept;
FILEIOEXPORT BOOL EscapeKeyDown();
FILEIOEXPORT void SetBasePath(const String &);
FILEIOEXPORT String GetBasePath() noexcept;
FILEIOEXPORT void FreeBasePaths() noexcept;
FILEIOEXPORT void WatchMouse(BOOL) noexcept;
FILEIOEXPORT BOOL IsWatchMouse() noexcept;
FILEIOEXPORT void HideCursor() noexcept; // does ShowCursor(False) with return value checking
FILEIOEXPORT void ShowCursor() noexcept; // does ShowCursor(True)
FILEIOEXPORT BOOL MessageReceived(BOOL includemouseup = false);
FILEIOEXPORT String GetResourceString(UINT id) noexcept;
//returning a CString instead of allocating a hash string, prevent many conversions for AFX functions
FILEIOEXPORT CString GetResource_CString(UINT id);
FILEIOEXPORT void DoEvents(CWnd *pWnd = nullptr);
FILEIOEXPORT void DoOneEvent(CWnd *pWnd = nullptr);
FILEIOEXPORT void EventsResponsible();
FILEIOEXPORT float GetClockTicks() noexcept; //in seconds
FILEIOEXPORT ULONG GetClockCount(); //returning timeGetTime()
FILEIOEXPORT void PrintMemoryMessage(const String &title);
FILEIOEXPORT void SetSwapping(BOOL pswapping);
FILEIOEXPORT BOOL IsSwapping() noexcept;
FILEIOEXPORT void RemoveCachedMessages();
FILEIOEXPORT void RemoveCachedKeyMessages();
FILEIOEXPORT int GetRegistryValue(const String &section, const String &entry, int defaultvalue);
FILEIOEXPORT float GetRegistryValue(const String &section, const String &entry, float defaultvalue);
FILEIOEXPORT double GetRegistryValue(const String &section, const String &entry, double defaultvalue);
FILEIOEXPORT String GetRegistryString(const String &section, const String &entry, const String &defaultstring);
FILEIOEXPORT BOOL SetRegistryValue(const String &section, const String &entry, int tvalue);
FILEIOEXPORT BOOL SetRegistryValue(const String &section, const String &entry, float value);
FILEIOEXPORT BOOL SetRegistryValue(const String &section, const String &entry, double value);
FILEIOEXPORT BOOL SetRegistryString(const String &section, const String &entry, const String &string);
FILEIOEXPORT BOOL DeleteRegistryItem(const String &section, const String &entry);
FILEIOEXPORT void ResetRegistry(const String &regname);
FILEIOEXPORT void ResetRegistry(const String &key, const String &regname);
FILEIOEXPORT BOOL GetRegistryBOOL(const String &section, const String &entry, BOOL defaultvalue);
FILEIOEXPORT BOOL SetRegistryBOOL(const String &section, const String &entry, BOOL value);
FILEIOEXPORT bool GetRegistryBOOL(const String &section, const String &entry, bool defaultvalue);
FILEIOEXPORT bool SetRegistryBOOL(const String &section, const String &entry, bool value);
FILEIOEXPORT int GetRegistryValue(BOOL ischar, const char *section, const char *entry, int defaultvalue);
FILEIOEXPORT float GetRegistryValue(BOOL ischar, const char *section, const char *entry, float defaultvalue);
FILEIOEXPORT char *GetRegistryString(BOOL ischar, const char *section, const char *entry, const char *defaultstring);
FILEIOEXPORT BOOL SetRegistryValue(BOOL ischar, const char *section, const char *entry, int tvalue);
FILEIOEXPORT BOOL SetRegistryValue(BOOL ischar, const char *section, const char *entry, float value);
FILEIOEXPORT BOOL SetRegistryString(BOOL ischar, const char *section, const char *entry, const char *string);
FILEIOEXPORT BOOL WriteProfileBinarySplit(BOOL ischar, const char *section, const char *entry, LPBYTE pData, UINT nBytes);
FILEIOEXPORT BOOL GetProfileBinarySplit(BOOL ischar, const char *section, const char *entry, LPBYTE *ppData, UINT *pBytes);
FILEIOEXPORT int GetLocalRegistryValue(const String &section, const String &entry, int defaultvalue);
FILEIOEXPORT float GetLocalRegistryValue(const String &section, const String &entry, float defaultvalue);
FILEIOEXPORT String GetLocalRegistryString(const String &section, const String &entry, const String &defaultstring);
FILEIOEXPORT BOOL SetLocalRegistryValue(const String &section, const String &entry, int tvalue);
FILEIOEXPORT BOOL SetLocalRegistryValue(const String &section, const String &entry, float value);
FILEIOEXPORT BOOL SetLocalRegistryString(const String &section, const String &entry, const String &string);
FILEIOEXPORT void SetLocalRegistryProfile(const String &myprofile);
FILEIOEXPORT String GetLocalRegistryProfile();
FILEIOEXPORT void FreeLocalRegistryProfile();
FILEIOEXPORT void ResetLocalRegistry(const String &regname);
FILEIOEXPORT void ResetLocalRegistry(const String &key, const String &regname);
FILEIOEXPORT void SetProfileLocation(const String &profilelocation);
FILEIOEXPORT String GetProfileLocation();
FILEIOEXPORT void FreeProfileLocation();
FILEIOEXPORT void SetFoldersLocation(const String &folderslocation);
FILEIOEXPORT String GetFoldersLocation();
FILEIOEXPORT void FreeFoldersLocation();
FILEIOEXPORT BOOL WriteProfileBinarySplit(const String &section, const String &entry, LPBYTE pData, UINT nBytes);
FILEIOEXPORT BOOL GetProfileBinarySplit(const String &section, const String &entry, LPBYTE *ppData, UINT *pBytes);

class CHashFileDialog;

FILEIOEXPORT BOOL SaveRequest(UINT titleid, UINT filterid, String &filename, const char *extension, const char *inilookup, CWnd *parent = nullptr);
FILEIOEXPORT BOOL SaveRequest(UINT titleid, const String &filters, String &filename, const char *extension, const char *inilookup, CWnd *parent = nullptr, int *pindex = nullptr);
FILEIOEXPORT BOOL SaveRequest(const String &title, const String &filters, String &filename, const char *cextension, const char *inilookup, CWnd *parent = nullptr, int *pindex = nullptr);
FILEIOEXPORT String GetDescriptionGivenIndex(const String &filters, int index);

class StringList;

FILEIOEXPORT void DeleteStringList(const StringList *);
FILEIOEXPORT BOOL OpenRequest(UINT titleid, UINT filterid, String &filename, const char *extension, const char *inilookup, int *index = nullptr, CWnd *parent = nullptr, StringList **multiselect = nullptr, CHashFileDialog *pdlg = nullptr);
FILEIOEXPORT BOOL OpenRequest(const String &title, const String &filter, String &filename, const char *cextension, const char *inilookup, int *index = nullptr, CWnd *parent = nullptr, StringList **multiselect = nullptr, CHashFileDialog *pdlg = nullptr);
FILEIOEXPORT BOOL OpenRequest(const String &title, const String &filter, String &filename, const char *cextension, const char *inilookup, int *pindex, CWnd *parent, StringList **multiselect, CHashFileDialog *pdlg, BOOL *pbCancelAll);
FILEIOEXPORT BOOL StringRequest(UINT messageid, String &string, CWnd *parent = nullptr, UINT titleid = 0);
FILEIOEXPORT BOOL StringRequest(CString &message, String &string, CWnd *parent = nullptr, UINT titleid = 0);
FILEIOEXPORT BOOL StringRequest(const CString &message, String &string, CWnd *parent = nullptr, UINT titleid = 0);
FILEIOEXPORT BOOL DirRequest(String &dir, const String &Caption, const String &InitialDir, CWnd *pWndParent = nullptr);

FILEIOEXPORT BOOL LaunchAssociatedApp(const String &filename);
FILEIOEXPORT void LaunchEMail(HWND hwnd, const String &address);
FILEIOEXPORT void LaunchURL(HWND hwnd, const String &url);
FILEIOEXPORT void LogPoolMemory();
FILEIOEXPORT void LogPoolMemory(String &logstring) noexcept;
FILEIOEXPORT BOOL QueryRegistration() noexcept;
FILEIOEXPORT BOOL IsRegistered() noexcept;
FILEIOEXPORT void SetRegistered(BOOL value) noexcept;
FILEIOEXPORT CFont *GetGUIFont();

class Time;
FILEIOEXPORT void AFXAPI DDX_Time(CDataExchange *pDX, int nIDC, Time &time, int fps, int timeunits, BOOL treatasdelta = false);
FILEIOEXPORT void AFXAPI DDX_Time(CDataExchange *pDX, int nIDC, Time &time, int fps, TimeUnit timeunits, BOOL treatasdelta = false);
FILEIOEXPORT void AFXAPI DDV_MinMaxTime(CDataExchange *pDX, Time time, Time minvalue, Time maxvalue, int fps, int timeunits);
FILEIOEXPORT void AFXAPI DDV_MinMaxTime(CDataExchange *pDX, Time time, Time minvalue, Time maxvalue, int fps, TimeUnit timeunits);
FILEIOEXPORT void AFXAPI DDV_NotEmpty(CDataExchange *pDX, const String &string);

//Internet
FILEIOEXPORT BOOL IsConnectedToInternet() noexcept;
FILEIOEXPORT BOOL IsUseDialUp() noexcept;
FILEIOEXPORT DWORD ConnectToInternetUsingDialUp(DWORD &connection) noexcept;
FILEIOEXPORT BOOL HangUpDialUp(DWORD connection) noexcept;

//Resource
FILEIOEXPORT BOOL GetProductVersion(const String &filename, int &vermajor, int &verminor, int &revmajor, int &revminor) noexcept;
FILEIOEXPORT String GetProductVersion(const String &filename);
