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
// gbrgxfnt.cpp
//
// Contains the extended font management routines.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <gutenbrg.h>

#include <assert.h>
#include <string.h>

#include <ivory.hpp>
#include <xfile.hpp>

#include <gutenbrg.hpp>

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

extern "C" GBergIData   *GBergInstance;

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// gberg_remove_font                                                        �
//                                                                          �
// This routine removes the given font from memory.                         �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
extern "C" gberg_error_codes gberg_remove_font (const char *fntname)
{
    ulong               i;
    GBergFontInfo       *fnt;

    assertMyth("Gutenberg must be initialized",GBergInstance);

    if (!fntname)
        return GBERG_ERR_FONTNOTINSTALLED;

//陳 Check to see if active
    fnt=GBergInstance->font_active;
    if (fnt)
    {
        if (*fntname == *fnt->name)
        {
            if (!strcmp(fntname,fnt->name))
            {
                assertMyth("gberg_remove_font assumes active font has valid data",
                           fnt->data);

                ivory_hunlock(fnt->data);
                fnt->ptr=0;

                GBergInstance->font_active=0;
            }
        }
    }

//陳 Search for given font name
    for(i=0, fnt=&GBergInstance->fonts[0]; i < GBergInstance->fonts_hi; i++, fnt++)
    {
        if (*fntname == *fnt->name)
        {
            if (!strcmp(fntname,fnt->name))
                break;
        }
    }

    if (i >= GBergInstance->fonts_hi)
    {
        return GBERG_ERR_FONTNOTINSTALLED;
    }

//陳 Remove font
    if (fnt->data)
    {
        if (fnt->ptr)
        {
            ivory_hunlock(fnt->data);
            fnt->ptr=0;
        }
        ivory_hfree(&fnt->data);
    }
    memset(fnt,0,sizeof(GBergFontInfo));

    return GBERG_ERR_NONE;
}

//葦� End of module - gbrgxfnt.cpp 憶�


