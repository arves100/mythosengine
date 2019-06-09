//���������������������������������������������������������������������������
//
//                               Debug Header
//
//              Copyright (c) 1994-1998 by Charybdis Enterprises, Inc.
//                            All Rights Reserved.
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
// Standard Debug Header
//
//      Contains various switches for debugging purposes.
//
//���������������������������������������������������������������������������

#ifndef __DEBUG_H
#define __DEBUG_H  1

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

#ifdef DEBUG
#define STATIC 
#else
#define STATIC static
#endif

#endif

//��� End of header - debug.h ���
