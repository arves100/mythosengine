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
// Ivory.h
//
//              Ivory provides a malloc-style memory allocation library.
//      Ivory allows the programmer to allocate memory either from a global
//      pool (like malloc), or to allocate chunks from a special arena.
//      Arena allocations may be rapidly freed by freeing the arena, or
//      by re-initializing the arena's internal pointers.  As you may have
//      guessed, the arena may be allocated with the global allocation routines.
//      The provided lock functions lock the pages of the given memory areas
//      until they are unlocked.
//
//���������������������������������������������������������������������������

#ifndef __IVORY_H
#define __IVORY_H 1

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif

#include <platform.h>

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <portable.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

//#include "ivmem.h"

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// Define for ivory_initialize()
//���������������������������������������������������������������������������
#define IVORY_HANDLESPACE_PERCENT   50

//���������������������������������������������������������������������������
//
//                                 Types
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// Error codes for the ivory error handler
//���������������������������������������������������������������������������
enum _ivory_error_codes
{
    IVORY_NO_ERROR      = 0,
    IVORY_CORRUPT_CHAIN = 1
};

typedef enum _ivory_error_codes ivory_error_codes;


//���������������������������������������������������������������������������
//  Initialization values for ivory_initialize.
//���������������������������������������������������������������������������
enum _ivory_init_codes
{
    IVORY_RESERVE_HANDLE = 0,   // SIZE == handle space to allocate
    IVORY_RESERVE_STATIC = 1,   // SIZE == standard allocation space to reserve
    IVORY_RESERVE_PERCENT = 2   // SIZE == percent to allocate for handles
};

typedef enum _ivory_init_codes ivory_init_codes;


//���������������������������������������������������������������������������
// The type of the handler function
//���������������������������������������������������������������������������
typedef void (*ivory_error_handler) (ivory_error_codes);

//���������������������������������������������������������������������������
// The actual Handle type returned by the Handle based allocation routines.
//���������������������������������������������������������������������������
#ifdef __IMPLEMENT_HANDLES__
typedef ulong IvoryHandle;
#else
typedef void *IvoryHandle;
#endif

//���������������������������������������������������������������������������
//
//                               Structures
//
//���������������������������������������������������������������������������


//���������������������������������������������������������������������������
// This defines an internal structure used to manage unallocated memory
// blocks in the standard and sub allocation routines.
// There is no reason for an application to use this structure.
//���������������������������������������������������������������������������
typedef struct _AllocationHeader AllocationHeader;
struct _AllocationHeader
{
    AllocationHeader    *next;
    dword               size;
    dword               padding[2]; // Forces 16 byte size, so data aligns
};

// This macro computes the end address of a block of memory described
// by the AllocationHeader.
#define end_of(ph) ((AllocationHeader *)((byte *)(ph) + (ph)->size))



//���������������������������������������������������������������������������
// This defines the inner structure of an allocation arena.  There is no
// constructor, since this struct breaks the C++ rule of knowing how
// large something is at compile time.  This struct sits at the beginning
// of an arbitrarily large block.
//���������������������������������������������������������������������������
typedef struct _IvoryArena IvoryArena;
struct _IvoryArena
{
    IvoryArena          *next;      // Link to next block in arena chain
    char                *current;   // Points to unused bytes
    char                *end;       // Points to the end of this block
    size_t              size;       // Size of this block in bytes
    char                data[1];    // This is a placeholder
};


//���������������������������������������������������������������������������
//  This defines the metric information kept by the Ivory memory allocator.
//  This data is really just the header of an internal structure
//���������������������������������������������������������������������������
typedef struct _IvoryInfo IvoryInfo;
struct _IvoryInfo
{
    ulong       memory_size;
    ulong       allocation_count;
    ulong       free_count;
    ulong       memory_alloced;
};


//���������������������������������������������������������������������������
//  This type defines the SubAllocation header.  None of these fields
//  are for public use, but the struct is provided here so that you can
//  take its size (useful when deciding how much RAM you'll need in a buffer).
//���������������������������������������������������������������������������
typedef struct _IvorySubAlloc IvorySubAlloc;
struct _IvorySubAlloc
{
    // These fields are identical to the IvoryInfo structure
    ulong   memory_size;
    ulong   allocation_count;
    ulong   free_count;
    ulong   memory_alloced;

    // These fields extend the structure
    AllocationHeader    *freelist;
    byte                *next_free;
    byte                wildspace_start;
};


//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������


//���������������������������������������������������������������������������
//
//                               Prototypes
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// The Initialization and termination routines
//���������������������������������������������������������������������������
void ivory_initialize (size_t, ivory_init_codes);
void ivory_terminate ();
void ivory_getinfo (IvoryInfo *);
void ivory_sethandler (ivory_error_handler);
void ivory_default_handler (ivory_error_codes);

//���������������������������������������������������������������������������
// Global space functions
//���������������������������������������������������������������������������
void *ivory_alloc  (size_t);
void *ivory_zalloc (size_t);
void ivory_free    (void **);

//���������������������������������������������������������������������������
// Handle space functions
//���������������������������������������������������������������������������
#ifdef __IMPLEMENT_HANDLES__

IvoryHandle ivory_halloc (size_t);
IvoryHandle ivory_zhalloc(size_t);
void ivory_hfree   (IvoryHandle *);
void *ivory_hlock  (IvoryHandle);
void ivory_hunlock (IvoryHandle);

#else

// Just wrap up malloc for efficieny's sake.
#define ivory_halloc(siz) malloc (siz)
#define ivory_zhalloc(siz) memset (malloc (siz), 0, siz)
#define ivory_hfree(handp) (free (*handp), *handp=0)
#define ivory_hlock(hand) (hand)
#define ivory_hunlock(hand)

#endif

//���������������������������������������������������������������������������
// Arena space functions
//���������������������������������������������������������������������������
#ifdef __cplusplus
void *ivory_arena_alloc (IvoryArena *arena, size_t size);
#else
#define ivory_arena_alloc ivory_arena_alloc_internal
#endif

IvoryArena *ivory_arena_initialize (IvoryArena *arena, size_t arena_size);
void ivory_arena_clear (IvoryArena *arena);
int  ivory_arena_chainlength (const IvoryArena *arena);
void *ivory_arena_zalloc(IvoryArena *arena, size_t size);
void *ivory_arena_alloc_internal (IvoryArena *arena, size_t size);

//���������������������������������������������������������������������������
// Sub allocation functions
//���������������������������������������������������������������������������
void ivory_sub_initialize (IvorySubAlloc *, size_t);
void ivory_sub_terminate (IvorySubAlloc *);
void *ivory_sub_alloc (IvorySubAlloc *, size_t);
void *ivory_sub_zalloc (IvorySubAlloc *, size_t);
void ivory_sub_free (IvorySubAlloc *, void **);


#ifdef __cplusplus
}
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//��� End of header - ivory.hpp ���
