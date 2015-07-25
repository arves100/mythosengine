//���������������������������������������������������������������������������
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
//���������������������������������������������������������������������������
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
//���������������������������������������������������������������������������
//
// vngtri.cpp
//
//     The Flat/Solid colored polygon code for the VanGogh Draw library.
//
//����������������������������� Revision History ����������������������������
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

extern "C" void vngo_triangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color);
extern "C" void vngo_ztriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color);
extern "C" void vngo_atriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color,long alpha);
extern "C" void vngo_aztriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color,long alpha);
extern "C" void vngo_tatriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color,long alpha);
extern "C" void vngo_taztriangle16 (VngoVbuffer *vb,VngoPoint2 *pts,dword color,long alpha);

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
//  vngo_poly8(VngoVport *vp, int count, VngoPoint2 *pts);
//      Draws an N sided convex polygon, by breaking it down into triangles
//      if it is not already a triangle.  It draws in a solid color.
//���������������������������������������������������������������������������
void vngo_poly16 (VngoVport *vp,int count,VngoPoint2 *pts)
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
                    vngo_ztriangle16 (&vp->vbuff,tpts,pts[0].clr);
                else
                    vngo_triangle16 (&vp->vbuff,tpts,pts[0].clr);
            }
        }
        //
        // It would be nice to do some pixel and line degeneration here.
        //
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            vngo_ztriangle16 (&vp->vbuff,pts,pts[0].clr);
        else
            vngo_triangle16 (&vp->vbuff,pts,pts[0].clr);
    }
}


void vngo_apoly16 (VngoVport *vp,int count,VngoPoint2 *pts, long alpha)
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
                    if (vp->vflags & VNGO_TRUE_ALPHA)
                        vngo_taztriangle16 (&vp->vbuff,tpts,pts[0].clr,alpha);
                    else
                        vngo_aztriangle16 (&vp->vbuff,tpts,pts[0].clr,alpha);
                else
                    if (vp->vflags & VNGO_TRUE_ALPHA)
                        vngo_tatriangle16 (&vp->vbuff,tpts,pts[0].clr,alpha);
                    else
                        vngo_atriangle16 (&vp->vbuff,tpts,pts[0].clr,alpha);
            }
        }
        //
        // It would be nice to do some pixel and line degeneration here.
        //
    }
    else
    {
        if (vp->vflags & VNGO_ZBUFFER_ACTIVE)
            if (vp->vflags & VNGO_TRUE_ALPHA)
                vngo_taztriangle16 (&vp->vbuff,pts,pts[0].clr,alpha);
            else
                vngo_aztriangle16 (&vp->vbuff,pts,pts[0].clr,alpha);
        else
            if (vp->vflags & VNGO_TRUE_ALPHA)
                vngo_tatriangle16 (&vp->vbuff,pts,pts[0].clr,alpha);
            else
                vngo_atriangle16 (&vp->vbuff,pts,pts[0].clr,alpha);
    }
}




//��� End of module - vngtri.cpp ���