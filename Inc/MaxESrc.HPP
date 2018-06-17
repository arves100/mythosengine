//���������������������������������������������������������������������������
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
// Created by Dan Higdon
//
// maxesrc.hpp
//
// Event Source
//
//  EventSource --  This class associates Events with EventTriggers,
//                  and contains the physical device objects that can be
//                  shown to EventTriggers.
//
//���������������������������������������������������������������������������

#ifndef __MAXESRC_HPP
#define __MAXESRC_HPP    1

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <string.h>
#include <portable.h>

#include <xfile.hpp>

#include "maxdevs.hpp"
#include "maxevt.hpp"

//���������������������������������������������������������������������������
//
//                                Pragmas
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                               Structures
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������


//���������������������������������������������������������������������������
// This is the basic event source notion.  All event sources descend
// from this class, and add whatever functionality they need.
//���������������������������������������������������������������������������
class MaxEventSource
{
public:
        MaxEventSource ()  { }
virtual ~MaxEventSource () { }

        // Enable/disable the EventSource.
virtual void    install () = 0;
virtual void    uninstall () = 0;

        // Allow any applicable Events to run, return #events processed.
virtual MaxEventList process (const MaxEventList & = MaxEventList (1)) = 0;
        MaxEventList process_wait (const MaxEventList & = MaxEventList (1));

        // Virtualization of the input devices.
virtual void get_mouse_movement (short *, short *) const    { }
virtual void get_mouse_pos (short *, short *) const         { }
virtual void set_mouse_pos (short, short)                   { }
virtual byte get_mouse_buttons () const                     { return 0; }
virtual int  check_key (int) const                          { return 0; }
virtual void get_joystick (JOYINFOEX *) const               { }
};


//���������������������������������������������������������������������������
// This class associates EventTriggers and Events, and provides a
// framework for checking EventTriggers against a set of input devices.
//���������������������������������������������������������������������������
class MaxEventUser: public MaxEventSource
{
private:
        // This private class provides storage for event bindings.
        class EventBinding
        {
        public:
                EventBinding        *next;
                const MaxTrigger    &trigger;
                const MaxEvent      event;

                EventBinding (const MaxTrigger &, MaxEvent, EventBinding * = 0);

                // Equality is not concerned with the next pointer.
                int operator == (const EventBinding &) const;
        };

        EventBinding    *bindings;
        MaxTrigger      *TRGS;
        int             ntriggers;

public:
        // This simple struct defines the header type used by
        // the MaxEventUser to read the IFF data.
        struct MaxHeader
        {
            char    name[12];   // Actually 8+null+padding
            ulong   num_trigs;
        };

        // The physical input devices.  Anyone can query these.
        MaxDevices  &theDevices;

        // Construction of the EventSource.  Initially, it is disabled.
        MaxEventUser    (MaxDevices &, const char * = 0, const char * = 0);
        ~MaxEventUser   ();

        // Load an event system from an IFF file
        int load (const char *fname, const char *ename = 0);
        int load (XFParseIFF *iffp, const char *ename = 0);

        // Enable/disable the EventSource.
        void install    ();
        void uninstall  ();

        // Event association members.
        void connect    (const MaxTrigger &, MaxEvent);
        void disconnect (const MaxTrigger &, MaxEvent);

        // Enumerate the triggers.
        void enumerate_triggers (int (*func) (MaxTrigger *));

        // Empty the trigger bindings
        void clear ();

        // Allow any applicable Events to run, return #events processed.
        MaxEventList process (const MaxEventList & = MaxEventList (1));

        // Support the virtual devices with physical ones!
        void get_mouse_movement (short *, short *) const;
        void get_mouse_pos (short *, short *) const;
        void set_mouse_pos (short, short);
        byte get_mouse_buttons () const;
        int  check_key (int) const;
        void get_joystick (JOYINFOEX *) const;
};


//���������������������������������������������������������������������������
//
//                               Inlines
//
//���������������������������������������������������������������������������


//���������������������������������������������������������������������������
//  These are the inline expansions of some of the MaxEventUser members.
//  Only fairly basic "pass-through" members have been inlined here.
//���������������������������������������������������������������������������

inline MaxEventUser::EventBinding::EventBinding (const MaxTrigger &t, MaxEvent e, EventBinding *n):
    trigger (t),
    event (e),
    next (n)
{
}


//���������������������������������������������������������������������������
//  MaxEventUser::EventBinding operator ==
//
//���������������������������������������������������������������������������
inline int MaxEventUser::EventBinding::operator == (const EventBinding &bind) const
{
    return trigger == bind.trigger && event == bind.event;
}


//���������������������������������������������������������������������������
//  MaxEventUser::get_mouse_movement
//
//���������������������������������������������������������������������������
inline void MaxEventUser::get_mouse_movement (short *dx, short *dy) const
{
    theDevices.get_mouse_movement (dx, dy);
}


//���������������������������������������������������������������������������
//  MaxEventUser::get_mouse_pos
//
//���������������������������������������������������������������������������
inline void MaxEventUser::get_mouse_pos (short *x, short *y) const
{
    theDevices.get_mouse_pos (x, y);
}


//���������������������������������������������������������������������������
//  MaxEventUser::set_mouse_pos
//
//���������������������������������������������������������������������������
inline void MaxEventUser::set_mouse_pos (short x, short y)
{
    theDevices.set_mouse_pos (x, y);
}


//���������������������������������������������������������������������������
//  MaxEventUser::get_mouse_buttons
//
//���������������������������������������������������������������������������
inline byte MaxEventUser::get_mouse_buttons () const
{
    return theDevices.get_mouse_buttons ();
}


//���������������������������������������������������������������������������
//  MaxEventUser::check_key
//
//���������������������������������������������������������������������������
inline int MaxEventUser::check_key (int key) const
{
    return theDevices.check_keyboard_key (key);
}


//���������������������������������������������������������������������������
//  MaxEventUser::get_joystick
//
//���������������������������������������������������������������������������
inline void MaxEventUser::get_joystick (JOYINFOEX *js) const
{
    theDevices.get_joystick (js);
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//��� End of header - maxesrc.hpp ���
