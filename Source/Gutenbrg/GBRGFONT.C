//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//           __ ,
//            ,-| ~           ,               ,,
//           ('||/__,        ||               ||                  _
//          (( |||  | \\ \\ =||=   _-_  \\/\\ ||/|,  _-_  ,._-_  / \\
//          (( |||==| || ||  ||   || \\ || || || || || \\  ||   || ||
//           ( / |  , || ||  ||   ||/   || || || |' ||/    ||   || ||
//            -____/  \\/\\  \\,  \\,/  \\ \\ \\/   \\,/   \\,  \\_-|
//                                                               /  \
//                                                              '----`
//                     Text Output and Font Management System
//                       Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1995-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
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
// Created by Chuck Walbourn
//
// gbrgfont.c
//
// Contains the basic font management routines.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <debug.h>

#include <assert.h>
#include <string.h>

#include <gutenbrg.h>

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Routines
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

extern GBergFontInfo *igberg_empty_font();

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

extern GBergIData   *GBergInstance;

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// gberg_color                                                              �
//                                                                          �
// This sets the current color for the font draw which is used by the mono  �
// fonts.                                                                   �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
gberg_error_codes gberg_color(dword fcol, dword bcol)
{
    assertMyth("Gutenberg must be initialized",GBergInstance);

    GBergInstance->fcol = fcol;
    GBergInstance->bcol = bcol;

    return GBERG_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// gberg_select_font                                                        �
//                                                                          �
// Makes the given font active, locking it's handle.                        �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
gberg_error_codes gberg_select_font(const char *fntname)
{
    ulong               i;
    GBergFontInfo       *fnt, *nfnt;

    assertMyth("Gutenberg must be initialized",GBergInstance);

    if (!fntname)
        return GBERG_ERR_FONTNOTINSTALLED;

    fnt=GBergInstance->font_active;
    if (fnt)
    {
//陳 Check to see if already active
        if (*fntname == *fnt->name)
        {
            if (!strcmp(fntname,fnt->name))
                return GBERG_ERR_NONE;
        }
    }

//陳 Search for given font name
    for(i=0, nfnt=&GBergInstance->fonts[0]; i < GBergInstance->fonts_hi; i++, nfnt++)
    {
        if (*fntname == *nfnt->name)
        {
            if (!strcmp(fntname,nfnt->name))
                break;
        }
    }

    if (i >= GBergInstance->fonts_hi)
    {
        return GBERG_ERR_FONTNOTINSTALLED;
    }

//陳 Unlock old font, if active
    if (fnt)
    {
        assertMyth("gberg_select_font assumes active font has valid data",
                   fnt->data);

        ivory_hunlock(fnt->data);
        fnt->ptr=0;

        GBergInstance->font_active=0;
    }

//陳 Lock new font
    assertMyth("gberg_select_font assumes font not already locked",
               !nfnt->ptr);

    nfnt->ptr=ivory_hlock(nfnt->data);
    if (!nfnt->ptr)
        return GBERG_ERR_LOCKFAILED;

    GBergInstance->font_active=nfnt;

    return GBERG_ERR_NONE;
}

//葦� End of module - gbrgfont.c 憶�
