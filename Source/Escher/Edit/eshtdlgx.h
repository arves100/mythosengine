//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//���������������������������������������������������������������������������
//����������旭旭旭旭旭�旭旭旭旭���旭旭旭旭��旭姻���旭姻旭旭旭旭旭�旭旭旭旭姻�
//���������葦姻������葦姻���葦姻葦姻���葦姻葦姻���葦姻葦姻�������葦姻���葦姻�
//��������碓甥������碓甥�������碓甥�������碓甥���碓甥碓甥�������碓甥���碓甥��
//�������渦臼葦渦��渦臼葦渦臼�渦甥�������渦臼葦渦臼�渦臼葦渦���渦臼葦渦姻����
//������渦甥�������������渦甥渦甥�������渦甥���渦甥渦甥�������渦甥���渦甥����
//�����憶悔������憶悔���憶悔憶悔���憶悔憶悔���憶悔憶悔�������憶悔���憶悔�����
//����臆臆臆臆臆�臆臆臆臆���臆臆臆臆��臆悔���臆悔臆臆臆臆臆�臆悔���臆悔������
//���������������������������������������������������������������������������
//����������������� Microsoft Windows 95/98/NT Version ����������������������
//���������������������������������������������������������������������������
//���Copyright (c) 1994-1999 by Dan Higdon, Tim Little, and Chuck Walbourn���
//���������������������������������������������������������������������������
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
// THE AUTHORS MAKE NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
// OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT.  THE AUTHORS
// PROVIDE THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
// LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
// OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
//                        http://www.mythos-engine.org/
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
//                        *** Escher Terrain Editor ***
//
// Created by Chuck Walbourn
//
// eshtdlgx.h
//
// Terrain Editor Tool Dialog Classes
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Classes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

class TerrEditDoc;

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//旭旭旭旭旭旭旭旭旭旭旭 Texture/Coloring Tool Dialogs 旭旭旭旭旭旭旭旭旭旭旭
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// HeightToolDlg                                                            �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class HeightToolDlg : public CDialog
{
// Construction
public:
        HeightToolDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
        //{{AFX_DATA(HeightToolDlg)
        enum { IDD = IDD_TOOL_HEIGHT };
        CEdit   m_height7Ctl;
        CEdit   m_height6Ctl;
        CEdit   m_height5Ctl;
        CEdit   m_height4Ctl;
        CEdit   m_height3Ctl;
        CEdit   m_height2Ctl;
        CEdit   m_height1Ctl;
        CEdit   m_height0Ctl;
        CComboBox       m_tc7;
        CComboBox       m_tc6;
        CComboBox       m_tc5;
        CComboBox       m_tc4;
        CComboBox       m_tc3;
        CComboBox       m_tc2;
        CComboBox       m_tc1;
        CComboBox       m_tc0;
        float   m_height0;
        float   m_height1;
        float   m_height2;
        float   m_height3;
        float   m_height4;
        float   m_height5;
        float   m_height6;
        float   m_height7;
        float   m_height_stop;
        BOOL    m_preserve;
        //}}AFX_DATA

    ulong   count;
    ushort  tc[8];
    ushort  istxt[8];
    float   heights[8];

    void setup(TerrEditDoc *pd) { pDoc=pd; }

    BOOL    area;

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(HeightToolDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
    TerrEditDoc *pDoc;

        // Generated message map functions
        //{{AFX_MSG(HeightToolDlg)
        afx_msg void OnSelchangeToolTc0();
        afx_msg void OnSelchangeToolTc1();
        afx_msg void OnSelchangeToolTc2();
        afx_msg void OnSelchangeToolTc3();
        afx_msg void OnSelchangeToolTc4();
        afx_msg void OnSelchangeToolTc5();
        afx_msg void OnSelchangeToolTc6();
        afx_msg void OnSelchangeToolTc7();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// RandomToolDlg                                                            �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class RandomToolDlg : public CDialog
{
// Construction
public:
        RandomToolDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
        //{{AFX_DATA(RandomToolDlg)
        enum { IDD = IDD_TOOL_RANDOM };
        CButton m_elvcutoffCtl;
        CEdit   m_elvlowCtl;
        CEdit   m_elvhighCtl;
        CEdit   m_range7Ctl;
        CEdit   m_range6Ctl;
        CEdit   m_range5Ctl;
        CEdit   m_range4Ctl;
        CEdit   m_range3Ctl;
        CEdit   m_range2Ctl;
        CEdit   m_range1Ctl;
        CEdit   m_range0Ctl;
        CComboBox       m_tc7;
        CComboBox       m_tc6;
        CComboBox       m_tc5;
        CComboBox       m_tc4;
        CComboBox       m_tc3;
        CComboBox       m_tc2;
        CComboBox       m_tc1;
        CComboBox       m_tc0;
        UINT    m_range0;
        UINT    m_range1;
        UINT    m_range2;
        UINT    m_range3;
        UINT    m_range4;
        UINT    m_range5;
        UINT    m_range6;
        UINT    m_range7;
        BOOL    m_preserve;
        BOOL    m_elvcutoff;
        float   m_elvhigh;
        float   m_elvlow;
        //}}AFX_DATA

    ulong   count;
    ushort  tc[8];
    ushort  istxt[8];
    UINT    chances[8];

    void setup(TerrEditDoc *pd) { pDoc=pd; }

    BOOL    area;

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(RandomToolDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
    TerrEditDoc *pDoc;

        // Generated message map functions
        //{{AFX_MSG(RandomToolDlg)
        afx_msg void OnSelchangeToolTc0();
        afx_msg void OnSelchangeToolTc1();
        afx_msg void OnSelchangeToolTc2();
        afx_msg void OnSelchangeToolTc3();
        afx_msg void OnSelchangeToolTc4();
        afx_msg void OnSelchangeToolTc5();
        afx_msg void OnSelchangeToolTc6();
        afx_msg void OnSelchangeToolTc7();
        afx_msg void OnToolElvCutoffActive();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};


//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
// AngleToolDlg                                                             �
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
class AngleToolDlg : public CDialog
{
// Construction
public:
        AngleToolDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
        //{{AFX_DATA(AngleToolDlg)
        enum { IDD = IDD_TOOL_ANGLE };
        CEdit   m_elvlowCtl;
        CEdit   m_elvhighCtl;
        CButton m_elvcutoffCtl;
        CEdit   m_angle7Ctl;
        CEdit   m_angle6Ctl;
        CEdit   m_angle5Ctl;
        CEdit   m_angle4Ctl;
        CEdit   m_angle3Ctl;
        CEdit   m_angle2Ctl;
        CEdit   m_angle1Ctl;
        CEdit   m_angle0Ctl;
        CComboBox       m_tc7;
        CComboBox       m_tc6;
        CComboBox       m_tc5;
        CComboBox       m_tc4;
        CComboBox       m_tc3;
        CComboBox       m_tc2;
        CComboBox       m_tc1;
        CComboBox       m_tc0;
        float   m_angle_stop;
        float   m_angle0;
        float   m_angle1;
        float   m_angle2;
        float   m_angle3;
        float   m_angle4;
        float   m_angle5;
        float   m_angle6;
        float   m_angle7;
        BOOL    m_preserve;
        BOOL    m_elvcutoff;
        float   m_elvhigh;
        float   m_elvlow;
        //}}AFX_DATA

    ulong   count;
    ushort  tc[8];
    ushort  istxt[8];
    float   angles[8];

    void setup(TerrEditDoc *pd) { pDoc=pd; }

    BOOL    area;

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(AngleToolDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
    TerrEditDoc *pDoc;

        // Generated message map functions
        //{{AFX_MSG(AngleToolDlg)
        afx_msg void OnSelchangeToolTc0();
        afx_msg void OnSelchangeToolTc1();
        afx_msg void OnSelchangeToolTc2();
        afx_msg void OnSelchangeToolTc3();
        afx_msg void OnSelchangeToolTc4();
        afx_msg void OnSelchangeToolTc5();
        afx_msg void OnSelchangeToolTc6();
        afx_msg void OnSelchangeToolTc7();
        afx_msg void OnToolElvCutoff();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//葦� eof - eshtdlgx.h 憶�

