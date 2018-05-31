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
// Ivory.ipp
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

#ifndef __IVORY_IPP
#define __IVORY_IPP 1

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������


//���������������������������������������������������������������������������
//
//                                                         Inline Functions
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// Arena allocation inlines
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
//      ivory_arena_alloc                                                                                                               �
//              Allocate a block from the provided arena.                                                       �
//              For an Assembly interface, provide similar functionality in a macro.�
//���������������������������������������������������������������������������
inline void *ivory_arena_alloc (IvoryArena *arena, size_t size)
{
    if (arena->current + size <= arena->end)
    {
        void *ptr = arena->current;
        arena->current += size;
        return ptr;
    }
    else
        return ivory_arena_alloc_internal (arena, size);
}

#endif

//��� End of header - ivory.hpp ���
