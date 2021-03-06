//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//���������������������������������������������������������������������������
//����������旭旭旭旭旭�旭旭旭旭���旭旭旭旭��旭姻���旭姻旭旭旭旭旭�旭旭旭旭姻�
//���������葦姻������葦姻���葦姻葦姻���葦姻葦姻���葦姻葦姻�������葦姻���葦姻�
//��������碓甥������碓甥�������碓甥�������碓甥���碓甥碓甥�������碓甥���碓甥��
//�������渦臼葦渦��渦臼葦渦臼�渦甥�������渦臼葦渦臼�渦臼葦渦���渦臼葦渦姻����
//������渦甥�������������渦甥渦甥�������渦甥���渦甥渦甥�������渦甥���渦甥����
//�����憶悔������憶悔���憶悔憶悔���憶悔憶悔���憶悔憶悔�������憶悔���憶悔�����
//����臆臆臆臆臆�臆臆臆臆���臆臆臆臆��臆悔���臆悔臆臆臆臆臆�臆悔���臆悔������
//���������������������������������������������������������������������������
//����������������� Microsoft Windows 95/98/NT Version ����������������������
//���������������������������������������������������������������������������
//���Copyright (c) 1994-1999 by Dan Higdon, Tim Little, and Chuck Walbourn���
//���������������������������������������������������������������������������
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
// Created by Tim Little & Chuck Walbourn
//
// estfile.cpp
//
// Contains the code for the texture file management routines that are
// static members of EschTexture.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "escher.hpp"
#include "esfile.hpp"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#define INIT_TFILE_SIZE 4

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschTexture - file_load                                                  �
//                                                                          �
// Loads an instance of the texture from the data file if found in          �
// registered texture files.                                                �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
EschTexture *EschTexture::file_load(const char *n, VngoPal *pal, dword ctrlfl)
{
    if (!EschSysInstance || !EschSysInstance->tfile || !n)
        return 0;

//陳� Scan through each registered file
    for(ulong i=0; i < EschSysInstance->tfile_hi; i++)
    {
        EschTextureFile *tf = &EschSysInstance->tfile[i];

        if (tf->iff)
        {
            assertMyth("EschTexture::file_load needs valid entry",
                       tf->names != 0 && tf->count > 0);

            //陳� Find name in list of textures located within this file
            for(ulong j=0; j < tf->count; j++)
            {
                if (!strncmp(n,&tf->names[j*ESCH_MAX_NAME],ESCH_MAX_NAME))
                {
                    //陳� Found, so load texture
                    XFParseIFF *iff = tf->iff;

                    for(;;)
                    {
                        if (iff->next() != XF_ERR_NONE)
                        {
                            if (!iff->depth)
                            {
                                //陳� Shouldn't happen, but just in case...
                                iff->topofcontext(0);

                                return 0;
                            }
                            iff->leaveform();
                            continue;
                        }

                        if (iff->chunkid == iff->makeid('F','O','R','M'))
                        {
                            if (iff->formid == iff->makeid('E','M','T','L')
                                || iff->formid == iff->makeid('E','M','T','1'))
                            {
                                if (j > 0)
                                    j--;
                                else
                                {
                                    EschTexture *t = ((ctrlfl & ESCH_TXTLD_MFRAME)
                                                      && iff->formid == iff->makeid('E','M','T','1'))
                                                     ? (EschTexture *) new EschMultiFrameTexture
                                                     : (EschTexture *) new EschStaticTexture;

                                    if (t && t->load(iff, n, ctrlfl, pal))
                                    {
                                        delete t;
                                        t=0;
                                    }

                                    while (iff->depth)
                                        iff->leaveform();

                                    iff->topofcontext(0);

                                    return t;
                                }
                            }

                            // Must scan inside any ESEN Scene forms.
                            else if (iff->formid == iff->makeid('E','S','E','N'))
                            {
                                iff->enterform();
                            }

                            // Must scan inside any EMSH Mesh forms.
                            else if (iff->formid == iff->makeid('E','M','S','H'))
                            {
                                iff->enterform();
                            }

                            // Must scan inside any ETER Terrain forms.
                            else if (iff->formid == iff->makeid('E','T','E','R'))
                            {
                                iff->enterform();
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschTexture - file_register                                              �
//                                                                          �
// Adds a new texture file to the list of shared texture files.             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
esch_error_codes EschTexture::file_register(const char *fname)
{
    assertMyth("EschTexture::file_register needs System",
               EschSysInstance != 0);

//陳� Initialize texture file array if needed
    if (!EschSysInstance->tfile)
    {
        EschSysInstance->tfile = new EschTextureFile[INIT_TFILE_SIZE];
        if (!EschSysInstance->tfile)
            return ESCH_ERR_NOMEMORY;

        EschSysInstance->tfile_hi = 0;
        EschSysInstance->tfile_max = INIT_TFILE_SIZE;
    }

//陳� Find open slot
    ulong i=0;
    for(i=0; i < EschSysInstance->tfile_hi; i++)
    {
        if (!EschSysInstance->tfile[i].iff)
            break;
    }

    if (i >= EschSysInstance->tfile_hi)
    {
        if (EschSysInstance->tfile_hi >= EschSysInstance->tfile_max)
        {
            //陳� Must expand
            EschTextureFile *t
                    = new EschTextureFile[EschSysInstance->tfile_max << 1];
            if (!t)
                return ESCH_ERR_NOMEMORY;

            memcpy(t, EschSysInstance->tfile, EschSysInstance->tfile_max
                                               * sizeof(EschTextureFile));
            delete [] EschSysInstance->tfile;
            EschSysInstance->tfile=t;
            EschSysInstance->tfile_max <<= 1;
        }

        EschSysInstance->tfile_hi++;
    }

//陳� Fill slot
    assert(i < EschSysInstance->tfile_hi && i < EschSysInstance->tfile_max);

    EschTextureFile *tf = &EschSysInstance->tfile[i];

    strncpy(tf->fname, fname, XF_MAX_PATH);
    tf->flags = 0;
    tf->count = 0;

    tf->iff = new XFParseIFF;
    if (!tf->iff)
        return ESCH_ERR_NOMEMORY;

    XFParseIFF *iff = tf->iff;

    //陳� Try to open file
    if (iff->open(fname,XF_OPEN_READ | XF_OPEN_DENYWRITE))
    {
        delete tf->iff;
        tf->iff = 0;
        return ESCH_ERR_FILEERROR;
    }

    //陳� Count number of EMTL/EMT1 chunks
    for(;;)
    {
        if (iff->next() != XF_ERR_NONE)
        {
            if (!iff->depth)
                break;
            iff->leaveform();
            continue;
        }

        if (iff->chunkid == iff->makeid('F','O','R','M'))
        {
            if (iff->formid == iff->makeid('E','M','T','L')
                || iff->formid == iff->makeid('E','M','T','1'))
            {
                tf->count++;
            }

            // Must scan inside any ESEN Scene forms.
            else if (iff->formid == iff->makeid('E','S','E','N'))
            {
                iff->enterform();
            }

            // Must scan inside any EMSH Mesh forms.
            else if (iff->formid == iff->makeid('E','M','S','H'))
            {
                iff->enterform();
            }

            // Must scan inside any ETER Terrain forms.
            else if (iff->formid == iff->makeid('E','T','E','R'))
            {
                iff->enterform();
            }
        }
    }

    if (!tf->count)
    {
        delete tf->iff;
        tf->iff = 0;
        return ESCH_ERR_NOTFOUND;
    }

    iff->topofcontext(0);

    //陳� Allocate space for names
    tf->names = new char[ESCH_MAX_NAME*tf->count];
    if (!tf->names)
    {
        delete tf->iff;
        tf->iff = 0;
        return ESCH_ERR_NOMEMORY;
    }

    //陳� Read names from EMTL/EMT1 chunks
    esch_error_codes err = ESCH_ERR_NONE;

    ulong j=0;
    for(j=0; j < tf->count;)
    {
        if (iff->next() != XF_ERR_NONE)
        {
            if (!iff->depth)
                break;
            iff->leaveform();
            continue;
        }

        if (iff->chunkid == iff->makeid('F','O','R','M'))
        {
            if (iff->formid == iff->makeid('E','M','T','L')
                || iff->formid == iff->makeid('E','M','T','1'))
            {
                iff->enterform();

                if (iff->seekchunk(iff->makeid('M','H','D','R'))
                    || iff->chunkSize != sizeof(EschFileMtlMHDR))
                {
                    iff->leaveform();
                    err=ESCH_ERR_INVALIDDATA;
                    goto error_exit;
                }

                EschFileMtlMHDR header;
                if (iff->read(&header))
                {
                    iff->leaveform();
                    err=ESCH_ERR_FILEERROR;
                    goto error_exit;
                }

                strncpy(&tf->names[j*ESCH_MAX_NAME],header.name,ESCH_MAX_NAME);

                iff->leaveform();

                j++;
            }

            // Must scan inside any ESEN Scene forms.
            else if (iff->formid == iff->makeid('E','S','E','N'))
            {
                iff->enterform();
            }

            // Must scan inside any EMSH Mesh forms.
            else if (iff->formid == iff->makeid('E','M','S','H'))
            {
                iff->enterform();
            }

            // Must scan inside any ETER Terrain forms.
            else if (iff->formid == iff->makeid('E','T','E','R'))
            {
                iff->enterform();
            }
        }
    }

    if (j < tf->count)
    {
        err=ESCH_ERR_MISSINGDATA;
        goto error_exit;
    }

    iff->topofcontext(0);

    return ESCH_ERR_NONE;

error_exit : ;

    if (tf->iff)
        delete tf->iff;
    tf->iff = 0;

    if (tf->names)
        delete [] tf->names;
    tf->names = 0;

    return err;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschTexture - file_unregister                                            �
//                                                                          �
// Removes a registered texture file from the list of shared texture files. �
// If '0' is passed as the name, all files are unregistered.                �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void EschTexture::file_unregister(const char *fname)
{
    assertMyth("EschTexture::file_unregister needs System",
               EschSysInstance != 0);

    if (!EschSysInstance->tfile)
        return;

//陳� Scan through each registered file
    for(ulong i=0; i < EschSysInstance->tfile_hi; i++)
    {
        EschTextureFile *tf = &EschSysInstance->tfile[i];

        if (tf->iff)
        {
            if (!fname || !strncmp(fname,tf->fname,XF_MAX_PATH))
            {
                if (tf->names)
                {
                    delete [] tf->names;
                    tf->names = 0;
                }
                if (tf->iff)
                {
                    delete tf->iff;
                    tf->iff = 0;
                }
                tf->flags = 0;
                tf->count = 0;
                *tf->fname = 0;
            }
        }
    }
}

//葦� End of module - estfile.cpp 憶�

