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
// eshtlist.cpp
//
// Terrain View support class
//
// The List class handles the Texture definition list box.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#include "stdafx.h"
#include "eshtedit.h"

#include "eshtmfrm.h"
#include "eshtdoc.h"
#include "eshtview.h"

//���������������������������������������������������������������������������
//
//                                 Data
//
//���������������������������������������������������������������������������

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//�������������������������������������������������������������������������Ŀ
// TerrEditList                                                             �
//���������������������������������������������������������������������������
BEGIN_MESSAGE_MAP(TerrEditList, CListBox)
        //{{AFX_MSG_MAP(TerrEditList)
        ON_WM_RBUTTONDOWN()
        ON_WM_MOUSEMOVE()
        ON_WM_LBUTTONDBLCLK()
        ON_WM_LBUTTONDOWN()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//������������������������� Constructor/Destructor ��������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// TerrEditList - Constructor                                               �
//���������������������������������������������������������������������������
TerrEditList::TerrEditList()
{
}

//�������������������������������������������������������������������������Ŀ
// TerrEditList - Destructor                                                �
//���������������������������������������������������������������������������
TerrEditList::~TerrEditList()
{
}



//���������������������������������������������������������������������������
//������������������������������� Operations ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// TerrEditList - UpdateContents                                            �
//���������������������������������������������������������������������������
void TerrEditList::UpdateContents()
{
    if (!m_hWnd)
        return;

    TerrEditDoc* pDoc = (TerrEditDoc *) ((CView *) GetParent())->GetDocument();
    ASSERT_VALID(pDoc);

    char buff[255];
    int err = 0;

    int i = GetCurSel();
    if (i != LB_ERR)
    {
        strcpy(buff, pDoc->txtName[i]);
    }
    else
        err = 1;



    ResetContent();
    for(i=0; i < pDoc->txtNumb; i++)
        AddString(pDoc->txtName[i]);

    // Set on the currently selected here!


    if (!err)
    {

        for (i=0; i< pDoc->txtNumb; i++)
        {
            if (!strcmp(buff, pDoc->txtName[i]))
            {
                SetCurSel(i);
                break;
            }
        }
    }

}


//���������������������������������������������������������������������������
//���������������������������� Message Handlers �����������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// TerrEditList - OnLButtonDblClk                                           �
//���������������������������������������������������������������������������
void TerrEditList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CWnd *w = AfxGetMainWnd();

    BOOL flag;
    int i = ItemFromPoint(point, flag);
    SetCurSel(i);

    if ((GetCurSel() == LB_ERR) || nFlags & MK_CONTROL)
        w->SendMessage(WM_COMMAND, ID_SURF_DEFINETXT, NULL);
    else
        w->SendMessage(WM_COMMAND, ID_SURF_EDITTXT, NULL);

}


//�������������������������������������������������������������������������Ŀ
// TerrEditList - OnLButtonDown                                             �
//���������������������������������������������������������������������������
void TerrEditList::OnLButtonDown(UINT nFlags, CPoint point)
{

    BOOL flag;
    int i = ItemFromPoint(point, flag);
    SetCurSel(i);

    TerrEditDoc* pDoc = (TerrEditDoc *) ((CView *) GetParent())->GetDocument();

    pDoc->UpdateAllViews(0, HINT_UPDATETXTLIST, 0);

        CListBox::OnLButtonDown(nFlags, point);
}


//�������������������������������������������������������������������������Ŀ
// TerrEditList - OnRButtonDown                                             �
//���������������������������������������������������������������������������
void TerrEditList::OnRButtonDown(UINT nFlags, CPoint point)
{
    CRect   rct;
    GetWindowRect (&rct);

    point.x += rct.left;
    point.y += rct.top;

    CMenu   rMenu;

    rMenu.CreatePopupMenu();
    rMenu.AppendMenu(MF_STRING, ID_SURF_DEFINETXT, "Define Texture...");
    rMenu.AppendMenu(MF_STRING, ID_SURF_EDITTXT, "Edit Texture...");
    rMenu.AppendMenu(MF_STRING, ID_SURF_DELETETXT, "Delete Texture");
    rMenu.AppendMenu(MF_SEPARATOR);
    rMenu.AppendMenu(MF_STRING, ID_SURF_LOADTXT, "Load Textures...");
    rMenu.AppendMenu(MF_STRING, ID_SURF_SAVETXT, "Save Textures...");

    ASSERT(AfxGetMainWnd());
    rMenu.TrackPopupMenu( TPM_RIGHTBUTTON | TPM_LEFTALIGN,
                          point.x, point.y,
                          AfxGetMainWnd());
    rMenu.DestroyMenu();
}


//�������������������������������������������������������������������������Ŀ
// TerrEditList - OnMouseMove                                               �
//���������������������������������������������������������������������������
void TerrEditList::OnMouseMove(UINT nFlags, CPoint point)
{
    ((TerrMainFrame *) AfxGetMainWnd())->SetMessageText("Ready");

        CListBox::OnMouseMove(nFlags, point);
}


//�������������������������������������������������������������������������Ŀ
// TerrColorList - Constructor                                              �
//���������������������������������������������������������������������������
TerrColorList::TerrColorList()
{
}

//�������������������������������������������������������������������������Ŀ
// TerrColorList - Destructor                                               �
//���������������������������������������������������������������������������
TerrColorList::~TerrColorList()
{
}


BEGIN_MESSAGE_MAP(TerrColorList, CListBox)
        //{{AFX_MSG_MAP(TerrColorList)
        ON_WM_LBUTTONDBLCLK()
        ON_WM_MOUSEMOVE()
        ON_WM_RBUTTONDOWN()
        ON_WM_LBUTTONDOWN()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//�������������������������������������������������������������������������Ŀ
// TerrColorList - OnLButtonDblClk                                          �
//���������������������������������������������������������������������������
void TerrColorList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CWnd *w = AfxGetMainWnd();

#if 0
    if ((GetCurSel() == LB_ERR) || nFlags & MK_CONTROL)
        w->SendMessage(WM_COMMAND, ID_SURF_DEFCLR, NULL);
    else
        w->SendMessage(WM_COMMAND, ID_SURF_EDITCLR, NULL);
#else

    BOOL flag;
    int i = ItemFromPoint(point, flag);
    SetCurSel(i);

    if ((GetCurSel() == LB_ERR) || nFlags & MK_CONTROL)
        w->SendMessage(WM_COMMAND, ID_SURF_DEFCLR, NULL);
    else
        w->SendMessage(WM_COMMAND, ID_SURF_EDITCLR, NULL);

#endif
}

//�������������������������������������������������������������������������Ŀ
// TerrColorList - OnMouseMove                                              �
//���������������������������������������������������������������������������
void TerrColorList::OnMouseMove(UINT nFlags, CPoint point)
{
    ((TerrMainFrame *) AfxGetMainWnd())->SetMessageText("Ready");

        CListBox::OnMouseMove(nFlags, point);
}

//�������������������������������������������������������������������������Ŀ
// TerrColorList - OnRButtonDown                                            �
//���������������������������������������������������������������������������
void TerrColorList::OnRButtonDown(UINT nFlags, CPoint point)
{
    CRect   rct;
    GetWindowRect (&rct);

    point.x += rct.left;
    point.y += rct.top;

    CMenu   rMenu;

    rMenu.CreatePopupMenu();
    rMenu.AppendMenu(MF_STRING, ID_SURF_DEFCLR, "Define Color...");
    rMenu.AppendMenu(MF_STRING, ID_SURF_EDITCLR, "Edit Color...");
    rMenu.AppendMenu(MF_STRING, ID_SURF_DELETECLR, "Delete Color");
    rMenu.AppendMenu(MF_SEPARATOR);
    rMenu.AppendMenu(MF_STRING, ID_SURF_LOADCLR, "Load Colors...");
    rMenu.AppendMenu(MF_STRING, ID_SURF_SAVECLR, "Save Colors...");

    ASSERT(AfxGetMainWnd());
    rMenu.TrackPopupMenu( TPM_RIGHTBUTTON | TPM_LEFTALIGN,
                          point.x, point.y,
                          AfxGetMainWnd());
    rMenu.DestroyMenu();
}


//�������������������������������������������������������������������������Ŀ
// TerrColorList - OnLButtonDown                                            �
//���������������������������������������������������������������������������
void TerrColorList::OnLButtonDown(UINT nFlags, CPoint point)
{
    BOOL flag;
    int i = ItemFromPoint(point, flag);
    SetCurSel(i);

    TerrEditDoc* pDoc = (TerrEditDoc *) ((CView *) GetParent())->GetDocument();

    pDoc->UpdateAllViews(0, HINT_UPDATECLRLIST, 0);

        CListBox::OnLButtonDown(nFlags, point);
}


//�������������������������������������������������������������������������Ŀ
// TerrColorList - UpdateContents                                           �
//���������������������������������������������������������������������������
void TerrColorList::UpdateContents()
{
    if (!m_hWnd)
        return;

    TerrEditDoc* pDoc = (TerrEditDoc *) ((CView *) GetParent())->GetDocument();
    ASSERT_VALID(pDoc);
    char buff[255];

    int err = 0;
    int i = GetCurSel();
    if (i != LB_ERR)
    {
        strcpy(buff, pDoc->colorName[i]);
    }
    else
        err = 1;

    ResetContent();
    for(i=0; i < pDoc->colorNumb; i++)
        AddString(pDoc->colorName[i]);


    if (!err)
    {
        // Set on the currently selected here!
        for (i=0; i< pDoc->colorNumb; i++)
        {
            if (!strcmp(buff, pDoc->colorName[i]))
            {
                SetCurSel(i);
                break;
            }
        }
    }
}

//��� eof - eshtlist.cpp ���

