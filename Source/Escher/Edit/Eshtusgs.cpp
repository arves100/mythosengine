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
//                        *** Escher Terrain Editor ***
//
// Created by Chuck Walbourn
//
// USGS DEM Parse class by Sean Gallagher
//
// eshtusgs.cpp
//
// USGS DEM Support class
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "stdafx.h"
#include "eshtedit.h"

#include "eshtusgs.h"

#include "eshtdlg.h"

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//������������������������� Constructor/Destructor ��������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// USGSFileParseDEM                                                         �
//���������������������������������������������������������������������������
USGSFileParseDEM::USGSFileParseDEM() :
    profiles(0),
    level_code(0),
    ground_units(UNITS_METERS),
    elev_units(UNITS_METERS),
    polygon_sides(0),
    min_elev(0),
    max_elev(0),
    profile_rows(0),
    profile_columns(0)
{
    for(ulong i=0; i < 8; i++)
        xy_corners[i]=0;
    *name=0;
    *comment=0;
    axis[0] = axis[1] = axis[2] = 0;
}


//�������������������������������������������������������������������������Ŀ
// USGSFileParseDEM                                                         �
//���������������������������������������������������������������������������
USGSFileParseDEM::~USGSFileParseDEM()
{
    if (profiles)
    {
        delete [] profiles;
        profiles = 0;
    }
}



//���������������������������������������������������������������������������
//������������������������������� Operations ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// USGSFileParseDEM - skip_n_tokens                                         �
//                                                                          �
// Skips a specified number of tokens.                                      �
//���������������������������������������������������������������������������
USGSFileParseDEM::usgs_error USGSFileParseDEM::skip_n_tokens(ulong n)
{
    Token tk;

    for (ulong i=0; i < n; i++)
    {
        usgs_error err = read_next_token(&tk);
        if (err)
            return err;
    }

    return ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// USGSFileParseDEM - read_next_token                                       �
//                                                                          �
// Reads the next white-space delimited token in the file.                  �
//���������������������������������������������������������������������������
USGSFileParseDEM::usgs_error USGSFileParseDEM::read_next_token(Token *tk)
{
    char ch;
    char buff[128];

//��� clear the data type flags
    tk->flags = 0;

//��� Skip past any whitespace...
    for(;;)
    {
        if (xf.read(&ch,1) != 1)
        {
            return (xf.error() == XF_ERR_EOF)
                   ? ERR_UNEXPECTEDEOF : ERR_FILEERROR;
        }

        if (!strchr(" \t\r\n",ch))
            break;
    }

//��� Read in next token
    memset(buff, 0, sizeof(buff));
    buff[0] = ch;
	ulong i = 0;

    for(i=1; i < sizeof(buff); i++)
    {
        if (xf.read(&ch,1) != 1)
        {
            if (xf.error() == XF_ERR_EOF)
                break;
            else
                return ERR_FILEERROR;
        }

        if (strchr(" \t\r\n",ch))
            break;

        buff[i] = ch;
    }

//��� Don't overrun our buffer...
    if (i >= sizeof(buff))
        return ERR_TOKENTOOLONG;

//��� Test for type and put into token structure
    if (strchr(buff,'.') != NULL)
    {
        // we've got a floating point value...
        tk->flags = IS_DOUBLE;

        tk->a = 0;
        tk->b = atof(buff);
    }
    else
    {
        // we've got something else that we'll try to convert to a ushort
        tk->flags = IS_UINT;

        int res = atol(buff);
        tk->a = (ushort)res;
        tk->b = 0.0;
    }

    return ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// USGSFileParseDEM - read_header_info                                      �
//                                                                          �
// Reads in the type A record of the USGS DEM file                          �
//���������������������������������������������������������������������������
USGSFileParseDEM::usgs_error USGSFileParseDEM::read_header_info()
{
    usgs_error  err;
    Token       tk;

//��� Read name fields
    if (xf.read(name,40) != 40)
    {
        return (xf.error() == XF_ERR_EOF)
                ? ERR_UNEXPECTEDEOF : ERR_FILEERROR;
    }

    if (xf.read(comment,104) != 104)
    {
        return (xf.error() == XF_ERR_EOF)
                ? ERR_UNEXPECTEDEOF : ERR_FILEERROR;
    }

//��� Get the DEM level code
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    level_code = tk.a;

//��� Skip past some info we don't care about
    err=skip_n_tokens(18);
    if (err)
        return err;

//��� Get the unit of measure for the ground coordinates
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    ground_units = tk.a;

//��� Get the unit of measure for the elevation coordinates
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    elev_units = tk.a;

//��� Get the number of sides of the region
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    polygon_sides = tk.a;

//��� Get the ground coords of the four corners of the DEM.
    for (ulong i=0; i < 4; i++)
    {
        err=read_next_token(&tk);
        if (err)
            return err;

        if (tk.flags != IS_DOUBLE)
            return ERR_INVALIDTOKEN;

        xy_corners[2*i] = tk.b;

        err=read_next_token(&tk);
        if (err)
            return err;

        if (tk.flags != IS_DOUBLE)
            return ERR_INVALIDTOKEN;

        xy_corners[2*i+1] = tk.b;
    }

//��� Get the minimum elevation for the DEM
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_DOUBLE)
        return ERR_INVALIDTOKEN;

    min_elev = tk.b;

//��� Get the maximum elevation for the DEM
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_DOUBLE)
        return ERR_INVALIDTOKEN;

    max_elev = tk.b;

//��� Read the axis values
    {
        char buff[16];
        memset(buff,0,sizeof(buff));

        if (xf.seek_set(816) != 816)
            return ERR_FILEERROR;

        //��� X
        if (xf.read(buff,12) != 12)
            return ERR_FILEERROR;

        if (!strchr(buff,'.'))
            return ERR_INVALIDTOKEN;

        axis[0] = atof(buff);

        //��� Y
        if (xf.read(buff,12) != 12)
            return ERR_FILEERROR;

        if (!strchr(buff,'.'))
            return ERR_INVALIDTOKEN;

        axis[1] = atof(buff);

        //��� Z
        if (xf.read(buff,12) != 12)
            return ERR_FILEERROR;

        if (!strchr(buff,'.'))
            return ERR_INVALIDTOKEN;

        axis[2] = atof(buff);
    }

//��� Get profile row count
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    profile_rows = tk.a;

//��� Get profile column count
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    profile_columns = tk.a;

    return ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// USGSFileParseDEM - read_profile                                          �
//                                                                          �
// Reads in a number of type B records of a USGS DEM file for a single      �
// profile.                                                                 �
//���������������������������������������������������������������������������
USGSFileParseDEM::usgs_error USGSFileParseDEM::read_profile(USGSProfileDEM *prof)
{
    usgs_error  err;
    Token       tk;

//��� Get row id
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    prof->row_id = tk.a;

//��� Get column id
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    prof->column_id = tk.a;

//��� Get number of rows
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    prof->rows = tk.a;

//��� Get number of columns
    err=read_next_token(&tk);
    if (err)
        return err;

    if (tk.flags != IS_UINT)
        return ERR_INVALIDTOKEN;

    prof->columns = tk.a;

//��� Skip past some info we don't care about
    err=skip_n_tokens(5);
    if (err)
        return err;

//��� Allocated profile memory
    ulong data_size = prof->rows*prof->columns;
    if (!data_size)
        return ERR_INVALIDPROFILE;

    prof->data = new ushort[data_size];
    if (!prof->data)
        return ERR_NOMEMORY;

//��� Read profile values
    for (ulong i=0; i < data_size; i++)
    {
        err=read_next_token(&tk);
        if (err)
            return err;

        if (tk.flags != IS_UINT)
            return ERR_INVALIDTOKEN;

        prof->data[i] = tk.a;
    }

    return ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// USGSFileParseDEM - read                                                  �
//                                                                          �
// Reads the USGS DEM file into memory, returning an error or 0 if          �
// successful.                                                              �
//���������������������������������������������������������������������������
USGSFileParseDEM::usgs_error USGSFileParseDEM::read(const char *fname)
{
    ulong       i;
    usgs_error  err;
    ulong       data_size;

    if (!fname)
        return ERR_INVALIDPARMS;

    DEMProgressDlg dlg(this);
    dlg.m_fname = fname;
    dlg.m_status = "Opening file";
    dlg.m_pbar.SetRange(0, 1);
    dlg.m_pbar.SetPos(0);
    dlg.ShowWindow(SW_SHOW);
    dlg.RedrawWindow();

    if (xf.open(fname, XF_OPEN_READ))
    {
        err=ERR_FILEERROR;
        goto error_exit;
    }

    xf.setbuffersize(262144);

//��� Read header
    dlg.m_status = "Reading header";
    dlg.UpdateData(FALSE);
    dlg.RedrawWindow();

    err=read_header_info();
    if (err)
        goto error_exit;

    dlg.m_pbar.SetPos(1);
    dlg.UpdateData(FALSE);
    dlg.RedrawWindow();

//��� Allocate profile memory
    data_size = profile_rows*profile_columns;
    if (!data_size)
    {
        err=ERR_NOPROFILES;
        goto error_exit;
    }

    profiles = new USGSProfileDEM[data_size];
    if (!profiles)
    {
        err=ERR_NOMEMORY;
        goto error_exit;
    }

    memset(profiles, 0, sizeof(USGSProfileDEM)*data_size);

//��� Read profiles
    dlg.m_pbar.SetRange(0, short(data_size));
    dlg.m_status = "Reading profiles";
    dlg.UpdateData(FALSE);
    dlg.RedrawWindow();

    for (i=0; i < data_size; i++)
    {
        dlg.m_pbar.SetPos(i);
        err = read_profile(&profiles[i]);
        if (err)
            goto error_exit;
    }

    dlg.DestroyWindow();
    dlg.okon=TRUE;
    dlg.m_status = "Read Complete";
    dlg.DoModal();

    return ERR_NONE;

error_exit:;
    dlg.DestroyWindow();
    dlg.okon=TRUE;
    dlg.m_status = get_error_string(err);
    dlg.m_status += " - Read Failed";
    dlg.DoModal();

    return err;
}


//�������������������������������������������������������������������������Ŀ
// USGSFileParseDEM - expand_data                                           �
//                                                                          �
// Converts the USGS DEM file in memory into a 2D array based on a starting �
// longitude, latitude pair and a target size.  The ground parametetric data�
// is converted into 1 arc-second data, which is close to 30 meters.        �
//���������������������������������������������������������������������������
USGSFileParseDEM::usgs_error USGSFileParseDEM::expand_data(long longitude,
                                                           long latitude,
                                                           int width, int depth,
                                                           ushort **result)
{
    if (!profiles)
        return ERR_NODATA;

//��� Determine original arc-second seperation to convert to
//��� a 1 arc-second seperation in X and in Y
    long arc_seconds_x, arc_seconds_y;
    if (ground_units == UNITS_METERS)
    {
        arc_seconds_x = (long)(axis[0] / 30.0);
        arc_seconds_y = (long)(axis[1] / 30.0);
    }
    else if (ground_units == UNITS_ARCSECONDS)
    {
        arc_seconds_x = (long)axis[0];
        arc_seconds_y = (long)axis[1];
    }
    else
        return ERR_NOTSUPPORTED;

    if (arc_seconds_x <= 0
        || arc_seconds_y <= 0)
        return ERR_NOTSUPPORTED;

//��� Check for height multiplier
    double height_factor;
    if (elev_units == UNITS_FEET)
    {
        height_factor = (axis[2]/3.0);
    }
    else if (elev_units == UNITS_METERS)
    {
        height_factor = axis[2];
    }
    else
        return ERR_NOTSUPPORTED;

    if (height_factor <= 0.0)
        return ERR_NOTSUPPORTED;

//��� Setup
    int start_profile=0;
    int start_element=0;
    int work_longitude = longitude -  (longitude % arc_seconds_x);
    int work_latitude = latitude - (latitude % arc_seconds_y);

//��� Check to make sure the region being requested is in the
//��� currently loaded data.
    if ((work_longitude < xy_corners[0])
        || ((work_longitude + width) > xy_corners[4])
        || (work_latitude < xy_corners[1])
        || ((work_latitude + depth) > xy_corners[5]))
    {
        return ERR_DATAOVERRUN;
    }

//��� Allocate space
    ushort *new_data = new ushort[width * depth];
    if (!new_data)
    {
        return ERR_NOMEMORY;
    }
    memset(new_data,0,sizeof(ushort)*width*depth);
    *result = new_data;

//��� Compute start point
    start_element = (work_latitude - (int)xy_corners[1]) / arc_seconds_y;
    start_profile = (work_longitude - (int)xy_corners[0]) / arc_seconds_x;

    int new_latcount = depth / arc_seconds_y;
    int new_longcount = width / arc_seconds_x;

//��� do interpolation, and fill in the data....
    for (int i=0; i < new_latcount; i++)
    {
        for (int j=0; j < new_longcount; j++)
        {
            double left = (double) profiles[j+start_profile].data[i+start_element];
            double right= (double) profiles[j+start_profile+1].data[(i+start_element)];
            double next_left = (double) profiles[j+start_profile].data[i+start_element+1];
            double next_right = (double) profiles[(j+start_profile+1)].data[(i+start_element+1)];
            double leftstep = (next_left - left) / (double)arc_seconds_y;
            double rightstep = (next_right - right) / (double)arc_seconds_y;

            for (int l=0; l < arc_seconds_y; l++)
            {
                double this_pt = left;
                double next_pt = right;

                double steps = (next_pt - this_pt) / (double)arc_seconds_x;

                for (int k=0; k < arc_seconds_x; k++)
                {
                    int xpos = (j*arc_seconds_x) + k;
                    int ypos = (i*arc_seconds_y) + l;
                    //
                    // if we are not overshooting the end of the target data area,
                    // move the data to the dest.
                    //
                    if ((xpos < width) && (ypos < depth))
                    {
                        new_data[ypos * width + xpos] = (ushort)((this_pt*height_factor)+0.5);
                    }
                    this_pt += steps;

                }
                left += leftstep;
                right += rightstep;
            }
        }
    }

    return ERR_NONE;
}


//�������������������������������������������������������������������������Ŀ
// USGSFileParseDEM - get_error_string                                      �
//���������������������������������������������������������������������������
const char *USGSFileParseDEM::get_error_string(usgs_error err)
{
    switch (err)
    {
        case ERR_INVALIDPARMS:
            return "Invalid parameters were given to the reader";
        case ERR_FILEERROR:
            return "A file error occurred";
        case ERR_NOPROFILES:
        case ERR_INVALIDPROFILE:
            return "Invalid profile counts were encountered";
        case ERR_NOMEMORY:
            return "Failed to allocate needed memory";
        case ERR_UNEXPECTEDEOF:
            return "The end-of-file was encountered before it was expected";
        case ERR_TOKENTOOLONG:
            return "A token was encountered that was too long for the token buffer";
        case ERR_INVALIDTOKEN:
            return "An invalide token was encountered";
        case ERR_NODATA:
            return "USGS data has not been read";
        case ERR_NOTSUPPORTED:
            return "This version of USGS data is not supported";
        case ERR_DATAOVERRUN:
            return "Requested data not fully within data set";
    }

    return NULL;
}

//��� eof - eshtusgs.cpp ���

