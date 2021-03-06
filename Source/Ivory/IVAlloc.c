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
// ivalloc.c
//
// Ivory Allocation - Primary allocation routines.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "ivory.h"

#include <windows.h>
#include <assert.h>


//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

// This is the size of a single page of memory.  It MUST be a power of 2!
#define PAGE_SIZE  (4096*4)
#define PAGE_MASK  (~(PAGE_SIZE-1))

static const char BLOCK_GUARD[16] = { " El Chupacabra " };
static const char FREE_GUARD[16]  = { " No es mi Perro" };

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Structures
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// The extended information structure
//  (This is the same as the Internal allocation structure!)
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
typedef IvorySubAlloc InternalIvoryInfo;

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Routines
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// A routine to construct a dword from two words
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
#define MAKEDWORD(a,b) ((((dword)a) << 16) | (b))

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
//  Find the greatest common divisor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
static int gcd (int, int);

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// This is the pointer to the main memory buffer
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
InternalIvoryInfo   *main_memory;

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// ivory_initialize
//
// Initialize the global memory arena.  Must be called first.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
void ivory_initialize (size_t mem_size, ivory_init_codes opt)
{
    MEMORY_BASIC_INFORMATION    mem;
    MEMORYSTATUS memstat;

//陳� No need to initialize this twice!
    if (main_memory)
        return;

    switch (opt)
    {
        case IVORY_RESERVE_HANDLE:
            memstat.dwLength = sizeof (memstat);
            GlobalMemoryStatus (&memstat);
            mem_size = memstat.dwAvailVirtual - mem_size;
            break;

        case IVORY_RESERVE_STATIC:
            // No change
            break;

        case IVORY_RESERVE_PERCENT:
            memstat.dwLength = sizeof (memstat);
            GlobalMemoryStatus (&memstat);
            mem_size = memstat.dwAvailPhys * 100 / mem_size;
            break;
    }

    assertMyth("ivory_initialize needs valid memory size",
               mem_size >= 4096);

    if (mem_size < 4096)
        return;

//陳� Get the block required to store the requested allocations
#if 1
    main_memory = VirtualAlloc (NULL, mem_size, MEM_RESERVE, PAGE_READWRITE);
#else
    main_memory = VirtualAlloc (NULL, mem_size, MEM_COMMIT, PAGE_READWRITE);
#endif
    assertMyth("ivory_initialize couldn't get memory from VirtualAlloc",
               main_memory != 0);

//陳� Find out how much actually got allocated
    VirtualQuery (main_memory, &mem, sizeof (mem));
    mem_size = mem.RegionSize;

#if 1
    VirtualAlloc (main_memory, sizeof (*main_memory), MEM_COMMIT, PAGE_READWRITE);
#endif

//陳� Once we have the block, set up the allocation header
//陳� Fill in the "public" fields
    main_memory->memory_size = mem_size - sizeof (*main_memory);

//陳� Initialize the counters
    main_memory->allocation_count = 0;
    main_memory->free_count = 0;
    main_memory->memory_alloced = 0;

//陳� Now, the internal fields (memory is allocated from the top)
    main_memory->next_free = (byte *)main_memory + mem_size - sizeof (AllocationHeader);
    main_memory->freelist = 0;

//陳� Lastly, we must manually lock the top of memory, since by the above
//陳� calculation, we have effectively allocated sizeof(AllocationHeader)
//陳� bytes already!
    VirtualAlloc ((void *)((dword)main_memory->next_free & PAGE_MASK), PAGE_SIZE,
                  MEM_COMMIT, PAGE_READWRITE);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// ivory_terminate
//
// Free all ivory-allocated resources and shut down the library.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
void ivory_terminate ()
{
    if (main_memory)
    {
#ifndef NDEBUG
        if (main_memory->allocation_count != main_memory->free_count)
        {
            char txt[32];
            wsprintf (txt, "alloc count off by %d",
                      main_memory->allocation_count - main_memory->free_count);
            assertMyth (txt, 0);
        }

        if (main_memory->memory_alloced != 0)
        {
            char txt[32];
            wsprintf (txt, "%d left allocated",
                      main_memory->memory_alloced);
            assertMyth (txt, 0);
        }
#endif

        //陳� Free the block we allocated.
        VirtualFree (main_memory, 0, MEM_RELEASE);
        main_memory = NULL;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// ivory_alloc
//
// Allocate a block out of main memory.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
void *ivory_alloc (size_t size)
{
    AllocationHeader    **pph, *ph;
    size_t              alloc_size;

    assertMyth("ivory_alloc must be called after ivory_initialize",
               main_memory != 0);

    assertMyth("ivory_alloc needs valid size", size > 0);

//陳� Now, make sure there is room for the AllocationHeader, and
//陳� then round the size to the nearest (greater) 16 byte alignment
#ifdef DEBUG
    size += 32;   // Make room for border dwords
#endif

    alloc_size  = size + sizeof (AllocationHeader) + 0x0f;
    alloc_size &= ~0x0f;

//陳� First, scan the free list to see if we can find a suitable block
//陳� Will this be fast enough, with the double pointer scheme?
    pph = &main_memory->freelist;
    ph  = main_memory->freelist;

    while (ph && ph->size < alloc_size)
    {
        pph = &ph->next;

        assert(ph != ph->next);
        ph  = ph->next;
    }

//陳� If we have found a suitable block....
    if (ph)
    {
        //陳� If this block is large enough to split, do so
        //陳� (Needs at least as enough extra space to hold 16 bytes!)
        if (ph->size > alloc_size + sizeof (AllocationHeader) + 16)
        {
            // Remove our block from the end, so as to preserve the chain.
            ph->size -= alloc_size;
            ph = (AllocationHeader *)((char *)ph + ph->size);
        }
        //陳� Otherwise, claim it as our own by overwriting
        //陳� whatever pointed to it.
        else
            *pph = ph->next;
    }
    else
    {
        //陳� Allocate a new block from the unused memory

        //陳� If there isn't enough memory....
        if (main_memory->next_free < &main_memory->wildspace_start + alloc_size)
        {
            // Expand the block?
            return 0;
        }
        else
        {
            //陳� Otherwise, take as much as we need (but no more!)

            //陳� Get the top and bottom page pointers, rounded down and up respectively
            dword top_page    = (dword)main_memory->next_free & PAGE_MASK;
            dword bottom_page = (dword)(main_memory->next_free - alloc_size) & PAGE_MASK;

            //陳� Commit and lock the memory if we need to.
            if (top_page > bottom_page)
            {
                VirtualAlloc ((void *)bottom_page, top_page - bottom_page,
                              MEM_COMMIT, PAGE_READWRITE);
            }

            //陳� Allocate the memory from wildspace
            main_memory->next_free -= alloc_size;
            ph = (AllocationHeader *)main_memory->next_free;
        }
    }

//陳� Now, 'ph' points to a usable chunk of memory.
    assert (ph != 0);
    ph->size = alloc_size;
    ph->next = 0;

//陳� Now, return the area past the buffer (our user's memory)
    main_memory->allocation_count++;
    main_memory->memory_alloced += alloc_size;

//陳� Make sure the block actually contains as many bytes as we want!
//陳� (Testing by protfault! :-)
#ifdef DEBUG
    memset (ph+1, 0, size);
    {
        byte *pdata = (byte *)(ph + 1);

        memcpy (pdata, BLOCK_GUARD, 16);
        memcpy (pdata + alloc_size - 16 - sizeof (AllocationHeader), BLOCK_GUARD, 16);

        return pdata + 16;
    }
#else

    return ph + 1;
#endif
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// ivory_zalloc
//
// Allocate and zero a block from standard memory.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
void *ivory_zalloc (size_t size)
{
    void *ptr = ivory_alloc (size);

    assertMyth("ivory_zalloc needs valid size", size > 0);
    if (!ptr)
        return 0;

    memset (ptr, 0, size);
    return ptr;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// ivory_free
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
void ivory_free (void **ptr)
{
    AllocationHeader *freeblk, *prevprev, *prevblk, *nextblk;

    assertMyth("ivory_alloc must be called after ivory_initialize",
               main_memory != 0);

    assertMyth("ivory_free needs valid pointer", ptr != 0 && *ptr != 0);

//陳� Make sure this is our pointer!
    assertMyth ("ivory_free given pointer not in Ivory's memory range",
                *ptr > (void *)main_memory);
    assertMyth ("ivory_free given pointer not in Ivory's memory range",
                (*ptr < (void *)(((char *)main_memory) + main_memory->memory_size)));

//陳� Get a pointer to the header info in front of this block
#ifdef DEBUG
    {
        byte *pdata = ((byte *)*ptr) - 16;
        freeblk = (AllocationHeader *)pdata;
        freeblk--;

        assert (memcmp (pdata, FREE_GUARD, 16) != 0);
        assert (memcmp (pdata, BLOCK_GUARD, 16) == 0);
        assert (memcmp (pdata + freeblk->size - 16 - sizeof (AllocationHeader), BLOCK_GUARD, 16) == 0);

        // Mark this block as freed already
        memcpy (pdata, FREE_GUARD, 16);
    }

#else
    freeblk = (AllocationHeader *)*ptr;
    freeblk--;

#endif

//陳� Record the free for statistical purposes
    main_memory->memory_alloced -= freeblk->size;
    main_memory->free_count++;

//陳� Scan until we are past all free blocks lower in memory than
//陳� ourselves.  This is the most expensive part of this deallocator.
//陳� Note: the '== 0' case is ok, since 0 is not greater than anything!
    prevprev  = prevblk = 0;
    nextblk   = main_memory->freelist;
    while (nextblk > freeblk)
    {
        prevprev = prevblk;
        prevblk  = nextblk;
        nextblk  = nextblk->next;
    }

    assertMyth("ivory_free told to free memory already in free list",
               nextblk != freeblk);

//陳� Now, we have either a point in the list to add our link, or
//陳� the end of the list.
//陳� 'ph2' points to the link we want to point to our
//陳� free region, and prevblk points to the block containing
//陳� that pointer.
    assert ((prevblk == 0 && nextblk == main_memory->freelist) ||
            (prevblk != 0 && prevblk->next == nextblk));
    assert (prevprev == 0 || prevprev->next == prevblk);

//陳� If the next block is adjacent, merge.  Otherwise chain it.
    if (nextblk)
    {
        if (freeblk == end_of (nextblk))
        {
            nextblk->size += freeblk->size;
            freeblk = nextblk;
        }
        else
            freeblk->next = nextblk;
    }
#ifdef DEBUG
    else
    {
        assert (freeblk->next == 0);
    }
#endif

//陳� At this point, we know that....
    assert (freeblk == nextblk ||       // We have merged, or
            freeblk->next == nextblk);  // we are linked in.

//陳� If there's a previous block, and it's adjacent, eat our block
    if (prevblk)
    {
        if (prevblk == end_of (freeblk))
        {
            freeblk->size += prevblk->size;

            //陳� Patch our pointer, which is the freelist head if there is no previous block
            if (prevprev)
                prevprev->next = freeblk;
            else
                main_memory->freelist = freeblk;

            //陳� Back up our previous block pointer for the next step
            prevblk = prevprev;
        }
        //陳� Otherwise, put our block into place
        else
            prevblk->next = freeblk;
    }
    //陳� Otherwise, set this as the first block
    else
        main_memory->freelist = freeblk;

//陳� If our block is now the last thing in memory, return it to wildspace
    if (freeblk == (AllocationHeader *)main_memory->next_free)
    {
        int freesize = freeblk->size;

#if 1
        //陳� Unlock and decommit the memory.  We guarantee that
        //陳� everything below next_free-BLKSIZE inclusive is decommitted.
        //陳� So, we need to decommit any pages between the partial pages
        //陳� at the top and bottom.

        //陳� Get the top and bottom page pointers, rounded down and up respectively
        dword bottom_page = ((dword)freeblk + PAGE_SIZE-1) & PAGE_MASK;
        dword top_page    = ((dword)freeblk + freesize) & PAGE_MASK;

        if (top_page > bottom_page)
        {
            VirtualFree ((void *)bottom_page, top_page - bottom_page, MEM_DECOMMIT);
        }
#endif

        main_memory->next_free += freesize;

        //陳� Make sure that we no longer point at this memory.
        if (prevblk)
            prevblk->next = 0;
        else
            main_memory->freelist = 0;
    }

//陳� Lastly, zero out the pointer so we don't get into trouble later
    *ptr = 0;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
// gcd
//
// Find the greatest common divisor of the two numbers.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳
static int gcd (int i, int j)
{
    assert (i != 0);
    assert (j != 0);

//陳� The classic algorithm
    while (i != j)
    {
        if (i > j)
            i -= j;
        else
            j -= i;
    }

//陳� Either i or j will work, since they are equal
    return i;
}

//葦� End of module - ivalloc.c 憶�
