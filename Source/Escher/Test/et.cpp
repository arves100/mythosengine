//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//����������������� Microsoft Windows 95/98/NT Version ����������������������
//���������������������������������������������������������������������������
//���Copyright (c) 1994-1999 by Dan Higdon, Tim Little, and Chuck Walbourn���
//���������������������������������������������������������������������������
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
// et.cpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#define WIN32_LEAN_AND_MEAN
#include "global.hpp"

#include "etevt.hpp"

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

const int COLORS = 256;

const int MAXPAGES = 3;

extern MaxDevices *Devs;
extern ulong EschProposedTris;
extern ulong EschDrawnTris;
extern ulong EschElementDepth;
extern ulong EschElementSize;

int GlobalFireTest;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// EscherTest - Constructor
//���������������������������������������������������������������������������
EscherTest::EscherTest (MaxDevices *d):
    devs (d),
    evt (0),
    hpal (0),
    active (FALSE),
    show_fps (FALSE),
    pick_test(FALSE),
    collide_test(FALSE),
    use_new_terrain(FALSE),
    cam(0),
    light(0),
    draws(0),
    scene(0),
    terrain(0),
    prtgen(0),
    starfield(0),
    explosion(0),
    sprite(0),
    metabox(0),
    plane(0),
    curmesh(0),
    fire(0),
    partn(0),
    mtxt(0),
    drawexts(0),
    drawpartn(0),
    RotateDegrees(1),
    ScriptRotateDegrees(3),
    backgrnd (0),
    frames (0),
    screen (0),
    total_frames (0),
    map_xsize (MAP_XSIZE),
    map_ysize (MAP_YSIZE),
    total_time (0),
    alpha (255),
    anim_time(1.0),
    anim_step_time(1.0),
    keyframe_animation(0),
    anim_current_frame(0),
    anim_current_step(0),
    anim_chain_count(0),
    anim_root(0),
    part_linear(1),
    part_life(5),
    part_speed(50),
    part_count(128),
    part_alpha(255),
    scale(1.0f)
{
    int use_fullscreen = 0;
    int use_zbuffer=TRUE;
    char buff[128];
    char palname[128];
    char targetname[64];
    int bpp = 8;
    XFParseINI  ini;

    if (ini.open(".\\ET.INI",XF_OPEN_READ) == XF_ERR_NONE)
    {
        ini.section("Screen");
        if (!ini.read("TargetName",targetname))
        {
            _strlwr(targetname);
        }
        else
        {
            strcpy(targetname,"bsdev (No not this one)");
        }
        if (!ini.read("FullScreen",buff))
        {
            _strlwr(buff);
            if (strstr(buff,"yes") || strstr(buff,"on"))
            {
                use_fullscreen |= VNGO_SET_RESOLUTION;
            }
        }

        if (!ini.read("TrueFlip",buff))
        {
            _strlwr(buff);
            if (strstr(buff,"yes") || strstr(buff,"on"))
            {
                use_fullscreen |= VNGO_TRUE_FLIP;
            }
        }

        if (!ini.read("UseDirectDraw",buff))
        {
            _strlwr(buff);
            if (strstr(buff,"yes") || strstr(buff,"on"))
            {
                screen = new VngoDirectDraw (hWndClient);
//                use_fullscreen |= VNGO_ALLOC_ZBUFFER;
            }
        }
#ifdef _OEMS
#ifdef _MSI
        if (!ini.read("UseMSI",buff))
        {
            strlwr(buff);
            if (strstr(buff,"yes") || strstr(buff,"on"))
            {
                screen = new VngoMSI (ClientWndProc);
            }
        }
#endif
#ifdef _3DFX
        if (!ini.read("Use3DFX",buff))
        {
            strlwr(buff);
            if (strstr(buff,"yes") || strstr(buff,"on"))
            {
                screen = new Vngo3Dfx ();
            }
        }
#endif
#ifdef _CLEAR_3D
        if (!ini.read("UseClear3D",buff))
        {
            strlwr(buff);
            if (strstr(buff,"yes") || strstr(buff,"on"))
            {
                screen = new VngoClear3D (hWndClient);
                use_fullscreen |= VNGO_3DDEVICE | VNGO_ALLOC_ZBUFFER;
            }
        }
#endif
#endif
        if (!ini.read("UseD3D",buff))
        {
            _strlwr(buff);
            if (strstr(buff,"yes") || strstr(buff,"on"))
            {
                screen = new VngoDirect3D (hWndClient,targetname);
                use_fullscreen |= VNGO_3DDEVICE | VNGO_ALLOC_ZBUFFER;
            }
        }

        if (!ini.read("Resolution",buff))
        {
            _strlwr(buff);
            if (strstr(buff,"640x480"))
            {
                map_xsize = 640;
                map_ysize = 480;
            }
            if (strstr(buff,"320x240"))
            {
                map_xsize = 320;
                map_ysize = 240;
            }
            if (strstr(buff,"320x200"))
            {
                map_xsize = 320;
                map_ysize = 200;
            }
            if (strstr(buff,"800x600"))
            {
                map_xsize = 800;
                map_ysize = 600;
            }
            if (strstr(buff,"1024x768"))
            {
                map_xsize = 1024;
                map_ysize = 768;
            }
        }
        if (!ini.read("ZBuffer",buff))
        {
            _strlwr(buff);
            if (strstr(buff,"yes") || strstr(buff,"on"))
            {
                use_zbuffer = TRUE;
            }
            else
            {
                use_zbuffer = FALSE;
            }
        }

        if (!ini.read("ColorDepth",buff))
        {
            _strlwr(buff);
            if (strstr(buff,"16"))
            {
                bpp = 16;
            }
            else if (strstr(buff,"15"))
            {
                bpp = 15;
            }
        }

        if (!ini.read("Palette",palname))
        {
            _strlwr(palname);
        }
        else
        {
            strcpy(palname,"default.pal");
        }

        ini.close();
        // If we did not want a DDraw screen then use a DIB.
        if (screen == NULL)
        {
            screen = new VngoDIB (hWndClient);
        }
        else if (screen->get_initstate() != VNGO_NO_ERROR)
        {
            delete screen;
            screen = new VngoDIB (hWndClient);
        }
    }
    else
    {
        screen = new VngoDIB (hWndClient);
    }

    assert(screen != NULL);
    assert(screen->get_initstate() == VNGO_NO_ERROR);


    if (bpp == 8)
        mypal = new VngoPal8;
    else if (bpp == 15)
        mypal = new VngoPal15;
    else if (bpp == 16)
        mypal = new VngoPal16;

    if (mypal)
    {
        if (mypal->init(0,palname) != 0)
        {
            delete mypal;
            mypal = NULL;
        }
    }
    if (mypal)
    {
        VNGError    vgerr;
        if (bpp == 8)
            vgerr=screen->set_mode (map_xsize, map_ysize, 8 , mypal, use_fullscreen);
        else
            vgerr=screen->set_mode (map_xsize, map_ysize, 16 , mypal, use_fullscreen);

        if (vgerr != VNGO_NO_ERROR && bpp != 8)
        {
            int type = screen->get_type();
            delete screen;
            delete mypal;

            if (vgerr == VNGO_NEEDS_PAL15)
            {
                mypal = new VngoPal15;
            }
            else if (vgerr == VNGO_NEEDS_PAL16)
            {
                mypal = new VngoPal16;
            }

            if (type == VngoScreenManager::SCREENTYPE_DDRAW)
            {
                screen = new VngoDirectDraw(hWndClient);
            }
            else if (type == VngoScreenManager::SCREENTYPE_DIB)
            {
                screen = new VngoDIB(hWndClient);
            }
            else if (type == VngoScreenManager::SCREENTYPE_D3D)
            {
                screen = new VngoDirect3D(hWndClient,targetname);
            }
            if (mypal)
            {
                if (mypal->init(0,palname) != 0)
                {
                    delete mypal;
                    mypal = NULL;
                }
            }

            vgerr=screen->set_mode (map_xsize, map_ysize, 16 , mypal, use_fullscreen);
            if (vgerr != VNGO_NO_ERROR)
            {
                delete screen;
                screen=NULL;
                delete mypal;
                mypal = NULL;
                return; // I can't realy return an error so just return;
            }
        }
        else if (vgerr != VNGO_NO_ERROR)
        {
            delete screen;
            screen = NULL;
            delete mypal;
            mypal = NULL;
            return;
        }

        if (screen->get_type() == VngoScreenManager::SCREENTYPE_DDRAW)
        {
            VngoDirectDraw *ldd = (VngoDirectDraw *)screen;
            if (bpp == 8)
            {
                gvp = new VngoVportDD8(ldd->SurfaceManager, NULL, mypal,
                                       VNGO_ZBUFFER_DEV);
            }
            else
            {
                gvp = new VngoVportDD16(ldd->SurfaceManager, NULL, mypal,
                                        VNGO_ZBUFFER_DEV);
            }
        }
        else if (screen->get_type() == VngoScreenManager::SCREENTYPE_DIB)
        {
            VngoDIB *ldib = (VngoDIB *)screen;
            if (bpp == 8)
            {
                gvp = new VngoVportDB8(map_xsize,map_ysize,ldib->gmap,NULL,mypal,
                                       VNGO_ZBUFFER_DEV);
            }
            else
            {
                gvp = new VngoVportDB16(map_xsize,map_ysize,ldib->gmap,NULL,mypal,
                                       VNGO_ZBUFFER_DEV);
            }
        }
#ifdef _OEMS
#ifdef _3DFX
        else if (screen->get_type() == VngoScreenManager::SCREENTYPE_3DFX)
        {
            gvp = new VngoVport3Dfx(map_xsize,map_ysize,0,0,mypal,VNGO_ZBUFFER_DEV);
        }
#endif
#ifdef _MSI
        else if (screen->get_type() == VngoScreenManager::SCREENTYPE_MSI)
        {
            VngoMSI *msi = (VngoMSI *)screen;
            gvp = new VngoVportMSI(map_xsize,map_ysize,0,0,mypal,VNGO_ZBUFFER_DEV,msi);
              gvp = NULL;
        }
#endif
#ifdef _CLEAR_3D
        else if (screen->get_type() == VngoScreenManager::SCREENTYPE_CLEAR3D)
        {
            VngoRect srect(0,0,map_xsize,map_ysize);
            gvp = new VngoVportCL3D(srect,mypal,VNGO_ZBUFFER_DEV,screen);
        }
#endif

#endif
        else if (screen->get_type() == VngoScreenManager::SCREENTYPE_D3D)
        {
            VngoRect srect(0,0,map_xsize,map_ysize);
            gvp = new VngoVportD3D(srect,mypal,VNGO_ZBUFFER_DEV,screen);
        }
        else
        {
            VngoRect srect(0,0,map_xsize,map_ysize);
            gvp = new VngoVVport8(srect,mypal,VNGO_ZBUFFER_DEV);
        }

        if (!use_zbuffer)
        {
            gvp->zbuffer_off();
        }

        gberg_color(gvp->vbuff.pal->get_index(VngoColor24bit(255,255,255)),
                    VNGO_TRANSPARENT);

        exts_color = gvp->vbuff.pal->get_index(VngoColor24bit(255,255,255));
    }
}


//���������������������������������������������������������������������������
// EscherTest - Destructor
//���������������������������������������������������������������������������
EscherTest::~EscherTest ()
{
    if (hpal)
        DeleteObject(hpal);

    // Clean up our event source
    if (evt)
    {
        evt->uninstall();
        delete evt;
        evt = 0;
    }

    if (fire)
    {
        delete fire;
        fire = 0;
    }

    if (partn)
    {
        delete partn;
        partn = 0;
    }

    if (mtxt)
    {
        delete mtxt;
        mtxt = 0;
    }

    if (backgrnd)
    {
        delete backgrnd;
        backgrnd = 0;
    }

    if (terrain)
    {
        delete terrain;
        terrain = 0;
    }

    if (trees)
    {
        if (trees->txt)
        {
            for (ulong i=0; i < trees->tmax; i++)
            {
                if (trees->txt[i])
                    delete trees->txt[i];
            }
            delete trees->txt;
        }
        delete trees;
        trees = 0;
    }

    if (gvp)
    {
        delete gvp;
        gvp = 0;
    }

    if (scene)
    {
        // Hack due to messed-up drawlist in some cases...
        scene->meshes=0;
        delete scene;
        scene = 0;
    }
    if (EschKeyframeMan)
    {
        delete EschKeyframeMan;
        EschKeyframeMan = 0;
    }

    if (mypal)
    {
        delete mypal;
        mypal = 0;
    }

    if (prtgen)
    {
        delete prtgen;
        prtgen = 0;
    }

    if (starfield)
    {
        delete starfield;
        starfield = 0;
    }

    if (explosion)
    {
        delete explosion;
        explosion = 0;
    }

    if (sprite)
    {
        delete sprite;
        sprite = 0;
    }

    if (metabox)
    {
        delete metabox;
        metabox = 0;
    }

    if (plane)
    {
        delete plane;
        plane = 0;
    }

    if (cam)
    {
        delete cam;
        cam = 0;
    }

    if (screen)
    {
        delete screen;
        screen = 0;
    }
}



//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// EscherTest - LoadEvents
//���������������������������������������������������������������������������
void EscherTest::LoadEvents (LPCSTR lpszFile)
{
    // remember the filename
    strcpy (szFileName, lpszFile);

    // If we have an old event system, kill it
    if (evt)
    {
        evt->uninstall();
        delete evt;
    }

    // Create a new system
    evt = new MaxEventUser (*devs, szFileName);

    // Verify the event system matches our set of events?

    // Now, let 'er rip!
    evt->install();
    active = TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupFireTest
//���������������������������������������������������������������������������
BOOL EscherTest::SetupFireTest()
{
    if (fire)
        return TRUE;

    fire = new EschFireTexture(128,128,mypal);
    if (!fire)
    {
        MessageBox("Couldn't create fire texture", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    fire->set_flags(ESCH_TXT_SKIPANIMATE, 1);

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupPartitionTest
//���������������������������������������������������������������������������
BOOL EscherTest::SetupPartitionTest(const char *buff)
{
    if (strstr(buff,"grid"))
    {
        partn = new EschGridPartition;
        if (!partn
            || ((EschGridPartition*)partn)->init(4,4,128,&EschPoint(-256,0,-256)))
        {
            MessageBox("Couldn't create grid", MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }
    }
    else if (strstr(buff,"quad"))
    {
        partn = new EschQuadTreePartition;
        if (!partn
            || ((EschQuadTreePartition*)partn)->init(&EschPoint(-256,0,-256),128*4,128*4))
        {
            MessageBox("Couldn't create quadtree", MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        ((EschQuadTreePartition*)partn)->set_maxdepth(8);
        ((EschQuadTreePartition*)partn)->set_maxcount(1);
    }
    else if (strstr(buff,"oct"))
    {
        partn = new EschOctTreePartition;
        if (!partn
            || ((EschOctTreePartition*)partn)->init(&EschPoint(-256,-128,-256),128*4,128*4,128*4))
        {
            MessageBox("Couldn't create octtree", MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        ((EschQuadTreePartition*)partn)->set_maxdepth(8);
        ((EschQuadTreePartition*)partn)->set_maxcount(1);
    }
    else
    {
        MessageBox("Couldn't create partitioning", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (draws)
        return FALSE;

    draws = partn;

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupMultiTest
//���������������������������������������������������������������������������
BOOL EscherTest::SetupMultiTest(const char *name)
{
    XFBitmap    bm[16];

    ushort count=0;
    float rate=0;
    for (const char *s=name, *c=name; ; c++)
    {
        if (!*c || *c == ',')
        {
            if (s == name)
            {
                char value[128];
                memset(value,0,sizeof(value));
                strncpy(value,s,c-s);
                rate = float(atof(value));
            }
            else
            {
                if (count >= 16)
                {
                    MessageBox("Too many MultiTest bitmaps found",
                            MB_OK | MB_ICONEXCLAMATION);
                    return FALSE;
                }

                char fname[128];
                memset(fname,0,sizeof(fname));
                strncpy(fname,s,c-s);

                XFParseBMP bmp(&bm[count]);
                if (bmp.nameread(fname))
                {
                    MessageBox(fname, MB_OK | MB_ICONEXCLAMATION);
                    return FALSE;
                }

                count++;
            }

            if (!*c)
                break;

            s=c+1;
        }
    }

    if (!count)
    {
        MessageBox("No MultiTest bitmaps found",
                   MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    mtxt = new EschMultiFrameTexture;
    if (!mtxt
        || mtxt->create(count,bm))
    {
        MessageBox("Couldn't create multi-frame texture",
                   MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    if (rate > 0)
        mtxt->set_rate(rate);

    mtxt->set_flags(ESCH_TXT_SKIPANIMATE, 1);

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupSprite
//���������������������������������������������������������������������������
BOOL EscherTest::SetupSprite(const char *name)
{
    if (sprite)
        return FALSE;

    XFParseBMP bmp;
    if (bmp.nameread((strstr(name,",")) ? strstr(name,",")+1 : name))
    {
        MessageBox((strstr(name,",")) ? strstr(name,",")+1 : name,
                   MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    sprite = new EschSprite;
    if (!sprite
        || sprite->create(bmp.bm,10,10))
    {
        MessageBox("Could not create sprite",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (strstr(name,"infinite"))
    {
        sprite->set_position(0,0,100);
        sprite->set_flags(ESCH_SPRITE_INFINITE, 1);
    }
    else
    {
        sprite->set_position(0,0,0);
    }

    sprite->set_alpha(alpha);

    if (!cam)
    {
        cam = new EschCameraEx(gvp);
        cam->set_position(0,0,-100);
        cam->set_flags(ESCH_CAM_SHADE_SMOOTH
                       | ESCH_CAM_SHADE_FLAT
                       | ESCH_CAM_SHADE_SOLID
                       | ESCH_CAM_SHADE_WIRE
                       | ESCH_CAM_BACKCULL
                       | ESCH_CAM_MODELSPACE
                       | ESCH_CAM_ALPHA
                       | ESCH_CAM_TEXTURED, 1);
        cam->create_bg_bitmap(backgrnd);
    }

    cam->set_bcolor(mypal->get_index(VngoColor24bit(0,0,128)));

    if (draws)
        sprite->sibling(draws);
    else
        draws = sprite;

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - LoadScene
//���������������������������������������������������������������������������
BOOL EscherTest::LoadScene(char *fn, dword in_type)
{
    int err;

    if (scene)
        return FALSE;

    scene = new EschScene;
    if (!scene)
        return FALSE;

    if ((err=scene->load(fn,0,mypal,in_type))!=0)
    {
        char buff[256];
        sprintf(buff,"Could not load a scene from file '%s', error %d",fn,err);
        MessageBox(buff,MB_OK| MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!cam)
    {
        if (scene->cameras)
        {
             cam = new EschCameraEx(*scene->cameras);
             if (!cam)
                return FALSE;
        }
        else
        {
             cam = new EschCameraEx;
             if (!cam)
                return FALSE;

             cam->set_position(0,0,500);
             cam->set_lookat(0,0,0);
        }

        cam->attach(gvp);
        cam->set_flags(ESCH_CAM_SHADE_SMOOTH
                       | ESCH_CAM_SHADE_FLAT
                       | ESCH_CAM_SHADE_SOLID
                       | ESCH_CAM_SHADE_WIRE
                       | ESCH_CAM_BACKCULL
                       | ESCH_CAM_MODELSPACE
                       | ESCH_CAM_PERSPECTIVE
                       | ESCH_CAM_TEXTURED
                       | ESCH_CAM_ALPHA, 1);

        cam->set_bcolor(mypal->get_index(VngoColor24bit(0,0,128)));
        cam->set_yon(2500);
        cam->create_bg_bitmap(backgrnd);
    }

    if (!light)
        light=scene->lights;

    if (scene->meshes)
    {
        curmesh=scene->meshes;

        if (fire)
        {
            if (curmesh && curmesh->txt)
            {
                curmesh->set_flags(ESCH_MSHD_OWNSNOPRCTXT, 1);
                curmesh->txt[0] = fire;
            }
            else
            {
                MessageBox("Couldn't put fire texture on first object",
                           MB_OK | MB_ICONEXCLAMATION);
            }
        }
        else if (mtxt)
        {
            if (curmesh && curmesh->txt)
            {
                curmesh->txt[0] = mtxt;
            }
            else
            {
                MessageBox("Couldn't put multi-frame texture on first object",
                           MB_OK | MB_ICONEXCLAMATION);
            }
        }

        if (partn)
        {
            for(EschMeshDraw *ptr = scene->meshes; ptr != 0; ptr = (EschMeshDraw*)ptr->next())
            {
                if (partn->insert(ptr))
                {
                    char buff[64];
                    wsprintf(buff,"Couldn't put drawable '%s' into partition",ptr->name);
                    MessageBox(buff,
                               MB_OK | MB_ICONEXCLAMATION);
                }
            }
        }
        else
        {
            if (draws)
                ((EschDrawable*)scene->meshes)->sibling(draws);
            else
                draws = scene->meshes;
        }
    }

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - LoadTreeTops
//���������������������������������������������������������������������������
BOOL EscherTest::LoadTreeTops(const char *buff)
{
    // parameters (all required)
    //  terrain filename
    //  left x value
    //  top y(z) value
    //  right x value
    //  bottom y(z) value

    int count=0;
    int coords[4];
    float hgt;
    int i=0, bmpcount=0;

    if (!use_new_terrain)
    {
        MessageBox ("TreeTops require new terrain",
                    MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    // parse the command line for the filename
    for (const char *s=buff, *c=buff; ; c++)
    {
        if (!*c || *c == ',')
        {
            // if s is still the start of the list, its the filename
            if (count >= 11)
            {
                MessageBox ("Too many parameters found for TreeTops",
                            MB_OK | MB_ICONEXCLAMATION);
                return FALSE;
            }
            else if (count >= 6)
            {
                char fname[128];
                memset (fname, 0, sizeof (fname));
                strncpy(fname, s, c-s);

                XFParseBMP bmp;
                xf_error_codes tree_err;

                if (bmp.nameread(fname))
                {
                    tree_err = bmp.error();
                    char err_str[128];
                    sprintf (err_str, "BMP load failed %s %d", fname, bmpcount);
                    MessageBox (err_str, MB_OK | MB_ICONEXCLAMATION);
                    return FALSE;
                }
                else
                {
                    trees->txt[bmpcount] = new EschStaticTexture;
                    ((EschStaticTexture *)trees->txt[bmpcount])->create(bmp.bm,1);
                }
                bmpcount ++;
            }
            else if (count == 5)
            {
                char value[128];
                memset (value,0, sizeof(value));
                strncpy(value, s, c-s);

                hgt = (float)atof(value);
                trees = new EschTerrainTreeTop ((EschTerrainEx*)terrain,
                                                coords[0], coords[1], coords[2], coords[3], hgt);
                if (!trees)
                {
                    MessageBox ("Failed to allocate memory for TreeTops",
                                MB_OK | MB_ICONEXCLAMATION);
                    return FALSE;
                }
                trees->txt = new EschTexture *[trees->tmax];
                trees->set_start_lod(0);
                trees->set_texture_lod(3);
                trees->set_perspective_lod(0);
                trees->set_smooth_lod(3);
            }
            else if (count >= 1)
            {
                char value[128];
                memset (value,0,sizeof(value));
                strncpy(value,s,c-s);

                coords[i] = atoi (value);
                i ++;
            }
            else
            {
                char *fname = new char [128];
                memset(fname, 0, sizeof(fname));
                strncpy (fname, s, c-s);
                if (!LoadTerrain(fname))
                {
                    MessageBox ("Failed to initialize terrain for TreeTops",
                                MB_OK | MB_ICONEXCLAMATION);
                    return FALSE;
                }
                delete fname;
            }
            count ++;
            if (!*c)
                break;

            s=c+1;
        }
    }

    if (draws)
        trees->sibling(draws);
    else
    {
        MessageBox ("TreeTops cannot draw by themselves",
                    MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - LoadTerrain
//���������������������������������������������������������������������������
BOOL EscherTest::LoadTerrain(char *fn)
{
    int err;

    if (terrain)
        return FALSE;

    if (!use_new_terrain)
        terrain = new EschTerrain;
    else
        terrain = new EschTerrainEx;

    if (!terrain)
        return FALSE;

    if ((err=terrain->load(fn,0))!=0)
    {
        char buff[256];
        sprintf(buff,"Could not load a terrain from file '%s', error %d",fn,err);
        MessageBox(buff, MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (!cam)
    {
        cam = new EschCameraEx(gvp);
        cam->set_position(0,terrain->get_height(0,0) + 2.0f,0);  // only two meters above the ground.
        cam->set_flags(ESCH_CAM_SHADE_SMOOTH
                       | ESCH_CAM_SHADE_FLAT
                       | ESCH_CAM_SHADE_SOLID
                       | ESCH_CAM_SHADE_WIRE
                       | ESCH_CAM_BACKCULL
                       | ESCH_CAM_MODELSPACE
                       | ESCH_CAM_PERSPECTIVE
                       | ESCH_CAM_TEXTURED
                       | ESCH_CAM_ALPHA, 1);
        cam->set_bcolor(mypal->get_index(VngoColor24bit(0,0,128)));
        cam->create_bg_bitmap(backgrnd);
    }
//    cam->set_fov(27);
//    cam->set_factor(7.5f);
    cam->set_yon(3800);

    if (!use_new_terrain)
    {
        terrain->set_lod(250,500);
    }
    else
    {
        EschTerrainEx   *tt=(EschTerrainEx*)terrain;
//        tt->set_lod(2,250.0f);
        tt->set_lod(3,350.0f,750.0f,1500.f,3000.f);
        tt->set_perspective_lod(0);
        tt->set_texture_lod(3);
        tt->set_smooth_lod(3);
    }

    if (!light)
        light = new EschVectorLight(-1,-1,-1);

    terrain->compute_shades(cam, light);

    if (draws)
        terrain->sibling(draws);
    else
        draws = terrain;

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupParticleSystem
//���������������������������������������������������������������������������
BOOL EscherTest::SetupParticleSystem(const char *name)
{
    if (prtgen)
        return FALSE;

//��� Setup generator
    prtgen =new EschParticleGenerator;
    if (!prtgen
        || prtgen->init(part_count))
    {
        MessageBox("Could not create particle generator",
                   MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    prtgen->set_linear(part_linear);

    if (strstr(name,"gravity"))
    {
        prtgen->set_acceleration(-2.0f,-9.8f,0);
    }

    if (strstr(name,"circle"))
    {
        prtgen->set_circle(250, 0);
        prtgen->set_init_dir(0,-1,0);
    }
    else if (strstr(name,"rect"))
    {
        prtgen->set_rectangle(5, 20, 45);
    }
    else
    {
        prtgen->set_sphere(5);
    }

    prtgen->set_speed(part_speed,(part_speed/4));
    prtgen->set_alpha(part_alpha,(part_alpha/4));

    if (strstr(name,"color"))
    {
        prtgen->set_color(mypal,
                          VngoColor24bit(0,200,0),
                          VngoColor24bit(255,55,0));
    }
    else
    {
        prtgen->set_color(mypal->get_index(VngoColor24bit(255,0,0)));
    }


    if (strstr(name,"pyramids"))
    {
        prtgen->set_parts(100);
        prtgen->set_size(2,7);
        prtgen->set_callback(esch_generate_pyramid);
    }
    else if (strstr(name,"sprites"))
    {
        if (!sprite)
        {
            MessageBox("Must have Sprite Test enabled",
                       MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }
        float temp_part = (part_count < 1000)?100.0f:part_count / 10.0f;
        prtgen->set_parts(temp_part);
        prtgen->set_callback(esch_generate_sprite,sprite);
        prtgen->set_rotrate(part_rotrate);
        prtgen->set_rotrate_low(part_rotrate_low);
        prtgen->set_rotrate_high(part_rotrate_high);
    }
    if (strstr(name, "lines"))
    {
        float temp_part = (part_count < 1000)?100.0f:part_count / 10.0f;
        prtgen->set_parts(temp_part);
        prtgen->set_callback(esch_generate_line);
        prtgen->set_init_dir (0,1.f,0);
    }
    else
    {
        float temp_part = (part_count < 1000)?100.0f:part_count / 10.0f;
        prtgen->set_parts(temp_part,100);
        prtgen->set_init_dir(0,-1.0f,0);
    }
    prtgen->set_lifetime(part_life,(part_life/4));

//��� Create camera/lights if not already defined
    if (!cam)
    {
        cam = new EschCameraEx(gvp);
        cam->set_position(0,0,-500);
        cam->set_flags(ESCH_CAM_SHADE_SMOOTH
                       | ESCH_CAM_SHADE_FLAT
                       | ESCH_CAM_SHADE_SOLID
                       | ESCH_CAM_SHADE_WIRE
                       | ESCH_CAM_BACKCULL
                       | ESCH_CAM_MODELSPACE
                       | ESCH_CAM_TEXTURED
                       | ESCH_CAM_ALPHA, 1);
        cam->set_bcolor(mypal->get_index(VngoColor24bit(0,0,0)));
        cam->create_bg_bitmap(backgrnd);
    }

    if (!light)
        light = new EschVectorLight(-1,-1,-1);

//��� Add to drawlist
    if (draws)
        prtgen->sibling(draws);
    else
        draws = prtgen;

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupStarfield
//���������������������������������������������������������������������������
BOOL EscherTest::SetupStarfield(BOOL fixed, BOOL brights)
{
    if (starfield)
        return FALSE;

    starfield = new EschStarfield;
    if (!starfield
        || starfield->create_stars(10000,(brights) ? 1 : 0))
    {
        MessageBox("Could not create starfield", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    starfield->set_color(mypal->get_index(VngoColor24bit(255,255,255)));

    if (fixed)
        starfield->set_flags(ESCH_SFLD_FTL, 1);

    if (!cam)
    {
        cam = new EschCameraEx(gvp);
        cam->set_position(0,0,-300);
        cam->set_flags(ESCH_CAM_SHADE_SMOOTH
                       | ESCH_CAM_SHADE_FLAT
                       | ESCH_CAM_SHADE_SOLID
                       | ESCH_CAM_SHADE_WIRE
                       | ESCH_CAM_BACKCULL
                       | ESCH_CAM_MODELSPACE
                       | ESCH_CAM_TEXTURED
                       | ESCH_CAM_ALPHA, 1);
        cam->create_bg_bitmap(backgrnd);
        cam->set_yon(20000);
    }

    cam->set_bcolor(mypal->get_index(VngoColor24bit(0,0,0)));

    if (draws)
        starfield->sibling(draws);
    else
        draws = starfield;

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupExplosion
//���������������������������������������������������������������������������
BOOL EscherTest::SetupExplosion(const char *buff)
{
    if (explosion)
        return FALSE;

    if (!fire)
    {
        fire = new EschFireTexture(128,128,mypal);
        if (!fire)
        {
            MessageBox("Couldn't create fire texture", MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }
        fire->set_flags(ESCH_TXT_SKIPANIMATE, 1);
    }

    explosion = new EschPlosion(40,40,fire);
    if (!explosion)
    {
        MessageBox("Could not create explosion", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (strstr(buff,"circular"))
        explosion->set_flags(ESCH_PLSN_CIRCULAR, 1);
    else if (strstr(buff,"triangular"))
        explosion->set_flags(ESCH_PLSN_TRIANGULAR, 1);

    explosion->set_step(0.02f);
    explosion->set_alpha(alpha);

    if (!cam)
    {
        cam = new EschCameraEx(gvp);
        cam->set_position(0,0,-300);
        cam->set_flags(ESCH_CAM_SHADE_SMOOTH
                       | ESCH_CAM_SHADE_FLAT
                       | ESCH_CAM_SHADE_SOLID
                       | ESCH_CAM_SHADE_WIRE
                       | ESCH_CAM_BACKCULL
                       | ESCH_CAM_MODELSPACE
                       | ESCH_CAM_TEXTURED
                       | ESCH_CAM_ALPHA, 1);
        cam->create_bg_bitmap(backgrnd);
    }

    if (draws)
        explosion->sibling(draws);
    else
        draws = explosion;

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupMetabox
//���������������������������������������������������������������������������
BOOL EscherTest::SetupMetabox(const char *buff)
{
    if (metabox)
        return FALSE;

    metabox = new EschMetabox;
    if (!metabox)
    {
        MessageBox("Could not create metabox",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    metabox->set_position(0,0,0);

    metabox->set_color(mypal->get_index(VngoColor24bit(255,0,0)),
                       ESCH_MBOX_FACE_TOP);
    metabox->set_color(mypal->get_index(VngoColor24bit(255,0,0)),
                       ESCH_MBOX_FACE_BOTTOM);
    metabox->set_color(mypal->get_index(VngoColor24bit(0,255,0)),
                       ESCH_MBOX_FACE_FRONT);
    metabox->set_color(mypal->get_index(VngoColor24bit(0,255,0)),
                       ESCH_MBOX_FACE_BACK);
    metabox->set_color(mypal->get_index(VngoColor24bit(0,0,255)),
                       ESCH_MBOX_FACE_LEFT);
    metabox->set_color(mypal->get_index(VngoColor24bit(0,0,255)),
                       ESCH_MBOX_FACE_RIGHT);
    metabox->create_cube(10);
    mbox_size = 10;

    if (mtxt)
        metabox->set_texture(mtxt);

    metabox->set_alpha(alpha);

    if (!cam)
    {
        cam = new EschCameraEx(gvp);
        cam->set_position(0,0,-100);
        cam->set_flags(ESCH_CAM_SHADE_SMOOTH
                       | ESCH_CAM_SHADE_FLAT
                       | ESCH_CAM_SHADE_SOLID
                       | ESCH_CAM_SHADE_WIRE
                       | ESCH_CAM_BACKCULL
                       | ESCH_CAM_MODELSPACE
                       | ESCH_CAM_ALPHA
                       | ESCH_CAM_TEXTURED, 1);
        cam->create_bg_bitmap(backgrnd);
    }

    cam->set_bcolor(mypal->get_index(VngoColor24bit(0,0,128)));

    if (draws)
        metabox->sibling(draws);
    else
        draws = metabox;

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupPlane
//���������������������������������������������������������������������������
BOOL EscherTest::SetupPlane(const char *buff)
{
    if (plane)
        return FALSE;

    plane = new EschPlaneDraw;
    if (!plane)
    {
        MessageBox("Could not create plane",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    plane->set_plane(0,1,0,0,-15,0);

    plane->set_color(mypal->get_index(VngoColor24bit(0,255,0)));

    if (mtxt)
        plane->set_texture(mtxt);

    plane->set_alpha(alpha);

    if (!cam)
    {
        cam = new EschCameraEx(gvp);
        cam->set_position(0,0,-100);
        cam->set_flags(ESCH_CAM_SHADE_SMOOTH
                       | ESCH_CAM_SHADE_FLAT
                       | ESCH_CAM_SHADE_SOLID
                       | ESCH_CAM_SHADE_WIRE
                       | ESCH_CAM_MODELSPACE
                       | ESCH_CAM_PERSPECTIVE
                       | ESCH_CAM_ALPHA
                       | ESCH_CAM_TEXTURED, 1);
        cam->create_bg_bitmap(backgrnd);
    }

    cam->set_bcolor(mypal->get_index(VngoColor24bit(0,0,128)));

    if (draws)
        plane->sibling(draws);
    else
        draws = plane;

    if (!light)
        light = new EschVectorLight(-1,-1,-1);

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - SetupAnimation
//���������������������������������������������������������������������������
BOOL EscherTest::SetupAnimation(const char *buff)
{
    char key_file[80];
    char tok_file[80];
    char hide_file[80];
    int count = 0;

    // parse the command line for filenames
    for (const char *s=buff, *c=buff; ; c++)
    {
        if (!*c || *c == ',')
        {
            if (count == 0)
            {
                // keyframe filename
                memset(key_file,0,sizeof(key_file));
                strncpy (key_file, s, c-s);
                XFParseIFF iff;
                int err;

                if (iff.open(key_file, XF_OPEN_READ | XF_OPEN_DENYWRITE))
                {
                    MessageBox("ERROR: File Open failed in SetupAnimation",MB_OK | MB_ICONEXCLAMATION);
                }
                int keyforms_found = 0;

                while (iff.next() == XF_ERR_NONE)
                {
                    if (iff.chunkid == iff.makeid ('F','O','R','M')
                        && iff.formid == iff.makeid ('K','E','Y','F'))
                            keyforms_found ++;
                }
                iff.close();
                if (!keyforms_found)
                {
                    MessageBox ("Error: Keyframe file contains no keyframes", MB_OK | MB_ICONEXCLAMATION);
                }

                if (EschKeyframeMan)
                    delete EschKeyframeMan;
                EschKeyframeMan = new EschKeyframer;

                if (!EschKeyframeMan)
                {
                    MessageBox("Error: EschKeyframeMan create failed", MB_OK | MB_ICONEXCLAMATION);
                }
                if (iff.open (key_file, XF_OPEN_READ | XF_OPEN_DENYWRITE))
                {
                    MessageBox("ERROR: File Reopen failed in SetupAnimation",MB_OK | MB_ICONEXCLAMATION);
                }

                while (iff.next() == XF_ERR_NONE)
                {
                    if (iff.chunkid == iff.makeid('F','O','R','M')
                        && iff.formid == iff.makeid('K','E','Y','F'))
                    {
                        err = EschKeyframeMan->load (&iff);
                        if (err)
                            break;
                    }
                }
                iff.close();
            }
            else if (count == 1)
            {
                // token filename
                memset(tok_file,0,sizeof(tok_file));
                strncpy (tok_file, s, c-s);
                ((EschKeyframeDraw *)curmesh)->initialize_tokens(tok_file);
                ((EschKeyframeDraw *)curmesh)->tokenize_names();
            }
            else if (count == 2)
            {
                // hide-list filename
                memset(hide_file, 0, sizeof(hide_file));
                strncpy (hide_file, s, c-s);
                XFParseIFF iff;
                int hide_count=0;

                if (iff.open (hide_file, XF_OPEN_READ | XF_OPEN_DENYWRITE))
                {
                    MessageBox("ERROR: SetupAnimation object hide file open failed",MB_OK|MB_ICONEXCLAMATION);
                }

                while (iff.next() == XF_ERR_NONE)
                {
                    if (iff.chunkid == iff.makeid ('H','I','D','E'))
                        hide_count ++;
                }
                iff.close();

                if (hide_count)
                {
                    struct to_hide
                    {
                        dword type;
                    };

                    to_hide *temp_list = new to_hide[hide_count];

                    if (!temp_list)
                    {
                        MessageBox ("Error: Failed to allocate memory for hide list", MB_OK | MB_ICONEXCLAMATION);
                    }
                    if (iff.open (hide_file, XF_OPEN_READ | XF_OPEN_DENYWRITE))
                    {
                        MessageBox("Error: Failed to reopen hide list file", MB_OK|MB_ICONEXCLAMATION);
                    }

                    int i=0;
                    while (iff.next() == XF_ERR_NONE)
                    {
                        if (iff.chunkid == iff.makeid('H','I','D','E'))
                        {
                            if (iff.read(&temp_list[i].type))
                            {
                                MessageBox ("Error: Hide type read failed",MB_OK|MB_ICONEXCLAMATION);
                            }
                            i++;
                        }
                    }
                    for (i=0; i<hide_count; i++)
                    {
                        ((EschKeyframeDraw *)curmesh)->hide_by_absolute_ktype (temp_list[i].type);
                    }
                    delete [] temp_list;
                }
            }
            else if (count >= 3)
            {
                MessageBox ("Too many parameters found for Animation",
                           MB_OK | MB_ICONEXCLAMATION);
                return FALSE;
            }
            count ++;
            if (!*c)
                break;
            s=c+1;
        }
    }

    // now get and set all keyframes

    // step through animations and build a list of key_chains
    anim_chain_count = EschKeyframeMan->get_chain_count();

    struct tempkey
    {
        char key_type[M_TYPE_LEN];
    };
    tempkey *kchain_temp = new tempkey[anim_chain_count];

    if (!kchain_temp)
    {
        MessageBox("ERROR:  SetupAnimation() failed to allocate memory for key chains",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

	int i = 0;

    // look into the Keyframe Manager and copy the key_types into the temp array in order of appearance
    EschKeyframeMan->get_next_chain_type(0, kchain_temp[0].key_type);
    for (i=1; i<anim_chain_count; i++)
    {
        EschKeyframeMan->get_next_chain_type(kchain_temp[i-1].key_type, kchain_temp[i].key_type);
    }

    // step through the temp array and grab the coresponding keyframes from the Keyframe Manager
    // stuff the pointers to the Keyframes into the mesh hierarchy with set_key
    // set the key_chain as inactive so it won't animation right now
    for (i=0; i<anim_chain_count; i++)
    {
        EschKeyframe *temp_key;
        temp_key = EschKeyframeMan->get (((EschKeyframeDraw *)curmesh)->get_ktype(),
                                         kchain_temp[i].key_type, 0);
        if (temp_key)
        {
            ((EschKeyframeDraw *)curmesh)->set_key(temp_key, 0, anim_time);
            ((EschKeyframeDraw *)curmesh)->set_inactivity(i);
        }
    }
    delete [] kchain_temp;

    ((EschKeyframeDraw *)curmesh)->set_activity(0);
    float time = float(anim_clock.check())/1024.0f;
    ((EschKeyframeDraw *)curmesh)->reset_keyframes(0,time);

    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - GetEvents
//���������������������������������������������������������������������������
void EscherTest::GetEvents()
{
    if (!evt)
    {
        events = MaxEventList (0);
        return;
    }

    // Otherwise, strobe the devices and get our events (and oneshots)
    events = evt->process ();
    single_events = oneshot.process (events);
    toggle_events = toggles.process (events);
}


//���������������������������������������������������������������������������
// EscherTest - Begin
//���������������������������������������������������������������������������
void EscherTest::Begin ()
{
    clock.clear();
    fps_clock.clear();
    anim_clock.clear();
    frames=0;
    total_frames=0;
    total_time=0;
}


//���������������������������������������������������������������������������
// EscherTest - End
//���������������������������������������������������������������������������
void EscherTest::End (char *buff)
{
    total_frames += frames;
    total_time += fps_clock.check();

    sprintf(buff,"%d frames in %d ms, rate=%f\n sins = 0x%x\n Screen Name = %s\n",
                 total_frames, total_time,
                 (float)( (total_time)
                          ? ((double)total_frames / (double)total_time) * double(1000)
                          : 0), screen->sins, screen->hwName);
}


//���������������������������������������������������������������������������
// EscherTest - PumpWindows
//���������������������������������������������������������������������������
BOOL EscherTest::PumpWindows ()
{
    MSG msg;

    Devs->wm_clear();
    while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
    {
        if (GetMessage (&msg, 0, 0, 0) == 0)
            return FALSE;

        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
    return TRUE;
}


//���������������������������������������������������������������������������
// EscherTest - ProcessEvents
//���������������������������������������������������������������������������
void EscherTest::ProcessEvents()
{
    int                 doreshade=0;
    short               dx, dy;
    dword               cam_flags;

    // The shift has the effect of simultaneously
    // converting the number to a Flx16 and dividing by 1024,
    Flx16 interval(clock.check() << 6,0);

    if (prtgen)
        prtgen->set_interval(interval);

    clock.clear();

    evt->get_mouse_movement (&dx, &dy);

//��� Check general events
    if (events.check (DONE))
    {
        PostQuitMessage(0);
    }

    if (events.check (FASTER))
    {
        if (ScriptRotateDegrees < 180)
            ScriptRotateDegrees = ScriptRotateDegrees + 1.0f;
    }
    else if (events.check (SLOWER))
    {
        if (ScriptRotateDegrees > 1)
            ScriptRotateDegrees = ScriptRotateDegrees - 1.0f;
    }

    if (single_events.check(SHOW_FPS))
    {
        show_fps = !show_fps;
    }

//��� Object hierarchy movement
    if (curmesh && scene)
    {
        if (single_events.check(OBJECT_NEXT))
        {
            if (curmesh->next() != NULL)
                curmesh = (EschMeshDraw*) curmesh->next();
        }
        if (single_events.check(OBJECT_PREV))
        {
             if (curmesh->prev() != NULL)
                 curmesh = (EschMeshDraw*) curmesh->prev();
        }
        if (single_events.check(OBJECT_CHILD))
        {
            if (curmesh->child() != NULL)
                curmesh = (EschMeshDraw*) curmesh->child();
            else
                curmesh = scene->meshes;
        }
    }

//��� Object rotation
    if (events.check(OBJECT_ROTATE))
    {
        if (events.check (MOVEXY))
        {
            if (curmesh)
            {
                curmesh->rotatex (float(-dy));
                curmesh->rotatey (float(-dx));
            }
            if (metabox)
            {
                metabox->rotatex (float(-dy));
                metabox->rotatey (float(-dx));
            }
            if (plane)
            {
                plane->rotatex (float(dy));
                plane->rotatey (float(dx));
            }
            if (explosion)
            {
                explosion->rotatex (float(-dy));
                explosion->rotatey (float(-dx));
            }
            if (prtgen)
            {
                prtgen->rotatex (float(-dy));
                prtgen->rotatey (float(-dx));
            }
        }

        if (events.check (MOVEZ))
        {
            if (curmesh)
                curmesh->rotatez (float(-dx));
            if (metabox)
                metabox->rotatez (float(-dx));
            if (plane)
                plane->rotatez (float(dx));
            if (explosion)
                explosion->rotatez (float(-dx));
            if (prtgen)
                prtgen->rotatez (float(-dx));
        }

        if (events.check (UP))
        {
            if (curmesh)
                curmesh->rotatex (RotateDegrees);
            if (metabox)
                metabox->rotatex (RotateDegrees);
            if (plane)
                plane->rotatex (-RotateDegrees);
            if (prtgen)
                prtgen->rotatex (RotateDegrees);
        }

        if (events.check (DOWN))
        {
            if (curmesh)
                curmesh->rotatex (-RotateDegrees);
            if (metabox)
                metabox->rotatex (-RotateDegrees);
            if (plane)
                plane->rotatex (RotateDegrees);
            if (explosion)
                explosion->rotatex (-RotateDegrees);
            if (prtgen)
                prtgen->rotatex (-RotateDegrees);
        }

        if (events.check (LEFT))
        {
            if (curmesh)
                curmesh->rotatey (RotateDegrees);
            if (metabox)
                metabox->rotatey (RotateDegrees);
            if (plane)
                plane->rotatey (-RotateDegrees);
            if (explosion)
                explosion->rotatey (RotateDegrees);
            if (prtgen)
                prtgen->rotatey (RotateDegrees);
        }

        if (events.check (RIGHT))
        {
            if (curmesh)
                curmesh->rotatey (-RotateDegrees);
            if (metabox)
                metabox->rotatey (-RotateDegrees);
            if (plane)
                plane->rotatey (RotateDegrees);
            if (explosion)
                explosion->rotatey (-RotateDegrees);
            if (prtgen)
                prtgen->rotatey (-RotateDegrees);
        }
    }

//��� Object movement
    if (events.check (OBJECT_MOVE))
    {
        if (events.check (MOVEXY))
        {
            EschVector v(float(dx), float(-dy), 0.0f);

            v.transform(&cam->eye.orient);

            if (curmesh)
                curmesh->translate (&v);
            if (metabox)
                metabox->translate (&v);
            if (explosion)
                explosion->translate (&v);
            if (prtgen)
                prtgen->translate (&v);
        }

        if (events.check (MOVEZ))
        {
            EschVector v(0.0f, 0.0f, float(-dy));

            v.transform(&cam->eye.orient);

            if (curmesh)
                curmesh->translate (&v);
            if (metabox)
                metabox->translate (&v);
            if (explosion)
                explosion->translate (&v);
            if (prtgen)
                prtgen->translate (&v);
        }

        if (events.check (UP))
        {
            EschVector v(0.0f, 1.0f, 0.0f);

            v.transform(&cam->eye.orient);

            if (curmesh)
                curmesh->translate (&v);
            if (metabox)
                metabox->translate (&v);
            if (explosion)
                explosion->translate (&v);
            if (prtgen)
                prtgen->translate (&v);
        }

        if (events.check (DOWN))
        {
            EschVector v(0.0f, -1, 0.0f);

            v.transform(&cam->eye.orient);

            if (curmesh)
                curmesh->translate (&v);
            if (metabox)
                metabox->translate (&v);
            if (explosion)
                explosion->translate (&v);
            if (prtgen)
                prtgen->translate (&v);
        }

        if (events.check (LEFT))
        {
            EschVector v(-1, 0.0f, 0.0f);

            v.transform(&cam->eye.orient);

            if (curmesh)
                curmesh->translate (&v);
            if (metabox)
                metabox->translate (&v);
            if (explosion)
                explosion->translate (&v);
            if (prtgen)
                prtgen->translate (&v);
        }

        if (events.check (RIGHT))
        {
            EschVector v(1, 0.0f, 0.0f);

            v.transform(&cam->eye.orient);

            if (curmesh)
                curmesh->translate (&v);
            if (metabox)
                metabox->translate (&v);
            if (explosion)
                explosion->translate (&v);
            if (prtgen)
                prtgen->translate (&v);
        }

        if (partn && curmesh)
            partn->update(curmesh);
    }

//��� Camera rotation
    if (events.check (CAMERA_ROTATE))
    {
        if (events.check (MOVEXY))
        {
            cam->yaw (float(-dx));
            cam->pitch (float(-dy));
        }

        if (events.check (MOVEZ))
            cam->roll (float(-dx));

        if (events.check (UP))
            cam->pitch (RotateDegrees);

        if (events.check (DOWN))
            cam->pitch (-RotateDegrees);

        if (events.check (LEFT))
            cam->yaw (RotateDegrees);

        if (events.check (RIGHT))
            cam->yaw (-RotateDegrees);
    }

//��� Camera movement
    if (events.check (CAMERA_MOVE))
    {
        if (events.check (MOVEXY))
        {
            cam->move(float(-dx), float(dy), 0.0f);
        }

        if (events.check (MOVEZ))
        {
            cam->move(0.0f, 0.0f, float(dy));
        }

        if (events.check (UP))
        {
            cam->move(0.0f, 1, 0.0f);
        }

        if (events.check (DOWN))
        {
            cam->move(0.0f, -1, 0.0f);
        }

        if (events.check (LEFT))
        {
            cam->move(-1, 0.0f, 0.0f);
        }

        if (events.check (RIGHT))
        {
            cam->move(1, 0.0f, 0.0f);
        }
        if ((cam->flags & ESCH_CAM_APP0) && terrain)
        {
            EschPoint tp;
            cam->get_position(&tp);
            cam->set_position(tp.x,terrain->get_height(tp.x,tp.z) + 2.5f,tp.z);  // only two meters above the ground.

        }
    }

//��� Camera misc
    if (events.check (ADJUST_FOV))
    {
        float fov = cam->fov;

        if (events.check (MOVEXY))
        {
            fov += float(dy);

            if (fov < 1.0f)
                fov = 1.0f;

            if (fov > 175.0f)
                fov = 175.0f;
        }

        cam->set_fov(fov);
    }

    if (events.check (ADJUST_ORTHO))
    {
        float w = (cam->flags & ESCH_CAM_ORTHO) ? cam->width : 100.0f;

        if (events.check (MOVEXY))
        {
            w += float(dy);

            if (w < 1.0f)
                w = 1.0f;

            if (w > 1000.0f)
                w = 1000.0f;
        }

        cam->set_ortho(w);
    }

    if (events.check (ADJUST_FACTOR))
    {
        if (events.check (MOVEXY))
        {
            float factor = cam->factor;

            factor += float(dy);

            if (factor < 1.0f)
                factor = 1.0f;

            if (factor > 12.0f)
                factor = 12.0f;

            cam->set_factor(factor);
        }
    }

    if (backgrnd && events.check (ADJUST_BM_OFFSET))
    {
        if (events.check (MOVEXY))
        {
            long offx = cam->bg_offx;
            long offy = cam->bg_offy;

            offx -= dx;
            offy -= dy;

            if (offx < -(backgrnd->width+cam->vport->vbuff.width))
                offx = -((short)backgrnd->width+cam->vport->vbuff.width);

            if (offx > backgrnd->width)
                offx = backgrnd->width;

            if (offy < -(backgrnd->height+cam->vport->vbuff.height))
                offy = -((short)backgrnd->height+cam->vport->vbuff.height);

            if (offy > backgrnd->height)
                offy = backgrnd->height;

            cam->set_bg_offset((short)offx, (short)offy);
        }
    }

    // Get the camera flags so we can change 'em!
    cam_flags = cam->flags;

    // These SHADE events are meant to be mutually exclusive.
    if (single_events.check (SHADE_SOLID))
    {
        cam_flags &= ~(ESCH_CAM_SHADE_FLAT
                       |ESCH_CAM_SHADE_SMOOTH
                       |ESCH_CAM_SHADE_SPECULAR);
        cam_flags |= ESCH_CAM_SHADE_SOLID
                     | ESCH_CAM_SHADE_WIRE;
        doreshade=1;
    }

    if (single_events.check (SHADE_FLAT))
    {
        cam_flags &= ~(ESCH_CAM_SHADE_SMOOTH
                       |ESCH_CAM_SHADE_SPECULAR);
        cam_flags |= ESCH_CAM_SHADE_FLAT
                     | ESCH_CAM_SHADE_SOLID
                     | ESCH_CAM_SHADE_WIRE;
        doreshade=1;
    }

    if (single_events.check (SHADE_FLAT_SPECULAR))
    {
        cam_flags &= ~ESCH_CAM_SHADE_SMOOTH;
        cam_flags |= ESCH_CAM_SHADE_SPECULAR
                     | ESCH_CAM_SHADE_FLAT
                     | ESCH_CAM_SHADE_SOLID
                     | ESCH_CAM_SHADE_WIRE;
        doreshade=1;
    }

    if (single_events.check (SHADE_SMOOTH))
    {
        cam_flags &= ~ESCH_CAM_SHADE_SPECULAR;
        cam_flags |= ESCH_CAM_SHADE_SMOOTH
                     | ESCH_CAM_SHADE_FLAT
                     | ESCH_CAM_SHADE_SOLID
                     | ESCH_CAM_SHADE_WIRE;
        doreshade=1;
    }

    if (single_events.check (SHADE_SPECULAR))
    {
        cam_flags |= ESCH_CAM_SHADE_SPECULAR
                     | ESCH_CAM_SHADE_SMOOTH
                     | ESCH_CAM_SHADE_FLAT
                     | ESCH_CAM_SHADE_SOLID
                     | ESCH_CAM_SHADE_WIRE;
        doreshade=1;
    }

    if (single_events.check (SHADE_WIRE))
    {
        cam_flags &= ~(ESCH_CAM_SHADE_SOLID
                       |ESCH_CAM_SHADE_FLAT
                       |ESCH_CAM_SHADE_SPECULAR
                       |ESCH_CAM_SHADE_SMOOTH);
        cam_flags |= ESCH_CAM_SHADE_WIRE;
        doreshade=1;
    }

    if (single_events.check (BACKCULL))
        cam_flags ^= ESCH_CAM_BACKCULL;

    if (single_events.check (ALL_LINES))
        cam_flags ^= ESCH_CAM_SHOW_ALL_LINES;

    if (single_events.check (MODEL_SPACE))
        cam_flags ^= ESCH_CAM_MODELSPACE;

    if (single_events.check (TEXTURE_MAP))
        cam_flags ^= ESCH_CAM_TEXTURED;

    if (single_events.check (BITMAP_BACKGROUND))
        cam_flags ^= ESCH_CAM_IGNORE_BMAP;

    if (single_events.check (SHADE_PERSPECTIVE))
        cam_flags ^= ESCH_CAM_PERSPECTIVE;

    if (single_events.check (SHADE_ALPHA))
        cam_flags ^= ESCH_CAM_ALPHA;

    // Now, set those flags!
    cam->set_flags (cam_flags);

    if (single_events.check (HAZING))
    {
        if (cam->vport->vflags & VNGO_HAZE_ON)
        {
            cam->vport->haze_off();
        }
        else
        {
            cam->set_haze(0.5f, 0.85f);
        }
    }

    if (single_events.check (GRADIENT))
    {
        if (cam->flags & ESCH_CAM_GRADIENT)
        {
            cam->flags &= ~ESCH_CAM_GRADIENT;
        }
        else
        {
            cam->set_gradient(VngoColor24bit(0,0,128), 10,
                              VngoColor24bit(0,128,0), 0,
                              VngoColor24bit(128,0,0), -10);
        }
    }

//��� Alpha adjust
    if (events.check (ADJUST_ALPHA))
    {
        if (events.check (MOVEXY))
        {
            alpha += dy;

            if (alpha < 0)
                alpha = 0;

            if (alpha > 255)
                alpha = 255;

            if (explosion)
                explosion->set_alpha(alpha);
            if (sprite)
                sprite->set_alpha(alpha);
            if (metabox)
                metabox->set_alpha(alpha);
            if (plane)
                plane->set_alpha(alpha);
        }
    }

//��� Metabox adjust
    if (events.check (ADJUST_MBOX_SIZE) && metabox)
    {
        if (events.check (MOVEXY))
        {
            mbox_size -= float(dy) / 16.0f;

            if (mbox_size < 1.0f)
                mbox_size = 1.0f;

            if (mbox_size > 500.0f)
                mbox_size = 500.0f;

            metabox->create_cube(mbox_size);
        }
    }

//��� Terrain adjust
    if (single_events.check (TERRAIN_DOTS) && terrain)
        terrain->flags ^= ESCH_TRN_DOTS;
    if (single_events.check (TERRAIN_LOD) && terrain)
        terrain->flags ^= ESCH_TRN_LOD;
    if (single_events.check (TERRAIN_DEBUG) && terrain)
        terrain->flags ^= ESCH_TRN_DEBUG;

    if (single_events.check (CAM_HOVER) && terrain)
        cam->set_flags(cam->flags ^ ESCH_CAM_APP0);

//��� Misc adjust
    if (single_events.check (SHOW_EXTENTS))
    {
        drawexts++;
        if (drawexts > 3)
            drawexts=0;
    }

    if (single_events.check (CHECK_EXTENTS))
    {
        for(EschMeshDraw *ptr=scene->meshes;
            ptr != NULL;
            ptr = (EschMeshDraw*)ptr->next())
        {
            if (ptr->flags & ESCH_MSHD_NOEXTENTSCHK)
                ptr->set_flags(ESCH_MSHD_NOEXTENTSCHK, 0);
            else
                ptr->set_flags(ESCH_MSHD_NOEXTENTSCHK, 1);
        }

    }

    if (single_events.check (SHOW_PARTN))
    {
        drawpartn = !drawpartn;
    }

    if (single_events.check (ZBUFFER))
    {
        if (cam->vport->vflags & VNGO_ZBUFFER_DEV)
        {
            if (cam->vport->vflags & VNGO_ZBUFFER_ACTIVE)
                cam->vport->zbuffer_off();
            else
                cam->vport->zbuffer_on();
        }
    }

    if (single_events.check (SORT))
    {
        cam->flags ^= ESCH_CAM_SORT;
        if (cam->vport->vflags & VNGO_ZBUFFER_DEV)
        {
            if (cam->flags & ESCH_CAM_SORT)
                cam->vport->zbuffer_off();
            else
                cam->vport->zbuffer_on();
        }
    }

    if (single_events.check (PARTN_LIST) && partn)
    {
        switch (partn->get_type())
        {
            case ESCH_DRWT_PRTN_GRID:
                {
                    EschGridPartition *gpartn = (EschGridPartition*)partn;

                    for(ulong i=0; i < gpartn->nregions; i++)
                    {
                        for(EschPartitionList *ptr = gpartn->regions[i]; ptr != 0; ptr = ptr->next)
                        {
                            char buff[128];
                            if (!ptr->item)
                            {
                                wsprintf(buff,"Region #%i\n\n Invalid Entry!", i);
                            }
                            else
                            {
                                wsprintf(buff,"Region #%i\n\nDrawables '%s'",
                                            i,
                                            ptr->item->name);
                            }
                            MessageBox(buff, MB_OK);
                        }
                    }
                }
                break;
            case ESCH_DRWT_PRTN_QUAD:
                {
                    EschQuadTreePartition *qpartn = (EschQuadTreePartition*)partn;

                    EschQuadTreeStats stats;
                    qpartn->compute_stats(&stats);

                    char    buff[64];
                    char    str[4096];
                    *str = 0;

                    sprintf(buff,"hidepth=%d\n",stats.hidepth);
                    strcat(str,buff);

                    sprintf(buff,"hicount=%d\n",stats.hicount);
                    strcat(str,buff);

                    sprintf(buff,"nodes=%d\n",stats.nodes);
                    strcat(str,buff);

                    sprintf(buff,"leaves=%d\n",stats.leaves);
                    strcat(str,buff);

                    sprintf(buff,"items=%d\n",stats.items);
                    strcat(str,buff);

                    sprintf(buff,"items_nonleaf=%d\n",stats.items_nonleaf);
                    strcat(str,buff);

                    sprintf(buff,"items_global=%d\n",stats.items_global);
                    strcat(str,buff);

                    MessageBox(str, MB_OK);
                }
                break;
            case ESCH_DRWT_PRTN_OCT:
                {
                    EschOctTreePartition *opartn = (EschOctTreePartition*)partn;

                    EschOctTreeStats stats;
                    opartn->compute_stats(&stats);

                    char    buff[64];
                    char    str[4096];
                    *str = 0;

                    sprintf(buff,"hidepth=%d\n",stats.hidepth);
                    strcat(str,buff);

                    sprintf(buff,"hicount=%d\n",stats.hicount);
                    strcat(str,buff);

                    sprintf(buff,"nodes=%d\n",stats.nodes);
                    strcat(str,buff);

                    sprintf(buff,"leaves=%d\n",stats.leaves);
                    strcat(str,buff);

                    sprintf(buff,"items=%d\n",stats.items);
                    strcat(str,buff);

                    sprintf(buff,"items_nonleaf=%d\n",stats.items_nonleaf);
                    strcat(str,buff);

                    sprintf(buff,"items_global=%d\n",stats.items_global);
                    strcat(str,buff);

                    MessageBox(str, MB_OK);
                }
                break;
        }
    }

    if (single_events.check(PARTN_TOGGLE) && partn)
    {
        partn->set_flags(partn->flags ^ ESCH_PARTN_OFF);
    }

    if (explosion)
    {
        if (single_events.check(EXPLOSION_RESET))
            explosion->reset();
    }

//��� Light adjust
    if (light)
    {
        EschLight   *l;

        // Can't move 'ambients'
        for(l=light; l != NULL; l = l->next())
        {
            if (l->get_type() != ESCH_LGTT_AMBIENT)
                break;
        }
        if (l == NULL)
            l = light;

        if (events.check (LIGHT_IN_BRIGHTER))
        {
            if (l->get_intensity() < 255-16)
                l->set_intensity((byte)( l->get_intensity() + 16) );
            doreshade=1;
        }
        else if (events.check (LIGHT_IN_DIMMER))
        {
            if (l->get_intensity() > 16)
                l->set_intensity( (byte)( l->get_intensity() - 16) );
            doreshade=1;
        }

        if (events.check (LIGHT_POSITION))
        {
            if (l->get_type() == ESCH_LGTT_VECTOR)
            {

                if (events.check (MOVEXY))
                {
                    ((EschVectorLight*)l)->rotatey (dx);
                    ((EschVectorLight*)l)->rotatex (dy);
                }

                if (events.check (UP))
                    ((EschVectorLight*)l)->rotatex (RotateDegrees);

                if (events.check (DOWN))
                    ((EschVectorLight*)l)->rotatex (-RotateDegrees);

                if (events.check (LEFT))
                    ((EschVectorLight*)l)->rotatey (RotateDegrees);

                if (events.check (RIGHT))
                    ((EschVectorLight*)l)->rotatey (-RotateDegrees);
            }
            else if (l->get_type() == ESCH_LGTT_FPOINT
                     || l->get_type() == ESCH_LGTT_FATTEN
                     || l->get_type() == ESCH_LGTT_FSPOT)
            {

                if (events.check (MOVEXY))
                    ((EschFastPointLight*)l)->translate (float(dx), float(-dy), 0.0f);

                if (events.check (MOVEZ))
                    ((EschFastPointLight*)l)->translate (0.0f, 0.0f, float(-dx));

                if (events.check (UP))
                    ((EschFastPointLight*)l)->translate (0.0f, 1, 0.0f);

                if (events.check (DOWN))
                    ((EschFastPointLight*)l)->translate (0.0f, -1, 0.0f);

                if (events.check (LEFT))
                    ((EschFastPointLight*)l)->translate (-1, 0.0f, 0.0f);

                if (events.check (RIGHT))
                    ((EschFastPointLight*)l)->translate (1, 0.0f, 0.0f);

            }
            else if (l->get_type() == ESCH_LGTT_POINT
                     || l->get_type() == ESCH_LGTT_ATTEN
                     || l->get_type() == ESCH_LGTT_SPOT)
            {

                if (events.check (MOVEXY))
                    ((EschPointLight*)l)->translate (float(dx), float(-dy), 0.0f);

                if (events.check (MOVEZ))
                    ((EschPointLight*)l)->translate (0.0f, 0.0f, float(-dx));

                if (events.check (UP))
                    ((EschPointLight*)l)->translate (0.0f, 1, 0.0f);

                if (events.check (DOWN))
                    ((EschPointLight*)l)->translate (0.0f, -1, 0.0f);

                if (events.check (LEFT))
                    ((EschPointLight*)l)->translate (-1, 0.0f, 0.0f);

                if (events.check (RIGHT))
                    ((EschPointLight*)l)->translate (1, 0.0f, 0.0f);

            }
            doreshade=1;
        }
    }

//��� Handle auto rotatation
    if (scene)
    {
        for(EschGeometry *g=scene->meshes; g != NULL; g = g->next())
        {
            if (toggle_events.check(ALLI))
            {
                g->rotatex(ScriptRotateDegrees);
            }
            if (toggle_events.check(ALLJ))
            {
                g->rotatey(ScriptRotateDegrees);
            }
            if (toggle_events.check(ALLK))
            {
                g->rotatez(ScriptRotateDegrees);
            }
        }
    }

    if (metabox)
    {
        if (toggle_events.check(ALLI))
        {
            metabox->rotatex(ScriptRotateDegrees);
        }
        if (toggle_events.check(ALLJ))
        {
            metabox->rotatey(ScriptRotateDegrees);
        }
        if (toggle_events.check(ALLK))
        {
            metabox->rotatez(ScriptRotateDegrees);
        }
    }

    if (explosion)
    {
        if (toggle_events.check(ALLI))
        {
            explosion->rotatex(ScriptRotateDegrees);
        }
        if (toggle_events.check(ALLJ))
        {
            explosion->rotatey(ScriptRotateDegrees);
        }
        if (toggle_events.check(ALLK))
        {
            explosion->rotatez(ScriptRotateDegrees);
        }
    }

    if (prtgen)
    {
        if (toggle_events.check(ALLI))
        {
            prtgen->rotatex(ScriptRotateDegrees);
        }
        if (toggle_events.check(ALLJ))
        {
            prtgen->rotatey(ScriptRotateDegrees);
        }
        if (toggle_events.check(ALLK))
        {
            prtgen->rotatez(ScriptRotateDegrees);
        }
    }

//��� Do animates and per frame updates
    if (terrain && doreshade)
        terrain->compute_shades(cam, light);

    if (prtgen)
        prtgen->set_interval(interval);
#if 0
    if (prtgen)
    {
        EschPoint cam_pos;
        cam->get_position(&cam_pos);
        cam_pos.y += 50.0f;
        prtgen->set_position (&cam_pos);

        EschVector v(0,0, 1.0f);
        v.transform(&cam->eye.orient);
        v.j=0;
        prtgen->set_init_dir (&v);
    }
#endif
    if (fire)
    {
        if (events.check(FIRE_INCREASE))
            fire->increase();
        else if (events.check(FIRE_DECREASE))
            fire->decrease();

        if (events.check(FIRE_DOUSE))
            fire->douse();

        if (single_events.check(FIRE_FIREBALL))
            fire->fireball();

        fire->animate();
    }

    if (mtxt)
    {
        mtxt->set_interval(interval);
        mtxt->animate();
    }


    // Perform animation of all drawables!
    for(EschDrawable *dptr = draws; dptr != NULL; dptr = dptr->next())
        dptr->animate();
}


//���������������������������������������������������������������������������
// draw_extents
//���������������������������������������������������������������������������
void EscherTest::draw_extents(EschMeshDraw *ptr)
{
    if (!ptr)
        return;

    for(;ptr != NULL; ptr = (EschMeshDraw*)ptr->next())
    {
        if (!(ptr->flags & ESCH_DRW_SKIP))
        {
            if (drawexts & 0x2)
                ptr->mesh->box.draw(&ptr->world,exts_color);
            if (drawexts & 0x1)
                ptr->draw_extents(exts_color);

            if (ptr->child())
                draw_extents((EschMeshDraw*)ptr->child());
        }
    }
}


//���������������������������������������������������������������������������
// EscherTest - Render
//���������������������������������������������������������������������������
void EscherTest::Render()
{
    if (!cam || !draws)
        return;

    char        buff[256];
    GBergText   gt(gvp);

    EschContext ec(EschCurrent);
    ec.camera = cam;
    ec.lights = light;
    ec.eschs = draws;
    ec.push();

    cam->render();

    if (scene)
    {
        if (drawexts)
        {
            draw_extents(scene->meshes);
        }
    }

    if (drawpartn && partn)
    {
        switch (partn->get_type())
        {
            case ESCH_DRWT_PRTN_GRID:
                ((EschGridPartition*)partn)->draw_grid(exts_color);
                break;
            case ESCH_DRWT_PRTN_QUAD:
                ((EschQuadTreePartition*)partn)->draw_quadtree(exts_color);
                break;
            case ESCH_DRWT_PRTN_OCT:
                ((EschOctTreePartition*)partn)->draw_octtree(exts_color);
                break;
        }
    }

    frames++;

    if (show_fps)
    {
        clock_t clk = fps_clock.check();

        sprintf (buff, "FPS:%5.2f\n\n", (float)( (clk)
                                                ? ((float)frames / (float)clk) * 1000.0f
                                                : 0) );
        gt.out (buff);

        sprintf (buff, "Proposed %d tris, %d drawn\n", EschProposedTris,EschDrawnTris);
        gt.out (buff);

        sprintf(buff, "Frames count %d\n", total_frames + frames);
        gt.out(buff);

        sprintf (buff, "FOV: %5.3f\n",float(cam->fov));
        gt.out (buff);


        gt.outc('\n');
        if (cam->flags & ESCH_CAM_SORT)
        {
            gt.out("SORT MODE\n");

            sprintf (buff, "Depth %d\n%d bytes\n",
                           EschSysInstance->sspace_mdepth,
                           EschSysInstance->sspace_mbytes);
            gt.out (buff);

            EschSysInstance->sspace_mdepth=0;
            EschSysInstance->sspace_mbytes=0;
        }
    }

    if (keyframe_animation)
    {
        sprintf (buff, "Animation:\n");
        gt.out (buff);
        sprintf (buff, "   time scale:  %5.0fX\n", scale);
        gt.out (buff);
        if (anim_current_frame == 0)
            sprintf (buff, "   current chain:  WALK\n");
        else if (anim_current_frame == 1)
            sprintf (buff, "   current chain:  RUN\n");
        else if (anim_current_frame == 2)
            sprintf (buff, "   current chain:  CROUCH\n");
        else if (anim_current_frame == 3)
            sprintf (buff, "   current chain:  EXPLOSION DEATH\n");
        else if (anim_current_frame == 4)
            sprintf (buff, "   current chain:  BULLET DEATH\n");
        else if (anim_current_frame == 5)
            sprintf (buff, "   current chain:  KNEEL\n");
        gt.out (buff);

        sprintf (buff, "   frame_num:  %d\n", ((EschKeyframeDraw *)scene->meshes)->get_current_key(anim_current_frame));
        gt.out(buff);

#if 0
        if (GlobalFireTest == ESCH_KEYFRAME_LOOPEND)
        {
            sprintf (buff, "  FIRE!\n");
            gt.out(buff);
        }
        else if (GlobalFireTest > 0)
        {
            sprintf (buff, "   swap_count:  %d", GlobalFireTest);
            gt.out (buff);
        }
#endif
    }

    if (frames > 100)
    {
        total_frames += frames;
        frames=0;
        total_time += fps_clock.check();
        fps_clock.clear();
    }

    if (pick_test)
    {
        //��� Pick Test
        short x, y;
        evt->get_mouse_pos(&x,&y);

        wsprintf(buff,"Mouse: %d, %d\n",(int)x,(int)y);
        gt.out(buff);

        EschPicking pick(cam, x, y, draws, 16U);

        esch_error_codes err;
        err=draws->pick(&pick);
        if (err)
        {
            wsprintf(buff,"Pick returned error %d\n",(int)err);
            gt.out(buff);
        }
        if (pick.count)
        {
            wsprintf(buff,"Picks: %d (of %d max)\n",pick.count,pick.maxcount);
            gt.out(buff);

            if (!pick.result)
                gt.out("Error, no result pointer\n");
            else
            {
                int c=1;
                for(EschDrawList *r = pick.result;
                    r != 0;
                    r = r->next, c++)
                {
                    if (!r->item)
                        wsprintf(buff,"(%d) = No item pointer!\n",c);
                    else if (r->item->partn_data)
                    {
                        assert(partn != 0);
                        switch (partn->get_type())
                        {
                            case ESCH_DRWT_PRTN_QUAD:
                                {
                                    EschQuadTreeNode *node =
                                       (EschQuadTreeNode*)r->item->partn_data;

                                    sprintf(buff,"(%d) = '%s' @ %6.2f (partn depth %d, partn count %d)\n",c,
                                            (r->item->name) ? r->item->name : "NoName",
                                            (float)r->dist, node->depth, node->count);
                                }
                                break;
                            case ESCH_DRWT_PRTN_OCT:
                                {
                                    EschOctTreeNode *node =
                                       (EschOctTreeNode*)r->item->partn_data;

                                    sprintf(buff,"(%d) = '%s' @ %6.2f (partn depth %d, partn count %d)\n",c,
                                            (r->item->name) ? r->item->name : "NoName",
                                            (float)r->dist, node->depth, node->count);
                                }
                                break;
                            default:
                                sprintf(buff,"(%d) = '%s' @ %6.2f\n",c,
                                        (r->item->name) ? r->item->name : "NoName",
                                        (float)r->dist);
                                break;
                        }
                    }
                    else
                    {
                        sprintf(buff,"(%d) = '%s' @ %6.2f\n",c,
                                (r->item->name) ? r->item->name : "NoName",
                                (float)r->dist);
                    }
                    gt.out(buff);
                }
            }
        }
        else
        {
            gt.out("No Picks\n");
        }
    }

    if (collide_test)
    {
        //��� Collision Test
        EschCollision collide(draws, 16);

        EschDrawable *drw = (curmesh) ? curmesh : draws;

        esch_error_codes err;
        err = drw->collide(&collide);
        if (err)
        {
            wsprintf(buff,"Collide returned error %d\n",(int)err);
            gt.out(buff);
        }
        if (collide.count)
        {
            wsprintf(buff,"Collisions:\n"
                        "'%s' hit %d (of %d max)\n",drw->name,
                                                    collide.count,
                                                    collide.maxcount);
            gt.out(buff);

            if (!collide.result)
                gt.out("Error, no result pointer\n");
            else
            {
                int c=1;
                for(EschDrawList *r = collide.result;
                    r != 0;
                    r = r->next, c++)
                {
                    if (!r->item)
                        wsprintf(buff,"(%d) = No item pointer!\n",c);
                    else
                        wsprintf(buff,"(%d) = '%s'\n",c,
                                (r->item->name) ? r->item->name : "NoName");
                    gt.out(buff);
                }
            }
        }
        else
        {
            gt.out("No collides\n");
        }
    }

    ec.pop();
    screen->invalidate();
}


//���������������������������������������������������������������������������
// EscherTest - Display
//���������������������������������������������������������������������������
void EscherTest::Display()
{
#if 1
    screen->flip();
#else
    SetDIBitsToDevice (hdc, 0, 0, MAP_XSIZE, MAP_YSIZE, 0, 0, 0, MAP_YSIZE,
                       gmap, bmi, DIB_PAL_COLORS);
#endif
}


//���������������������������������������������������������������������������
// EscherTest - MessageBox
//���������������������������������������������������������������������������
int EscherTest::MessageBox(LPCSTR lpText, UINT nType)
{
    return ::MessageBox(hWndClient,lpText,szAppName,nType);
}

void EscherTest::update_keys(float interval)
{
    float temp_clock = float (anim_clock.check()) / 1024.0f;
    anim_current_step += interval;
    if (anim_current_step > anim_step_time)
    {
        anim_current_step = 0.0f;
        scale *= 2.0f;
        if (scale > anim_max_compress)
        {
            scale = 1.0f;
            ((EschKeyframeDraw *)curmesh)->set_inactivity(anim_current_frame);
            anim_current_frame ++;
            if (anim_current_frame >= anim_chain_count)
            {
                anim_current_frame = 0;
            }
            ((EschKeyframeDraw *)curmesh)->set_activity(anim_current_frame);
        }
        ((EschKeyframeDraw *)curmesh)->reset_keyframes(anim_current_frame, temp_clock, interval, scale);
        ((EschKeyframeDraw *)curmesh)->reset_ktypes();
    }
    if (terrain)
    {
        float offset= - scene->meshes->mesh->box.mins[1];
        EschKeyframeDraw *step = (EschKeyframeDraw *)scene->meshes->child();
        while (step)
        {
            if (step->get_ktype() & ESCH_KEYFRAME_LEG)
            {
                offset -= step->mesh->box.mins[1];
                step = (EschKeyframeDraw *)step->child();
            }
            else
            {
                step = (EschKeyframeDraw *)step->next();
            }
        }

        float h = terrain->get_height(0,0) + offset;

        scene->meshes->set_position(0,h,0);

    }
}


//���������������������������������������������������������������������������
// EscherTest - Animate
//���������������������������������������������������������������������������
void EscherTest::Animate()
{
    if (scene && scene->meshes)
    {
        if (keyframe_animation)
        {
            Flx16 interval(clock.check()<<6,0);
            long tc = (anim_clock.check());
            float temp_c = float(tc);
            float temp_clock = temp_c / 1024.0f;
            interval *= scale;
            update_keys(interval);
            GlobalFireTest = int(((EschKeyframeDraw *)scene->meshes)->step(interval,1.0,temp_clock,scale));
        }
    }
    if (cam && keyframe_animation)
    {
        EschPoint pnt;
        anim_root->get_position(&pnt);
        cam->set_lookat(&pnt);
    }
}

//��� eof - et.cpp ���

