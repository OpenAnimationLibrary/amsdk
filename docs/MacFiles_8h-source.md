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

# MacFiles.h

[Go to the documentation of this file.](MacFiles_8h.md)

<div class="fragment">

``` fragment
00001 /************************************************************************
00002 * @doc
00003 * $Workfile: MacFiles.h $
00004 * Copyright (c) 1995 - 1997 CoreTek, Inc.
00005 * This work is protected by United States and international copyright laws 
00006 * and contains certain trade secret information.  All use of this work is  
00007 * governed by the terms of agreements between CoreTek Corporation and its     
00008 * licensees or potential licensees.  Disclosure or disassembly of the      
00009 * contents of embodied programs or algorithms is prohibited.  
00010 * All rights reserved.
00011 * Description: 
00012 * $Revision: 8 $ $Author: Yury $ $Date: 6/23/97 5:22p $
00013 ************************************************************************/
00014 // Search flags
00015 #ifndef __OS9FILES_H
00016 #define __OS9FILES_H
00017 
00018 #include "Exports.h"
00019 
00020 #define SF_MATAC  0x0001         // mask AND (type AND creator)
00021 #define SF_MATOC  0x0002         // mask AND (type OR creator)
00022 #define SF_MOTAC  0x0004         // mask OR  (type AND creator)
00023 #define SF_MOTOC  0x0008         // mask OR  (type OR creator)
00024 #define SF_SHOWDIR   0x1000         // return directories
00025 
00026 #ifdef _OS9
00027 #ifndef _XMAC_H
00028 #include <xMac.h>
00029 #endif
00030 
00031 //\/\/\/\/\/\ MacData
00032 //Additional attribute to specify volume attributes
00033 //@msg Volume Attributes | Some additional definitions to specify the volume attributes.<nl>
00034 //<f Value><tab><tab><tab><tab><tab><tab><f Meaning><nl>
00035 //FILE_ATTRIBUTE_VOLUME       <tab>This is a volume not a file or folder<nl>
00036 //VOLUME_ATTRIBUTE_NETWORK    <tab>Network volume <nl>
00037 //VOLUME_ATTRIBUTE_EJECTABLE  <tab><tab>Ejectable volume (CD-ROM or floppy) <nl>
00038 //VOLUME_ATTRIBUTE_LOCKED     <tab>Volume is hardware locked.<nl>
00039 //VOLUME_ATTRIBUTE_FLOPPY     <tab>Volume is a floppy  <nl>
00040 //VOLUME_ATTRIBUTE_CD         <tab>Volume is a CD-ROM <nl>
00041 //VOLUME_ATTRIBUTE_EJECTED    <tab>Volume is ejected.<nl>
00042 //@xref <f MacFindFirst>, <c xFileData>, <f MacEnumVolumes>
00043 #define FILE_ATTRIBUTE_VOLUME       0x00001000  
00044 #define VOLUME_ATTRIBUTE_NETWORK    0x00010000
00045 #define VOLUME_ATTRIBUTE_EJECTABLE     0x00020000
00046 #define VOLUME_ATTRIBUTE_LOCKED        0x00040000
00047 #define VOLUME_ATTRIBUTE_FLOPPY        0x00080000
00048 #define VOLUME_ATTRIBUTE_CD            0x00100000
00049 #define VOLUME_ATTRIBUTE_EJECTED    0x00200000
00050    
00051 //@class    Helper class to contain the file and volume information.
00052 //@base     public   | CObject.
00053 class FILEIOEXPORT xFileData : public CObject
00054 {
00055 public:
00056    xFileData(WIN32_FIND_DATA *fd);
00057    xFileData();
00058    void  operator=(const xFileData& srcFD){
00059       this->m_Attrib  = srcFD.m_Attrib;
00060       this->m_Type    = srcFD.m_Type;
00061       this->m_Sig    = srcFD.m_Sig;
00062       this->m_Size   = srcFD.m_Size;
00063       this->m_Name    = srcFD.m_Name;
00064       this->m_modTime = srcFD.m_modTime;
00065       this->m_crTime  = srcFD.m_crTime;
00066       this->m_vRefNum = srcFD.m_vRefNum;
00067    }
00068    //@cmember  File or Volume attributes. See additional volume attributes.
00069    DWORD m_Attrib;
00070    //@cmember  File Type
00071    DWORD m_Type;
00072    //@cmember  Signature of file creator
00073    DWORD m_Sig;
00074    //@cmember  Size of the file in bytes
00075    DWORD m_Size;
00076    //@cmember  File name.
00077    CString  m_Name;
00078    //@cmember  Last modification time
00079    time_t   m_modTime;
00080    //@cmember  Creation time
00081    time_t   m_crTime;
00082    //@cmember  Volume reference number the file resides on
00083    short m_vRefNum;
00084 };
00085 
00086 #define    SysWDProcID 0x4552494B    
00087 #define    BootDrive   0x210
00088 // Address of Low-Mem global that contains system map reference number
00089 #define    SysMap      0xA58                     
00090 #define    FSFCBLen    0x3F6
00091 #define    HFSIsRunning ((*(short int *)(FSFCBLen)) > 0)
00092 
00093 //\/\/\/\/\/\ MacFiles Helper functions
00094 short   FILEIOEXPORT MacVolumeRefNum      (LPCTSTR volume);
00095 CString  FILEIOEXPORT MacPathName         (short vRefNum, long dirID);
00096 long  FILEIOEXPORT MacDirID            (LPCTSTR path, short vRefNum);
00097 short FILEIOEXPORT MacFileID           (LPCTSTR path, short vRefNum);
00098 BOOL  FILEIOEXPORT MacIsNetVolume         (LPCTSTR volume);
00099 BOOL  FILEIOEXPORT MacIsEjectable         (LPCTSTR volume);
00100 BOOL  FILEIOEXPORT MacIsLocked         (LPCTSTR volume);
00101 BOOL  FILEIOEXPORT MacIsCDROM          (LPCTSTR volume);
00102 void  FILEIOEXPORT MacGetVolumeData    (xFileData *volData);
00103 void  FILEIOEXPORT MacEjectVolume         (LPCTSTR volume);
00104 
00105 void  FILEIOEXPORT MacSetFileAttrib    (LPCSTR fullPath,DWORD creator, DWORD type);
00106 
00107 short FILEIOEXPORT MacEnumVolumes         (xFileData **dataArray);
00108 CString FILEIOEXPORT MacGetBootVolume     (void);
00109 CString FILEIOEXPORT MacGetPrefFolder     (void);
00110 void  FILEIOEXPORT StripTrailingColon     (LPCTSTR name);
00111 void  FILEIOEXPORT StripLeadingColon      (LPCTSTR name);
00112 void  FILEIOEXPORT AddTrailingColon    (LPCTSTR name);
00113 void  FILEIOEXPORT AddLeadingColon     (LPCTSTR name);
00114 
00115 
00116 //\/\/\/\/\/\ Path
00117 #undef   _MAX_PATH
00118 #define _MAX_PATH   260       // max. length of full pathname 
00119 #define _MAX_DRIVE  32        // max. length of volume name component
00120 #undef   _MAX_DIR
00121 #define _MAX_DIR    256       // max. length of path component */
00122 #undef   _MAX_FNAME
00123 #define _MAX_FNAME  256       // max. length of file name component */
00124 #define _MAX_EXT    _MAX_FNAME  // max. length of extension component assume the same as filename
00125 #define _MAX_TEMP_FNAME    32 // max length of the temp filename.
00126 void FILEIOEXPORT _splitpath( const char *path, char *volume, char *folder, char *fname, char *ext );
00127 
00129 //\/\/\/\/\/\ FindFile 
00130 // The difference between 1/1/1904 and 1/1/1970 (Mac and Win base for the time_t).
00131 #define TIME_ADJUSTMENT       0x7C25B080     //0x7C102800
00132 
00133 //@struct MFF_DATA | Internal structure used to contain the information about current search. 
00134 //      The structure used internally by <f MacFindFirst>, <c MacFindNext> functions. The
00135 typedef struct S_FindFileData {
00136    short vRefNum;       //@field Volume ID for this search
00137    long  dirID;            //@field directory ID
00138    short index;            //@field current file index
00139    DWORD type;          //@field file type
00140    DWORD creator;       //@field file creator
00141    WORD  flags;            //@field search flags
00142    char  mask[_MAX_FNAME]; //@field search mask
00143    char  path[_MAX_DRIVE+_MAX_DIR+_MAX_PATH];   //@field base dir
00144 } MFF_DATA;
00145 
00146 HANDLE FILEIOEXPORT cpxFindFirst (LPCTSTR pName,DWORD type, DWORD creator, WORD flags, WIN32_FIND_DATA *pFD);
00147 BOOL   FILEIOEXPORT cpxFindNext     (HANDLE fH,WIN32_FIND_DATA *pFD);
00148 BOOL   FILEIOEXPORT cpxFindClose (HANDLE fH);
00149 short  FILEIOEXPORT cpxFileCount (LPCTSTR path);
00150 
00151 BOOL   FILEIOEXPORT CheckPattern (char *s, char *p);
00152 
00153 
00154 DWORD FILEIOEXPORT cpxGetModuleFileName   (HMODULE hModule,LPTSTR lpFilename,DWORD nSize);
00155 CString FILEIOEXPORT cpxGetRealFileName      (LPCSTR lpPathName);
00156 UINT  FILEIOEXPORT cpxGetSystemDirectory  (LPTSTR path, UINT uSize);
00157 BOOL  FILEIOEXPORT cpxGetDiskFreeSpace (LPCTSTR lpVolume,LPDWORD lpSectorsPerCluster,LPDWORD lpBytesPerSector,LPDWORD lpNumberOfFreeClusters,LPDWORD lpTotalNumberOfClusters);
00158 DWORD FILEIOEXPORT cpxGetFileAttributes   (LPCTSTR pName,DWORD *type, DWORD *creator);
00159 
00160 // for compatability with v1.0
00161 #define   MacGetModuleFileName   cpxGetModuleFileName
00162 #define   MacFindFirst        cpxFindFirst        
00163 #define  MacFindNext       cpxFindNext         
00164 #define  MacFindClose         cpxFindClose        
00165 #define  MacGetModuleFileName cpxGetModuleFileName
00166 #define  MacFileCount         cpxFileCount        
00167 
00168 
00169 BOOL  FILEIOEXPORT cpxLaunchBrowserToURL (LPCSTR progname,LPCSTR url );
00170 
00171 //@msg  System Specific File System Punctuation| Some additional definitions <nl>
00172 //PATH_SEPARATOR     <tab>Path dividers - ':' on Mac and '\\' on Win32 <nl>
00173 //PATH_SEPARATOR_STR <tab>Path dividers - ":" on Mac and "\\" on Win32 <nl>
00174 #define PATH_SEPARATOR     ':'
00175 #define PATH_SEPARATOR_STR ":"
00176 
00177 #else // Win32 Version
00178 
00179 #define PATH_SEPARATOR     '\\'
00180 #define PATH_SEPARATOR_STR "\\"
00181 
00182 //\/\/\/\/\/\ FindFile 
00183 #define MacFindFirst(pName,type,creator,flags,pFD) FindFirstFile(pName,pFD)
00184 #define MacFindNext     FindNextFile
00185 #define MacFindClose FindClose
00186 #define MacGetModuleFileName(hModule,path,ptSize)  GetModuleFileName(hModule,path,ptSize)
00187 #define MacFileCount(path)
00188 
00189 #define cpxFindFirst(pName,type,creator,flags,pFD) FindFirstFile(pName,pFD)
00190 #define cpxFindNext     FindNextFile
00191 #define cpxFindClose FindClose
00192 #define cpxGetModuleFileName(hModule,path,ptSize)  GetModuleFileName(hModule,path,ptSize)
00193 #define cpxFileCount(path)
00194 #define cpxGetRealFileName
00195 #define cpxGetSystemDirectory(path,uSize)       GetWindowsDirectory(path,uSize)
00196 #define  cpxGetDiskFreeSpace                    GetDiskFreeSpace 
00197 #define cpxGetFileAttributes(pName,type,creator)   GetFileAttributes(pName)
00198 
00199 #endif   // _OS9
00200 
00201 #define  ALL_FILES_FILTER     "*.*|****"
00202 
00203 // Both versions
00204 CString FILEIOEXPORT cpxGetTempFile       (LPCTSTR lpPathName,LPCTSTR lpPrefixString, UINT uUnique);
00205 BOOL  FILEIOEXPORT cpxExec          (BOOL wait, LPCSTR progname, char **argv);
00206 BOOL  FILEIOEXPORT cpxVolumeCanDenyOpen   (LPCSTR volume);
00207 BOOL  FILEIOEXPORT cpxCanLockFiles     (LPCSTR volume);
00208 
00209 // for compatability with v1.0
00210 #define   MacGetTempFile      cpxGetTempFile
00211 
00212 void  FILEIOEXPORT StripExtension      (CString &fName);
00213 void  FILEIOEXPORT AddPathSeparator (CString &fName);
00214 
00215 #endif   //__OS9FILES_H
```

</div>

------------------------------------------------------------------------

<span class="small">This A:M SDK v12.0 documentation is maintained by Hash Inc. Please address any comments concerning this documentation to [AMReports](http://www.hash.com/reports). If you have any information, knowledge, or documentation to share with the A:M developer community, please post them on the [Hash SDK forum](http://www.hash.com/forums/index.php?showforum=11).</span>

Generated on Thu Oct 27 11:46:44 2005 with [<span class="image placeholder" original-image-src="doxygen.png" original-image-title="" height="45" width="100" align="middle" border="0">doxygen</span>](http://www.doxygen.org/index.html) 1.4.5 written by [Dimitri van Heesch](mailto:dimitri@stack.nl), © 1997-2001
