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
// eshtlist.h
//
// Terrain View support class
//
// The List class handles the Texture definition list box.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// TerrEditList                                                             �
//���������������������������������������������������������������������������

class TerrEditList : public CListBox
{
// Construction
public:
        TerrEditList();

// Attributes
public:

// Operations
public:
    void UpdateContents();

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(TerrEditList)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~TerrEditList();

        // Generated message map functions
protected:
        //{{AFX_MSG(TerrEditList)
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};



//�������������������������������������������������������������������������Ŀ
// TerrColorList                                                            �
//���������������������������������������������������������������������������
class TerrColorList : public CListBox
{
// Construction
public:
        TerrColorList();

// Attributes
public:

// Operations
public:
    void UpdateContents();

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(TerrColorList)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~TerrColorList();

        // Generated message map functions
protected:
        //{{AFX_MSG(TerrColorList)
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};
//��� eof - eshtlist.h ���
