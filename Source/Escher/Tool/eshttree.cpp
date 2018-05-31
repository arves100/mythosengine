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
// eshttree.cpp
//
// Escher Tool tree view class, which is a child of the view class.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "stdafx.h"
#include "eshtool.h"
#include "eshtdoc.h"
#include "eshtview.h"

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

#define TREEIMG_SCENE       0
#define TREEIMG_SCENES      1
#define TREEIMG_MESH        2
#define TREEIMG_MESHS       3
#define TREEIMG_LIGHT       4
#define TREEIMG_LIGHTS      5
#define TREEIMG_CAMERA      6
#define TREEIMG_CAMERAS     7

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern ToolApp theApp;

//�������������������������������������������������������������������������Ŀ
// ToolTree                                                                 �
//���������������������������������������������������������������������������

BEGIN_MESSAGE_MAP(ToolTree, CTreeCtrl)
        //{{AFX_MSG_MAP(ToolTree)
        ON_WM_RBUTTONDOWN()
        ON_WM_LBUTTONDBLCLK()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//�������������������������������������������������������������������������Ŀ
// Image List array                                                         �
//���������������������������������������������������������������������������

static UINT ToolTree_icons[] =
{
    IDR_ICON_SCENE,
    IDR_ICON_SCENES,
    IDR_ICON_MESH,
    IDR_ICON_MESHS,
    IDR_ICON_LIGHT,
    IDR_ICON_LIGHTS,
    IDR_ICON_CAMERA,
    IDR_ICON_CAMERAS,
};

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//������������������������� Constructor/Destructor ��������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolTree - Constructor                                                   �
//���������������������������������������������������������������������������
ToolTree::ToolTree()
{
}


//�������������������������������������������������������������������������Ŀ
// ToolTree - Destructor                                                    �
//���������������������������������������������������������������������������
ToolTree::~ToolTree()
{
}



//���������������������������������������������������������������������������
//������������������������������� Diagnostics �������������������������������
//���������������������������������������������������������������������������



//���������������������������������������������������������������������������
//������������������������������� Operations ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolTree - Create                                                        �
//���������������������������������������������������������������������������
BOOL ToolTree::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
    HICON   i;

        if (!CTreeCtrl::Create(dwStyle, rect, pParentWnd, nID))
        return FALSE;

    // Create imagelist for tree
    if (!imList.Create(16,16,TRUE,3,2))
    {
        DestroyWindow();
        return FALSE;
    }

    // Load icons and setup image list
    for(int c=0; c < sizeof(ToolTree_icons)/sizeof(UINT); c++)
    {
        i=theApp.LoadIcon(ToolTree_icons[c]);
        imList.Add(i);
    }

    SetImageList(&imList,TVSIL_NORMAL);

    return TRUE;
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// ToolTree - build_mesh_tree                                               �
//���������������������������������������������������������������������������
void ToolTree::build_mesh_tree(HTREEITEM hp, TV_INSERTSTRUCT *i,
                               EschMeshDraw *mptr, int *count)
{
    HTREEITEM   h;

    for (; mptr; mptr = (EschMeshDraw*) mptr->next())
    {
        i->hParent=hp;
        i->item.pszText = mptr->name;
        i->item.cchTextMax = strlen(mptr->name);
        i->item.lParam = TREE_MESH_BASE + ((*count)++);
        h=InsertItem(i);
        if (mptr->child())
        {
            build_mesh_tree(h,i,(EschMeshDraw*)mptr->child(),count);
        }
        Expand(h,TVE_TOGGLE);
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolTree - RebuildTreeList                                               �
//���������������������������������������������������������������������������
void ToolTree::RebuildTreeList(void)
{
    int             c;
    HTREEITEM       h;
    HTREEITEM       hscene;
    TV_INSERTSTRUCT i;

    ToolDoc *pDoc = (ToolDoc*)((CView*)GetParent())->GetDocument();
    ASSERT_VALID(pDoc);

    DeleteAllItems();

    i.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

//��� Scene
    i.hParent = NULL;
    i.hInsertAfter = TVI_LAST;
    i.item.iImage = TREEIMG_SCENE;
    i.item.iSelectedImage = TREEIMG_SCENES;
    i.item.pszText = pDoc->name;
    i.item.cchTextMax = strlen(pDoc->name);
    i.item.lParam = TREE_SCENE_BASE + 1;
    hscene = InsertItem(&i);

//��� Meshes
    i.hParent = hscene;
    i.hInsertAfter = TVI_LAST;
    i.item.iImage = TREEIMG_MESH;
    i.item.iSelectedImage = TREEIMG_MESHS;
    i.item.pszText = "Meshes";
    i.item.cchTextMax = sizeof("Meshes");
    i.item.lParam = TREE_MESH_BASE;
    h = InsertItem(&i);

    i.hInsertAfter = TVI_SORT;
    c=1;
    build_mesh_tree(h,&i,pDoc->meshes,&c);
    Expand(h,TVE_TOGGLE);

//��� Lights
    i.hParent = hscene;
    i.hInsertAfter = TVI_LAST;
    i.item.iImage = TREEIMG_LIGHT;
    i.item.iSelectedImage = TREEIMG_LIGHTS;
    i.item.pszText = "Lights";
    i.item.cchTextMax = sizeof("Lights");
    i.item.lParam = TREE_LIGHT_BASE;
    h = InsertItem(&i);

    i.hParent = h;
    i.hInsertAfter = TVI_SORT;
    c=1;
    for (EschLight *lptr=pDoc->lights; lptr; c++, lptr = lptr->next())
    {
        i.item.pszText = lptr->name;
        i.item.cchTextMax = strlen(lptr->name);
        i.item.lParam = TREE_LIGHT_BASE + c;
        InsertItem(&i);
    }
    Expand(i.hParent,TVE_TOGGLE);

//��� Cameras
    i.hParent = hscene;
    i.hInsertAfter = TVI_LAST;
    i.item.iImage = TREEIMG_CAMERA;
    i.item.iSelectedImage = TREEIMG_CAMERAS;
    i.item.pszText = "Cameras";
    i.item.cchTextMax = sizeof("Cameras");
    i.item.lParam = TREE_CAMERA_BASE;
    h = InsertItem(&i);

    i.hParent = h;
    i.hInsertAfter = TVI_SORT;
    c=1;
    for (EschCameraEx *cptr=pDoc->cameras; cptr;
         c++, cptr = (EschCameraEx*)cptr->next())
    {
        i.item.pszText = cptr->name;
        i.item.cchTextMax = strlen(cptr->name);
        i.item.lParam = TREE_CAMERA_BASE + c;
        InsertItem(&i);
    }
    Expand(i.hParent,TVE_TOGGLE);

    Expand(hscene,TVE_TOGGLE);
}


//�������������������������������������������������������������������������Ŀ
// ToolTree - GetSelected                                                   �
//���������������������������������������������������������������������������
dword ToolTree::GetSelected(void)
{
    HTREEITEM       h;
    TV_ITEM         i;

    h = GetSelectedItem();

    if (!h)
        return 0;

    i.mask = TVIF_HANDLE;
    i.hItem = h;

    if (!GetItem(&i))
        return 0;

    return (dword)i.lParam;
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// ToolTree - get_mesh_tree                                                 �
//���������������������������������������������������������������������������
EschMeshDraw *ToolTree::get_mesh_tree(EschMeshDraw *mptr, int *count)
{
    for (; mptr; mptr = (EschMeshDraw*) mptr->next())
    {
        if (*count <= 1)
            return mptr;

        (*count)--;

        if (mptr->child())
        {
            EschMeshDraw *m = get_mesh_tree((EschMeshDraw*)mptr->child(),count);
            if (m)
                return m;
        }
    }

    return NULL;
}


//�������������������������������������������������������������������������Ŀ
// ToolTree - GetMeshItem                                                   �
//���������������������������������������������������������������������������
EschMeshDraw *ToolTree::GetMeshItem(dword i)
{
    if ((i & 0xffff0000) != TREE_MESH_BASE)
        return NULL;

    i &= 0xffff;

    if (!i)
        return NULL;

    ToolDoc *pDoc = (ToolDoc*)((CView*)GetParent())->GetDocument();
    ASSERT_VALID(pDoc);

    EschMeshDraw *msh=pDoc->meshes;

    return get_mesh_tree(pDoc->meshes,(int*)&i);
}


//�������������������������������������������������������������������������Ŀ
// ToolTree - GetLightItem                                                  �
//���������������������������������������������������������������������������
EschLight *ToolTree::GetLightItem(dword i)
{
    if ((i & 0xffff0000) != TREE_LIGHT_BASE)
        return NULL;

    i &= 0xffff;

    if (!i)
        return NULL;

    ToolDoc *pDoc = (ToolDoc*)((CView*)GetParent())->GetDocument();
    ASSERT_VALID(pDoc);

    EschLight *lgt=pDoc->lights;

    while(lgt != NULL)
    {
        if (i <= 1)
            return lgt;

        lgt=lgt->next();
        i--;
    }

    return NULL;
}


//�������������������������������������������������������������������������Ŀ
// ToolTree - GetCameraItem                                                 �
//���������������������������������������������������������������������������
EschCameraEx *ToolTree::GetCameraItem(dword i)
{
    if ((i & 0xffff0000) != TREE_CAMERA_BASE)
        return NULL;

    i &= 0xffff;

    if (!i)
        return NULL;

    ToolDoc *pDoc = (ToolDoc*)((CView*)GetParent())->GetDocument();
    ASSERT_VALID(pDoc);

    EschCameraEx *cam=pDoc->cameras;

    while(cam != NULL)
    {
        if (i <= 1)
            return cam;

        cam=(EschCameraEx*)cam->next();
        i--;
    }

    return NULL;
}



//���������������������������������������������������������������������������
//���������������������������� Message Handlers �����������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolTree - OnLButtonDblClk                                               �
//���������������������������������������������������������������������������
void ToolTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
//��� Select item (if over one)
    UINT        flags;
    HTREEITEM   h;

    h = HitTest( point, &flags);

    if (flags & TVHT_ONITEM)
    {
        SelectItem(h);
        ((ToolView*)GetParent())->EditProperties();
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolTree - OnRButtonDown                                                 �
//���������������������������������������������������������������������������
void ToolTree::OnRButtonDown(UINT nFlags, CPoint point)
{
//��� Select item (if over one)
    UINT        flags;
    HTREEITEM   h;

    h = HitTest( point, &flags);

    if (flags & TVHT_ONITEM)
        SelectItem(h);

//��� Right-mouse menu
    CRect       rct;
    CMenu       rMenu;

    GetWindowRect (&rct);

    point.x += rct.left;
    point.y += rct.top;

    //��� New Submenu
    CMenu   newMenu;
    newMenu.CreatePopupMenu();

    newMenu.AppendMenu(MF_STRING, ID_EDIT_NEW_CAM, "Camera...");
    newMenu.AppendMenu(MF_STRING, ID_EDIT_NEW_LIGHT, "Light...");

    //��� Menu
    rMenu.CreatePopupMenu();
    rMenu.AppendMenu(MF_STRING, ID_VIEW_ATTACHCAM, "Attach Camera");
    rMenu.AppendMenu(MF_SEPARATOR);
    rMenu.AppendMenu(MF_STRING, ID_FILE_IMPORT, "Import...");
    rMenu.AppendMenu(MF_STRING | MF_POPUP, (unsigned int) newMenu.m_hMenu, "New");
    rMenu.AppendMenu(MF_SEPARATOR);
    rMenu.AppendMenu(MF_STRING, ID_EDIT_DELETE, "Delete");
    rMenu.AppendMenu(MF_SEPARATOR);
    rMenu.AppendMenu(MF_STRING, ID_EDIT_PROP, "Properties...");

    ASSERT(AfxGetMainWnd());
    rMenu.TrackPopupMenu( TPM_RIGHTBUTTON | TPM_LEFTALIGN,
                          point.x, point.y,
                          AfxGetMainWnd());
    rMenu.DestroyMenu();
    newMenu.DestroyMenu();
}

//��� eof - eshttree.cpp ���
