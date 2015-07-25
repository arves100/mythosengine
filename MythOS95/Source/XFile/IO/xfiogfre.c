//���������������������������������������������������������������������������
//                            
//           ^           **   **   **** ***** *    ****     ^      Take me to
//          (_)            * *     *      *   *    *       (_)    / your
//     ^                    *      **     *   *    **            ^  leader...
//    (_)       ^          * *     *      *   *    *            (_)
//             (_)       **   **   *    ***** **** ****
//
//            Copyright (c) 1994-1997 by Charybdis Enterprises, Inc.
//                              All Rights Reserved.
//                        Microsoft Windows '95 Version
//
//���������������������������������������������������������������������������
//
//           *** Charybdis Enterprises, Inc. Company Confidential ***
//
//  This file and all associated files are the company proprietary property
//        of Charybdis Enterprises, Inc.  Unauthorized use prohibited.
//
// CHARYBDIS ENTERPRISES, INC. MAKES NO WARRANTIES, EXPRESS OR IMPLIED, AS
// TO THE CORRECTNESS OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE
// IT.  CHARYBDIS ENTERPRISES, INC. PROVIDES THE CODE ON AN "AS-IS" BASIS
// AND EXPLICITLY DISCLAIMS ANY LIABILITY, INCLUDING CONSEQUENTIAL AND
// INCIDENTAL DAMAGES FOR ERRORS, OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//���������������������������������������������������������������������������
//
// Created by Chuck Walbourn
// Ported to Windows by Dan Higdon
//
// xfiogfre.c
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//                                
//���������������������������������������������������������������������������

#include "xfio.h"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ulong xf_getfreebytes(char drive);                                       �
//                                                                          �
// Gets the number of free bytes on the disk for the given drive letter.    �
// If 'drive' is 0, then the default drive is checked.                      �
//                                                                          �
// Returns the number of free bytes or -1 if error.                         �
//���������������������������������������������������������������������������
ulong xf_getfreebytes (char drive)
{
    DWORD   dwSectorsPerCluster;
    DWORD   dwBytesPerSector;
    DWORD   dwFreeClusters;
    DWORD   dwClusters;
    TCHAR   path[4];

    path[0] = drive;
    path[1] = ':';
    path[2] = '\\';
    path[3] = '\0';

    if (GetDiskFreeSpace (path,
                          &dwSectorsPerCluster,
                          &dwBytesPerSector,
                          &dwFreeClusters,
                          &dwClusters))
        return dwFreeClusters * dwSectorsPerCluster * dwBytesPerSector;

    return (word)-1;
}

//��� End of module - xfiogfre.c ���
