//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
// _________________________________________________________________________
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
// |       1       2       3       4       5       6       7       8       9
// |                                                                       |
// |              E U L E R:   Math and Computation Library                |
// |_______________________________________________________________________|
//
//                      Microsoft Windows 95/NT Version
//
//               Copyright (c) 1998 by Charybdis Enterprises, Inc.
//                           All Rights Reserved.
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
// INCIDENTAL DAMAGES FOR ERRORS, OMISSIONS, AND OTHER PbROBLEMS IN THE CODE.
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
// Created by Chuck Walbourn
//
// elrpoint.hpp
//
// Contains the class definitions for the point data types:
//
//  ElrPoint2D is a 2-dimensional point
//
//  ElrPoint2DW is a 2-dimensional point with a homogeneous w value
//
//  ElrPoint3D is a 3-dimensional point
//
//  ElrPoint3DW is a 3-dimensional point with a homogeneous w value
//
//  ElrPoint is a generic n-dimensional piont
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

#ifndef __ELRPOINT_HPP
#define __ELRPOINT_HPP   1

#ifdef __WATCOMC__
#pragma pack(1);
#endif

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "elrmath.hpp"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Classes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint2D - 2D Point
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrPoint2D
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float   x;
    float   y;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrPoint2D() {}
    ElrPoint2D(float _x, float _y) : x(_x), y(_y) {}

    ~ElrPoint2D() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Arithmetic operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Addition/Subtraction
    ElrPoint2D operator + (const ElrVector2D &v) const;
        // see elrvect.hpp
    ElrPoint2D operator + (const ElrPoint2D &b) const
    {
        return ElrPoint2D(x + b.x, y + b.y);
    }

    ElrPoint2D operator += (const ElrVector2D &v);
        // see elrvect.hpp
    ElrPoint2D operator += (const ElrPoint2D &b)
    {
        x = x + b.x;
        y = y + b.y;
        return (*this);
    }

    ElrPoint2D operator - (const ElrVector2D &v) const;
        // see elrvect.hpp
    ElrPoint2D operator - (const ElrPoint2D &b) const
    {
        return ElrPoint2D(x - b.x, y - b.y);
    }

    ElrPoint2D operator -= (const ElrVector2D &v);
        // see elrvect.hpp
    ElrPoint2D operator -= (const ElrPoint2D &b)
    {
        x = x - b.x;
        y = y - b.y;
        return (*this);
    }

    //陳� Negation
    ElrPoint2D operator - () const
    {
        return ElrPoint2D(-x,-y);
    }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float distance(const ElrPoint2D &p) const;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Transform by a matrix
    void transform(const ElrMatrix2D &mtx, ElrPoint2DW &result, int hn=0) const
    {
        ::elr_transform2d(this,&mtx,&result,hn);
    }

    //陳� Rotate
    void rotate(const float degrees)
    {
        // x' = x * c + y * s
        // y' = y * c - x * s

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        float nx = x*cn + y*sn;
        float ny = y*cn - x*sn;

        x = nx;
        y = ny;
    }
    void rotate(const float degrees, ElrPoint2D &result) const
    {
        // x' = x * c + y * s
        // y' = y * c - x * s

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        result.x = x*cn + y*sn;
        result.y = y*cn - x*sn;
    }
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint2DW - 2D Point with W
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrPoint2DW
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float   x;
    float   y;
    float   w;
    dword   na;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrPoint2DW() {}
    ElrPoint2DW(const ElrPoint2DW &p) : x(p.x), y(p.y), w(1.0f) {}
    ElrPoint2DW(float _x, float _y, float _w=1.0f) : x(_x), y(_y), w(_w) {}

    ~ElrPoint2DW() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Transform by a matrix
    void transform(const ElrMatrix2D &mtx, int hn=0)
    {
        ::elr_transform2dw(this,&mtx,this,hn);
    }
    void transform(const ElrMatrix2D &mtx, ElrPoint2DW &result, int hn=0) const
    {
        ::elr_transform2dw(this,&mtx,&result,hn);
    }
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint3D - 3D Point
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrPoint3D
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float   x;
    float   y;
    float   z;
    dword   na;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrPoint3D() {}
    ElrPoint3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    ~ElrPoint3D() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Arithmetic operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Addition/Subtraction
    ElrPoint3D operator + (const ElrVector3D &v) const;
        // see elrvect.hpp
    ElrPoint3D operator + (const ElrPoint3D &b) const
    {
        return ElrPoint3D(x + b.x, y + b.y, z + b.z);
    }

    ElrPoint3D operator += (const ElrVector3D &v);
        // see elrvect.hpp
    ElrPoint3D operator += (const ElrPoint3D &b)
    {
        x = x + b.x;
        y = y + b.y;
        z = z + b.z;
        return (*this);
    }

    ElrPoint3D operator - (const ElrVector3D &v) const;
        // see elrvect.hpp
    ElrPoint3D operator - (const ElrPoint3D &b) const
    {
        return ElrPoint3D(x - b.x, y - b.y, z - b.z);
    }

    ElrPoint3D operator -= (const ElrVector3D &v);
        // see elrvect.hpp
    ElrPoint3D operator -= (const ElrPoint3D &b)
    {
        x = x - b.x;
        y = y - b.y;
        z = z - b.z;
        return (*this);
    }

    //陳� Negation
    ElrPoint3D operator - () const
    {
        return ElrPoint3D(-x,-y,-z);
    }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float distance(const ElrPoint3D &p) const;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Transform by a matrix
    void transform(const ElrMatrix3D &mtx, ElrPoint3DW &result, int hn=0) const
    {
        ::elr_transform3d(this,&mtx,&result,hn);
    }

    //陳� Rotate
    void rotatex(const float degrees)
    {
        // x' = x
        // y' = y * c + z * s
        // z' = z * c - y * s

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        float ny = y*cn + z*sn;
        float nz = z*cn - y*sn;

        y = ny;
        z = nz;
    }
    void rotatex(const float degrees, ElrPoint3D &result) const
    {
        // x' = x
        // y' = y * c + z * s
        // z' = z * c - y * s

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        result.x = x;
        result.y = y*cn + z*sn;
        result.z = z*cn - y*sn;
    }

    void rotatey(const float degrees)
    {
        // x' = x * c - z * s
        // y' = y
        // z' = x * s + z * c

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        float nx = x*cn - z*sn;
        float nz = x*sn + z*cn;

        x = nx;
        z = nz;
    }
    void rotatey(const float degrees, ElrPoint3D &result) const
    {
        // x' = x * c - z * s
        // y' = y
        // z' = x * s + z * c

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        result.x = x*cn - z*sn;
        result.y = y;
        result.z = x*sn + z*cn;
    }

    void rotatez(const float degrees)
    {
        // x' = x * c + y * s
        // y' = y * c - x * s
        // z' = z

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        float nx = x*cn + y*sn;
        float ny = y*cn - x*sn;

        x = nx;
        y = ny;
    }
    void rotatez(const float degrees, ElrPoint3D &result) const
    {
        // x' = x * c + y * s
        // y' = y * c - x * s
        // z' = z

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        result.x = x*cn + y*sn;
        result.y = y*cn - x*sn;
        result.z = z;
    }
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint3DW - 3D Point with W
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrPoint3DW
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float   x;
    float   y;
    float   z;
    float   w;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrPoint3DW() {}
    ElrPoint3DW(const ElrPoint3DW &p) : x(p.x), y(p.y), z(p.z), w(1.0f) {}
    ElrPoint3DW(float _x, float _y, float _z, float _w=1.0f) :
        x(_x), y(_y), z(_z), w(_w) {}

    ~ElrPoint3DW() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Transform by a matrix
    void transform(const ElrMatrix3D &mtx, int hn=0)
    {
        ::elr_transform3dw(this,&mtx,this,hn);
    }
    void transform(const ElrMatrix3D &mtx, ElrPoint3DW &result, int hn=0) const
    {
        ::elr_transform3dw(this,&mtx,&result,hn);
    }
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint - Generic Point
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

#ifdef __WATCOMC__
#pragma pack();
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//葦� End of header - elrpoint.hpp 憶�
