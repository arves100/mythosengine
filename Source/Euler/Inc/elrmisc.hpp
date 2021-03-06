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
// elrmisc.hpp
//
// Contains the class definitions of misc. data types and classes:
//
//  ElrPlane is a 3-dimensional plane defined by a vector and a distance
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

#ifndef __ELRMISC_HPP
#define __ELRMISC_HPP   1

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
// ElrPlane - 3D plane defined by a vector and distance
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class ElrPlane
{
public:
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Public data members
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrVector3D normal;
    float       dist;

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Contructors/Destructors
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    ElrPlane() {}
    ElrPlane(float _a, float _b, float _c, float _d) :
        normal(_a,_b,_c), dist(_d) {}
    ElrPlane(ElrVector3D &_n, float _d) :
        normal(_n), dist(_d) {}

    ~ElrPlane() {}

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    void normalize()
    {
        float mag = normal.magnitude();

        if (mag > 0.0001f)
        {
            normal.i /= mag;
            normal.j /= mag;
            normal.k /= mag;
            dist /= mag;
        }
    }

    void nearest(const ElrPoint3D &p, ElrPoint3D &result) const
    {
        float d = (normal DOT *((const ElrVector3D*)&p)) + dist;
        result.x = p.x - (d * normal.i);
        result.y = p.y - (d * normal.j);
        result.z = p.z - (d * normal.k);
    }

    float distance(const ElrPoint3D &p) const
    {
        return (normal DOT *((const ElrVector3D*)&p)) + dist;
    }

    void project(ElrVector3D &v, ElrVector3D result) const
    {
        float dot = normal DOT v;

        result.i = v.i - (dot * normal.i);
        result.j = v.j - (dot * normal.j);
        result.k = v.k - (dot * normal.k);
    }

    float ray(const ElrPoint3D &p, const ElrVector3D &v) const
    {
        float dot = normal DOT v;
        if (dot <= 0.0f)
            return 0.0f;

        float t = - ((dist + (normal DOT *((const ElrVector3D*)&p))) / dot);

        if (t <= 0.0f)
            return 0.0f;

        return t;
    }

    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    // Transformation operations
    //陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

    //陳� Transform by a matrix
    void transform(const ElrMatrix3D &imtx, int hn=0);
    void transform(const ElrMatrix3D &imtx, ElrPlane &result, int hn=0) const;
};

#ifdef __WATCOMC__
#pragma pack();
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//葦� End of header - elrmisc.hpp 憶�
