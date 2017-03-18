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
// ivmfc.c
//
// Ivory Allocation - Primary allocation routines.
//
// This is an MFC-friendly version of the IvoryAllocation routines.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <malloc.h>
#include <assert.h>

#include "ivory.h"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//��������������������������������������������������������������������������
// ivory_initialize
//
// Initialize the global memory arena.  Must be called first.
//��������������������������������������������������������������������������
void ivory_initialize (size_t mem_size, ivory_init_codes opt)
{
    // This function does nothing in this implementation;
    (void)mem_size;
    (void)opt;
}


//��������������������������������������������������������������������������
// ivory_terminate
//
// Free all ivory-allocated resources and shut down the library.
//��������������������������������������������������������������������������
void ivory_terminate ()
{
    // This function does nothing in this implementation;
}


//��������������������������������������������������������������������������
// ivory_alloc
//
// Allocate a block out of main memory.
//��������������������������������������������������������������������������
void *ivory_alloc (size_t size)
{
    assertMyth("ivory_alloc (MFC version) needs valid size", size > 0);
    return malloc (size);
}


//��������������������������������������������������������������������������
// ivory_zalloc
//
// Allocate and zero a block from standard memory.
//��������������������������������������������������������������������������
void *ivory_zalloc (size_t size)
{
    void *ptr;

    assertMyth("ivory_zalloc (MFC version) needs valid size", size > 0);

    ptr = ivory_alloc (size);
    if (!ptr)
        return 0;

    memset (ptr, 0, size);
    return ptr;
}


//��������������������������������������������������������������������������
// ivory_free
//��������������������������������������������������������������������������
void ivory_free (void **ptr)
{
    assertMyth("ivory_free (MFC version) needs valid pointer", ptr != 0 && *ptr != 0);

    free (*ptr);
    *ptr = 0;
}

//��� End of module - ivmfc.c ���
