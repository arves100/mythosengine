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
// eshtedit.cpp
//
// Terrain Editor main application class.
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
#include "eshtedit.h"

#include "eshtmfrm.h"
#include "eshtdoc.h"
#include "eshtview.h"

//���������������������������������������������������������������������������
//
//                                Equates
//
//���������������������������������������������������������������������������

#define VERSION "2.12"

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
// TerrEditApp                                                              �
//���������������������������������������������������������������������������

BEGIN_MESSAGE_MAP(TerrEditApp, CWinApp)
        //{{AFX_MSG_MAP(TerrEditApp)
        ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
                // NOTE - the ClassWizard will add and remove mapping macros here.
                //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
        // Standard file based document commands
        ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
        ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

//�������������������������������������������������������������������������Ŀ
// Global Data                                                              �
//���������������������������������������������������������������������������
TerrEditApp     theApp;

MythosSystem    *MythOS=NULL;

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//���������������� Application Initialization/Termination �������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// TerrEditApp - Constructor                                                �
//���������������������������������������������������������������������������
TerrEditApp::TerrEditApp()
{
}


//�������������������������������������������������������������������������Ŀ
// TerrEditApp - InitInstance                                               �
//���������������������������������������������������������������������������
BOOL TerrEditApp::InitInstance()
{
    MythOS = new MythosSystem();
    if (!MythOS)
        return FALSE;

    if (MythOS->init())
        return FALSE;

        // Standard initialization
        // If you are not using these features and wish to reduce the size
        //  of your final executable, you should remove from the following
        //  the specific initialization routines you do not need.

        //Enable3dControls();

        LoadStdProfileSettings();  // Load standard INI file options (including MRU)

        // Register the application's document templates.  Document templates
        //  serve as the connection between documents, frame windows and views.

        CSingleDocTemplate* pDocTemplate;
        pDocTemplate = new CSingleDocTemplate(
                IDR_MAINFRAME,
                RUNTIME_CLASS(TerrEditDoc),
                RUNTIME_CLASS(TerrMainFrame),       // main SDI frame window
                RUNTIME_CLASS(TerrEditView));
        AddDocTemplate(pDocTemplate);

        // Enable DDE Execute open
        EnableShellOpen();
        RegisterShellFileTypes(TRUE);

        // simple command line parsing
        if (m_lpCmdLine[0] == '\0')
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
// TerrEditApp - ExitInstance                                               �
//���������������������������������������������������������������������������
int TerrEditApp::ExitInstance()
{
    if (MythOS)
    {
        delete MythOS;
        MythOS = NULL;
    }

    return CWinApp::ExitInstance();
}


//�������������������������������������������������������������������������Ŀ
// TerrEditApp - LoadImage                                                  �
//���������������������������������������������������������������������������
BOOL TerrEditApp::LoadImage(const char *fname, XFBitmap *bm)
{
    ASSERT(fname != NULL && bm != NULL);

    // Create parser for input bitmap filename type
    XFParseBitmap *b;
    if (strstr(fname,".bmp") || strstr(fname,".BMP"))
    {
        b = new XFParseBMP(bm);
    }
    else if (strstr(fname,".cel") || strstr(fname,".CEL"))
    {
        b = new XFParseCEL(bm);
    }
    else if (strstr(fname,".lbm") || strstr(fname,".LBM"))
    {
        b = new XFParseLBM(bm);
    }
    else if (strstr(fname,".tga") || strstr(fname,".TGA"))
    {
        b = new XFParseTGA(bm);
    }
    else if (strstr(fname,".pcx") || strstr(fname,".PCX"))
    {
        b = new XFParsePCX(bm);
    }
    else
    {
        char str[256];
        sprintf(str,"Cannot read given input file:\n%s",fname);
        MessageBox(NULL, str, "Bitmap Load Error", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }

    // Read bitmap
    ASSERT(b);
    int err;
    if ((err=b->nameread(fname)) != 0)
    {
        char    str[256];

        sprintf(str,"Error %x reading input file:\n%s",err,fname);
        MessageBox(NULL,str, "Bitmap Load Error",
                   MB_OK | MB_ICONEXCLAMATION);
        delete b;
        return FALSE;
    }

    delete b;
    return TRUE;
}



//�������������������������������������������������������������������������Ŀ
// TerrEditApp - SaveImage                                                  �
//���������������������������������������������������������������������������
BOOL TerrEditApp::SaveImage(const char *fname, XFBitmap *bm)
{
    ASSERT(fname != NULL && bm != NULL);


    char tname[256];
    strcpy(tname, fname);
    char *tempname;

    tempname = tname;

    // Create parser for input bitmap filename type
    XFParseBitmap *b;
    if (strstr(fname,".bmp") || strstr(fname,".BMP"))
    {
        b = new XFParseBMP(bm);
    }
    else if ((strstr(fname,".cel") || strstr(fname,".CEL")) && bm->bpp == 1)
    {
        b = new XFParseCEL(bm);
    }
    else if ((strstr(fname,".lbm") || strstr(fname,".LBM")) && bm->bpp == 1)
    {
        b = new XFParseLBM(bm);
    }
    else if ((strstr(fname,".tga") || strstr(fname,".TGA"))
             && (bm->bpp == 2 || bm->bpp == 3))
    {
        b = new XFParseTGA(bm);

    }
    else if ((strstr(fname,".pcx") || strstr(fname,".PCX")) && bm->bpp == 1)
    {
        b = new XFParsePCX(bm);
    }
    else if (strstr(fname,"."))
    {
        char str[256];
        sprintf(str,"Cannot write given input file:\n%s",fname);
        MessageBox(NULL, str, "Bitmap Write Error", MB_OK | MB_ICONEXCLAMATION);
        return FALSE;
    }
    else
    {
        strcat(tname, ".BMP");
        b = new XFParseBMP(bm);
    }

    // Read bitmap
    ASSERT(b);
    int err;
    if ((err=b->namewrite(tempname)) != 0)
    {
        char    str[256];

        sprintf(str,"Error %x reading input file:\n%s",err,tempname);
        MessageBox(NULL,str, "Bitmap Load Error",
                   MB_OK | MB_ICONEXCLAMATION);
        delete b;
        return FALSE;
    }

    delete b;
    return TRUE;
}






//���������������������������������������������������������������������������
//����������������������������� About Dialog ��������������������������������
//���������������������������������������������������������������������������

//�������������������������������������������������������������������������Ŀ
// CAboutDlg                                                                �
//                                                                          �
// 'About Terrain Editor...' dialog.                                        �
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
// TerrEditApp - OnAppAbout                                                 �
//                                                                          �
// Display about dialog.                                                    �
//���������������������������������������������������������������������������
void TerrEditApp::OnAppAbout()
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

    i=MessageBox( (AfxGetMainWnd()) ? AfxGetMainWnd()->GetSafeHwnd() : NULL,
                 buff,
                 title,
                 MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONSTOP);

    if (i == IDCANCEL)
        ExitProcess(1);
}

//��� eof - eshtedit.cpp ���
