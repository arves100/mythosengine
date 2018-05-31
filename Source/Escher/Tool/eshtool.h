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
// eshtool.h
//
// Escher Tool main application class.
//
// The application class controls the overall application and flow of
// control.
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#ifndef __AFXWIN_H__
        #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

#define AUTOROTATE_X    0x1
#define AUTOROTATE_Y    0x2
#define AUTOROTATE_Z    0x4

#define AUTOROTATE_FAST 90
#define AUTOROTATE_SLOW 30

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

class ToolApp : public CWinApp
{
public:
        ToolApp();

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(ToolApp)
        public:
        virtual BOOL InitInstance();
        virtual int ExitInstance();
        virtual int Run();
        //}}AFX_VIRTUAL

// Implementation

        //{{AFX_MSG(ToolApp)
        afx_msg void OnAppAbout();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//��� eof - eshtool.h ���
