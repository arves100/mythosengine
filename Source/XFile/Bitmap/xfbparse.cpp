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
// xfbparse.cpp
//
// Contains the code for the XFParseBitmap base class.
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
// XFParseBitmap - Constructor                                              �
//���������������������������������������������������������������������������
XFParseBitmap::XFParseBitmap()
{
    xf=&xfile;
    bm=&bitmap;
}

XFParseBitmap::XFParseBitmap(XFile *f) :
    xf(f)
{
    bm=&bitmap;
}

XFParseBitmap::XFParseBitmap(XFBitmap *b) :
    bm(b)
{
    xf=&xfile;
}

XFParseBitmap::XFParseBitmap(XFile *f, XFBitmap *b) :
    xf(f),
    bm(b)
{
}


//�������������������������������������������������������������������������Ŀ
// XFParseBitmap - Destructor                                               �
//���������������������������������������������������������������������������
XFParseBitmap::~XFParseBitmap()
{
    xf->close();
}



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFParseBitmap - nameread                                                 �
//                                                                          �
// Opens the XFile object and then calls virtual member.                    �
//���������������������������������������������������������������������������
xf_error_codes XFParseBitmap::nameread(const char *name, XFBitmap *b)
{
    xf_error_codes error;

    if (!b)
        b = bm;

    b->release();

    error=xf->open(name,XF_OPEN_READ);
    if (error)
    {
        errorn=error;
        return error;
    }

    error=read(b);

    xf->close();

    return error;
}


//�������������������������������������������������������������������������Ŀ
// XFParseBitmap - namewrite                                                �
//                                                                          �
// Opens the XFile object and then calls virtual member.                    �
//���������������������������������������������������������������������������
xf_error_codes XFParseBitmap::namewrite(const char *name, XFBitmap *b)
{
    xf_error_codes error;

    error=xf->open(name,XF_OPEN_WRITE|XF_OPEN_CREATE);
    if (error)
    {
        errorn=error;
        return error;
    }

    error=write(b);

    xf->close();

    return error;
}

//��� End of module - xfbparse.cpp ���
