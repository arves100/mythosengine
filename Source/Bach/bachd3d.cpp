//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//                        樛樛樛樛樛                       樛樛
//     敖朕                栩�     栩�                     渟栩
//     �  �       敖朕     栩�     栩�   樛樛      樛樛�    栩� 樛�
//     �  � 敖朕  �  �     栩桀樛樂栩�  �  渟�    栩�   炳  栩栩桎栩
//     �  � �  �  �  �     栩�     栩�  樂栩栩�  栩�        栩�   栩�
//    O� O� �  �  �  �     栩�     栩� 渟�  栩�  栩�    樂  栩�   栩�
//          �  � O� O�    樂栩樛樂栩�   栩栩毯桀  炳桀樂�  樂栩� 樂栩�
//         O� O�
//                            C++ Music, Sound, and Effects Library
//                               Microsoft Windows 95/98/NT Version
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
// Created by Dan Higdon & Chuck Walbourn
//
// bachd3d.cpp
//
// Digital 3D sound source implementation
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//#include <stdli.h>
#include <string.h>

#include "bach.hpp"

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭�  Constructors/Destructors  碓旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - Constructor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
BachDigital3D::BachDigital3D (ulong drate, bach_digi_fmt fmt):
    BachDigital(drate,fmt),
    listener(0)
{
    flags |= BACH_DIGI_3D;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - Destructor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
BachDigital3D::~BachDigital3D()
{
    close ();
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - init
//
// Initializes the digital driver with a 3D primary buffer
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::init (HWND hWnd, DWORD coop_level, int cont_play)
{
    if (dsound)
        return BACH_ERR_NONE;

    if (!hWnd)
        return BACH_ERR_INVALIDPARAMS;

    switch (driverFmt)
    {
        case BACH_DIGI_STEREO_8:
        case BACH_DIGI_STEREO_16:
            break;
        default:
            return BACH_ERR_INVALIDPARAMS;
    }

    switch (coop_level)
    {
        case DSSCL_WRITEPRIMARY:
        case DSSCL_EXCLUSIVE:
        case DSSCL_PRIORITY:
        case DSSCL_NORMAL:
            break;
        default:
            return BACH_ERR_INVALIDPARAMS;
    }

//陳 Create Direct Sound Object
    if (DirectSoundCreate (NULL, &dsound, NULL) != DS_OK)
        return BACH_ERR_DSCONNECTFAIL;

    assertMyth("BachDigital3D::init has invalid DSound create result",
               dsound != 0);

//陳 Let Direct Sound know how much control we need
    if (dsound->SetCooperativeLevel (hWnd, coop_level) != DS_OK)
    {
        close();
        return BACH_ERR_DSSETCOOPFAIL;
    }

//陳 Create Primary Direct 3D Sound Buffer
    DSBUFFERDESC    bd;
    memset (&bd, 0, sizeof (bd));

    bd.dwSize = sizeof (bd);
    bd.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;

    if (dsound->CreateSoundBuffer (&bd, &primary, NULL) != DS_OK)
    {
        close();
        return BACH_ERR_DSPRICREATFAIL;
    }

    assertMyth("BachDigital3D::init failed DSound buffer create",
                primary != 0);

//陳 Get caps of primary buffer
    DSBCAPS     caps;
    caps.dwSize = sizeof(caps);

    primary->GetCaps(&caps);

    assertMyth("BachDigital3D::init has invalid caps for primary buffer",
               (caps.dwFlags & DSBCAPS_PRIMARYBUFFER)
               && (caps.dwBufferBytes > 0));

//陳 Setup format
    WAVEFORMATEX    wfmt;
    memset(&wfmt,0,sizeof(wfmt));

    switch (driverFmt)
    {
        // Mono formats invalid for 3D sound...

        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳 Stereo 8-bit
        case BACH_DIGI_STEREO_8:
            wfmt.nChannels      = 2;
            wfmt.wBitsPerSample = 8;
            wfmt.nBlockAlign    = 2;
            break;
        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Stereo 16-bit
        case BACH_DIGI_STEREO_16:
            wfmt.nChannels      = 2;
            wfmt.wBitsPerSample = 16;
            wfmt.nBlockAlign    = 4;
            break;
        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Unknown
        default:
            close();
            return BACH_ERR_NOTSUPPORTED;
    }

    wfmt.wFormatTag      = WAVE_FORMAT_PCM;
    wfmt.nSamplesPerSec  = driverRate;
    wfmt.cbSize          = 0;
    wfmt.nAvgBytesPerSec = driverRate * wfmt.nBlockAlign;

//陳 Set format for primaray buffer
    if (coop_level == DSSCL_WRITEPRIMARY)
    {
        if (primary->SetFormat (&wfmt) != DS_OK)
        {
            close();
            return BACH_ERR_DSFORMATFAILED;
        }
    }
    else
    {
        if (primary->SetFormat (&wfmt) != DS_OK
            && coop_level != DSSCL_NORMAL)
        {
            close();
            return BACH_ERR_DSFORMATFAILED;
        }
    }

//陳 Get secondary interfaces
    if (FAILED(primary->QueryInterface(IID_IDirectSound3DListener,
                                       (LPVOID *)&listener)))
    {
        close();
        return BACH_ERR_DSFAILED;
    }

    assertMyth("BachDigital3D::init failed DSound listener interface query",
                listener != 0);

//陳 Initialize 3D listener to known reference frame
    DS3DLISTENER settings;
    memset(&settings,0,sizeof(settings));
    settings.vOrientFront.x = 0.0f;
    settings.vOrientFront.y = 0.0f;
    settings.vOrientFront.z = 1.0f;
    settings.vOrientTop.x = 0.0f;
    settings.vOrientTop.y = 1.0f;
    settings.vOrientTop.z = 0.0f;
    settings.flDistanceFactor = 1.0f;
    settings.flRolloffFactor = 1.0f;
    settings.flDopplerFactor = 1.0f;

    bach_err_codes err = set(settings);
    if (err)
    {
        close();
        return err;
    }

//陳 Begin primary buffer play
    if (cont_play)
    {
        if (primary->Play (0, 0, DSBPLAY_LOOPING) != DS_OK)
        {
            close();
            return BACH_ERR_DSFAILED;
        }
    }

    flags |= BACH_DIGI_PRIMARY_INITIALIZED;

    return BACH_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - close
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void BachDigital3D::close()
{
//陳 Release secondary interfaces
    if (listener)
    {
        listener->Release();
        listener=0;
    }

    BachDigital::close();
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - set
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::set(DS3DLISTENER &settings, int recalc)
{
    if (!listener)
        return BACH_ERR_UNINITIALIZED;

    settings.dwSize = sizeof(DS3DLISTENER);

    if (listener->SetAllParameters(&settings, DS3D_DEFERRED) != DS_OK)
        return BACH_ERR_DSFAILED;

    if (recalc)
    {
        if (listener->CommitDeferredSettings() != DS_OK)
            return BACH_ERR_DSFAILED;
    }

    return BACH_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - set_distance
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::set_distance(float factor, int recalc)
{
    if (!listener)
        return BACH_ERR_UNINITIALIZED;

    if (listener->SetDistanceFactor(factor, DS3D_DEFERRED) != DS_OK)
        return BACH_ERR_DSFAILED;

    if (recalc)
    {
        if (listener->CommitDeferredSettings() != DS_OK)
            return BACH_ERR_DSFAILED;
    }

    return BACH_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - set_doppler
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::set_doppler(float factor, int recalc)
{
    if (!listener)
        return BACH_ERR_UNINITIALIZED;

    if (listener->SetDopplerFactor(factor, DS3D_DEFERRED) != DS_OK)
        return BACH_ERR_DSFAILED;

    if (recalc)
    {
        if (listener->CommitDeferredSettings() != DS_OK)
            return BACH_ERR_DSFAILED;
    }

    return BACH_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - set_rolloff
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::set_rolloff(float factor, int recalc)
{
    if (!listener)
        return BACH_ERR_UNINITIALIZED;

    if (listener->SetRolloffFactor(factor, DS3D_DEFERRED) != DS_OK)
        return BACH_ERR_DSFAILED;

    if (recalc)
    {
        if (listener->CommitDeferredSettings() != DS_OK)
            return BACH_ERR_DSFAILED;
    }

    return BACH_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - set_orient
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::set_orient(float fi, float fj, float fk,
                                         float ti, float tj, float tk, int recalc)
{
    if (!listener)
        return BACH_ERR_UNINITIALIZED;

    if (listener->SetOrientation(fi, fj, fk, ti, tj, tk, DS3D_DEFERRED) != DS_OK)
        return BACH_ERR_DSFAILED;

    if (recalc)
    {
        if (listener->CommitDeferredSettings() != DS_OK)
            return BACH_ERR_DSFAILED;
    }

    return BACH_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - set_position
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::set_position(float x, float y, float z, int recalc)
{
    if (!listener)
        return BACH_ERR_UNINITIALIZED;

    if (listener->SetPosition(x, y, z, DS3D_DEFERRED) != DS_OK)
        return BACH_ERR_DSFAILED;

    if (recalc)
    {
        if (listener->CommitDeferredSettings() != DS_OK)
            return BACH_ERR_DSFAILED;
    }

    return BACH_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - set_velocity
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::set_velocity(float i, float j, float k, int recalc)
{
    if (!listener)
        return BACH_ERR_UNINITIALIZED;

    if (listener->SetVelocity(i, j, k, DS3D_DEFERRED) != DS_OK)
        return BACH_ERR_DSFAILED;

    if (recalc)
    {
        if (listener->CommitDeferredSettings() != DS_OK)
            return BACH_ERR_DSFAILED;
    }

    return BACH_ERR_NONE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - recalc
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
bach_err_codes BachDigital3D::recalc()
{
    if (!listener)
        return BACH_ERR_UNINITIALIZED;

    if (listener->CommitDeferredSettings() != DS_OK)
        return BACH_ERR_DSFAILED;

    return BACH_ERR_NONE;
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭葦  Utilities 碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - get
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void BachDigital3D::get(DS3DLISTENER &settings) const
{
    if (!listener)
        return;

    memset(&settings,0,sizeof(DS3DLISTENER));
    settings.dwSize = sizeof(DS3DLISTENER);

    listener->GetAllParameters(&settings);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - get_distance
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
float BachDigital3D::get_distance() const
{
    D3DVALUE    result;

    if (!listener
        || listener->GetDistanceFactor(&result) != DS_OK)
        return 0.0f;

    return result;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - get_doppler
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
float BachDigital3D::get_doppler() const
{
    D3DVALUE    result;

    if (!listener
        || listener->GetDopplerFactor(&result) != DS_OK)
        return 0.0f;

    return result;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - get_rolloff
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
float BachDigital3D::get_rolloff() const
{
    D3DVALUE    result;

    if (!listener
        || listener->GetRolloffFactor(&result) != DS_OK)
        return 0.0f;

    return result;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - get_orient
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void BachDigital3D::get_orient(float &fi, float &fj, float &fk,
                               float &ti, float &tj, float &tk) const
{
    if (!listener)
        return;

    D3DVECTOR front;
    D3DVECTOR top;

    if (listener->GetOrientation(&front, &top) != DS_OK)
        return;

    fi = front.x;
    fj = front.y;
    fk = front.z;

    ti = top.x;
    tj = top.y;
    tk = top.z;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - get_position
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void BachDigital3D::get_position(float &x, float &y, float &z) const
{
    if (!listener)
        return;

    D3DVECTOR pos;

    if (listener->GetPosition(&pos) != DS_OK)
        return;

    x = pos.x;
    y = pos.y;
    z = pos.z;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachDigital3D - get_velocity
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void BachDigital3D::get_velocity(float &i, float &j, float &k) const
{
    if (!listener)
        return;

    D3DVECTOR vel;

    if (listener->GetVelocity(&vel) != DS_OK)
        return;

    i = vel.x;
    j = vel.y;
    k = vel.z;
}

//葦� End of module - bachd3d.cpp 憶�
