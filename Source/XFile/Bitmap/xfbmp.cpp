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
// xfbmp.cpp
//
// Contains code for working with Windows 3 BMP files.  OS/2 1.x
// format BMPs are not supported by this code.  The writer always
// outputs monochrome, 8-bit, or 24-bit uncompressed images.
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

struct File_header
{
    char    bfType[2];              // 'BM' in ASCII
    ulong   bfSize;                 // Size in longwords of file
    word    bfReserved1;
    word    bfReserved2;
    ulong   bfOffBits;              // Offset for image data
};

struct Info_header
{
    ulong   biSize;                 // 40 bytes for Windows
    ulong   biWidth;                // Image width in pixels
    ulong   biHeight;               // Image height in pixels
    ushort  biPlanes;               // Number of image planes (always 1)
    ushort  biBitCount;             // Bits per pixel (1,4,8, or 24)
    ulong   biCompression;          // Compression type
    ulong   biSizeImage;            // Size in bytes of compressed image
    ulong   biXPelsPerMeter;        // Horiz. resolution in pixels/meter
    ulong   biYPelsPerMeter;        // Vert. resolution in pixels/meter
    ulong   biClrUsed;              // Number of colors used
    ulong   biClrImportant;         // Number of colors important
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
// XFParseBMP - read                                                        �
//                                                                          �
// Reads a BMP format bitmap from the file object.                          �
//                                                                          �
// Doesn't handle OS/2 v1 format.                                           �
//���������������������������������������������������������������������������
xf_error_codes XFParseBMP::read(XFBitmap *b)
{
    int             i, j;
    int             x;
    int             y;
    ulong           w;
    byte            *ptr;
    byte            *sptr;
    byte            *dptr;
    int             ncolors;
    File_header     fheader;
    Info_header     iheader;
    byte            work[4*256];

    if (!b)
        b = bm;

//��� Read file header ���
    if (xf->read(&fheader,sizeof(File_header)) != sizeof(File_header))
        return (errorn=xf->error());

//��� Verify valid file header ���
    if ( fheader.bfType[0] != 'B'
         || fheader.bfType[1] != 'M' )
        return (errorn=XF_ERR_INVALIDHEADER);

//��� Read info header ���
    if (xf->read(&iheader,sizeof(Info_header)) != sizeof(Info_header))
        return (errorn=xf->error());

//��� Verify valid info header  ���
    if ( iheader.biSize != 40
         || iheader.biPlanes != 1
         || (iheader.biBitCount != 1
             && iheader.biBitCount != 4
             && iheader.biBitCount != 8
             && iheader.biBitCount != 16
             && iheader.biBitCount != 24)
         || !iheader.biWidth
         || !iheader.biHeight
         || iheader.biWidth >= XF_MAX_WIDTH
         || iheader.biHeight >= XF_MAX_HEIGHT )
        return (errorn=XF_ERR_NOTSUPPORTED);

//��� Check for unsupported formats ���
    if ( (iheader.biCompression != 0
          && iheader.biCompression != 1
          && iheader.biCompression != 2 ) )
        return (errorn=XF_ERR_NOTSUPPORTED);

//��� Setup bitmap object ���
    b->release();

    b->flags=0;
    b->clrinuse=0;
    b->width = (ushort) iheader.biWidth;
    b->height = (ushort) iheader.biHeight;

    if (iheader.biBitCount == 1)
    {
        b->bpp = XFBM_BPP_MONO;
    }
    else if (iheader.biBitCount == 16)
    {
        b->bpp = XFBM_BPP_15BIT;
    }
    else if (iheader.biBitCount == 24)
    {
        b->bpp = XFBM_BPP_24BIT;
    }
    else
    {
        b->bpp = XFBM_BPP_8BIT;
    }

//��� Get palette data ���
    if (iheader.biBitCount == 4 || iheader.biBitCount == 8)
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

        if (!iheader.biClrUsed)
        {
            switch (iheader.biBitCount)
            {
                case 4:
                    ncolors = 16;
                    break;
                default:
                    ncolors = 256;
            }
        }
        else
            ncolors = iheader.biClrUsed;

        // Load palette into work-memory
        if (xf->read (work, 4*ncolors) != ulong (4*ncolors))
        {
            b->release();
            return (errorn=XF_ERR_INVALIDPALETTE);
        }

        // Move to standard Van Gogh order color dwords RGBX.
        for (i = 0, ptr = (byte*)b->pal; i < ncolors; i++)
        {
            *(ptr++) = work[i*4+2];     // red
            *(ptr++) = work[i*4+1];     // green
            *(ptr++) = work[i*4];       // blue
            *(ptr++) = 0;               // na to make dword
        }

        b->clrinuse=ncolors-1;
    }
    else if (iheader.biBitCount == 1)
    {
        ncolors = (!iheader.biClrUsed) ? 2 : iheader.biClrUsed;

        // Skip palette entries
        if (xf->read (work, 4*ncolors) != ulong(4*ncolors))
        {
            b->release();
            return (errorn=XF_ERR_INVALIDPALETTE);
        }
        b->clrinuse=1;
    }

//��� Setup bitmap memory
    ulong size = (iheader.biBitCount == 1)
                 ? (((b->width + 7) >> 3) * b->height)
                 : (b->width * b->height * b->bpp);

    // Allocate memory
    b->handle = ivory_halloc(size);
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

//��� Load image data ���
    switch (iheader.biBitCount)
    {
        //�������������������������������������������������� 1 Bits per Pixel
        case 1:
            w = ((b->width+7) >> 3);

            for (ptr=b->data+(w*(b->height-1)), y=0;
                 y < b->height; y++, ptr -= w)
            {
                if (xf->read(ptr,w) != w)
                {
                    b->release();
                    return (errorn=XF_ERR_INVALIDIMAGE);
                }

                // Skip any padding
                i = (w & 0x3);
                if (i)
                {
                    if (xf->read(work,4-i) != ulong (4-i))
                    {
                        b->release();
                        return (errorn=XF_ERR_INVALIDIMAGE);
                    }
                }
            }
            break;

        //�������������������������������������������������� 4 Bits per Pixel
        case 4:
            if (!iheader.biCompression)
            {
                for(ptr=b->data+(b->width*(b->height-1)), y=0;
                    y < b->height; y++, ptr -= b->width)
                {

                    if (xf->read(ptr,(b->width+1)>>1) != ulong (b->width+1) >> 1)
                    {
                        b->release();
                        return (errorn=XF_ERR_INVALIDIMAGE);
                    }

                    // Expand nibbles into bytes
                    for (sptr=ptr+((b->width+1)>>1)-1, dptr=ptr+b->width-1, x=b->width;
                        x > 0;
                        x -= 2)
                    {
                        *(dptr--) = (byte) (*sptr & 0xf);
                        *(dptr--) = (byte) ((*(sptr--) & 0xf0) >> 4);
                    }

                    // Skip any padding
                    i = (((b->width+1)>>1) & 0x3);
                    if (i)
                    {
                        if (xf->read (work, 4-i) != ulong (4-i))
                        {
                            b->release();
                            return (errorn=XF_ERR_INVALIDIMAGE);
                        }
                    }
                }
            }
            else
            {
                // RLE 4-bit compression

                assertMyth("XFParseBMP::read",
                           iheader.biCompression == 2);

                for (y=0; y < b->height; y++)
                {
                    ptr=b->data+(b->width*(b->height-1-y));

                    for (j=0;;)
                    {
                        if (xf->read (work,2) != 2ul)
                        {
                            b->release();
                            return (errorn=XF_ERR_INVALIDIMAGE);
                        }

                        if (*work == 0)
                        {
                            if (*(work+1) == 0)
                            {
                                // End of row
                                break;
                            }
                            else if (*(work+1) == 1)
                            {
                                // End of bitmap
                                goto rle4_end;
                            }
                            else if (*(work+1) == 2)
                            {
                                // Position delta
                                b->release();
                                return (errorn=XF_ERR_NOTSUPPORTED);
                            }
                            else
                            {
                                // Literal group
                                i = *(work+1);

                                j += i;
                                if (j > b->width)
                                {
                                    b->release();
                                    return (errorn=XF_ERR_INVALIDIMAGE);
                                }

                                if (xf->read(ptr,(i+1) >> 1) != ulong (i+1) >> 1)
                                {
                                    b->release();
                                    return (errorn=XF_ERR_INVALIDIMAGE);
                                }

                                // Expand nibbles into bytes
                                for (sptr=ptr+((i+1)>>1)-1, dptr=ptr+i-1, x=i;
                                     x > 0;
                                     x -= 2)
                                {
                                    *(dptr--) = (byte) (*sptr & 0xf);
                                    *(dptr--) = (byte) ((*(sptr--) & 0xf0) >> 4);
                                }

                                ptr += i;

                                if (((i+1)>>1) & 0x1)
                                {
                                    if (xf->read(work,1) != 1ul)
                                    {
                                        b->release();
                                        return (errorn=XF_ERR_INVALIDIMAGE);
                                    }
                                }
                            }
                        }
                        else
                        {
                            // Repeat group
                            i = *work;

                            j += i;
                            if (j > b->width)
                            {
                                b->release();
                                return (errorn=XF_ERR_INVALIDIMAGE);
                            }

                            for(x=1; i > 0; i--)
                            {
                                if (x)
                                    *(ptr++) = (byte) ((*(work+1) & 0xf0) >> 4);
                                else
                                    *(ptr++) = (byte) (*(work+1) & 0xf);
                                x = !x;
                            }
                        }
                    }
                }
rle4_end:;
            }
            break;

        //�������������������������������������������������� 8 Bits per Pixel
        case 8:
            if (!iheader.biCompression)
            {
                for(ptr=b->data+(b->width*(b->height-1)), y=0;
                    y < b->height;
                    y++, ptr -= b->width)
                {
                    if (xf->read(ptr,b->width) != b->width)
                    {
                        b->release();
                        return (errorn=XF_ERR_INVALIDIMAGE);
                    }

                    // Skip any padding
                    i = ((b->width) & 0x3);
                    if (i)
                    {
                        if (xf->read(work,4-i) != ulong (4-i))
                        {
                            b->release();
                            return (errorn=XF_ERR_INVALIDIMAGE);
                        }
                    }
                }
            }
            else
            {
                // RLE 8-bit compression

                assertMyth("XFParseBMP::read",
                           iheader.biCompression == 1);

                for(y=0; y < b->height; y++)
                {
                    ptr=b->data+(b->width*(b->height-1-y));

                    for(j=0;;)
                    {
                        if (xf->read(work,2) != 2ul)
                        {
                            b->release();
                            return (errorn=XF_ERR_INVALIDIMAGE);
                        }

                        if (*work == 0)
                        {
                            if (*(work+1) == 0)
                            {
                                // End of row
                                break;
                            }
                            else if (*(work+1) == 1)
                            {
                                // End of bitmap
                                goto rle8_end;
                            }
                            else if (*(work+1) == 2)
                            {
                                // Position delta
                                b->release();
                                return (errorn=XF_ERR_NOTSUPPORTED);
                            }
                            else
                            {
                                // Literal group
                                i = *(work+1);

                                j += i;
                                if (j > b->width)
                                {
                                    b->release();
                                    return (errorn=XF_ERR_INVALIDIMAGE);
                                }

                                if (xf->read(ptr,i) != ulong (i))
                                {
                                    b->release();
                                    return (errorn=XF_ERR_INVALIDIMAGE);
                                }
                                ptr += i;

                                if (i & 0x1)
                                {
                                    if (xf->read(work,1) != 1ul)
                                    {
                                        b->release();
                                        return (errorn=XF_ERR_INVALIDIMAGE);
                                    }
                                }
                            }
                        }
                        else
                        {
                            // Repeat group
                            i = *work;

                            j += i;
                            if (j > b->width)
                            {
                                b->release();
                                return (errorn=XF_ERR_INVALIDIMAGE);
                            }

                            for(; i > 0; i--)
                            {
                                *(ptr++) = *(work+1);
                            }
                        }
                    }
                }
rle8_end:;
            }
            break;


        //������������������������������������������������� 16 Bits per Pixel
        case 16:
            w = b->width * 2;

            for (ptr=b->data+(w*(b->height-1)), y=0;
                 y < b->height; y++, ptr -= w)
            {

                if (xf->read(ptr,w) != w)
                {
                    b->release();
                    return (errorn=XF_ERR_INVALIDIMAGE);
                }

                // Skip any padding
                i = (w & 0x3);
                if (i)
                {
                    if (xf->read(work,4-i) != ulong (4-i))
                    {
                        b->release();
                        return (errorn=XF_ERR_INVALIDIMAGE);
                    }
                }
            }
            break;

        //������������������������������������������������� 24 Bits per Pixel
        case 24:
            w = b->width * 3;

            for (ptr=b->data+(w*(b->height-1)), y=0;
                 y < b->height; y++, ptr -= w)
            {

                if (xf->read(ptr,w) != w)
                {
                    b->release();
                    return (errorn=XF_ERR_INVALIDIMAGE);
                }

                // Skip any padding
                i = (w & 0x3);
                if (i)
                {
                    if (xf->read(work,4-i) != ulong (4-i))
                    {
                        b->release();
                        return (errorn=XF_ERR_INVALIDIMAGE);
                    }
                }

                // Swap BGR to RGB for line
                for(sptr=ptr, i=0; i < b->width; i++)
                {
                    x = *sptr;
                    *sptr = *(sptr+2);
                    sptr += 2;
                    *(sptr++) = (byte)x;
                }
            }
            break;
    }

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFParseBMP - write                                                       �
//                                                                          �
// Writes a BMP format bitmap to the file object.                           �
//                                                                          �
// Writes out as 8-bit or 24-bit image uncompressed.                        �
//���������������������������������������������������������������������������
xf_error_codes XFParseBMP::write(XFBitmap *b)
{
    int             i;
    int             y;
    int             w;
    byte            *sptr, *dptr, *ptr;
    byte            *tmp;
    ulong           headerpos;
    ulong           pos;
    int             locked=0;
    File_header     fheader;
    Info_header     iheader;
    byte            work[4*256];

    if (!b)
        b = bm;

//��� Check for unsupported formats ���
    if (!b->width || !b->height)
        return XF_ERR_NOTSUPPORTED;

    switch (b->bpp)
    {
        case XFBM_BPP_MONO:
        case XFBM_BPP_8BIT:
        case XFBM_BPP_15BIT:
        case XFBM_BPP_24BIT:
            break;
        default:
            return XF_ERR_NOTSUPPORTED;
    }

//��� Create/write file header ���
    // Save to later write out Size and OffBits...
    headerpos=xf->tell();
    memset(&fheader,0,sizeof(File_header));
    fheader.bfType[0]='B';
    fheader.bfType[1]='M';

    if (xf->write(&fheader,sizeof(File_header)) != sizeof(File_header))
    {
        errorn=xf->error();
        return errorn;
    }

//��� Create/write image header ���
    memset(&iheader,0,sizeof(Info_header));
    iheader.biSize=40;
    iheader.biWidth=(ulong)b->width;
    iheader.biHeight=(ulong)b->height;
    iheader.biPlanes=1;

    switch (b->bpp)
    {
        case XFBM_BPP_MONO:
            iheader.biBitCount = 1;
            break;
        case XFBM_BPP_8BIT:
            iheader.biBitCount = 8;
            break;
        case XFBM_BPP_15BIT:
            iheader.biBitCount = 16;
            break;
        case XFBM_BPP_24BIT:
            iheader.biBitCount = 24;
            break;
    }

                                            //��� Doesn't compress on output
    iheader.biCompression=0;

    if (xf->write(&iheader,sizeof(Info_header)) != sizeof(Info_header))
    {
        errorn=xf->error();
        return errorn;
    }

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

//��� Write out palette, if any ���
    if (iheader.biBitCount == 8)
    {
        if (!b->pal)
        {
            if (!locked)
                b->unlock();
            return (errorn=XF_ERR_INVALIDPALETTE);
        }

        for (i=0, ptr=(byte*)b->pal; i < 256; i++)
        {
             work[i*4+3] = 0;
             work[i*4+2] = *(ptr++);    // red
             work[i*4+1] = *(ptr++);    // green
             work[i*4]   = *(ptr++);    // blue
             ptr++;                     // na to make dword
        }

        if (xf->write(work,4*256) != 4*256)
        {
            if (!locked)
                b->unlock();
            errorn=xf->error();
            return errorn;
        }
    }
    else if (iheader.biBitCount == 1)
    {
        memset(work,0,8);
        work[4+2] = 255;
        work[4+1] = 255;
        work[4+0] = 255;

        if (xf->write(work,4*2) != 4*2)
        {
            if (!locked)
                b->unlock();
            errorn=xf->error();
            return errorn;
        }
    }

//��� Write out image ���
    if (!b->data)
    {
        if (!locked)
            b->unlock();
        return (errorn=XF_ERR_INVALIDIMAGE);
    }

    fheader.bfOffBits=xf->tell() - headerpos;

    work[0]=work[1]=work[2]=0;

    switch (iheader.biBitCount)
    {
        //�������������������������������������������������� 1 Bits per Pixel
        case 1:
            w = (b->width+7) >> 3;

            for(ptr=b->data+(w*(b->height-1)), y=0;
                y < b->height; y++, ptr -= w)
            {
                if (xf->write (ptr, w) != ulong (w))
                {
                    if (!locked)
                        b->unlock();
                    errorn=xf->error();
                    return errorn;
                }

                // Pad, if needed.
                i=(w & 0x3);
                if (i)
                {
                    if (xf->write(work,4-i) != ulong (4-i))
                    {
                        if (!locked)
                            b->unlock();
                        errorn=xf->error();
                        return errorn;
                    }

                }
            }
            break;

        //�������������������������������������������������� 8 Bits per Pixel
        case 8:
            for(ptr=b->data+(b->width*(b->height-1)), y=0;
                y < b->height; y++, ptr -= b->width)
            {

                if (xf->write(ptr,b->width) != b->width)
                {
                    if (!locked)
                        b->unlock();
                    errorn=xf->error();
                    return errorn;
                }

                // Pad, if needed.
                i=b->width & 0x3;
                if (i)
                {
                    if (xf->write(work,4-i) != ulong (4-i))
                    {
                        errorn=xf->error();
                        if (!locked)
                            b->unlock();
                        return errorn;
                    }
                }
            }
            break;


        //������������������������������������������������� 15 Bits per Pixel
        case 16:
            w= b->width*2;

            // If this doesn't work we will reorder to BRG.

            for(ptr=b->data+(w*(b->height-1)), y=0;
                y < b->height; y++, ptr -= w)
            {

                if (xf->write(ptr,w) != ulong(w))
                {
                    if (!locked)
                        b->unlock();
                    errorn=xf->error();
                    return errorn;
                }

                // Pad, if needed.
                i=b->width & 0x3;
                if (i)
                {
                    if (xf->write(work,4-i) != ulong (4-i))
                    {
                        errorn=xf->error();
                        if (!locked)
                            b->unlock();
                        return errorn;
                    }
                }
            }
            break;

        //������������������������������������������������� 24 Bits per Pixel
        case 24:
            w= b->width*3;

            tmp = new byte[w];
            if (!tmp)
                return XF_ERR_NOMEMORY;

            for(ptr=b->data+(w*(b->height-1)), y=0;
                y < b->height; y++, ptr -= w)
            {
                // Swap RGB to BGR for line
                for(sptr=ptr, dptr=tmp, i=0; i < b->width; i++)
                {
                    *(dptr++) = *(sptr+2);
                    *(dptr++) = *(sptr+1);
                    *(dptr++) = *(sptr);
                    sptr += 3;
                }

                if (xf->write (tmp, w) != ulong (w))
                {
                    if (!locked)
                        b->unlock();
                    errorn=xf->error();
                    delete [] tmp;
                    return errorn;
                }

                // Pad, if needed.
                i=(w & 0x3);
                if (i)
                {
                    if (xf->write(work,4-i) != ulong (4-i))
                    {
                        if (!locked)
                            b->unlock();
                        errorn=xf->error();
                        delete [] tmp;
                        return errorn;
                    }

                }
            }

            delete [] tmp;
            break;
    }

    if (!locked)
        b->unlock();

//��� Fix-up header ���
    pos=xf->tell();
    fheader.bfSize=pos-headerpos;
    xf->seek_set(headerpos);
    if (xf->write(&fheader,sizeof(File_header)) != sizeof(File_header))
    {
        errorn=xf->error();
        return errorn;
    }
    xf->seek_set(pos);

    return XF_ERR_NONE;
}

//��� End of module - xfbmp.cpp ���

