//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//                  ooo        ooooo
//                  `88.       .888'
//                   888b     d'888   .oooo.   oooo    ooo
//                   8 Y88. .P  888  `P  )88b   `88b..8P'
//                   8  `888'   888   .oP"888     Y888'
//                   8    Y     888  d8(  888   .o8"'88b
//                  o8o        o888o `Y888""8o o88'   888o
//
//                          Across the event horizon...
//
//                       Microsoft Windows 95/98/NT Version
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
// Created by Dan Higdon
//
// maxevt.cpp
//
// Events and Triggers
//
//      This module defines the types used in the Event system.
// The following types are defined within:
//  Event -- The concept of an event that the user is interested in,
//          such as "balance shields", or "fire lasers".
//  EventList -- A collection of Events.  Events may be added to or removed
//          from the list, as well as checked for presence.  Technically,
//          this structure is a Set, but List is close enough. :-)
//  EventTrigger -- A user action, classified in terms of keypress
//          combinations and mouse moves/button presses.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <Max.hpp>
#include <assert.h>
#include <ivory.hpp>
#include <xfile.hpp>

#include "maxevt.hpp"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Structures
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                               Routines
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// Now, for an extensive array of boolean operations on EventLists.
// These are not inlined, since they are relatively complex, and it seems
// unlikely that the call time would outweigh the execution time.
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

const int EVENT_DWORDS = EVENT_MAX_EVENT / (8 * sizeof (dword));
typedef dword *pdword;


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList::empty
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
int MaxEventList::empty () const
{
    for (int i = 0; i < EVENT_DWORDS; i++)
        if (((pdword)mask)[i] != 0)
            return 0;
    return 1;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList operator ~
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxEventList MaxEventList::operator ~() const
{
    MaxEventList res;
    for (int i = 0; i < EVENT_DWORDS; i++)
        ((pdword)res.mask)[i] = ~((pdword)mask)[i];
    return res;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList operator ^
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxEventList MaxEventList::operator ^ (const MaxEventList &el) const
{
    MaxEventList res;
    for (int i = 0; i < EVENT_DWORDS; i++)
        ((pdword)res.mask)[i] = ((pdword)mask)[i] ^ ((pdword)el.mask)[i];
    return res;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList operator |
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxEventList MaxEventList::operator | (const MaxEventList &el) const
{
    MaxEventList res;
    for (int i = 0; i < EVENT_DWORDS; i++)
        ((pdword)res.mask)[i] = ((pdword)mask)[i] | ((pdword)el.mask)[i];
    return res;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList operator &
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxEventList MaxEventList::operator & (const MaxEventList &el) const
{
    MaxEventList res;
    for (int i = 0; i < EVENT_DWORDS; i++)
        ((pdword)res.mask)[i] = ((pdword)mask)[i] & ((pdword)el.mask)[i];
    return res;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList operator =
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxEventList &MaxEventList::operator = (const MaxEventList &el)
{
    memcpy (mask, el.mask, sizeof (mask));
    return *this;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList operator ^=
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxEventList &MaxEventList::operator ^= (const MaxEventList &el)
{
    for (int i = 0; i < EVENT_DWORDS; i++)
        ((pdword)mask)[i] ^= ((pdword)el.mask)[i];
    return *this;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList operator |=
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxEventList &MaxEventList::operator |= (const MaxEventList &el)
{
    for (int i = 0; i < EVENT_DWORDS; i++)
        ((pdword)mask)[i] |= ((pdword)el.mask)[i];
    return *this;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxEventList operator &=
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxEventList &MaxEventList::operator &= (const MaxEventList &el)
{
    for (int i = 0; i < EVENT_DWORDS; i++)
        ((pdword)mask)[i] &= ((pdword)el.mask)[i];
    return *this;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  Create an EventTrigger that will trigger always.                        �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxTrigger::MaxTrigger ()
{
    for (int i = 0; i < max_keys; i++)
        Keys[i] = word (-1);

    MouseButtons = 0;
    JoyButtons   = 0;
    BegX = EndX = -1;
    BegY = EndY = -1;
    DeltaX = DeltaY = -1;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  Does this trigger check the mouse status?                               �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
int MaxTrigger::uses_mouse () const
{
    return MouseButtons != 0
    ||     BegX != -1
    ||     BegY != -1
    ||     EndX != -1
    ||     EndY != -1
    ||     DeltaX != -1
    ||     DeltaY != -1;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  Does this trigger check the keyboard status?                            �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
int MaxTrigger::uses_keyboard () const
{
    return Keys[0] != -1;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  Does this trigger use the joystick status?                              �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
int MaxTrigger::uses_joystick () const
{
    return JoyButtons != 0;
}

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  Check the EventTrigger against the passed input source.                 �
//      Triggers are always true unless there are constraints that don't    �
//      match, in which case they return false.                             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
int MaxTrigger::check (const MaxDevices &devs) const
{
    // First, the keyboard part
    for (int i = 0; Keys[i] != word (-1) && i < max_keys; i++)
    {
        const ushort key (Keys[i]);
        BOOL match = false;

        // Special case of the "generic shift key"
        if (key & 0x400)
        {
            const ushort mkey (key & 0x4ff);
            switch (mkey)
            {
                case 0x401:
                    match = devs.check_keyboard_key (DIK_LALT)
                            || devs.check_keyboard_key (DIK_RALT);
                    break;

                case 0x402:
                    match = devs.check_keyboard_key (DIK_LCONTROL)
                            || devs.check_keyboard_key (DIK_RCONTROL);
                    break;

                case 0x403:
                    match = devs.check_keyboard_key (DIK_LSHIFT)
                            || devs.check_keyboard_key (DIK_RSHIFT);
                    break;
            }
        }
        else
            match = devs.check_keyboard_key (key & 0xff) != 0;

        // Straight compare, or negation?
        if (key & 0x200)
            match = !match;

        // If this key doesn't match, then the trigger doesn't match
        if (!match)
            return 0;
    }

    // Now, check the mouse
    LONG   mx, my, dx, dy;

    devs.get_mouse_pos (&mx, &my);
    devs.get_mouse_movement (&dx, &dy);

    if (BegX != -1 && EndX != -1)
        if (mx < BegX || mx > EndX)
            return 0;

    if (BegY != -1 && EndY != -1)
        if (my < BegY || my > EndY)
            return 0;

    if (DeltaX != -1 && DeltaY != -1)
        if ((dx < DeltaX && dx > -DeltaX) ||
            (dy < DeltaY && dy > -DeltaY))
            return 0;

    if (MouseButtons)
        if ((devs.get_mouse_buttons() & MouseButtons) != MouseButtons)
            return 0;

    // Now, check the joystick
    if (JoyButtons)
    {
        JOYINFOEX jstat;
        devs.get_joystick (&jstat);

        if ((jstat.dwButtons & JoyButtons) != JoyButtons)
            return 0;
    }

    // Otherwise, either all cases match, or there were no constraints.
    // Either way, this trigger may fire!
    return 1;
}

//葦� End of module - maxevt.cpp 憶�
