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
// simulatr.cpp
//
// This module contains the simulator-specific state management class.
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
// SimulatorState - Constructor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
SimulatorState::SimulatorState() :
     ui (0),
     objects (0),
     temps (0),
     timeshift (0)
{
    memset(teams, 0, sizeof(teams));
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimulatorState - Destructor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
SimulatorState::~SimulatorState()
{
    deactivate();
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimulatorState - activate
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimulatorState::activate ()
{
//陳� Create model storage
    obj_hi = 0;
    obj_max = SIM_INIT_OBJECTS;
    objects = new SimObject *[SIM_INIT_OBJECTS];
    if (!objects)
    {
        panic(IDS_SIM_NOMEMORY,"SimulatorState::activate");
        return;
    }
    memset(objects, 0, sizeof(SimObject*) * SIM_INIT_OBJECTS);

    temp_hi = 0;
    temp_max = SIM_INIT_TEMPS;
    temps = new SimTemp *[SIM_INIT_TEMPS];
    if (!temps)
    {
        panic(IDS_SIM_NOMEMORY,"SimulatorState::activate");
        return;
    }
    memset(temps, 0, sizeof(SimTemp*) * SIM_INIT_TEMPS);

    for (int t=0; t < SIM_MAX_TEAMS; t++)
    {
        sim_team_t *st = &teams[t];

        st->unit_hi = 0;
        st->unit_max = SIM_INIT_UNITS;
        st->units = new SimUnit *[SIM_INIT_UNITS];
        if (!st->units)
        {
            panic(IDS_SIM_NOMEMORY,"SimulatorState::activate");
            return;
        }
        memset(st->units, 0, sizeof(SimUnit*) * SIM_INIT_UNITS);

        st->ofld_hi = 0;
        st->ofld_max = SIM_INIT_OFFIELDS;
        st->offields = new SimOffield *[SIM_INIT_OFFIELDS];
        if (!st->offields)
        {
            panic(IDS_SIM_NOMEMORY,"SimulatorState::activate");
            return;
        }
        memset(st->offields, 0, sizeof(SimOffield*) * SIM_INIT_OFFIELDS);
    }

    timebase=0;
    time_now=0;

//陳� Startup UI
    assertMyth("SimulatorState::activate needs valid starting ui", ui != 0);

    ui->activate();

    clock.clear();
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimulatorState - deactivate
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimulatorState::deactivate ()
{
//陳� Terminate UI
    if (ui)
        ui->deactivate();

//陳� Destroy model storage
    if (objects)
    {
        for(int i=0; i < obj_hi; i++)
        {
            if (objects[i])
                delete objects[i];
        }

        delete [] objects;
        objects = 0;
    }
    if (temps)
    {
        for(int i=0; i < temp_hi; i++)
        {
            if (temps[i])
                delete temps[i];
        }

        delete [] temps;
        temps = 0;
    }
    for (int t=0; t < SIM_MAX_TEAMS; t++)
    {
        sim_team_t *st = &teams[t];

        if (st->units)
        {
            for(int i=0; i < st->unit_hi; i++)
            {
                if (st->units[i])
                    delete st->units[i];
            }

            delete [] st->units;
            st->units = 0;
        }
        if (st->offields)
        {
            for(int i=0; i < st->ofld_hi; i++)
            {
                if (st->offields[i])
                    delete st->offields[i];
            }

            delete [] st->offields;
            st->offields = 0;
        }
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimulatorState - process_events
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimulatorState::process_events ()
{
    if (!(flags & MODEL_FROZEN))
    {
        //陳� Determine mission time...

        const float interval (float(clock.check() << timeshift) / 1000.0f);
        timebase += interval;
        clock.clear();

        if (timebase > 0)
        {
			int i = 0;
            time_now = ulong(timebase * 1000.0f);

            //陳� Step model
            for(i=0; i < obj_hi; i++)
            {
                SimObject *ptr = objects[i];
                if (ptr && !(ptr->base_flags & SimObject::BASE_INACTIVE))
                {
                    ptr->step(interval);
                }
            }

            for(i=0; i < temp_hi; i++)
            {
                SimTemp *ptr = temps[i];
                if (ptr && !(ptr->base_flags & SimObject::BASE_INACTIVE))
                {
                    ptr->step(interval);
                }
            }

            sim_team_t *st = teams;
            for(int t=0; t < SIM_MAX_TEAMS; t++, st++)
            {
                for(i=0; i < st->unit_hi; i++)
                {
                    SimUnit *ptr = st->units[i];
                    if (ptr && !(ptr->base_flags & SimObject::BASE_INACTIVE))
                    {
                        ptr->step(interval);
                    }
                }
                for(i=0; i < st->ofld_hi; i++)
                {
                    SimOffield *ptr = st->offields[i];
                    if (ptr && !(ptr->base_flags & SimObject::BASE_INACTIVE))
                    {
                        ptr->step(interval);
                    }
                }
            }
        }
    }

//陳� Process UI
    assertMyth("SimulatorState::process_events needs valid ui", ui != 0);

    ui->process_events();
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// SimulatorState - render
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void SimulatorState::render ()
{
    assertMyth("SimulatorState::render needs valid ui", ui != 0);

    ui->render();
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭�  Utility Routines  碓旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//葦� End of module - simulatr.cpp 憶�

