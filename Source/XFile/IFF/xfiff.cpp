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
// xfiff.cpp
//
// The XFParseIFF object provides reading and writing of the Electronic Arts
// 'IFF' file format.  FORMs are supported, but CATs and LISTs are ignored.
//
// If the control flag has XF_IFF_RIFF set, then 'RIFF' is used instead
// of 'FORM' and the sizes are in Intel rather than Motorola format.
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
// XFParseIFF - Contructor for the .INI object.                             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
XFParseIFF::XFParseIFF(dword cf) :
    cflags(cf)
{
    xf=&xfile;
    initvars();
}

XFParseIFF::XFParseIFF(XFile *f, dword cf) :
    cflags(cf),
    xf(f)
{
    initvars();
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFParseIFF - Destructor for the .INI object.                             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
XFParseIFF::~XFParseIFF()
{
    end();
};



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFParseIFF - begin                                                       �
//                                                                          �
// Sets up for processing of the .IFF file.                                 �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFParseIFF::begin(void)
{
    char           buff[8];

    if (!(xf->status() & (XF_OPEN_READ|XF_OPEN_WRITE)))
    {
        errorn=XF_ERR_NEEDREADORWRITE;
        return errorn;
    }

//陳� Get initial file statistics 陳�
    icurPos=xf->tell();
    ilength=xf->getsize();

//陳� Check for IFF chunk-based file if non-zero length 陳�
    if (ilength)
    {
        //陳� Read first id/size pair
        if (xf->read(buff,8) != 8)
        {
            goto invalid_iff;
        }

        //陳� Check id is in valid IFF range
        if ((buff[0] < 0x20 || buff[0] > 0x7e)
            || (buff[1] < 0x20 || buff[1] > 0x7e)
            || (buff[2] < 0x20 || buff[2] > 0x7e)
            || (buff[3] < 0x20 || buff[3] > 0x7e))
        {
            goto invalid_iff;
        }

        //陳� See if size exceeds size of file
        if (((ulong) ((cflags & XF_IFF_RIFF)
                      ? *((dword *)&buff[4])
                      : swapendian(*((dword *)&buff[4]))) + 8) > ilength)
        {
            goto invalid_iff;
        }

        //陳� Reset to start of file
        xf->seek_set(icurPos);
    }

//陳� return success 陳�
    return XF_ERR_NONE;

//陳� invalid IFF 陳�
invalid_iff: ;
    errorn=XF_ERR_NOTIFF;
    return errorn;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFParseIFF - end                                                         �
//                                                                          �
// End processing of the .IFF file.                                         �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFParseIFF::end(void)
{
    xf_error_codes err;

//陳� Must leave all open forms to ensure sizes are correct 陳�
    if (xf->status() & XF_STATUS_WRITE)
    {
        leaveform();
        while (idepth)
            leaveform();
    }

//陳� Reset internal state 陳�
    initvars();

//陳� Flush the filehandle 陳�
    err=xf->flush();
    if (err)
        errorn=err;

    return err;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFParseIFF - leaveform                                                   �
//                                                                          �
// Leaves the current form context.                                         �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFParseIFF::leaveform(void)
{
    ulong   w;
    XFForm  *f;
    char    buff[4];

    if (idepth > 0)
    {

//陳� If FORM is dirty, must update file's FORM size count 陳�
        f=&iforms[idepth-1];

        if (f->flags & XF_IFFFORM_DIRTY)
        {

            *((dword *)&buff[0]) = (ulong)
                      ((cflags & XF_IFF_RIFF)
                       ? (f->len+4)
                       : swapendian(f->len+4));

            xf->seek_set(f->start-8);
            w=xf->write(buff,4);

            if (w != 4)
            {
                xf->seek_set(icurPos);
                errorn=xf->error();
                return errorn;
            }
        }

//陳� Set current position to end of form 陳�
        w = f->start+f->len+((f->len & 0x1 & !(cflags & XF_IFF_NOPAD)) ? 1 : 0);
        icurPos=w;
        if (xf->seek_set(w) != w)
        {
            errorn=xf->error();
            return errorn;
        }

//陳� Reduce depth 陳�
        idepth--;
        depth = idepth;

//陳� Clear current chunk 陳�
        ichunkSize=0;
        chunkid=0;
        formid=(idepth) ? iforms[idepth-1].id : 0;
    }

    return XF_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFParseIFF - next                                                        �
//                                                                          �
// Moves the file to the next data block in the current form (or whole file �
// if no current form).                                                     �
//                                                                          �
// Returns 0 or error condition.                                            �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFParseIFF::next(void)
{
    char    buff[8];

//陳� If chunkSize internal set, then skip previous unread chunk 陳�
    if (ichunkSize)
    {

        // Handle odd-byte padding
        if (ichunkSize & 0x1
            && !(cflags & XF_IFF_NOPAD))
            ichunkSize++;

        icurPos = xf->seek_cur(ichunkSize);
        ichunkSize=0;
    }

//陳� Check for EOF 陳�
    if ( (!idepth && icurPos >= ilength)
        || (idepth && (icurPos - iforms[idepth-1].start) >= iforms[idepth-1].len) )
    {
        chunkid=0;
        errorn=XF_ERR_EOF;
        return errorn;
    }

//陳� Read current chunk id/size pair 陳�
    if (xf->read(buff,8) != 8)
    {
        errorn=XF_ERR_UNEXPECTEDEOF;
        xf->seek_set(icurPos);
        return errorn;
    }

//陳� Check id is in valid IFF range 陳�
    if ((buff[0] < 0x20 || buff[0] > 0x7e)
        || (buff[1] < 0x20 || buff[1] > 0x7e)
        || (buff[2] < 0x20 || buff[2] > 0x7e)
        || (buff[3] < 0x20 || buff[3] > 0x7e))
    {
        errorn=XF_ERR_INVALIDID;
        xf->seek_set(icurPos);
        return errorn;
    }
    chunkid = *((dword *)&buff[0]);

    icurPos += 8;

//陳� Get chunk size 陳�
    chunkSize = ichunkSize = (ulong)
                    ((cflags & XF_IFF_RIFF)
                     ? *((dword *)&buff[4])
                     : swapendian(*((dword *)&buff[4])));

//陳� Handle FORM/RIFF 陳�
    if (chunkid == ((cflags & XF_IFF_RIFF)
                    ? makeid('R','I','F','F')
                    : makeid('F','O','R','M')))
    {

        if ((ichunkSize < 4)
            || (xf->read(buff,4) != 4))
        {
            errorn=XF_ERR_TRUNCATEDCHUNK;
            return errorn;
        }

        xf->seek_set(icurPos);
        formid = *((dword *)&buff[0]);
    }

#if 0
//陳� Check for chunk size too large for context 陳�
    if ( (!idepth && ((ichunkSize + icurPos) > ilength))
         || (idepth && ((ichunkSize +
             (icurPos - iforms[idepth-1].start)) > iforms[idepth-1].len)))
    {
        ichunkSize = (len-icurPos);
        errorn=XF_ERR_TRUNCATEDCHUNK;
        return errorn;
    }
#endif

    return XF_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// XFParseIFF - topofcontext                                                �
//                                                                          �
// Moves the pointer to the top of the current context.                     �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
xf_error_codes XFParseIFF::topofcontext(int donext)
{
    ichunkSize=0;

    if (!idepth)
    {
        icurPos = xf->seek_set(0);
    }
    else
    {
        icurPos = xf->seek_set(iforms[idepth-1].start);
    }

    if (!donext)
        return XF_ERR_NONE;

    return next();
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                           旭� Private 旭�                                �
// XFParseIFF - initvars                                                    �
//                                                                          �
// Sets the internal private members to initial values.                     �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void XFParseIFF::initvars(void)
{
    idepth=0;
    ichunkSize=0;
    depth=0;
    formid=0;
    chunkid=0;
    chunkSize=0;
}

//葦� End of module - xfiff.cpp 憶�

