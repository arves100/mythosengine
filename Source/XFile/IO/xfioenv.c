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
// Ported to Windows by Dan Higdon
//
// xfioenv.c
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
//                               Routines
//
//���������������������������������������������������������������������������

char *getenv(const char *varname);
void _searchenv(const char *, const char *, char *);

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// char *xf_getenv(const char *varname);                                    �
//                                                                          �
// Returns a pointer to the environment string for the variable name.       �
//���������������������������������������������������������������������������
char *xf_getenv(const char *varname)
{
    return getenv(varname);
}


//�������������������������������������������������������������������������Ŀ
// xf_searchenv                                                             �
//                                                                          �
// Searchings the directories given in environment variable and the current �
// working directory for the file.                                          �
//���������������������������������������������������������������������������
char *xf_searchenv(const char *filename, const char *env_var, char *path)
{
    _searchenv(filename,env_var,path);
    return path;
}

//��� End of module - xfioenv.c ���

