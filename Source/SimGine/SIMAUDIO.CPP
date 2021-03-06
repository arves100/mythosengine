//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//                              S I M   G I N E
//
//             __               ___   ______,-------
//           __==__,------------/|\--|      | .-.-.|    ___________
//         (|     |--------------|---|------| '-`-`|  _/___________\_
//         (|_____|      _       _   |   _  | 6000 | |               |
//          |__\\_|`-._/___\___/___\_|_/___\|      | |               |
//         __/ |===|--|_____|_|_____|_|___  |\_____|=|_______________|
//      |=|[_]==[_]    \ _ /   \ _ /   \ _ /          [_]   [_]   [_]
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
//                     A Simluator Framework for MythOS(tm)
//
//                     Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1997-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
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
// Created by Dan Higdon and Chuck Walbourn
//
// simaudio.cpp
//
// This module contains the Audio management class.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "simgine.hpp"

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭�  Constructors/Destructors  碓旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimGine - Constructor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
SimAudio::SimAudio() :
    digi(0),
    channels3d(0),
    channels(0),
    stream(0)
{
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - Destructor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
SimAudio::~SimAudio()
{
    release();
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - init
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
SimAudio::error_codes SimAudio::init (ulong drate,
                                      bach_digi_fmt dfmt,
                                      ulong _nchannels, ulong _nreserved,
                                      ulong n3d)
{
    if (digi)
        release();

//陳� Create digital object and init()
    if (n3d > 0)
    {
        digi = new BachDigital3D(drate,dfmt);
        if (!digi)
            return ERROR_NOMEMORY;
    }
    else
    {
        digi = new BachDigital(drate,dfmt);
        if (!digi)
            return ERROR_NOMEMORY;
    }

    if (digi->init(SimApp->hWndClient) != BACH_ERR_NONE)
    {
        release();
        return ERROR_INIT;
    }

//陳� Allocate 3D channels
    if (n3d > 0)
    {
        channels3d = new BachSample3D*[n3d];
        if (!channels3d)
        {
            release();
            return ERROR_NOMEMORY;
        }

        nchannels3d = n3d;

        for(ulong i=0; i < n3d; i++)
        {
            channels3d[i] = new BachSample3D((BachDigital3D*)digi);
            if (!channels3d[i])
            {
                release();
                return ERROR_NOMEMORY;
            }
        }
    }

//陳� Allocate channels
    if (_nchannels > 0)
    {
        channels = new BachStaticSample*[_nchannels];
        if (!channels)
        {
            release();
            return ERROR_NOMEMORY;
        }
        nchannels = _nchannels;
        nreserved = _nreserved;

        for (ulong i=0; i < _nchannels; i++)
        {
            channels[i] = new BachStaticSample(digi);
            if (!channels[i])
            {
                release();
                return ERROR_NOMEMORY;
            }
        }
    }

//陳� Allocate streaming sample
    stream = new BachFileSample(digi);
    if (!stream)
    {
        release();
        return ERROR_NOMEMORY;
    }

    return ERROR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - release
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimAudio::release()
{
    if (stream)
    {
        delete stream;
        stream = 0;
    }

    if (channels)
    {
        for(ulong i=0; i < nchannels; i++)
        {
            if (channels[i])
                delete channels[i];
        }
        delete [] channels;
        channels = 0;
    }

    if (channels3d)
    {
        for(ulong i=0; i < nchannels3d; i++)
        {
            if (channels3d[i])
                delete channels3d[i];
        }
        delete [] channels3d;
        channels3d = 0;
    }

    if (digi)
    {
        delete digi;
        digi=0;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - clear_all_sounds
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimAudio::clear_all_sounds()
{
    if (stream)
    {
        stream->stop();
    }

    if (channels3d)
    {
        for(ulong i=0; i < nchannels3d; i++)
        {
            channels3d[i]->release();
        }
    }

    if (channels)
    {
        for(ulong i=0; i < nchannels; i++)
        {
            channels[i]->release();
        }
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - prepare_wav
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
int SimAudio::prepare_wav(const char *fname, int channel)
{
    if (!channels)
        return -1;

	ulong i = 0;

//陳陳 Find free channel
    if (channel == -1)
    {
        for(i=nreserved; i < nchannels; i++)
        {
            if (!channels[i]->handle
                || !(channels[i]->status() & BACH_SMPSTAT_PLAYING))
                break;
        }

        if (i >= nchannels)
        {
            // All channels busy...
            return -1;
        }

        channel = i;
    }

//陳陳 Stop channel if needed
    if (channels[channel]->handle
        && (channels[channel]->status() & BACH_SMPSTAT_PLAYING))
        channels[channel]->stop();

//陳陳 Load file into sample
    if (channels[channel]->load_wav(fname) != BACH_ERR_NONE)
        return -1;

    return channel;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - play
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimAudio::play(ulong channel, int loop)
{
    if (!channels
        || (channel >= nchannels))
        return;

    if (!channels[channel]->handle)
        return;

    channels[channel]->play(loop);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - stop
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimAudio::stop(ulong channel)
{
    if (!channels
        || (channel >= nchannels))
        return;

    if (!channels[channel]->handle)
        return;

    channels[channel]->stop();
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - prepare_wav_stream
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
int SimAudio::prepare_wav_stream(const char *fname)
{
    if (!stream)
        return -1;

    if (stream->ready_wav(fname) != BACH_ERR_NONE)
        return -1;

    return 0;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - play_stream
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimAudio::play_stream(int loop)
{
    if (!stream)
        return;

    stream->play(loop);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - next_stream
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimAudio::next_stream()
{
    if (!stream)
        return;

    stream->next();
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimAudio - stop_stream
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimAudio::stop_stream()
{
    if (!stream)
        return;

    stream->stop();
}

//葦� End of module - simaudio.cpp 憶�
