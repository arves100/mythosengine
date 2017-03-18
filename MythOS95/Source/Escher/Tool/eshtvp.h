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
// eshtvp.h
//
// Escher Tool viewport class, which is a child of the view class.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

typedef enum _vport_type {
    VPORT_NONE                      =0,
    VPORT_CAMERA                    =1,
} vport_type;

typedef enum _rndctrl_mode_type
{
    RNDCTRL_NONE            =0,
    RNDCTRL_ROTATEXY        =1,
    RNDCTRL_MOVEXY          =2,
    RNDCTRL_ROTMOVEZ        =3,
    RNDCTRL_ROTATEIJ        =4,
    RNDCTRL_MOVEIJ          =5,
    RNDCTRL_ROTMOVEK        =6,
    RNDCTRL_LIGHTXY         =7,
    RNDCTRL_LIGHTBRIGHT     =8,
} rnd_ctrl_mode_type;

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolVPort                                                                �
//���������������������������������������������������������������������������

class ToolVPort : public CWnd
{
// Construction
public:
        ToolVPort();

    enum
    {
        SPHERE_EXTS = 0x1,
        BOX_EXTS    = 0x2,
    };

// Attributes
public:
    vport_type  vptype;
    EschCameraEx *cam;
    dword       cflags;
    dword       extra_flags;

// Operations
public:
    void SetCamera(EschCameraEx *c);
    void Render(void);
    void SetMode(rnd_ctrl_mode_type m, void *t=0);
    rnd_ctrl_mode_type GetMode() { return mode; }
    void *GetModeTarget() { return modeTarget; }

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ToolVPort)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~ToolVPort();

protected:
    rnd_ctrl_mode_type  mode;
    void                *modeTarget;
    INT                 lastx, lasty;
    int                 capture;
    BITMAPINFO          *bmi;
    BYTE                *gmap;
    VngoVport           *gvp;

    void setup_vport(int width, int height);
    void release_vport();
    void extents_render(EschMeshDraw *ptr);

        // Generated message map functions
protected:
        //{{AFX_MSG(ToolVPort)
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnPaint();
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//��� eof - eshtvp.h ���
