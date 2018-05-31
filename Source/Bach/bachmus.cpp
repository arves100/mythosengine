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
// bachmus.cpp
//
// Music sound source implementation
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

#include <direct.h>

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

int     BachCOMInit     =  0;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// BachMusic - Constructor
//���������������������������������������������������������������������������
BachMusic::BachMusic () :
    dmusic(0),
    port(0),
    perf(0),
    loader(0)
{
}


//���������������������������������������������������������������������������
// BachMusic - Destructor
//���������������������������������������������������������������������������
BachMusic::~BachMusic()
{
    close ();
}



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// BachMusic - init
//
// Initializes the music source by obtaining DirectMusic performance
// and loader objects.
//���������������������������������������������������������������������������
bach_err_codes BachMusic::init (BachDigital *digi, HWND hwnd, DWORD effects)
{
    if (dmusic)
        return BACH_ERR_NONE;

    if (!BachCOMInit)
    {
        CoInitialize(NULL);
        BachCOMInit=1;
    }

//��� Create a performance object
    HRESULT hr = CoCreateInstance(CLSID_DirectMusicPerformance,
                                  NULL,
                                  CLSCTX_INPROC,
                                  IID_IDirectMusicPerformance,
                                  (void **) &perf);

    if (FAILED(hr))
    {
        close();
        return BACH_ERR_DMFAILED;
    }

    assertMyth("BachMusic::init() failed to obtain performance object",
               perf != 0);

//��� Initialize performance object (and get DirectMusic object)
    dmusic=NULL;
    hr = perf->Init(&dmusic, (digi) ? digi->dsound : NULL, hwnd);
    if (FAILED(hr))
    {
        close();
        return (hr == E_OUTOFMEMORY) ? BACH_ERR_OUTOFMEMORY : BACH_ERR_DMFAILED;
    }

    assertMyth("BachMusic::init() failed to obtain DirectMusic object",
               dmusic != 0);

//��� Create and assign port
    DMUS_PORTCAPS   caps;
    memset(&caps,0,sizeof(caps));
    caps.dwSize = sizeof(caps);

    for(int index=0; ; index++)
    {
        hr = dmusic->EnumPort(index, &caps);
        if (FAILED(hr))
        {
            close();
            return BACH_ERR_DMFAILED;
        }

        if (hr == S_FALSE)
            break;

        if (caps.dwClass == DMUS_PC_OUTPUTCLASS)
        {
            break;
        }
    }

    DMUS_PORTPARAMS params;
    memset(&params,0,sizeof(params));
    params.dwSize = sizeof(params);
    params.dwEffectFlags = effects;
    params.dwChannelGroups = 1;
    params.dwValidParams = DMUS_PORTPARAMS_CHANNELGROUPS
                           | DMUS_PORTPARAMS_EFFECTS;

    hr = dmusic->CreatePort(caps.guidPort, &params, &port, NULL);
    if (FAILED(hr))
    {
        close();
        return BACH_ERR_DMFAILED;

    }
    assertMyth("BachMusic::init() failed to obtain port",
               port != 0);

    port->Activate(TRUE);

    hr = perf->AddPort(port);
    if (FAILED(hr))
    {
        close();
        return (hr == E_OUTOFMEMORY) ? BACH_ERR_OUTOFMEMORY : BACH_ERR_DMFAILED;
    }

    hr = perf->AssignPChannelBlock(0, port, 1);
    if (FAILED(hr))
    {
        close();
        return BACH_ERR_DMFAILED;
    }

//��� Obtain loader
    hr = CoCreateInstance(CLSID_DirectMusicLoader,
                          NULL,
                          CLSCTX_INPROC,
                          IID_IDirectMusicLoader,
                          (void **) &loader);

    if (FAILED(hr))
    {
        close();
        return BACH_ERR_DMFAILED;
    }

    assertMyth("BachMusic::init() failed to obtain loader object",
               loader != 0);

//��� Ensure loader is using app's current directory
    char szDir[_MAX_PATH];
    WCHAR wszDir[_MAX_PATH];

    if(_getcwd( szDir, _MAX_PATH ) == NULL )
    {
        close();
        return BACH_ERR_FILEERROR;
    }

    mbstowcs(wszDir, szDir, _MAX_PATH);

    hr = loader->SetSearchDirectory(GUID_DirectMusicAllTypes,
                                    wszDir, FALSE );

    if (FAILED(hr))
    {
        close();
        return (hr == E_OUTOFMEMORY) ? BACH_ERR_OUTOFMEMORY : BACH_ERR_DMFAILED;
    }

    return BACH_ERR_NONE;
}


//���������������������������������������������������������������������������
// BachMusic - close
//���������������������������������������������������������������������������
void BachMusic::close()
{
//�� Stop all music
    if (perf)
        perf->Stop(NULL, NULL, 0, 0);

//�� Release DirectMusic objects
    if (loader)
    {
        loader->Release();
        loader = 0;
    }
    if (perf)
    {
        perf->Release();
        perf = 0;
    }
    if (port)
    {
        port->Release();
        port=0;
    }
    if (dmusic)
    {
        dmusic->Release();
        dmusic=0;
    }
}



//���������������������������������������������������������������������������
//������������������������������  Utilities ���������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// BachMusic - activate
//���������������������������������������������������������������������������
bach_err_codes BachMusic::activate()
{
    if (!dmusic)
        return BACH_ERR_UNINITIALIZED;

    HRESULT hr = dmusic->Activate(TRUE);
    if (FAILED(hr))
        return BACH_ERR_DMFAILED;

    return BACH_ERR_NONE;
}

//���������������������������������������������������������������������������
// BachMusic - deactivate
//���������������������������������������������������������������������������
bach_err_codes BachMusic::deactivate()
{
    if (!dmusic)
        return BACH_ERR_UNINITIALIZED;

    HRESULT hr = dmusic->Activate(FALSE);
    if (FAILED(hr))
        return BACH_ERR_DMFAILED;

    return BACH_ERR_NONE;
}

//��� End of module - bachmus.cpp ���
