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
// ivalloc.c
//
// Ivory Allocation - Primary allocation routines.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "ivory.h"

#include <windows.h>
#include <assert.h>


//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

// This is the size of a single page of memory.  It MUST be a power of 2!
#define PAGE_SIZE  (4096*4)
#define PAGE_MASK  (~(PAGE_SIZE-1))

static const char BLOCK_GUARD[16] = { " El Chupacabra " };
static const char FREE_GUARD[16]  = { " No es mi Perro" };

//���������������������������������������������������������������������������
//
//                               Structures
//
//���������������������������������������������������������������������������

//��������������������������������������������������������������������������
// The extended information structure
//  (This is the same as the Internal allocation structure!)
//��������������������������������������������������������������������������
typedef IvorySubAlloc InternalIvoryInfo;

//���������������������������������������������������������������������������
//
//                               Routines
//
//���������������������������������������������������������������������������

//��������������������������������������������������������������������������
// A routine to construct a dword from two words
//��������������������������������������������������������������������������
#define MAKEDWORD(a,b) ((((dword)a) << 16) | (b))

//��������������������������������������������������������������������������
//  Find the greatest common divisor
//��������������������������������������������������������������������������
static int gcd (int, int);

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

//��������������������������������������������������������������������������
// This is the pointer to the main memory buffer
//��������������������������������������������������������������������������
InternalIvoryInfo   *main_memory;

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
    MEMORY_BASIC_INFORMATION    mem;
    MEMORYSTATUS memstat;

//��� No need to initialize this twice!
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

//��� Get the block required to store the requested allocations
#if 1
    main_memory = VirtualAlloc (NULL, mem_size, MEM_RESERVE, PAGE_READWRITE);
#else
    main_memory = VirtualAlloc (NULL, mem_size, MEM_COMMIT, PAGE_READWRITE);
#endif
    assertMyth("ivory_initialize couldn't get memory from VirtualAlloc",
               main_memory != 0);

//��� Find out how much actually got allocated
    VirtualQuery (main_memory, &mem, sizeof (mem));
    mem_size = mem.RegionSize;

#if 1
    VirtualAlloc (main_memory, sizeof (*main_memory), MEM_COMMIT, PAGE_READWRITE);
#endif

//��� Once we have the block, set up the allocation header
//��� Fill in the "public" fields
    main_memory->memory_size = mem_size - sizeof (*main_memory);

//��� Initialize the counters
    main_memory->allocation_count = 0;
    main_memory->free_count = 0;
    main_memory->memory_alloced = 0;

//��� Now, the internal fields (memory is allocated from the top)
    main_memory->next_free = (byte *)main_memory + mem_size - sizeof (AllocationHeader);
    main_memory->freelist = 0;

//��� Lastly, we must manually lock the top of memory, since by the above
//��� calculation, we have effectively allocated sizeof(AllocationHeader)
//��� bytes already!
    VirtualAlloc ((void *)((dword)main_memory->next_free & PAGE_MASK), PAGE_SIZE,
                  MEM_COMMIT, PAGE_READWRITE);
}


//��������������������������������������������������������������������������
// ivory_terminate
//
// Free all ivory-allocated resources and shut down the library.
//��������������������������������������������������������������������������
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

        //��� Free the block we allocated.
        VirtualFree (main_memory, 0, MEM_RELEASE);
        main_memory = NULL;
    }
}


