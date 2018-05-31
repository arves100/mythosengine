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
// xfiofind.c
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "xfio.h"
#include <assert.h>

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_findfirst(const char *fname, int attr,                 �
//                  struct xf_find_type *fileinfo);                         �
//                                                                          �
// Starts a file search based on a wildcard.                                �
//                                                                          �
// Returns 0 if ok, XF_ERR_FILENOTFOUND, XF_ERR_PATHNOTFOUND,               �
// or XF_ERR_NOMOREFILES                                                    �
//���������������������������������������������������������������������������
xf_error_codes xf_findfirst (const char *fname, int attr,
                             struct xf_find_type *fileinfo)
{
    // If this context is in use, close it.
    if (fileinfo->xf_hFind != NULL)
        FindClose (fileinfo->xf_hFind);

    // Set up a pointer for backward compatability with MythOS
    fileinfo->xf_name = &fileinfo->xf_find.cFileName[0];

    // Start the search
    fileinfo->xf_hFind = FindFirstFile (fname, &fileinfo->xf_find);

    if (fileinfo->xf_hFind == INVALID_HANDLE_VALUE)
        return xf_last_error = GetLastError();

    // Stuff the fields for backwards compatability
    fileinfo->xf_size   = fileinfo->xf_find.nFileSizeLow;
    fileinfo->xf_attrib = fileinfo->xf_find.dwFileAttributes;
    FileTimeToDosDateTime (&fileinfo->xf_find.ftLastWriteTime,
                           &fileinfo->xf_wr_date,
                           &fileinfo->xf_wr_time);
    return 0;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_findnext(struct xf_find_type *fileinfo);               �
//                                                                          �
// Continues a file search based on a wildcard.                             �
//                                                                          �
// Returns 0 if ok, or XF_ERR_NOMOREFILES                                   �
//���������������������������������������������������������������������������
xf_error_codes xf_findnext (struct xf_find_type *fileinfo)
{
    assertMyth("xf_findnext assumes valid find handle in fileinfo",
               fileinfo->xf_hFind != INVALID_HANDLE_VALUE);

    if (FindNextFile (fileinfo->xf_hFind, &fileinfo->xf_find))
    {
        // Stuff the fields for backwards compatability
        fileinfo->xf_size   = fileinfo->xf_find.nFileSizeLow;
        fileinfo->xf_attrib = fileinfo->xf_find.dwFileAttributes;
        FileTimeToDosDateTime (&fileinfo->xf_find.ftLastWriteTime,
                               &fileinfo->xf_wr_date,
                               &fileinfo->xf_wr_time);
        return 0;
    }

    FindClose (fileinfo->xf_hFind);
    fileinfo->xf_hFind = INVALID_HANDLE_VALUE;
    return XF_ERR_NOMOREFILES;
}


//�������������������������������������������������������������������������Ŀ
// xf_error_codes xf_findclose(struct xf_find_type *fileinfo);              �
//                                                                          �
// Ends the file file search, freeing any resources.                        �
//                                                                          �
// Returns 0 if ok, or XF_ERR_INVALIDHANDLE                                 �
//���������������������������������������������������������������������������
xf_error_codes xf_findclose (struct xf_find_type *fileinfo)
{
    if (fileinfo->xf_hFind == INVALID_HANDLE_VALUE)
        return XF_ERR_INVALIDHANDLE;

    FindClose (fileinfo->xf_hFind);
    return 0;
}

//��� End of module - xfiofind.c ���

