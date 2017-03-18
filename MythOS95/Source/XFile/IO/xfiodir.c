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
// xfiodir.c
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "xfdefs.h"

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

extern xf_error_codes xf_last_error;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_chdir(const char *path);                               �
//                                                                          �
// Changes the current directory to the path.                               �
//                                                                          �
// Returns 0 if ok, XF_ERR_PATHNOTFOUND, or XF_ERR_ACCESSDENIED             �
//���������������������������������������������������������������������������
xf_error_codes xf_chdir (const char *path)
{
    if (SetCurrentDirectory (path))
        return 0;

    // Need to find the actual error condition
    return XF_ERR_PATHNOTFOUND;
}


//�������������������������������������������������������������������������Ŀ
// char *xf_getdir(char *path);                                             �
//                                                                          �
// Gets the current directory on the current drive.                         �
//                                                                          �
// Returns a pointer to the path, with path set to the empty string if an   �
// error occurrs.                                                           �
//                                                                          �
// Buffer should be MAX_PATH.                                               �
//���������������������������������������������������������������������������
char *xf_getdir (char *path)
{
    if (GetCurrentDirectory (MAX_PATH, path) < MAX_PATH)
        return path;

    return NULL;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_mkdir(const char *path);                               �
//                                                                          �
// Creates a new directory in path                                          �
//                                                                          �
// Returns 0 if ok, XF_ERR_PATHNOTFOUND, or XF_ERR_ACCESSDENIED             �
//���������������������������������������������������������������������������
xf_error_codes xf_mkdir (const char *path)
{
    if (CreateDirectory (path, NULL))
        return 0;

    xf_last_error = GetLastError();
    return xf_last_error;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_rmdir(const char *path);                               �
//                                                                          �
// Removes a directory specified in path.                                   �
//                                                                          �
// Returns 0 if ok, XF_ERR_PATHNOTFOUND, XF_ERR_ACCESSDENIED,               �
// XF_ERR_INVALIDHANDLE, or XF_ERR_CANTREMOVECHDIR                          �
//���������������������������������������������������������������������������
xf_error_codes xf_rmdir (const char *path)
{
    if (RemoveDirectory (path))
        return 0;

    xf_last_error = GetLastError();
    return xf_last_error;
}

//��� End of module - xfiodir.c ���

