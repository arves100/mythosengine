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
//
// xfio.h
//
// This contains the C-callable low-level routines used by the
// XFile class.
//
//���������������������������������������������������������������������������

#ifndef __XFIO_H
#define __XFIO_H    1

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "debug.h"
#include "portable.h"
#include "xfdefs.h"

//���������������������������������������������������������������������������
//
//                               Structures
//
//���������������������������������������������������������������������������

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __WATCOMC__
#pragma pack(1);
#endif

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//�������������������������������������������������������������������������Ŀ
// Structure needed by the xf_findfirst, xf_findnext routines.              �
//���������������������������������������������������������������������������
struct xf_find_type
{
    HANDLE              xf_hFind;
    WIN32_FIND_DATA     xf_find;

    // These values get stuffed for backward compatability
    dword               xf_attrib;
    word                xf_wr_time;
    word                xf_wr_date;
    ulong               xf_size;
    char                *xf_name;   // For backward compatability
};

//���������������������������������������������������������������������������
//
//                               Prototypes
//
//���������������������������������������������������������������������������

extern xf_error_codes xf_last_error;

//�������������������������������������������������������������������������Ŀ
// File-level i/o (used by XFile)                                           �
//���������������������������������������������������������������������������

HANDLE xf_open(const char *name, dword flags);
HANDLE xf_opentmp (const char *name, dword flags);
xf_error_codes xf_close (HANDLE hFile);
xf_error_codes xf_flush (HANDLE hFile);
ulong xf_read (HANDLE hFile, void *ptr, ulong size);
ulong xf_write (HANDLE hFile, const void *ptr, ulong size);
ulong xf_seek (HANDLE hFile, int mode, long offset);

xf_error_codes xf_lock (HANDLE hFile, ulong offset, ulong nbytes);
xf_error_codes xf_unlock (HANDLE hFile, ulong offset, ulong nbytes);

ulong xf_getsize (HANDLE hFile);
ulong xf_setsize (HANDLE hFile, ulong size);

word xf_getfdate (HANDLE hFile);
word xf_getftime (HANDLE hFile);


//�������������������������������������������������������������������������Ŀ
// Utility routines for DOS file operations                                 �
//���������������������������������������������������������������������������

xf_error_codes xf_remove (const char *name);
xf_error_codes xf_rename (const char *oldname, const char *newname);
int xf_exist (const char *name);
word xf_getattr (const char *name);
word xf_setattr (const char *name, word attr);

xf_error_codes xf_findfirst (const char *fname, int attr, struct xf_find_type *fileinfo);
xf_error_codes xf_findnext  (struct xf_find_type *fileinfo);
xf_error_codes xf_findclose (struct xf_find_type *fileinfo);

ulong xf_getfreebytes (char drive);     // 0 for drive is current drive

char *xf_getdir (char *path);           // Buffer should be 67-bytes or more
xf_error_codes xf_chdir (const char *path);
xf_error_codes xf_mkdir (const char *path);
xf_error_codes xf_rmdir (const char *path);


//�������������������������������������������������������������������������Ŀ
// Miscellaneous routines                                                   �
//���������������������������������������������������������������������������

char *xf_getenv (const char *varname);
char *xf_searchenv (const char *filename, const char *env_var, char *path);

char *xf_makepath (char *path, const char *drive, const char *dir, const char *fname, const char *ext);
void xf_splitpath (const char *path, char *drive, char *dir, char *fname, char *ext);


//�������������������������������������������������������������������������Ŀ
// Error return routine for low-level i/o functions                         �
//���������������������������������������������������������������������������

xf_error_codes xf_error(void);

#ifdef __WATCOMC__
#pragma pack();
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#ifdef __cplusplus
};
#endif

#endif

//��� End of header - xfio.h ���
