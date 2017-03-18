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
// eshtview.cpp
//
// Escher Tool view class.
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

//�������������������������������������������������������������������������Ŀ
// ToolView                                                                 �
//���������������������������������������������������������������������������
IMPLEMENT_DYNCREATE(ToolView, CView)

BEGIN_MESSAGE_MAP(ToolView, CView)
        //{{AFX_MSG_MAP(ToolView)
        ON_WM_SIZE()
        ON_COMMAND(ID_VIEW_RND_WIREFRAME, OnViewRndWireframe)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_WIREFRAME, OnUpdateViewRndWireframe)
        ON_COMMAND(ID_VIEW_RND_SOLID, OnViewRndSolid)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_SOLID, OnUpdateViewRndSolid)
        ON_COMMAND(ID_VIEW_RND_FLAT, OnViewRndFlat)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_FLAT, OnUpdateViewRndFlat)
        ON_COMMAND(ID_VIEW_RND_SMOOTH, OnViewRndSmooth)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_SMOOTH, OnUpdateViewRndSmooth)
        ON_COMMAND(ID_VIEW_RND_SPECULAR, OnViewRndSpecular)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_SPECULAR, OnUpdateViewRndSpecular)
        ON_COMMAND(ID_VIEW_RND_BACKFACE, OnViewRndBackface)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_BACKFACE, OnUpdateViewRndBackface)
        ON_COMMAND(ID_VIEW_RND_TEXTURES, OnViewRndTextures)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_TEXTURES, OnUpdateViewRndTextures)
        ON_COMMAND(ID_VIEW_RND_PERSPECTIVE, OnViewRndPerspective)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_PERSPECTIVE, OnUpdateViewRndPerspective)
        ON_COMMAND(ID_EDIT_PROP, OnEditProperties)
        ON_UPDATE_COMMAND_UI(ID_EDIT_PROP, OnUpdateEditProperties)
        ON_COMMAND(ID_VIEW_RND_ALL_LINES, OnViewRndShowAllLines)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_ALL_LINES, OnUpdateViewRndShowAllLines)
        ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
        ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
        ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
        ON_COMMAND(ID_VIEW_ROTXY, OnViewRotateXY)
        ON_UPDATE_COMMAND_UI(ID_VIEW_ROTXY, OnUpdateViewRotateXY)
        ON_COMMAND(ID_VIEW_MOVEXY, OnViewMoveXY)
        ON_UPDATE_COMMAND_UI(ID_VIEW_MOVEXY, OnUpdateViewMoveXY)
        ON_COMMAND(ID_VIEW_ROTMOVEZ, OnViewRotateMoveZ)
        ON_UPDATE_COMMAND_UI(ID_VIEW_ROTMOVEZ, OnUpdateViewRotateMoveZ)
        ON_COMMAND(ID_MESH_MOVEIJ, OnMeshMoveIJ)
        ON_UPDATE_COMMAND_UI(ID_MESH_MOVEIJ, OnUpdateMeshMoveIJ)
        ON_UPDATE_COMMAND_UI(ID_MESH_ROTIJ, OnUpdateMeshRotateIJ)
        ON_COMMAND(ID_MESH_ROTIJ, OnMeshRotateIJ)
        ON_COMMAND(ID_MESH_ROTMOVEK, OnMeshRotateMoveK)
        ON_UPDATE_COMMAND_UI(ID_MESH_ROTMOVEK, OnUpdateMeshRotateMoveK)
        ON_COMMAND(ID_LGT_ADJUSTXY, OnLightAdjustXY)
        ON_UPDATE_COMMAND_UI(ID_LGT_ADJUSTXY, OnUpdateLightAdjustXY)
        ON_UPDATE_COMMAND_UI(ID_LGT_ABRIGHT, OnUpdateLightIntensity)
        ON_COMMAND(ID_LGT_ABRIGHT, OnLightIntensity)
        ON_COMMAND(ID_VIEW_ATTACHCAM, OnViewAttachCamera)
        ON_UPDATE_COMMAND_UI(ID_VIEW_ATTACHCAM, OnUpdateViewAttachCamera)
        ON_COMMAND(ID_EDIT_NEW_CAM, OnEditNewCamera)
        ON_COMMAND(ID_EDIT_NEW_LIGHT, OnEditNewLight)
        ON_COMMAND(ID_VIEW_AUTOROTX, OnViewAutoRotateX)
        ON_UPDATE_COMMAND_UI(ID_VIEW_AUTOROTX, OnUpdateViewAutoRotateX)
        ON_COMMAND(ID_VIEW_AUTOROTY, OnViewAutoRotateY)
        ON_UPDATE_COMMAND_UI(ID_VIEW_AUTOROTY, OnUpdateViewAutoRotateY)
        ON_COMMAND(ID_VIEW_AUTOROTZ, OnViewAutoRotateZ)
        ON_UPDATE_COMMAND_UI(ID_VIEW_AUTOROTZ, OnUpdateViewAutoRotateZ)
        ON_COMMAND(ID_VIEW_AUTOFAST, OnViewAutoRotateFast)
        ON_UPDATE_COMMAND_UI(ID_VIEW_AUTOFAST, OnUpdateViewAutoRotateFast)
        ON_COMMAND(ID_VIEW_AUTOSLOW, OnViewAutoRotateSlow)
        ON_UPDATE_COMMAND_UI(ID_VIEW_AUTOSLOW, OnUpdateViewAutoRotateSlow)
        ON_COMMAND(ID_VIEW_AUTOOFF, OnViewAutoRotateOff)
        ON_COMMAND(ID_VIEW_RND_MSPACE, OnViewRndModelSpace)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_MSPACE, OnUpdateViewRndModelSpace)
        ON_COMMAND(ID_VIEW_SHOW_BOXEXTS, OnViewShowBoxExtents)
        ON_COMMAND(ID_VIEW_SHOW_SPHEXTS, OnViewShowSphereExtents)
        ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_SPHEXTS, OnUpdateViewShowSphereExtents)
        ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_BOXEXTS, OnUpdateViewShowBoxExtents)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_SORT, OnUpdateViewRndSort)
        ON_COMMAND(ID_VIEW_RND_SORT, OnViewRndSort)
        ON_COMMAND(ID_VIEW_RND_ALPHA, OnViewRndAlpha)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_ALPHA, OnUpdateViewRndAlpha)
        ON_COMMAND(ID_VIEW_RND_ORTHO, OnViewRndOrtho)
        ON_UPDATE_COMMAND_UI(ID_VIEW_RND_ORTHO, OnUpdateViewRndOrtho)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern dword AutoRotate;
extern float AutoRotateSpeed;
extern Chronometer Clock;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//������������������������� Constructor/Destructor ��������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolView - Constructor                                                   �
//���������������������������������������������������������������������������
ToolView::ToolView()
{
    vpmode=VPMODE_NONE;
}


//�������������������������������������������������������������������������Ŀ
// ToolView - Desctructor                                                   �
//���������������������������������������������������������������������������
ToolView::~ToolView()
{
}



//���������������������������������������������������������������������������
//������������������������������� Diagnostics �������������������������������
//���������������������������������������������������������������������������

#ifdef _DEBUG
//�������������������������������������������������������������������������Ŀ
// ToolView - AssertValid                                                   �
//���������������������������������������������������������������������������
void ToolView::AssertValid() const
{
        CView::AssertValid();
}


//�������������������������������������������������������������������������Ŀ
// ToolView - Dump                                                          �
//���������������������������������������������������������������������������
void ToolView::Dump(CDumpContext& dc) const
{
        CView::Dump(dc);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - GetDocument                                                   �
//���������������������������������������������������������������������������
ToolDoc* ToolView::GetDocument() // non-debug version is inline
{
        ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ToolDoc)));
        return (ToolDoc*)m_pDocument;
}
#endif //_DEBUG



//���������������������������������������������������������������������������
//������������������������������� Operations ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolView - OnIdle                                                        �
//���������������������������������������������������������������������������
void ToolView::OnIdle()
{
        ToolDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);

    if (pDoc->meshes)
    {
        if (AutoRotate)
        {
            float degrees = float(Flx16(Clock.check() << 6,0)) * AutoRotateSpeed;
            Clock.clear();

            for(EschMeshDraw *m=pDoc->meshes; m != NULL; m=(EschMeshDraw*)m->next())
            {
                if (AutoRotate & AUTOROTATE_X)
                    m->rotatex(degrees);
                if (AutoRotate & AUTOROTATE_Y)
                    m->rotatey(degrees);
                if (AutoRotate & AUTOROTATE_Z)
                    m->rotatez(degrees);
            }
        }

        for(EschMeshDraw *m=pDoc->meshes; m != NULL; m=(EschMeshDraw*)m->next())
        {
            m->animate();
        }

        switch (vpmode)
        {
            case VPMODE_NONE:
                break;
            case VPMODE_STANDARD:
                wVp[0].Render();
                wVp[0].Invalidate();
                break;
            default:
                ASSERT(0);
                break;
        }
    }
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// ToolView - ui_scene_properties                                           �
//���������������������������������������������������������������������������
BOOL ToolView::ui_scene_properties(int doupdate)
{
    ToolDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

//��� General
    ScenePropGeneralPage    gdlg;
    gdlg.m_name = pDoc->name;
    gdlg.m_name = gdlg.m_name.Left(ESCH_MAX_NAME);

    // Count cameras, lights, meshes
    pDoc->GetCounts((ulong*)&gdlg.m_ncameras,
                    (ulong*)&gdlg.m_nvlights,
                    (ushort*)&gdlg.m_nfplights,
                    (ushort*)&gdlg.m_nfalights,
                    (ushort*)&gdlg.m_nfslights,
                    (ulong*)&gdlg.m_nplights,
                    (ushort*)&gdlg.m_nalights,
                    (ushort*)&gdlg.m_nslights,
                    (ulong*)&gdlg.m_nmeshes);

//��� Misc
    ScenePropMiscPage       mdlg;
    mdlg.m_desc = pDoc->desc;
    mdlg.m_auth = pDoc->auth;
    mdlg.m_copy = pDoc->copy;

//��� Interact
    CPropertySheet  sh("Scene Properties");
    sh.AddPage(&gdlg);
    sh.AddPage(&mdlg);

//��� Store results, if OK
    if (sh.DoModal() == IDOK)
    {
        //��� General
        strncpy(pDoc->name,gdlg.m_name,ESCH_MAX_NAME);

        //��� Misc
        strncpy(pDoc->desc,mdlg.m_desc,ESCH_MAX_NAME);
        strncpy(pDoc->auth,mdlg.m_auth,ESCH_MAX_NAME);
        strncpy(pDoc->copy,mdlg.m_copy,ESCH_MAX_NAME);

        //��� Update views
        if (doupdate)
        {
            pDoc->SetModifiedFlag();
            pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST,NULL);
        }

        return TRUE;
    }

    return FALSE;
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// ToolView - ui_camera_properties                                          �
//���������������������������������������������������������������������������
BOOL ToolView::ui_camera_properties(EschCameraEx *cam, int doupdate)
{
    if (!cam)
        return FALSE;

    ToolDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

//��� General
    CameraPropGeneralPage   gdlg;
    gdlg.m_name = cam->name;
    gdlg.m_name = gdlg.m_name.Left(ESCH_MAX_NAME);

    EschPoint   pos;
    cam->get_position(&pos);
        gdlg.m_xpos = pos.x;
        gdlg.m_ypos = pos.y;
        gdlg.m_zpos = pos.z;

        gdlg.m_idir = cam->eye.dir.i;
        gdlg.m_jdir = cam->eye.dir.j;
        gdlg.m_kdir = cam->eye.dir.k;

        gdlg.m_itop = cam->top.i;
        gdlg.m_jtop = cam->top.j;
        gdlg.m_ktop = cam->top.k;

        gdlg.m_fov  = cam->fov;
    gdlg.m_width = cam->width;
    gdlg.m_height = cam->height;

//��� Application Flags
    CameraPropAppFlagsPage  afdlg;

    afdlg.m_app0 = (cam->flags & ESCH_CAM_APP0) ? 1 : 0;
    afdlg.m_app1 = (cam->flags & ESCH_CAM_APP1) ? 1 : 0;
    afdlg.m_app2 = (cam->flags & ESCH_CAM_APP2) ? 1 : 0;
    afdlg.m_app3 = (cam->flags & ESCH_CAM_APP3) ? 1 : 0;
    afdlg.m_app4 = (cam->flags & ESCH_CAM_APP4) ? 1 : 0;
    afdlg.m_app5 = (cam->flags & ESCH_CAM_APP5) ? 1 : 0;
    afdlg.m_app6 = (cam->flags & ESCH_CAM_APP6) ? 1 : 0;
    afdlg.m_app7 = (cam->flags & ESCH_CAM_APP7) ? 1 : 0;

//��� Misc
    CameraPropMiscPage      mdlg;

    ASSERT(pDoc->palette != 0);
    VngoColor24bit clr = pDoc->palette->hw_pal.p[(byte)cam->bcolor];
    mdlg.m_bcolor = (clr.r | (clr.g << 8) | (clr.b << 16));

        mdlg.m_hither = cam->hither;
        mdlg.m_yon    = cam->yon;
        mdlg.m_scalef = cam->factor;

//��� Extended
    CameraPropExPage        xdlg;

    if (cam->vport)
        xdlg.m_haze_active = (cam->vport->vflags & VNGO_HAZE_ON) ? 1 : 0;
    else
        xdlg.m_haze_active = 0;
    xdlg.haze_change = FALSE;
    xdlg.haze_color = (clr.r | (clr.g << 8) | (clr.b << 16));
    xdlg.m_bg_active = (cam->bg_bitmap) ? 1 : 0;
    xdlg.bg_bm = (XFBitmap*)cam->app_data;

//��� Interact
    CPropertySheet  sh("Camera Properties");
    sh.AddPage(&gdlg);
    sh.AddPage(&afdlg);
    sh.AddPage(&mdlg);
    sh.AddPage(&xdlg);

//��� Store results, if OK
    if (sh.DoModal() == IDOK)
    {
        //��� General
        strncpy(cam->name,gdlg.m_name,ESCH_MAX_NAME);
        cam->set_position(gdlg.m_xpos,gdlg.m_ypos,gdlg.m_zpos);
        cam->set_vects(gdlg.m_itop,gdlg.m_jtop,gdlg.m_ktop,
                       gdlg.m_idir,gdlg.m_jdir,gdlg.m_kdir);

        if (cam->flags & ESCH_CAM_ORTHO)
        {
            cam->fov = gdlg.m_fov;
            cam->set_ortho(gdlg.m_width,gdlg.m_height);
        }
        else
        {
            cam->width = gdlg.m_width;
            cam->height = gdlg.m_height;
            cam->set_fov(gdlg.m_fov);
        }

        //��� Application Flags
        dword flags = cam->flags;
        flags &= ~(ESCH_CAM_APP0
                   | ESCH_CAM_APP1
                   | ESCH_CAM_APP2
                   | ESCH_CAM_APP3
                   | ESCH_CAM_APP4
                   | ESCH_CAM_APP5
                   | ESCH_CAM_APP6
                   | ESCH_CAM_APP7);
        if (afdlg.m_app0)
            flags |= ESCH_CAM_APP0;
        if (afdlg.m_app1)
            flags |= ESCH_CAM_APP1;
        if (afdlg.m_app2)
            flags |= ESCH_CAM_APP2;
        if (afdlg.m_app3)
            flags |= ESCH_CAM_APP3;
        if (afdlg.m_app4)
            flags |= ESCH_CAM_APP4;
        if (afdlg.m_app5)
            flags |= ESCH_CAM_APP5;
        if (afdlg.m_app6)
            flags |= ESCH_CAM_APP6;
        if (afdlg.m_app7)
            flags |= ESCH_CAM_APP7;
        cam->set_flags(flags);

        //��� Misc
        cam->set_yon(mdlg.m_yon);
        cam->set_hither(mdlg.m_hither);
        cam->set_factor(mdlg.m_scalef);
        ASSERT(pDoc->palette != 0);
        cam->set_bcolor(pDoc->palette->get_index((VngoColor24bit)mdlg.m_bcolor));

        //��� Extended
        if (cam->vport)
        {
            if (xdlg.m_haze_active)
            {
                cam->set_haze(xdlg.m_startz, xdlg.m_midz,
                              VngoColor24bit(xdlg.haze_color));
            }
            else
            {
                cam->vport->haze_off();
            }
        }

        if (xdlg.m_bg_active && xdlg.bg_bm)
        {
            cam->app_data = xdlg.bg_bm;
            if (cam->create_bg_bitmap(xdlg.bg_bm))
            {
                MessageBox("Create of bitmap background failed",
                           "Bitmap Background",
                           MB_OK | MB_ICONEXCLAMATION);
            }
        }
        else
        {
            if (xdlg.bg_bm)
                delete xdlg.bg_bm;
            cam->app_data = 0;
            cam->set_bg_bitmap(0);
        }

        //��� Update views
        if (doupdate)
        {
            pDoc->SetModifiedFlag();
            pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST | HINT_UPDATERENDER,NULL);
        }

        return TRUE;
    }

    if (xdlg.bg_bm != cam->app_data)
    {
        if (xdlg.bg_bm)
            delete xdlg.bg_bm;
    }

    return FALSE;
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// ToolView - ui_light_properties                                           �
//���������������������������������������������������������������������������
BOOL ToolView::ui_light_properties(EschLight **lgt, int doupdate, int edittype)
{
    if (!lgt || !*lgt)
        return FALSE;

    ToolDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

//��� General
    LightPropGeneralPage   gdlg;
    gdlg.m_edit = (edittype) ? 1 : 0;

    gdlg.m_name = (*lgt)->name;
    gdlg.m_name = gdlg.m_name.Left(ESCH_MAX_NAME);

    gdlg.m_intensity = (*lgt)->get_intensity();
    switch ((*lgt)->get_type())
    {
        case ESCH_LGTT_AMBIENT:
            gdlg.m_type = 0;
            break;
        case ESCH_LGTT_VECTOR:
            gdlg.m_type = 1;
            break;
        case ESCH_LGTT_FPOINT:
            gdlg.m_type = 2;
            break;
        case ESCH_LGTT_FATTEN:
            gdlg.m_type = 3;
            break;
        case ESCH_LGTT_FSPOT:
            gdlg.m_type = 4;
            break;
        case ESCH_LGTT_POINT:
            gdlg.m_type = 5;
            break;
        case ESCH_LGTT_ATTEN:
            gdlg.m_type = 6;
            break;
        case ESCH_LGTT_SPOT:
            gdlg.m_type = 7;
            break;
        default:
            ASSERT(0);
    }
    gdlg.m_active = ((*lgt)->flags & ESCH_LGT_OFF) ? 0 : 1;
    gdlg.m_dark = ((*lgt)->flags & ESCH_LGT_DARK) ? 1 : 0;
    gdlg.m_atten = ((*lgt)->flags & ESCH_LGT_ATTEN) ? 1 : 0;
    switch ((*lgt)->get_type())
    {
        case ESCH_LGTT_VECTOR:
            gdlg.m_xiValue = ((EschVectorLight*)(*lgt))->dir.i;
            gdlg.m_yjValue = ((EschVectorLight*)(*lgt))->dir.j;
            gdlg.m_zkValue = ((EschVectorLight*)(*lgt))->dir.k;
            break;
        case ESCH_LGTT_FPOINT:
        case ESCH_LGTT_FATTEN:
        case ESCH_LGTT_FSPOT:
            gdlg.m_xiValue = ((EschFastPointLight*)(*lgt))->pos.x;
            gdlg.m_yjValue = ((EschFastPointLight*)(*lgt))->pos.y;
            gdlg.m_zkValue = ((EschFastPointLight*)(*lgt))->pos.z;
            break;
        case ESCH_LGTT_POINT:
        case ESCH_LGTT_ATTEN:
        case ESCH_LGTT_SPOT:
            gdlg.m_xiValue = ((EschPointLight*)(*lgt))->pos.x;
            gdlg.m_yjValue = ((EschPointLight*)(*lgt))->pos.y;
            gdlg.m_zkValue = ((EschPointLight*)(*lgt))->pos.z;
            break;
    }

//��� Extra
    LightPropExtraPage  xdlg;

    switch ((*lgt)->get_type())
    {
        case ESCH_LGTT_FATTEN:
            xdlg.m_inner = ((EschFastAttenLight*)(*lgt))->inner;
            xdlg.m_outer = ((EschFastAttenLight*)(*lgt))->outer;
            break;
        case ESCH_LGTT_ATTEN:
            xdlg.m_inner = ((EschAttenLight*)(*lgt))->inner;
            xdlg.m_outer = ((EschAttenLight*)(*lgt))->outer;
            break;
        case ESCH_LGTT_FSPOT:
            xdlg.m_diri = ((EschFastSpotLight*)(*lgt))->dir.i;
            xdlg.m_dirj = ((EschFastSpotLight*)(*lgt))->dir.j;
            xdlg.m_dirk = ((EschFastSpotLight*)(*lgt))->dir.k;
            xdlg.m_hotspot = ((EschFastSpotLight*)(*lgt))->hotspot;
            xdlg.m_falloff = ((EschFastSpotLight*)(*lgt))->falloff;
            xdlg.m_inner = ((EschFastSpotLight*)(*lgt))->inner;
            xdlg.m_outer = ((EschFastSpotLight*)(*lgt))->outer;
            break;
        case ESCH_LGTT_SPOT:
            xdlg.m_diri = ((EschSpotLight*)(*lgt))->dir.i;
            xdlg.m_dirj = ((EschSpotLight*)(*lgt))->dir.j;
            xdlg.m_dirk = ((EschSpotLight*)(*lgt))->dir.k;
            xdlg.m_hotspot = ((EschSpotLight*)(*lgt))->hotspot;
            xdlg.m_falloff = ((EschSpotLight*)(*lgt))->falloff;
            xdlg.m_inner = ((EschSpotLight*)(*lgt))->inner;
            xdlg.m_outer = ((EschSpotLight*)(*lgt))->outer;
            break;
    }

//��� Application Flags
    LightPropAppFlagsPage  afdlg;

    afdlg.m_app0 = ((*lgt)->flags & ESCH_LGT_APP0) ? 1 : 0;
    afdlg.m_app1 = ((*lgt)->flags & ESCH_LGT_APP1) ? 1 : 0;
    afdlg.m_app2 = ((*lgt)->flags & ESCH_LGT_APP2) ? 1 : 0;
    afdlg.m_app3 = ((*lgt)->flags & ESCH_LGT_APP3) ? 1 : 0;
    afdlg.m_app4 = ((*lgt)->flags & ESCH_LGT_APP4) ? 1 : 0;
    afdlg.m_app5 = ((*lgt)->flags & ESCH_LGT_APP5) ? 1 : 0;
    afdlg.m_app6 = ((*lgt)->flags & ESCH_LGT_APP6) ? 1 : 0;
    afdlg.m_app7 = ((*lgt)->flags & ESCH_LGT_APP7) ? 1 : 0;

//��� Interact
    CPropertySheet  sh("Light Properties");
    sh.AddPage(&gdlg);
    sh.AddPage(&xdlg);
    sh.AddPage(&afdlg);

//��� Store results, if OK
    if (sh.DoModal() == IDOK)
    {
        if (edittype && ((*lgt)->get_type() != gdlg.m_type))
        {
            delete (*lgt);
            switch (gdlg.m_type)
            {
                case 0:     // Ambient
                    *lgt = new EschLight;
                    break;
                case 1:     // Vector
                    *lgt = new EschVectorLight;
                    break;
                case 2:     // FastPoint
                    *lgt = new EschFastPointLight;
                    break;
                case 3:     // FastAtten
                    *lgt = new EschFastAttenLight;
                    break;
                case 4:     // FastSpot
                    *lgt = new EschFastSpotLight;
                    break;
                case 5:     // Point
                    *lgt = new EschPointLight;
                    break;
                case 6:     // Atten
                    *lgt = new EschAttenLight;
                    break;
                case 7:     // Spot
                    *lgt = new EschSpotLight;
                    break;
                default:
                    ASSERT(0);
            }
        }

        strncpy((*lgt)->name,gdlg.m_name,ESCH_MAX_NAME);
        (*lgt)->set_intensity(gdlg.m_intensity);
        switch ((*lgt)->get_type())
        {
            case ESCH_LGTT_VECTOR:
                ((EschVectorLight*)(*lgt))->set_direction(gdlg.m_xiValue,
                                                          gdlg.m_yjValue,
                                                          gdlg.m_zkValue);
                break;
            case ESCH_LGTT_FPOINT:
            case ESCH_LGTT_FATTEN:
            case ESCH_LGTT_FSPOT:
                ((EschFastPointLight*)(*lgt))->set_position(gdlg.m_xiValue,
                                                            gdlg.m_yjValue,
                                                            gdlg.m_zkValue);
                break;
            case ESCH_LGTT_POINT:
            case ESCH_LGTT_ATTEN:
            case ESCH_LGTT_SPOT:
                ((EschPointLight*)(*lgt))->set_position(gdlg.m_xiValue,
                                                        gdlg.m_yjValue,
                                                        gdlg.m_zkValue);
                break;
        }

        dword flags = (*lgt)->flags;
        if (gdlg.m_active)
            flags &= ~ESCH_LGT_OFF;
        else
            flags |= ESCH_LGT_OFF;

        if (gdlg.m_dark)
            flags |= ESCH_LGT_DARK;
        else
            flags &= ~ESCH_LGT_DARK;

        if (gdlg.m_atten)
            flags |= ESCH_LGT_ATTEN;
        else
            flags &= ~ESCH_LGT_ATTEN;


        //��� Extra
        switch ((*lgt)->get_type())
        {
            case ESCH_LGTT_FATTEN:
                ((EschFastAttenLight*)(*lgt))->set_inner(xdlg.m_inner);
                ((EschFastAttenLight*)(*lgt))->set_outer(xdlg.m_outer);
                break;
            case ESCH_LGTT_ATTEN:
                ((EschAttenLight*)(*lgt))->set_inner(xdlg.m_inner);
                ((EschAttenLight*)(*lgt))->set_outer(xdlg.m_outer);
                break;
            case ESCH_LGTT_FSPOT:
                ((EschFastSpotLight*)(*lgt))->set_direction(xdlg.m_diri,
                                                            xdlg.m_dirj,
                                                            xdlg.m_dirk);
                ((EschFastSpotLight*)(*lgt))->set_hotspot(xdlg.m_hotspot);
                ((EschFastSpotLight*)(*lgt))->set_falloff(xdlg.m_falloff);
                ((EschFastSpotLight*)(*lgt))->set_inner(xdlg.m_inner);
                ((EschFastSpotLight*)(*lgt))->set_outer(xdlg.m_outer);
                break;
            case ESCH_LGTT_SPOT:
                ((EschSpotLight*)(*lgt))->set_direction(xdlg.m_diri,
                                                        xdlg.m_dirj,
                                                        xdlg.m_dirk);
                ((EschSpotLight*)(*lgt))->set_hotspot(xdlg.m_hotspot);
                ((EschSpotLight*)(*lgt))->set_falloff(xdlg.m_falloff);
                ((EschSpotLight*)(*lgt))->set_inner(xdlg.m_inner);
                ((EschSpotLight*)(*lgt))->set_outer(xdlg.m_outer);
                break;
        }

        //��� Application Flags
        flags &= ~(ESCH_LGT_APP0
                   | ESCH_LGT_APP1
                   | ESCH_LGT_APP2
                   | ESCH_LGT_APP3
                   | ESCH_LGT_APP4
                   | ESCH_LGT_APP5
                   | ESCH_LGT_APP6
                   | ESCH_LGT_APP7);
        if (afdlg.m_app0)
            flags |= ESCH_LGT_APP0;
        if (afdlg.m_app1)
            flags |= ESCH_LGT_APP1;
        if (afdlg.m_app2)
            flags |= ESCH_LGT_APP2;
        if (afdlg.m_app3)
            flags |= ESCH_LGT_APP3;
        if (afdlg.m_app4)
            flags |= ESCH_LGT_APP4;
        if (afdlg.m_app5)
            flags |= ESCH_LGT_APP5;
        if (afdlg.m_app6)
            flags |= ESCH_LGT_APP6;
        if (afdlg.m_app7)
            flags |= ESCH_LGT_APP7;
        (*lgt)->set_flags(flags);

        //��� Update views
        if (doupdate)
        {
            pDoc->SetModifiedFlag();
            pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST | HINT_UPDATERENDER,NULL);
        }

        return TRUE;
    }

    return FALSE;
}


//�������������������������������������������������������������������������Ŀ
//                             ��� Protected ���                            �
// ToolView - ui_mesh_properties                                            �
//���������������������������������������������������������������������������
BOOL ToolView::ui_mesh_properties(EschMeshDraw *msh, int doupdate)
{
    if (!msh)
        return FALSE;

    ToolDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

//��� General
    MeshPropGeneralPage   gdlg;
    gdlg.m_name = msh->name;
    gdlg.m_name = gdlg.m_name.Left(ESCH_MAX_NAME);

    ASSERT(msh->mesh != 0);
    gdlg.m_nfaces = msh->mesh->nfaces;
    gdlg.m_nverts = msh->mesh->nverts;

    if (msh->parent())      // Disabled
    {
        gdlg.m_parent = msh->parent()->name;
        gdlg.m_parent = gdlg.m_parent.Left(ESCH_MAX_NAME);
    }
    if (msh->child())       // Disabled
    {
        gdlg.m_child = msh->child()->name;
        gdlg.m_child = gdlg.m_child.Left(ESCH_MAX_NAME);
    }

    gdlg.m_visible = (msh->flags & ESCH_DRW_SKIP) ? 0 : 1;
    gdlg.m_chkext = (msh->flags & ESCH_MSHD_NOEXTENTSCHK) ? 0 : 1;

    EschPoint   pos;
    msh->get_position(&pos);
    gdlg.m_xpos = pos.x;
    gdlg.m_ypos = pos.y;
    gdlg.m_zpos = pos.z;

//��� Orientation
    MeshPropOrientPage      odlg;

    odlg.m_mtxa = msh->local.orient.mtx[ESCH_MTX_A];
    odlg.m_mtxb = msh->local.orient.mtx[ESCH_MTX_B];
    odlg.m_mtxc = msh->local.orient.mtx[ESCH_MTX_C];
    odlg.m_mtxd = msh->local.orient.mtx[ESCH_MTX_D];
    odlg.m_mtxe = msh->local.orient.mtx[ESCH_MTX_E];
    odlg.m_mtxf = msh->local.orient.mtx[ESCH_MTX_F];
    odlg.m_mtxg = msh->local.orient.mtx[ESCH_MTX_G];
    odlg.m_mtxh = msh->local.orient.mtx[ESCH_MTX_H];
    odlg.m_mtxi = msh->local.orient.mtx[ESCH_MTX_I];

//��� Extents
    MeshPropExtPage         edlg;

    ASSERT(msh->mesh != 0);
    edlg.m_xcen   = msh->mesh->sphere.center.x;
    edlg.m_ycen   = msh->mesh->sphere.center.y;
    edlg.m_zcen   = msh->mesh->sphere.center.z;
    edlg.m_radius = msh->mesh->sphere.radius;
    edlg.m_xmin   = msh->mesh->box.mins[0];
    edlg.m_ymin   = msh->mesh->box.mins[1];
    edlg.m_zmin   = msh->mesh->box.mins[2];
    edlg.m_xmax   = msh->mesh->box.maxs[0];
    edlg.m_ymax   = msh->mesh->box.maxs[1];
    edlg.m_zmax   = msh->mesh->box.maxs[2];

//��� Application Flags
    MeshPropAppFlagsPage  afdlg;

    afdlg.m_app0 = (msh->mesh->flags & ESCH_MSH_APP0) ? 1 : 0;
    afdlg.m_app1 = (msh->mesh->flags & ESCH_MSH_APP1) ? 1 : 0;
    afdlg.m_app2 = (msh->mesh->flags & ESCH_MSH_APP2) ? 1 : 0;
    afdlg.m_app3 = (msh->mesh->flags & ESCH_MSH_APP3) ? 1 : 0;
    afdlg.m_app4 = (msh->mesh->flags & ESCH_MSH_APP4) ? 1 : 0;
    afdlg.m_app5 = (msh->mesh->flags & ESCH_MSH_APP5) ? 1 : 0;
    afdlg.m_app6 = (msh->mesh->flags & ESCH_MSH_APP6) ? 1 : 0;
    afdlg.m_app7 = (msh->mesh->flags & ESCH_MSH_APP7) ? 1 : 0;
    afdlg.m_app8 = (msh->mesh->flags & ESCH_MSH_APP8) ? 1 : 0;
    afdlg.m_app9 = (msh->mesh->flags & ESCH_MSH_APP9) ? 1 : 0;
    afdlg.m_appa = (msh->mesh->flags & ESCH_MSH_APPA) ? 1 : 0;
    afdlg.m_appb = (msh->mesh->flags & ESCH_MSH_APPB) ? 1 : 0;
    afdlg.m_appc = (msh->mesh->flags & ESCH_MSH_APPC) ? 1 : 0;
    afdlg.m_appd = (msh->mesh->flags & ESCH_MSH_APPD) ? 1 : 0;
    afdlg.m_appe = (msh->mesh->flags & ESCH_MSH_APPE) ? 1 : 0;
    afdlg.m_appf = (msh->mesh->flags & ESCH_MSH_APPF) ? 1 : 0;

//��� Verticies
    MeshPropVertsPage   vdlg;
    vdlg.nverts = msh->mesh->nverts;
    vdlg.v = msh->mesh->v;

//��� Faces
    MeshPropFacePage    fdlg;
    fdlg.nfaces = msh->mesh->nfaces;
    fdlg.f = msh->mesh->f;
    fdlg.nverts = msh->mesh->nverts;
    fdlg.tmax = msh->mesh->tmax;
    fdlg.txt = msh->mesh->txt;

    fdlg.setup(pDoc);

//��� Textures
    MeshPropTexturePage  txdlg;
    txdlg.tmax = msh->mesh->tmax;
    txdlg.txt = msh->mesh->txt;

    txdlg.setup(pDoc);

//��� Interact
    CPropertySheet  sh("Mesh Properties");
    sh.AddPage(&gdlg);
    sh.AddPage(&odlg);
    sh.AddPage(&edlg);
    sh.AddPage(&afdlg);
    sh.AddPage(&vdlg);
    sh.AddPage(&fdlg);
    sh.AddPage(&txdlg);

//��� Store results, if OK
    if (sh.DoModal() == IDOK)
    {
        //��� General
        strncpy(msh->name,gdlg.m_name,ESCH_MAX_NAME);

        if (gdlg.m_visible)
            msh->flags &= ~ESCH_DRW_SKIP;
        else
            msh->flags |= ESCH_DRW_SKIP;

        if (gdlg.m_chkext)
            msh->flags &= ~ESCH_MSHD_NOEXTENTSCHK;
        else
            msh->flags |= ESCH_MSHD_NOEXTENTSCHK;

        // Set directly since we are already directly setting
        // the orient matrix below.
        msh->local.orient.mtx[ESCH_MTX_J] = gdlg.m_xpos;
        msh->local.orient.mtx[ESCH_MTX_K] = gdlg.m_ypos;
        msh->local.orient.mtx[ESCH_MTX_L] = gdlg.m_zpos;

        //��� Orientation
        msh->local.orient.mtx[ESCH_MTX_A] = odlg.m_mtxa;
        msh->local.orient.mtx[ESCH_MTX_B] = odlg.m_mtxb;
        msh->local.orient.mtx[ESCH_MTX_C] = odlg.m_mtxc;
        msh->local.orient.mtx[ESCH_MTX_D] = odlg.m_mtxd;
        msh->local.orient.mtx[ESCH_MTX_E] = odlg.m_mtxe;
        msh->local.orient.mtx[ESCH_MTX_F] = odlg.m_mtxf;
        msh->local.orient.mtx[ESCH_MTX_G] = odlg.m_mtxg;
        msh->local.orient.mtx[ESCH_MTX_H] = odlg.m_mtxh;
        msh->local.orient.mtx[ESCH_MTX_I] = odlg.m_mtxi;
        msh->local.compute_inverse();
        msh->compute_world();

        //��� Extents
        msh->mesh->sphere.center.x  = edlg.m_xcen;
        msh->mesh->sphere.center.y  = edlg.m_ycen;
        msh->mesh->sphere.center.z  = edlg.m_zcen;
        msh->mesh->sphere.radius    = edlg.m_radius;
        msh->mesh->box.mins[0]      = edlg.m_xmin;
        msh->mesh->box.mins[1]      = edlg.m_ymin;
        msh->mesh->box.mins[2]      = edlg.m_zmin;
        msh->mesh->box.maxs[0]      = edlg.m_xmax;
        msh->mesh->box.maxs[1]      = edlg.m_ymax;
        msh->mesh->box.maxs[2]      = edlg.m_zmax;

        //��� Application Flags
        dword flags = msh->mesh->flags;
        flags &= ~(ESCH_MSH_APP0
                   | ESCH_MSH_APP1
                   | ESCH_MSH_APP2
                   | ESCH_MSH_APP3
                   | ESCH_MSH_APP4
                   | ESCH_MSH_APP5
                   | ESCH_MSH_APP6
                   | ESCH_MSH_APP7
                   | ESCH_MSH_APP8
                   | ESCH_MSH_APP9
                   | ESCH_MSH_APPA
                   | ESCH_MSH_APPB
                   | ESCH_MSH_APPC
                   | ESCH_MSH_APPD
                   | ESCH_MSH_APPE
                   | ESCH_MSH_APPF);
        if (afdlg.m_app0)
            flags |= ESCH_MSH_APP0;
        if (afdlg.m_app1)
            flags |= ESCH_MSH_APP1;
        if (afdlg.m_app2)
            flags |= ESCH_MSH_APP2;
        if (afdlg.m_app3)
            flags |= ESCH_MSH_APP3;
        if (afdlg.m_app4)
            flags |= ESCH_MSH_APP4;
        if (afdlg.m_app5)
            flags |= ESCH_MSH_APP5;
        if (afdlg.m_app6)
            flags |= ESCH_MSH_APP6;
        if (afdlg.m_app7)
            flags |= ESCH_MSH_APP7;
        if (afdlg.m_app8)
            flags |= ESCH_MSH_APP8;
        if (afdlg.m_app9)
            flags |= ESCH_MSH_APP9;
        if (afdlg.m_appa)
            flags |= ESCH_MSH_APPA;
        if (afdlg.m_appb)
            flags |= ESCH_MSH_APPB;
        if (afdlg.m_appc)
            flags |= ESCH_MSH_APPC;
        if (afdlg.m_appd)
            flags |= ESCH_MSH_APPD;
        if (afdlg.m_appe)
            flags |= ESCH_MSH_APPE;
        if (afdlg.m_appf)
            flags |= ESCH_MSH_APPF;
        msh->mesh->set_flags(flags);

        //��� Verticies/Faces/Textures
        // Changes are made while inside the dialog...

        //��� Update views
        if (doupdate)
        {
            pDoc->SetModifiedFlag();
            pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST | HINT_UPDATERENDER,NULL);
        }

        return TRUE;
    }

    return FALSE;
}


//�������������������������������������������������������������������������Ŀ
// ToolView - EditProperties                                                �
//���������������������������������������������������������������������������
void ToolView::EditProperties()
{
    dword       sel;
    EschLight   *lgt;

        sel = iTree.GetSelected();

    switch (sel & 0xffff0000)
    {
        case TREE_SCENE_BASE:
            ui_scene_properties();
            break;
        case TREE_CAMERA_BASE:
            ui_camera_properties(iTree.GetCameraItem(sel));
            break;
        case TREE_LIGHT_BASE:
            lgt = iTree.GetLightItem(sel);
            ui_light_properties(&lgt);
            break;
        case TREE_MESH_BASE:
            ui_mesh_properties(iTree.GetMeshItem(sel));
            break;
        default:
            break;
    }

    iTree.SetFocus();
}



//���������������������������������������������������������������������������
//���������������������������� Message Handlers �����������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolView - Create                                                        �
//���������������������������������������������������������������������������
BOOL ToolView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
                      const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
//��� Create view window
    if (!CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext))
        return FALSE;

    int     i;
    CRect   rct;

    rct.SetRectEmpty();

//��� Create tree view
    if (!iTree.Create(WS_CHILD
                      | WS_DLGFRAME
                      | WS_CLIPSIBLINGS
                      | WS_VISIBLE
                      | TVS_HASLINES
                      | TVS_HASBUTTONS,
                      rct, this, VIEWID_ITREE))
        goto error_exit;

//��� Create viewports
    if (!wVp[0].Create(NULL, "Viewport",
                       WS_CHILD
                       | WS_VISIBLE
                       | WS_BORDER
                       | WS_CLIPSIBLINGS
                       | WS_VSCROLL
                       | WS_HSCROLL,
                       rct, this, VIEWID_VP0))
        goto error_exit;

#if (MAX_VPORTS > 1)
    for(i=0; i < MAX_VPORTS-1; i++)
    {
        if (!wVp[i+1].Create(NULL, "Viewport",
                             WS_CHILD
                             | WS_BORDER
                             | WS_CLIPSIBLINGS
                             | WS_VSCROLL
                             | WS_HSCROLL,
                             rct, this, VIEWID_VP1 + i))
            goto error_exit;
    }
#endif

    vpmode = VPMODE_STANDARD;
    wVp[0].SetMode(RNDCTRL_ROTATEXY);

    return TRUE;

//��� Handle create failure
error_exit: ;

    if (iTree.m_hWnd)
        iTree.DestroyWindow();
    for(i=0; i < MAX_VPORTS; i++)
    {
        if (wVp[i].m_hWnd)
            wVp[i].DestroyWindow();
    }
    DestroyWindow();
    return FALSE;
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnInitialUpdate                                               �
//���������������������������������������������������������������������������
void ToolView::OnInitialUpdate()
{
    switch (vpmode)
    {
        case VPMODE_NONE:
            break;
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_ROTATEXY);
            break;
        default:
            ASSERT(0);
        break;
    }

        CView::OnInitialUpdate();
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnUpdate                                                      �
//���������������������������������������������������������������������������
void ToolView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
        ToolDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);

//�� Reset AutoRotate clock
    if (!lHint)
        Clock.clear();

//�� Build treelist of items in document
    if (!lHint || (lHint & HINT_UPDATETREELIST))
    {

        iTree.RebuildTreeList();
    }

//�� Attach camera
    if (!lHint || (lHint & HINT_UPDATECAMATTACH))
    {
        switch (vpmode)
        {
            case VPMODE_NONE:
                break;
            case VPMODE_STANDARD:
                wVp[0].SetCamera(pDoc->cameras);
                break;
            default:
                ASSERT(0);
                break;
        }
    }

//�� Render
    if (!lHint || (lHint & HINT_UPDATERENDER | HINT_UPDATECAMATTACH))
    {
        switch (vpmode)
        {
            case VPMODE_NONE:
                break;
            case VPMODE_STANDARD:
                wVp[0].Render();
                wVp[0].Invalidate();
                break;
            default:
                ASSERT(0);
                break;
        }
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnActivateView                                                �
//���������������������������������������������������������������������������
void ToolView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
    if (bActivate)
    {
        ToolDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);

        CClientDC dc (this);

        SelectPalette(dc.m_hDC,pDoc->hpal,0);
        dc.RealizePalette ();
    }
        CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnDraw                                                        �
//���������������������������������������������������������������������������
void ToolView::OnDraw(CDC* pDC)
{
        ToolDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnSize                                                        �
//���������������������������������������������������������������������������
void ToolView::OnSize(UINT nType, int cx, int cy)
{
    int width_of_vports=0;

    switch (vpmode)
    {
        case VPMODE_NONE:
            break;
        case VPMODE_STANDARD:
            width_of_vports = cx / 4 * 3;
            width_of_vports &= ~0x3;
            width_of_vports += GetSystemMetrics(SM_CXBORDER)*2;

            if (wVp[0].m_hWnd)
                wVp[0].MoveWindow(cx - width_of_vports, 0, width_of_vports, cy);
            break;
        default:
            ASSERT(0);
            break;
    }

    if (iTree.m_hWnd)
        iTree.MoveWindow(0,0,cx - width_of_vports,cy);

        CView::OnSize(nType, cx, cy);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnEdit(Update)Delete                                          �
//���������������������������������������������������������������������������
void ToolView::OnEditDelete()
{
    dword           sel;
    EschCameraEx    *cam;
    EschLight       *lgt;
    EschMeshDraw    *msh;
    char            str[128];

    ToolDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

        sel = iTree.GetSelected();

    switch (sel & 0xffff0000)
    {
        case TREE_CAMERA_BASE:
            cam = iTree.GetCameraItem(sel);
            if (!cam)
                return;

            sprintf(str,"Are you sure you wish to delete '%s'?",cam->name);
            if (MessageBox(str, "Delete Camera", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                if (cam == pDoc->cameras)
                    pDoc->cameras = (EschCameraEx*)cam->next();
                cam->remove();
                delete cam;
                pDoc->SetModifiedFlag();
                pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST | HINT_UPDATECAMATTACH,NULL);
            }
            break;
        case TREE_LIGHT_BASE:
            lgt = iTree.GetLightItem(sel);
            if (!lgt)
                return;

            sprintf(str,"Are you sure you wish to delete '%s'?",lgt->name);
            if (MessageBox(str, "Delete Light", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                if (lgt == pDoc->lights)
                    pDoc->lights = lgt->next();
                lgt->remove();
                switch (vpmode)
                {
                    case VPMODE_STANDARD:
                        if (wVp[0].GetModeTarget() == lgt
                            && (wVp[0].GetMode() == RNDCTRL_LIGHTXY
                                || wVp[0].GetMode() == RNDCTRL_LIGHTBRIGHT))
                        {
                                wVp[0].SetMode(RNDCTRL_ROTATEXY);
                        }
                        break;
                }
                delete lgt;
                pDoc->SetModifiedFlag();
                pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST | HINT_UPDATERENDER,NULL);
            }
            break;
        case TREE_MESH_BASE:
            msh = iTree.GetMeshItem(sel);
            if (!msh)
                return;

            sprintf(str,"Are you sure you wish to delete '%s'?",msh->name);
            if (MessageBox(str, "Delete Mesh", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                if (msh->child())
                {
                    sprintf(str,"All children of '%s' will be deleted.\n\nContinue?",msh->name);
                    if (MessageBox(str,"Delete Mesh", MB_YESNO | MB_ICONSTOP) != IDYES)
                        return;
                }

                if (msh == pDoc->meshes)
                    pDoc->meshes = (EschMeshDraw*)msh->next();
                msh->remove(1);
                switch (vpmode)
                {
                    case VPMODE_STANDARD:
                        if (wVp[0].GetModeTarget() == msh
                            && (wVp[0].GetMode() == RNDCTRL_ROTATEIJ
                                || wVp[0].GetMode() == RNDCTRL_MOVEIJ
                                || wVp[0].GetMode() == RNDCTRL_ROTMOVEZ))
                        {
                                wVp[0].SetMode(RNDCTRL_ROTATEXY);
                        }
                        break;
                }
                delete msh;
                pDoc->SetModifiedFlag();
                pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST | HINT_UPDATERENDER,NULL);
            }
            break;
        default:
            break;
    }

    iTree.SetFocus();
}

void ToolView::OnUpdateEditDelete(CCmdUI* pCmdUI)
{
    switch (iTree.GetSelected() & 0xffff0000)
    {
        case TREE_CAMERA_BASE:
        case TREE_LIGHT_BASE:
        case TREE_MESH_BASE:
            pCmdUI->Enable(1);
            break;
        default:
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnEditNewCamera                                               �
//���������������������������������������������������������������������������
void ToolView::OnEditNewCamera()
{
    ToolDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

//��� Generate unique name
    char str[ESCH_MAX_NAME];

    if (pDoc->cameras)
    {
        for(int i=1; i < 65536; i++)
        {
            if (i < 10)
                sprintf(str,"Camera0%d",i);
            else
                sprintf(str,"Camera%d",i);
            if (!pDoc->cameras->find(str))
                break;
        }
    }
    else strcpy(str,"Camera01");

//��� Edit new camera, adding to list if OK pressed (delete otherwise)
    EschCameraEx *cam = new EschCameraEx;
    ASSERT(cam);
    strncpy(cam->name,str,ESCH_MAX_NAME);
    ASSERT(pDoc->palette != 0);
    cam->set_bcolor(pDoc->palette->get_index(VngoColor24bit(20,20,32)));

    if (ui_camera_properties(cam,0))
    {
        if (!pDoc->cameras)
            pDoc->cameras = cam;
        else
            cam->sibling(pDoc->cameras);

        pDoc->SetModifiedFlag();
        pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST | HINT_UPDATERENDER,NULL);
    }
    else
        delete cam;

    iTree.SetFocus();
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnEditNewLight                                                �
//���������������������������������������������������������������������������
void ToolView::OnEditNewLight()
{
    ToolDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

//��� Generate unique name
    char str[ESCH_MAX_NAME];

    if (pDoc->lights)
    {
        for(int i=1; i < 65536; i++)
        {
            if (i < 10)
                sprintf(str,"Light0%d",i);
            else
                sprintf(str,"Light%d",i);
            if (!pDoc->lights->find(str))
                break;
        }
    }
    else strcpy(str,"Light01");

//��� Edit new light, adding to list if OK pressed (delete otherwise)
    EschLight *lgt = new EschVectorLight;
    ASSERT(lgt);
    strncpy(lgt->name,str,ESCH_MAX_NAME);

    if (ui_light_properties(&lgt,0,1))
    {
        if (!pDoc->lights)
            pDoc->lights = lgt;
        else
            lgt->sibling(pDoc->lights);

        pDoc->SetModifiedFlag();
        pDoc->UpdateAllViews(NULL,HINT_UPDATETREELIST | HINT_UPDATERENDER,NULL);
    }
    else
        delete lgt;

    iTree.SetFocus();
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnEdit(Update)Properties                                      �
//���������������������������������������������������������������������������
void ToolView::OnEditProperties()
{
    EditProperties();
}

void ToolView::OnUpdateEditProperties(CCmdUI* pCmdUI)
{
    pCmdUI->Enable( (iTree.GetSelected() & 0xffff) ? 1 : 0);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnViewRefresh                                                 �
//���������������������������������������������������������������������������
void ToolView::OnViewRefresh()
{
    iTree.RedrawWindow();

    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].Render();
            wVp[0].RedrawWindow();
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndWireframe                                    �
//���������������������������������������������������������������������������
void ToolView::OnViewRndWireframe()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags &= ~(ESCH_CAM_SHADE_SPECULAR
                               | ESCH_CAM_SHADE_SMOOTH
                               | ESCH_CAM_SHADE_FLAT
                               | ESCH_CAM_SHADE_SOLID);
            wVp[0].cflags |= ESCH_CAM_SHADE_WIRE;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndWireframe(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( ((wVp[0].cflags & (ESCH_CAM_SHADE_WIRE
                                                 | ESCH_CAM_SHADE_SOLID
                                                 | ESCH_CAM_SHADE_FLAT
                                                 | ESCH_CAM_SHADE_SMOOTH
                                                 | ESCH_CAM_SHADE_SPECULAR))==ESCH_CAM_SHADE_WIRE) ? 1: 0 );
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndSolid                                        �
//���������������������������������������������������������������������������
void ToolView::OnViewRndSolid()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags &= ~(ESCH_CAM_SHADE_SPECULAR
                               | ESCH_CAM_SHADE_SMOOTH
                               | ESCH_CAM_SHADE_FLAT);
            wVp[0].cflags |= ESCH_CAM_SHADE_WIRE
                             | ESCH_CAM_SHADE_SOLID;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndSolid(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( ((wVp[0].cflags & (ESCH_CAM_SHADE_SOLID
                                                 | ESCH_CAM_SHADE_FLAT
                                                 | ESCH_CAM_SHADE_SMOOTH
                                                 | ESCH_CAM_SHADE_SPECULAR))==ESCH_CAM_SHADE_SOLID) ? 1: 0 );
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndFlat                                         �
//���������������������������������������������������������������������������
void ToolView::OnViewRndFlat()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags &= ~(ESCH_CAM_SHADE_SPECULAR
                               | ESCH_CAM_SHADE_SMOOTH);
            wVp[0].cflags |= ESCH_CAM_SHADE_WIRE
                             | ESCH_CAM_SHADE_SOLID
                             | ESCH_CAM_SHADE_FLAT;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndFlat(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( ((wVp[0].cflags & (ESCH_CAM_SHADE_FLAT
                                                 | ESCH_CAM_SHADE_SMOOTH
                                                 | ESCH_CAM_SHADE_SPECULAR))==ESCH_CAM_SHADE_FLAT) ? 1: 0 );
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndSmooth                                       �
//���������������������������������������������������������������������������
void ToolView::OnViewRndSmooth()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags &= ~ESCH_CAM_SHADE_SPECULAR;
            wVp[0].cflags |= ESCH_CAM_SHADE_WIRE
                             | ESCH_CAM_SHADE_SOLID
                             | ESCH_CAM_SHADE_FLAT
                             | ESCH_CAM_SHADE_SMOOTH;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndSmooth(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
             pCmdUI->Enable(1);
             pCmdUI->SetCheck( ((wVp[0].cflags & (ESCH_CAM_SHADE_SMOOTH
                                                  | ESCH_CAM_SHADE_SPECULAR))==ESCH_CAM_SHADE_SMOOTH) ? 1: 0 );
             break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndSpecular                                     �
//���������������������������������������������������������������������������
void ToolView::OnViewRndSpecular()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags |= ESCH_CAM_SHADE_WIRE
                             | ESCH_CAM_SHADE_SOLID
                             | ESCH_CAM_SHADE_FLAT
                             | ESCH_CAM_SHADE_SMOOTH
                             | ESCH_CAM_SHADE_SPECULAR;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndSpecular(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
             pCmdUI->Enable(1);
             pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_SHADE_SPECULAR) ? 1 : 0);
             break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndShowAllLines                                 �
//���������������������������������������������������������������������������
void ToolView::OnViewRndShowAllLines()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags ^= ESCH_CAM_SHOW_ALL_LINES;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndShowAllLines(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable( ((wVp[0].cflags & (ESCH_CAM_SHADE_WIRE
                                               | ESCH_CAM_SHADE_SOLID
                                               | ESCH_CAM_SHADE_FLAT
                                               | ESCH_CAM_SHADE_SMOOTH
                                               | ESCH_CAM_SHADE_SPECULAR))==ESCH_CAM_SHADE_WIRE) ? 1: 0 );
            pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_SHOW_ALL_LINES) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndBackface                                     �
//���������������������������������������������������������������������������
void ToolView::OnViewRndBackface()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags ^= ESCH_CAM_BACKCULL;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndBackface(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_BACKCULL) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndModelSpace                                   �
//���������������������������������������������������������������������������
void ToolView::OnViewRndModelSpace()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags ^= ESCH_CAM_MODELSPACE;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndModelSpace(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_MODELSPACE) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndTextures                                     �
//���������������������������������������������������������������������������
void ToolView::OnViewRndTextures()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags ^= ESCH_CAM_TEXTURED;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndTextures(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_TEXTURED) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndPerspective                                  �
//���������������������������������������������������������������������������
void ToolView::OnViewRndPerspective()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags ^= ESCH_CAM_PERSPECTIVE;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndPerspective(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable( (wVp[0].cflags & ESCH_CAM_TEXTURED) ? 1 : 0);
            pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_PERSPECTIVE) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndAlpha                                        �
//���������������������������������������������������������������������������
void ToolView::OnViewRndAlpha()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags ^= ESCH_CAM_ALPHA;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndAlpha(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_ALPHA) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndSort                                         �
//���������������������������������������������������������������������������
void ToolView::OnViewRndSort()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags ^= ESCH_CAM_SORT;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                if (wVp[0].cam->vport)
                {
                    if (wVp[0].cflags & ESCH_CAM_SORT)
                        wVp[0].cam->vport->zbuffer_off();
                    else
                        wVp[0].cam->vport->zbuffer_on();
                }
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndSort(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_SORT) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnView(Update)RndOrtho                                        �
//���������������������������������������������������������������������������
void ToolView::OnViewRndOrtho()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].cflags ^= ESCH_CAM_ORTHO;
            if (wVp[0].cam)
            {
                wVp[0].cam->set_flags(wVp[0].cflags);
                wVp[0].cam->compute_scalar();
                wVp[0].cam->compute_frustrum();
                wVp[0].Render();
                wVp[0].RedrawWindow();
            }
            break;
    }
}

void ToolView::OnUpdateViewRndOrtho(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].cflags & ESCH_CAM_ORTHO) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnViewShowSphereExtents                                       �
//���������������������������������������������������������������������������
void ToolView::OnViewShowSphereExtents()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].extra_flags ^= ToolVPort::SPHERE_EXTS;
            wVp[0].Render();
            wVp[0].RedrawWindow();
            break;
    }
}

void ToolView::OnUpdateViewShowSphereExtents(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].extra_flags & ToolVPort::SPHERE_EXTS) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - OnViewShowBoxExtents                                          �
//���������������������������������������������������������������������������
void ToolView::OnViewShowBoxExtents()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].extra_flags ^= ToolVPort::BOX_EXTS;
            wVp[0].Render();
            wVp[0].RedrawWindow();
            break;
    }
}

void ToolView::OnUpdateViewShowBoxExtents(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].extra_flags & ToolVPort::BOX_EXTS) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewAttachCamera                                    �
//���������������������������������������������������������������������������
void ToolView::OnViewAttachCamera()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetCamera(iTree.GetCameraItem(iTree.GetSelected()));
            wVp[0].Render();
            wVp[0].RedrawWindow();
            break;
    }
}

void ToolView::OnUpdateViewAttachCamera(CCmdUI* pCmdUI)
{
        dword sel = iTree.GetSelected();

    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable( ( ((sel & 0xffff0000) == TREE_CAMERA_BASE)
                              && (sel & 0xffff) ) ? 1 : 0 );
            break;
        default:
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewRotateXY                                        �
//���������������������������������������������������������������������������
void ToolView::OnViewRotateXY()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_ROTATEXY);
            break;
    }
}

void ToolView::OnUpdateViewRotateXY(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].GetMode() == RNDCTRL_ROTATEXY) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewMoveXY                                          �
//���������������������������������������������������������������������������
void ToolView::OnViewMoveXY()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_MOVEXY);
            break;
    }
}

void ToolView::OnUpdateViewMoveXY(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].GetMode() == RNDCTRL_MOVEXY) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewRotateMoveZ                                     �
//���������������������������������������������������������������������������
void ToolView::OnViewRotateMoveZ()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_ROTMOVEZ);
            break;
    }
}

void ToolView::OnUpdateViewRotateMoveZ(CCmdUI* pCmdUI)
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable(1);
            pCmdUI->SetCheck( (wVp[0].GetMode() == RNDCTRL_ROTMOVEZ) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewAutoRotateOff                                   �
//���������������������������������������������������������������������������
void ToolView::OnViewAutoRotateOff()
{
    AutoRotate = 0;
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewAutoRotateX                                     �
//���������������������������������������������������������������������������
void ToolView::OnViewAutoRotateX()
{
    AutoRotate ^= AUTOROTATE_X;
    Clock.clear();
}

void ToolView::OnUpdateViewAutoRotateX(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck( (AutoRotate & AUTOROTATE_X) ? 1 : 0);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewAutoRotateY                                     �
//���������������������������������������������������������������������������
void ToolView::OnViewAutoRotateY()
{
    AutoRotate ^= AUTOROTATE_Y;
    Clock.clear();
}

void ToolView::OnUpdateViewAutoRotateY(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck( (AutoRotate & AUTOROTATE_Y) ? 1 : 0);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewAutoRotateZ                                     �
//���������������������������������������������������������������������������
void ToolView::OnViewAutoRotateZ()
{
    AutoRotate ^= AUTOROTATE_Z;
    Clock.clear();
}

void ToolView::OnUpdateViewAutoRotateZ(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck( (AutoRotate & AUTOROTATE_Z) ? 1 : 0);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewAutoRotateFast                                  �
//���������������������������������������������������������������������������
void ToolView::OnViewAutoRotateFast()
{
    AutoRotateSpeed = float(AUTOROTATE_FAST);
    Clock.clear();
}

void ToolView::OnUpdateViewAutoRotateFast(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck( (AutoRotateSpeed == float(AUTOROTATE_FAST)) ? 1 : 0);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)ViewAutoRotateSlow                                  �
//���������������������������������������������������������������������������
void ToolView::OnViewAutoRotateSlow()
{
    AutoRotateSpeed = float(AUTOROTATE_SLOW);
    Clock.clear();
}

void ToolView::OnUpdateViewAutoRotateSlow(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck( (AutoRotateSpeed == float(AUTOROTATE_SLOW)) ? 1 : 0);
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)MeshRotateIJ                                        �
//���������������������������������������������������������������������������
void ToolView::OnMeshRotateIJ()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_ROTATEIJ,iTree.GetMeshItem(iTree.GetSelected()));
            break;
    }
}

void ToolView::OnUpdateMeshRotateIJ(CCmdUI* pCmdUI)
{
        dword sel = iTree.GetSelected();

    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable( ( ((sel & 0xffff0000) == TREE_MESH_BASE)
                              && (sel & 0xffff) ) ? 1 : 0 );
            pCmdUI->SetCheck( (wVp[0].GetMode() == RNDCTRL_ROTATEIJ) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)Mesh                                                �
//���������������������������������������������������������������������������
void ToolView::OnMeshMoveIJ()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_MOVEIJ,iTree.GetMeshItem(iTree.GetSelected()));
            break;
    }
}

void ToolView::OnUpdateMeshMoveIJ(CCmdUI* pCmdUI)
{
        dword sel = iTree.GetSelected();

    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable( ( ((sel & 0xffff0000) == TREE_MESH_BASE)
                              && (sel & 0xffff) ) ? 1 : 0 );
            pCmdUI->SetCheck( (wVp[0].GetMode() == RNDCTRL_MOVEIJ) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)Mesh                                                �
//���������������������������������������������������������������������������
void ToolView::OnMeshRotateMoveK()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_ROTMOVEK,iTree.GetMeshItem(iTree.GetSelected()));
            break;
    }
}

void ToolView::OnUpdateMeshRotateMoveK(CCmdUI* pCmdUI)
{
        dword sel = iTree.GetSelected();

    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable( ( ((sel & 0xffff0000) == TREE_MESH_BASE)
                              && (sel & 0xffff) ) ? 1 : 0 );
            pCmdUI->SetCheck( (wVp[0].GetMode() == RNDCTRL_ROTMOVEK) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)LightAdjustXY                                       �
//���������������������������������������������������������������������������
void ToolView::OnLightAdjustXY()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_LIGHTXY,iTree.GetLightItem(iTree.GetSelected()));
            break;
    }
}

void ToolView::OnUpdateLightAdjustXY(CCmdUI* pCmdUI)
{
        dword sel = iTree.GetSelected();

    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable( ( ((sel & 0xffff0000) == TREE_LIGHT_BASE)
                              && (sel & 0xffff) ) ? 1 : 0 );
            pCmdUI->SetCheck( (wVp[0].GetMode() == RNDCTRL_LIGHTXY) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}


//�������������������������������������������������������������������������Ŀ
// ToolView - On(Update)LightIntensity                                      �
//���������������������������������������������������������������������������
void ToolView::OnLightIntensity()
{
    switch (vpmode)
    {
        case VPMODE_STANDARD:
            wVp[0].SetMode(RNDCTRL_LIGHTBRIGHT,iTree.GetLightItem(iTree.GetSelected()));
            break;
    }
}

void ToolView::OnUpdateLightIntensity(CCmdUI* pCmdUI)
{
        dword sel = iTree.GetSelected();

    switch (vpmode)
    {
        case VPMODE_STANDARD:
            pCmdUI->Enable( ( ((sel & 0xffff0000) == TREE_LIGHT_BASE)
                              && (sel & 0xffff) ) ? 1 : 0 );
            pCmdUI->SetCheck( (wVp[0].GetMode() == RNDCTRL_LIGHTBRIGHT) ? 1 : 0);
            break;
        default:
            pCmdUI->SetCheck(0);
            pCmdUI->Enable(0);
            break;
    }
}

//��� eof - eshtview.cpp ���
