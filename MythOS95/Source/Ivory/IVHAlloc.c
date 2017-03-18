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
// ivhalloc.c
//
// Ivory Handle Allocation - Relocatable block allocation.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <assert.h>

#include "ivory.h"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// Handle allocation routines.
//    For now, the memory is actually allocated with the standard routines.
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// ivory_halloc
//
// Allocate a block out of handle memory.
//���������������������������������������������������������������������������
IvoryHandle ivory_halloc (size_t size)
{
    assertMyth("ivory_halloc needs valid size", size > 0);

    return (IvoryHandle)GlobalAlloc (GMEM_MOVEABLE, size);
}


//���������������������������������������������������������������������������
// ivory_zhalloc
//
// Allocate and zero a block from handle memory.
//���������������������������������������������������������������������������
IvoryHandle ivory_zhalloc (size_t size)
{
    assert("ivory_zhalloc needs valid size", size > 0);

    return (IvoryHandle)GlobalAlloc (GHND, size);
}


//���������������������������������������������������������������������������
// ivory_hfree
//���������������������������������������������������������������������������
void ivory_hfree (IvoryHandle *ptr)
{
    assertMyth("ivory_hfree needs pointer to handle", ptr != 0);

    GlobalFree ((HANDLE)*ptr);

    *ptr = 0;
}


//���������������������������������������������������������������������������
// ivory_hlock
//
// Lock a block of memory, returning a handle to it.
//���������������������������������������������������������������������������
void *ivory_hlock (IvoryHandle h)
{
    assertMyth("ivory_hlock needs valid handle", h != 0);

    return GlobalLock ((HANDLE)h);
}


//���������������������������������������������������������������������������
// ivory_hunlock
//
// Unock a block of memory.
//���������������������������������������������������������������������������
void ivory_hunlock (IvoryHandle h)
{
    assertMyth("ivory_hunlock needs valid handle", h != 0);

    GlobalUnlock ((HANDLE)h);
}

//��� End of module - ivhalloc.c ���
