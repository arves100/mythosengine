//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//                   Ivory -- A Memory Management Library
//
//                     Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1994-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
// THE AUTHORS MAKE NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
// OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT.  THE AUTHORS
// PROVIDE THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
// LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
// OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
//                        http://www.mythos-engine.org/
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
// Created by Dan Higdon
//
// ivarcppc.cpp
//
// Ivory Allocation - Arena allocation routines for C++.
//
// These routines provide a C++ wrapper for the Ivory Arena allocation
// routines.  Note that there is no delete operator, since arena allocations
// are never deleted individually.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "ivory.h"
#include "ivory.hpp"

#include <malloc.h>
#include <memory.h>
#include <new.h>
#include <assert.h>


//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//  These are versions of the C++ new and delete operators, wired to
//  use the ivory arena routines.
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

void *operator new (size_t size, IvoryArena *arena)
{
    assertMyth("Ivory Arena operator new needs valid inputs",
                size > 0 && arena != 0);
    return ivory_arena_alloc (arena, size);
}

void *operator new (size_t size, IvorySubAlloc *suballoc)
{
    assertMyth("Ivory Sub Alloc operator new needs valid inputs",
                size > 0 && suballoc != 0);
    return ivory_sub_alloc (suballoc, size);
}

void operator delete (void* ptr, IvoryArena *arena)
{
    assertMyth("Ivory Arena operator delete needs valid inputs",
                ptr == NULL);
    delete (ptr);
}

void operator delete (void* ptr, IvorySubAlloc *suballoc)
{
    assertMyth("Ivory Sub Alloc operator delete needs valid inputs",
                ptr == NULL);
    delete(ptr);
}

#if 0
void *operator new [] (size_t size, IvoryArena *arena)
{
    return ivory_arena_alloc (arena, size);
}
#endif

//葦� End of module - ivarcpp.cpp 憶�
