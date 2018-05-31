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
// bachmisc.hpp
//
// BachSampleSequencer - plays a series of static samples in order
//
//���������������������������������������������������������������������������

#ifndef __BACHMISC_HPP
#define __BACHMISC_HPP    1

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <dsound.h>

//��� Charybdis headers
#include <debug.h>
#include <portable.h>
#include <ivory.hpp>
#include <xfile.hpp>

//�������������������������������������������������������������������������Ŀ
// Bach Library Includes                                                    �
//���������������������������������������������������������������������������
#include "bachdefs.h"
#include "bachdigi.hpp"

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// BachSampleSequencer - plays a series of static samples in order.         �
//���������������������������������������������������������������������������
class BachSampleSequencer
{
    // For storing the samples to sequence
    struct Link
    {
        BachStaticSample    *sample;
        Link                *next;

        Link (BachStaticSample *_sample, Link *_next = 0):
            sample (_sample), next (_next) { }
    };

    //���������������������������������������������������������������������Ŀ
    // Protected data members                                               �
    //�����������������������������������������������������������������������
    HANDLE                  thread_handle;
    CRITICAL_SECTION        critical_section;
    HANDLE                  thread_event;

    Link                    *sequence;

    //���������������������������������������������������������������������Ŀ
    // Internal routines                                                    �
    //�����������������������������������������������������������������������
    static DWORD CALLBACK   thread_proc (LPVOID);

    // We cannot allow copying because of the critical section
    BachSampleSequencer (BachSampleSequencer const &);
    BachSampleSequencer &operator= (BachSampleSequencer const &);

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members.                                                 �
    //�����������������������������������������������������������������������
    dword   flags;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructor                                               �
    //�����������������������������������������������������������������������
    BachSampleSequencer ();
    virtual ~BachSampleSequencer ();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������

    //��� Free all associated memory
    virtual void release();

    //��� Initializes class
    bach_err_codes init();

    //��� Sample management
    bach_err_codes add (BachStaticSample *sample, int start_play=1);
    BachStaticSample *next ();
    bach_err_codes play();
    void stop(int stop_current=1);

    //��� Information about the sequence
    BachStaticSample *current () const { return (sequence) ? sequence->sample : 0; }
    ulong get_playtime ();
};

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//��� End of header - bachmisc.hpp ���
