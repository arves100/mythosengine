//���������������������������������������������������������������������������
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
//���������������������������������������������������������������������������
//
// THE AUTHORS MAKE NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
// OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT.  THE AUTHORS
// PROVIDE THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
// LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
// OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//���������������������������������������������������������������������������
//
//                        http://www.mythos-engine.org/
//
//���������������������������������������������������������������������������
//
// Created by Chuck Walbourn
// Ported to Windows by Dan Higdon
//
// xfiobase.c
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "xfio.h"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// HANDLE xf_open(const char *fname, dword flags);                          �
//                                                                          �
// Opens a DOS file for use by the other xf_ low-level routines.  Flags     �
// determines the type of file opened and uses defines in the               �
//                                                                          �
//       name - Pointer to path/filename for the file to open.              �
//                                                                          �
//       flags -                                                            �
//               XF_OPEN_READ     - Read file mode                          �
//               XF_OPEN_WRITE    - Write file mode                         �
//               XF_OPEN_APPEND   - Append to file if one exists (write)    �
//               XF_OPEN_CREATE   - Create file if it doesn't exist         �
//               XF_OPEN_EXCLUSIVE- Fails if creating file already existing �
//               XF_OPEN_READONLY - File attributes                         �
//               XF_OPEN_HIDDEN        (used for create as file,            �
//               XF_OPEN_SYSTEM         used for open as mask)              �
//               XF_OPEN_ARCHIVE                                            �
//               XF_OPEN_SHAREABLE                                          �
//               XF_OPEN_DENYALL  - Share mode                              �
//               XF_OPEN_DENYWRITE                                          �
//               XF_OPEN_DENYREAD                                           �
//               XF_OPEN_DENYNONE                                           �
//                                                                          �
//               XF_OPEN_PRIVATE  - Inheritance (open only)                 �
//                                                                          �
// Returns INVALID_HANDLE_VALUE if failure, file handle otherwise.          �
//���������������������������������������������������������������������������
HANDLE xf_open (const char *fname, dword flags)
{
    HANDLE  res;
    DWORD   dwAccess;
    DWORD   dwShare;
    DWORD   dwCreate;
    DWORD   dwAttrib;

    // Build the dwAccess parameter
    dwAccess = 0;
    if (flags & XF_OPEN_READ)
        dwAccess |= GENERIC_READ;
    if (flags & (XF_OPEN_WRITE | XF_OPEN_CREATE | XF_OPEN_APPEND))
        dwAccess |= GENERIC_WRITE;

    // Build the Share parameter
    dwShare = 0;
    switch (flags & 0xf0000000)
    {
    case XF_OPEN_DENYWRITE:
        dwShare = FILE_SHARE_READ;
        break;

    case XF_OPEN_DENYREAD:
        dwShare = FILE_SHARE_WRITE;
        break;

    case XF_OPEN_DENYNONE:
        dwShare = FILE_SHARE_READ | FILE_SHARE_WRITE;
        break;

    default:
        dwShare = 0;    // No sharing by default
        break;
    }

    // Build the dwCreate parameter
    if ((flags & XF_OPEN_EXCLUSIVE) && (flags & XF_OPEN_CREATE))
        dwCreate = CREATE_NEW;
    else if (flags & XF_OPEN_CREATE)
        dwCreate = CREATE_ALWAYS;
    else
        dwCreate = OPEN_EXISTING;

    // Build the attribute parameter
    dwAttrib = FILE_ATTRIBUTE_NORMAL;
    if (flags & XF_OPEN_READONLY)
        dwAttrib |= FILE_ATTRIBUTE_READONLY;
    if (flags & XF_OPEN_HIDDEN)
        dwAttrib |= FILE_ATTRIBUTE_HIDDEN;
    if (flags & XF_OPEN_SYSTEM)
        dwAttrib |= FILE_ATTRIBUTE_SYSTEM;
    if (flags & XF_OPEN_ARCHIVE)
        dwAttrib |= FILE_ATTRIBUTE_ARCHIVE;
    if (flags & XF_OPEN_KILL)
        dwAttrib |= FILE_FLAG_DELETE_ON_CLOSE;
    if (flags & XF_OPEN_RANDOM_ACCESS)
        dwAttrib |= FILE_FLAG_RANDOM_ACCESS;
    if (flags & XF_OPEN_SEQUENTIAL_ACCESS)
        dwAttrib |= FILE_FLAG_SEQUENTIAL_SCAN;

    res = CreateFile (fname, dwAccess, dwShare, NULL, dwCreate, dwAttrib, NULL);

    if (res == INVALID_HANDLE_VALUE)
        xf_last_error = GetLastError ();

    // If we're in append mode, then put us at the end of the file
    if (flags & XF_OPEN_APPEND)
        xf_seek (res, 2, 0);

    return res;
}


//�������������������������������������������������������������������������Ŀ
// HANLDE xf_opentmp(const char *fname, dword flags);                       �
//                                                                          �
// Opens a DOS file, generating a temporary filename.  Tempfile assumes that�
// CREATE and WRITE are implied.                                            �
//                                                                          �
//       name - Pointer to path.                                            �
//                                                                          �
//       flags -                                                            �
//               same as xf_open                                            �
//                                                                          �
// Returns INVALID_HANDLE_VALUE if failure, file handle otherwise.          �
//���������������������������������������������������������������������������
HANDLE xf_opentmp (const char *fname, dword flags)
{
    TCHAR   szTmpName[MAX_PATH];
    TCHAR   szTmpPath[MAX_PATH];

    if (GetTempPath (sizeof (szTmpPath), szTmpPath) != 0 &&
        GetTempFileName (szTmpPath, fname, 0, szTmpName) != 0)
        return xf_open (szTmpName, flags | XF_OPEN_WRITE & ~XF_OPEN_CREATE);

    xf_last_error = GetLastError ();
    return INVALID_HANDLE_VALUE;
}


//�������������������������������������������������������������������������Ŀ
// ulong xf_read(int fhandle, void *ptr, ulong size);                       �
//                                                                          �
// Read data from file into buffer.                                         �
//                                                                          �
// Returns number of bytes read, 0 on eof, and -1 on error.                 �
//���������������������������������������������������������������������������
ulong xf_read (HANDLE fhandle, void *ptr, ulong size)
{
    ulong res;

    if (ReadFile (fhandle, ptr, size, &res, NULL))
    {
        if (res == 0)
            xf_last_error = XF_ERR_EOF;
        return res;
    }

    xf_last_error = GetLastError();
    return (ulong)-1;
}


//�������������������������������������������������������������������������Ŀ
// ulong xf_write(int fhandle, const void *ptr, ulong size);                �
//                                                                          �
// Write data from a buffer into a file.                                    �
//���������������������������������������������������������������������������
ulong xf_write (HANDLE fhandle, const void *ptr, ulong size)
{
    DWORD res;

    if (WriteFile (fhandle, ptr, size, &res, NULL))
        return res;

    xf_last_error = GetLastError ();
    return (ulong)-1;
}


//�������������������������������������������������������������������������Ŀ
// ulong xf_seek(int fhandle, int mode, long offset);                       �
//                                                                          �
// Seeks to a given position in the file, with mode set to 0 for start,     �
// 1 for current, 2 for eof relative movement.                              �
//                                                                          �
// Returns -1 if error, or offset from start of file.                       �
//���������������������������������������������������������������������������
ulong xf_seek (HANDLE fhandle, int mode, long offset)
{
static const int translate_seekmode[] = { FILE_BEGIN, FILE_CURRENT, FILE_END };
    DWORD   res;

    res = SetFilePointer (fhandle, offset, NULL, translate_seekmode[mode & 3]);

    if (res == -1)
        xf_last_error = GetLastError();

    return res;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_flush(int fhandle);                                    �
//                                                                          �
// Flushes a file handle.                                                   �
//                                                                          �
// Returns 0 or error                                                       �
//���������������������������������������������������������������������������
xf_error_codes xf_flush (HANDLE fhandle)
{
    if (FlushFileBuffers (fhandle))
        return 0;

    xf_last_error = GetLastError ();
    return xf_last_error;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_close(HANDLE fhandle);                                 �
//                                                                          �
// Closes a file handle.                                                    �
//                                                                          �
// Returns 0 or XF_ERR_INVALIDHANDLE                                        �
//���������������������������������������������������������������������������
xf_error_codes xf_close (HANDLE fhandle)
{
    if (CloseHandle (fhandle))
        return 0;

    return XF_ERR_INVALIDHANDLE;
}

//��� End of module - xfiobase.c ���

