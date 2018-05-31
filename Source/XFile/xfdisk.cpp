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
// xfdisk.cpp
//
// Contains the code for the disk file object.  This object performs
// non-buffered file input/output using the low-level C calls in
// the XFile library.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <string.h>

#include "xfbase.hpp"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFileDisk - Constructor                                                  �
//���������������������������������������������������������������������������
XFileDisk::XFileDisk() :
    fHandle(INVALID_HANDLE_VALUE)
{
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - Destructor                                                   �
//���������������������������������������������������������������������������
XFileDisk::~XFileDisk()
{
    //��� Close the file handle, if open ���
    if (sFlags & XF_STATUS_OPEN)
        close();
}



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFileDisk - open                                                         �
//                                                                          �
// Opens file handle for object.  Returns 0 if ok, error number otherwise.  �
//���������������������������������������������������������������������������
xf_error_codes XFileDisk::open (const char *name, dword flags)
{
    if (sFlags & XF_STATUS_OPEN)
        return XF_ERR_ALREADYOPEN;

//��� Open file ���
    fHandle = ::xf_open (name, flags);

    if (fHandle == INVALID_HANDLE_VALUE)
    {
        errorn = xf_last_error;
        return errorn;
    }

    strncpy (fName, name, sizeof(fName));

    sFlags |= XF_STATUS_OPEN;

    if (flags & XF_OPEN_WRITE)
        sFlags |= XF_STATUS_WRITE;
    if (flags & XF_OPEN_READ)
        sFlags |= XF_STATUS_READ;
    if (flags & XF_OPEN_KILL)
        sFlags |= XF_STATUS_KILL;

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - opentmp                                                      �
//                                                                          �
// Opens file handle for object with temporary filename.  Returns 0 if ok,  �
// error number otherwise.                                                  �
//���������������������������������������������������������������������������
xf_error_codes XFileDisk::opentmp (const char *name, dword flags)
{
    if (sFlags & XF_STATUS_OPEN)
        return XF_ERR_ALREADYOPEN;

//��� Open file ���
    fHandle = ::xf_opentmp (name, flags);

    if (fHandle == INVALID_HANDLE_VALUE)
    {
        errorn=xf_last_error;
        return errorn;
    }

    strncpy(fName,name,sizeof(fName));

    sFlags |= XF_STATUS_OPEN | XF_STATUS_ISTMP;

    if (flags & XF_OPEN_WRITE)
        sFlags |= XF_STATUS_WRITE;
    if (flags & XF_OPEN_READ)
        sFlags |= XF_STATUS_READ;
    if (flags & XF_OPEN_KILL)
        sFlags |= XF_STATUS_KILL;

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - close                                                        �
//                                                                          �
// Closes a file handle for object.  Returns 0 if ok, error number otherwise�
// If STATUS_KILL is active, then the file is killed on close.              �
//���������������������������������������������������������������������������
xf_error_codes XFileDisk::close ()
{
    if (!(sFlags & XF_STATUS_OPEN))
        return XF_ERR_NOTOPEN;

    sFlags &= ~XF_STATUS_OPEN;

    if (::xf_close (fHandle))
    {
        errorn = xf_last_error;
        return errorn;
    }

    if ((sFlags & XF_STATUS_KILL)
        && ::xf_remove (fName))
    {
        errorn = xf_last_error;
        return errorn;
    }

    sFlags = 0;

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - flush                                                        �
//                                                                          �
// Flushes any buffered writes and forces disk to update it's structures.   �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFileDisk::flush ()
{
    if (!(sFlags & XF_STATUS_OPEN))
        return XF_ERR_NOTOPEN;

    if (::xf_flush (fHandle))
    {
        errorn = xf_last_error;
        return errorn;
    }

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - read                                                         �
//                                                                          �
// Read a block of the given size from the open file.                       �
// Returns number of bytes read or 0 if error.                              �
//���������������������������������������������������������������������������
ulong XFileDisk::read (void *ptr, ulong size)
{
    ulong x = ::xf_read (fHandle, ptr, size);

    if (x == -1)
    {
         errorn = xf_last_error;
         return 0;
    }
    else if  (!x)
        errorn = XF_ERR_EOF;

    return x;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - write                                                        �
//                                                                          �
// Write a block of the given size to the open file.                        �
// Returns number of bytes written or 0 if error.                           �
//���������������������������������������������������������������������������
ulong XFileDisk::write (const void *ptr, ulong size)
{
    ulong x = ::xf_write (fHandle, ptr, size);

    if (x == -1)
    {
        errorn=xf_last_error;
        return 0;
    }

    return x;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - seek                                                         �
//                                                                          �
// Seeks to an offset in the file (0=set, 1=current, 2=end)                 �
// Returns -1 if error, offset within file otherwise.                       �
//���������������������������������������������������������������������������
ulong XFileDisk::seek (long offset, int mode)
{
    ulong x = ::xf_seek (fHandle, mode, offset);

    if (x == -1)
        errorn = xf_last_error;

    return x;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - getsize                                                      �
//                                                                          �
// Returns the size of the current file or -1 if error.                     �
//���������������������������������������������������������������������������
ulong XFileDisk::getsize ()
{
    ulong x = ::xf_getsize(fHandle);

    if (x == -1)
        errorn = xf_last_error;

    return x;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - setsize                                                      �
//                                                                          �
// Extends or truncates the file to the given size.  Returns new size or    �
// -1 on error.                                                             �
//���������������������������������������������������������������������������
ulong XFileDisk::setsize (ulong size)
{
   ulong x = ::xf_setsize (fHandle, size);

   if (x == -1)
       errorn = xf_last_error;

   return x;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - getfdate                                                     �
//                                                                          �
// Returns the current file date of the file or 0 if error.                 �
//���������������������������������������������������������������������������
word XFileDisk::getfdate ()
{
    word x = ::xf_getfdate (fHandle);

    if (!x)
        errorn = xf_last_error;

    return x;
}


//�������������������������������������������������������������������������Ŀ
// XFileDisk - getftime                                                     �
//                                                                          �
// Returns the current file time of the file or 0 if error.                 �
//���������������������������������������������������������������������������
word XFileDisk::getftime ()
{
    word x = ::xf_getftime (fHandle);
    if (!x)
        errorn = xf_last_error;

    return x;
}

//��� End of module - xfdisk.cpp ���

