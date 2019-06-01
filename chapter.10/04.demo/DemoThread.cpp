// DemoThread.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DemoThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoThread

IMPLEMENT_DYNCREATE(CDemoThread, CWinThread)

CDemoThread::CDemoThread()
{
    m_bAutoDelete = TRUE; 
}

CDemoThread::~CDemoThread()
{
}

BOOL CDemoThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
    TRACE("Thread InitInstance()\n"); 
	return FALSE;
}

int CDemoThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
    TRACE("Thread ExitInstance()\n");
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDemoThread, CWinThread)
	//{{AFX_MSG_MAP(CDemoThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoThread message handlers
