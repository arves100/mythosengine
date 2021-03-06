//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//           ^           **   **   **** ***** *    ****     ^      Take me to
//          (_)            * *     *      *   *    *       (_)    / your
//     ^                    *      **     *   *    **            ^  leader...
//    (_)       ^          * *     *      *   *    *            (_)
//             (_)       **   **   *    ***** **** ****
//
//                    Microsoft Windows 95/98/NT Version
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
// Created by Chuck Walbourn
//
// xuiffdir.cpp
//
// This is a utility module for the XFile library for printing out
// a directory of the contents of an .IFF file.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "xfile.hpp"

using namespace std; 

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#define FLAGS_PAUSE         0x1
#define FLAGS_RIFF          0x2
#define FLAGS_NOPAD         0x4

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Routines
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

STATIC void print_help(int full);
STATIC void print_error(XFParseIFF &xp, char *s=0);

STATIC void directory(XFParseIFF &iff);

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

STATIC dword   Flags=0;

STATIC ulong   Line=0;
STATIC ulong   Maxline=24;

STATIC char Util_name[]
       = "葦 IFF Directory - (C) 1994-9 by D. Higdon, T. Little, C. Walbourn  碓\n"
          "                  Subject to the terms of the MIT License  " __DATE__ "\n";

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// main                                                                     �
//                                                                          �
// Entry point for the IFFDIR utility.                                      �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void main(int argc, char *argv[])
{
    int         i;
    char        *fn;

//陳� Handle no filename for directory...
    if (argc < 2)
    {
        print_help(0);
        return;
    }

//陳� Process arguments
    for(i=1, fn=0; i < argc; i++)
    {
        if (*argv[i] == '-' || *argv[i] == '/')
        {
            switch (argv[i][1])
            {
                case 'p':
                case 'P':
                    Flags |= FLAGS_PAUSE;
                    break;
                case 'r':
                case 'R':
                    Flags |= FLAGS_RIFF;
                    break;
                case 'z':
                case 'Z':
                    Flags |= FLAGS_NOPAD;
                    break;
                case '?':
                    print_help(1);
                    return;
                default:
                    cout << "Unknown option " << argv[i] << " ignored\n";
                    break;
            }
        }
        else if (!fn)
        {
            fn=argv[i];
        }
    }

    if (!fn)
    {
        print_help(0);
        return;
    }

//陳� Check to see if supplied iff file exists
    if (!xf_exist(fn))
    {
        cout << "臼� " << fn << " does not exist\n";
        return;
    }

//陳� Construct IFF reader
    XFParseIFF  iff( ((Flags & FLAGS_RIFF) ? XF_IFF_RIFF : 0)
                     | ((Flags & FLAGS_NOPAD) ? XF_IFF_NOPAD : 0) );

//陳� Open supplied iff file
    if (iff.open(fn,XF_OPEN_READ | XF_OPEN_DENYWRITE))
    {
        print_error(iff,"Failed to open file");
        return;
    }

//陳� Print outline of file contents
    cout << Util_name;
    cout << "   File: " << fn << "\t"
         << ((Flags & FLAGS_RIFF) ? "Microsoft RIFF Format" : "EA IFF Format")
         << ((Flags & FLAGS_NOPAD) ? ", no padding" : "") << endl;
    Line=2;
    directory(iff);

//陳� Close file
    iff.close();
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// print_help                                                               �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
STATIC void print_help(int full)
{
    cout << Util_name;
    cout << "   Usage: iffdir [-p] [-r] [-z] <filename.iff/.xxx>\n";
    if (full)
    {
        cout << "          -p = Pause between screens.\n";
        cout << "          -r = Use Microsoft RIFF instead of EA IFF\n";
        cout << "          -z = Don't assume even byte padding (MID files)\n";
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// print_error                                                              �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
STATIC void print_error(XFParseIFF &xp, char *s)
{
    cout << "臼� ";

    if (s)
    {
        cout << s << ", ";
    }

    switch (xp.error())
    {
        case XF_ERR_NOTIFF:
            cout << "not an IFF/RIFF file error";
            break;
        case XF_ERR_CHUCKNOTFOUND:
            cout << "chunk not found error";
            break;
        case XF_ERR_FORMNOTFOUND:
            cout << "form not found error";
            break;
        case XF_ERR_UNEXPECTEDEOF:
            cout << "unexpected end-of-file error";
            break;
        case XF_ERR_INVALIDFORFORM:
            cout << "invalid operation for FORM/RIFF error";
            break;
        case XF_ERR_INVALIDFORCHUNK:
             cout << "invalid operation for chunk error";
            break;
        case XF_ERR_INVALIDID:
            cout << "invalid identifier error";
            break;
        case XF_ERR_TRUNCATEDCHUNK:
            cout << "truncated chunk error";
            break;
        case XF_ERR_WRITENOTALLOWED:
            cout << "write not allowed error";
            break;
        case XF_ERR_MAXDEPTHREACHED:
            cout << "maximum supported depth reached error";
            break;
        default:
            cout << "error " << (int)xp.error();
            break;
    }

    cout << "\n";
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// directory                                                                �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

#define COLUMN 45
#define MAXCOLUMN  75

STATIC void directory(XFParseIFF &iff)
{
    ulong   i;
    ulong   size;
    char    buff[5] = { 0, 0, 0, 0, 0 };

//陳 Loop through current level
    while (iff.next() == XF_ERR_NONE)
    {
        if (iff.chunkid == ((Flags & FLAGS_RIFF)
                            ? iff.makeid('R','I','F','F')
                            : iff.makeid('F','O','R','M')))
        {

            //陳 FORM/RIFF
            for (i=0; i < iff.depth; i++)
                cout << "�";

            cout << ((Flags & FLAGS_RIFF) ? "RIFF" : "FORM");

            cout << " '" << iff.strid(iff.formid,buff) << "'";

            for(i=iff.depth + sizeof("XXXX ''")+4; i < MAXCOLUMN; i++)
                cout << "�";

            cout << "\n";
            if ((Flags & FLAGS_PAUSE) && (++Line >= Maxline))
            {
                cout << "旭 More 旭\r";
                _getch();
                Line=1;
            }

            size = iff.chunkSize + 8;

            if (iff.enterform() != XF_ERR_NONE)
            {
                print_error(iff,"Problem entering FORM/RIFF");
            }
            else
            {
                directory(iff);

                for(i=0; i < iff.depth-1; i++)
                    cout << "�";

                cout << "�";

                for(; i < COLUMN - sizeof("Total "); i++)
                    cout << "�";

                cout << "Total " << size << " bytes\n";
                if ((Flags & FLAGS_PAUSE) && (++Line >= Maxline))
                {
                    cout << "旭 More 旭\r";
                    cout.flush();
                    _getch();
                    Line=1;
                }

                iff.leaveform();
            }
        }
        else
        {

            //陳 Chunk
            for(i=0; i < iff.depth; i++)
                cout << "�";

            cout << "'" << iff.strid(iff.chunkid,buff) << "' ";
            for(i=iff.depth + sizeof("'' ")+4; i < COLUMN; i++)
                cout << " ";

            cout << iff.chunkSize << " bytes\n";
            if ((Flags & FLAGS_PAUSE) && (++Line >= Maxline))
            {
                cout << "旭 More 旭\r";
                cout.flush();
                _getch();
                Line=1;
            }

        }
    }

    if (iff.error() != XF_ERR_EOF)
    {
        print_error(iff,"Problem processing file");
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// _charybdis_assert
//
// Handler for failed asserts.  If msg is set to non-NULL, then an assertMyth
// was used with a comment.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
extern "C" void _charybdis_assert(char *msg, char *exp, char *f, unsigned ln)
{
    cout.flush();
    printf("\n\n臼� Assertion Failed 臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼\n"
           "Expr:\t%s\n"
           "File:\t%s\t\tLine %d\n",exp,f,ln);
    if (msg)
    {
        printf("Comment:\n%s\n",msg);
    }

    exit(1);
}

//葦� End of module - xuiffdir.cpp 憶�

