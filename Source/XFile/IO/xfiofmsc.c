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
// xfiofmsc.c
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
// int xf_exist(const char *name)                                           �
//                                                                          �
// Tests for existance of the file.                                         �
//                                                                          �
// Returns 1 if exists, 0 if it does not.                                   �
//���������������������������������������������������������������������������
int xf_exist (const char *name)
{
    return GetFileAttributes (name) != (DWORD)-1;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_lock(int fhandle, ulong offset, ulong nbytes);         �
//                                                                          �
// Locks a region of the file, if possible.                                 �
//                                                                          �
// Returns 0 if ok, XF_ERR_FUNCINVALID, XF_ERR_INVALIDHANDLE,               �
// XF_ERR_LOCKVIOLATION, or XF_ERR_SHAREBUFFEROVERFLOW                      �
//���������������������������������������������������������������������������
xf_error_codes xf_lock (HANDLE fhandle, ulong offset, ulong nbytes)
{
    if (LockFile (fhandle, offset, 0, nbytes, 0))
        return 0;

    xf_last_error = GetLastError ();
    return xf_last_error;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_remove(const char *name);                              �
//                                                                          �
// Removes (unlinks) the file.                                              �
//                                                                          �
// Returns 0 if ok, XF_ERR_FILENOTFOUND, XF_ERR_PATHNOTFOUND,               �
// or XF_ERR_ACCESSDENIED                                                   �
//���������������������������������������������������������������������������
xf_error_codes xf_remove (const char *name)
{
    if (DeleteFile (name))
        return 0;

    xf_last_error = GetLastError ();
    return xf_last_error;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_rename(const char *oldname, const char *newname);      �
//                                                                          �
// Renames the file.                                                        �
//                                                                          �
// Returns 0 if ok, XF_ERR_FILENOTFOUND, XF_ERR_PATHNOTFOUND,               �
// XF_ERR_ACCESSDENIED, or XF_ERR_NOTSAMEDEVICE                             �
//���������������������������������������������������������������������������
xf_error_codes xf_rename (const char *oldname, const char *newname)
{
    if (MoveFile (oldname, newname))
        return 0;

    xf_last_error = GetLastError ();
    return xf_last_error;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_unlock(int fhandle, ulong offset, ulong nbytes);       �
//                                                                          �
// Unlocks a region of the file, if possible.                               �
//                                                                          �
// Returns 0 if ok, XF_ERR_FUNCINVALID, XF_ERR_INVALIDHANDLE,               �
// XF_ERR_LOCKVIOLATION, or XF_ERR_SHAREBUFFEROVERFLOW                      �
//���������������������������������������������������������������������������
xf_error_codes xf_unlock (HANDLE fhandle, ulong offset, ulong nbytes)
{
    if (UnlockFile (fhandle, offset, 0, nbytes, 0))
        return 0;

    xf_last_error = GetLastError ();
    return xf_last_error;
}

//��� End of module - xfiofmsc.c ���

