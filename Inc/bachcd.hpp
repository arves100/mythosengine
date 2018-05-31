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
// bachcd.hpp
//
// BachCD - CD Audio controller class
//
//���������������������������������������������������������������������������

#ifndef __BACHCD_HPP
#define __BACHCD_HPP    1

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <mmsystem.h>

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

//�������������������������������������������������������������������������Ŀ
// BachCD - CD Audio control object.                                        �
//���������������������������������������������������������������������������
class BachCD
{
public:
    //���������������������������������������������������������������������Ŀ
    // Public data members.                                                 �
    //�����������������������������������������������������������������������
    ulong   devid;                          // Device ID
    dword   flags;                          // Flags

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructor                                               �
    //�����������������������������������������������������������������������
    BachCD();
    virtual ~BachCD();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual bach_err_codes init (ulong id=0);
    virtual void close ();

    virtual bach_err_codes play (ulong sms=0, ulong ems=0);
    virtual bach_err_codes stop ();
    virtual bach_err_codes pause();
    virtual bach_err_codes resume();
    virtual dword status() const;

    virtual bach_err_codes eject();
    virtual bach_err_codes retract();

    virtual bach_err_codes set_track(ulong ntrack);
    virtual bach_err_codes set_position(ulong ms);

    //���������������������������������������������������������������������Ŀ
    // Utility functions.                                                   �
    //�����������������������������������������������������������������������
    ulong get_track() const;
    ulong get_position() const;

    ulong get_num_tracks() const;
    bach_err_codes get_track_info(ulong ntrack, ulong &sms, ulong &ems) const;

    void set_flags(dword f) { flags = f; }
};

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//��� End of header - bachcd.hpp ���
