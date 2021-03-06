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
//                          *** Tester Application ***
//
// Created by Chuck Walbourn
//
// xtlow.cpp
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <iostream>

#include <io.h>
#include <fcntl.h>

#include "xfile.hpp"

using namespace std; 

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Routines
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

void print_error(char *s);
void print_error(class XFile *xf, char *s);

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// low_level                                                                �
//                                                                          �
//     Entry point for the low-level file tests for XFile.                  �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void low_level()
{
   HANDLE   fhandle;

//陳陳 Perform file tests 陳陳
   cout << "\n\n\n旭旭旭臼臼臼臆臆臆 Low-level/Base object tests 臆臆臆臼臼臼旭旭旭\n";

   cout << "旭� Using low-level functions 旭�\n";
   fhandle=xf_open("TESTFILE.DAT",XF_OPEN_CREATE|XF_OPEN_WRITE);

   if (fhandle == INVALID_HANDLE_VALUE)
   {
       print_error("Failed to open file");
   }
   else
   {
       ulong   result;
       char    data[128];

       cout << "File created.\n";

       result = xf_write(fhandle,"Test String\n",sizeof("Test String\n") );

       if (result != sizeof("Test String\n"))
           print_error("Failed to write string");
       else
           cout << "Written.\n";

       cout << "Current file position: " << xf_seek (fhandle,1,0) << "\n";

       xf_flush (fhandle);
       xf_close (fhandle);

       fhandle = xf_open("TESTFILE.DAT",XF_OPEN_READ);
       if (fhandle == INVALID_HANDLE_VALUE)
       {
           print_error("Failed to open file");
       }
       else
       {
           ulong    i;

           cout << "File size " << xf_getsize(fhandle) << "\n";

           result = xf_read (fhandle, data, 128);

           if (!result)
               print_error ("Error reading");
           else
           {
               for (i = 0; i < result; i++)
                   cout << data[i];
           }

           xf_close(fhandle);
       }
   }

   cout << "旭� Temporary file" << endl;

   char fname[16] = "xxx";

   fhandle=xf_opentmp(fname,XF_OPEN_CREATE|XF_OPEN_WRITE);

   if (fhandle == INVALID_HANDLE_VALUE)
   {
       print_error("Failed to open temporary file");
   }
   else
   {
       ulong   result;
       char    data[128];
	   char	   pFileName[MAX_PATH+1];

	   cout << "File created as " << fname << ".\n";
       
	   result=xf_write(fhandle,"Test String\n",sizeof("Test String\n") );

       if (result != sizeof("Test String\n"))
           print_error("Failed to write string");
       else
           cout << "Written.\n";

       cout << "Current file position: " << xf_seek(fhandle,1,0) << "\n";

	   if (xf_getname(fhandle, pFileName, sizeof(pFileName)) != pFileName)
	   {
			print_error("Cannot get file path");
	   }
	   else
	   {
			cout << "File path is " << pFileName << ".\n";
	   }

       xf_flush(fhandle);
       xf_close(fhandle);

	   fhandle=xf_open(pFileName[0] == '\0' ? fname : pFileName,XF_OPEN_READ);
       if (fhandle == INVALID_HANDLE_VALUE)
       {
           print_error("Failed to open file");
       }
       else
       {
           ulong    i;

           cout << "File size " << xf_getsize(fhandle) << "\n";

           result=xf_read(fhandle,data,128);

           if (!result)
               print_error("Error reading");
           else
           {
               for (i = 0; i < result; i++)
                   cout << data[i];
           }

           xf_close(fhandle);
       }

       xf_remove(fname);
   }

   cout << "\n旭� Using XFileDisk object 旭�\n";
   XFileDisk   xf;

   if (xf.create("TESTFIL2.DAT",0))
   {
       print_error(&xf,"Failed to create file");
   }
   else
   {
       ulong   result;
       char    data[128];

       cout << "File created.\n";

       result=xf.write("Test string\n",sizeof("Test string\n"));

       if (result != sizeof("Test string\n"))
           print_error(&xf,"Failed to write string");
       else
           cout << "Written.\n";

       cout << "Current file position: " << xf.tell() << "\n";

       xf.flush();
       xf.close();

       if (xf.open("TESTFIL2.DAT",XF_OPEN_READ))
       {
           print_error(&xf,"Failed to open file");
       }
       else
       {
           ulong    i;

           result=xf.read(data,128);

           if (!result)
               print_error(&xf,"Failed to read");
           else
           {
               for (i = 0; i < result; i++)
                   cout << data[i];
           }

           xf.close();
       }
   }

   cout << "\n旭� Testing miscellanous low-level routines 旭�\n";

   if (xf_exist("TESTFILE.DAT"))
   {
       int attrs;

       cout << "Testfile.dat exists, this is correct.  Attributes =";

       attrs=xf_getattr("TESTFILE.DAT");

       if (attrs & XF_ATTRIB_READONLY)
           cout << " Ronly";
       if (attrs & XF_ATTRIB_HIDDEN)
           cout << " Hidden";
       if (attrs & XF_ATTRIB_SYSTEM)
           cout << " System";
       if (attrs & XF_ATTRIB_LABEL)
           cout << " Label";
       if (attrs & XF_ATTRIB_DIRECTORY)
           cout << " Directory";
       if (attrs & XF_ATTRIB_ARCHIVE)
           cout << " Archive";
       if (attrs & XF_ATTRIB_SHAREABLE)
           cout << " Shareable";

       cout << "\n";
   }
   else
       print_error("Testfile.dat should exist at this point");

   if (xf_remove("TESTFILE.DAT"))
       print_error("Error removing file");
   else
       cout << "File removed\n";

   if (!xf_exist("TESTFILE.DAT"))
       cout << "Testfile.dat doesnt exist, this is correct\n";
   else
       print_error("Testfile.dat should NOT exist at this point");

   if (xf_rename("TESTFIL2.DAT","TESTFILE.DAT"))
   {
       print_error("Renaming didn't work");
       xf_remove("TESTFIL2.DAT");
   }
   else
   {
       cout << "Renamed file work...\n";

       xf_remove("TESTFILE.DAT");
   }

   char *c;
   cout << "\nDumping PATH\n";

   c=xf_getenv("PATH");
   if (!c)
       cout << "Path not set\n";
   else
       cout << "Path = " << c;
   cout << "\n";

   cout << "\nTest searching\n";
   char buff[128];
   if (*xf_searchenv("WPP386.EXE","PATH",buff))
   {
       cout << "Filename: " << buff << "\n";
   }

   cout << "Test path ops\n";
   cout << xf_makepath(buff,"C:","TEMP","RESULT","DAT") << "\n";

   cout << "Test find file\n";
   struct xf_find_type find;

   if (!xf_findfirst ("*.bat",0,&find))
   {
       cout << find.xf_name << "  " << find.xf_size << " bytes\n";

       while (xf_findnext (&find) == 0)
       {
            cout << find.xf_name << "  " << find.xf_size << " bytes\n";
       }

       xf_findclose(&find);
   }
   else
       cout << "No Files Found\n";
}

//葦� End of module - xtlow.cpp 憶�

