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
//
// xfdskbuf.cpp
//
// This a version of XFileDisk that buffers all i/o routines for faster
// performance on small data blocks.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <assert.h>
#include <string.h>

#include "xfbase.hpp"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#define XF_BUFFINIT 1024

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭�  Constructors/Destructors  碓旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - Constructor                                               �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
XFileDiskBuf::XFileDiskBuf() :
    XFileDisk(),
    end(0),
    next(0),
    data(0),
    buffSize(0)
{
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - Destructor                                                �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
XFileDiskBuf::~XFileDiskBuf()
{
//陳� Close the file handle, if open 陳�
    if (sFlags & XF_STATUS_OPEN)
        close();
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - open                                                      �
//                                                                          �
// Opens file handle for object.  Returns 0 if ok, error number otherwise.  �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFileDiskBuf::open(const char *name, dword flags)
{
    xf_error_codes  err;

//陳 Perform base open
    err=XFileDisk::open(name,flags);
    if (err)
        return err;

//陳 Allocate buffer space
    data = new byte [XF_BUFFINIT];
    if (!data)
    {
        errorn=XF_ERR_NOMEMORY;
        close();
        return errorn;
    }
    buffSize = XF_BUFFINIT;
    next = end = data;

    sFlags &= ~(XF_STATUS_DIRTY|XF_STATUS_LASTREAD|XF_STATUS_LASTWRITE);

    return XF_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - opentmp                                                   �
//                                                                          �
// Opens file handle for object with temporary filename.  Returns 0 if ok,  �
// error number otherwise.                                                  �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFileDiskBuf::opentmp (const char *name, dword flags)
{
    xf_error_codes  err;

//陳 Perform base open
    err=XFileDisk::opentmp(name,flags);
    if (err)
        return err;

//陳 Allocate buffer space
    data = new byte [XF_BUFFINIT];
    if (!data)
    {
        errorn=XF_ERR_NOMEMORY;
        close();
        return errorn;
    }
    buffSize = XF_BUFFINIT;
    next = end = data;

    sFlags &= ~(XF_STATUS_DIRTY|XF_STATUS_LASTREAD|XF_STATUS_LASTWRITE);

    return XF_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - close                                                     �
//                                                                          �
// Closes a file handle for object.  Returns 0 if ok, error number otherwise�
// If STATUS_KILL is active, then the file is killed on close.              �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFileDiskBuf::close ()
{
    xf_error_codes  err=XF_ERR_NONE;

    if (!(sFlags & XF_STATUS_OPEN))
        return XF_ERR_NOTOPEN;

//陳 Perform flush, if needed
    if (sFlags & XF_STATUS_WRITE)
        err=flush();

//陳 Free buffer
    if (data)
    {
        delete [] data;
        next=end=data=0;
        buffSize=0;
    }

//陳 Perform base close
    if (err)
        XFileDisk::close();
    else
        err=XFileDisk::close();

    return err;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - flush                                                     �
//                                                                          �
// Flushes any buffered writes and forces disk to update it's structures.   �
// Returns 0 if ok, error number otherwise.                                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFileDiskBuf::flush ()
{
    xf_error_codes  err = XF_ERR_NONE;

    if (!(sFlags & XF_STATUS_OPEN))
        return XF_ERR_NOTOPEN;

    assertMyth("XFileDiskBuf::flush assumes buffer exists",
               data);

    if (!(sFlags & XF_STATUS_WRITE))
    {
        return XF_ERR_NONE;
    }

    if (sFlags & XF_STATUS_LASTWRITE && ((next - data) > 0))
    {
        if (XFileDisk::write (data,next - data) != ulong (next-data))
        {
            err = XF_ERR_WRITEFAULT;
            errorn = err;
        }
    }

    next = end = data;
    sFlags &= ~(XF_STATUS_DIRTY|XF_STATUS_LASTWRITE);

//陳 Perform base flush
    if (err)
        XFileDisk::flush();
    else
        err=XFileDisk::flush();

    return err;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - read                                                      �
//                                                                          �
// Read a block of the given size from the open file.                       �
// Returns number of bytes read or 0 if error.                              �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
ulong XFileDiskBuf::read (void *ptr, ulong size)
{
    ulong   t;
    ulong   ns;
    byte    *p = (byte*)ptr;

    assertMyth("XFileDiskBuf::read assumes buffer exists",
               data);

    if (!size || !(sFlags & XF_STATUS_READ))
        return 0;

    if (sFlags & XF_STATUS_LASTWRITE)
    {
        if (flush())
            return 0;
    }

    sFlags |= XF_STATUS_LASTREAD;

    for(ns=size; ns > 0;)
    {
        if (next >= end)
        {
            t=XFileDisk::read(data,buffSize);
            if (t == -1)
            {
                errorn=xf_last_error;
                return 0;
            }
            else if (!t)
            {
                errorn=XF_ERR_EOF;
                break;
            }
            next = data;
            end = data + t;
        }

        t = end-next;
        if (ns < t)
            t = ns;

        memcpy(p, next, t);
        p += t;
        next += t;
        ns -= t;
    }

    return (size - ns);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - write                                                     �
//                                                                          �
// Write a block of the given size to the open file.                        �
// Returns number of bytes written or 0 if error.                           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
ulong XFileDiskBuf::write (const void *ptr, ulong size)
{
    ulong   t;
    ulong   ns;
    byte    *p = (byte*)ptr;

    assertMyth("XFileDiskBuf::write assumes buffer exists",
               data);

    if (!size || !(sFlags & XF_STATUS_WRITE))
        return 0;

    if (sFlags & XF_STATUS_LASTREAD)
    {
        seek_cur(0);
    }

    for(ns=size; ns > 0;)
    {
        if (next >= end)
        {
            if (sFlags & XF_STATUS_LASTWRITE && ((next - data) > 0))
            {
                t=XFileDisk::write(data,next - data);
                if (t == -1)
                {
                    errorn = xf_last_error;
                    return 0;
                }
                else if (t != ulong (next-data))
                {
                    errorn = XF_ERR_WRITEFAULT;
                    return 0;
                }
            }

            sFlags |= XF_STATUS_DIRTY|XF_STATUS_LASTWRITE;
            next = data;
            end = data + buffSize;
        }

        t = end-next;
        if (ns < t)
            t = ns;

        memcpy(next, p, t);
        p += t;
        next += t;
        ns -= t;
    }

    return (size - ns);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - seek                                                      �
//                                                                          �
// Seeks to an offset in the file (0=set, 1=current, 2=end)                 �
// Returns -1 if error, offset within file otherwise.                       �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
ulong XFileDiskBuf::seek(long offset, int mode)
{
    xf_error_codes  err;

//陳 Perform flush, if needed
    if (sFlags & XF_STATUS_LASTWRITE)
    {
        err=flush();
        if (err)
            return err;
    }
    else if (sFlags & XF_STATUS_LASTREAD)
    {
        if (mode == 1)
        {
            offset -= (long)(end-next);
        }

        sFlags &= ~XF_STATUS_LASTREAD;
        next = end = data;
    }

//陳 Perform base seek
    return XFileDisk::seek(offset,mode);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFileDiskBuf - setbuffersize                                             �
//                                                                          �
// Sets the size of the buffer based on the input size, forcing it to a 1K  �
// boundary.                                                                �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
ulong XFileDiskBuf::setbuffersize(ulong size)
{
    byte *nb;

    if (!(sFlags & XF_STATUS_OPEN))
        return XF_ERR_NOTOPEN;

    assertMyth("XFileDiskBuf::setbuffersize assumes buffer exists",
               data);

    size &= 0xfffffe00;
    if (size < XF_BUFFINIT)
        size = XF_BUFFINIT;

    seek_cur(0);

    nb = new byte[size];
    if (nb)
    {
        delete [] data;
        data = nb;
        buffSize = size;
    }

    return buffSize;
}

//葦� End of module - xfdskbuf.cpp 憶�

