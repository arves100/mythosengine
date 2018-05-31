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
// eshtusgs.h
//
// USGS DEM Support class Definitions
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// USGSProfileDEM                                                           �
//���������������������������������������������������������������������������
class USGSProfileDEM
{
public:
    //��������������������������������������������������������������������Ŀ
    // Data                                                                �
    //����������������������������������������������������������������������
    ulong   row_id;
    ulong   column_id;

    ulong   rows;
    ulong   columns;

    ushort  *data;

    //��������������������������������������������������������������������Ŀ
    // Constructors/Destructors                                            �
    //����������������������������������������������������������������������
    USGSProfileDEM() :
        row_id(0), column_id(0), rows(0), columns(0), data(0) {}
    ~USGSProfileDEM()
    {
        if (data)
        {
            delete [] data;
            data = 0;
        }
    }
};


//�������������������������������������������������������������������������Ŀ
// USGSFileParseDEM                                                         �
//���������������������������������������������������������������������������
class USGSFileParseDEM
{
public:
    //��������������������������������������������������������������������Ŀ
    // Equates                                                             �
    //����������������������������������������������������������������������
    enum usgs_error
    {
        ERR_NONE            =0,
        ERR_INVALIDPARMS    =1,
        ERR_FILEERROR       =2,
        ERR_NOPROFILES      =3,
        ERR_INVALIDPROFILE  =4,
        ERR_NOMEMORY        =5,
        ERR_UNEXPECTEDEOF   =6,
        ERR_TOKENTOOLONG    =7,
        ERR_INVALIDTOKEN    =8,
        ERR_NODATA          =9,
        ERR_NOTSUPPORTED    =10,
        ERR_DATAOVERRUN     =11,
    };

    enum
    {
        UNITS_RADIANS       =0,
        UNITS_FEET          =1,
        UNITS_METERS        =2,
        UNITS_ARCSECONDS    =3,
    };

protected:
    //��������������������������������������������������������������������Ŀ
    // Implementation                                                      �
    //����������������������������������������������������������������������
    enum
    {
        IS_UINT   = 0x1,
        IS_DOUBLE = 0x2,
    };

    struct Token
    {
        ulong   flags;
        ushort  a;
        double  b;
    };

    XFileDiskBuf    xf;

    usgs_error skip_n_tokens(ulong n);
    usgs_error read_next_token(Token *tk);
    usgs_error read_header_info();
    usgs_error read_profile(USGSProfileDEM *prof);

public:
    //��������������������������������������������������������������������Ŀ
    // Data                                                                �
    //����������������������������������������������������������������������
    ushort          level_code;         // 1, 2, 3 for DEM quality level
    ushort          ground_units;       // Units of measure for ground
    ushort          elev_units;         // Units of measure for elevation
    ushort          polygon_sides;      // Number of sides (should be 4)
    double          xy_corners[8];      // Coords of each corner
    double          min_elev;           // Minimum elevation
    double          max_elev;           // Maximum elevation
    double          axis[3];            // Spatal-axis for data set (X, Y, Z)

    ushort          profile_rows;       // Profiles
    ushort          profile_columns;
    USGSProfileDEM  *profiles;

    char            name[40];           // Text
    char            comment[104];

    //��������������������������������������������������������������������Ŀ
    // Constructors/Destructors                                            �
    //����������������������������������������������������������������������
    USGSFileParseDEM();
    ~USGSFileParseDEM();

    //��������������������������������������������������������������������Ŀ
    // Operations                                                          �
    //����������������������������������������������������������������������
    usgs_error read(const char *filename);

    usgs_error expand_data(long longitude, long latitude,
                           int width, int depth, ushort **result);

    const char *get_error_string(usgs_error err);
};

//��� eof - eshtusgs.h ���

