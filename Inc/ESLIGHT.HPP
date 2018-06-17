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
// Created by Tim Little & Chuck Walbourn
//
// eslight.hpp
//
// EschLight and the other associated light classes are container classes
// for the various light sources in the environment.  Lists of
// light objects are maintained and used by the other objects to
// perform shading calculations.
//
// The EschLight class defines the light interface and implementes basic
// ambient lighting.
//
// EschVectorLights are vector light sources with a direction, but no
// originating point.  They are the fastest non-ambient light sources
// available.
//
// EschFastPointLights are approximations of point light sources which
// form a vector light with each object.  They require more setup than
// vector lights.
//
// EschFastAttenLights are approximated point light sources with
// intensity attenuation.  They are inherited from EschFastPointLights.
//
// EschFastSpotLight are approixmated point light sources with
// a directed output.  They inherit the properties of the EschFastAttenLight.
//
// EschPointLights are point light sources with a position in world
// space.  They are much slower to use than vector lights since they
// require vector normalization on each vertex/face.
//
// EschAttenLight are point light sources which support intensity
// attenuation, which adds a small overhead to point lights.  They are
// inherited from EschPointLight.
//
// EschSpotLight direct their output wihtin a one defined by a hotspot
// angle and a fall-off angle.  They inherit the attenuation properties
// of the EschAttenLight.
//
//���������������������������������������������������������������������������

#ifndef __ESLIGHT_HPP
#define __ESLIGHT_HPP    1

#ifdef __WATCOMC__
#pragma pack(1);
#endif

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include <portable.h>
#include <felix.hpp>
#include <vangogh.hpp>
#include <xfile.hpp>

#include "esmath.hpp"

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// EschLight - Base object for light (Used for ambient light).              �
//���������������������������������������������������������������������������
class EschLight {

protected:
    //���������������������������������������������������������������������Ŀ
    // Protected data members                                               �
    //�����������������������������������������������������������������������
    EschLight   *inext;
    EschLight   *iprev;
    float       _intensity;                 // Normal intensity
    float       _hintensity;                // Highlight intensity

    long        mp;                         // Palette-midpoint

    word        ltyp;                       // Run-time type

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    byte        intensity;                  // Intensity setting
    byte        na;
    dword       flags;                      // Light flags
    char        name[ESCH_MAX_NAME];        // Light name
    void        *app_data;                  // Application data pointer

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    EschLight(const char *fname=0, const char *lname=0);
    EschLight(const EschLight &l);

    virtual ~EschLight();

    //���������������������������������������������������������������������Ŀ
    // Accessor functions                                                   �
    //�����������������������������������������������������������������������
    word get_type() const { return ltyp; }

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    const EschLight &operator = (const EschLight &l);

    virtual void sibling(EschLight *myprev);
    virtual void remove();

    EschLight *next() const { return inext; }
    EschLight *prev() const { return iprev; }

    virtual EschLight *find(const char *lname) const;

    virtual void setup(const EschFrameRef *fr);
    virtual void shine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;
    virtual void hishine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;

    //���������������������������������������������������������������������Ŀ
    // Utility functions                                                    �
    //�����������������������������������������������������������������������
    byte get_intensity() const { return (byte)intensity; }
    void set_intensity(const byte i) { intensity = i; }

    void set_flags(const dword f) { flags = f; }
    void set_flags(const dword m, const int on)
    {
        if (on)
            flags |= m;
        else
            flags &= ~m;
    }

    void set_app_data(void *p) { app_data = p; }

    //���������������������������������������������������������������������Ŀ
    // I/O routines.                                                        �
    //�����������������������������������������������������������������������
    virtual esch_error_codes load(const char *fname, const char *lname=0);
    virtual esch_error_codes load(XFParseIFF *iff, const char *lname=0);
};


//�������������������������������������������������������������������������Ŀ
// EschVectorLight - Directional light source.                              �
//���������������������������������������������������������������������������
class EschVectorLight : public EschLight {

protected:
    //���������������������������������������������������������������������Ŀ
    // Protected data members                                               �
    //�����������������������������������������������������������������������
    EschVector  tdir;                       // Setup direction vector

public:
    //���������������������������������������������������������������������Ŀ
    // Public data member                                                   �
    //�����������������������������������������������������������������������
    EschVector  dir;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    EschVectorLight(const char *fname=0, const char *lname=0);
    EschVectorLight(const EschVector *vec);
    EschVectorLight(float ix, float iy, float iz);

    virtual ~EschVectorLight() {};

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void setup(const EschFrameRef *fr);
    virtual void shine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;
    virtual void hishine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;

    //���������������������������������������������������������������������Ŀ
    // Utility routines.                                                    �
    //�����������������������������������������������������������������������
    void set_direction(const EschVector *d)
    {
        dir = *d;
        dir.normalize();
    }
    void set_direction(float ii, float ij, float ik)
    {
        dir.i = ii;
        dir.j = ij;
        dir.k = ik;
        dir.normalize();
    }

    void rotatex(const float degrees)
    {
        dir.rotatex(degrees);
        dir.normalize();
    }
    void rotatey(const float degrees)
    {
        dir.rotatey(degrees);
        dir.normalize();
    }
    void rotatez(const float degrees)
    {
        dir.rotatez(degrees);
        dir.normalize();
    }

    //���������������������������������������������������������������������Ŀ
    // I/O routines.                                                        �
    //�����������������������������������������������������������������������
    virtual esch_error_codes load(const char *fname, const char *lname=0);
    virtual esch_error_codes load(XFParseIFF *iff, const char *lname=0);
};


//�������������������������������������������������������������������������Ŀ
// EschFastPointLight - Single point light source approximation.            �
//���������������������������������������������������������������������������
class EschFastPointLight : public EschLight {

protected:
    //���������������������������������������������������������������������Ŀ
    // Protected data members                                               �
    //�����������������������������������������������������������������������
    EschVector  tdir;                       // Setup direction vector

public:
    //���������������������������������������������������������������������Ŀ
    // Public data member                                                   �
    //�����������������������������������������������������������������������
    EschPoint   pos;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    EschFastPointLight(const char *fname=0, const char *lname=0);
    EschFastPointLight(const EschPoint *pnt);
    EschFastPointLight(float ix, float iy, float iz);

    virtual ~EschFastPointLight() {};

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void setup(const EschFrameRef *fr);
    virtual void shine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;
    virtual void hishine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;

    //���������������������������������������������������������������������Ŀ
    // Utility routines.                                                    �
    //�����������������������������������������������������������������������
    void set_position(const EschPoint *pnt)
    {
        pos = *pnt;
    }
    void set_position(float ix, float iy, float iz)
    {
        pos.x = ix;
        pos.y = iy;
        pos.z = iz;
    }

    void translate(float tx, float ty, float tz)
    {
        pos.x = pos.x + tx;
        pos.y = pos.y + ty;
        pos.z = pos.z + tz;
    }
    void translate(const EschVector *v)
    {
        pos.x = pos.x + v->i;
        pos.y = pos.y + v->j;
        pos.z = pos.z + v->k;
    }

    //���������������������������������������������������������������������Ŀ
    // I/O routines.                                                        �
    //�����������������������������������������������������������������������
    virtual esch_error_codes load(const char *fname, const char *lname=0);
    virtual esch_error_codes load(XFParseIFF *iff, const char *lname=0);
};


//�������������������������������������������������������������������������Ŀ
// EschFastAttenLight - Approx. point light source with attenuated output   �
//���������������������������������������������������������������������������
class EschFastAttenLight : public EschFastPointLight {

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    float       inner;
    float       outer;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    EschFastAttenLight(const char *fname=0, const char *lname=0);
    EschFastAttenLight(const EschPoint *pnt, float i, float o);
    EschFastAttenLight(float ix, float iy, float iz, float i, float o);

    virtual ~EschFastAttenLight() {};

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void setup(const EschFrameRef *fr);

    //���������������������������������������������������������������������Ŀ
    // Utility routines.                                                    �
    //�����������������������������������������������������������������������
    void set_inner(float i) { inner=i; }
    void set_outer(float o) { outer=o; }

    //���������������������������������������������������������������������Ŀ
    // I/O routines.                                                        �
    //�����������������������������������������������������������������������
    virtual esch_error_codes load(const char *fname, const char *lname=0);
    virtual esch_error_codes load(XFParseIFF *iff, const char *lname=0);
};


//�������������������������������������������������������������������������Ŀ
// EschFastSpotLight - Approx. directional point light source               �
//���������������������������������������������������������������������������
class EschFastSpotLight : public EschFastAttenLight {

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    EschVector  dir;
    float       hotspot;
    float       falloff;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    EschFastSpotLight(const char *fname=0, const char *lname=0);
    EschFastSpotLight(const EschPoint *pnt,
                      const EschVector *d,
                      float h, float f, float i=0, float o=0x1000);
    EschFastSpotLight(float ix, float iy, float iz,
                      float ii, float ij, float ik,
                      float h, float f, float i=0, float o=0x1000);

    virtual ~EschFastSpotLight() {};

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void setup(const EschFrameRef *fr);

    //���������������������������������������������������������������������Ŀ
    // Utility routines.                                                    �
    //�����������������������������������������������������������������������
    void set_direction(const EschVector *d)
    {
        dir = *d;
        dir.normalize();
    }
    void set_direction(float ii, float ij, float ik)
    {
        dir.i = ii;
        dir.j = ij;
        dir.k = ik;
        dir.normalize();
    }

    void rotatex(const float degrees)
    {
        dir.rotatex(degrees);
        dir.normalize();
    }
    void rotatey(const float degrees)
    {
        dir.rotatey(degrees);
        dir.normalize();
    }
    void rotatez(const float degrees)
    {
        dir.rotatez(degrees);
        dir.normalize();
    }

    void set_hotspot(float degrees) { hotspot=degrees; }
    void set_falloff(float degrees) { falloff=degrees; }

    //���������������������������������������������������������������������Ŀ
    // I/O routines.                                                        �
    //�����������������������������������������������������������������������
    virtual esch_error_codes load(const char *fname, const char *lname=0);
    virtual esch_error_codes load(XFParseIFF *iff, const char *lname=0);
};


//�������������������������������������������������������������������������Ŀ
// EschPointLight - Single point light source.                              �
//���������������������������������������������������������������������������
class EschPointLight : public EschLight {

protected:
    //���������������������������������������������������������������������Ŀ
    // Protected data members                                               �
    //�����������������������������������������������������������������������
    EschPoint   tpos;                       // Setup light position

public:
    //���������������������������������������������������������������������Ŀ
    // Public data member                                                   �
    //�����������������������������������������������������������������������
    EschPoint   pos;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    EschPointLight(const char *fname=0, const char *lname=0);
    EschPointLight(const EschPoint *pnt);
    EschPointLight(float ix, float iy, float iz);

    virtual ~EschPointLight() {};

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void setup(const EschFrameRef *fr);
    virtual void shine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;
    virtual void hishine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;

    //���������������������������������������������������������������������Ŀ
    // Utility routines.                                                    �
    //�����������������������������������������������������������������������
    void set_position(const EschPoint *pnt)
    {
        pos = *pnt;
    }
    void set_position(float ix, float iy, float iz)
    {
        pos.x = ix;
        pos.y = iy;
        pos.z = iz;
    }

    void translate(float tx, float ty, float tz)
    {
        pos.x = pos.x + tx;
        pos.y = pos.y + ty;
        pos.z = pos.z + tz;
    }
    void translate(const EschVector *v)
    {
        pos.x = pos.x + v->i;
        pos.y = pos.y + v->j;
        pos.z = pos.z + v->k;
    }

    //���������������������������������������������������������������������Ŀ
    // I/O routines.                                                        �
    //�����������������������������������������������������������������������
    virtual esch_error_codes load(const char *fname, const char *lname=0);
    virtual esch_error_codes load(XFParseIFF *iff, const char *lname=0);
};


//�������������������������������������������������������������������������Ŀ
// EschAttenLight - Point light source with attenuated output.              �
//���������������������������������������������������������������������������
class EschAttenLight : public EschPointLight {

protected:
    //���������������������������������������������������������������������Ŀ
    // Protected data members                                               �
    //�����������������������������������������������������������������������
    float       tinner;                     // Setup data
    float       touter;
    float       arate;
    float       harate;

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    float       inner;
    float       outer;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    EschAttenLight(const char *fname=0, const char *lname=0);
    EschAttenLight(const EschPoint *pnt, float i, float o);
    EschAttenLight(float ix, float iy, float iz, float i, float o);

    virtual ~EschAttenLight() {};

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void setup(const EschFrameRef *fr);
    virtual void shine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;
    virtual void hishine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;

    //���������������������������������������������������������������������Ŀ
    // Utility routines.                                                    �
    //�����������������������������������������������������������������������
    void set_inner(float i) { inner=i; }
    void set_outer(float o) { outer=o; }

    //���������������������������������������������������������������������Ŀ
    // I/O routines.                                                        �
    //�����������������������������������������������������������������������
    virtual esch_error_codes load(const char *fname, const char *lname=0);
    virtual esch_error_codes load(XFParseIFF *iff, const char *lname=0);
};


//�������������������������������������������������������������������������Ŀ
// EschSpotLight - Directional point light source                           �
//���������������������������������������������������������������������������
class EschSpotLight : public EschAttenLight {

protected:
    //���������������������������������������������������������������������Ŀ
    // Protected data members                                               �
    //�����������������������������������������������������������������������
    EschVector  tdir;                       // Setup data
    float       hotcos;
    float       fallcos;
    float       frate;
    float       hfrate;

public:
    //���������������������������������������������������������������������Ŀ
    // Public data members                                                  �
    //�����������������������������������������������������������������������
    EschVector  dir;
    float       hotspot;
    float       falloff;

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    EschSpotLight(const char *fname=0, const char *lname=0);
    EschSpotLight(const EschPoint *pnt,
                  const EschVector *d,
                  float h, float f, float i=0, float o=0x1000);
    EschSpotLight(float ix, float iy, float iz,
                  float ii, float ij, float ik,
                  float h, float f, float i=0, float o=0x1000);

    virtual ~EschSpotLight() {};

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    virtual void setup(const EschFrameRef *fr);
    virtual void shine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;
    virtual void hishine(const EschVertex *v, VngoPoint *vpt, int revnrml=0) const;

    //���������������������������������������������������������������������Ŀ
    // Utility routines.                                                    �
    //�����������������������������������������������������������������������
    void set_direction(const EschVector *d)
    {
        dir = *d;
        dir.normalize();
    }
    void set_direction(float ii, float ij, float ik)
    {
        dir.i = ii;
        dir.j = ij;
        dir.k = ik;
        dir.normalize();
    }

    void rotatex(const float degrees)
    {
        dir.rotatex(degrees);
        dir.normalize();
    }
    void rotatey(const float degrees)
    {
        dir.rotatey(degrees);
        dir.normalize();
    }
    void rotatez(const float degrees)
    {
        dir.rotatez(degrees);
        dir.normalize();
    }

    void set_hotspot(float degrees) { hotspot=degrees; }
    void set_falloff(float degrees) { falloff=degrees; }

    //���������������������������������������������������������������������Ŀ
    // I/O routines.                                                        �
    //�����������������������������������������������������������������������
    virtual esch_error_codes load(const char *fname, const char *lname=0);
    virtual esch_error_codes load(XFParseIFF *iff, const char *lname=0);
};

#ifdef __WATCOMC__
#pragma pack();
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//��� End of header - eslight.hpp ���
