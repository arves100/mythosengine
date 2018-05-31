//���������������������������������������������������������������������������
//
//                                /\    /\
//                               /  \  /  \
//                              /    \/    \
//                             /  /\    /\  \
//                            /  /  \  /  Y T H O S
//                           /  /    \/    \  \
//                          /  /            \  \
//                         /__/              \__\
//
//                  Microsoft Windows 95/98/NT Version
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
//                          LUNAR LANDER EXAMPLE
//
// Created by Chuck Walbourn and Dan Higdon
//
// llend.cpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "llander.hpp"

#include "llevt.hpp"

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// Constructor - LanderEnd
//���������������������������������������������������������������������������
LanderEnd::LanderEnd() :
    evt (0)
{
};


//���������������������������������������������������������������������������
// Destructor - LanderEnd
//���������������������������������������������������������������������������
LanderEnd::~LanderEnd()
{
    deactivate();
};



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// LanderEnd - activate
//���������������������������������������������������������������������������
void LanderEnd::activate()
{
    gberg_color(Screen->find(VngoColor24bit(255,255,0)), VNGO_TRANSPARENT);

    int waslocked=Screen->lock();

    SimText st(Screen);
    char    buf[64];

    gberg_select_font ("12x24");
    if (crashed)
        wsprintf (buf, "You crashed with dx = %d, dy = %d at %d frames/sec\n",
                       lander_dx, lander_dy, frame_rate);
    else
        wsprintf (buf, "You landed with dx = %d, dy = %d at %d frames/sec\n",
                       lander_dx, lander_dy, frame_rate);

    st.out (buf);

    Screen->invalidate();

    if (!waslocked)
        Screen->unlock();

//��� Create event system
    evt = new MaxEventUser (*Devs);

    if (!evt
        || evt->load (szIFF,0) != 0)
        panic("LanderEnd::activate fail for event");

    evt->install();

}


//���������������������������������������������������������������������������
// LanderEnd - deactivate
//���������������������������������������������������������������������������
void LanderEnd::deactivate()
{
    if (evt)
    {
        delete evt;
        evt = 0;
    }
}


//���������������������������������������������������������������������������
// LanderEnd - process_events
//���������������������������������������������������������������������������
void LanderEnd::process_events()
{
    MaxEventList events = evt->process();

    if (events.check (QUIT))
        theSim.exit();

    if (events.check (NEXT))
        switch_to(theSim.game);
}


//���������������������������������������������������������������������������
// LanderEnd - render
//���������������������������������������������������������������������������
void LanderEnd::render()
{
}

//��� eof - llend.cpp ���
