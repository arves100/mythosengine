//���������������������������������������������������������������������������
//           __ ,
//            ,-| ~           ,               ,,
//           ('||/__,        ||               ||                  _
//          (( |||  | \\ \\ =||=   _-_  \\/\\ ||/|,  _-_  ,._-_  / \\
//          (( |||==| || ||  ||   || \\ || || || || || \\  ||   || ||
//           ( / |  , || ||  ||   ||/   || || || |' ||/    ||   || ||
//            -____/  \\/\\  \\,  \\,/  \\ \\ \\/   \\,/   \\,  \\_-|
//                                                               /  \
//                                                              '----`
//                     Text Output and Font Management System
//                       Microsoft Windows 95/98/NT Version
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
// Created by Chuck Walbourn
//
// gbrgfile.hpp
//
// Header for file structures
//
//���������������������������������������������������������������������������

#ifndef __GBRGFILE_HPP
#define __GBRGFILE_HPP   1

#ifdef __WATCOMC__
#pragma pack(1);
#endif

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "gutenbrg.h"

//���������������������������������������������������������������������������
//
//                               Structures
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// FORM 'GFNT' - Font IFF form.                                             �
//���������������������������������������������������������������������������

//�� 'HDR ' - Header
struct GBergFileFontHDR {
    char                name[GBERG_MAX_NAME];   // Name
    ushort              width;                  // Size, if fixed
    ushort              height;
    ushort              bpc;                    // Bytes/character
    ushort              type;                   // Type
    byte                compression;            // 0=none
    char                na[7];
};

//�������������������������������������������������������������������������Ŀ
// FORM 'GTXT' - String IFF form.                                           �
//���������������������������������������������������������������������������

//�� 'HDR ' - Header
struct GBergFileTextHDR {
    char                name[GBERG_MAX_NAME];   // Name
    ulong               number_of_strings;      // Count of strings
    byte                compression;            // 0=none
    char                na[11];
};

//�� 'AUTH' - Author

//�� 'DESC' - Description

//�� '(C) ' - Copyright line

//�� 'BODY' - String buffer

#ifdef __WATCOMC__
#pragma pack();
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//��� End of header - gbrgfile.hpp ���
