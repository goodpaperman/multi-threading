#if !defined(AFX_DEMOTHREAD_H__DBDC6903_D842_4362_8865_770024FF8EB7__INCLUDED_)
#define AFX_DEMOTHREAD_H__DBDC6903_D842_4362_8865_770024FF8EB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DemoThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDemoThread thread

class CDemoThread : public CWinThread
{
	DECLARE_DYNCREATE(CDemoThread)
protected:
	CDemoThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDemoThread();

	// Generated message map functions
	//{{AFX_MSG(CDemoThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOTHREAD_H__DBDC6903_D842_4362_8865_770024FF8EB7__INCLUDED_)
