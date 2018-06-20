//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//           ^           **   **   **** ***** *    ****     ^      Take me to
//          (_)            * *     *      *   *    *       (_)    / your
//     ^                    *      **     *   *    **            ^  leader...
//    (_)       ^          * *     *      *   *    *            (_)
//             (_)       **   **   *    ***** **** ****
//
//                    Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1994-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
// THE AUTHORS MAKE NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
// OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT.  THE AUTHORS
// PROVIDE THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
// LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
// OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
//                        http://www.mythos-engine.org/
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
// Created by Chuck Walbourn
// Ported to Windows by Dan Higdon
//
// xfiofinf.c
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <assert.h>
#include <xfio.h>
#include <Strsafe.h>

#if _WIN32_WINNT >= 0x600
#include <Psapi.h>

#if PSAPI_VERSION >= 2
#define GetMappedFileName K32GetMappedFileName
#endif /* PSAPI_VERSION */
#endif /* _WIN32_WINNT */

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// word xf_getattr (const char *name);                                      �
//                                                                          �
// Get attribute bits for a file.                                           �
//                                                                          �
// Returns -1 on error, attribute bits otherwise.                           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
word xf_getattr (const char *name)
{
    DWORD attrs = GetFileAttributes (name);

    if (attrs == -1)
        xf_last_error = GetLastError();

    return (word)attrs;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// FILETIME xf_getfdate(HANDLE fhandle);                                    �
//                                                                          �
// Gets the file's modification date.                                       �
//                                                                          �
// Returns date, or 0 if error.                                             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
word xf_getfdate (HANDLE fhandle)
{
    BY_HANDLE_FILE_INFORMATION  finfo;

    if (GetFileInformationByHandle (fhandle, &finfo))
    {
        WORD    wdate, wtime;

        if (FileTimeToDosDateTime (&finfo.ftLastWriteTime, &wdate, &wtime))
            return wdate;
    }

    return 0;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// word xf_getftime(int fhandle);                                           �
//                                                                          �
// Gets the file's modification time.                                       �
//                                                                          �
// Returns time, or 0 if error.                                             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
word xf_getftime (HANDLE fhandle)
{
    BY_HANDLE_FILE_INFORMATION  finfo;

    if (GetFileInformationByHandle (fhandle, &finfo))
    {
        WORD    wdate, wtime;

        if (FileTimeToDosDateTime (&finfo.ftLastWriteTime, &wdate, &wtime))
            return wtime;
    }

    xf_last_error = GetLastError ();
    return 0;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// xf_getsize                                                               �
//                                                                          �
// Returns size of the file in bytes or -1 if error.                        �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
ulong xf_getsize (HANDLE fhandle)
{
    DWORD res;

    res = GetFileSize (fhandle, NULL);

    if (res == (DWORD)-1)
        xf_last_error = GetLastError();

    return res;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// word xf_setattr(const char *name, word attr);                            �
//                                                                          �
// Set attribute bits for a file.                                           �
//                                                                          �
// Returns -1 on error, set attribute bits otherwise.                       �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
word xf_setattr (const char *name, word attr)
{
    // set and validate attributes
    if (!SetFileAttributes (name, attr) ||
        (word)GetFileAttributes (name) != attr)
    {
        xf_last_error = GetLastError();
        return (word)-1;
    }

    return attr;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// xf_setsize                                                               �
//                                                                          �
// Sets the size of the file to the given length (either extending or       �
// truncating).  Returns the new size or -1 if error.                       �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
ulong xf_setsize (HANDLE fhandle, ulong size)
{
    if (SetFilePointer (fhandle, size, NULL, FILE_BEGIN) == size)
    {
        if (SetEndOfFile (fhandle))
            return size;
    }

    return (ulong)-1;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳朕
// const char* xf_getname(HANDLE fhandle, char* pReturn, size_t pReturnSize);  �
//                                                                             �
// Get the file name of an handle.                                             �
//                                                                             �
// Returns pReturn or NULL if error                                            �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳潰

const char* xf_getname(HANDLE fhandle, char* pReturn, size_t pReturnSize)
{
#if _WIN32_WINNT < 0x600
	BOOL bSuccess = FALSE;
	HANDLE hFileMap = 0;
	void* pMem = 0;

	if (fhandle == NULL)
		return NULL;

	if (pReturn == NULL || pReturnSize < 1)
		return NULL;

	if (xf_getsize(fhandle) < 1)
		return NULL;
	
	hFileMap = CreateFileMapping(fhandle, NULL, PAGE_READONLY, 0, 1, NULL);
	if (hFileMap)
	{
		pMem = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 1);
		if (pMem)
		{
			if (GetMappedFileName(GetCurrentProcess(), pMem, pReturn, pReturnSize))
			{
				TCHAR szTemp[512];
				szTemp[0] = '\0';

				if (GetLogicalDriveStrings(511, szTemp))
				{
					TCHAR szName[MAX_PATH];
					TCHAR szDrive[3] = TEXT(" :");
					BOOL bFound = FALSE;
					TCHAR* p = szTemp;

					do
					{
						*szDrive = *p;
						if (QueryDosDevice(szDrive, szName, MAX_PATH))
						{
							size_t uNameLen = strlen(szName);
							if (uNameLen < MAX_PATH)
							{
								bFound = _strnicmp(pReturn, szName, uNameLen) == 0
										&& *(pReturn + uNameLen) == '\\';

								if (bFound)
								{
									TCHAR szTempFile[MAX_PATH];

									StringCchPrintf(szTempFile, MAX_PATH, TEXT("%s%s"), szDrive, pReturn+uNameLen);
									StringCchCopyN(pReturn, MAX_PATH+1, szTempFile, strlen(szTempFile));
								}
							}
						}

						while (*p++);
					} while (!bFound && *p);
				}
			}

			bSuccess = TRUE;

			UnmapViewOfFile(pMem);
		}

		CloseHandle(hFileMap);
	}
	
	if (bSuccess)
		return pReturn;

	xf_last_error = GetLastError();

	return NULL;
#else
	size_t ps = 0, i = 0;

	// Windows Vista or later code
	if (GetFinalPathNameByHandle(fhandle, pReturn, pReturnSize, FILE_NAME_NORMALIZED) == 0)
	{
		xf_last_error = GetLastError();
		return NULL;
	}

	return pReturn;
#endif
}

//葦� End of module - xfiofinf.c 憶�
