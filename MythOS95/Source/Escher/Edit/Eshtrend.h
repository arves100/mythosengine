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
// eshtrend.h
//
// Terrain View support class.
//
// The Render class controls the 3D viewer window for the editor.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

typedef enum _rndctrl_mode_type
{
    RNDCTRL_NONE            =0,
    RNDCTRL_HOVER           =1,
    RNDCTRL_ROTATEXY        =2,
    RNDCTRL_MOVEXY          =3,
    RNDCTRL_ROTMOVEZ        =4,
    RNDCTRL_LIGHTXY         =5,
    RNDCTRL_LIGHTBRIGHT     =6,
} rnd_ctrl_mode_type;

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// TerrEditRender                                                           �
//���������������������������������������������������������������������������

class TerrEditRender : public CWnd
{
// Construction
public:
        TerrEditRender();

// Attributes
public:
    EschTerrainEx       terr;
    VngoPal             *pal;

// Operations
public:
    void UpdateRender();

    void SetMode(rnd_ctrl_mode_type m);
    rnd_ctrl_mode_type GetMode() { return mode; }

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(TerrEditRender)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~TerrEditRender();

protected:
    rnd_ctrl_mode_type  mode;
    int                 lastx, lasty;
    int                 capture;
    BITMAPINFO          *bmi;
    BYTE                *gmap;
    VngoVport           *gvp;

    void setup_vport(int width, int height);
    void release_vport();

        // Generated message map functions
protected:
        //{{AFX_MSG(TerrEditRender)
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnPaint();
        afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//��� eof - eshtrend.h ���
