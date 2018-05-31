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
// xfiff.cpp
//
// The XFParseIFF object provides reading and writing of the Electronic Arts
// 'IFF' file format.  FORMs are supported, but CATs and LISTs are ignored.
//
// If the control flag has XF_IFF_RIFF set, then 'RIFF' is used instead
// of 'FORM' and the sizes are in Intel rather than Motorola format.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "xfile.hpp"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFParseIFF - Contructor for the .INI object.                             �
//���������������������������������������������������������������������������
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


//�������������������������������������������������������������������������Ŀ
// XFParseIFF - Destructor for the .INI object.                             �
//���������������������������������������������������������������������������
XFParseIFF::~XFParseIFF()
{
    end();
};



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFParseIFF - begin                                                       �
//                                                                          �
// Sets up for processing of the .IFF file.                                 �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseIFF::begin(void)
{
    char           buff[8];

    if (!(xf->status() & (XF_OPEN_READ|XF_OPEN_WRITE)))
    {
        errorn=XF_ERR_NEEDREADORWRITE;
        return errorn;
    }

//��� Get initial file statistics ���
    icurPos=xf->tell();
    ilength=xf->getsize();

//��� Check for IFF chunk-based file if non-zero length ���
    if (ilength)
    {
        //��� Read first id/size pair
        if (xf->read(buff,8) != 8)
        {
            goto invalid_iff;
        }

        //��� Check id is in valid IFF range
        if ((buff[0] < 0x20 || buff[0] > 0x7e)
            || (buff[1] < 0x20 || buff[1] > 0x7e)
            || (buff[2] < 0x20 || buff[2] > 0x7e)
            || (buff[3] < 0x20 || buff[3] > 0x7e))
        {
            goto invalid_iff;
        }

        //��� See if size exceeds size of file
        if (((ulong) ((cflags & XF_IFF_RIFF)
                      ? *((dword *)&buff[4])
                      : swapendian(*((dword *)&buff[4]))) + 8) > ilength)
        {
            goto invalid_iff;
        }

        //��� Reset to start of file
        xf->seek_set(icurPos);
    }

//��� return success ���
    return XF_ERR_NONE;

//��� invalid IFF ���
invalid_iff: ;
    errorn=XF_ERR_NOTIFF;
    return errorn;
}


//�������������������������������������������������������������������������Ŀ
// XFParseIFF - end                                                         �
//                                                                          �
// End processing of the .IFF file.                                         �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseIFF::end(void)
{
    xf_error_codes err;

//��� Must leave all open forms to ensure sizes are correct ���
    if (xf->status() & XF_STATUS_WRITE)
    {
        leaveform();
        while (idepth)
            leaveform();
    }

//��� Reset internal state ���
    initvars();

//��� Flush the filehandle ���
    err=xf->flush();
    if (err)
        errorn=err;

    return err;
}


//�������������������������������������������������������������������������Ŀ
// XFParseIFF - leaveform                                                   �
//                                                                          �
// Leaves the current form context.                                         �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseIFF::leaveform(void)
{
    ulong   w;
    XFForm  *f;
    char    buff[4];

    if (idepth > 0)
    {

//��� If FORM is dirty, must update file's FORM size count ���
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

//��� Set current position to end of form ���
        w = f->start+f->len+((f->len & 0x1 & !(cflags & XF_IFF_NOPAD)) ? 1 : 0);
        icurPos=w;
        if (xf->seek_set(w) != w)
        {
            errorn=xf->error();
            return errorn;
        }

//��� Reduce depth ���
        idepth--;
        depth = idepth;

//��� Clear current chunk ���
        ichunkSize=0;
        chunkid=0;
        formid=(idepth) ? iforms[idepth-1].id : 0;
    }

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFParseIFF - next                                                        �
//                                                                          �
// Moves the file to the next data block in the current form (or whole file �
// if no current form).                                                     �
//                                                                          �
// Returns 0 or error condition.                                            �
//���������������������������������������������������������������������������
xf_error_codes XFParseIFF::next(void)
{
    char    buff[8];

//��� If chunkSize internal set, then skip previous unread chunk ���
    if (ichunkSize)
    {

        // Handle odd-byte padding
        if (ichunkSize & 0x1
            && !(cflags & XF_IFF_NOPAD))
            ichunkSize++;

        icurPos = xf->seek_cur(ichunkSize);
        ichunkSize=0;
    }

//��� Check for EOF ���
    if ( (!idepth && icurPos >= ilength)
        || (idepth && (icurPos - iforms[idepth-1].start) >= iforms[idepth-1].len) )
    {
        chunkid=0;
        errorn=XF_ERR_EOF;
        return errorn;
    }

//��� Read current chunk id/size pair ���
    if (xf->read(buff,8) != 8)
    {
        errorn=XF_ERR_UNEXPECTEDEOF;
        xf->seek_set(icurPos);
        return errorn;
    }

//��� Check id is in valid IFF range ���
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

//��� Get chunk size ���
    chunkSize = ichunkSize = (ulong)
                    ((cflags & XF_IFF_RIFF)
                     ? *((dword *)&buff[4])
                     : swapendian(*((dword *)&buff[4])));

//��� Handle FORM/RIFF ���
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
//��� Check for chunk size too large for context ���
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


//�������������������������������������������������������������������������Ŀ
// XFParseIFF - topofcontext                                                �
//                                                                          �
// Moves the pointer to the top of the current context.                     �
//���������������������������������������������������������������������������
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


//�������������������������������������������������������������������������Ŀ
//                           ��� Private ���                                �
// XFParseIFF - initvars                                                    �
//                                                                          �
// Sets the internal private members to initial values.                     �
//���������������������������������������������������������������������������
void XFParseIFF::initvars(void)
{
    idepth=0;
    ichunkSize=0;
    depth=0;
    formid=0;
    chunkid=0;
    chunkSize=0;
}

//��� End of module - xfiff.cpp ���

