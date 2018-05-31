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
// xfiofinf.c
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <assert.h>
#include <xfio.h>

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// word xf_getattr (const char *name);                                      �
//                                                                          �
// Get attribute bits for a file.                                           �
//                                                                          �
// Returns -1 on error, attribute bits otherwise.                           �
//���������������������������������������������������������������������������
word xf_getattr (const char *name)
{
    DWORD attrs = GetFileAttributes (name);

    if (attrs == -1)
        xf_last_error = GetLastError();

    return (word)attrs;
}


//�������������������������������������������������������������������������Ŀ
// FILETIME xf_getfdate(HANDLE fhandle);                                    �
//                                                                          �
// Gets the file's modification date.                                       �
//                                                                          �
// Returns date, or 0 if error.                                             �
//���������������������������������������������������������������������������
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


//�������������������������������������������������������������������������Ŀ
// word xf_getftime(int fhandle);                                           �
//                                                                          �
// Gets the file's modification time.                                       �
//                                                                          �
// Returns time, or 0 if error.                                             �
//���������������������������������������������������������������������������
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


//�������������������������������������������������������������������������Ŀ
// xf_getsize                                                               �
//                                                                          �
// Returns size of the file in bytes or -1 if error.                        �
//���������������������������������������������������������������������������
ulong xf_getsize (HANDLE fhandle)
{
    DWORD res;

    res = GetFileSize (fhandle, NULL);

    if (res == (DWORD)-1)
        xf_last_error = GetLastError();

    return res;
}


//�������������������������������������������������������������������������Ŀ
// word xf_setattr(const char *name, word attr);                            �
//                                                                          �
// Set attribute bits for a file.                                           �
//                                                                          �
// Returns -1 on error, set attribute bits otherwise.                       �
//���������������������������������������������������������������������������
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


//�������������������������������������������������������������������������Ŀ
// xf_setsize                                                               �
//                                                                          �
// Sets the size of the file to the given length (either extending or       �
// truncating).  Returns the new size or -1 if error.                       �
//���������������������������������������������������������������������������
ulong xf_setsize (HANDLE fhandle, ulong size)
{
    if (SetFilePointer (fhandle, size, NULL, FILE_BEGIN) == size)
    {
        if (SetEndOfFile (fhandle))
            return size;
    }

    return (ulong)-1;
}

//��� End of module - xfiofinf.c ���

