//���������������������������������������������������������������������������
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
// Created by Tim Little
//
// vngttri8.cpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������
#include <assert.h>

#include "debug.h"
#include "portable.h"
#include "vangogh.hpp"

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
//                               Routines
//
//���������������������������������������������������������������������������

extern "C" void vngo_ttriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,
                                 VngoTexture3D *tex);
extern "C" void vngo_zttriangle8 (VngoVbuffer *vbb,VngoPoint2 *pts,
                                  VngoTexture3D *tex);
extern "C" void vngo_tgtriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,
                                   VngoTexture3D *tex);
extern "C" void vngo_ztgtriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,
                                   VngoTexture3D *tex);
extern "C" void vngo_aztgtriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,
                                    VngoTexture3D *tex,long alpha);
extern "C" void vngo_azttriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,
                                   VngoTexture3D *tex, long alpha);
extern "C" void vngo_attriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,
                                  VngoTexture3D *tex,long alpha);
extern "C" void vngo_atgtriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,
                                    VngoTexture3D *tex,long alpha);

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������


//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������


//���������������������������������������������������������������������������
//  vngo_tpoly(VngoVport *vb, int count, VngoPoint2 *pts,
//              VngoTexture3D *tex);
//      Draws an N sided convex polygon, by breaking it down into triangles
//      if it is not already a triangle.  It draws with flat shading, and
//      texture mapping.
//���������������������������������������������������������������������������
void vngo_tpoly8 (VngoVport *vp,int count,VngoPoint2 *pts, VngoTexture3D *tex)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            for (int i=1;i < count-1;i++)
            {
                VngoPoint2 tpts[3];
                tpts[0] = pts[0];
                tpts[1] = pts[i];
                tpts[2] = pts[i+1];
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_zttriangle8 (&vp->vbuff,tpts,tex);
                else
                    vngo_ttriangle8 (&vp->vbuff,tpts,tex);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_zttriangle8 (&vp->vbuff,pts,tex);
        else
            vngo_ttriangle8 (&vp->vbuff,pts,tex);
    }
}


//���������������������������������������������������������������������������
//  vngo_tpoly(VngoVport *vb, int count, VngoPoint2 *pts,
//              VngoTexture3D *tex);
//      Draws an N sided convex polygon, by breaking it down into triangles
//      if it is not already a triangle.  It draws with flat shading, and
//      texture mapping.
//���������������������������������������������������������������������������
void vngo_atpoly8 (VngoVport *vp,int count,VngoPoint2 *pts,
                   VngoTexture3D *tex, long alpha)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            for (int i=1;i < count-1;i++)
            {
                VngoPoint2 tpts[3];
                tpts[0] = pts[0];
                tpts[1] = pts[i];
                tpts[2] = pts[i+1];
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_azttriangle8 (&vp->vbuff,tpts,tex,alpha);
                else
                    vngo_attriangle8 (&vp->vbuff,tpts,tex,alpha);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_azttriangle8 (&vp->vbuff,pts,tex,alpha);
        else
            vngo_attriangle8 (&vp->vbuff,pts,tex,alpha);
    }
}


//���������������������������������������������������������������������������
//  vngo_tgpoly(VngoVport *vp, int count, VngoPoint2 *pts,
//              VngoTexture3D *tex);
//      Draws an N sided convex polygon, by breaking it down into triangles
//      if it is not already a triangle.  It draws with Gouraud shading and
//      texture mapping.
//���������������������������������������������������������������������������
void vngo_tgpoly8 (VngoVport *vp,int count,VngoPoint2 *pts, VngoTexture3D *tex)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            for (int i=1;i < count-1;i++)
            {
                VngoPoint2 tpts[3];
                tpts[0] = pts[0];
                tpts[1] = pts[i];
                tpts[2] = pts[i+1];
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_ztgtriangle8 (&vp->vbuff,tpts,tex);
                else
                    vngo_tgtriangle8 (&vp->vbuff,tpts,tex);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_ztgtriangle8 (&vp->vbuff,pts,tex);
        else
            vngo_tgtriangle8 (&vp->vbuff,pts,tex);
    }
}


//���������������������������������������������������������������������������
//  vngo_tgpoly(VngoVport *vp, int count, VngoPoint2 *pts,
//              VngoTexture3D *tex);
//      Draws an N sided convex polygon, by breaking it down into triangles
//      if it is not already a triangle.  It draws with Gouraud shading and
//      texture mapping.
//���������������������������������������������������������������������������
void vngo_atgpoly8 (VngoVport *vp,int count,VngoPoint2 *pts,
                    VngoTexture3D *tex, long alpha)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            for (int i=1;i < count-1;i++)
            {
                VngoPoint2 tpts[3];
                tpts[0] = pts[0];
                tpts[1] = pts[i];
                tpts[2] = pts[i+1];
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_aztgtriangle8 (&vp->vbuff,tpts,tex,alpha);
                else
                    vngo_atgtriangle8 (&vp->vbuff,tpts,tex,alpha);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_aztgtriangle8 (&vp->vbuff,pts,tex,alpha);
        else
            vngo_atgtriangle8 (&vp->vbuff,pts,tex,alpha);
    }
}







//��� End of module - vngttri.cpp ���
