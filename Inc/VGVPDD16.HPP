//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//                                                           %__________%
//                                                          %/ . .  .   \%
//           Van Gogh 2D-Display Library                     |  . .  o. |
//                                                           |. _  .   .|
//        Microsoft Windows 95/98/NT Version                 | / \   .  |
//                                                           |_|_|_._._.|
//                                                           |.-.-.-.-..|
//                                                          %\__________/%
//                                                           %          %
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
// Created by Tim Little
//
// vgvpdd16.hpp
//
// Contains the 15/16-bit DirectDraw surface viewport class definition
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

#ifndef __VNGVPDD16_HPP
#define __VNGVPDD16_HPP

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <ddraw.h>

#include "vngvvp16.hpp"

#ifdef __WATCOMC__
#pragma pack(1);
#endif

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Classes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

class VngoVportDD16 : public VngoVVport16
{
    dword                   vp_offset;
    dword                   zp_offset;
    VngoRect                vp_rect;
    DDSURFACEDESC           ddsd;
    DDSURFACEDESC           zddsd;
    IDirectDrawSurface      *pddsurf;
    IDirectDrawSurface      *zddsurf;
    VngoSurfaceManager      *surf_stat;

public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Constructor/Destructors                                              �
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    VngoVportDD16 () {};
    VngoVportDD16 (VngoSurfaceManager *_pddsurf, VngoSurfaceManager *zbptr,
                  VngoPal *my_pal,dword flags);
    VngoVportDD16 (VngoSurfaceManager *_pddsurf, VngoSurfaceManager *zbptr,
                  VngoRect &srect, VngoPal *my_pal, dword flags);

    virtual ~VngoVportDD16();

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Operations                                                           �
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    VNGError init (VngoSurfaceManager *_pddsurf, VngoSurfaceManager *zbptr,
                   VngoPal *my_pal,dword flags);

    VNGError init (VngoSurfaceManager *_pddsurf, VngoSurfaceManager *zbptr,
                   VngoRect &srect, VngoPal *my_pal,dword flags);

    virtual VNGError capture(XFBitmap *bm)
    {
        VNGError err = VNGO_INTERNAL_ERROR;
        int was_locked = lock();
        if(was_locked != -1)
        {
            err = VngoVport::capture(bm);
            if (!was_locked)
                unlock();
        }
        return err;
    }

    virtual int lock();
    virtual int unlock();

    //陳� Basic drawing functions
    virtual void reset(dword c=0,dword farz=0xffffffff);

    //陳� Rectangle drawing functions
    virtual VNGError frect (VngoRect *rect, dword color);
    virtual VNGError frect (VngoRect *rect, VngoColor24bit *rgb_val);
    virtual VNGError clip_frect (VngoRect *rect, dword color, VngoRect *clip=NULL);
    virtual VNGError clip_frect (VngoRect *rect, VngoColor24bit *rgb_val, VngoRect *clip=NULL);

    //陳� Pixel drawing functions
    virtual VNGError pixel (VngoPoint *pt, VngoColor24bit *rgb_val = NULL);
    virtual VNGError pixel (VngoPointF *pt, VngoColor24bit *rgb_val = NULL);
    virtual VNGError clip_pixel (VngoPoint *pt, VngoColor24bit *rgb_val = NULL,
                                 VngoRect *clip_rect=NULL);
    virtual VNGError clip_pixel (VngoPointF *pt, VngoColor24bit *rgb_val = NULL,
                                 VngoRect *clip_rect=NULL);
    virtual dword read_pixel (VngoPoint *pt, VngoPoint *dest);
    virtual dword read_pixel (int x, int y, VngoPoint *dest);

    //陳� Image transfer functions
    virtual VNGError image_trans (VngoRect *dest_rect,VngoTexture *img,
                                  dword flags=0);
    virtual VNGError image_trans_a (VngoRect *dest_rect,VngoTexture *img,
                                    long alpha=127, dword flags=0)
        { return VNGO_NOT_SUPPORTED; }

    virtual VNGError image_trans_mono (VngoRect *dest_rect,VngoTexture *img,
                                       dword fgcol,dword bgcol=VNGO_TRANSPARENT);
    virtual VNGError zblit_mono (VngoRect *dest_rect,VngoZMap *zmp,
                                 dword fdist,dword ndist=0);

    //陳� Line drawing functions
    virtual VNGError line (VngoPoint *p1, VngoPoint *p2,
                           VngoColor24bit *rgb_val=NULL);
    virtual VNGError line (VngoPointF *p1, VngoPointF *p2,
                           VngoColor24bit *rgb_val=NULL);
    virtual VNGError gline (VngoPoint *p1, VngoPoint *p2);
    virtual VNGError gline (VngoPointF *p1, VngoPointF *p2);
    virtual VNGError gline_persp (VngoPoint *p1, VngoPoint *p2) {return VNGO_NOT_SUPPORTED;};
    virtual VNGError gline_persp (VngoPointF *p1, VngoPointF *p2){return VNGO_NOT_SUPPORTED;};
    virtual VNGError clip_line (VngoPoint *p1, VngoPoint *p2,
                                VngoColor24bit *rgb_val=NULL,
                                VngoRect *clip_rect=NULL);
    virtual VNGError clip_line (VngoPointF *p1, VngoPointF *p2,
                                VngoColor24bit *rgb_val=NULL,
                                VngoRect *clip_rect=NULL);
    virtual VNGError clip_gline (VngoPoint *p1, VngoPoint *p2,
                                 VngoRect *clip_rect=NULL);
    virtual VNGError clip_gline (VngoPointF *p1, VngoPointF *p2,
                                 VngoRect *clip_rect=NULL);
    virtual VNGError clip_gline_persp (VngoPoint *p1, VngoPoint *p2,
                                       VngoRect *clip_rect=NULL){return VNGO_NOT_SUPPORTED;};
    virtual VNGError clip_gline_persp (VngoPointF *p1, VngoPointF *p2,
                                       VngoRect *clip_rect=NULL){return VNGO_NOT_SUPPORTED;};

    //陳� Polygon drawing functions
    virtual VNGError poly (int count, VngoPoint pts[]);
    virtual VNGError poly (int count, VngoPointF pts[]);
    virtual VNGError gpoly (int count, VngoPoint pts[]);
    virtual VNGError gpoly (int count, VngoPointF pts[]);
    virtual VNGError gpoly_persp (int count, VngoPoint pts[]);
    virtual VNGError gpoly_persp (int count, VngoPointF pts[]);
    virtual VNGError tpoly (int count, VngoPoint pts[],VngoTexture *tex);
    virtual VNGError tpoly (int count, VngoPointF pts[],VngoTexture *tex);
    virtual VNGError tpoly_persp (int count, VngoPoint pts[],VngoTexture *tex);
    virtual VNGError tpoly_persp (int count, VngoPointF pts[],VngoTexture *tex);
    virtual VNGError gtpoly (int count, VngoPoint pts[],VngoTexture *tex);
    virtual VNGError gtpoly (int count, VngoPointF pts[],VngoTexture *tex);
    virtual VNGError gtpoly_persp (int count, VngoPoint pts[],VngoTexture *tex);
    virtual VNGError gtpoly_persp (int count, VngoPointF pts[],VngoTexture *tex);
    virtual VNGError grpoly (int count,VngoPoint pts[]);
    virtual VNGError grpoly (int count,VngoPointF pts[]);

    //陳� Alpha-blended polygon drawing functions
    virtual VNGError poly_a (int count, VngoPoint pts[],long alpha=127);
    virtual VNGError poly_a (int count, VngoPointF pts[],long alpha=127);
    virtual VNGError gpoly_a (int count, VngoPoint pts[],long alpha=127);
    virtual VNGError gpoly_a (int count, VngoPointF pts[],long alpha=127);
    virtual VNGError gpoly_persp_a (int count, VngoPoint pts[],long alpha=127);
    virtual VNGError gpoly_persp_a (int count, VngoPointF pts[],long alpha=127);
    virtual VNGError tpoly_a (int count, VngoPoint pts[],VngoTexture *tex,
                              long alpha=127);
    virtual VNGError tpoly_a (int count, VngoPointF pts[],VngoTexture *tex,
                              long alpha=127);
    virtual VNGError tpoly_persp_a (int count, VngoPoint pts[],
                                    VngoTexture *tex,long alpha=127);
    virtual VNGError tpoly_persp_a (int count, VngoPointF pts[],
                                    VngoTexture *tex,long alpha=127);
    virtual VNGError gtpoly_a (int count, VngoPoint pts[],VngoTexture *tex,
                               long alpha=127);
    virtual VNGError gtpoly_a (int count, VngoPointF pts[],VngoTexture *tex,
                               long alpha=127);
    virtual VNGError gtpoly_persp_a (int count, VngoPoint pts[],
                                     VngoTexture *tex,long alpha=127);
    virtual VNGError gtpoly_persp_a (int count, VngoPointF pts[],
                                     VngoTexture *tex,long alpha=127);

    //陳� Fogging/hazing functions
    virtual VNGError haze()
    {
        VNGError    err = VNGO_INTERNAL_ERROR;
        int was_locked = lock();
        if(was_locked != -1)
        {
            err = VngoVVport16::haze();
            if (!was_locked)
                unlock();
        }
        return err;
    }
};

#ifdef __WATCOMC__
#pragma pack();
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif  // __VNGVPDD16_HPP

//葦� End of header - vgvpdd16.hpp 憶�
