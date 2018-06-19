//���������������������������������������������������������������������������
//                                                      _o######ooooooo-_
//     Spielberg -- Animation player library          o#####o_o#####~~~~~~
//                                                   ################o__o
//      Microsoft Windows 95/98/NT Version        _o###########~~~~~###~
//                                               o##############
//                                            _o###############~
//                                          _o#########~ooo~##~
//                                     _o############# ##o::___
//                                   _o#################oo:~~~~~
//                                 _o#####################~
//                               _####~_oooooooo:~~######~
//                             _##### o###########_:~##~
//                            o#####_##################
//                           _#######_~#################_
//                           ##########o:~###############o
//                         _##############o~##############_
//                       o#############~~     ~~~~~~~######_
//                   __o##########~::o_             o#######
//              _oo##########~~::o#####            o###########o___
//          o##########~~~~    ~~~##########       ~~~~#############o
//         #####~~~~~~                ~~~
//
//  Copyright (c) 1996-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
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
//                          *** Tester Application ***
//
// Created by Tim Little & Chuck Walbourn
//
// sbrgtest.cpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <conio.h>
#include <stdio.h>
#include <iostream>

#include "spielbrg.hpp"

using namespace std; 

//���������������������������������������������������������������������������
//
//                               Routines
//
//���������������������������������������������������������������������������

BOOL PumpWindows();
STATIC BOOL InitApplication (HINSTANCE, int, int, int);
LRESULT CALLBACK ClientWndProc (HWND, UINT, WPARAM, LPARAM);

char *str_error(char *str, sberg_err_codes err);

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

//��� Global Windows data
HINSTANCE       hInst;
HWND            hWndClient;
const char      szAppName[]     = "Spielberg Tester";

//��� Tester data
BOOL                Batch=FALSE;
SpielbergPlayer     *Player=0;
LPDIRECTDRAW        DD=0;
LPDIRECTDRAWSURFACE DDSurf=0;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// WinMain
//���������������������������������������������������������������������������
int APIENTRY WinMain (HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR     lpCmdLine,
                      int       nCmdShow)
{
//��� Initialize Windows

    //��� If we are already running, this routine will reactivate the older
    //��� application and return failure.
    if (!InitApplication (hInstance, nCmdShow, 640, 480))
        return 1;

    IvorySystem ivory;

//��� Check for direct-draw command-line switch
    if (strstr(lpCmdLine,"-ddraw"))
    {
        HRESULT hr = DirectDrawCreate(NULL, &DD, NULL);
        if (hr != DD_OK)
        {
            MessageBox(hWndClient,"DirectDraw connect failed",
                       szAppName,MB_OK | MB_ICONEXCLAMATION);
        }
        else
        {
                DD->SetCooperativeLevel(hWndClient, (strstr(lpCmdLine,"-nomode")
                                                 ? DDSCL_NORMAL
                                                 : (DDSCL_EXCLUSIVE
                                                    | DDSCL_FULLSCREEN
                                                    | DDSCL_ALLOWMODEX)));

            if (strstr(lpCmdLine,"-nomode"))
            {
                hr = DD_OK;
            }
            else
            {
                if (strstr(lpCmdLine,"-800x600"))
                    hr = DD->SetDisplayMode(800,600,16);
                else if (strstr(lpCmdLine,"-320x240"))
                    hr = DD->SetDisplayMode(320,240,16);
                else if (strstr(lpCmdLine,"-320x200"))
                    hr = DD->SetDisplayMode(320,200,16);
                else
                    hr = DD->SetDisplayMode(640,480,16);
            }

            if (hr != DD_OK)
            {
                DD->Release();
                DD=0;
                MessageBox(hWndClient,"DirectDraw mode set failed",
                           szAppName,MB_OK | MB_ICONEXCLAMATION);
            }
            else
            {
                    DDSURFACEDESC ddsd;

                memset(&ddsd,0,sizeof(ddsd));

                    ddsd.dwSize = sizeof(ddsd);
                    ddsd.dwFlags = DDSD_CAPS;
                    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

                    hr = DD->CreateSurface(&ddsd, &DDSurf, NULL);
                if (hr != DD_OK)
                {
                    DD->RestoreDisplayMode();
                    DD->Release();
                    DD=0;
                    MessageBox(hWndClient,"DirectDraw primary surface failed",
                               szAppName,MB_OK | MB_ICONEXCLAMATION);
                }
            }
        }
    }

    if (strstr(lpCmdLine,"-file"))
    {
        Batch=TRUE;

        char *s = strstr(lpCmdLine,"-file");
        for (;*s != ' ' && *s != '\0'; s++);
        if (*s == '\0' || *(++s) == '\0')
        {
            MessageBox(hWndClient,"Expected a filename after -file",
                                  szAppName,MB_OK | MB_ICONEXCLAMATION);
            ExitProcess(1);
        }

        if (DD)
            Player = new SpielbergAMStreamPlayer(DD,DDSurf);
        else
            Player = new SpielbergAMPlayer(hWndClient);

        if (!Player)
        {
            MessageBox(hWndClient,"Out of memory!",
                        szAppName,MB_OK | MB_ICONEXCLAMATION);
            ExitProcess(1);
        }

        char buff[256];
        memset(buff,0,sizeof(buff));
        for(char *d=buff; *s != ' ' && *s != '\0'; *(d++) = *(s++));

        sberg_err_codes err = Player->open(buff, SBERG_CTRL_FULLSCREEN);
        if (err)
        {
            char buff[128];
            strcat(str_error(buff,err)," - '-file' open");
            MessageBox(hWndClient,buff,
                        szAppName,MB_OK | MB_ICONEXCLAMATION);
            ExitProcess(1);
        }

        err = Player->play();
        if (err)
        {
            char buff[128];
            strcat(str_error(buff,err)," - '-file' play");
            MessageBox(hWndClient,buff,
                        szAppName,MB_OK | MB_ICONEXCLAMATION);
            ExitProcess(1);
        }
    }

//��� Main Loop
    while (PumpWindows());

//��� Cleanup
    if (Player)
    {
        delete Player;
        Player = 0;
    }
    if (DDSurf)
    {
        DDSurf->Release();
        DDSurf=0;
    }
    if (DD)
    {
        DD->RestoreDisplayMode();
        DD->Release();
        DD=0;
    }

    return 0;
}


//���������������������������������������������������������������������������
// PumpWindows
//���������������������������������������������������������������������������
BOOL PumpWindows()
{
    MSG msg;
    while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
    {
        if (GetMessage (&msg, 0, 0, 0) == 0)
            return FALSE;

        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }

    if (Player)
    {
        Player->display();

        if (Batch && !(Player->get_flags() & SBERG_PLAYER_PLAYING))
            return FALSE;
    }

    if (DDSurf)
    {
        if (DDSurf->IsLost() == DDERR_SURFACELOST)
            DDSurf->Restore();

        DDSurf->Flip(NULL,DDFLIP_WAIT);
    }

    return TRUE;
}


//���������������������������������������������������������������������������
// ClientWndProc
//���������������������������������������������������������������������������
LRESULT CALLBACK ClientWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int      shift = 0;
    static int      ctrl = 0;

    switch (message)
    {
        //��������������������������������������������������� Keyboard Events
        case WM_KEYDOWN:
            switch (wParam)
            {
                case VK_ESCAPE:
                    DestroyWindow(hWndClient);
                    break;
                case 'U':
                    if (Player)
                    {
                        sberg_err_codes err=Player->pause();
                        if (err)
                        {
                            char buff[128];
                            strcat(str_error(buff,err)," - Player pause");
                            MessageBox(hWndClient,buff,
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                        }
                    }
                    break;
                case 'R':
                    if (Player)
                    {
                        sberg_err_codes err=Player->resume();
                        if (err)
                        {
                            char buff[128];
                            strcat(str_error(buff,err)," - Player resume");
                            MessageBox(hWndClient,buff,
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                        }
                    }
                    break;
                case 'S':
                    if (Player)
                    {
                        sberg_err_codes err=Player->stop();
                        if (err)
                        {
                            char buff[128];
                            strcat(str_error(buff,err)," - Player stop");
                            MessageBox(hWndClient,buff,
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                        }
                    }
                    break;
                case 'P':
                    if (Player)
                    {
                        sberg_err_codes err=Player->play();
                        if (err)
                        {
                            char buff[128];
                            strcat(str_error(buff,err)," - Player play");
                            MessageBox(hWndClient,buff,
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                        }
                    }
                    break;
                case 'I':
                    if (Player)
                    {
                        SpielbergInfo info;

                        sberg_err_codes err=Player->get_info(&info);
                        if (err)
                        {
                            char buff[128];
                            strcat(str_error(buff,err)," - Player get_info");
                            MessageBox(hWndClient,buff,
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                        }
                        else
                        {
                            char buff[1024];
                            wsprintf(buff," Spielberg Information\n"
                                          " Size=%d by %d\n"
                                          " Duration=%d ms",
                                          info.width, info.height,
                                          info.duration);
                            MessageBox(hWndClient,buff,
                                       szAppName,MB_OK);
                        }
                    }
                    break;
                case 'C':
                    if (Player)
                    {
                        delete Player;
                        Player = 0;
                    }
                    break;
                case '1':
                    if (!Player)
                    {
                        if (DD)
                            Player = new SpielbergAMStreamPlayer(DD,DDSurf);
                        else
                            Player = new SpielbergAMPlayer(hWndClient);

                        if (!Player)
                        {
                            MessageBox(hWndClient,"Out of memory!",
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                            ExitProcess(1);
                        }

                        sberg_err_codes err = Player->open("DOBERMAN.AVI",
                                                           (shift)
                                                           ? SBERG_CTRL_FULLSCREEN
                                                           : 0);
                        if (err)
                        {
                            char buff[128];
                            strcat(str_error(buff,err)," - Player open");
                            MessageBox(hWndClient,buff,
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                            ExitProcess(1);
                        }
                    }
                    break;
                case '2':
                    if (!Player)
                    {
                        if (DD)
                            Player = new SpielbergAMStreamPlayer(DD,DDSurf);
                        else
                            Player = new SpielbergAMPlayer(hWndClient);

                        if (!Player)
                        {
                            MessageBox(hWndClient,"Out of memory!",
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                            ExitProcess(1);
                        }

                        sberg_err_codes err = Player->open("BLASTOFF.MPG",
                                                           (shift)
                                                           ? SBERG_CTRL_FULLSCREEN
                                                           : 0);
                        if (err)
                        {
                            char buff[128];
                            strcat(str_error(buff,err)," - Player open");
                            MessageBox(hWndClient,buff,
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                            ExitProcess(1);
                        }
                    }
                    break;
                case '3':
                    if (!Player)
                    {
                        if (DD)
                            Player = new SpielbergAMStreamPlayer(DD,DDSurf);
                        else
                            Player = new SpielbergAMPlayer(hWndClient);

                        if (!Player)
                        {
                            MessageBox(hWndClient,"Out of memory!",
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                            ExitProcess(1);
                        }

                        sberg_err_codes err = Player->open("ASTRNMY.MOV",
                                                           (shift)
                                                           ? SBERG_CTRL_FULLSCREEN
                                                           : 0);
                        if (err)
                        {
                            char buff[128];
                            strcat(str_error(buff,err)," - Player open");
                            MessageBox(hWndClient,buff,
                                        szAppName,MB_OK | MB_ICONEXCLAMATION);
                            ExitProcess(1);
                        }
                    }
                    break;
                case VK_SHIFT:
                    shift=1;
                    break;
                case VK_CONTROL:
                    ctrl=1;
                    break;
            }
            return 0;

        case WM_KEYUP:
            switch (wParam)
            {
                case VK_SHIFT:
                    shift=0;
                    break;
                case VK_CONTROL:
                    ctrl=0;
                    break;
            }
            return 0;

        //������������������������������������������������ Application Events
        case WM_CREATE:
            return 0;

        case WM_ACTIVATEAPP:
            return 0;

        case WM_CLOSE:
            DestroyWindow(hWndClient);
            return 0;

        case WM_DESTROY:
            PostQuitMessage (0);
            return 0;

        default:
            return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


//���������������������������������������������������������������������������
// str_error
//���������������������������������������������������������������������������
char *str_error(char *str, sberg_err_codes err)
{
    switch (err)
    {
        case SBERG_ERR_INVALIDPARMS:
            strcpy(str,"invalid parameters");
            break;
        case SBERG_ERR_NOMEMORY:
            strcpy(str,"no memory");
            break;
        case SBERG_ERR_NOTSUPPORTED:
            strcpy(str,"not supported");
            break;
        case SBERG_ERR_UNINITIALIZED:
            strcpy(str,"uninitalized");
            break;
        case SBERG_ERR_ALREADYOPEN:
            strcpy(str,"already open");
            break;
        case SBERG_ERR_FILENOTFOUND:
            strcpy(str,"file not found");
            break;
        case SBERG_ERR_OPENFAILED:
            strcpy(str,"open failed");
            break;
        case SBERG_ERR_NOTPLAYING:
            strcpy(str,"not playing");
            break;
        case SBERG_ERR_MISSINGDATA:
            strcpy(str,"missing data");
        case SBERG_ERR_VIDEOFAILED:
            strcpy(str,"video failed");
            break;
        case SBERG_ERR_AUDIOFAILED:
            strcpy(str,"audio failed");
            break;
        case SBERG_ERR_AMCONNECTFAILED:
            strcpy(str,"AM connect failed");
            break;
        case SBERG_ERR_AMQUERYIFAILED:
            strcpy(str,"AM query interface failed");
            break;
        case SBERG_ERR_AMEVENTFAILED:
            strcpy(str,"AM event failed");
            break;
        case SBERG_ERR_AMFSFAILED:
            strcpy(str,"AM full-screen failed");
            break;
        case SBERG_ERR_AMFAILED:
            strcpy(str,"AM failed");
            break;
        default:
            strcpy(str,"*unknown error*");
            break;
    }

    return str;
}

//���������������������������������������������������������������������������
//�������������������� Windows Initialization Functions ���������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// InitApplication
//���������������������������������������������������������������������������
BOOL InitApplication (HINSTANCE hInstance, int nCmdShow, int w, int h)
{
//��� Win32 will always set hPrevInstance to NULL, so lets check
//��� things a little closer. This is because we only want a single
//��� version of this app to run at a time
    HWND hwnd = FindWindow (szAppName, NULL);
    if (hwnd != 0)
    {
        // We found another version of ourself. Lets defer to it:
        if (IsIconic (hwnd))
            ShowWindow (hwnd, SW_RESTORE);
        SetForegroundWindow (hwnd);
        return FALSE;
    }

//��� Register the client window's class
    WNDCLASSEX  wc;

    // Fill in window class structure with parameters that describe
    // the main window.
    wc.cbSize        = sizeof (WNDCLASSEX);
    wc.style         = CS_OWNDC;
    wc.lpfnWndProc   = (WNDPROC)ClientWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (hInstance, szAppName);
    wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject (BLACK_BRUSH);
    wc.lpszClassName = szAppName;
    wc.lpszMenuName  = 0;

    // This will load the small icon image from the icon resource
    wc.hIconSm = (HICON__*)LoadImage (hInstance,
                                      szAppName,
                                      IMAGE_ICON,
                                      GetSystemMetrics(SM_CXSMICON),
                                      GetSystemMetrics(SM_CYSMICON),
                                      LR_DEFAULTCOLOR);

    if (!RegisterClassEx (&wc))
        return FALSE;

    // Save the instance handle in static variable, which will be used in
    // many subsequence calls from this application to Windows.
    hInst = hInstance;

    hWndClient = CreateWindowEx (0,
                                 szAppName, szAppName,
                                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                 0, 0, w, h,
                                 NULL, NULL, hInstance, NULL);

    if (hWndClient == 0)
        return FALSE;

    ShowWindow (hWndClient, nCmdShow);
    UpdateWindow (hWndClient);
    SetFocus (hWndClient);

    return TRUE;
}


//���������������������������������������������������������������������������
//�������������������������� MythOS Assert Display ��������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// _charybdis_assert
//
// Handler for failed asserts.  If msg is set to non-NULL, then an assertMyth
// was used with a comment.
//���������������������������������������������������������������������������
extern "C" void _charybdis_assert (char *msg, char *exp, char *f, unsigned ln)
{
    int     i;
    char    title[32];
    char    buff[988];

    wsprintf (buff,"Assertion Failed\t\t\t\t\t\n"
                   "Expr:\t%s\n"
                   "File:\t%s\t\tLine %d",exp,f,ln);
    if (msg)
    {
        strcat (buff, "\nComment:\n");
        strcat (buff, msg);
    }
    strcat (buff,"\n\n\tOK to continue, Cancel to exit");

    strcpy (title, szAppName);
    strcat (title, " Debug Message");

    i = MessageBox (IsWindow (hWndClient) ? hWndClient : NULL,
                    buff,
                    title,
                    MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONSTOP);

    if (i == IDCANCEL)
        ExitProcess (1);
}

//��� End of module - bmain.cpp ���

