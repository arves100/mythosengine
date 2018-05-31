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
//                             *** Escher Tool ***
//
// Chuck Walbourn
//
// eshtdoc.h
//
// Escher Tool Document Class
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

class ToolDoc : public CDocument
{
protected: // create from serialization only
        ToolDoc();
        DECLARE_DYNCREATE(ToolDoc)

// Attributes
public:

    // Scene information
    char        name[ESCH_MAX_NAME];
    char        desc[256];
    char        auth[256];
    char        copy[256];

    ulong           ncameras;
    EschCameraEx    *cameras;

    ulong           nlights;
    EschLight       *lights;

    ulong           nmeshes;
    EschMeshDraw    *meshes;

    // Support data
    char            pfname[256];
    VngoPal         *palette;

    HPALETTE        hpal;

    enum
    {
        COMPRESS    =0x1,
        TRUECOLOR   =0x2,
        USE15BIT    =0x4,
        FLOATING    =0x8,
    };

    dword           flags;

// Operations
public:
    BOOL LoadPalette(const char *fname);
    void GetCounts(ulong *ncams,
                   ulong *nvlgts,
                   ushort *nfplgts, ushort *nfalgts, ushort *nfslgts,
                   ulong *nplgts, ushort *nalgts, ushort *nslgts,
                   ulong *nobjs);

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ToolDoc)
        public:
        virtual BOOL OnNewDocument();
        virtual void DeleteContents();
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~ToolDoc();
        virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    int count_mesh(EschMeshDraw *msh);
    esch_error_codes serialize_store_mesh(XFParseIFF *iff, EschMeshDraw *msh);

// Generated message map functions
protected:
        //{{AFX_MSG(ToolDoc)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//��� eof - eshtdoc.h ���
