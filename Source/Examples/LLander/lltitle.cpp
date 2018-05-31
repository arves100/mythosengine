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
// lltitle.cpp
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
// Constructor - LanderTitle
//���������������������������������������������������������������������������
LanderTitle::LanderTitle() :
    evt (0),
    scene (0),
    vport (0)
{
};


//���������������������������������������������������������������������������
// Destructor - LanderTitle
//���������������������������������������������������������������������������
LanderTitle::~LanderTitle()
{
    deactivate();
};



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// LanderTitle - activate
//���������������������������������������������������������������������������
void LanderTitle::activate()
{
//��� Load palette and set color
    if (!Screen->load_palette(szIFF, 0))
        panic("LanderTitle::activate failed to load palette");

    gberg_color(Screen->find(VngoColor24bit(255,255,0)), VNGO_TRANSPARENT);

//��� Load data
    assert(scene == 0);
    scene = new EschScene;
    if (!scene
        || scene->load(szIFF,0,Screen->pal)
        || scene->cameras == 0
        || scene->meshes == 0
        || scene->lights == 0)
        panic("LanderTitle::activate failed scene load");

//��� Create viewport
    assert(vport == 0);
    vport = Screen->create_subviewport(VngoRect(0,0,Screen->width,Screen->height),
                                       VNGO_ZBUFFER_DEV);
    if (!vport)
        panic("LanderTitle::activiate failed viewport create");

//�� Setup cameras
    for (EschCamera *cam = scene->cameras; cam != NULL; cam = cam->next ())
    {
        cam->attach (vport);
        cam->set_flags (cam->flags | ESCH_CAM_SHADE_SPECULAR
                                   | ESCH_CAM_SHADE_SMOOTH
                                   | ESCH_CAM_SHADE_FLAT
                                   | ESCH_CAM_SHADE_SOLID
                                   | ESCH_CAM_SHADE_WIRE
                                   | ESCH_CAM_TEXTURED
                                   | ESCH_CAM_BACKCULL
                                   | ESCH_CAM_MODELSPACE);
    }

//��� Create event system
    evt = new MaxEventUser (*Devs);

    if (!evt
        || evt->load (szIFF,0) != 0)
        panic("LanderTitle::activate fail for event");

    evt->install();

}


//���������������������������������������������������������������������������
// LanderTitle - deactivate
//���������������������������������������������������������������������������
void LanderTitle::deactivate()
{
    if (evt)
    {
        delete evt;
        evt = 0;
    }
    if (vport)
    {
        delete vport;
        vport = 0;
    }
    if (scene)
    {
        delete scene;
        scene = 0;
    }
}


//���������������������������������������������������������������������������
// LanderTitle - process_events
//���������������������������������������������������������������������������
void LanderTitle::process_events()
{
    MaxEventList events = evt->process();

    if (events.check (QUIT))
        theSim.exit();

    if (events.check (NEXT))
    {
        switch_to(theSim.game);
        return;
    }

    assertMyth ("LunarTitle::process_events init must be called first",
                scene != 0);
    for (EschMeshDraw *msh = scene->meshes;
         msh != 0;
         msh = (EschMeshDraw*)msh->next ())
    {
        msh->yaw (3);
    }
}


//���������������������������������������������������������������������������
// LanderTitle - render
//���������������������������������������������������������������������������
void LanderTitle::render()
{
    Screen->clear();

    int waslocked=Screen->lock();

    SimText st(Screen);

    assertMyth ("LunarTitle::render init must be called first",
                scene != 0);

    scene->cameras->render (scene->meshes,scene->lights);

    gberg_select_font ("12x24");
    st.out ("Lunar Lander\n");

    gberg_select_font ("9x15");
    st.out ("An example of using SimGine with MythOS");

    Screen->invalidate();

    if (!waslocked)
        Screen->unlock();
}

//��� eof - lltitle.cpp ���
