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
// eshttree.h
//
// Escher Tool tree view class, which is a child of the view class.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

#define TREE_SCENE_BASE     0x00010000
#define TREE_CAMERA_BASE    0x00020000
#define TREE_MESH_BASE      0x00030000
#define TREE_LIGHT_BASE     0x00040000

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolTree                                                                 �
//���������������������������������������������������������������������������

class ToolTree : public CTreeCtrl
{
// Construction
public:
        ToolTree();

// Attributes
public:

// Operations
public:
    void RebuildTreeList();
    dword GetSelected(void);
    EschMeshDraw *GetMeshItem(dword i);
    EschLight *GetLightItem(dword i);
    EschCameraEx *GetCameraItem(dword i);


// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ToolTree)
        public:
        virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~ToolTree();

protected:
    CImageList  imList;

    void build_mesh_tree(HTREEITEM hp, TV_INSERTSTRUCT *i, EschMeshDraw *mptr, int *count);
    EschMeshDraw *get_mesh_tree(EschMeshDraw *mptr, int *count);

        // Generated message map functions
protected:

        //{{AFX_MSG(ToolTree)
        afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

//��� eof - eshttree.h ���
