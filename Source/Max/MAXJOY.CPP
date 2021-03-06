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
// maxjoy.cpp
//
// Event Devices
//
//      This module defines the physical devices used by the event
//  system.  Each device has a unique interface, suited to the device.
//
//  Joystick -- The standard IBM Joystick.  Like the mouse, this device
//          can only be queried for its current state.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <Max.hpp>

#include <assert.h>
#include <string.h>

#include <windows.h>

#include <ivory.hpp>

#include "maxdevs.hpp"
#include "maxjoy.hpp"

#include <iostream>

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
//                              Static Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                     MaxJoystick Member Functions
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystick Constructor
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxJoystick::MaxJoystick():
    joy_present (0),
    initialized (false),
    auto_polled (0),
    timer_id (0)
{
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystick Destructor
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxJoystick::~MaxJoystick()
{
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystick::clear
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void MaxJoystick::clear()
{
    // NOP
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystick::get_di2
//      Returns a pointer to IDirectInput2, or NULL
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
IDirectInputDevice2 *MaxJoystick::get_di2() const
{
    return 0;
}


//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                     MaxJoystickWin32 Member Functions
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickWin32 Constructor
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxJoystickWin32::MaxJoystickWin32():
    MaxJoystick ()
{
    // Make sure this starts off empty
    memset (&info, 0, sizeof (info));
    info.dwSize  = sizeof (JOYINFOEX);
    info.dwFlags = JOY_RETURNALL | JOY_RETURNCENTERED | JOY_USEDEADZONE;

    memset (&caps, 0, sizeof (caps));

    joy_present = short (joyGetNumDevs());
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickWin32 Destructor
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxJoystickWin32::~MaxJoystickWin32()
{
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickWin32::init
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
short MaxJoystickWin32::init ()
{
    if (joy_present)
    {
        // Fill in the capabilities
        joyGetDevCaps (0, &caps, sizeof (caps));

        // Get the initial state of the joystick.
        // (In autopoll it would otherwise be possible to get the value before a poll cycle)
        info.dwSize = sizeof (JOYINFOEX);
        info.dwFlags = JOY_RETURNALL | JOY_RETURNCENTERED | JOY_USEDEADZONE;
        if (joyGetPosEx (0, &info) != JOYERR_NOERROR)
            joy_present = 0;
    }

    initialized = joy_present != 0;
    return joy_present;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickWin32::uninit
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void MaxJoystickWin32::uninit()
{
    initialized = false;
    if (timer_id)
    {
        timeKillEvent (timer_id);
        timer_id = 0;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickWin32::get_stat
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void MaxJoystickWin32::get_stat (JOYINFOEX *stat) const
{
    if (joy_present && initialized)
    {
        if (auto_polled)
        {
            // Assume that the current info struct has been filled in
            // by the user
            *stat = info;

            // This const_cast is needed because this member is only const
            // while not in auto_poll mode.
            const_cast<MaxJoystickWin32 *>(this)->info.dwButtons = 0;
        }
        else
        {
            stat->dwSize = sizeof (JOYINFOEX);
            stat->dwFlags = JOY_RETURNALL | JOY_RETURNCENTERED | JOY_USEDEADZONE;
            joyGetPosEx (0, stat);

            // Now, cook the values so that they are normalized from 0..65536
            if (caps.wNumAxes > 0)
            {
                dword dwXrange (caps.wXmax - caps.wXmin);
                if (dwXrange)
                {
                    dword xpos (stat->dwXpos - caps.wXmin);
                    xpos = (xpos << 16) / dwXrange;
                    stat->dwXpos = xpos;
                }
            }

            if (caps.wNumAxes > 1)
            {
                dword dwYrange (caps.wYmax - caps.wYmin);
                if (dwYrange)
                {
                    dword ypos (stat->dwYpos - caps.wYmin);
                    ypos = (ypos << 16) / dwYrange;
                    stat->dwYpos = ypos;
                }
            }

            if (caps.wNumAxes > 2)
            {
                dword dwZrange (caps.wZmax - caps.wZmin);
                if (dwZrange)
                {
                    dword zpos (stat->dwZpos - caps.wZmin);
                    zpos = (zpos << 16) / dwZrange;
                    stat->dwZpos = zpos;
                }
            }
        }
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// MaxJoystickWin32::auto_poll
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void CALLBACK MaxJoystickWin32::win32_poll_routine (UINT idTimer,
                                                    UINT msg,
                                                    DWORD dwUser,
                                                    DWORD dw1,
                                                    DWORD dw2)
{
    MaxJoystickWin32 *p = (MaxJoystickWin32 *)dwUser;
    DWORD old_buttons = p->info.dwButtons;
    joyGetPosEx (0, &p->info);
    p->info.dwButtons |= old_buttons;
}


int MaxJoystickWin32::auto_poll (BOOL activate, UINT rate)
{
    auto_polled = activate;

    if (activate)
    {
        timer_id = timeSetEvent (rate, rate, win32_poll_routine, DWORD (this), TIME_PERIODIC);
        return timer_id != 0;
    }
    else
    {
        if (timer_id)
        {
            timeKillEvent (timer_id);
            timer_id = 0;
        }
        return 0;
    }
}


//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                     MaxJoystickDirectX Member Functions
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

BOOL CALLBACK joy_enum_callback (LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef)
{
    LPGUID pguid = static_cast <LPGUID> (pvRef);

    // We only enumerate Joysticks, so in this case, take the first one we get
    *pguid = pdinst->guidInstance;
    return DIENUM_STOP;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickDirectX Constructor
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxJoystickDirectX::MaxJoystickDirectX (IDirectInput *pdi, HWND _hwnd):
    MaxJoystick (),
    pdid (0)
{
    HRESULT hr;

    // Find the GUID of the joystick device
    GUID guid_joy;
    hr = pdi->EnumDevices (DIDEVTYPE_JOYSTICK,
                           joy_enum_callback,
                           (LPVOID)&guid_joy,
                           DIEDFL_ATTACHEDONLY);

    // If a joystick exists, create an interface to it
    if (SUCCEEDED(hr))
    {
        IDirectInputDevice *pdev;
        hr = pdi->CreateDevice (guid_joy, &pdev, NULL);

        // Obtain an IDirectInputDevice2 interface
        if (SUCCEEDED(hr))
        {
            hr = pdev->QueryInterface (IID_IDirectInputDevice2, (void **)&pdid);
            pdev->Release();
            if (!SUCCEEDED(hr))
                pdid = 0;

            pdid->SetDataFormat (&c_dfDIJoystick);
            pdid->SetCooperativeLevel (_hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
        }
    }

    joy_present = (pdid != 0);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickDirectX Destructor
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
MaxJoystickDirectX::~MaxJoystickDirectX()
{
    if (pdid)
    {
        pdid->Unacquire();
        pdid->Release();
        pdid = 0;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickDirectX::get_di2
//      Returns a pointer to IDirectInput2, or NULL
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
IDirectInputDevice2 *MaxJoystickDirectX::get_di2() const
{
    return pdid;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickDirectX::init
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
short MaxJoystickDirectX::init ()
{
    if (joy_present)
    {
//        pdid->SetDataFormat (&c_dfDIJoystick);
        dicaps.dwSize = sizeof (DIDEVCAPS);
        pdid->GetCapabilities (&dicaps);

#if 0
        // Set the Joystick up for buffered access
        // THIS HAPPENS IN AUTO_POLL ENABLE NOW!
        DIPROPDWORD prop;
        prop.diph.dwSize = sizeof (DIPROPDWORD);
        prop.diph.dwHeaderSize = sizeof (DIPROPHEADER);
        prop.diph.dwObj = 0;
        prop.diph.dwHow = DIPH_DEVICE;
        prop.dwData = DIDATA_SIZE;
        pdid->SetProperty (DIPROP_BUFFERSIZE, &prop.diph);
#endif

        // Finally, aquire the device
        HRESULT hr = pdid->Acquire();
        initialized = SUCCEEDED (hr);
    }

    return joy_present;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickDirectX::uninit
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void MaxJoystickDirectX::uninit()
{
    initialized = false;
    if (pdid)
        pdid->Unacquire();

    if (timer_id)
    {
        timeKillEvent (timer_id);
        timer_id = 0;
    }

    auto_polled = 0;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  MaxJoystickDirectX::get_stat
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void MaxJoystickDirectX::get_stat (JOYINFOEX *stat) const
{
    HRESULT hr;

    if (!pdid || !initialized)
    {
        memset (stat, 0, sizeof (*stat));
        return;
    }

    if (!auto_polled)
        pdid->Poll();

    // Get the DirectInput data
    DIJOYSTATE distat;
    memset (&distat, 0, sizeof (DIJOYSTATE));
    while (pdid->GetDeviceState (sizeof (distat), &distat) == DIERR_INPUTLOST)
    {
        hr = pdid->Acquire();

        // We can't reacquire, so don't go any further
        if (!SUCCEEDED (hr))
        {
            memset (stat, 0, sizeof (*stat));
            return;
        }
    }

    // Fill in the JOYINFOEX structure
    stat->dwSize  = sizeof (JOYINFOEX);
    stat->dwFlags = JOY_RETURNALL | JOY_RETURNCENTERED | JOY_USEDEADZONE;
    stat->dwXpos  = distat.lX;
    stat->dwYpos  = distat.lY;
    stat->dwZpos  = distat.lZ;
    stat->dwRpos  = distat.lRx;
    stat->dwUpos  = distat.lRy;
    stat->dwVpos  = distat.lRz;
    stat->dwButtonNumber = 0;

    if (dicaps.dwPOVs > 0)
        stat->dwPOV = distat.rgdwPOV[0];
    else
        stat->dwPOV = JOY_POVCENTERED;

    // Compute and store the button state
    assert (dicaps.dwButtons <= 32);
    dword d = 0;
    for (int i = dicaps.dwButtons-1; i >= 0; i--)
    {
        d <<= 1;
        if (distat.rgbButtons[i] & 0x80)
            d |= 1;
    }
    stat->dwButtons = d;

    // If we are in auto_polled mode, it is possible that our polling
    // routine found buttons that when down and up again between calls
    // to get_stat.  If this might be true, we need to scan the buffered
    // data for button down messages.  If any are there, we should report
    // the button as down this time, even though it may no longer be
    // depressed.  Subsequent calls will return the "real" value.  The
    // one case this DOESN'T catch is if the button is pressed more than
    // once.  Since the Max event system has no way of dealing with this case,
    // the data will simply be lost.  Since this would happen without auto
    // polling anyway, it is judged to be acceptable under the current
    // limitations of Max.
    if (auto_polled)
    {
        // Process data
        DIDEVICEOBJECTDATA od[DIDATA_SIZE];
        DWORD size = DIDATA_SIZE;
        while (pdid->GetDeviceData (sizeof (DIDEVICEOBJECTDATA),
                                    od,
                                    &size,
                                    0) == DIERR_INPUTLOST)
        {
            HRESULT hr = pdid->Acquire();
            if (!SUCCEEDED (hr))
                return;
        }

        for (dword i = 0; i < size; i++)
        {
            switch (od[i].dwOfs)
            {
                case DIJOFS_BUTTON0:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000001;
                    break;
                case DIJOFS_BUTTON1:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000002;
                    break;
                case DIJOFS_BUTTON2:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000004;
                    break;
                case DIJOFS_BUTTON3:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000008;
                    break;
                case DIJOFS_BUTTON4:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000010;
                    break;
                case DIJOFS_BUTTON5:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000020;
                    break;
                case DIJOFS_BUTTON6:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000040;
                    break;
                case DIJOFS_BUTTON7:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000080;
                    break;
                case DIJOFS_BUTTON8:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000100;
                    break;
                case DIJOFS_BUTTON9:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000200;
                    break;
                case DIJOFS_BUTTON10:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000400;
                    break;
                case DIJOFS_BUTTON11:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00000800;
                    break;
                case DIJOFS_BUTTON12:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00001000;
                    break;
                case DIJOFS_BUTTON13:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00002000;
                    break;
                case DIJOFS_BUTTON14:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00004000;
                    break;
                case DIJOFS_BUTTON15:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00008000;
                    break;
                case DIJOFS_BUTTON16:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00010000;
                    break;
                case DIJOFS_BUTTON17:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00020000;
                    break;
                case DIJOFS_BUTTON18:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00040000;
                    break;
                case DIJOFS_BUTTON19:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00080000;
                    break;
                case DIJOFS_BUTTON20:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00100000;
                    break;
                case DIJOFS_BUTTON21:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00200000;
                    break;
                case DIJOFS_BUTTON22:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00400000;
                    break;
                case DIJOFS_BUTTON23:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x00800000;
                    break;
                case DIJOFS_BUTTON24:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x01000000;
                    break;
                case DIJOFS_BUTTON25:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x02000000;
                    break;
                case DIJOFS_BUTTON26:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x04000000;
                    break;
                case DIJOFS_BUTTON27:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x08000000;
                    break;
                case DIJOFS_BUTTON28:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x10000000;
                    break;
                case DIJOFS_BUTTON29:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x20000000;
                    break;
                case DIJOFS_BUTTON30:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x40000000;
                    break;
                case DIJOFS_BUTTON31:
                    if (od[i].dwData & 0x80)
                        stat->dwButtons |= 0x80000000;
                    break;
            }
        }
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// MaxJoystickDirectX::auto_poll
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void CALLBACK MaxJoystickDirectX::di_poll_routine (UINT idTimer, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    MaxJoystickDirectX *p = reinterpret_cast <MaxJoystickDirectX *> (dwUser);

    if (p->pdid)
        p->pdid->Poll();
}


int MaxJoystickDirectX::auto_poll (BOOL activate, UINT rate)
{
    if (!pdid || !initialized)
        return 0;

    auto_polled = activate;

    if (activate)
    {
        bool was_acquired (pdid->Unacquire() == DI_OK);

        // Set the Joystick up for buffered access
        DIPROPDWORD prop;
        prop.diph.dwSize = sizeof (DIPROPDWORD);
        prop.diph.dwHeaderSize = sizeof (DIPROPHEADER);
        prop.diph.dwObj = 0;
        prop.diph.dwHow = DIPH_DEVICE;
        prop.dwData = DIDATA_SIZE;
        pdid->SetProperty (DIPROP_BUFFERSIZE, &prop.diph);

        if (was_acquired)
            pdid->Acquire();

        timer_id = timeSetEvent (rate, rate, di_poll_routine, DWORD (this), TIME_PERIODIC);
        return timer_id != 0;
    }
    else
    {
        bool was_acquired (pdid->Unacquire() == DI_OK);

        // Cancel buffered access
        DIPROPDWORD prop;
        prop.diph.dwSize = sizeof (DIPROPDWORD);
        prop.diph.dwHeaderSize = sizeof (DIPROPHEADER);
        prop.diph.dwObj = 0;
        prop.diph.dwHow = DIPH_DEVICE;
        prop.dwData = 0;
        pdid->SetProperty (DIPROP_BUFFERSIZE, &prop.diph);

        if (was_acquired)
            pdid->Acquire();

        if (timer_id)
        {
            timeKillEvent (timer_id);
            timer_id = 0;
        }
        return 0;
    }
}


//葦� End of module - maxjoy.cpp 憶�
