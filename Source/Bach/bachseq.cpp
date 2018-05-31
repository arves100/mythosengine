//���������������������������������������������������������������������������
//
//                        ����������                       ����
//     ��Ŀ                ���     ���                     ����
//     �  �       ��Ŀ     ���     ���   ����      �����    ��� ���
//     �  � ��Ŀ  �  �     �����������  �  ���    ���   ��  ��������
//     �  � �  �  �  �     ���     ���  �������  ���        ���   ���
//    O� O� �  �  �  �     ���     ��� ���  ���  ���    ��  ���   ���
//          �  � O� O�    �����������   ��������  �������  ����� �����
//         O� O�
//                            C++ Music, Sound, and Effects Library
//                               Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1995-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
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
// Created by Dan Higdon & Chuck Walbourn
//
// bachseq.cpp
//
// Music sound container class implementation.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <stdlib.h>
#include <string.h>

#include "bach.hpp"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// BachSequence - Constructor
//���������������������������������������������������������������������������
BachSequence::BachSequence (BachMusic *mus) :
    segment(0)
{
    assertMyth("BachSequence needs initialized BachMusic object",
               mus && mus->perf != 0 && mus->loader != 0);

    perf = mus->perf;
    if (perf)
        perf->AddRef();

    loader = mus->loader;
    if (loader)
        loader->AddRef();
}


//���������������������������������������������������������������������������
// BachSequence - Destructor
//���������������������������������������������������������������������������
BachSequence::~BachSequence()
{
    release();

    if (loader)
    {
        loader->Release();
        loader=0;
    }
    if (perf)
    {
        perf->Release();
        perf=0;
    }
}



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// BachSequence - rleease
//���������������������������������������������������������������������������
void BachSequence::release()
{
    if (segment)
    {
        segment->Release();
        segment=0;
    }
}


//���������������������������������������������������������������������������
// BachSequence - play
//���������������������������������������������������������������������������
bach_err_codes BachSequence::play (long start)
{
    if (!segment || !perf)
        return BACH_ERR_UNINITIALIZED;

    HRESULT hr = segment->SetStartPoint(start);

    if (FAILED(hr))
    {
        return BACH_ERR_DMFAILED;
    }

    hr = perf->PlaySegment(segment, 0, 0, NULL);

    if (FAILED(hr))
    {
        return (hr == E_OUTOFMEMORY)
               ? BACH_ERR_OUTOFMEMORY : BACH_ERR_DMFAILED;
    }

    return BACH_ERR_NONE;
}


//���������������������������������������������������������������������������
// BachSequence - queue
//���������������������������������������������������������������������������
bach_err_codes BachSequence::queue (long start)
{
    if (!segment || !perf)
        return BACH_ERR_UNINITIALIZED;

    HRESULT hr = segment->SetStartPoint(start);

    if (FAILED(hr))
    {
        return BACH_ERR_DMFAILED;
    }

    hr = perf->PlaySegment(segment, DMUS_SEGF_QUEUE, 0, NULL);

    if (FAILED(hr))
    {
        return (hr == E_OUTOFMEMORY)
               ? BACH_ERR_OUTOFMEMORY : BACH_ERR_DMFAILED;
    }

    return BACH_ERR_NONE;
}


//���������������������������������������������������������������������������
// BachSequence - stop
//���������������������������������������������������������������������������
bach_err_codes BachSequence::stop ()
{
    if (!segment || !perf)
        return BACH_ERR_UNINITIALIZED;

    HRESULT hr = perf->Stop(segment, NULL, 0, 0);

    if (FAILED(hr))
    {
        return BACH_ERR_DMFAILED;
    }

    return BACH_ERR_NONE;
}


//���������������������������������������������������������������������������
// BachSequence - status
//���������������������������������������������������������������������������
dword BachSequence::status() const
{
    if (!segment || !perf)
        return 0;

    HRESULT hr = perf->IsPlaying(segment, NULL);
    if (FAILED(hr))
        return 0;

    return  (hr == S_OK) ? BACH_SEQSTAT_PLAYING : 0;
}


//���������������������������������������������������������������������������
// BachSequence - set_repeats
//���������������������������������������������������������������������������
bach_err_codes BachSequence::set_repeats(ulong count)
{
    if (!segment)
        return BACH_ERR_UNINITIALIZED;

    HRESULT hr = segment->SetRepeats(count);
    if (FAILED(hr))
        return BACH_ERR_DMFAILED;

    return BACH_ERR_NONE;
}


//���������������������������������������������������������������������������
// BachSequence - set_loop_points
//���������������������������������������������������������������������������
bach_err_codes BachSequence::set_loop_points(long start, long end)
{
    if (!segment)
        return BACH_ERR_UNINITIALIZED;

    HRESULT hr = segment->SetLoopPoints(start, end);
    if (FAILED(hr))
        return BACH_ERR_DMFAILED;

    return BACH_ERR_NONE;
}



//���������������������������������������������������������������������������
//������������������������������  Utilities ���������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// BachSequence - get_length
//���������������������������������������������������������������������������
long BachSequence::get_length() const
{
    if (!segment)
        return 0;

    MUSIC_TIME  mt;

    HRESULT hr = segment->GetLength(&mt);
    if (FAILED(hr))
        return 0;

    return mt;
}


//���������������������������������������������������������������������������
// BachSequence - load_mid
//���������������������������������������������������������������������������
bach_err_codes BachSequence::load_mid(const char *fname)
{
    if (!loader)
        return BACH_ERR_UNINITIALIZED;

    if (!fname)
        return BACH_ERR_INVALIDPARAMS;

    release();

//��� Setup description
    DMUS_OBJECTDESC desc;
    memset(&desc,0,sizeof(desc));
    desc.dwSize = sizeof(desc);
    desc.guidClass = CLSID_DirectMusicSegment;
    mbstowcs(desc.wszFileName, fname, strlen(fname)+1);
    desc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;

//��� Load object
    HRESULT hr = loader->GetObject( &desc,
                                    IID_IDirectMusicSegment,
                                    (void**) &segment );

    if (FAILED(hr))
    {
        release();
        switch (hr)
        {
            case E_OUTOFMEMORY:
                return BACH_ERR_OUTOFMEMORY;

            case DMUS_E_LOADER_FAILEDOPEN:
                return BACH_ERR_FILEERROR;

            case DMUS_E_LOADER_FORMATNOTSUPPORTED:
                return BACH_ERR_NOTSUPPORTED;

            default:
                return BACH_ERR_DMFAILED;
        }
    }

    assertMyth("BachSequence::load_mid() failed to obtain segment object",
               segment != 0);

    return BACH_ERR_NONE;
}

//��� End of module - bachseq.cpp ���
