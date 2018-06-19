//���������������������������������������������������������������������������
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
//���������������������������������������������������������������������������
//
//                     A Simluator Framework for MythOS(tm)
//
//                     Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1997-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
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
//                               *** Tester ***
//
// Created by Dan Higdon and Chuck Walbourn
//
// stapp.cpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "st.hpp"

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

TesterApp theSim;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// Constructor - TesterApp
//���������������������������������������������������������������������������
TesterApp::TesterApp() :
    SimGine (),
    start (0),
    sim (0)
{
};


//���������������������������������������������������������������������������
// Destructor - TesterApp
//���������������������������������������������������������������������������
TesterApp::~TesterApp()
{
};



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// TesterApp - init_instance
//���������������������������������������������������������������������������
BOOL TesterApp::init_instance()
{
//��� Load settings from .INI file
    {
        XFParseINI ini;
        char buff[256];

        ini.open("ST.INI", XF_OPEN_READ);

        if (!ini.section("StartUp"))
        {
            if (!ini.read("DisplayDevice",buff))
            {
                _strlwr(buff);

                startup &= ~(STARTUP_DDRAW
                             | STARTUP_D3D);

                if (strstr(buff,"direct3d"))
                    startup |= STARTUP_D3D;
                else

                if (strstr(buff,"directdraw"))
                    startup |= STARTUP_DDRAW;
            }

            if (!ini.read("FullScreen",buff))
            {
                _strlwr(buff);
                if (strstr(buff,"no"))
                    startup &= ~STARTUP_FULLSCREEN;
            }

            if (!ini.read("ColorDepth",buff))
            {
                if (strstr(buff,"8"))
                    startup_bitdepth = 8;
                else if (strstr(buff,"15"))
                    startup_bitdepth = 15;
                else if (strstr(buff,"16"))
                    startup_bitdepth = 16;
            }

            if (!ini.read("Target",buff))
            {
                memset(startup_target,0,sizeof(startup_target));
                strncpy(startup_target,buff,sizeof(startup_target)-1);
            }
        }
    }

    if (startup & STARTUP_D3D)
    {
        // Direct3D can only run in 15- or 16-bit
        if (startup_bitdepth == 8)
            startup_bitdepth = 16;
    }
    else

#ifdef  _OEMS
#ifdef  _CLEAR_3D
    if (startup & STARTUP_CLEAR3D)
    {
        // Clear3D can only run in 16-bit
        startup_bitdepth = 16;
    }
    else
#endif
#endif

    if (!(startup & STARTUP_DDRAW))
    {
        // DIB can only run in 8- or 15-bit
        if (startup_bitdepth == 16)
            startup_bitdepth = 15;
    }

//��� Perform base init
    if (!SimGine::init_instance())
    {
        MessageBox(hWndClient, "SimGine Failed to Initialize Instance",
                   appName, MB_ICONEXCLAMATION | MB_OK);
        return FALSE;
    }

//��� Install fonts
    if (gberg_install_font("arl-7x12.iff", 0))
        return FALSE;

//��� Create states
    start = new TesterState;
    if (!start)
        return FALSE;

    sim = new TesterSim;
    if (!sim)
        return FALSE;

    Mode = start;

    return TRUE;
}


//���������������������������������������������������������������������������
// TesterApp - exit_instance
//���������������������������������������������������������������������������
int TesterApp::exit_instance()
{
    if (start)
    {
        delete start;
        start = 0;
    }

    return SimGine::exit_instance();
}

//��� End of module - stapp.cpp ���

