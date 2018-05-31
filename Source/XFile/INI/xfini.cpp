//���������������������������������������������������������������������������
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
// Created by Chuck Walbourn
//
// xfini.cpp
//
// XFParseINI
//
// The internal implementation of the .INI reader is fairly simple -
//
// Basically, it maintains a buffer with a copy of the current
// .INI file for fast reading and as the basis of searches for
// the write operations.  The 'current section' is maintained by
// keeping a string with the last set name for searching purposes.
// If the current name is empty, then the file is assumed to be a
// 'single-section' .INI.
//
// The end of file is indicated by the hitting the end of the file
// or the beginning of another section.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <string.h>

#include "xfile.hpp"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFParseINI - Constructor                                                 �
//���������������������������������������������������������������������������
XFParseINI::XFParseINI() :
    buffsize(0),
    buff(0)
{
    *sectname=0;
    xf=&xfile;
}

XFParseINI::XFParseINI(XFile *f) :
    buffsize(0),
    buff(0),
    xf(f)
{
    *sectname=0;
}


//�������������������������������������������������������������������������Ŀ
// XFParseINI - Destructor                                                  �
//���������������������������������������������������������������������������
XFParseINI::~XFParseINI()
{
    end();
    xf->close();
}


//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFParseINI - begin                                                       �
//                                                                          �
// Sets up for processing of the .INI file.                                 �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseINI::begin(void)
{
    if (!(xf->status() & (XF_OPEN_READ|XF_OPEN_WRITE)))
    {
        errorn=XF_ERR_NEEDREADORWRITE;
        return errorn;
    }

//��� Load file image ���
    return load();
}


//�������������������������������������������������������������������������Ŀ
// XFParseINI - end                                                         �
//                                                                          �
// Close the .INI file.                                                     �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseINI::end(void)
{
    xf_error_codes err;

//��� Free memory buffer ���
    if (buff)
    {
        delete [] buff;
        buffsize=0;
        buff=0;
        *sectname=0;
    }

//��� Flush the filehandle ���
    err=xf->flush();
    if (err)
        errorn=err;

    return err;
}


//�������������������������������������������������������������������������Ŀ
// XFParseINI - section                                                     �
//                                                                          �
// Sets the active section name.  If NULL, then the file has no sections,   �
// with all variables visible.                                              �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseINI::section(const char *name)
{
    if (!name || !*name)
    {
        *sectname = 0;
        return XF_ERR_NONE;
    }

//��� Test length of section name ���
    if ((strlen(name)+3) > XF_MAX_ININAME)
    {
        errorn=XF_ERR_NAME_TOO_LONG;
        return errorn;
    }

//��� Save section name ���
    sectname[0] = '[';
    strcpy(&sectname[1],name);
    sectname[strlen(name)+1] = ']';
    sectname[strlen(name)+2] = 0;

//��� If read only, test for section ���
    if ((xf->status() & (XF_STATUS_READ|XF_STATUS_WRITE)) == XF_STATUS_READ)
    {
        if (!strstr(buff,sectname))
        {
            errorn=XF_ERR_SECTION_NOT_FOUND;
            return errorn;
        }
    }

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
//                          ��� Protected ���                               �
// XFParseINI - load                                                        �
//                                                                          �
// Reloads the current file image into a memory buffer.  Will resize memory �
// buffer if needed.                                                        �
//                                                                          �
// Returns an error code if an error ocurrs.                                �
//���������������������������������������������������������������������������
xf_error_codes XFParseINI::load(void)
{
    ulong size;

//��� Get size ���
    size = xf->getsize();
    if (size == -1)
    {
        errorn=xf->error();
        return errorn;
    }

//��� Allocate buffer if too small ���
    if (size > buffsize)
    {
        if (buff)
            delete [] buff;
        buffsize = size;
        buff = new char[buffsize+1];
        if (!buff)
        {
            errorn=XF_ERR_NOMEMORY;
            return errorn;
        }
    }

//��� If size is non-zero, load image ���
    xf->seek_set(0);

    if (size && (xf->read(buff,size) != size))
    {
        errorn=xf->error();
        return errorn;

    }

//��� Put a 0 at end for string searches ���
    if (buff && size)
        buff[size] = 0;

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
//                          ��� Protected ���                               �
// XFParseINI - start                                                       �
//                                                                          �
// Gets start location for current section name.  If *sections is non-zero, �
// then the '[name]' is skipped, so the pointer points just past the name   �
// of the section.                                                          �
//���������������������������������������������������������������������������
char *XFParseINI::start(void)
{
    char *ptr;

    if (!buff)
    {
        errorn=XF_ERR_SECTION_NOT_FOUND;
        return 0;
    }

    ptr = buff;
    if (*sectname)
    {
        ptr = strstr(ptr,sectname);
        if (!ptr)
        {
            errorn=XF_ERR_SECTION_NOT_FOUND;
            return 0;
        }
        for(; *ptr && *ptr != ']'; ptr++);
    }

    return ptr;
}

//�������������������������������������������������������������������������Ŀ
//                          ��� Protected ���                               �
// XFParseINI - find                                                        �
//                                                                          �
// Find variable in buffer.  Buffer is assumed to have a 0 at end to        �
// indicate end of file.  Scanning starts from 'ptr' and ends at end-of-    �
// file or the first '[ character, indicating beginning of new section      �
//                                                                          �
// Returns pointer to buffer line with variable or 0 if not found.          �
//���������������������������������������������������������������������������
char *XFParseINI::find(char *ptr, const char *item)
{
    int     itemlen;

//��� Check for NULL start position ���
    if (!ptr)
        return 0;

//��� Scan buffer ���
    itemlen = strlen(item);
    while (ptr && *ptr)
    {
        switch (*ptr)
        {
                                           // Whitespace
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                ptr++;
                break;
                                           // Comments
            case ';':
                for(; *ptr && *ptr != '\n'; ptr++);
                if (*ptr)
                    ptr++;
                break;
                                           // Section
            case '[':
                ptr=NULL;
                break;

            default:                        // Text line
                if (!strncmp(ptr,item,itemlen))
                    return ptr;
                for(; *ptr && *ptr != '\n'; ptr++);
                break;
        }
    }

    return 0;
}

//��� End of module - xfini.cpp ���

