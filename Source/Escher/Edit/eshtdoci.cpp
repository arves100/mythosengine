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
//                        *** Escher Terrain Editor ***
//
// Created by Chuck Walbourn
//
// eshtdoci.cpp
//
// Terrain Editor Document class import routines.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Includes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include "stdafx.h"
#include <process.h>

#include "eshtedit.h"

#include "eshtdoc.h"
#include "eshtview.h"
#include "eshtdlg.h"
#include "eshtusgs.h"

#include "esfile.hpp"
#include "dem.h"

#include <float.h>
#include <math.h>

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Data
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�
//
//                                 Code
//
//臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                             旭� Protected 旭�                            �
// TerrEditDoc - find_closest_htable_entry                                  �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
long TerrEditDoc::find_closest_htable_entry(float h, long start, long end)
{
    if (start >= end)
    {
        if (start < 0)
            return 0;
        else if (start > 255)
            return 255;
        else
            return start;
    }

    long mid = (start+end) >> 1;

    if (htable[mid] > h)
    {
        return find_closest_htable_entry(h, start, mid-1);
    }
    else if (htable[mid] < h)
    {
        return find_closest_htable_entry(h, mid+1, end);
    }
    else
        return mid;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                             旭� Protected 旭�                            �
// TerrEditDoc - find_entry                                                 �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
long TerrEditDoc::find_entry(float *heights, float h, long start, long end)
{
    if (start >= end)
    {
        if (start > end)
            return -1;

        return ((heights[start] == h) ? start : -1);
    }

    long mid = (start+end) >> 1;

    if (heights[mid] > h)
    {
        return find_entry(heights, h, start, mid-1);
    }
    else if (heights[mid] < h)
    {
        return find_entry(heights, h, mid+1, end);
    }
    else
        return mid;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                             旭� Protected 旭�                            �
// TerrEditDoc - compress_heights_standard                                  �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void TerrEditDoc::compress_heights_standard(long xs, long ys, long w, long h,
                                            ushort *data, BOOL normalize)
{
    ushort  *sptr;
    long    x, y;

    ProgressDlg dlg;
    dlg.m_pbar.SetRange(0, 1);
    dlg.m_pbar.SetPos(0);
    dlg.SetWindowText("Compressing heights...");
    dlg.ShowWindow(SW_SHOW);

    //陳� Find minimum value
    ushort min;
    for(y=ys, min=65535; y < h; y++)
    {
        for(x=xs, sptr=data+(y*w)+xs; x < w; x++)
        {
            if (*sptr < min)
                min = *sptr;

            sptr++;
        }
    }

    //陳� Setup height table
    for(long i=0; i < 256; i++)
    {
        htable[i] = float(16*i) + float(((normalize) ? 0 : min));
    }

    //陳� Copy data
    byte    *dptr;
    long    cx, cy;

    for(y=ys, cy=0; y < h; y++)
    {
        for(x=xs, cx=0, sptr=data+(y*w)+xs, dptr=hfield+(y*width);
            x < w; x++)
        {
            // Perform VistaPro's standard conversion of DEM->PCX
            // (although VistaPro arbitrarily never uses color 0 for
            //  PCX output, so we will not do this so we can represent
            //  height 0)
            *(dptr++) = (byte)(( ((*sptr++) - min + 15) >> 4 ) & 0xff);
            if (++cx >= width)
                break;
        }

        if (++cy >= depth)
            break;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                             旭� Protected 旭�                            �
// TerrEditDoc - compress_heights_uniform                                   �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void TerrEditDoc::compress_heights_uniform(long xs, long ys, long w, long h,
                                           ushort *data, BOOL normalize)
{
    ushort  *sptr;
    long    x, y;

    ProgressDlg dlg;
    dlg.m_pbar.SetRange(0, 1);
    dlg.m_pbar.SetPos(0);
    dlg.SetWindowText("Compressing heights...");
    dlg.ShowWindow(SW_SHOW);

    //陳� Find minimum/maximum value
    ushort min, max;
    for(y=ys, min=65535, max=0; y < h; y++)
    {
        for(x=xs, sptr=data+(y*w)+xs; x < w; x++)
        {
            if (*sptr < min)
                min = *sptr;
            if (*sptr > max)
                max = *sptr;

            sptr++;
        }
    }

    //陳� Setup height table
    htable[0] = (normalize) ? 0.0f : float(min);

    float step = float(max-min) / 256.0f;
    for(long i=1; i < 256; i++)
    {
        htable[i] = htable[i-1] + step;
    }

    //陳� Copy data (use closest height in table)
    byte    *dptr;
    long    cx, cy;

    ushort  adjust = (normalize) ? min : 0;

    for(y=ys, cy=0; y < h; y++)
    {
        for(x=xs, cx=0, sptr=data+(y*w)+xs, dptr=hfield+(y*width);
            x < w; x++)
        {
            *(dptr++) = (byte)find_closest_htable_entry(float(*(sptr++)-adjust),0,255);
            if (++cx >= width)
                break;
        }

        if (++cy >= depth)
            break;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                             旭� Protected 旭�                            �
// TerrEditDoc - compress_heights_averaged                                  �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void TerrEditDoc::compress_heights_averaged(float threshold,
                                            long xs, long ys, long w, long h,
                                            ushort *data, BOOL normalize)
{
    ushort  *sptr;
    long    x, y;

    ProgressDlg dlg;
    dlg.m_pbar.SetRange(0, 1);
    dlg.m_pbar.SetPos(0);
    dlg.SetWindowText("Compressing heights...");
    dlg.ShowWindow(SW_SHOW);

    //陳� Gather counts on all heights used (and minimum)
    ushort  min;
    ulong   maxh = 256, hcount=0;

    float *heights = new float[maxh];
    ASSERT(heights);

    long *counts = new long[maxh];
    ASSERT(counts);

    for(y=ys, min=65535; y < h; y++)
    {
        for(x=xs, sptr=data+(y*w)+xs; x < w; x++)
        {
            if (*sptr < min)
                min = *sptr;

            float h = (float) *(sptr++);

            long ind = find_entry(heights,h,0,hcount);
            if (ind == -1)
            {
                if (hcount >= maxh)
                {
                    // Handle expand of array
                    float *nh = new float[maxh*2];
                    ASSERT(nh);
                    memcpy(nh,heights,sizeof(float)*maxh);
                    delete [] heights;
                    heights = nh;

                    long *nc = new long[maxh*2];
                    ASSERT(nc);
                    memcpy(nc,counts,sizeof(long)*maxh);
                    delete [] counts;
                    counts = nc;

                    maxh *= 2;
                }

                heights[hcount] = h;
                counts[hcount] = 1;

                // Resort (by height)
                for(long i = hcount; i > 0; i--)
                {
                    if (heights[i] < heights[i-1])
                    {
                        float h = heights[i-1];
                        heights[i-1] = heights[i];
                        heights[i] = h;

                        long c = counts[i-1];
                        counts[i-1] = counts[i];
                        counts[i] = c;
                    }
                    else
                        break;
                }

                hcount++;
            }
            else
            {
                counts[ind]++;
            }
        }
    }

    //陳� Compact table to 256 entries

    // Keep averaging least used 'close' heights
    // until we reduce the table to 256 or fewer entries

    if (hcount > 256)
        dlg.m_pbar.SetRange(0, short(hcount-256));

    for(long loops=0; hcount > 256; loops++)
    {
        dlg.m_pbar.SetPos(loops);

        // Sort by decending count
        for(;;)
        {
            BOOL changed=FALSE;

            for(long i=hcount-1; i > 0; i--)
            {
                if (counts[i] > counts[i-1])
                {
                    float h = heights[i-1];
                    heights[i-1] = heights[i];
                    heights[i] = h;

                    long c = counts[i-1];
                    counts[i-1] = counts[i];
                    counts[i] = c;

                    changed=TRUE;
                }
            }

            if (!changed)
                break;
        }

        // Find two indexes that are 'closest'
        ulong ind1=0, ind2=0;

        for(long cnt=counts[hcount-1];;)
        {
			long stop = 0;
            for(stop=hcount-1; stop > 0; stop--)
            {
                if (counts[stop-1] > cnt)
                    break;
            }

            float mind = FLT_MAX;
            for(long i=hcount-1; i >= stop; i--)
            {
                for(long j=hcount-1; j >= stop; j--)
                {
                    if (i == j)
                        continue;

                    float d = float(fabs(heights[i] - heights[j]));

                    if (d < mind)
                    {
                        mind = d;
                        ind1 = i;
                        ind2 = j;
                    }
                }
            }

            if (mind <= threshold)
                break;

            if (stop <= 0 || cnt >= counts[0])
            {
                MessageBox(NULL,
                           "Averaged height table cannot be created\n"
                           "based on given input threshold...\n\n"
                           "Using uniform table...",
                           "Import Terrain Error",
                           MB_OK);
                compress_heights_uniform(xs,ys,w,h,data,normalize);
                delete [] heights;
                delete [] counts;
                return;
            }
            cnt=counts[stop-1];
        }

        ASSERT(ind1 != ind2 && ind1 < hcount && ind2 < hcount);

        // Make sure index 1 is 'higher' in the table for
        // better sorting/removing performance
        if (ind1 > ind2)
        {
            long t=ind1;
            ind1=ind2;
            ind2=t;
        }

        // Create averaged entry with sum of usage counts
        heights[ind1] = (heights[ind1] + heights[ind2]) / 2.0f;
        counts[ind1] = counts[ind1] + counts[ind2];

        // Remove now freed index
        for(long i=ind2; i < (long)hcount-1; i++)
        {
            heights[i] = heights[i+1];
            counts[i] = counts[i+1];
        }

        // We have removing one entry
        hcount--;
    }

    //陳� Setup height table
    ushort  adjust = (normalize) ? min : 0;

    memset(htable,0,sizeof(float)*256);
    for(long i=0; i < (long)hcount; i++)
    {
        htable[i] = heights[i] - float(adjust);
    }

    // Free temp data
    delete [] heights;
    delete [] counts;

    // Sort by height
    for(;;)
    {
        BOOL changed=FALSE;

        for(long i=hcount-1; i > 0; i--)
        {
            if (htable[i] < htable[i-1])
            {
                float h = htable[i-1];
                htable[i-1] = htable[i];
                htable[i] = h;

                changed=TRUE;
            }
        }

        if (!changed)
            break;
    }

    //陳� Copy data (use closest height in table)
    byte    *dptr;
    long    cx, cy;

    for(y=ys, cy=0; y < h; y++)
    {

        for(x=xs, cx=0, sptr=data+(y*w)+xs, dptr=hfield+(y*width);
            x < w; x++)
        {
            *(dptr++) = (byte)find_closest_htable_entry(float(*(sptr++)-adjust),0,hcount-1);
            if (++cx >= width)
                break;
        }

        if (++cy >= depth)
            break;
    }
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                             旭� Protected 旭�                            �
// TerrEditDoc - import_heights_from_vpdem                                  �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
BOOL TerrEditDoc::import_heights_from_vpdem(const char *fname, BOOL *isvpdem)
{
    int                 i;
    XFileDOS            xf;
    struct DEM_HEADER   demh;

//陳� Read and verify VistaPro DEM file
    if ((i=xf.open(fname,XF_OPEN_READ))!=0)
    {
        char    str[512];

        sprintf(str,"Error #%x opening input terrain file:\n\n%s",(int)i,fname);

        MessageBox(NULL,
                   str,"Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    //陳� Load header of DEM file
    if (xf.read(&demh,sizeof(struct DEM_HEADER)) != sizeof(struct DEM_HEADER))
    {
        char    str[512];

        sprintf(str,"Error #%x reading header from input terrain file:\n\n%s",
                    (int)i,fname);

        MessageBox(NULL,
                   str,"Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    //陳� Verify header
    if (strncmp(demh.id,"Vista DEM File",32))
    {
        if (isvpdem)
        {
            *isvpdem = FALSE;
        }
        return FALSE;
    }

    if (isvpdem)
        *isvpdem = TRUE;

    //陳� If compressed, try to decompress
    if (demh.compression != 0)
    {
        char tname[MAX_PATH];
        char pname[MAX_PATH];

        xf.close();

        //陳� Try to spawn DECOMP to a temp file...
        GetTempPath(MAX_PATH, tname);
        GetTempFileName(tname, "DEM", 0, tname);

        if (!SearchPath(NULL, "DECOMP.EXE", NULL, MAX_PATH, pname, NULL))
        {
            xf_remove(tname);

            if (MessageBox(NULL,
                           "Could not find VistaPro DECOMP decompressor\n\n"
                           "DEM must already be decompressed to read",
                           "Import Terrain Error",MB_OKCANCEL | MB_ICONEXCLAMATION) == IDCANCEL)
                return FALSE;
        }
        else if (_spawnl(_P_WAIT, pname, pname, fname, tname, NULL))
        {
            xf_remove(tname);

            char    str[512];

            sprintf(str,"Error while trying to run VistaPro decompressor DECOMP on:\n\n%s",
                        fname);

            if (MessageBox(NULL,
                        str,"Import Terrain Error",MB_OKCANCEL | MB_ICONEXCLAMATION)==IDCANCEL)
                return FALSE;
        }

        //陳� Open DEM file for processing.
        if ((i=xf.open(tname,XF_OPEN_READ | XF_OPEN_KILL))!=0)
        {
            char    str[512];

            sprintf(str,"Error #%x opening temporary terrain file:\n\n%s",(int)i,tname);

            MessageBox(NULL,
                       str,"Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        //陳� Load header of DEM file
        if (xf.read(&demh,sizeof(struct DEM_HEADER)) != sizeof(struct DEM_HEADER))
        {
            char    str[512];

            sprintf(str,"Error #%x reading header from temporary terrain file:\n\n%s",
                        (int)i,tname);

            MessageBox(NULL,
                       str,"Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        //陳� Verify header
        if (strncmp(demh.id,"Vista DEM File",32)
            || demh.compression != 0)
        {
            char    str[512];

            sprintf(str,"DECOMP decompress failed to operate correctly on:\n\n%s",tname);

            MessageBox(NULL,
                       str,"Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }
    }

    if (demh.header_type != 0 && demh.header_type != 16777216)
    {
        MessageBox(NULL,
                   "The import file contains an unknown series DEM, which is not supported",
                   "Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

//陳� Load data from DEM
    long iwidth, idepth;
    if (demh.header_type == 16777216)
    {
        demh.ex_width = ((demh.ex_width & 0xff) << 24) |
                        ((demh.ex_width & 0xff00) << 8) |
                        ((demh.ex_width & 0xff0000) >> 8) |
                        ((demh.ex_width & 0xff000000) >> 24);
        demh.ex_depth = ((demh.ex_depth & 0xff) << 24) |
                        ((demh.ex_depth & 0xff00) << 8) |
                        ((demh.ex_depth & 0xff0000) >> 8) |
                        ((demh.ex_depth & 0xff000000) >> 24);

        if (!demh.ex_width || !demh.ex_depth)
        {
            MessageBox(NULL,
                   "The import file hsa an invalid field size",
                   "Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        if ((demh.ex_width > 65535) || (demh.ex_depth > 65535))
        {
            MessageBox(NULL,
                   "The import file is too large, it MUST be less than 64k by 64k",
                   "Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
        }

        iwidth = (ushort)demh.ex_width;
        idepth = (ushort)demh.ex_depth;
    }
    else
    {
        ASSERT(demh.header_type == 0);

        iwidth = 258;
        idepth = 258;
    }

    ushort *data = new ushort[iwidth * idepth];
    if (!data)
    {
        MessageBox(NULL,
             "Failed to allocate enough memory for import",
             "Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    if (xf.read(data,sizeof(ushort)*iwidth * idepth) != sizeof(ushort)*iwidth * idepth)
    {
        MessageBox(NULL,
             "Could not load height field from DEM file",
             "Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
        delete [] data;
        return FALSE;
    }

//陳� Close
    xf.close();

//陳� Determine data conversion algorithm
    int option;
    float threshold;
    BOOL normalize;
    {
        DEMImportDlg dlg;
        if (dlg.DoModal() == IDCANCEL)
            return FALSE;

        option=dlg.option;
        threshold=dlg.m_avg_maxd;
        normalize=dlg.m_normalize;
    }

//陳� Copy data from DEM
    memset(name,0,sizeof(name));
    strncpy(name,demh.name,ESCH_MAX_NAME-1);

    memset(desc,0,sizeof(desc));
    strncpy(desc,demh.comment,sizeof(desc));

    scale = 32;

    // Clear buffer
    memset(hfield,0,width*depth);

    switch (option)
    {
        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Standard 16 meter conversion
        case DEMImportDlg::STANDARD:
            compress_heights_standard(0, 0, iwidth, idepth, data, normalize);
            break;
        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Uniform height table
        case DEMImportDlg::UNIFORM:
            compress_heights_uniform(0, 0, iwidth, idepth, data, normalize);
            break;
        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Averaged table
        case DEMImportDlg::AVERAGE:
            compress_heights_averaged(threshold, 0, 0, iwidth, idepth, data, normalize);
            break;
    }

//陳� Delete data
    delete [] data;

    return TRUE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                             旭� Protected 旭�                            �
// TerrEditDoc - import_heights_from_usgsdem                                �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
BOOL TerrEditDoc::import_heights_from_usgsdem(const char *fname)
{
    int                 i;
    USGSFileParseDEM    usgs;

//陳� Read USGS data (class displays error!)
    if ((i=usgs.read(fname)) != 0)
        return FALSE;

//陳� Determine data conversion algorithm
    int option;
    float threshold;
    BOOL normalize;
    long longitude, latitude;
    for(;;)
    {
        DEMImportDlg      dlg;
        dlg.isusgs=TRUE;
        dlg.longitude=(long)usgs.xy_corners[0];
        dlg.latitude=(long)usgs.xy_corners[1];
        if (dlg.DoModal() == IDCANCEL)
        {
            if (MessageBox(NULL,
                           "Are you sure you wish to abort import?",
                           "Terrain Import Warning",
                           MB_YESNO | MB_ICONQUESTION) == IDYES)
                return FALSE;
            else
                continue;
        }

        option=dlg.option;
        threshold=dlg.m_avg_maxd;
        normalize=dlg.m_normalize;
        longitude=dlg.longitude;
        latitude=dlg.latitude;
        break;
    }

//陳� Expand data into 2D array
    ushort *data=0;
    USGSFileParseDEM::usgs_error err = usgs.expand_data(longitude,
                                                        latitude,
                                                        width,
                                                        depth,
                                                        &data);
    if (err)
    {
        char str[512];

        sprintf(str,"Error while converting USGS profles:\n\n%s",usgs.get_error_string(err));
        MessageBox(NULL,
                   str,
                   "Terrain Import Error",
                   MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

//陳� Copy data from DEM
    CString str=usgs.name;  str.TrimRight();  str.TrimLeft();

    memset(name,0,sizeof(name));
    strncpy(name,str,ESCH_MAX_NAME-1);

    memset(desc,0,sizeof(desc));
    strncpy(desc,str,sizeof(desc));

    // Expand data always goes to 1 arc-second...
    scale = 32;

    // Clear buffer
    memset(hfield,0,width*depth);

    switch (option)
    {
        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Standard 16 meter conversion
        case DEMImportDlg::STANDARD:
            compress_heights_standard(0, 0, width, depth, data, normalize);
            break;
        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Uniform height table
        case DEMImportDlg::UNIFORM:
            compress_heights_uniform(0, 0, width, depth, data, normalize);
            break;
        //陳陳陳陳陳陳陳陳陳陳陳陳陳陳� Averaged table
        case DEMImportDlg::AVERAGE:
            compress_heights_averaged(threshold, 0, 0, width, depth, data, normalize);
            break;
    }

//陳� Delete data
    delete [] data;

    return TRUE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//                             旭� Protected 旭�                            �
// TerrEditDoc - import_heights_from_pcx                                    �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
BOOL TerrEditDoc::import_heights_from_pcx(const char *fname)
{
    int         i, x, y, cx, cy;
    byte        *dptr, *sptr;
    XFParsePCX  pcx;

//陳� Load data from PCX
    if (pcx.nameread(fname))
    {
        char    str[512];

        sprintf(str,"Error #%x opening input terrain file:\n\n%s",
                    (int)pcx.error(),fname);
        MessageBox(NULL,
                   str,"Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

//陳� Check values in bitmap
    if (pcx.bm->bpp != 1)
    {
        MessageBox(NULL,
                   "PCX terrain files must be have 8-bit color depth",
                   "Import Terrain Error",MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

//陳� Setup height table
    for(i=0; i < 256; i++)
    {
        htable[i] = float(16*i);
    }

//陳� Copy data from PCX
    memset(hfield,0,width*depth);

    // Copy data
    for(y=0, cy=0; y < pcx.bm->height; y++)
    {
        for(x=0, cx=0,
            sptr=pcx.bm->data+(y*(pcx.bm->width)), dptr=hfield+(y*(width));
            x < pcx.bm->width; x++)
        {
            *(dptr++) = *(sptr++);
            if (++cx >= width)
                break;
        }

        if (++cy >= depth)
            break;
    }

    return TRUE;
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// TerrEditDoc - ImportTerrain                                              �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void TerrEditDoc::ImportTerrain(const char *fname, int losswarn)
{
	int i = 0;
    ASSERT(width && depth && hfield && htable);

    if (losswarn)
    {
        byte *ptr=hfield;
        for(i=0; i < (width * depth); i++)
        {
            if (*(ptr++))
                break;
        }

        if (i < (width*depth))
        {
            if (MessageBox(NULL,
                           "All current terrain height and normal data will be lost.\n\n"
                           "Do you wish to continue import?",
                           "Import Terrain Warning",
                           MB_OKCANCEL | MB_ICONEXCLAMATION) == IDCANCEL)
                return;
        }
    }

    undo_valid=FALSE;

//陳� Import DEM File
    if (strstr(fname,".DEM") || strstr(fname,".dem"))
    {
        BOOL isvpdem;

        if (!import_heights_from_vpdem(fname,&isvpdem))
        {
            if (isvpdem)
                return;

            if (!import_heights_from_usgsdem(fname))
                return;
        }
    }
//陳� Import PCX File
    else if (strstr(fname,".PCX") || strstr(fname,".pcx"))
    {
        if (!import_heights_from_pcx(fname))
            return;
    }
//陳� Import USGS DEM File
    else
    {
        if (!import_heights_from_usgsdem(fname))
            return;
    }

//陳� Update application
    ComputeNormals(NORMALS_SMOOTH);
    ComputeNormals(NORMALS_FLAT);

    SetModifiedFlag();
    SetLightsModifiedFlag();
    UpdateAllViews(NULL,HINT_UPDATETERR|HINT_UPDATECOLR|HINT_UPDATELIGHTS,NULL);
}


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// TerrEditDoc - ImportSurface                                              �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
void TerrEditDoc::ImportSurface(const char *fname, int losswarn)
{
    int             x, y, cx, cy;
    byte            *sptr;
    dword           *dptr;
    XFParsePCX      pcx;

    ASSERT(width && depth && surfcolr);

    dword surfsize = (width * depth) >> (surfshift*2);

    if (losswarn)
    {
        dword i;
        dword *ptr;

        for(i=0, ptr=surfcolr; i < surfsize; i++)
        {
            if (*(ptr++))
                break;
        }

        if (i < surfsize)
        {
            if (MessageBox(NULL,
                           "All current terrain surface color data will be lost.\n\n"
                           "Do you wish to continue import?",
                           "Import Surface Warning",
                           MB_OKCANCEL | MB_ICONEXCLAMATION) == IDCANCEL)
                return;
        }
    }

//陳� Load data from PCX
    if (pcx.nameread(fname))
    {
        char    str[512];

        sprintf(str,"Error #%x opening input surface file:\n\n%s",
                    (int)pcx.error(),fname);

        MessageBox(NULL,
                  str,"Import Surface Error",MB_OK | MB_ICONEXCLAMATION);
        return;
    }

//陳� Check values in bitmap
    if (pcx.bm->bpp != 1)
    {
        MessageBox(NULL,
                  "PCX surface color files must be have 8-bit color depth",
                  "Import Surface Error",MB_OK | MB_ICONEXCLAMATION);
        return;
    }

    PushUndo();

//陳� Copy data from PCX (converting to RGB)
    memset(surfcolr,0,surfsize*sizeof(dword));

    // Copy data
    for(y=0, cy=0; y < pcx.bm->height;)
    {
        for(x=0,
            cx=0,
            sptr=pcx.bm->data+((pcx.bm->height-y-1)*(pcx.bm->width)),
            dptr=surfcolr+(cy*(width >> surfshift));
            x < pcx.bm->width; )
        {
            *dptr = pcx.bm->pal[*sptr];

            x += (1 << surfshift);
            sptr += (1 << surfshift);

            dptr++;
            if (++cx >= (width >> surfshift))
                break;
        }

        y += (1 << surfshift);
        if (++cy >= (depth >> surfshift))
            break;
    }

    map_surfcolor_to_palette();

//陳� Update application
    SetModifiedFlag();
    UpdateAllViews(NULL,HINT_UPDATECOLR,NULL);
}

//葦� eof - eshtdoci.cpp 憶�
