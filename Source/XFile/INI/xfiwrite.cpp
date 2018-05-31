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
// xfiwrite.cpp
//
// XFParseINI -
//
// Writing includes a number of cases.  The memory-copy of the buffer is
// scanned for the item to see if it needs to be replaced.  If not found,
// then the section is created and the variable is written out.
// The first part of the buffer is written, then the new lines, then
// the second part to replace a buffer.  Comments and whitespace
// are preserved expect on the actual line replaced.  The buffer is
// then reloaded.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "xfile.hpp"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// XFParseINI - write                                                       �
//                                                                          �
// Writes a variable (overwriting if it already exists in this section).    �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseINI::write(const char *item, const char *value)
{
    int  addcrlf=0;
    xf_error_codes error;
    char *ptr;
    char *prologue;
    char crlf[2] = { '\r', '\n' };
    char equal = '=';

    prologue=0;

//��� Setup start of search  ���
    ptr = start();
    if (!ptr && *sectname)
    {

//��� Section doesn't exist, so this is definetly new:
//                                       append and write section name ���
        xf->seek_end(0);
        if (xf->write(crlf,2) != 2)
        {
            errorn=xf->error();
            return errorn;
        }
        if (xf->write(sectname,strlen(sectname)) != strlen(sectname))
        {
            errorn=xf->error();
            return errorn;
        }
        if (xf->write(crlf,2) != 2)
        {
            errorn=xf->error();
            return errorn;
        }

    }
    else
    {
//��� Empty current file ���
        xf->setsize(0);

//��� Scan section for variable already defined  ���
        if ((ptr=find(ptr,item))!=0)
        {

//��� Variable already defined ���
            for(prologue=ptr; *prologue && *prologue != '\n'; prologue++);
            if (*prologue)
                prologue++;

            if (ptr != buff && *ptr)
                ptr--;
        }
        else
        {

//��� Variable not defined in section ���
            ptr = start();
            if (ptr && *sectname)
            {
                addcrlf=1;
                for(prologue=ptr; *prologue && *prologue != '\n'; prologue++);
                if (*prologue)
                    prologue++;
            }
            else
                prologue=ptr;
        }

//��� Write any area previous to variable's location ���
        if (ptr && buff && (ptr != buff))
        {
            if (xf->write(buff,ptr-buff+1) != (ulong)(ptr-buff+1))
            {
                errorn=xf->error();
                return errorn;
            }
        }
    }

//��� Write out ���
    if (addcrlf)
    {
        if (xf->write(crlf,2) != 2)
        {
            errorn=xf->error();
            return errorn;
        }
    }

    if (xf->write(item,strlen(item)) != strlen(item))
    {
        errorn=xf->error();
        return errorn;
    }
    if (xf->write(&equal,1) != 1)
    {
        errorn=xf->error();
        return errorn;
    }
    if (xf->write(value,strlen(value)) != strlen(value))
    {
        errorn=xf->error();
        return errorn;
    }
    if (xf->write(crlf,2) != 2)
    {
        errorn=xf->error();
        return errorn;
    }
    if (prologue && *prologue)
    {
        if (xf->write(prologue,strlen(prologue)) != strlen(prologue))
        {
            errorn=xf->error();
            return errorn;
        }
    }

//��� Reload ���
    error=load();
    if (error)
        return error;

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFParseINI - write                                                       �
//                                                                          �
// Writes a block of variables                                              �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseINI::write(const char **item, const char **value)
{
    int i;

    for(i=0; item[i] && *item[i]; i++)
    {
        if (write(item[i],value[i]))
            return errorn;
    }

    return XF_ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// XFParseINI - write                                                       �
//                                                                          �
// Writes a variable with an integer value.                                 �
//                                                                          �
// Returns 0 if ok, error number otherwise.                                 �
//���������������������������������������������������������������������������
xf_error_codes XFParseINI::write(const char *item, int value)
{
    char            str[XF_MAX_INIVALUE];

    sprintf(str,"%d",value);

    return write(item,str);
}

//��� End of module - xfiwrite.cpp ���

