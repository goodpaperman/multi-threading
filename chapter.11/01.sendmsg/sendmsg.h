// sendmsg.h : main header file for the SENDMSG application
//

#if !defined(AFX_SENDMSG_H__DE6D22D3_D6B1_41E4_8C2F_0879C3152204__INCLUDED_)
#define AFX_SENDMSG_H__DE6D22D3_D6B1_41E4_8C2F_0879C3152204__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSendmsgApp:
// See sendmsg.cpp for the implementation of this class
//

class CSendmsgApp : public CWinApp
{
public:
	CSendmsgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendmsgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSendmsgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMSG_H__DE6D22D3_D6B1_41E4_8C2F_0879C3152204__INCLUDED_)
