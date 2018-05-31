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
// xfifform.cpp
//
// This contains the form-based movement for the XFParseIFF object.
//
// If the control flag has XF_IFF_RIFF set, then 'RIFF' is used instead
// of 'FORM' and the sizes are in Intel rather than Motorola format.
//
// (leaveform is in the main module since it is always called by
//  the end() function).
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
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFParseIFF - seekform                                                    �
//                                                                          �
// Scans the current form-level for the given form id.  If found, then the  �
// form is the current chunk.  If not found, then the current position is   �
// at the end of the current form.                                          �
//                                                                          �
// Returns 0 or error condition.                                            �
//���������������������������������������������������������������������������
xf_error_codes XFParseIFF::seekform(dword id)
{
    while(!next())
    {
        if (chunkid == ((cflags & XF_IFF_RIFF)
                        ? makeid('R','I','F','F')
                        : makeid('F','O','R','M'))
             && formid==id)
            return XF_ERR_NONE;
    }

    return XF_ERR_FORMNOTFOUND;
}


//�������������������������������������������������������������������������Ŀ
// XFParseIFF - newform                                                     �
//                                                                          �
// Creates a new form and enters it.                                        �
//                                                                          �
// Returns 0 or error condition.                                            �
//���������������������������������������������������������������������������
xf_error_codes XFParseIFF::newform(dword id)
{
    ulong   i;
    ulong   w;
    XFForm  *f;
    char    buff[12];

//��� Check to see if we are in the middle of a form/chunk (overwrite
//��� not current allowed).

    if (chunkid)
    {
        errorn=XF_ERR_WRITENOTALLOWED;
        return errorn;
    }

//��� Make sure that FORM is not used as the FORM's id ���
    if (id == ((cflags & XF_IFF_RIFF)
               ? makeid('R','I','F','F')
               : makeid('F','O','R','M')))
    {
        errorn=XF_ERR_INVALIDID;
        return errorn;
    }

//��� If too deep, error ���
    if (idepth+1 >= XF_MAX_IFFDEPTH)
    {
        errorn=XF_ERR_MAXDEPTHREACHED;
        return errorn;
    }

//��� Write FORM empty entry (will be filled in later on leaveform()) ���
    *((dword *)&buff[0]) = (cflags & XF_IFF_RIFF)
                            ? makeid('R','I','F','F')
                            : makeid('F','O','R','M');
    *((dword *)&buff[4]) = 4;
    *((dword *)&buff[8]) = id;
    w=xf->write(buff,12);
    icurPos += 12;
    if (w == -1)
    {
        errorn=xf->error();
        return errorn;
    }

//��� Must set previous depths to DIRTY and increase size by 12
    for(i=idepth; i > 0; i--)
    {
        iforms[i-1].flags |= XF_IFFFORM_DIRTY;
        iforms[i-1].len += 12;
    }

//��� Setup context structure (array index is idepth-1 with 0 being full file)
    f=&iforms[idepth++];
    depth=idepth;

    f->id = id;
    f->flags = 0;
    f->start = icurPos;
    f->len = 0;

//��� Clear data in context ���
    formid = id;
    ichunkSize=0;
    chunkid=0;

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFParseIFF - enterform                                                   �
//                                                                          �
// Enters the current FORM chunk, if any.                                   �
//                                                                          �
// Returns 0 or error condition.                                            �
//���������������������������������������������������������������������������
xf_error_codes XFParseIFF::enterform(void)
{
    XFForm  *f;
    char    buff[4];

//��� Make sure current chunk is an enterable form ���
    if (chunkid != ((cflags & XF_IFF_RIFF)
                    ? makeid('R','I','F','F')
                    : makeid('F','O','R','M')))
    {
        errorn=XF_ERR_INVALIDFORCHUNK;
        return errorn;
    }

//��� If too deep, error ���
    if (idepth+1 >= XF_MAX_IFFDEPTH)
    {
        errorn=XF_ERR_MAXDEPTHREACHED;
        return errorn;
    }

//��� Read FORM id ���
    if ((ichunkSize < 4)
        || (xf->read(buff,4) != 4))
    {
        errorn=XF_ERR_TRUNCATEDCHUNK;
        return errorn;
    }
    formid = *((dword *)&buff[0]);
    icurPos += 4;

//��� Setup context structure (array index is idepth-1 with 0 being full file)

    f=&iforms[idepth++];
    depth=idepth;

    f->id = formid;
    f->flags = 0;
    f->start = icurPos;
    f->len = ichunkSize - 4;

//��� Clear data in context ���
    ichunkSize=0;
    chunkid=0;

    return XF_ERR_NONE;
}

//��� End of module - xfifform.cpp ���

