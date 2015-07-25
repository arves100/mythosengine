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
// vngtri8.cpp
//
//     The 8bpp specific polygon scan conversion code for VanGogh.
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
extern "C" void vngo_gtriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color);
extern "C" void vngo_zgtriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color);
extern "C" void vngo_agtriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color,long alpha);
extern "C" void vngo_azgtriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color,long alpha);
extern "C" void vngo_tagtriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color,long alpha);
extern "C" void vngo_tazgtriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color,long alpha);

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
//  vngo_gpoly(VngoVbuffer *vb, int count, VngoPoint2 *pts);                �
//      Draws an N sided convex polygon, by breaking it down into triangles �
//      if it is not already a triangle.  It draws with Gouraud shading.    �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void vngo_gpoly16 (VngoVport *vp,int count,VngoPoint2 *pts)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            VngoPoint2 tpts[3];
            tpts[0] = pts[0];
            for (int i=1;i < count-1;i++)
            {
                tpts[1] = pts[i];
                tpts[2] = pts[i+1];
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    vngo_zgtriangle16 (&vp->vbuff,tpts,pts[0].clr);
                else
                    vngo_gtriangle16 (&vp->vbuff,tpts,pts[0].clr);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_zgtriangle16 (&vp->vbuff,pts,pts[0].clr);
        else
            vngo_gtriangle16 (&vp->vbuff,pts,pts[0].clr);
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//  vngo_gpoly(VngoVbuffer *vb, int count, VngoPoint2 *pts);                �
//      Draws an N sided convex polygon, by breaking it down into triangles �
//      if it is not already a triangle.  It draws with Gouraud shading.    �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void vngo_agpoly16 (VngoVport *vp,int count,VngoPoint2 *pts,long alpha)
{
    if (count != 3)
    {
        if (count > 3)
        {
            // if there are more than three vertices, break it into a series
            // of triangles.
            VngoPoint2 tpts[3];
            tpts[0] = pts[0];
            for (int i=1;i < count-1;i++)
            {
                tpts[1] = pts[i];
                tpts[2] = pts[i+1];
                if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
                    if (vp->vflags & VNGO_TRUE_ALPHA)
                        vngo_tazgtriangle16 (&vp->vbuff,tpts,pts[0].clr,alpha);
                    else
                        vngo_azgtriangle16 (&vp->vbuff,tpts,pts[0].clr,alpha);
                else
                    if (vp->vflags & VNGO_TRUE_ALPHA)
                        vngo_tagtriangle16 (&vp->vbuff,tpts,pts[0].clr,alpha);
                    else
                        vngo_agtriangle16 (&vp->vbuff,tpts,pts[0].clr,alpha);
            }
        }
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            if (vp->vflags & VNGO_TRUE_ALPHA)
                vngo_tazgtriangle16 (&vp->vbuff,pts,pts[0].clr,alpha);
            else
                vngo_azgtriangle16 (&vp->vbuff,pts,pts[0].clr,alpha);
        else
            if (vp->vflags & VNGO_TRUE_ALPHA)
                vngo_tagtriangle16 (&vp->vbuff,pts,pts[0].clr,alpha);
            else
                vngo_agtriangle16 (&vp->vbuff,pts,pts[0].clr,alpha);
    }
}

//葦� End of module - vngtri8.cpp 憶�
