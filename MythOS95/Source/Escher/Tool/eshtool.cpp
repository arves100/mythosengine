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
// eshtool.cpp
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

#include "stdafx.h"
#include "eshtool.h"

#include "eshtmfrm.h"
#include "eshtdoc.h"
#include "eshtview.h"

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

#define VERSION "2.06"

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
// ToolApp                                                                  �
//���������������������������������������������������������������������������

BEGIN_MESSAGE_MAP(ToolApp, CWinApp)
        //{{AFX_MSG_MAP(ToolApp)
        ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
        //}}AFX_MSG_MAP
        // Standard file based document commands
        ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
        ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

//�������������������������������������������������������������������������Ŀ
// Global Data                                                              �
//���������������������������������������������������������������������������
ToolApp theApp;

MythosSystem    *MythOS=NULL;

ulong           BitDepth=8;
dword           AutoRotate=0;
float           AutoRotateSpeed=float(AUTOROTATE_SLOW);
Chronometer     Clock;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//���������������� Application Initialization/Termination �������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolApp - Constructor                                                    �
//���������������������������������������������������������������������������
ToolApp::ToolApp()
{
}


//�������������������������������������������������������������������������Ŀ
// ToolApp - InitInstance                                                   �
//���������������������������������������������������������������������������
BOOL ToolApp::InitInstance()
{
    MythOS = new MythosSystem();
    if (!MythOS)
        return FALSE;

    if (MythOS->init())
        return FALSE;

        // Standard initialization

        Enable3dControls();

        LoadStdProfileSettings();  // Load standard INI file options (including MRU)

        // Register document templates

        CSingleDocTemplate* pDocTemplate;
        pDocTemplate = new CSingleDocTemplate(
                IDR_MAINFRAME,
                RUNTIME_CLASS(ToolDoc),
                RUNTIME_CLASS(ToolFrame),       // main SDI frame window
                RUNTIME_CLASS(ToolView));
        AddDocTemplate(pDocTemplate);

        // Enable DDE Execute open
        EnableShellOpen();
        RegisterShellFileTypes(TRUE);

        // simple command line parsing
    if (strstr(m_lpCmdLine,"-demo"))
    {
        AutoRotate = AUTOROTATE_Y;
    }
    else
        AutoRotate = 0;

    if (strstr(m_lpCmdLine,"-8bpp"))
    {
        BitDepth=8;
    }
    else if (strstr(m_lpCmdLine,"-15bpp"))
    {
        BitDepth=15;
    }

        if (m_lpCmdLine[0] == '\0'
        || m_lpCmdLine[0] == '-')
        {
                // create a new (empty) document
                OnFileNew();
        }
        else
        {
                // open an existing document
                OpenDocumentFile(m_lpCmdLine);
        }

        // Enable drag/drop open
        m_pMainWnd->DragAcceptFiles();

        return TRUE;
}


//�������������������������������������������������������������������������Ŀ
// ToolApp - Run                                                            �
//���������������������������������������������������������������������������
int ToolApp::Run()
{
    ASSERT_VALID(this);

    if (m_pMainWnd == NULL && AfxOleGetUserCtrl())
    {
        // Not launched /Embedding or /Automation, but has no main window!
        TRACE0("Warning: m_pMainWnd is NULL in ToolApp::Run - quitting application");
        AfxPostQuitMessage(0);
    }

    // for tracking the idle time state
    LONG lIdleCount = 0;

    Clock.clear();

    // acquire and dispatch messages until a WM_QUIT message is received.
    for (;;)
    {
        // phase1: check to see if we can do idle work
        while (!::PeekMessage(&(AfxGetThreadState()->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE))
        {
            ((ToolFrame*)AfxGetMainWnd())->OnIdle();

            // call OnIdle while in bIdle state
            OnIdle(lIdleCount++);
        }
        // phase2: pump messages while available
        do
        {
            // pump message, but quit on WM_QUIT
            if (!PumpMessage())
                return ExitInstance();

            // reset "no idle" state after pumping "normal" message
            if (IsIdleMessage(&(AfxGetThreadState()->m_msgCur)))
            {
                lIdleCount = 0;
            }

        } while (::PeekMessage(&(AfxGetThreadState()->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE));
    }

    ASSERT(FALSE);  // not reachable
}


//�������������������������������������������������������������������������Ŀ
// ToolApp - ExitInstance                                                   �
//���������������������������������������������������������������������������
int ToolApp::ExitInstance()
{
    if (MythOS)
    {
        delete MythOS;
        MythOS = NULL;
    }

    return CWinApp::ExitInstance();
}



//���������������������������������������������������������������������������
//����������������������������� About Dialog ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// CAboutDlg                                                                �
//                                                                          �
// 'About Tool...' dialog.                                                  �
//���������������������������������������������������������������������������

class CAboutDlg : public CDialog
{
public:
        CAboutDlg();

// Dialog Data
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        CStatic m_verdate;
        //}}AFX_DATA

// Implementation
protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //{{AFX_MSG(CAboutDlg)
                // No message handlers
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
        //{{AFX_DATA_INIT(CAboutDlg)
        //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CAboutDlg)
        DDX_Control(pDX, IDC_ABOUT_VERSION, m_verdate);
        //}}AFX_DATA_MAP

    if (!pDX->m_bSaveAndValidate)
    {
        m_verdate.SetWindowText("Version " VERSION "     " __DATE__);
    }
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
        //{{AFX_MSG_MAP(CAboutDlg)
                // No message handlers
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()



//���������������������������������������������������������������������������
//������������������������� Main Application Handlers �����������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// ToolApp - OnAppAbout                                                     �
//���������������������������������������������������������������������������
void ToolApp::OnAppAbout()
{
        CAboutDlg aboutDlg;
        aboutDlg.DoModal();
}



//���������������������������������������������������������������������������
//������������������������� Charybdis Assert Routine ������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// _charybdis_assert
//
// Handler for failed asserts.  If msg is set to non-NULL, then an assertMyth
// was used with a comment.
//���������������������������������������������������������������������������
extern "C" void _charybdis_assert(char *msg, char *exp, char *f, unsigned ln)
{
    int     i;
    char    title[28];
    char    buff[988];

    sprintf(buff,"Assertion Failed\t\t\t\t\t\n"
                 "Expr:\t%s\n"
                 "File:\t%s\t\tLine %d",exp,f,ln);
    if (msg)
    {
        strcat(buff,
               "\nComment:\n");
        strcat(buff,msg);
    }
    strcat(buff,"\n\n\tOK to continue, Cancel to exit");

    sprintf(title,"%s Debug Message",theApp.m_pszAppName);

    i=MessageBox(NULL,
                 buff,
                 title,
                 MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONSTOP);

    if (i == IDCANCEL)
        ExitProcess(1);
}

//��� eof - eshtool.cpp ���
