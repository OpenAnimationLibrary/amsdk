;  // String containing the search query.
00272     LONG iProximity;         // Word proximity.
00273     BOOL fStemmedSearch;     // TRUE for StemmedSearch only.
00274     BOOL fTitleOnly;         // TRUE for Title search only.
00275     BOOL fExecute;           // TRUE to initiate the search.
00276     LPCTSTR pszWindow;       // Window to display in
00277 } HH_FTS_QUERY;
00278 
00279 // HH_WINTYPE Structure
00280 
00281 typedef struct tagHH_WINTYPE {
00282     int     cbStruct;        // IN: size of this structure including all Information Types
00283     BOOL    fUniCodeStrings; // IN/OUT: TRUE if all strings are in UNICODE
00284     LPCTSTR pszType;         // IN/OUT: Name of a type of window
00285     DWORD   fsValidMembers;  // IN: Bit flag of valid members (HHWIN_PARAM_)
00286     DWORD   fsWinProperties; // IN/OUT: Properties/attributes of the window (HHWIN_)
00287 
00288     LPCTSTR pszCaption;      // IN/OUT: Window title
00289     DWORD   dwStyles;        // IN/OUT: Window styles
00290     DWORD   dwExStyles;      // IN/OUT: Extended Window styles
00291     RECT    rcWindowPos;     // IN: Starting position, OUT: current position
00292     int     nShowState;      // IN: show state (e.g., SW_SHOW)
00293 
00294     HWND  hwndHelp;          // OUT: window handle
00295     HWND  hwndCaller;        // OUT: who called this window
00296 
00297     HH_INFOTYPE* paInfoTypes;  // IN: Pointer to an array of Information Types
00298 
00299     // The following members are only valid if HHWIN_PROP_TRI_PANE is set
00300 
00301     HWND  hwndToolBar;      // OUT: toolbar window in tri-pane window
00302     HWND  hwndNavigation;   // OUT: navigation window in tri-pane window
00303     HWND  hwndHTML;         // OUT: window displaying HTML in tri-pane window
00304     int   iNavWidth;        // IN/OUT: width of navigation window
00305     RECT  rcHTML;           // OUT: HTML window coordinates
00306 
00307     LPCTSTR pszToc;         // IN: Location of the table of contents file
00308     LPCTSTR pszIndex;       // IN: Location of the index file
00309     LPCTSTR pszFile;        // IN: Default location of the html file
00310     LPCTSTR pszHome;        // IN/OUT: html file to display when Home button is clicked
00311     DWORD   fsToolBarFlags; // IN: flags controling the appearance of the toolbar
00312     BOOL    fNotExpanded;   // IN: TRUE/FALSE to contract or expand, OUT: current state
00313     int     curNavType;     // IN/OUT: UI to display in the navigational pane
00314     int     tabpos;         // IN/OUT: HHWIN_NAVTAB_TOP, HHWIN_NAVTAB_LEFT, or HHWIN_NAVTAB_BOTTOM
00315     int     idNotify;       // IN: ID to use for WM_NOTIFY messages
00316     BYTE    tabOrder[HH_MAX_TABS + 1];    // IN/OUT: tab order: Contents, Index, Search, History, Favorites, Reserved 1-5, Custom tabs
00317     int     cHistory;       // IN/OUT: number of history items to keep (default is 30)
00318     LPCTSTR pszJump1;       // Text for HHWIN_BUTTON_JUMP1
00319     LPCTSTR pszJump2;       // Text for HHWIN_BUTTON_JUMP2
00320     LPCTSTR pszUrlJump1;    // URL for HHWIN_BUTTON_JUMP1
00321     LPCTSTR pszUrlJump2;    // URL for HHWIN_BUTTON_JUMP2
00322     RECT    rcMinSize;      // Minimum size for window (ignored in version 1)
00323     int     cbInfoTypes;    // size of paInfoTypes;
00324     LPCTSTR pszCustomTabs;  // multiple zero-terminated strings
00325 } HH_WINTYPE, *PHH_WINTYPE;
00326 
00327 enum {
00328     HHACT_TAB_CONTENTS,
00329     HHACT_TAB_INDEX,
00330     HHACT_TAB_SEARCH,
00331     HHACT_TAB_HISTORY,
00332     HHACT_TAB_FAVORITES,
00333 
00334     HHACT_EXPAND,
00335     HHACT_CONTRACT,
00336     HHACT_BACK,
00337     HHACT_FORWARD,
00338     HHACT_STOP,
00339     HHACT_REFRESH,
00340     HHACT_HOME,
00341     HHACT_SYNC,
00342     HHACT_OPTIONS,
00343     HHACT_PRINT,
00344     HHACT_HIGHLIGHT,
00345     HHACT_CUSTOMIZE,
00346     HHACT_JUMP1,
00347     HHACT_JUMP2,
00348     HHACT_ZOOM,
00349     HHACT_TOC_NEXT,
00350     HHACT_TOC_PREV,
00351     HHACT_NOTES,
00352 
00353     HHACT_LAST_ENUM,
00354 };
00355 
00356 typedef struct tagHHNTRACK
00357 {
00358     NMHDR   hdr;
00359     PCSTR   pszCurUrl;      // Multi-byte, null-terminated string
00360     int     idAction;       // HHACT_ value
00361     HH_WINTYPE* phhWinType; // Current window type structure
00362 } HHNTRACK;
00363 
00364 HWND
00365 WINAPI
00366 HtmlHelpA(
00367     HWND hwndCaller,
00368     LPCSTR pszFile,
00369     UINT uCommand,
00370     DWORD_PTR dwData
00371     );
00372 
00373 HWND
00374 WINAPI
00375 HtmlHelpW(
00376     HWND hwndCaller,
00377     LPCWSTR pszFile,
00378     UINT uCommand,
00379     DWORD_PTR dwData
00380     );
00381 #ifdef UNICODE
00382 #define HtmlHelp  HtmlHelpW
00383 #else
00384 #define HtmlHelp  HtmlHelpA
00385 #endif // !UNICODE
00386 
00387 // Use the following for GetProcAddress to load from hhctrl.ocx
00388 
00389 #define ATOM_HTMLHELP_API_ANSI    (LPTSTR)((DWORD)((WORD)(14)))
00390 #define ATOM_HTMLHELP_API_UNICODE (LPTSTR)((DWORD)((WORD)(15)))
00391 
00393 //
00394 // Global Control Properties. 
00395 //
00396 typedef enum tagHH_GPROPID
00397 {
00398     HH_GPROPID_SINGLETHREAD=1,      // VARIANT_BOOL: True for single thread
00399     HH_GPROPID_TOOLBAR_MARGIN=2,    // long: Provides a left/right margin around the toolbar.
00400     HH_GPROPID_UI_LANGUAGE=3,       // long: LangId of the UI.
00401     HH_GPROPID_CURRENT_SUBSET=4,    // BSTR: Current subset.
00402     HH_GPROPID_CONTENT_LANGUAGE=5   // long: LandId for desired content.
00403 } HH_GPROPID;
00404 
00406 //
00407 // Global Property structure
00408 //
00409 #ifdef __oaidl_h__
00410 
00411 #pragma pack(push, 8)
00412 
00413 typedef struct tagHH_GLOBAL_PROPERTY
00414 {
00415     HH_GPROPID  id;
00416     VARIANT     var;
00417 } HH_GLOBAL_PROPERTY ;
00418 
00419 #pragma pack(pop)
00420 #endif
00421 
00422 #ifdef __cplusplus
00423 }
00424 #endif // __cplusplus
00425 
00426 #endif // __HTMLHELP_H__
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