//��������������������������������������������������������������������������
// ivory_alloc
//
// Allocate a block out of main memory.
//��������������������������������������������������������������������������
void *ivory_alloc (size_t size)
{
    AllocationHeader    **pph, *ph;
    size_t              alloc_size;

    assertMyth("ivory_alloc must be called after ivory_initialize",
               main_memory != 0);

    assertMyth("ivory_alloc needs valid size", size > 0);

//��� Now, make sure there is room for the AllocationHeader, and
//��� then round the size to the nearest (greater) 16 byte alignment
#ifdef DEBUG
    size += 32;   // Make room for border dwords
#endif

    alloc_size  = size + sizeof (AllocationHeader) + 0x0f;
    alloc_size &= ~0x0f;

//��� First, scan the free list to see if we can find a suitable block
//��� Will this be fast enough, with the double pointer scheme?
    pph = &main_memory->freelist;
    ph  = main_memory->freelist;

    while (ph && ph->size < alloc_size)
    {
        pph = &ph->next;

        assert(ph != ph->next);
        ph  = ph->next;
    }

//��� If we have found a suitable block....
    if (ph)
    {
        //��� If this block is large enough to split, do so
        //��� (Needs at least as enough extra space to hold 16 bytes!)
        if (ph->size > alloc_size + sizeof (AllocationHeader) + 16)
        {
            // Remove our block from the end, so as to preserve the chain.
            ph->size -= alloc_size;
            ph = (AllocationHeader *)((char *)ph + ph->size);
        }
        //��� Otherwise, claim it as our own by overwriting
        //��� whatever pointed to it.
        else
            *pph = ph->next;
    }
    else
    {
        //��� Allocate a new block from the unused memory

        //��� If there isn't enough memory....
        if (main_memory->next_free < &main_memory->wildspace_start + alloc_size)
        {
            // Expand the block?
            return 0;
        }
        else
        {
            //��� Otherwise, take as much as we need (but no more!)

            //��� Get the top and bottom page pointers, rounded down and up respectively
            dword top_page    = (dword)main_memory->next_free & PAGE_MASK;
            dword bottom_page = (dword)(main_memory->next_free - alloc_size) & PAGE_MASK;

            //��� Commit and lock the memory if we need to.
            if (top_page > bottom_page)
            {
                VirtualAlloc ((void *)bottom_page, top_page - bottom_page,
                              MEM_COMMIT, PAGE_READWRITE);
            }

            //��� Allocate the memory from wildspace
            main_memory->next_free -= alloc_size;
            ph = (AllocationHeader *)main_memory->next_free;
        }
    }

//��� Now, 'ph' points to a usable chunk of memory.
    assert (ph != 0);
    ph->size = alloc_size;
    ph->next = 0;

//��� Now, return the area past the buffer (our user's memory)
    main_memory->allocation_count++;
    main_memory->memory_alloced += alloc_size;

//��� Make sure the block actually contains as many bytes as we want!
//��� (Testing by protfault! :-)
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


//��������������������������������������������������������������������������
// ivory_zalloc
//
// Allocate and zero a block from standard memory.
//��������������������������������������������������������������������������
void *ivory_zalloc (size_t size)
{
    void *ptr = ivory_alloc (size);

    assertMyth("ivory_zalloc needs valid size", size > 0);
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
    AllocationHeader *freeblk, *prevprev, *prevblk, *nextblk;

    assertMyth("ivory_alloc must be called after ivory_initialize",
               main_memory != 0);

    assertMyth("ivory_free needs valid pointer", ptr != 0 && *ptr != 0);

//��� Make sure this is our pointer!
    assertMyth ("ivory_free given pointer not in Ivory's memory range",
                *ptr > (void *)main_memory);
    assertMyth ("ivory_free given pointer not in Ivory's memory range",
                (*ptr < (void *)(((char *)main_memory) + main_memory->memory_size)));

//��� Get a pointer to the header info in front of this block
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

//��� Record the free for statistical purposes
    main_memory->memory_alloced -= freeblk->size;
    main_memory->free_count++;

//��� Scan until we are past all free blocks lower in memory than
//��� ourselves.  This is the most expensive part of this deallocator.
//��� Note: the '== 0' case is ok, since 0 is not greater than anything!
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

//��� Now, we have either a point in the list to add our link, or
//��� the end of the list.
//��� 'ph2' points to the link we want to point to our
//��� free region, and prevblk points to the block containing
//��� that pointer.
    assert ((prevblk == 0 && nextblk == main_memory->freelist) ||
            (prevblk != 0 && prevblk->next == nextblk));
    assert (prevprev == 0 || prevprev->next == prevblk);

//��� If the next block is adjacent, merge.  Otherwise chain it.
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

//��� At this point, we know that....
    assert (freeblk == nextblk ||       // We have merged, or
            freeblk->next == nextblk);  // we are linked in.

//��� If there's a previous block, and it's adjacent, eat our block
    if (prevblk)
    {
        if (prevblk == end_of (freeblk))
        {
            freeblk->size += prevblk->size;

            //��� Patch our pointer, which is the freelist head if there is no previous block
            if (prevprev)
                prevprev->next = freeblk;
            else
                main_memory->freelist = freeblk;

            //��� Back up our previous block pointer for the next step
            prevblk = prevprev;
        }
        //��� Otherwise, put our block into place
        else
            prevblk->next = freeblk;
    }
    //��� Otherwise, set this as the first block
    else
        main_memory->freelist = freeblk;

//��� If our block is now the last thing in memory, return it to wildspace
    if (freeblk == (AllocationHeader *)main_memory->next_free)
    {
        int freesize = freeblk->size;

#if 1
        //��� Unlock and decommit the memory.  We guarantee that
        //��� everything below next_free-BLKSIZE inclusive is decommitted.
        //��� So, we need to decommit any pages between the partial pages
        //��� at the top and bottom.

        //��� Get the top and bottom page pointers, rounded down and up respectively
        dword bottom_page = ((dword)freeblk + PAGE_SIZE-1) & PAGE_MASK;
        dword top_page    = ((dword)freeblk + freesize) & PAGE_MASK;

        if (top_page > bottom_page)
        {
            VirtualFree ((void *)bottom_page, top_page - bottom_page, MEM_DECOMMIT);
        }
#endif

        main_memory->next_free += freesize;

        //��� Make sure that we no longer point at this memory.
        if (prevblk)
            prevblk->next = 0;
        else
            main_memory->freelist = 0;
    }

//��� Lastly, zero out the pointer so we don't get into trouble later
    *ptr = 0;
}


//��������������������������������������������������������������������������
// gcd
//
// Find the greatest common divisor of the two numbers.
//��������������������������������������������������������������������������
static int gcd (int i, int j)
{
    assert (i != 0);
    assert (j != 0);

//��� The classic algorithm
    while (i != j)
    {
        if (i > j)
            i -= j;
        else
            j -= i;
    }

//��� Either i or j will work, since they are equal
    return i;
}

//��� End of module - ivalloc.c ���
