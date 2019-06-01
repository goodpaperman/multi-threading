// backprintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "backprint.h"
#include "backprintDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackprintDlg dialog

CBackprintDlg::CBackprintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackprintDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackprintDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBackprintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackprintDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBackprintDlg, CDialog)
	//{{AFX_MSG_MAP(CBackprintDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_FILE_EXIT, OnFileExit)
	ON_COMMAND(IDC_FILE_ABOUT, OnFileAbout)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_DISPLAY, OnBtnDisplay)
	ON_BN_CLICKED(IDC_BTN_PRINT, OnBtnPrint)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_SHOWBITMAP, OnShowBitmap) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackprintDlg message handlers

BOOL CBackprintDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

    //CMenu* pSysMenu = GetSystemMenu(FALSE);
    //if (pSysMenu != NULL)
    //{
    //    CString strAboutMenu;
    //    strAboutMenu.LoadString(IDS_ABOUTBOX);
    //    if (!strAboutMenu.IsEmpty())
    //    {
    //        pSysMenu->AppendMenu(MF_SEPARATOR);
    //        pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    //    }
    //}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBackprintDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

//HBITMAP g_bmp = 0; 

HBITMAP gbmpDisplay;
RECT gDisplayRect;

// Height of bitmap returned by DrawText
int iHeight;

void CBackprintDlg::OnPaint() 
{
    //if (IsIconic())
    //{
    //    CPaintDC dc(this); // device context for painting

    //    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

    //    // Center icon in client rectangle
    //    int cxIcon = GetSystemMetrics(SM_CXICON);
    //    int cyIcon = GetSystemMetrics(SM_CYICON);
    //    CRect rect;
    //    GetClientRect(&rect);
    //    int x = (rect.Width() - cxIcon + 1) / 2;
    //    int y = (rect.Height() - cyIcon + 1) / 2;

    //    // Draw the icon
    //    dc.DrawIcon(x, y, m_hIcon);
    //}
    //else
    //{
    //    CDialog::OnPaint();
    //}

    //if(g_bmp)
    //{
    //    CPaintDC dc(this); 
    //    CRect rect; 
    //    GetDlgItem(IDC_OUTPUT)->GetWindowRect(rect); 
    //    ScreenToClient(rect); 
        
    //    //RECT rectMem = *(RECT*)wParam; 
    //    HBITMAP hbmp = g_bmp; //(HBITMAP)lParam; 
    //    HDC hMem = (HDC)::CreateCompatibleBitmap(dc.m_hDC, rect.Height(), rect.Width()); 
    //    HBITMAP hbmpOld = (HBITMAP)::SelectObject(hMem, hbmp); 
    //    BitBlt(dc.m_hDC, 
    //        rect.left, 
    //        rect.top, 
    //        rect.right, 
    //        rect.bottom, 
    //        hMem, 0, 0, SRCCOPY); 
        
    //    ::SelectObject(hMem, hbmpOld); 
    //    ::DeleteDC(hMem); 
    //    //::ReleaseDC(m_hWnd, hDC); 
    //}
    
    PAINTSTRUCT paint;
    HWND hwndCtrl;
	HDC hdc;
    HDC hDcMem;
    HBITMAP bmpOld;
    RECT rect;
    POINT point;

	if (!gbmpDisplay)
		return;

    HWND hwnd = m_hWnd; 
    hwndCtrl = ::GetDlgItem(hwnd, IDC_OUTPUT);

    hdc = ::BeginPaint(hwnd, &paint);

    ::GetWindowRect(hwndCtrl, &rect);
    point = *((POINT *)&rect);
    ::ScreenToClient(hwnd, &point);

    hDcMem = ::CreateCompatibleDC(NULL);
    bmpOld = (HBITMAP)::SelectObject(hDcMem, gbmpDisplay);

    // Copy bitmap to screen
    MTVERIFY( ::BitBlt(hdc, point.x+10, point.y+40,
        gDisplayRect.right-gDisplayRect.left, gDisplayRect.bottom-gDisplayRect.top,
        hDcMem, iHeight, 0, SRCCOPY) );

    ::SelectObject(hDcMem, bmpOld);
    ::DeleteDC(hDcMem);

    ::EndPaint(hwnd, &paint);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBackprintDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBackprintDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	SendMessage(WM_CLOSE); 
}

void CBackprintDlg::OnFileAbout() 
{
	// TODO: Add your command handler code here
	CDialog dlg(IDD_ABOUTBOX); 
    dlg.DoModal(); 
}

HANDLE gPrintJob[64] = { 0 }; 
int gNumPrinting = 0 ; 
DWORD WINAPI BackgroundPrintThread(LPVOID pVoid); 

//
// Asks user which printer to use, then creates 
// background printing thread.
// 
void CBackprintDlg::PrintText(HWND hwndParent, char* pszText)
{
    ThreadPrintInfo* pInfo; 
    HANDLE hThread; 
    DWORD dwThreadId; 
    int result; 
    DOCINFO docInfo; 

    PRINTDLG dlgPrint; 
    // put up common dialog for printing and get hDC.
    memset(&dlgPrint, 0, sizeof(PRINTDLG)); 
    dlgPrint.lStructSize = sizeof(PRINTDLG); 
    dlgPrint.hwndOwner = hwndParent; 
    dlgPrint.Flags = PD_ALLPAGES | PD_USEDEVMODECOPIES | 
        PD_NOPAGENUMS | PD_NOSELECTION | PD_RETURNDC; 
    //dlgPrint.hInstance = AfxGetInstanceHandle(); //hInst; 
    if(!PrintDlg(&dlgPrint))
        return; 

    // Initialize Printer device 
    docInfo.cbSize = sizeof(DOCINFO); 
    docInfo.lpszDocName = "Background Printing Example"; 
    docInfo.lpszOutput = NULL; 
    docInfo.lpszDatatype = NULL; 
    docInfo.fwType = 0; 
    result = StartDoc(dlgPrint.hDC, &docInfo); 
    result = StartPage(dlgPrint.hDC); 
    
    pInfo = (ThreadPrintInfo*)HeapAlloc(GetProcessHeap(), 
        HEAP_ZERO_MEMORY, 
        sizeof(ThreadPrintInfo)); 
    pInfo->hDlg = hwndParent; 
    pInfo->hwndParent = hwndParent; 
    pInfo->hDC = dlgPrint.hDC; 
    pInfo->bPrint = TRUE; 
    strcpy(pInfo->szText, pszText); 

    MTVERIFY(hThread = CreateThread(NULL, 0, 
        BackgroundPrintThread, (LPVOID)pInfo, 
        0, &dwThreadId)); 

    // keep track of all background printing threads 
    gPrintJob[gNumPrinting++] = hThread; 
}


DWORD WINAPI BackgroundPrintThread(LPVOID pVoid)
{
    ThreadPrintInfo* pInfo = (ThreadPrintInfo*) pVoid; 
    RECT rect; 
    RECT rectMem; 
    HDC hDCMem; 
    HBITMAP bmpMem; 
    HBITMAP bmpOld; 
    int x, y; 
    int counter = 0; 
    int nHeight; 
    HFONT hFont; 
    HFONT hFontOld; 

    // Get dimensions of paper into rect 
    rect.left = 0; 
    rect.top = 0; 
    rect.right = GetDeviceCaps(pInfo->hDC, HORZRES); 
    rect.bottom = GetDeviceCaps(pInfo->hDC, VERTRES); 
    nHeight = -MulDiv(36, GetDeviceCaps(pInfo->hDC, LOGPIXELSY), 72); 

    // Create Font 
    hFont = CreateFont(nHeight, 0, 
        0, 0, FW_DONTCARE, 
        FALSE, FALSE, FALSE, 
        ANSI_CHARSET, 
        OUT_TT_PRECIS, 
        CLIP_DEFAULT_PRECIS, 
        PROOF_QUALITY, 
        VARIABLE_PITCH, 
        NULL); 
    MTASSERT(hFont != 0); 

    // Draw into memory device context 
    hDCMem = CreateCompatibleDC(pInfo->hDC); 
    hFontOld = (HFONT)SelectObject(hDCMem, hFont); 
    iHeight = DrawText(hDCMem, pInfo->szText, -1, &rect, DT_LEFT | DT_NOPREFIX | DT_WORDBREAK | DT_CALCRECT); 
    rectMem = rect; 
    rectMem.left = rect.left + iHeight; 
    rectMem.right = rect.right + iHeight * 2; 
    bmpMem = CreateCompatibleBitmap(hDCMem, rectMem.right, rect.bottom); 
    bmpOld = (HBITMAP)SelectObject(hDCMem, bmpMem); 
    OffsetRect(&rect, iHeight, 0); 
    DrawText(hDCMem, pInfo->szText, -1, &rect, 
        DT_LEFT | DT_NOPREFIX | DT_WORDBREAK); 

    // Italicize bitmap. We use GetPixel and 
    // SetPixel because they are horribly inefficient, 
    // thereby causing the thread to run for awhile.
    for(y=0; y<iHeight; y++)
    {
        // Italicize line y 
        for(x=rectMem.right; x>iHeight; x--)
        {
            // Move specified pixel to the right.
            COLORREF color; 
            int offset; 
            offset = y - iHeight; 
            color = GetPixel(hDCMem, x + offset, y); 
            if(color != 0)
                counter++; 

            SetPixel(hDCMem, x, y, color); 
        }

        //Sleep(20); 
    }
    MTASSERT(counter > 0); 

    // Copy bitmap of italicized text from memory to device.
    if(pInfo->bPrint)
    {
        BitBlt(pInfo->hDC, 50, 50, rectMem.right - rect.left, 
            rectMem.bottom - rect.top, 
            hDCMem, iHeight, 0, SRCCOPY); 
    }

    SelectObject(hDCMem, hFontOld); 
    SelectObject(hDCMem, bmpOld); 
    DeleteDC(hDCMem); 

    if(!pInfo->bPrint)
    {
        // We can't just write to the global variable where ths 
        // bitmap is kept or we might overwrite the work of 
        // another thread, thereby "losing" a bitmap 

        // Also, if we used PostMessage instead of SendMessage, then 
        // the rectangle could have been deleted (it's on the stack) 
        // by the time the main message loop is reached. 
        SendMessage(pInfo->hDlg, WM_SHOWBITMAP, (WPARAM)&rectMem, 
            (LPARAM)bmpMem); 
    }

    if(pInfo->bPrint)
    {
        // Finish printing 
        int result; 
        result = EndPage(pInfo->hDC); 
        MTASSERT(result != SP_ERROR); 
        result = EndDoc(pInfo->hDC); 
        MTASSERT(result != SP_ERROR); 
        DeleteDC(pInfo->hDC); 

        // If we are printing, we are done with the bitmap.
        DeleteObject(bmpMem); 
    }
    else 
        ReleaseDC(pInfo->hwndParent, pInfo->hDC); 

    // free data structure passed in.
    HeapFree(GetProcessHeap(), 0, pInfo); 
    return 0; 
}

void CBackprintDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	int index; 
    for(index = 0; index < gNumPrinting; index++)
    {
        DWORD status; 
        //do
        //{
        //    MTVERIFY(GetExitCodeThread(gPrintJob[index], &status)); 
        //    //Sleep(10); 
        //}while(status == STILL_ACTIVE); 
        MTVERIFY(GetExitCodeThread(gPrintJob[index], &status)); 
        if(status == STILL_ACTIVE)
            return; 
    }

	CDialog::OnClose();
}

void CBackprintDlg::OnBtnDisplay() 
{
	// TODO: Add your control notification handler code here
    CString str; 
    GetDlgItemText(IDC_EDIT_TEXT, str); 
    CDC* pDC = GetDC(); 

    ThreadPrintInfo* pInfo; 
    HANDLE hThread; 
    DWORD dwThreadId; 
    pInfo = (ThreadPrintInfo*)HeapAlloc(GetProcessHeap(), 
        HEAP_ZERO_MEMORY, 
        sizeof(ThreadPrintInfo)); 
    pInfo->hDlg = m_hWnd; 
    pInfo->hwndParent = m_hWnd; 
    pInfo->hDC = pDC->m_hDC; 
    pInfo->bPrint = FALSE; 
    strcpy(pInfo->szText, str); 

    MTVERIFY(hThread = CreateThread(NULL, 0, 
        BackgroundPrintThread, (LPVOID)pInfo, 
        0, &dwThreadId)); 

    // keep track of all background printing threads 
    gPrintJob[gNumPrinting++] = hThread; 
}

void CBackprintDlg::OnBtnPrint() 
{
	// TODO: Add your control notification handler code here
    CString str; 
    GetDlgItemText(IDC_EDIT_TEXT, str); 
	PrintText(m_hWnd, str.LockBuffer()); 	
    str.UnlockBuffer(); 
}


long CBackprintDlg::OnShowBitmap(WPARAM wParam, LPARAM lParam)
{
    //if(g_bmp)
    //    DeleteObject(g_bmp); 

    //g_bmp = (HBITMAP)wParam; 
    //Invalidate(); 
    
    if (gbmpDisplay)
        DeleteObject(gbmpDisplay);
    
    gDisplayRect = *(RECT*)wParam;
    gbmpDisplay = (HBITMAP) lParam;
    ::InvalidateRect(m_hWnd, NULL, TRUE);
    return 0; 
}
