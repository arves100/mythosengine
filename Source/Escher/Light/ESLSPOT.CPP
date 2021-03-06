//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//���������������������������������������������������������������������������
//����������旭旭旭旭旭�旭旭旭旭���旭旭旭旭��旭姻���旭姻旭旭旭旭旭�旭旭旭旭姻�
//���������葦姻������葦姻���葦姻葦姻���葦姻葦姻���葦姻葦姻�������葦姻���葦姻�
//��������碓甥������碓甥�������碓甥�������碓甥���碓甥碓甥�������碓甥���碓甥��
//�������渦臼葦渦��渦臼葦渦臼�渦甥�������渦臼葦渦臼�渦臼葦渦���渦臼葦渦姻����
//������渦甥�������������渦甥渦甥�������渦甥���渦甥渦甥�������渦甥���渦甥����
//�����憶悔������憶悔���憶悔憶悔���憶悔憶悔���憶悔憶悔�������憶悔���憶悔�����
//����臆臆臆臆臆�臆臆臆臆���臆臆臆臆��臆悔���臆悔臆臆臆臆臆�臆悔���臆悔������
//���������������������������������������������������������������������������
//����������������� Microsoft Windows 95/98/NT Version ����������������������
//���������������������������������������������������������������������������
//���Copyright (c) 1994-1999 by Dan Higdon, Tim Little, and Chuck Walbourn���
//���������������������������������������������������������������������������
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
// Created by Tim Little & Chuck Walbourn
//
// eslspot.cpp
//
// The EschLight and associated classes are used for implementing the
// lighting model.  EschLights affect objects by controlling the
// shade level and potentially color of a vertex.  EschLight objects
// are maintained in a linked list.
//
// An EschSpotLight shines in a given direction from a location in 3-space,
// with the intensity dropping off towords the edge of the cone defined
// for the spot.  It also supports distance attenuation.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "escher.hpp"
#include "esfile.hpp"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#define max(a,b)  (((a) > (b)) ? (a) : (b))

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭�  Constructors/Destructors  碓旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschSpotLight - Constructor                                              �
//                                                                          �
// Initializes the light object with full intesity and sets type.           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
EschSpotLight::EschSpotLight(const char *fname, const char *lname) :
    EschAttenLight(),
    dir(0,0,1),
    hotspot(44),
    falloff(45)
{
    ltyp = ESCH_LGTT_SPOT;

    if (fname)
    {
        load(fname,lname);
    }
};

EschSpotLight::EschSpotLight(const EschPoint *pnt,
                             const EschVector *d,
                             float h, float f, float i, float o) :
    EschAttenLight(pnt,i,o),
    dir(*d),
    hotspot(h),
    falloff(f)
{
    ltyp = ESCH_LGTT_SPOT;

    dir.normalize();
};

EschSpotLight::EschSpotLight(float ix, float iy, float iz,
                             float ii, float ij, float ik,
                             float h, float f, float i, float o) :
    EschAttenLight(ix,iy,iz,i,o),
    dir(ii,ij,ik),
    hotspot(h),
    falloff(f)
{
    ltyp = ESCH_LGTT_SPOT;

    dir.normalize();
};



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschSpotLight - setup                                                    �
//                                                                          �
// Performs the setup of the light on an object by object basis.            �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void EschSpotLight::setup(const EschFrameRef *fr)
{
    if (fr
        && EschCurrent
        && EschCurrent->camera
        && EschCurrent->camera->flags & ESCH_CAM_MODELSPACE)
    {
        pos.transform(&fr->iorient,&tpos);
        dir.transform(&fr->iorient,&tdir);
        tdir = -tdir;

        tinner = inner / fr->scalef;
        touter = outer / fr->scalef;
    }
    else
    {
        tpos = pos;
        tdir = -dir;

        tinner = inner;
        touter = outer;
    }
    if (tinner > touter)
        tinner = touter;

    EschLight::setup(fr);

    arate=harate=0;
    if ((outer-inner) > 0)
    {
        arate = _intensity / (outer - inner);
        harate = _hintensity / (outer - inner);
    }

    hotcos = esch_cos(hotspot);
    fallcos = esch_cos(falloff);

    frate=hfrate=0;
    if ((hotcos-fallcos) > 0)
    {
        frate = _intensity / (hotcos-fallcos);
        hfrate = _hintensity / (hotcos-fallcos);
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschSpotLight - shine                                                    �
//                                                                          �
// Sets the shade level in the Van Gogh point based on the intesity of the  �
// light and the given vertex information.                                  �
//                                                                          �
// The point light source computes a direction vector relative to the       �
// vertex and then computes a dot product.  The distance and angle away from�
// the spot's direction is used to attenuate the intensity.                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void EschSpotLight::shine(const EschVertex *v, VngoPoint *vpt, int revnrml) const
{
    if (!(flags & ESCH_LGT_OFF))
    {
        // Compute point source lighting vector
        EschVector vtx(tpos.x - v->x,
                       tpos.y - v->y,
                       tpos.z - v->z);

        float mag = vtx.magnitude();

        // Check for point beyond outer range before
        // continuing
        if (mag < outer)
        {
            // Complete normalization
            if (mag > 0)
            {
                vtx.i /= mag;
                vtx.j /= mag;
                vtx.k /= mag;
            }

            // Use dot product with light to determine fall-off
            float dotcone = vtx DOT tdir;

            // Check to see if we are inside fall-off cone
            if (dotcone > fallcos)
            {
                // Compute dot product
                float dot = v->normal DOT vtx;

                if (dot < 0)
                {
                    dot = (revnrml) ? -dot : 0;
                }

                // Compute intensity output (including attenuation)
                float inten = _intensity;

                if (dotcone < hotcos)
                {
                    inten -= (hotcos - dotcone) * frate;
                }

                if ((flags & ESCH_LGT_ATTEN) && (mag > inner))
                {
                    inten -= (mag - inner) * arate;
                }

                // Compute shade value
                vpt->shade += long(dot * inten);
            }
        }
    }

//陳� Chain for true multiple lights
    if (inext)
    {
        inext->shine(v,vpt,revnrml);
    }
//陳� Clamp shade value
    else
    {
        if (vpt->shade > mp)
            vpt->shade = mp;
        else if (vpt->shade < 0)
            vpt->shade = 0;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschSpotLight - hishine                                                  �
//                                                                          �
// Sets the shade level, allowing specular highlights to overdrive the      �
// color based on the intensity of the light and the given vertex info.     �
//                                                                          �
// The point light source computes a direction vector relative to the       �
// vertex and then computes a dot product.  The distance and angle away from�
// the spot's direction is used to attenuate the intensity.                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void EschSpotLight::hishine(const EschVertex *v, VngoPoint *vpt, int revnrml) const
{
    if (!(flags & ESCH_LGT_OFF))
    {
        // Compute point source lighting vector
        EschVector vtx(tpos.x - v->x,
                       tpos.y - v->y,
                       tpos.z - v->z);

        float mag = vtx.magnitude();

        // Check for point beyond outer range before
        // continuing
        if (mag < outer)
        {
            // Complete normalization
            if (mag > 0)
            {
                vtx.i /= mag;
                vtx.j /= mag;
                vtx.k /= mag;
            }

            // Use dot product with light to determine fall-off
            float dotcone = vtx DOT tdir;

            // Check to see if we are inside fall-off cone
            if (dotcone > fallcos)
            {
                // Compute dot product
                float dot = v->normal DOT vtx;

                if (dot < 0)
                {
                    dot = (revnrml) ? -dot : 0;
                }

                // Compute intensity output (including attenuation)
                float inten = _hintensity;

                if (dotcone < hotcos)
                {
                    inten -= (hotcos - dotcone) * hfrate;
                }

                if ((flags & ESCH_LGT_ATTEN) && (mag > inner))
                {
                    inten -= (mag - inner) * harate;
                }

                // Compute shade value
                vpt->shade += long(dot * inten);
            }
        }
    }

//陳� Chain for true multiple lights
    if (inext)
    {
        inext->hishine(v,vpt,revnrml);
    }
//陳� Clamp shade value
    else
    {
        if (vpt->shade > VNGO_SHADE_FULL)
            vpt->shade = VNGO_SHADE_FULL;
        else if (vpt->shade < 0)
            vpt->shade = 0;
    }
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  I/O Routines  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschSpotLight - load                                                     �
//                                                                          �
// Loads the position and other data of the attenuated light from an IFF    �
// file.                                                                    �
//                                                                          �
// The IFF version assumes that the IFF is open and pointing at the proper  �
// chunk.  If a 'lname' is given and the name doesn't match that in the     �
// chunk, an error is returned.                                             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
esch_error_codes EschSpotLight::load(const char *fname, const char *lname)
{
    esch_error_codes    err;
    XFParseIFF          iff;

//陳 Open file
    if (iff.open(fname,XF_OPEN_READ | XF_OPEN_DENYWRITE))
        return ESCH_ERR_FILEERROR;

//陳 Loop until a header with the correct name is found
    err=ESCH_ERR_NONE;

    for(;;)
    {
        if (iff.next() != XF_ERR_NONE)
        {
            if (!iff.depth)
                return ESCH_ERR_NOTFOUND;
            iff.leaveform();
            continue;
        }

        if (iff.chunkid == iff.makeid('E','S','P','T')
            || iff.chunkid == iff.makeid('E','S','P','1'))
        {
            err=load(&iff,lname);
            if (!err
                || err != ESCH_ERR_NOTFOUND)
                break;
        }

        // Must scan inside any ESEN Scene forms.
        else if (iff.chunkid == iff.makeid('F','O','R','M')
                 && iff.formid == iff.makeid('E','S','E','N'))
        {
            iff.enterform();
        }
    }

//陳 Return ok
    iff.close();
    return err;
}

esch_error_codes EschSpotLight::load(XFParseIFF *iff, const char *lname)
{
    assertMyth("EschSpotLight::load requries iff pointer",
               iff);

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Floating-point format
    if (iff->chunkid == iff->makeid('E','S','P','1'))
    {
        EschFileLightSpot   spot;

        if (iff->chunkSize != sizeof(spot))
            return ESCH_ERR_INVALIDDATA;

        //陳 Read chunk and verify name, if given.
        if (iff->read(&spot))
            return ESCH_ERR_FILEERROR;

        if (lname && strcmp(lname,spot.name))
            return ESCH_ERR_NOTFOUND;

        //陳 Found, so setup Spot Light
        strcpy(name,spot.name);
        flags = spot.flags;

        VngoColor24bit  c(spot.color);
        set_intensity( max( max(c.r, c.g), c.b ) );

        set_position( spot.x, spot.y, spot.z );
        set_direction( spot.i, spot.j, spot.k );

        set_inner( spot.inner );
        set_outer( spot.outer );

        set_hotspot( spot.hotspot );
        set_falloff( spot.falloff );
    }
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳 Fixed-point format
    else if (iff->chunkid == iff->makeid('E','S','P','T'))
    {
        EschFileLightSpotV1   spot;

        if (iff->chunkSize != sizeof(spot))
            return ESCH_ERR_INVALIDDATA;

        //陳 Read chunk and verify name, if given.
        if (iff->read(&spot))
            return ESCH_ERR_FILEERROR;

        if (lname && strcmp(lname,spot.name))
            return ESCH_ERR_NOTFOUND;

        //陳 Found, so setup Spot Light
        strcpy(name,spot.name);
        flags = spot.flags;

        VngoColor24bit  c(spot.color);
        set_intensity( max( max(c.r, c.g), c.b ) );

        set_position(spot.x / 65536.0f, spot.y / 65536.0f, spot.z / 65536.0f);
        set_direction(spot.i / 65536.0f, spot.j / 65536.0f, spot.k / 65536.0f);

        set_inner( spot.inner / 65536.0f );
        set_outer( spot.outer / 65536.0f );

        set_hotspot( spot.hotspot / 65536.0f );
        set_falloff( spot.falloff / 65536.0f );
    }
    else
    {
        return ESCH_ERR_NOTFOUND;
    }

//陳 Return ok
    return ESCH_ERR_NONE;
}

//葦� End of module - eslspot.cpp 憶�

