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
// xfpcx.cpp
//
// Contains code for working with Zsoft PCX files.  Only 256 color
// images are supported.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <assert.h>
#include <string.h>

#include "xfile.hpp"

//���������������������������������������������������������������������������
//
//                               Structures
//
//���������������������������������������������������������������������������

struct PCX_header
{
    byte    zsoft;                      // 0x0a magic code
    byte    version;                    // Version code
    byte    encoding;                   // 1 = PCX RLE
    byte    bpp;                        // Bits/pixel/plane
    ushort  xmin;                       // Image dimensions
    ushort  ymin;
    ushort  xmax;
    ushort  ymax;
    ushort  hres;                       // Dots/inch
    ushort  vres;
    byte    hpal[48];                   // Header palette
    byte    res;                        // always 0
    byte    planes;                     // Number of planes
    ushort  bpl;                        // Bytes/line/plane
    ushort  hpali;                      // 1 = color or B&W
                                        // 0 = greyscale
    ushort  vidx;                       // Video screen size
    ushort  vidy;
    byte    na[54];
};

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFParsePCX - read                                                        �
//                                                                          �
// Reads a PCX format bitmap from the file object.                          �
//���������������������������������������������������������������������������
xf_error_codes XFParsePCX::read(XFBitmap *b)
{
    int                 i, j;
    int                 x, y;
    byte                *ptr;
    byte                work[768];
    struct PCX_header   header;

    if (!b)
        b = bm;

//��� Read header ���
    if (xf->read(&header,sizeof(PCX_header)) != sizeof(PCX_header))
        return (errorn=xf->error());

//��� Verify valid header ���
    if ( header.zsoft != 0xa )
        return (errorn=XF_ERR_INVALIDHEADER);

//��� Check for unsupported formats ���
    if (header.bpp != 8 || header.planes != 1)
        return (errorn=XF_ERR_NOTSUPPORTED);

//��� Setup bitmap object ���
    b->release();

    b->flags=0;
    b->clrinuse=0;
    b->width = (ushort) (header.xmax - header.xmin + 1);
    b->height = (ushort) (header.ymax - header.ymin + 1);
    b->bpp = XFBM_BPP_8BIT;

//��� Load image data ���

    // Allocate memory
    b->handle = ivory_halloc(b->width * b->height * b->bpp);
    if (!b->handle)
    {
        b->release();
        return (errorn=XF_ERR_NOMEMORY);
    }

    b->data = (byte *)ivory_hlock(b->handle);
    if (!b->data)
    {
        b->release();
        return (errorn=XF_ERR_LOCKFAILED);
    }

    assertMyth("XFParsePCX::read assumes 1 bit plane",
               header.planes == 1);

    for(y=0, ptr = b->data; y < b->height; y++)
    {
        for(i=0, x=0; i < header.bpl;)
        {
            if (xf->read(work,1) != 1)
            {
                b->release();
                return (errorn=XF_ERR_INVALIDIMAGE);
            }

            if ((*work & 0xc0) == 0xc0)
            {
                // RLE
                j = (*work & 0x3f);

                if (xf->read(work,1) != 1)
                {
                    b->release();
                    return (errorn=XF_ERR_INVALIDIMAGE);
                }

                for(; j > 0; j--)
                {
                    if (x < b->width)
                    {
                        *(ptr++) = *work;
                        x++;
                    }
                    i++;
                }
            }
            else
            {
                // Literal
                if (x < b->width)
                {
                    *(ptr++) = *work;
                    x++;
                }
                i++;
            }
        }
    }

//��� Get palette data ���
    if (header.planes == 1)
    {
        // Allocate memory
        b->palhandle = ivory_halloc(sizeof(dword)*256);
        if (!b->palhandle)
        {
            return (errorn=XF_ERR_NOMEMORY);
        }

        b->pal = (dword *)ivory_hlock(b->palhandle);
        if (!b->pal)
        {
            b->release();
            return (errorn=XF_ERR_LOCKFAILED);
        }

        memset(b->pal,0,sizeof(dword)*256);

        if (xf->read(work,1) != 1 || *work != 0xc)
        {
            b->release();
            return (errorn=XF_ERR_INVALIDPALETTE);
        }

        if (xf->read(work,768) != 768)
        {
            b->release();
            return (errorn=XF_ERR_INVALIDPALETTE);
        }

        for(ptr=(byte *)b->pal, i=0; i < 256; i++)
        {
            *(ptr++) = work[i*3];
            *(ptr++) = work[i*3+1];
            *(ptr++) = work[i*3+2];
            *(ptr++) = 0;
        }
        b->clrinuse=255;
    }

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFParsePCX - write                                                       �
//                                                                          �
// Writes a PCX format bitmap to the file object.                           �
//���������������������������������������������������������������������������
xf_error_codes XFParsePCX::write(XFBitmap *b)
{
    int                 i, j;
    int                 y;
    int                 locked=0;
    byte                *s;
    byte                *ptr;
    byte                work[768];
    struct PCX_header   header;

    if (!b)
        b = bm;

    if (b->bpp != XFBM_BPP_8BIT
        || !b->width || !b->height)
        return (errorn=XF_ERR_NOTSUPPORTED);

//��� Write header ���
    memset(&header,0,sizeof(PCX_header));
    header.zsoft = 0xa;
    header.version = 5;
    header.encoding = 1;
    header.bpp = 8;
    header.xmin = 0;
    header.ymin = 0;
    header.xmax = (ushort) (b->width-1);
    header.ymax = (ushort) (b->height-1);
    header.planes = 1;
    header.bpl = (ushort)(b->width + ((b->width & 0x1) ? 1 : 0));

    if (xf->write(&header,sizeof(PCX_header)) != sizeof(PCX_header))
    {
        errorn=xf->error();
        return errorn;
    }

    // Lock palette and image data, if needed
    if (b->pal || b->data)
    {
        locked=1;
    }
    else
    {
        xf_error_codes err;

        err=b->lock();
        if (err)
        {
            return (errorn=err);
        }
    }

//��� Write out image ���
    if (!b->data)
    {
        if (!locked)
            b->unlock();
        return (errorn=XF_ERR_INVALIDIMAGE);
    }

    for(y=0, ptr = b->data; y < b->height; y++)
    {
        for(i=0; i < b->width; ptr++)
        {
            for(s=ptr, j=0;
                (j < 62) && ((j+i+1) < b->width) && (*s == *(ptr+1));
                j++)
            {
                ptr++;
            }

            if (j > 0)
            {
                // Found reps
                *work = (byte)(0xc0 | (j+1));
                *(work+1) = *ptr;

                if (xf->write(work,2) != 2)
                {
                    if (!locked)
                        b->unlock();
                    errorn=xf->error();
                    return errorn;
                }

                i += j+1;
            }
            else
            {
                // Literal
                if ((*ptr & 0xc0) == 0xc0)
                {
                    *work = 0xc1;
                    *(work+1) = *ptr;

                    if (xf->write(work,2) != 2)
                    {
                        if (!locked)
                            b->unlock();
                        errorn=xf->error();
                        return errorn;
                    }

                }
                else
                {
                    if (xf->write(ptr,1) != 1)
                    {
                        if (!locked)
                            b->unlock();
                        errorn=xf->error();
                        return errorn;
                    }
                }

                i++;
            }
        }

        // Handle BPL padding, if any
        if (b->width & 0x1)
        {
            *work = 0;
            if (xf->write(work,1) != 1)
            {
                if (!locked)
                    b->unlock();
                errorn=xf->error();
                return errorn;
            }
        }
    }

//��� Write out palette, if any ���
    if (header.planes == 1)
    {
        if (!b->pal)
        {
            if (!locked)
                b->unlock();
            return (errorn=XF_ERR_INVALIDPALETTE);
        }

        // Write palette check code
        *work = 0xc;
        if (xf->write(work,1) != 1)
        {
            if (!locked)
                b->unlock();
            errorn=xf->error();
            return errorn;
        }

        // Write palette data
        for (i=0, ptr=(byte*)b->pal; i < 256; i++)
        {
             work[i*3] = *(ptr++);      // red
             work[i*3+1] = *(ptr++);    // green
             work[i*3+2] = *(ptr++);    // blue
             ptr++;                     // na to make dword
        }

        if (xf->write(work,768) != 768)
        {
            if (!locked)
                b->unlock();
            errorn=xf->error();
            return errorn;
        }
    }

    if (!locked)
        b->unlock();

    return XF_ERR_NONE;
}

//��� End of module - xfpcx.cpp ���

