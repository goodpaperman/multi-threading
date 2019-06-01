// backprintDlg.h : header file
//

#if !defined(AFX_BACKPRINTDLG_H__1A778188_639F_487D_BE57_B0D6B8D54F1F__INCLUDED_)
#define AFX_BACKPRINTDLG_H__1A778188_639F_487D_BE57_B0D6B8D54F1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MtVerify.h" 

typedef struct
{
    HWND hDlg; 
    HWND hwndParent; 
    HDC hDC; 
    BOOL bPrint; 
    char szText[1024]; 
}ThreadPrintInfo; 

#define WM_SHOWBITMAP (WM_USER + 0x100) 

/////////////////////////////////////////////////////////////////////////////
// CBackprintDlg dialog

class CBackprintDlg : public CDialog
{
// Construction
public:
	CBackprintDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBackprintDlg)
	enum { IDD = IDD_BACKPRINT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackprintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
    void PrintText(HWND hwndParent, char* pszText); 

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBackprintDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileExit();
	afx_msg void OnFileAbout();
	afx_msg void OnClose();
	afx_msg void OnBtnDisplay();
	afx_msg void OnBtnPrint();
	//}}AFX_MSG
    afx_msg long OnShowBitmap(WPARAM wParam, LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKPRINTDLG_H__1A778188_639F_487D_BE57_B0D6B8D54F1F__INCLUDED_)
