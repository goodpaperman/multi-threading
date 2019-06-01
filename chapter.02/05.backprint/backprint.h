// backprint.h : main header file for the BACKPRINT application
//

#if !defined(AFX_BACKPRINT_H__7FE40E98_ADB8_4397_AECE_A3C9E9CA8CA6__INCLUDED_)
#define AFX_BACKPRINT_H__7FE40E98_ADB8_4397_AECE_A3C9E9CA8CA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBackprintApp:
// See backprint.cpp for the implementation of this class
//

class CBackprintApp : public CWinApp
{
public:
	CBackprintApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackprintApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBackprintApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKPRINT_H__7FE40E98_ADB8_4397_AECE_A3C9E9CA8CA6__INCLUDED_)
