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
// eslatten.cpp
//
// The EschLight and associated classes are used for implementing the
// lighting model.  EschLights affect objects by controlling the
// shade level and potentially color of a vertex.  EschLight objects
// are maintained in a linked list.
//
// An EschAttenLight shines in all directions equally, but has a specific
// location in 3-space, and has a fall-off for distance from the light
// source.
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
// EschAttenLight - Constructor                                             �
//                                                                          �
// Initializes the light object with full intesity and sets type.           �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
EschAttenLight::EschAttenLight(const char *fname, const char *lname) :
    EschPointLight(),
    inner(0),
    outer(0x1000)
{
    ltyp = ESCH_LGTT_ATTEN;
    flags |= ESCH_LGT_ATTEN;

    if (fname)
    {
        load(fname,lname);
    }
};

EschAttenLight::EschAttenLight(const EschPoint *pnt, float i, float o) :
    EschPointLight(pnt),
    inner(i),
    outer(o)
{
    ltyp = ESCH_LGTT_ATTEN;
    flags |= ESCH_LGT_ATTEN;
};

EschAttenLight::EschAttenLight(float ix, float iy, float iz, float i, float o) :
    EschPointLight(ix,iy,iz),
    inner(i),
    outer(o)
{
    ltyp = ESCH_LGTT_ATTEN;
    flags |= ESCH_LGT_ATTEN;
};



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschAttenLight - setup                                                   �
//                                                                          �
// Performs the setup of the light on an object by object basis.            �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void EschAttenLight::setup(const EschFrameRef *fr)
{
    if (fr
        && EschCurrent
        && EschCurrent->camera
        && EschCurrent->camera->flags & ESCH_CAM_MODELSPACE)
    {
        pos.transform(&fr->iorient,&tpos);
        tinner = inner / fr->scalef;
        touter = outer / fr->scalef;
    }
    else
    {
        tpos = pos;
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
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// EschAttenLight - shine                                                   �
//                                                                          �
// Sets the shade level in the Van Gogh point based on the intesity of the  �
// light and the given vertex information.                                  �
//                                                                          �
// The point light source computes a direction vector relative to the       �
// vertex and then computes a dot product.  The distance is used to         �
// attenuate the intensity.                                                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void EschAttenLight::shine(const EschVertex *v, VngoPoint *vpt, int revnrml) const
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

            // Compute dot product
            float dot = v->normal DOT vtx;

            if (dot < 0)
            {
                dot = (revnrml) ? -dot : 0;
            }

            // Compute intensity output (including attenuation)
            float inten = _intensity;

            if ((flags & ESCH_LGT_ATTEN) && (mag > inner))
            {
                inten -= (mag - inner) * arate;
            }

            // Compute final shade value
            vpt->shade += long(dot * inten);
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
// EschAttenLight - hishine                                                 �
//                                                                          �
// Sets the shade level, allowing specular highlights to overdrive the      �
// color based on the intensity of the light and the given vertex info.     �
//                                                                          �
// The point light source computes a direction vector relative to the       �
// vertex and then computes a dot product.  The distance is used to         �
// attenuate the intensity.                                                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void EschAttenLight::hishine(const EschVertex *v, VngoPoint *vpt, int revnrml) const
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

            // Compute dot product
            float dot = v->normal DOT vtx;

            if (dot < 0)
            {
                dot = (revnrml) ? -dot : 0;
            }

            // Compute intensity output (including attenuation)
            float inten = _hintensity;

            if ((flags & ESCH_LGT_ATTEN) && (mag > inner))
            {
                inten -= (mag - inner) * harate;
            }

            // Compute final shade value
            vpt->shade += long(dot * inten);
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
// EschAttenLight - load                                                    �
//                                                                          �
// Loads the position and other data of the attenuated light from an IFF    �
// file.                                                                    �
//                                                                          �
// The IFF version assumes that the IFF is open and pointing at the proper  �
// chunk.  If a 'lname' is given and the name doesn't match that in the     �
// chunk, an error is returned.                                             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
esch_error_codes EschAttenLight::load(const char *fname, const char *lname)
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

        if (iff.chunkid == iff.makeid('E','A','T','N')
            || iff.chunkid == iff.makeid('E','A','T','1'))
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

esch_error_codes EschAttenLight::load(XFParseIFF *iff, const char *lname)
{
    assertMyth("EschAttenLight::load requries iff pointer",
               iff);

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Floating-point format
    if (iff->chunkid == iff->makeid('E','A','T','1'))
    {
        EschFileLightAtten  atn;

        if (iff->chunkSize != sizeof(atn))
            return ESCH_ERR_INVALIDDATA;

        //陳 Read chunk and verify name, if given.
        if (iff->read(&atn))
            return ESCH_ERR_FILEERROR;

        if (lname && strcmp(lname,atn.name))
            return ESCH_ERR_NOTFOUND;

        //陳 Found, so setup Atten Light
        strcpy(name,atn.name);
        flags = atn.flags;

        VngoColor24bit  c(atn.color);
        set_intensity( max( max(c.r, c.g), c.b ) );

        set_position( atn.x, atn.y, atn.z );

        set_inner( atn.inner );
        set_outer( atn.outer );
    }
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳 Fixed-point format
    else if (iff->chunkid == iff->makeid('E','A','T','N'))
    {
        EschFileLightAttenV1  atn;

        if (iff->chunkSize != sizeof(atn))
            return ESCH_ERR_INVALIDDATA;

        //陳 Read chunk and verify name, if given.
        if (iff->read(&atn))
            return ESCH_ERR_FILEERROR;

        if (lname && strcmp(lname,atn.name))
            return ESCH_ERR_NOTFOUND;

        //陳 Found, so setup Atten Light
        strcpy(name,atn.name);
        flags = atn.flags;

        VngoColor24bit  c(atn.color);
        set_intensity( max( max(c.r, c.g), c.b ) );

        set_position(atn.x / 65536.0f, atn.y / 65536.0f, atn.z / 65536.0f);

        set_inner( atn.inner / 65536.0f );
        set_outer( atn.outer / 65536.0f );
    }
    else
    {
        return ESCH_ERR_NOTFOUND;
    }

//陳 Return ok
    return ESCH_ERR_NONE;
}

//葦� End of module - eslatten.cpp 憶�

