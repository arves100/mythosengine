//���������������������������������������������������������������������������
//
//                        ����������                       ����
//     ��Ŀ                ���     ���                     ����
//     �  �       ��Ŀ     ���     ���   ����      �����    ��� ���
//     �  � ��Ŀ  �  �     �����������  �  ���    ���   ��  ��������
//     �  � �  �  �  �     ���     ���  �������  ���        ���   ���
//    O� O� �  �  �  �     ���     ��� ���  ���  ���    ��  ���   ���
//          �  � O� O�    �����������   ��������  �������  ����� �����
//         O� O�
//                            C++ Music, Sound, and Effects Library
//                               Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1995-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
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
// Created by Dan Higdon & Chuck Walbourn
//
// bachmus.hpp
//
// BachSequence - Music container class
//
// BachMusic - Music sound source class
//
//���������������������������������������������������������������������������

#ifndef __BACHMUS_HPP
#define __BACHMUS_HPP    1

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <dmusicc.h>
#include <dmusici.h>

//��� Charybdis headers
#include <debug.h>
#include <portable.h>
#include <ivory.hpp>
#include <xfile.hpp>

//�������������������������������������������������������������������������Ŀ
// Bach Library Includes                                                    �
//���������������������������������������������������������������������������
#include "bachdefs.h"

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

class BachMusic;
class BachDigital;

//�������������������������������������������������������������������������Ŀ
// BachSequence - Music container class.                                    �
//���������������������������������������������������������������������������
class BachSequence
{
public:
    //���������������������������������������������������������������������Ŀ
    // Public data members.                                                 �
    //�����������������������������������������������������������������������
    IDirectMusicPerformance *perf;          // DirectMusic performance object
    IDirectMusicLoader      *loader;        // DirectMusic loader object
    IDirectMusicSegment     *segment;       // DirectMusic segement object

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructor                                               �
    //�����������������������������������������������������������������������
    BachSequence(BachMusic *mus);
    virtual ~BachSequence();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void release();

    virtual bach_err_codes play (long start=0);
    virtual bach_err_codes queue (long start=0);
    virtual bach_err_codes stop ();
    virtual dword status() const;

    bach_err_codes set_repeats(ulong count=0);
    bach_err_codes set_loop_points(long start, long end);

    //���������������������������������������������������������������������Ŀ
    // Utility functions.                                                   �
    //�����������������������������������������������������������������������
    long get_length() const;

    bach_err_codes load_mid(const char *fname);
};


//�������������������������������������������������������������������������Ŀ
// BachMusic - Music sound source class.                                    �
//���������������������������������������������������������������������������
class BachMusic
{
public:
    //���������������������������������������������������������������������Ŀ
    // Public data members.                                                 �
    //�����������������������������������������������������������������������
    IDirectMusic            *dmusic;        // DirectMusic object
    IDirectMusicPort        *port;          // DirectMusic port object
    IDirectMusicPerformance *perf;          // DirectMusic performance object
    IDirectMusicLoader      *loader;        // DirectMusic loader object

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructor                                               �
    //�����������������������������������������������������������������������
    BachMusic();
    virtual ~BachMusic();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual bach_err_codes init (BachDigital *digi, HWND hwnd,
                                 DWORD effects=DMUS_EFFECT_NONE);
    virtual void close ();

    //���������������������������������������������������������������������Ŀ
    // Utility functions.                                                   �
    //�����������������������������������������������������������������������
    bach_err_codes activate();
    bach_err_codes deactivate();
};

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//��� End of header - bachmus.hpp ���

