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
// bachsseq.cpp
//
// Static sample sequencer implementation for playing back one sample after
// another
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <windows.h>

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
// BachSampleSequencer - Constructor
//���������������������������������������������������������������������������
BachSampleSequencer::BachSampleSequencer ():
    thread_handle (0),
    thread_event (0),
    sequence (0),
    flags(0)
{
}


//���������������������������������������������������������������������������
// BachSampleSequencer - Destructor
//���������������������������������������������������������������������������
BachSampleSequencer::~BachSampleSequencer ()
{
    release();
}



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// BachSampleSequencer - release
//���������������������������������������������������������������������������
void BachSampleSequencer::release()
{
    if (thread_handle)
    {
        EnterCriticalSection (&critical_section);

        TerminateThread (thread_handle, 0);
        WaitForSingleObject (thread_handle, INFINITE);
        CloseHandle (thread_handle);
    }

    stop(1);

    if (thread_handle)
    {
        DeleteCriticalSection (&critical_section);
        thread_handle = 0;
    }

    if (thread_event)
    {
        CloseHandle(thread_event);
        thread_event = 0;
    }

    flags &= ~BACH_SSEQ_OWNSSAMPLES;
}


//���������������������������������������������������������������������������
// BachSampleSequencer - init
//���������������������������������������������������������������������������
bach_err_codes BachSampleSequencer::init()
{
    if (thread_handle)
        return BACH_ERR_NONE;

    DWORD thread_id;
    thread_handle = CreateThread (NULL, 4 * 1024, thread_proc, this,
                                  CREATE_SUSPENDED, &thread_id);
    if (!thread_handle)
        return BACH_ERR_THREADFAILED;

    thread_event = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!thread_event)
    {
        TerminateThread(thread_handle, 0);
        thread_handle = 0;
        return BACH_ERR_EVENTFAILED;
    }

    InitializeCriticalSection (&critical_section);

    return BACH_ERR_NONE;
}


//���������������������������������������������������������������������������
// BachSampleSequencer - add
//���������������������������������������������������������������������������
bach_err_codes BachSampleSequencer::add (BachStaticSample *sample,
                                         int start_play)
{
    if (!sample)
        return BACH_ERR_INVALIDPARAMS;

    if (!thread_handle)
    {
        bach_err_codes err = init();
        if (err)
            return err;
    }

//��� Add to sequence list
    EnterCriticalSection (&critical_section);

    const BOOL resume = (sequence == 0);

    Link *p = new Link (sample);
    if (!p)
    {
        LeaveCriticalSection (&critical_section);
        return BACH_ERR_OUTOFMEMORY;
    }

    sample->set_position(0);

    if (sequence == 0)
        sequence = p;
    else
    {
        for (Link *s = sequence; s->next != 0; s = s->next)
            ;
        s->next = p;
    }

    LeaveCriticalSection (&critical_section);

//��� Wake-up thread if we need to
    if (resume && start_play)
        ResumeThread (thread_handle);

    return BACH_ERR_NONE;
}


//���������������������������������������������������������������������������
// BachSampleSequencer - next
//���������������������������������������������������������������������������
BachStaticSample *BachSampleSequencer::next ()
{
    if (!thread_handle)
        return 0;

    EnterCriticalSection (&critical_section);

    if (sequence)
    {
        Link *p = sequence;

        p->sample->stop();
        sequence = p->next;

        if (flags & BACH_SSEQ_OWNSSAMPLES)
            delete p->sample;

        delete p;

        if (sequence)
        {
            ResumeThread(thread_handle);
            SetEvent(thread_event);
        }
    }

    LeaveCriticalSection (&critical_section);

    return (sequence) ? sequence->sample : 0;
}


//���������������������������������������������������������������������������
// BachSampleSequencer - play
//���������������������������������������������������������������������������
bach_err_codes BachSampleSequencer::play ()
{
    if (!thread_handle)
        return BACH_ERR_UNINITIALIZED;

    if (sequence)
    {
        ResumeThread (thread_handle);
    }

    return BACH_ERR_NONE;
}


//���������������������������������������������������������������������������
// BachSampleSequencer - stop
//���������������������������������������������������������������������������
void BachSampleSequencer::stop (int stop_current)
{
    if (thread_handle)
        EnterCriticalSection (&critical_section);

    if (sequence != 0)
    {
        if (stop_current)
        {
            // Stop the first one
            sequence->sample->stop();

            // Clean them all up
            while (sequence != 0)
            {
                Link *tp = sequence->next;

                if (flags & BACH_SSEQ_OWNSSAMPLES)
                    delete tp->sample;

                delete sequence;
                sequence = tp;
            }

            ResumeThread (thread_handle);
            SetEvent(thread_event);
        }
        else
        {
            // Skip the first one (terminate the link chain)
            Link *p = sequence->next;
            sequence->next = 0;
            while (p != 0)
            {
                Link *tp = p->next;

                if (flags & BACH_SSEQ_OWNSSAMPLES)
                    delete p->sample;

                delete p;
                p = tp;
            }
        }
    }

    if (thread_handle)
        LeaveCriticalSection (&critical_section);
}


//���������������������������������������������������������������������������
// BachSampleSequencer - get_playtime
//���������������������������������������������������������������������������
ulong BachSampleSequencer::get_playtime ()
{
    ulong   t = 0;

    if (thread_handle)
        EnterCriticalSection (&critical_section);

    Link *p = sequence;

    while (p)
    {
        t += p->sample->get_playtime ();
        p = p->next;
    }

    if (thread_handle)
        LeaveCriticalSection (&critical_section);

    return t;
}


//���������������������������������������������������������������������������
//                            �� Protected ��
// BachSampleSequencer - thread_proc
//���������������������������������������������������������������������������
DWORD CALLBACK BachSampleSequencer::thread_proc (LPVOID lpUser)
{
    BachSampleSequencer *that = (BachSampleSequencer *)lpUser;

    assertMyth("BachSampleSequencer::thread_proc needs valid lpUser",
               lpUser != 0);

    for (;;)
    {
        EnterCriticalSection (&that->critical_section);

        if (that->sequence != 0)
        {
            // Decide how long to sleep
            BachStaticSample *psamp = that->sequence->sample;
            assert (psamp);

            ULONG sleep_time = psamp->get_playtime ();
            psamp->play();

            LeaveCriticalSection (&that->critical_section);

            if (WaitForSingleObject(that->thread_event, sleep_time)
                        == WAIT_TIMEOUT)
            {
                that->next();
            }
        }
        else
        {
            // We don't have a sequence, so just suspend until we're needed
            LeaveCriticalSection (&that->critical_section);

            SuspendThread (GetCurrentThread());
        }
    }

    // This thread expects to be killed manually
    return 0;
}

//��� End of module - bachsseq.cpp ���
