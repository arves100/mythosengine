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
//                          *** Tester Application ***
//
// Created by Chuck Walbourn
//
// xtmain.cpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <ivory.hpp>

#include "xfile.hpp"

using namespace std; 

//���������������������������������������������������������������������������
//
//                               Routines
//
//���������������������������������������������������������������������������

void low_level(void);
void buffer(void);
void ram(void);
void ini(void);
void iff(void);
void bitmap(void);

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// print_error                                                              �
//���������������������������������������������������������������������������
void print_error(char *s)
{
    cout.flush();
    printf("���� Error %x %s\n",xf_error(),s);
}

void print_error(class XFile *xf, char *s)
{
    cout.flush();
    printf("���� Error %x %s\n",xf->error(),s);
}

void print_error(class XFParseINI *xp, char *s)
{
    cout.flush();
    printf("���� Error %x %s\n",xp->error(),s);
}

void print_error(class XFParseBitmap *bp, char *s)
{
    cout.flush();
    printf("���� Error %x %s\n",bp->error(),s);
}

void print_error(class XFParseIFF *xp, char *s)
{
    cout.flush();
    printf("���� Error %x %s\n",xp->error(),s);
}


//�������������������������������������������������������������������������Ŀ
// main                                                                     �
//                                                                          �
//     Entry point for the test program for XFile.                          �
//���������������������������������������������������������������������������
void main(int argc, char *argv[])
{
    IvorySystem ivory;

//���� Print welcome banner ����
    cout << "�� XFile Tester - (C) 1994-1999 by D. Higdon, T. Little, and C. Walbourn ��\n"
            "                  Subject to terms of MIT License "  __DATE__ "\n";

    if (argc > 1
        && (*argv[1] == '/' || *argv[1] == '-')
        && argv[1][1] == '?')
    {

        cout << "   Usage:  xt [l | u | r | i | b | f]\n";
        cout << "           l = Low-level file tests\n";
        cout << "           u = Buffered file tests\n";
        cout << "           r = RAM file tests\n";
        cout << "           i = INI file tests\n";
        cout << "           b = Bitmap file tests\n";
        cout << "           f = IFF file tests\n";
        return;
    }

//���� Perform file tests ����

    if (argc < 2 || *argv[1] == 'L' || *argv[1] == 'l')
    {
       low_level();
    }

    if (argc < 2 || *argv[1] == 'U' || *argv[1] == 'u')
    {
       buffer();
    }

    if (argc < 2 || *argv[1] == 'R' || *argv[1] == 'r')
    {
       ram();
    }

    if (argc < 2 || *argv[1] == 'I' || *argv[1] == 'i')
    {
       ini();
    }
    if (argc < 2 || *argv[1] == 'B' || *argv[1] == 'b')
    {
       bitmap();
    }
    if (argc < 2 || *argv[1] == 'F' || *argv[1] == 'f')
    {
       iff();
    }
}


//���������������������������������������������������������������������������
// _charybdis_assert
//
// Handler for failed asserts.  If msg is set to non-NULL, then an assertMyth
// was used with a comment.
//���������������������������������������������������������������������������
extern "C" void _charybdis_assert(char *msg, char *exp, char *f, unsigned ln)
{
    cout.flush();
    printf("\n\n��� Assertion Failed ����������������������������������\n"
           "Expr:\t%s\n"
           "File:\t%s\t\tLine %d\n",exp,f,ln);
    if (msg)
    {
        printf("Comment:\n%s\n",msg);
    }

    exit(1);
}

// A support function (usually provided by MythosSystem)
extern "C" int mythos_atexit( register void ( *__func )( void ) )
{
    return atexit (__func);
}

// Make sure it uses the correct calling convention!
#ifdef __WATCOMC__
#pragma aux (_ASMSTKCALL_) mythos_atexit;
#endif

//��� End of module - xtmain.cpp ���
