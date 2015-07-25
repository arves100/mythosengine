//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//                                                           %__________%
//                                                          %/ . .  .   \%
//           Van Gogh 2D-Display Library                     |  . .  o. |
//                                                           |. _  .   .|
//          Microsoft Windows '95 Version                    | / \   .  |
//                                                           |_|_|_._._.|
// Copyright (c) 1994-1997 by Charybdis Enterprises, Inc.    |.-.-.-.-..|
//              All rights reserved.                        %\__________/%
//                                                           %          %
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
//           *** Charybdis Enterprises, Inc. Company Confidential ***
//
//  This file and all associated files are the company proprietary property
//        of Charybdis Enterprises, Inc.  Unauthorized use prohibited.
//
// CHARYBDIS ENTERPRISES, INC. MAKES NO WARRANTIES, EXPRESS OR IMPLIED, AS
// TO THE CORRECTNESS OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE
// IT.  CHARYBDIS ENTERPRISES, INC. PROVIDES THE CODE ON AN "AS-IS" BASIS
// AND EXPLICITLY DISCLAIMS ANY LIABILITY, INCLUDING CONSEQUENTIAL AND
// INCIDENTAL DAMAGES FOR ERRORS, OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
// vngptri.cpp
//
//     The C++ perspective texture mapper for the VanGogh Draw library.
//
//様様様様様様様様様様様様様様� Revision History 様様様様様様様様様様様様様様
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
#include <assert.h>

#include "debug.h"
#include "portable.h"
#include "vangogh.hpp"

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
extern "C" void vngo_ttriangle16_persp (VngoVbuffer *vb,VngoPoint2 *pts,
                                       VngoTexture3D *ttex);
extern "C" void vngo_attriangle16_persp (VngoVbuffer *vb,VngoPoint2 *pts,
                                        VngoTexture3D *ttex,long alpha);
extern "C" void vngo_zttriangle16_persp (VngoVbuffer *vb,VngoPoint2 *pts,
                                        VngoTexture3D *ttex);
extern "C" void vngo_azttriangle16_persp (VngoVbuffer *vb,VngoPoint2 *pts,
                                         VngoTexture3D *ttex,long alpha);
extern "C" void vngo_tgtriangle16_persp (VngoVbuffer *vb,VngoPoint2 *pts,
                                        VngoTexture3D *ttex);
extern "C" void vngo_atgtriangle16_persp (VngoVbuffer *vb,VngoPoint2 *pts,
                                         VngoTexture3D *ttex,long alpha);
extern "C" void vngo_ztgtriangle16_persp (VngoVbuffer *vb,VngoPoint2 *pts,
                                         VngoTexture3D *ttex);
extern "C" void vngo_aztgtriangle16_persp (VngoVbuffer *vb,VngoPoint2 *pts,
                                          VngoTexture3D *ttex,long alpha);


//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�


//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�



//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  vngo_tpoly_persp (VngoVbuffer *vb, int count, VngoPoint2 *pts,          �
//              VngoTexture *tex);                                          �
//      Draws an N sided convex polygon, by breaking it down into triangles �
//      if it is not already a triangle.  This will also degenerate lines   �
//      and pixels appropriately.  It draws with Gouraud shading.           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void vngo_tpoly_persp16 (VngoVport *vp,int count,VngoPoint2 *pts,
                        VngoTexture3D *tex)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            VngoPoint2 tpts[3];

            tpts[0].x     = pts[0].x;
            tpts[0].y     = pts[0].y;
            tpts[0].z     = pts[0].z;
            tpts[0].u     = pts[0].u;
            tpts[0].v     = pts[0].v;
            tpts[0].w     = pts[0].w;
            tpts[0].shade = pts[0].shade;
            for (int i=1;i < count-1;i++)
            {
                tpts[1].x     = pts[i].x;
                tpts[1].y     = pts[i].y;
                tpts[1].z     = pts[i].z;
                tpts[1].u     = pts[i].u;
                tpts[1].v     = pts[i].v;
                tpts[1].w     = pts[i].w;
                tpts[1].shade = pts[i].shade;

                tpts[2].x     = pts[i+1].x;
                tpts[2].y     = pts[i+1].y;
                tpts[2].z     = pts[i+1].z;
                tpts[2].u     = pts[i+1].u;
                tpts[2].v     = pts[i+1].v;
                tpts[2].w     = pts[i+1].w;
                tpts[2].shade = pts[i+1].shade;

                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_zttriangle16_persp (&vp->vbuff,tpts,tex);
                else
                    vngo_ttriangle16_persp (&vp->vbuff,tpts,tex);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_zttriangle16_persp (&vp->vbuff,pts,tex);
        else
            vngo_ttriangle16_persp (&vp->vbuff,pts,tex);
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  vngo_tpoly_persp (VngoVbuffer *vb, int count, VngoPoint2 *pts,          �
//              VngoTexture *tex);                                          �
//      Draws an N sided convex polygon, by breaking it down into triangles �
//      if it is not already a triangle.  This will also degenerate lines   �
//      and pixels appropriately.  It draws with Gouraud shading.           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void vngo_atpoly_persp16 (VngoVport *vp,int count,VngoPoint2 *pts,
                         VngoTexture3D *tex,long alpha)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            VngoPoint2 tpts[3];

            tpts[0].x     = pts[0].x;
            tpts[0].y     = pts[0].y;
            tpts[0].z     = pts[0].z;
            tpts[0].u     = pts[0].u;
            tpts[0].v     = pts[0].v;
            tpts[0].w     = pts[0].w;
            tpts[0].shade = pts[0].shade;
            for (int i=1;i < count-1;i++)
            {
                tpts[1].x     = pts[i].x;
                tpts[1].y     = pts[i].y;
                tpts[1].z     = pts[i].z;
                tpts[1].u     = pts[i].u;
                tpts[1].v     = pts[i].v;
                tpts[1].w     = pts[i].w;
                tpts[1].shade = pts[i].shade;

                tpts[2].x     = pts[i+1].x;
                tpts[2].y     = pts[i+1].y;
                tpts[2].z     = pts[i+1].z;
                tpts[2].u     = pts[i+1].u;
                tpts[2].v     = pts[i+1].v;
                tpts[2].w     = pts[i+1].w;
                tpts[2].shade = pts[i+1].shade;
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_azttriangle16_persp (&vp->vbuff,tpts,tex,alpha);
                else
                    vngo_attriangle16_persp (&vp->vbuff,tpts,tex,alpha);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_azttriangle16_persp (&vp->vbuff,pts,tex,alpha);
        else
            vngo_attriangle16_persp (&vp->vbuff,pts,tex,alpha);
    }
}

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  vngo_tgpoly_persp (VngoVbuffer *vb, int count, VngoPoint2 *pts,         �
//              VngoTexture *tex);                                          �
//      Draws an N sided convex polygon, by breaking it down into triangles �
//      if it is not already a triangle.  This will also degenerate lines   �
//      and pixels appropriately.  It draws with Gouraud shading.           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void vngo_tgpoly_persp16 (VngoVport *vp,int count,VngoPoint2 *pts,
                         VngoTexture3D *tex)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            VngoPoint2 tpts[3];

            tpts[0].x = pts[0].x;
            tpts[0].y = pts[0].y;
            tpts[0].z = pts[0].z;
            tpts[0].u = pts[0].u;
            tpts[0].v = pts[0].v;
            tpts[0].w = pts[0].w;
            tpts[0].shade = pts[0].shade;

            for (int i=1;i < count-1;i++)
            {
                tpts[1].x     = pts[i].x;
                tpts[1].y     = pts[i].y;
                tpts[1].z     = pts[i].z;
                tpts[1].u     = pts[i].u;
                tpts[1].v     = pts[i].v;
                tpts[1].w     = pts[i].w;
                tpts[1].shade = pts[i].shade;

                tpts[2].x     = pts[i+1].x;
                tpts[2].y     = pts[i+1].y;
                tpts[2].z     = pts[i+1].z;
                tpts[2].u     = pts[i+1].u;
                tpts[2].v     = pts[i+1].v;
                tpts[2].w     = pts[i+1].w;
                tpts[2].shade = pts[i+1].shade;
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_ztgtriangle16_persp (&vp->vbuff,tpts,tex);
                else
                    vngo_tgtriangle16_persp (&vp->vbuff,tpts,tex);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_ztgtriangle16_persp (&vp->vbuff,pts,tex);
        else
            vngo_tgtriangle16_persp (&vp->vbuff,pts,tex);
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  vngo_tgpoly_persp (VngoVbuffer *vb, int count, VngoPoint2 *pts,         �
//              VngoTexture *tex);                                          �
//      Draws an N sided convex polygon, by breaking it down into triangles �
//      if it is not already a triangle.  This will also degenerate lines   �
//      and pixels appropriately.  It draws with Gouraud shading.           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void vngo_atgpoly_persp16 (VngoVport *vp,int count,VngoPoint2 *pts,
                          VngoTexture3D *tex,long alpha)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            VngoPoint2 tpts[3];

            tpts[0].x = pts[0].x;
            tpts[0].y = pts[0].y;
            tpts[0].z = pts[0].z;
            tpts[0].u = pts[0].u;
            tpts[0].v = pts[0].v;
            tpts[0].w = pts[0].w;
            tpts[0].shade = pts[0].shade;

            for (int i=1;i < count-1;i++)
            {
                tpts[1].x     = pts[i].x;
                tpts[1].y     = pts[i].y;
                tpts[1].z     = pts[i].z;
                tpts[1].u     = pts[i].u;
                tpts[1].v     = pts[i].v;
                tpts[1].w     = pts[i].w;
                tpts[1].shade = pts[i].shade;

                tpts[2].x     = pts[i+1].x;
                tpts[2].y     = pts[i+1].y;
                tpts[2].z     = pts[i+1].z;
                tpts[2].u     = pts[i+1].u;
                tpts[2].v     = pts[i+1].v;
                tpts[2].w     = pts[i+1].w;
                tpts[2].shade = pts[i+1].shade;
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_aztgtriangle16_persp (&vp->vbuff,tpts,tex,alpha);
                else
                    vngo_atgtriangle16_persp (&vp->vbuff,tpts,tex,alpha);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_aztgtriangle16_persp (&vp->vbuff,pts,tex,alpha);
        else
            vngo_atgtriangle16_persp (&vp->vbuff,pts,tex,alpha);
    }
}




//葦� End of module - vngtri.cpp 憶�
