//Dan  8/18/2004  \DanLP110\Include\Files.h
#pragma once

#include "Exports.h"

class String;

FILEIOEXPORT bool Remove(const String &filename);
FILEIOEXPORT bool RemoveDir(const String &dir);
FILEIOEXPORT bool Rename(const String &src, const String &dst);
FILEIOEXPORT bool DirExists(const String &pathname);
FILEIOEXPORT bool FileExists(const String &filename);
FILEIOEXPORT bool MakeDirPath(const String &name);
FILEIOEXPORT bool CanWriteDirPath(const String &name);
FILEIOEXPORT bool CanWriteToFile(const String &name);
FILEIOEXPORT bool IsReadOnly(const String &filename);
FILEIOEXPORT std::uintmax_t GetFileSize(const String &filename);
FILEIOEXPORT FILETIME GetFileModifiedTime(const String &filename);
FILEIOEXPORT bool IsFileModified(const String &filename, FILETIME reftime);
FILEIOEXPORT bool HashCopyFile(const String &srcpathname, const String &dstpathname);
FILEIOEXPORT int LargeFileSeek(FILE *m_pStream, LONGLONG offset, int origin) noexcept;
#ifdef _DIAGNOSTIC
FILEIOEXPORT void TestDiag(const String &p_pfad);
#endif

FILEIOEXPORT bool SVNIsVersioned(const String &filename);
FILEIOEXPORT String FindSVNDir(const String &path);
FILEIOEXPORT UINT SVNGetHeadRevNum(String url);
FILEIOEXPORT bool SVNCheckURLCase(const String &path);
FILEIOEXPORT DWORD FTPSendFile(const String &url, const String &filename, const String &remotefolder, const String &username, const String &password);

#ifdef _WILL
FILEIOEXPORT String SVNGetRepoCache(String filename);
FILEIOEXPORT void ClearSVNCacheList();
#endif
