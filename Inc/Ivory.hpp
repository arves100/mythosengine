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
// Ivory.hpp
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
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

#ifndef __IVORY_HPP
#define __IVORY_HPP 1

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// Basically the same as the "C" version, but with a few helpers
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

#include "ivory.h"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                 Types
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  Ivory System object
//      This class initalizes Ivory, and provides members for
//      unusual allocation requests.  Most allocation requests should
//      still be processed through operator new, and its variants.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class IvorySystem
{
public:
            IvorySystem (dword size = 2*1024*1024, ivory_init_codes opt = IVORY_RESERVE_STATIC)
                                            { ivory_initialize (size, opt); }
            ~IvorySystem ()                 { ivory_terminate (); }

        // Handle based allocation
IvoryHandle halloc  (size_t s)          { return ivory_halloc (s); }
IvoryHandle zhalloc (size_t s)          { return ivory_zhalloc (s); }
void        hfree   (IvoryHandle *ph)   { ivory_hfree (ph); }
void        *hlock  (IvoryHandle h)     { return ivory_hlock (h); }
void        hunlock (IvoryHandle h)     { ivory_hunlock (h); }

        // Arena creation/management.  Use 'new (arena) type' to allocate.
        // Where possible, use the IvoryNewArena template.
IvoryArena  *arena_initialize   (IvoryArena *a, size_t s)   { return ivory_arena_initialize (a, s); }
void        arena_clear         (IvoryArena *a)             { ivory_arena_clear (a); }
int         arena_chainlength   (const IvoryArena *a)       { return ivory_arena_chainlength (a); }

};


//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Templates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  ivory_hdup
//      This template duplicates a given object as a handle of one or more
//      copies of the original object.
//      Using this template function, the user is guaranteed that the the
//      allocated handle is initialized appropriately.
//      This function is not inline, so only one copy will be generated per
//      instantiation.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
template <class T>
IvoryHandle ivory_hdup (const T &t, int size)
{
    IvoryHandle h = ivory_halloc (sizeof (T) * size);
    T *p = (T *)ivory_hlock (h);

    // Copy the object into every slot
    while (size--)
        *p++ = t;

    ivory_hunlock (h);

    return h;
}

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  This template class encapsulates the arena type.
//      Since the size of an arena is part of its basic creation type,
//      this is a template.  The bytes allocated come after the IvoryArena
//      base type, and basically make this whole object the arena.
//      We allocation one fewer bytes than requested because the IvoryArena
//      type contains a single byte at the end.  This way, we will always
//      get at least as many bytes as we need, possibly more depending
//      on the structure padding used.
//      Note that an instance of this type may be passed in to the
//      operator new, just like an IvoryArena pointer.
//      (And for the skeptical, I checked the generated code, and it's
//       just as tight as the other method, and more typesafe!)
//      As with any arena, make sure it is cleared before you delete it,
//      especially if you "forget" that it's not an IvoryArena.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
template <int arena_size>
class IvoryNewArena: public IvoryArena
{
        char    bytes[arena_size - 1];

public:
        IvoryNewArena ()    { ivory_arena_initialize (this, arena_size); }
        ~IvoryNewArena ()   { clear(); }

void    clear ()        { ivory_arena_clear (this); }
int     chainlength()   { return ivory_arena_chainlength (this); }
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// This template class provides a handy method of locking a handle to
// a structure.  Types locked _must_ be classes or structures.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
template <class T>
class IvoryLock
{
        IvoryHandle h;
        T           *ptr;

public:
        IvoryLock (IvoryHandle _h): h (_h), ptr ((T *)ivory_hlock (_h))  { }
        ~IvoryLock ()       { ivory_hunlock (h); }

        T &operator * ()    { return *ptr; }
        T *operator -> ()   { return ptr;  }
};


//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                             Inline Functions
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�


void *operator new (size_t size, IvoryArena *arena);
void *operator new (size_t size, IvorySubAlloc *arena);
void operator delete (void* ptr, IvoryArena* arena);
void operator delete (void* ptr, IvorySubAlloc* arena);

#include "ivory.ipp"

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//葦� End of header - ivory.hpp 憶�
