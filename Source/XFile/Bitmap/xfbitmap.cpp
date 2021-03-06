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
// xfbitmap.cpp
//
// Contains the code for the XFBitmap container class
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "xfile.hpp"

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭�  Constructors/Destructors  碓旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFBitmap - Constructor                                                   �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
XFBitmap::XFBitmap() :
    flags(0),
    pal(0),
    data(0),
    palhandle(0),
    handle(0)
{
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFBitmap - Destructor                                                    �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
XFBitmap::~XFBitmap()
{
    release();
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFBitmap - release                                                       �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void XFBitmap::release()
{
    if (palhandle)
    {
        ivory_hfree(&palhandle);
        pal=0;
    }
    if (handle)
    {
        ivory_hfree(&handle);
        data=0;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFBitmap - lock                                                          �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFBitmap::lock()
{
    xf_error_codes err = XF_ERR_NONE;

    if (!pal && palhandle)
    {
        pal = (dword*)ivory_hlock(palhandle);

        if (!pal)
            err=XF_ERR_LOCKFAILED;
    }
    if (!data && handle)
    {
        data = (byte*)ivory_hlock(handle);

        if (!data)
            err=XF_ERR_LOCKFAILED;
    }

    return err;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFBitmap - unlock                                                        �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void XFBitmap::unlock()
{
    if (pal && palhandle)
    {
        ivory_hunlock(palhandle);
        pal=0;
    }
    if (data && handle)
    {
        ivory_hunlock(handle);
        data=0;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFBitmap - create                                                        �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFBitmap::create(ushort w, ushort h, byte _bpp, int clear)
{
    release();

//陳� Verify input
    if (!w || !h)
        return XF_ERR_NOTSUPPORTED;

    switch (_bpp)
    {
        case XFBM_BPP_MONO:
        case XFBM_BPP_8BIT:
        case XFBM_BPP_15BIT:
        case XFBM_BPP_24BIT:
        case XFBM_BPP_32BIT:
            break;
        default:
            return XF_ERR_NOTSUPPORTED;
    }

    width=w;
    height=h;
    bpp=_bpp;

//陳� Create palette if needed
    pal=0;
    if (_bpp == XFBM_BPP_8BIT)
    {
        palhandle = ivory_halloc(sizeof(dword)*256);
        if (!palhandle)
            return XF_ERR_NOMEMORY;

        pal = (dword*)ivory_hlock(palhandle);
        if (!pal)
            return XF_ERR_LOCKFAILED;

        if (clear)
            memset(pal,0,sizeof(dword)*256);
    }

//陳� Allocate bitmap and possibly clear it
    ulong size = (_bpp == XFBM_BPP_MONO)
                 ? (((w + 7) >> 3) * h)
                 : (w * h * _bpp);

    handle = ivory_halloc(size);
    if (!handle)
    {
        release();
        return XF_ERR_NOMEMORY;
    }

    data = (byte*)ivory_hlock(handle);
    if (!data)
    {
        release();
        return XF_ERR_LOCKFAILED;
    }

    if (clear)
        memset(data,0,size);

    return XF_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFBitmap - generate_mono                                                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
byte *XFBitmap::generate_mono(dword bgcolor)
{
//陳� Verify input
    if (bpp != XFBM_BPP_8BIT || !width || !height)
        return 0;

//陳� Allocate result space
    byte *nptr = new byte [((width+7) >> 3) * height];
    if (!nptr)
        return 0;

//陳� Lock bitmap
    int locked=0;
    if (data)
    {
        locked=1;
    }
    else if (lock())
    {
        delete nptr;
        return 0;
    }

    if (!data)
    {
        delete nptr;
        return 0;
    }

//陳� Convert to mono map
    ulong lwidth = width & ~0x7;
    ulong rwidth = width & 0x7;

    byte *dptr=nptr, *sptr=data;
    for (ulong j = 0; j < height; j++)
    {
        if (width >= 8)
        {
            for (ulong i = 0; i < lwidth; i+=8)
            {
                byte t = 0;
                for (ulong k = 0; k < 8; k++)
                {
                    if (*(sptr++) != (byte)bgcolor)
                    {
                        t |= (0x80 >> k);
                    }
                }
                *(dptr++) = t;
            }
        }
        if (rwidth)
        {
            byte t = 0;
            for (ulong k = 0; k < rwidth; k++)
            {
                if (*(sptr++) != (byte)bgcolor)
                    t |= (0x80 >> k);
            }
            *(dptr++) = t;
        }
    }

//陳� Unlock and return
    if (!locked)
        unlock();

    return nptr;
}

//葦� End of module - xfbitmap.cpp 憶�
