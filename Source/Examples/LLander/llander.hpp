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
// llander.hpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <simgine.hpp>

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//��������������������������� Primary Game State ����������������������������
//���������������������������������������������������������������������������

class Terrain;

//���������������������������������������������������������������������������
// LanderNetwork
//���������������������������������������������������������������������������
class LanderNetwork : public TurnerClassic
{
public:
    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    LanderNetwork (int players = 2);

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void handle_msg (DPID from, DPID to, LPVOID ptr, DWORD size);
    virtual void handle_chat (DPID fromplayer, DPID toplayer, DPID togroup, LPSTR msg);
    virtual void sys_newplayer (DPID player, LPCSTR short_name, LPCSTR long_name,
                               LPVOID data, DWORD size, DPID pgroup, DWORD _flags);
    virtual void sys_delplayer (DPID player, DWORD _flags);
};


//���������������������������������������������������������������������������
// Lander - The actual vehicle moving under the player's control.
//���������������������������������������������������������������������������
class Lander
{
    MaxEventSource  *evt;

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    BYTE        lander_color;
    BYTE        flame_color;
    BYTE        *lander_image;
    BYTE        *lander_image_lowburn;
    BYTE        *lander_image_highburn;
    BYTE        *lander_image_leftburn;
    BYTE        *lander_image_rightburn;

    time_t      start_time;
    time_t      last_update;
    DWORD       jcenterx;
    DWORD       jcentery;
    float       gravity;
    float       xacceleration;
    float       yacceleration;
    float       xvelocity;
    float       yvelocity;
    float       xpos;
    float       ypos;
    BOOL        remote;
    BOOL        active;
    DPID        player_id;
    RECT        damage;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    Lander  (MaxEventSource *, BOOL remote = FALSE,
             VngoColor24bit = VngoColor24bit (128, 128, 128));
    ~Lander ();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    void step ();

    void reset (float x = 0, float y = 10);

    void process_events ();
    void update_model ();
    BOOL load_images ();

    void draw (VngoVport *);

    float get_thrust () const
    {
        return flx_abs (yacceleration) + flx_abs (xacceleration);
    }

    BOOL too_fast () const
    {
        return (xvelocity < -15
                || yvelocity > 15
                || xvelocity < -5
                || xvelocity > 5);
    }

    BOOL collided (Terrain *);
    BOOL landed (Terrain *);
};


//���������������������������������������������������������������������������
// Terrain - The terrain is the moon's surface.
//���������������������������������������������������������������������������
class Terrain
{
public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    WORD        *aHeights;
    WORD        cHeights;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    Terrain (int num);
    ~Terrain ();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    void        draw     (VngoVport *) const;
    WORD        col_size (int wid) const { return wid / cHeights; }
};


//���������������������������������������������������������������������������
// LanderGame - Main state for lander game
//���������������������������������������������������������������������������
class LanderGame : public SimState
{
    VngoVport       *vport;

    MaxEventUser    *evt;

    UINT            frame;
    Chronometer     timer;

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    enum        { NUM_LANDERS = 4 };
    Lander      *aLanders[NUM_LANDERS];
    Terrain     terrain;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    LanderGame();
    virtual ~LanderGame();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void activate ();
    virtual void deactivate ();

    virtual void process_events();
    virtual void render();

    void    draw_terrain ();

    Lander *get_lander (DPID player);
    Lander *init_lander (DPID player);
    void kill_lander (DPID player);

    void restore (LPRECT);
};



//���������������������������������������������������������������������������
//��������������������������� Misc Game States ������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// LanderTitle
//���������������������������������������������������������������������������
class LanderTitle : public SimState
{
    MaxEventUser    *evt;

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    EschScene       *scene;
    VngoVport       *vport;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    LanderTitle();
    virtual ~LanderTitle();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void activate ();
    virtual void deactivate ();

    virtual void process_events();
    virtual void render();
};


//���������������������������������������������������������������������������
// LanderEnd
//���������������������������������������������������������������������������
class LanderEnd : public SimState
{
    MaxEventUser    *evt;

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    int         crashed;
    int         lander_dx;
    int         lander_dy;
    int         frame_rate;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    LanderEnd();
    virtual ~LanderEnd();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void activate ();
    virtual void deactivate ();

    virtual void process_events();
    virtual void render();
};



//���������������������������������������������������������������������������
//���������������������������� Application Class  ���������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// LanderApp
//���������������������������������������������������������������������������
class LanderApp : public SimGine
{
public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    LanderTitle *title;
    LanderGame  *game;
    LanderEnd   *end;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    LanderApp();
    virtual ~LanderApp();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual BOOL init_instance();
    virtual int exit_instance();
};

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

extern LanderApp theSim;

extern char szINI[];
extern char szIFF[];

//��� End of header - llander.hpp ���
