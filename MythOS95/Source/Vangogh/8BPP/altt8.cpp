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
// zlttr8.cpp
//
//     The flat shaded linearly texture mapped triangle code
//     for the VanGogh Draw library.
//
//����������������������������� Revision History ����������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������
#include <assert.h>
#include <string.h>

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

extern "C" void scan_lsolid_edge(VngoPoint2 *edge,VngoPoint2 *p1, VngoPoint2 *p2);
extern "C" void draw_alhlines(VngoTriangle *tri,long alpha);
extern "C" void vngo_ttriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,VngoTexture3D *tex);

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

extern long AlphaMatrix[4][4];

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//��������������������������������������������������������������������������
//  void vngo_triangle8(VngoVbuffer *vb,VngoPoint2 *pts,dword color)
//      This routine draws a flat shaded triangle, making the assumption
//      that it has already been clipped.
//��������������������������������������������������������������������������

extern "C" void vngo_attriangle8 (VngoVbuffer *vb,VngoPoint2 *pts,
                                   VngoTexture3D *tex,long alpha)
{
    long            mid_y;
    VngoTriangle    tri;
    int             high_pt_idx = 0;
    int             low_pt_idx = 2;
    int             mid_pt_idx = 1;
    VngoPoint2      *edge1 = vb->edge1;
    VngoPoint2      *edge2 = vb->edge2;

    if (alpha < 15)
        return;
    else if (alpha >= (15 << 4))
        vngo_ttriangle8(vb,pts,tex);

    calc_order(high_pt_idx,mid_pt_idx,low_pt_idx,pts);

    VngoPoint2 *high_pt = &pts[high_pt_idx];
    VngoPoint2 *mid_pt = &pts[mid_pt_idx];
    VngoPoint2 *low_pt = &pts[low_pt_idx];

    long    dy1 = ((low_pt->y + 0x8000) >> 16) - ((high_pt->y + 0x8000) >> 16);
    long    dy2 = ((mid_pt->y + 0x8000) >> 16) - ((high_pt->y + 0x8000) >> 16);

    if (dy1 == 0)
    {   // the triangle is completely flat if this is true.
        return;
    }

    tri.start_y = (high_pt->y + 0x8000) >> 16;
    tri.color = pts[0].clr;
    tri.sptr  = vb->scrn_ptr + vb->ytable[tri.start_y];

    scan_lsolid_edge(edge1,high_pt,low_pt);

    scan_lsolid_edge(edge2,high_pt,mid_pt);

    scan_lsolid_edge(&edge2[dy2],mid_pt,low_pt);

    tri.vbuff = vb;
    tri.pitch = vb->pitch;
    tri.height = dy1;

    assert (tex->get_type() == VNGO_MEM_TEX);
    tri.tex = (VngoMemTexture3D*)tex;
    tri.shade = pts[0].shade;

    if (dy1 > dy2)
    {
        mid_y = dy2;
    }
    else
    {
        mid_y = dy2 - 1;
    }
    long mid_dx = ((edge2[mid_y].x + 0x8000) >> 16)
                  - ((edge1[mid_y].x + 0x8000) >> 16);


    mid_dx = ((edge2[mid_y].x + 0x8000) >> 16)
             - ((edge1[mid_y].x + 0x8000) >> 16);


    if (mid_dx >= 0)
    {
        tri.left_edge = edge1;
        tri.right_edge = edge2;
        if (mid_dx)
        {
            tri.ustep_dx1 = ((edge2[mid_y].u - edge1[mid_y].u) / mid_dx) << tri.tex->u_upshift;
            tri.vstep_dx1 = ((edge2[mid_y].v - edge1[mid_y].v) / mid_dx) << tri.tex->v_upshift;
        }
        else
        {
            tri.ustep_dx1 = 0;
            tri.vstep_dx1 = 0;
        }
    }
    else
    {
        tri.left_edge = edge2;
        tri.right_edge = edge1;

        tri.ustep_dx1 = ((edge1[mid_y].u - edge2[mid_y].u) / -mid_dx) << tri.tex->u_upshift;
        tri.vstep_dx1 = ((edge1[mid_y].v - edge2[mid_y].v) / -mid_dx) << tri.tex->v_upshift;
    }
    draw_alhlines(&tri,alpha);
}


extern "C" void draw_alhlines(VngoTriangle *tri,long alpha)
{
    VngoShadePal8   *tp = (VngoShadePal8 *)tri->vbuff->pal->shd_pal;
    VngoColorShade8 *tc = &(*tp)[0];
    byte            *stable = &tc->shl[tri->shade >> 19];

    long            count = tri->height;
    long            pitch = tri->pitch;

    long            ustep_dx1 = tri->ustep_dx1;
    long            vstep_dx1 = tri->vstep_dx1;

    byte            *scrn = (byte*)tri->sptr;
    VngoPoint2      *edge1 = tri->left_edge;
    VngoPoint2      *edge2 = tri->right_edge;
    long            uup = tri->tex->u_upshift;
    long            vup = tri->tex->v_upshift;
    long            udown = tri->tex->u_downshift;
    long            vdown = tri->tex->v_downshift - tri->tex->widthshift;
    long            start_y = tri->start_y;
    byte            *tptr = (byte*)tri->tex->vtxt->tex;
    long            mask = ~((1 << tri->tex->widthshift) - 1);
    byte            clr;

    for (long y=0;y <= count;y++)
    {
        long tz = edge1->z;
        long tu = edge1->u << uup;
        long tv = edge1->v << vup;

        long tx = (edge1->x + 0x8000) >> 16;
        byte *ptr = scrn + tx;
        int dx = ((edge2->x + 0x8000) >> 16);
        long *amatrix = &AlphaMatrix[(start_y+y)&3][0];

        for (int x = tx;x <= dx; x++)
        {
            if ((amatrix[x&3] + alpha) >=255)
            {
                clr = tptr[(((dword)tv >> vdown) & mask)
                            + ((dword)tu >> udown)];

                if (clr != VNGO_TRANSPARENT_COLOR)
                {
                    *ptr = stable[(clr << 5)];
                }
            }
            ptr++;
            tu += ustep_dx1;
            tv += vstep_dx1;
        }
        scrn += pitch;
        edge1++;
        edge2++;
    }
}

//��� End of module - zlttri8.cpp ���