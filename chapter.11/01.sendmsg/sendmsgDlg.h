// sendmsgDlg.h : header file
//

#if !defined(AFX_SENDMSGDLG_H__4E1FA7AB_1A5B_4676_A822_B9E638A4E168__INCLUDED_)
#define AFX_SENDMSGDLG_H__4E1FA7AB_1A5B_4676_A822_B9E638A4E168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_THREAD_MSG 0x8765

/////////////////////////////////////////////////////////////////////////////
// CSendmsgDlg dialog

class CSendmsgDlg : public CDialog
{
// Construction
public:
	CSendmsgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSendmsgDlg)
	enum { IDD = IDD_SENDMSG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendmsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSendmsgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSend();
	//}}AFX_MSG
    afx_msg LRESULT OnThreadMsg(LPARAM lParam, WPARAM wParam); 
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMSGDLG_H__4E1FA7AB_1A5B_4676_A822_B9E638A4E168__INCLUDED_)
