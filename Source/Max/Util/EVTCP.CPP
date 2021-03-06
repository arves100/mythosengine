//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//                  ooo        ooooo
//                  `88.       .888'
//                   888b     d'888   .oooo.   oooo    ooo
//                   8 Y88. .P  888  `P  )88b   `88b..8P'
//                   8  `888'   888   .oP"888     Y888'
//                   8    Y     888  d8(  888   .o8"'88b
//                  o8o        o888o `Y888""8o o88'   888o
//
//                          Across the event horizon...
//
//                       Microsoft Windows 95/98/NT Version
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
//                              *** Utilities ***
//
// Created by Dan Higdon
//
// evtcp.cpp
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <conio.h>
#include <iostream>

#if _MSC_VER >= 1300 
#include <sstream>
#define ostrstream ostringstream
#else
#include <strstrea.h>
#endif

#include <stdlib.h>
#include <debug.h>

#include <xfiff.hpp>
#include <max.hpp>

#include "evttok.h"

using namespace std; 

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

//陳 External from scanner.
extern "C" int yylex (void);
extern "C" int yy_pushfile (const char *fname);
extern "C" int yywrap (void);

//陳 External from main module.
void print_error (XFParseIFF &xp, char *s=0);
void expand_work (ulong target);

//陳 Local

STATIC void include();
STATIC void event();
STATIC void trigger();
STATIC void constraint();

STATIC long integer(void);
STATIC long expr(void);
STATIC long term(void);
STATIC long factor(void);

STATIC void match(int tok);
extern "C" void error(const char *str);

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳 External from scanner.
extern "C" long    YY_integer;
extern "C" double  YY_real;
extern "C" int     YY_lineno;
extern "C" char    *yytext;

//陳 External from main module.
extern XFParseIFF  IFF;
extern XFileDOS    header;
extern byte        *Work;
extern ulong       Work_size;
extern dword       Flags;

//陳 Local
STATIC int  CurrentToken;

MaxTrigger  theTrigger;
int         event_id = 0;
int         triggers = 0;
int         trig_key = 0;

// These should be dynamically allocated.
const int MAX_TRIGS = 1024;
dword       EVNT[MAX_TRIGS];
MaxTrigger  TRGS[MAX_TRIGS];

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                               Messages
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

STATIC char cpp_header[] =
{
    "//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�\r\n"
    "// MaxC -- Event and Trigger Definition System                              �\r\n"
    "// (C) 1994-1999 by D. Higdon, T. Little, and C. Walbourn                   �\r\n"
    "//                                                                          �\r\n"
    "// Event Constants header file for C++                                      �\r\n"
    "//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�\r\n"
};

STATIC char cpp_trailer[] =
{
    "// EOF\r\n"
};

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// compile                                                                  �
//                                                                          �
// Parses file into output IFF (both already opened by main).               �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void compile (const char *evt_name)
{
    MaxEventUser::MaxHeader HDR;

    header.write (cpp_header, sizeof (cpp_header) - 1);

    event_id = triggers = 0;

    CurrentToken = yylex();
    while (CurrentToken)
        event();

    header.write (cpp_trailer, sizeof (cpp_trailer) - 1);

    // Write chunks out to the IFF file
    IFF.newform (IFF.makeid('M','E','V','T'));
    strcpy (HDR.name, evt_name);
    HDR.num_trigs = triggers;
    IFF.write (IFF.makeid('H','D','R',' '), &HDR, sizeof (HDR));
    IFF.write (IFF.makeid('E','V','N','T'), EVNT, sizeof (EVNT[0]) * triggers);
    IFF.write (IFF.makeid('T','R','G','S'), TRGS, sizeof (TRGS[0]) * triggers);
}

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// event                                                                    �
//                                                                          �
//      event :-  'event' <id> '{' <trigger> '}'                            �
//            |   'include' '"'filename'"'                                  �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
STATIC void event()
{
    ostrstream s;
    char ident[64];

    switch (CurrentToken)
    {
    case YY_EVENT:
        match (YY_EVENT);
        if (CurrentToken == YY_ID)
        {
            strcpy (ident, yytext);
            match (YY_ID);
        }
        else
        {
            error ("Expecting an identifier.");
        }

        if (event_id >= EVENT_MAX_EVENT)
        {
            error ("Number of events exceeds internal maximum -- see MaxEvent.HPP");
        }
        else
        {
            // store the event number with the specified trigger
            s << "#define " << ident << " MaxEvent (" << event_id << ")\r\n";
            header.write (s.str().c_str(), /*s.pcount()*/s.str().size());

            match (YY_LBRACE);
            while (CurrentToken && CurrentToken != YY_RBRACE)
                trigger();
            match (YY_RBRACE);

            // Advance to the next event_id
            event_id++;
        }

        break;

    case YY_INCLUDE:
        include();
        break;

    default:
        error("Invalid operation, expected an event");
        break;
   }
}

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// include                                                                  �
//                                                                          �
//     include :- 'include' <string>                                        �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
STATIC void include ()
{
    int err;

    match (YY_INCLUDE);

    switch (CurrentToken)
    {
    case YY_STRING:
#if 0
        if (!(Flags & FLAGS_QUIET))
            cout << "   旭� including '" << yytext << "' 旭�" << endl;
#endif

        err = yy_pushfile (yytext);
        switch (err)
        {
        case 0:     /* OK */
            break;
        case 1:     error("too many nested includes");
            break;
        case 2:     error("could not open include file");
            break;
        case 3:     error("not enough memory to include file");
        default:    error("include failed");
            break;
        }

        // Read first token from new file and continue processing
        // yywrap will undo include later
        CurrentToken = yylex();
        break;

    default:
        error("Invalid include command, expecting filename of CEL file to include");
        break;
    }
}

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// trigger                                                                  �
//                                                                          �
//     trigger :- '[' <constraint> * ']'                                    �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
STATIC void trigger ()
{
    EVNT[triggers] = event_id;

    match (YY_LBRACKET);

    // Collect all constraints
    trig_key = 0;
    theTrigger = MaxTrigger();
    while (CurrentToken && CurrentToken != YY_RBRACKET)
        constraint();

    match (YY_RBRACKET);

    TRGS[triggers] = theTrigger;

    // Advance to the next trigger
    triggers++;
    if (triggers > MAX_TRIGS)
        error ("Exceeded internal compiler limits -- too many triggers\n");
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// constraint                                                               �
//                                                                          �
//     constraint :- <key> | <mouseb> | <mousepos> | <mouserange>           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
STATIC void constraint ()
{
    switch (CurrentToken)
    {
    case YY_NOT:
        match (YY_NOT);
        match (YY_KEY);
        if (trig_key >= MaxTrigger::max_keys)
            error("Too many keys defined for event");
        else
            theTrigger.Keys[trig_key++] = word (0x200 | expr());
        break;

    case YY_KEY:
        match (YY_KEY);
        if (trig_key >= MaxTrigger::max_keys)
            error("Too many keys defined for event");
        else
            theTrigger.Keys[trig_key++] = word (expr());
        break;

    case YY_MOUSEB:
        match (YY_MOUSEB);
        // The number read is a bit position
        theTrigger.MouseButtons |= word (1 << (expr() - 1));
        break;

    case YY_JOYB:
        match (YY_JOYB);
        // The number read is a bit position
        theTrigger.JoyButtons |= word (1 << (expr() - 1));
        break;

    case YY_MOUSERANGE:
        match (YY_MOUSERANGE);
        theTrigger.BegX = (short)expr(); match (YY_COMMA);
        theTrigger.BegY = (short)expr(); match (YY_COMMA);
        theTrigger.EndX = (short)expr(); match (YY_COMMA);
        theTrigger.EndY = (short)expr();
        break;

    case YY_MOUSEDELTA:
        match (YY_MOUSEDELTA);
        theTrigger.DeltaX = (short)expr(); match (YY_COMMA);
        theTrigger.DeltaY = (short)expr();
        break;

    default:
        error("constraints must be either 'key', 'joyb', 'mouseb', 'mousedelta', or 'mouserange'");
        break;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// integer/expr                                                             �
//                                                                          �
// Signed integer expression parsers.                                       �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
STATIC long integer ()
{
    long    t = 0L;

    if (CurrentToken == YY_INTEGER)
    {
        t = YY_integer;
        match (YY_INTEGER);
    }
    else
        error("Integer expected");

    return t;
}


STATIC long expr ()
{
    long    t1, t2;

    t1 = term ();
    switch (CurrentToken)
    {
    case YY_PLUS:
        match (YY_PLUS);
        t2 = term();
        return (t1 + t2);

    case YY_MINUS:
        match (YY_MINUS);
        t2 = term();
        return (t1 - t2);

    default:
        return t1;
    }
}

STATIC long term ()
{
    long    t1, t2;
    t1 = factor();
    switch (CurrentToken)
    {
    case YY_MULTIPLY:
        match(YY_MULTIPLY);
        t2 = term();
        return (t1 * t2);

    case YY_DIVIDE:
        match(YY_DIVIDE);
        t2 = term();
        if (!t2)
            error("Divide by zero in expression");
        return (t1 / t2);

    default:
        return t1;
    }
}

STATIC long factor()
{
    long    t;

    switch(CurrentToken)
    {
    case YY_LPAREN:
        match(YY_LPAREN);
        t = expr();
        match(YY_RPAREN);
        return (t);

    case YY_INTEGER:
        return (integer());

    case YY_PLUS:
        match (YY_PLUS);
        return expr();

    case YY_MINUS:
        match (YY_MINUS);
        return -expr();

    default:
        error("Invalid expression");
        break;
    }

    return 0;
}

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// match                                                                    �
//                                                                          �
// Matches input token again target; if it failes, then it prints an error. �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
STATIC void match (int tok)
{
    if (tok != CurrentToken)
    {
        switch (tok)
        {
        case YY_LBRACKET:   error ("Expected a '['");
            break;
        case YY_RBRACKET:   error ("Expected a ']'");
            break;
        case YY_LBRACE:     error ("Expected a '{'");
            break;
        case YY_RBRACE:     error ("Expected a '}'");
            break;
        case YY_LPAREN:     error ("Expected a '('");
            break;
        case YY_RPAREN:     error ("Expected a ')'");
            break;
        default:            error ("Unexpected token in source file");
            break;
        }
    }

    CurrentToken = yylex();
}

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// error                                                                    �
//                                                                          �
// Emits an error and aborts processing.                                    �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void error (const char *str)
{
   cout << " Error(" << YY_lineno << "): " << str << "\n";
   exit (1);
}


//葦� End of module - xuiffcp.cpp 憶�

