//���������������������������������������������������������������������������
//
//                   Ivory -- A Memory Management Library
//
//                     Microsoft Windows 95/98/NT Version
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
// Created by Dan Higdon
//
// ivallcpp.cpp
//
// Ivory Allocation - Primary allocation routines for C++.
//
//      These routines provide a simple operator replacement for the
//  C++ memory allocation routines.  These routines call the standard
//  memory allocation routines found in IVALLOC.C
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <malloc.h>
#include <assert.h>
#include <xstddef>
#include <new>

#include "ivory.hpp"

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

extern "C" void *main_memory;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//  These are versions of the C++ new and delete operators, wired to
//  use the ivory routines when ivory has been initialized.
//
//���������������������������������������������������������������������������

#if 0
void * __CRTDECL operator new (size_t size) _THROW1(std::bad_alloc)
{
    assertMyth("Ivory operator new needs valid size", size > 0);
    if (main_memory)
        return ivory_alloc (size);
    else
        return malloc (size);
}

void __CRTDECL operator delete (void *ptr) _THROW0()
{
    assertMyth("Ivory operator delete needs valid pointer", ptr != 0);
    if (main_memory)
        ivory_free (&ptr);
    else
        free (ptr);
}
#endif

//��� End of module - ivallcpp.cpp ���
