//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//                        樛樛樛樛樛                       樛樛
//     敖朕                栩�     栩�                     渟栩
//     �  �       敖朕     栩�     栩�   樛樛      樛樛�    栩� 樛�
//     �  � 敖朕  �  �     栩桀樛樂栩�  �  渟�    栩�   炳  栩栩桎栩
//     �  � �  �  �  �     栩�     栩�  樂栩栩�  栩�        栩�   栩�
//    O� O� �  �  �  �     栩�     栩� 渟�  栩�  栩�    樂  栩�   栩�
//          �  � O� O�    樂栩樛樂栩�   栩栩毯桀  炳桀樂�  樂栩� 樂栩�
//         O� O�
//                            C++ Music, Sound, and Effects Library
//                               Microsoft Windows 95/98/NT Version
//
//  Copyright (c) 1995-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
//
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
// Created by Dan Higdon & Chuck Walbourn
//
// bachsamp.cpp
//
// Base sample container class implementation.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "bach.hpp"

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// db_table - a table converting numbers 0-127 into dBV values for DSound   �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
short BachSample::db_table[] =
{
      0,     16,     32,     48,     65,     82,     98,    115,
    133,    150,    167,    185,    202,    220,    238,    256,
    275,    293,    312,    331,    350,    369,    388,    408,
    427,    447,    467,    488,    508,    529,    550,    571,
    592,    614,    636,    658,    680,    703,    725,    748,
    772,    795,    819,    843,    868,    892,    917,    943,
    968,    994,   1020,   1047,   1074,   1101,   1129,   1157,
   1185,   1214,   1243,   1273,   1303,   1334,   1365,   1396,
   1428,   1461,   1494,   1527,   1561,   1596,   1631,   1667,
   1703,   1740,   1778,   1817,   1856,   1896,   1937,   1978,
   2021,   2064,   2109,   2154,   2200,   2248,   2296,   2346,
   2397,   2449,   2502,   2557,   2614,   2672,   2732,   2793,
   2857,   2922,   2990,   3060,   3132,   3207,   3285,   3365,
   3450,   3537,   3629,   3725,   3825,   3931,   4042,   4160,
   4285,   4418,   4560,   4713,   4878,   5057,   5254,   5471,
   5714,   5989,   6307,   6682,   7142,   7735,   8571,  10000
};

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭�  Constructors/Destructors  碓旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachSample - Constructor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
BachSample::BachSample(BachDigital *digi) :
    sbuffer(0),
    flags (0),
    fmt (BACH_DIGI_MONO_8),
    rate (BACH_SMP_DEFAULTRATE),
    app_data (0)
{
    assertMyth("BachSample needs initialized BachDigital object",
               digi && digi->dsound != 0);

    dsound = digi->dsound;
    if (dsound)
        dsound->AddRef();
}

BachSample::BachSample (BachSample const &b) :
    sbuffer(0),
    flags (b.flags),
    fmt (b.fmt),
    rate (b.rate),
    app_data (b.app_data)
{
    assertMyth("BachSample needs initialized BachDigital object",
               b.dsound != 0);

    dsound = b.dsound;
    if (dsound)
        dsound->AddRef();

    if (b.sbuffer)
    {
        if (dsound->DuplicateSoundBuffer (b.sbuffer, &sbuffer) != DS_OK)
        {
            sbuffer = 0;
            flags = 0;
            fmt = BACH_DIGI_MONO_8;
            rate = BACH_SMP_DEFAULTRATE;
            app_data = 0;
        }
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachSample - Destructor
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
BachSample::~BachSample()
{
    release();

    if (dsound)
    {
        dsound->Release();
        dsound=0;
    }
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭�  Operations  碓旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachSample - operator =
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
BachSample &BachSample::operator = (BachSample const &that)
{
    if (&that != this)
    {
        stop();
        release();

        flags = that.flags & ~BACH_SMP_OWNSDATA;
        fmt = that.fmt;
        rate = that.rate;
        app_data = that.app_data;

        assertMyth("BachSample::operator = needs initialized BachDigital object",
                   that.dsound != 0);

        dsound = that.dsound;
        if (dsound)
            dsound->AddRef();

        if (that.sbuffer)
        {
            if (dsound->DuplicateSoundBuffer (that.sbuffer, &sbuffer) != DS_OK)
            {
                sbuffer = 0;
                flags = 0;
                fmt = BACH_DIGI_MONO_8;
                rate = BACH_SMP_DEFAULTRATE;
                app_data = 0;
            }
        }
    }

    return *this;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachSample - release
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void BachSample::release ()
{
    flags &= ~BACH_SMP_OWNSDATA;
    if (sbuffer)
    {
        sbuffer->Stop();
        sbuffer->Release();
        sbuffer = 0;
    }
}



//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭旭旭�  Utility Routines  碓旭旭旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// BachSample - db_table_find                                               �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
short BachSample::db_table_find (int i)
{
    int lo = 0;
    int hi = db_table_size;

    for (;;)
    {
        // Catch the case where the value is not found
        int midp = (lo + hi) / 2;

        if (lo == midp)
            return midp;

        // See which partition the value lies in
        int midv = db_table[midp];

        if (i == midv)
            return midp;

        else if (i > midv)
            lo = midp;

        else // (i < midv)
            hi = midp;
    }
}

//葦� End of module - bachsamp.cpp 憶�
