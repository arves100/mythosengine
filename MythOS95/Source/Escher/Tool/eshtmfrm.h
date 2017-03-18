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
// eshtmfrm.h
//
// Main window frame class.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

class ToolFrame : public CFrameWnd
{
protected: // create from serialization only
        ToolFrame();
        DECLARE_DYNCREATE(ToolFrame)

// Attributes
public:

// Operations
public:
    void OnIdle();

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ToolFrame)
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~ToolFrame();
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
        CStatusBar  m_wndStatusBar;
        CToolBar    m_wndToolBar;

// Generated message map functions
protected:
        //{{AFX_MSG(ToolFrame)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnFilePalette();
        afx_msg void OnAppHelp();
        afx_msg void OnFileCompress();
        afx_msg void OnUpdateFileCompress(CCmdUI* pCmdUI);
        afx_msg void OnFileTruecolor();
        afx_msg void OnUpdateFileTruecolor(CCmdUI* pCmdUI);
        afx_msg void OnFileFloating();
        afx_msg void OnUpdateFileFloating(CCmdUI* pCmdUI);
        afx_msg void OnFile15bit();
        afx_msg void OnUpdateFile15bit(CCmdUI* pCmdUI);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//��� eof - eshtmfrm.h ���
