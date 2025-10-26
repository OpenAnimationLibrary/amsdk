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

# HtmlHelp.h

[Go to the documentation of this file.](HtmlHelp_8h.md)

<div class="fragment">

``` fragment
00001 /****************************************************************************
00002 *                                                                           *
00003 * HtmlHelp.h                                                                *
00004 *                                                                           *
00005 * Copyright (c) 1996-1997, Microsoft Corp. All rights reserved.             *
00006 *                                                                           *
00007 ****************************************************************************/
00008 
00009 #if _MSC_VER > 1000
00010 #pragma once
00011 #endif
00012 
00013 #ifndef __HTMLHELP_H__
00014 #define __HTMLHELP_H__
00015 
00016 #ifdef __cplusplus
00017 extern "C" {
00018 #endif  // __cplusplus
00019 
00020 // Defines for Win64
00021 #ifndef _WIN64
00022 #define DWORD_PTR DWORD
00023 #endif
00024 
00025 // Commands to pass to HtmlHelp()
00026 
00027 #define HH_DISPLAY_TOPIC        0x0000
00028 #define HH_HELP_FINDER          0x0000  // WinHelp equivalent
00029 #define HH_DISPLAY_TOC          0x0001  
00030 #define HH_DISPLAY_INDEX        0x0002  
00031 #define HH_DISPLAY_SEARCH       0x0003  
00032 #define HH_SET_WIN_TYPE         0x0004
00033 #define HH_GET_WIN_TYPE         0x0005
00034 #define HH_GET_WIN_HANDLE       0x0006
00035 #define HH_ENUM_INFO_TYPE       0x0007  // Get Info type name, call repeatedly to enumerate, -1 at end
00036 #define HH_SET_INFO_TYPE        0x0008  // Add Info type to filter.
00037 #define HH_SYNC                 0x0009
00038 #define HH_RESERVED1            0x000A
00039 #define HH_RESERVED2            0x000B
00040 #define HH_RESERVED3            0x000C
00041 #define HH_KEYWORD_LOOKUP       0x000D
00042 #define HH_DISPLAY_TEXT_POPUP   0x000E  // display string resource id or text in a popup window
00043 #define HH_HELP_CONTEXT         0x000F  // display mapped numeric value in dwData
00044 #define HH_TP_HELP_CONTEXTMENU  0x0010  // text popup help, same as WinHelp HELP_CONTEXTMENU
00045 #define HH_TP_HELP_WM_HELP      0x0011  // text popup help, same as WinHelp HELP_WM_HELP
00046 #define HH_CLOSE_ALL            0x0012  // close all windows opened directly or indirectly by the caller
00047 #define HH_ALINK_LOOKUP         0x0013  // ALink version of HH_KEYWORD_LOOKUP
00048 #define HH_GET_LAST_ERROR       0x0014  // not currently implemented // See HHERROR.h
00049 #define HH_ENUM_CATEGORY        0x0015 // Get category name, call repeatedly to enumerate, -1 at end
00050 #define HH_ENUM_CATEGORY_IT     0x0016  // Get category info type members, call repeatedly to enumerate, -1 at end
00051 #define HH_RESET_IT_FILTER      0x0017  // Clear the info type filter of all info types.
00052 #define HH_SET_INCLUSIVE_FILTER 0x0018  // set inclusive filtering method for untyped topics to be included in display
00053 #define HH_SET_EXCLUSIVE_FILTER 0x0019  // set exclusive filtering method for untyped topics to be excluded from display
00054 #define HH_INITIALIZE            0x001C  // Initializes the help system.
00055 #define HH_UNINITIALIZE          0x001D  // Uninitializes the help system.
00056 #define HH_PRETRANSLATEMESSAGE  0x00fd  // Pumps messages. (NULL, NULL, MSG*). 
00057 #define HH_SET_GLOBAL_PROPERTY  0x00fc  // Set a global property. (NULL, NULL, HH_GPROP)
00058 
00059 #define HHWIN_PROP_TAB_AUTOHIDESHOW (1 << 0)    // Automatically hide/show tri-pane window
00060 #define HHWIN_PROP_ONTOP            (1 << 1)    // Top-most window
00061 #define HHWIN_PROP_NOTITLEBAR       (1 << 2)    // no title bar
00062 #define HHWIN_PROP_NODEF_STYLES     (1 << 3)    // no default window styles (only HH_WINTYPE.dwStyles)
00063 #define HHWIN_PROP_NODEF_EXSTYLES   (1 << 4)    // no default extended window styles (only HH_WINTYPE.dwExStyles)
00064 #define HHWIN_PROP_TRI_PANE         (1 << 5)    // use a tri-pane window
00065 #define HHWIN_PROP_NOTB_TEXT        (1 << 6)    // no text on toolbar buttons
00066 #define HHWIN_PROP_POST_QUIT        (1 << 7)    // post WM_QUIT message when window closes
00067 #define HHWIN_PROP_AUTO_SYNC        (1 << 8)    // automatically ssync contents and index
00068 #define HHWIN_PROP_TRACKING         (1 << 9)    // send tracking notification messages
00069 #define HHWIN_PROP_TAB_SEARCH       (1 << 10)   // include search tab in navigation pane
00070 #define HHWIN_PROP_TAB_HISTORY      (1 << 11)   // include history tab in navigation pane
00071 #define HHWIN_PROP_TAB_FAVORITES    (1 << 12)   // include favorites tab in navigation pane
00072 #define HHWIN_PROP_CHANGE_TITLE     (1 << 13)   // Put current HTML title in title bar
00073 #define HHWIN_PROP_NAV_ONLY_WIN     (1 << 14)   // Only display the navigation window
00074 #define HHWIN_PROP_NO_TOOLBAR       (1 << 15)   // Don't display a toolbar
00075 #define HHWIN_PROP_MENU             (1 << 16)   // Menu
00076 #define HHWIN_PROP_TAB_ADVSEARCH    (1 << 17)   // Advanced FTS UI.
00077 #define HHWIN_PROP_USER_POS         (1 << 18)   // After initial creation, user controls window size/position
00078 #define HHWIN_PROP_TAB_CUSTOM1      (1 << 19)   // Use custom tab #1
00079 #define HHWIN_PROP_TAB_CUSTOM2      (1 << 20)   // Use custom tab #2
00080 #define HHWIN_PROP_TAB_CUSTOM3      (1 << 21)   // Use custom tab #3
00081 #define HHWIN_PROP_TAB_CUSTOM4      (1 << 22)   // Use custom tab #4
00082 #define HHWIN_PROP_TAB_CUSTOM5      (1 << 23)   // Use custom tab #5
00083 #define HHWIN_PROP_TAB_CUSTOM6      (1 << 24)   // Use custom tab #6
00084 #define HHWIN_PROP_TAB_CUSTOM7      (1 << 25)   // Use custom tab #7
00085 #define HHWIN_PROP_TAB_CUSTOM8      (1 << 26)   // Use custom tab #8
00086 #define HHWIN_PROP_TAB_CUSTOM9      (1 << 27)   // Use custom tab #9
00087 #define HHWIN_TB_MARGIN             (1 << 28)   // the window type has a margin
00088 
00089 #define HHWIN_PARAM_PROPERTIES      (1 << 1)    // valid fsWinProperties
00090 #define HHWIN_PARAM_STYLES          (1 << 2)    // valid dwStyles
00091 #define HHWIN_PARAM_EXSTYLES        (1 << 3)    // valid dwExStyles
00092 #define HHWIN_PARAM_RECT            (1 << 4)    // valid rcWindowPos
00093 #define HHWIN_PARAM_NAV_WIDTH       (1 << 5)    // valid iNavWidth
00094 #define HHWIN_PARAM_SHOWSTATE       (1 << 6)    // valid nShowState
00095 #define HHWIN_PARAM_INFOTYPES       (1 << 7)    // valid apInfoTypes
00096 #define HHWIN_PARAM_TB_FLAGS        (1 << 8)    // valid fsToolBarFlags
00097 #define HHWIN_PARAM_EXPANSION       (1 << 9)    // valid fNotExpanded
00098 #define HHWIN_PARAM_TABPOS          (1 << 10)   // valid tabpos
00099 #define HHWIN_PARAM_TABORDER        (1 << 11)   // valid taborder
00100 #define HHWIN_PARAM_HISTORY_COUNT   (1 << 12)   // valid cHistory
00101 #define HHWIN_PARAM_CUR_TAB         (1 << 13)   // valid curNavType
00102 
00103 #define HHWIN_BUTTON_EXPAND         (1 << 1)    // Expand/contract button
00104 #define HHWIN_BUTTON_BACK           (1 << 2)    // Back button
00105 #define HHWIN_BUTTON_FORWARD        (1 << 3)    // Forward button
00106 #define HHWIN_BUTTON_STOP           (1 << 4)    // Stop button
00107 #define HHWIN_BUTTON_REFRESH        (1 << 5)    // Refresh button
00108 #define HHWIN_BUTTON_HOME           (1 << 6)    // Home button
00109 #define HHWIN_BUTTON_BROWSE_FWD     (1 << 7)    // not implemented
00110 #define HHWIN_BUTTON_BROWSE_BCK     (1 << 8)    // not implemented
00111 #define HHWIN_BUTTON_NOTES          (1 << 9)    // not implemented
00112 #define HHWIN_BUTTON_CONTENTS       (1 << 10)   // not implemented
00113 #define HHWIN_BUTTON_SYNC           (1 << 11)   // Sync button
00114 #define HHWIN_BUTTON_OPTIONS        (1 << 12)   // Options button
00115 #define HHWIN_BUTTON_PRINT          (1 << 13)   // Print button
00116 #define HHWIN_BUTTON_INDEX          (1 << 14)   // not implemented
00117 #define HHWIN_BUTTON_SEARCH         (1 << 15)   // not implemented
00118 #define HHWIN_BUTTON_HISTORY        (1 << 16)   // not implemented
00119 #define HHWIN_BUTTON_FAVORITES      (1 << 17)   // not implemented
00120 #define HHWIN_BUTTON_JUMP1          (1 << 18)
00121 #define HHWIN_BUTTON_JUMP2          (1 << 19)
00122 #define HHWIN_BUTTON_ZOOM           (1 << 20)
00123 #define HHWIN_BUTTON_TOC_NEXT       (1 << 21)
00124 #define HHWIN_BUTTON_TOC_PREV       (1 << 22)
00125 
00126 #define HHWIN_DEF_BUTTONS           \
00127             (HHWIN_BUTTON_EXPAND |  \
00128              HHWIN_BUTTON_BACK |    \
00129              HHWIN_BUTTON_OPTIONS | \
00130              HHWIN_BUTTON_PRINT)
00131 
00132 // Button IDs
00133 
00134 #define IDTB_EXPAND             200
00135 #define IDTB_CONTRACT           201
00136 #define IDTB_STOP               202
00137 #define IDTB_REFRESH            203
00138 #define IDTB_BACK               204
00139 #define IDTB_HOME               205
00140 #define IDTB_SYNC               206
00141 #define IDTB_PRINT              207
00142 #define IDTB_OPTIONS            208
00143 #define IDTB_FORWARD            209
00144 #define IDTB_NOTES              210 // not implemented
00145 #define IDTB_BROWSE_FWD         211
00146 #define IDTB_BROWSE_BACK        212
00147 #define IDTB_CONTENTS           213 // not implemented
00148 #define IDTB_INDEX              214 // not implemented
00149 #define IDTB_SEARCH             215 // not implemented
00150 #define IDTB_HISTORY            216 // not implemented
00151 #define IDTB_FAVORITES          217 // not implemented
00152 #define IDTB_JUMP1              218
00153 #define IDTB_JUMP2              219
00154 #define IDTB_CUSTOMIZE          221
00155 #define IDTB_ZOOM               222
00156 #define IDTB_TOC_NEXT           223
00157 #define IDTB_TOC_PREV           224
00158 
00159 // Notification codes
00160 
00161 #define HHN_FIRST       (0U-860U)
00162 #define HHN_LAST        (0U-879U)
00163 
00164 #define HHN_NAVCOMPLETE   (HHN_FIRST-0)
00165 #define HHN_TRACK         (HHN_FIRST-1)
00166 #define HHN_WINDOW_CREATE (HHN_FIRST-2)
00167 
00168 typedef struct tagHHN_NOTIFY
00169 {
00170     NMHDR   hdr;
00171     PCSTR   pszUrl; // Multi-byte, null-terminated string
00172 } HHN_NOTIFY;
00173 
00174 typedef struct tagHH_POPUP
00175 {
00176     int       cbStruct;      // sizeof this structure
00177     HINSTANCE hinst;         // instance handle for string resource
00178     UINT      idString;      // string resource id, or text id if pszFile is specified in HtmlHelp call
00179     LPCTSTR   pszText;       // used if idString is zero
00180     POINT     pt;            // top center of popup window
00181     COLORREF  clrForeground; // use -1 for default
00182     COLORREF  clrBackground; // use -1 for default
00183     RECT      rcMargins;     // amount of space between edges of window and text, -1 for each member to ignore
00184     LPCTSTR   pszFont;       // facename, point size, char set, BOLD ITALIC UNDERLINE
00185 } HH_POPUP;
00186 
00187 typedef struct tagHH_AKLINK
00188 {
00189     int       cbStruct;     // sizeof this structure
00190     BOOL      fReserved;    // must be FALSE (really!)
00191     LPCTSTR   pszKeywords;  // semi-colon separated keywords
00192     LPCTSTR   pszUrl;       // URL to jump to if no keywords found (may be NULL)
00193     LPCTSTR   pszMsgText;   // Message text to display in MessageBox if pszUrl is NULL and no keyword match
00194     LPCTSTR   pszMsgTitle;  // Message text to display in MessageBox if pszUrl is NULL and no keyword match
00195     LPCTSTR   pszWindow;    // Window to display URL in
00196     BOOL      fIndexOnFail; // Displays index if keyword lookup fails.
00197 } HH_AKLINK;
00198 
00199 enum {
00200     HHWIN_NAVTYPE_TOC,
00201     HHWIN_NAVTYPE_INDEX,
00202     HHWIN_NAVTYPE_SEARCH,
00203     HHWIN_NAVTYPE_FAVORITES,
00204     HHWIN_NAVTYPE_HISTORY,   // not implemented
00205     HHWIN_NAVTYPE_AUTHOR,
00206     HHWIN_NAVTYPE_CUSTOM_FIRST = 11
00207 };
00208 
00209 enum {
00210     IT_INCLUSIVE,
00211     IT_EXCLUSIVE,
00212     IT_HIDDEN,
00213 };
00214 
00215 typedef struct tagHH_ENUM_IT
00216 {
00217     int       cbStruct;          // size of this structure
00218     int       iType;             // the type of the information type ie. Inclusive, Exclusive, or Hidden
00219     LPCSTR    pszCatName;        // Set to the name of the Category to enumerate the info types in a category; else NULL
00220     LPCSTR    pszITName;         // volitile pointer to the name of the infotype. Allocated by call. Caller responsible for freeing
00221     LPCSTR    pszITDescription;  // volitile pointer to the description of the infotype.
00222 } HH_ENUM_IT, *PHH_ENUM_IT;
00223 
00224 typedef struct tagHH_ENUM_CAT
00225 {
00226     int       cbStruct;          // size of this structure
00227     LPCSTR    pszCatName;        // volitile pointer to the category name
00228     LPCSTR    pszCatDescription; // volitile pointer to the category description
00229 } HH_ENUM_CAT, *PHH_ENUM_CAT;
00230 
00231 typedef struct tagHH_SET_INFOTYPE
00232 {
00233     int       cbStruct;          // the size of this structure
00234     LPCSTR    pszCatName;        // the name of the category, if any, the InfoType is a member of.
00235     LPCSTR    pszInfoTypeName;   // the name of the info type to add to the filter
00236 } HH_SET_INFOTYPE, *PHH_SET_INFOTYPE;
00237 
00238 typedef DWORD HH_INFOTYPE;
00239 typedef HH_INFOTYPE* PHH_INFOTYPE;
00240 
00241 enum {
00242     HHWIN_NAVTAB_TOP,
00243     HHWIN_NAVTAB_LEFT,
00244     HHWIN_NAVTAB_BOTTOM,
00245 };
00246 
00247 #define HH_MAX_TABS 19  // maximum number of tabs
00248 
00249 enum {
00250     HH_TAB_CONTENTS,
00251     HH_TAB_INDEX,
00252     HH_TAB_SEARCH,
00253     HH_TAB_FAVORITES,
00254     HH_TAB_HISTORY,
00255     HH_TAB_AUTHOR,
00256 
00257     HH_TAB_CUSTOM_FIRST = 11,
00258     HH_TAB_CUSTOM_LAST = HH_MAX_TABS
00259 };
00260 
00261 #define HH_MAX_TABS_CUSTOM (HH_TAB_CUSTOM_LAST - HH_TAB_CUSTOM_FIRST + 1)
00262 
00263 // HH_DISPLAY_SEARCH Command Related Structures and Constants
00264 
00265 #define HH_FTS_DEFAULT_PROXIMITY (-1)
00266 
00267 typedef struct tagHH_FTS_QUERY
00268 {
00269     int cbStruct;            // Sizeof structure in bytes.
00270     BOOL fUniCodeStrings;    // TRUE if all strings are unicode.
00271     LPCTSTR pszSearchQuery