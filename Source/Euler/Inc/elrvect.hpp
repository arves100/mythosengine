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
// elrvect.hpp
//
// Contains the class definitions for the vector data types:
//
//  ElrVector2D is a 2-dimensional vector
//
//  ElrVector2DW is a 2-dimensional vector with a homogeneous w value
//
//  ElrVector3D is a 3-dimensional vector
//
//  ElrVector3DW is a 3-dimensional vector with a homogeneous w value
//
//  ElrVector is a generic n-length vector
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

#ifndef __ELRVECT_HPP
#define __ELRVECT_HPP   1

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
#include "elrpoint.hpp"
#include "elrbasis.hpp"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#define DOT    |
#define CROSS  &

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Classes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrVector2D - 2D ElrBaseVector
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrVector2D
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float   i;
    float   j;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrVector2D() {}
    ElrVector2D(float _i, float _j) : i(_i), j(_j) {}
    ElrVector2D(const ElrPoint2D &p1, const ElrPoint2D &p2) :
        i(p2.x - p1.x), j(p2.y - p1.y) {}

    ~ElrVector2D() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Arithmetic operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Addition/Subtraction
    ElrVector2D operator + (const ElrVector2D &b) const
    {
        return ElrVector2D(i + b.i, j + b.j);
    }
    ElrVector2D operator += (const ElrVector2D &b)
    {
        i = i + b.i;
        j = j + b.j;
        return (*this);
    }

    ElrVector2D operator - (const ElrVector2D &b) const
    {
        return ElrVector2D(i - b.i, j - b.j);
    }
    ElrVector2D operator -= (const ElrVector2D &b)
    {
        i = i - b.i;
        j = j - b.j;
        return (*this);
    }

    //陳� Negation
    ElrVector2D operator - () const
    {
        return ElrVector2D(-i,-j);
    }

    //陳� Addition/Subtraction with a scalar.
    ElrVector2D operator + (const float scalar) const
    {
        return ElrVector2D(i + scalar, j + scalar);
    }
    ElrVector2D operator += (const float scalar)
    {
        i = i + scalar;
        j = j + scalar;
        return (*this);
    }

    ElrVector2D operator - (const float scalar) const
    {
        return ElrVector2D(i - scalar, j - scalar);
    }
    ElrVector2D operator -= (const float scalar)
    {
        i = i - scalar;
        j = j - scalar;
        return (*this);
    }

    //陳� Multiplication/Division by a scalar.
    ElrVector2D operator * (const float scalar) const
    {
        return ElrVector2D(i * scalar, j * scalar);
    }

    ElrVector2D operator *= (const float scalar)
    {
        i = i * scalar;
        j = j * scalar;
        return (*this);
    }

    ElrVector2D operator / (const float scalar) const
    {
        assertMyth("ElrVector2D::operator / needs valid scalar",
                   scalar != 0);

        return ElrVector2D(i / scalar, j / scalar);
    }

    ElrVector2D operator /= (const float scalar)
    {
        assertMyth("ElrVector2D::operator /= needs valid scalar",
                   scalar != 0);

        i = i / scalar;
        j = j / scalar;
        return (*this);
    }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float operator DOT (const ElrVector2D &v) const
    {
        return ((i*v.i) + (j*v.j));
    }

    float magnitude() const { return elr_sqrt((i*i) + (j*j)); }

    void normalize() { ::elr_normalize2d(this); }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Scale vector
    void scale(float scale)
    {
        i = i * scale;
        j = j * scale;
    }
    void scale(float scale, ElrVector2D &result) const
    {
        result.i = i * scale;
        result.j = j * scale;
    }

    //陳� Translate vector
    void translate(float _x, float _y)
    {
        i = i + _x;
        j = j + _y;
    }
    void translate(float _x, float _y, ElrVector2D &result)
    {
        result.i = i + _x;
        result.j = j + _y;
    }

    void translate(const ElrVector2D &v)
    {
        i = i + v.i;
        j = j + v.j;
    }
    void translate(const ElrVector2D &v, ElrVector2D &result)
    {
        result.i = i + v.i;
        result.j = j + v.j;
    }

    //陳� Transform by a matrix
    void transform(const ElrMatrix2D &mtx, ElrVector2DW &result, int hn=0) const
    {
        ::elr_transformv2d(this,&mtx,&result,hn);
    }

    //陳� Rotate
    void rotate(const float degrees)
    {
        // i' = i * c + j * s
        // j' = j * c - i * s

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        float ni = i*cn + j*sn;
        float nj = j*cn - i*sn;

        i = ni;
        j = nj;
    }
    void rotate(const float degrees, ElrVector2D &result) const
    {
        // i' = i * c + j * s
        // j' = j * c - i * s

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        result.i = i*cn + j*sn;
        result.j = j*cn - i*sn;
    }
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrVector2DW - 2D ElrBaseVector with W
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrVector2DW
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float   i;
    float   j;
    float   w;
    dword   na;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrVector2DW() {}
    ElrVector2DW(const ElrVector2D &v) : i(v.i), j(v.j), w(1.0f) {}
    ElrVector2DW(float _i, float _j, float _w=1.0f) : i(_i), j(_j), w(_w) {}
    ElrVector2DW(const ElrPoint2D &p1, const ElrPoint2D &p2) :
        i(p2.x - p1.x), j(p2.y - p1.y), w(1) {}

    ~ElrVector2DW() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    void hnormalize() { ::elr_hnormalize2d(this); }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Transform by a matrix
    void transform(const ElrMatrix2D &mtx, int hn=0)
    {
        ::elr_transformv2dw(this,&mtx,this,hn);
    }
    void transform(const ElrMatrix2D &mtx, ElrVector2DW &result, int hn=0) const
    {
        ::elr_transformv2dw(this,&mtx,&result,hn);
    }
};




//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrVector3D - 3D ElrBaseVector
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrVector3D
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float   i;
    float   j;
    float   k;
    dword   na;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrVector3D() {}
    ElrVector3D(float _i, float _j, float _k) : i(_i), j(_j), k(_k) {}
    ElrVector3D(const ElrPoint3D &p1, const ElrPoint3D &p2) :
        i(p2.x - p1.x), j(p2.y - p1.y), k(p2.z - p1.z) {}



    ~ElrVector3D() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Arithmetic operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Addition/Subtraction
    ElrVector3D operator + (const ElrVector3D &b) const
    {
        return ElrVector3D(i + b.i, j + b.j, k + b.k);
    }
    ElrVector3D operator += (const ElrVector3D &b)
    {
        i = i + b.i;
        j = j + b.j;
        k = k + b.k;
        return (*this);
    }

    ElrVector3D operator - (const ElrVector3D &b) const
    {
        return ElrVector3D(i - b.i, j - b.j, k - b.k);
    }
    ElrVector3D operator -= (const ElrVector3D &b)
    {
        i = i - b.i;
        j = j - b.j;
        k = k - b.k;
        return (*this);
    }

    //陳� Negation
    ElrVector3D operator - () const
    {
        return ElrVector3D(-i,-j,-k);
    }

    //陳� Addition/Subtraction with a scalar.
    ElrVector3D operator + (const float scalar) const
    {
        return ElrVector3D(i + scalar, j + scalar, k + scalar);
    }
    ElrVector3D operator += (const float scalar)
    {
        i = i + scalar;
        j = j + scalar;
        k = k + scalar;
        return (*this);
    }

    ElrVector3D operator - (const float scalar) const
    {
        return ElrVector3D(i - scalar, j - scalar, k - scalar);
    }
    ElrVector3D operator -= (const float scalar)
    {
        i = i - scalar;
        j = j - scalar;
        k = k - scalar;
        return (*this);
    }

    //陳� Multiplication/Division by a scalar.
    ElrVector3D operator * (const float scalar) const
    {
        return ElrVector3D(i * scalar, j * scalar, k * scalar);
    }

    ElrVector3D operator *= (const float scalar)
    {
        i = i * scalar;
        j = j * scalar;
        k = k * scalar;
        return (*this);
    }

    ElrVector3D operator / (const float scalar) const
    {
        assertMyth("ElrVector3D::operator / needs valid scalar",
                   scalar != 0);

        return ElrVector3D(i / scalar, j / scalar, k / scalar);
    }

    ElrVector3D operator /= (const float scalar)
    {
        assertMyth("ElrVector3D::operator /= needs valid scalar",
                   scalar != 0);

        i = i / scalar;
        j = j / scalar;
        k = k / scalar;
        return (*this);
    }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float operator DOT (const ElrVector3D &v) const
    {
        return ((i*v.i) + (j*v.j) + (k*v.k));
    }

    float magnitude() const { return elr_sqrt((i*i) + (j*j) + (k*k)); }

    void normalize() { ::elr_normalize3d(this); }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Scale vector
    void scale(float scale)
    {
        i = i * scale;
        j = j * scale;
        k = k * scale;
    }
    void scale(float scale, ElrVector3D &result) const
    {
        result.i = i * scale;
        result.j = j * scale;
        result.k = k * scale;
    }

    //陳� Translate vector
    void translate(float _x, float _y, float _z)
    {
        i = i + _x;
        j = j + _y;
        k = k + _z;
    }
    void translate(float _x, float _y, float _z, ElrVector3D &result)
    {
        result.i = i + _x;
        result.j = j + _y;
        result.k = k + _z;
    }

    void translate(const ElrVector3D &v)
    {
        i = i + v.i;
        j = j + v.j;
        k = k + v.k;
    }
    void translate(const ElrVector3D &v, ElrVector3D &result)
    {
        result.i = i + v.i;
        result.j = j + v.j;
        result.k = k + v.k;
    }

    //陳� Transform by a matrix
    void transform(const ElrMatrix3D &mtx, ElrVector3DW &result, int hn=0) const
    {
        ::elr_transformv3d(this,&mtx,&result,hn);
    }

    //陳� Rotate
    void rotatex(const float degrees)
    {
        // i' = i
        // j' = j * c + k * s
        // k' = k * c - j * s

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        float nj = j*cn + k*sn;
        float nk = k*cn - j*sn;

        j = nj;
        k = nk;
    }
    void rotatex(const float degrees, ElrVector3D &result) const
    {
        // i' = i
        // j' = j * c + k * s
        // k' = k * c - j * s

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        result.i = i;
        result.j = j*cn + k*sn;
        result.k = k*cn - j*sn;
    }

    void rotatey(const float degrees)
    {
        // i' = i * c - k * s
        // j' = j
        // k' = i * s + k * c

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        float ni = i*cn - k*sn;
        float nk = i*sn + k*cn;

        i = ni;
        k = nk;
    }
    void rotatey(const float degrees, ElrVector3D &result) const
    {
        // i' = i * c - k * s
        // j' = j
        // k' = i * s + k * c

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        result.i = i*cn - k*sn;
        result.j = j;
        result.k = i*sn + k*cn;
    }

    void rotatez(const float degrees)
    {
        // i' = i * c + j * s
        // j' = j * c - i * s
        // k' = k

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        float ni = i*cn + j*sn;
        float nj = j*cn - i*sn;

        i = ni;
        j = nj;
    }
    void rotatez(const float degrees, ElrVector3D &result) const
    {
        // i' = i * c + j * s
        // j' = j * c - i * s
        // k' = k

        float sn = elr_sin(degrees);
        float cn = elr_cos(degrees);

        result.i = i*cn + j*sn;
        result.j = j*cn - i*sn;
        result.k = k;
    }
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrVector3DW - 3D ElrBaseVector with W
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrVector3DW
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    float   i;
    float   j;
    float   k;
    float   w;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrVector3DW() {}
    ElrVector3DW(const ElrVector3D &v) : i(v.i), j(v.j), k(v.k), w(1.0f) {}
    ElrVector3DW(float _i, float _j, float _k, float _w=1.0f) :
        i(_i), j(_j), k(_k), w(_w) {}
    ElrVector3DW(const ElrPoint3D &p1, const ElrPoint3D &p2) :
        i(p2.x - p1.x), j(p2.y - p1.y), k(p2.z - p1.z), w(1) {}

    ~ElrVector3DW() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    void hnormalize() { ::elr_hnormalize3d(this); }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Transform by a matrix
    void transform(const ElrMatrix3D &mtx, int hn=0)
    {
        ::elr_transformv3dw(this,&mtx,this,hn);
    }
    void transform(const ElrMatrix3D &mtx, ElrVector3DW &result, int hn=0) const
    {
        ::elr_transformv3dw(this,&mtx,&result,hn);
    }
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrVector - Generic vector
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�


//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                 Inlines
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint2D - operator +
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
inline ElrPoint2D ElrPoint2D::operator + (const ElrVector2D &v) const
{
    return ElrPoint2D(x + v.i, y + v.j);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint2D - operator +=
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
inline ElrPoint2D ElrPoint2D::operator += (const ElrVector2D &v)
{
    x = x + v.i;
    y = y + v.j;
    return (*this);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint2D - operator -
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
inline ElrPoint2D ElrPoint2D::operator - (const ElrVector2D &v) const
{
    return ElrPoint2D(x - v.i, y - v.j);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint2D - operator -=
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
inline ElrPoint2D ElrPoint2D::operator -= (const ElrVector2D &v)
{
    x = x - v.i;
    y = y - v.j;
    return (*this);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint3D - operator +
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
inline ElrPoint3D ElrPoint3D::operator + (const ElrVector3D &v) const
{
    return ElrPoint3D(x + v.i, y + v.j, z + v.k);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint3D - operator +=
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
inline ElrPoint3D ElrPoint3D::operator += (const ElrVector3D &v)
{
    x = x + v.i;
    y = y + v.j;
    z = z + v.k;
    return (*this);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint3D - operator -
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
inline ElrPoint3D ElrPoint3D::operator - (const ElrVector3D &v) const
{
    return ElrPoint3D(x - v.i, y - v.j, z - v.k);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// ElrPoint3D - operator -=
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
inline ElrPoint3D ElrPoint3D::operator -= (const ElrVector3D &v)
{
    x = x - v.i;
    y = y - v.j;
    z = z - v.k;
    return (*this);
}

#ifdef __WATCOMC__
#pragma pack();
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//葦� End of header - elrvect.hpp 憶�
