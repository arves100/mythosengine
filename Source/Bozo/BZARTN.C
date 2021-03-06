//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//                oooooooooo.
//                `888'   `Y8b
//                 888     888  .ooooo.    oooooooo  .ooooo.
//                 888oooo888' d88' `88b  d'""7d8P  d88' `88b
//                 888    `88b 888   888    .d8P'   888   888
//                 888    .88P 888   888  .d8P'  .P 888   888
//                o888bood8P'  `Y8bod8P' d8888888P  `Y8bod8P'
//                           _
//                          /_\     |    _  _ | _ ._
//                         /   \  \_||_|(_|(_||(/_|
//                                       _| _|
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
// Coroutine
//
//      Bozo routine support.  This module provides the low-level
//  support required by Bozo's cooperative tasking system.  These
//  primitives should not be called directly by the application, but rather
//  provide building blocks for the tasking system.  These routines are
//  the implementation-specific parts of Bozo.  All other tasking
//  routines are implemented with these.
//
//  The two routines provided encapsulate the concept of the task portably
//  by using the ANSI-standard C routines setjmp() and longjmp().
//  corout()    fills a jmp_buf with implementation-dependent values so
//              that a long_jmp() with the buffer will switch the task
//              to execute the passed function on the passed stack.
//  swap()      saves the currently executing task into one buffer, and
//              "returns" into the second task.  When a task is switched
//              into, it appears to return from the swap() call.
//
//  Implementation note:
//      The purely setjmp/longjmp based code has been largely supplanted
//  by our own, "lean and mean" setjmp/longjmp routines.  These routines
//  don't even pretend to save the entire context; they only save the
//  registers that Watcom expects not to be trashed by a called routine.
//  In particular, the segment registers are neither saved nor restored,
//  giving us much faster context switching time.
//  Also, a small hack has been introduced to allow Bozo to work in
//  a register-calling environment.  See the code for information.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
#include <bozo.h>

#include <stdlib.h>
#include <portable.h>
#include "bzartn.h"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Structures
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Routines
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

// Imported routines from bzjump.asm

int bz_setjmp (int *);
void bz_longjmp (int *);


//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  Make jb refer to the entrypoint of pfn, with pstack as the              �
//  execution stack.  Thus, pfn can be invoked as longjmp (pjb, 1);         �
//  Note that this is the only implementation specific routine              �
//  in this library, assuming that setjmp and longjmp work properly.        �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void bz_corout (bz_context *ctxt, void (*pfn) (void *), char *pstack, int stack_size, void (*rtn) (void), void *param)
{
    // Adjust to point to the end of the stack
    pstack += stack_size;

    // Encode the user-defined parameter (assumes stack calling)
    pstack -= sizeof (param);
    *(void **)pstack = param;

    // Encode the rtn address as the return address
    // (This always goes on the stack!)
    pstack -= sizeof (rtn);
    *(void (**) (void))pstack = rtn;

    // Make sure that there is a dummy entry on the stack,
    // because we need to be "returning" from somewhere
    pstack -= sizeof (int);

    ctxt->jb[0] =       // esi
    ctxt->jb[1] =       // edi
    ctxt->jb[2] = 0;    // ebx
    ctxt->jb[3] =               // ebp
    ctxt->jb[4] = (int)pstack;  // esp
    ctxt->jb[5] = (int)pfn;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  Jump from 'from' to 'to'                                                �
//  Although this is not really implementation specific, it does            �
//  encapsulate the use of setjmp/longjmp, in case we need to replace       �
//  this implementation on hardware that has a bad set/longjmp.             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void bz_swap (bz_context *from, bz_context *to)
{
    if (from == NULL || bz_setjmp (from->jb) == 0)
    {
        bz_longjmp (to->jb);
    }
}

//葦� End of file - bzartn.c 憶�
